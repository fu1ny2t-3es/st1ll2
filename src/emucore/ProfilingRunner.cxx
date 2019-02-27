//============================================================================
//
//   SSSS    tt          lll  lll
//  SS  SS   tt           ll   ll
//  SS     tttttt  eeee   ll   ll   aaaa
//   SSSS    tt   ee  ee  ll   ll      aa
//      SS   tt   eeeeee  ll   ll   aaaaa  --  "An Atari 2600 VCS Emulator"
//  SS  SS   tt   ee      ll   ll  aa  aa
//   SSSS     ttt  eeeee llll llll  aaaaa
//
// Copyright (c) 1995-2019 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//============================================================================

#include <chrono>

#include "ProfilingRunner.hxx"
#include "FSNode.hxx"
#include "CartDetector.hxx"
#include "Cart.hxx"
#include "MD5.hxx"
#include "Control.hxx"
#include "M6502.hxx"
#include "M6532.hxx"
#include "TIA.hxx"
#include "ConsoleTiming.hxx"
#include "DummyFrameManager.hxx"
#include "System.hxx"
#include "Joystick.hxx"
#include "Random.hxx"
#include "DispatchResult.hxx"

using namespace std::chrono;

namespace {
  static constexpr uInt32 RUNTIME_DEFAULT = 60;
  static constexpr uInt32 cyclesPerSecond = 262 * 76 * 60;

  void updateProgress(uInt32 from, uInt32 to) {
    while (from < to) {
      if (from % 10 == 0 && from > 0) cout << from << "%";
      else cout << ".";

      cout.flush();

      from++;
    }
  }
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
ProfilingRunner::ProfilingRunner(int argc, char* argv[])
  : profilingRuns(std::max(argc - 2, 0))
{
  for (int i = 2; i < argc; i++) {
    ProfilingRun& run(profilingRuns[i-2]);

    string arg = argv[i];
    size_t splitPoint = arg.find_first_of(":");

    run.romFile = splitPoint == string::npos ? arg : arg.substr(0, splitPoint);

    if (splitPoint == string::npos) run.runtime = RUNTIME_DEFAULT;
    else  {
      int runtime = atoi(arg.substr(splitPoint+1, string::npos).c_str());
      run.runtime = runtime > 0 ? runtime : RUNTIME_DEFAULT;
    }
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ProfilingRunner::run()
{
  cout << "Profiling Stella..." << endl;

  for (ProfilingRun& run : profilingRuns) {
    cout << endl << "running " << run.romFile << " for " << run.runtime << " seconds..." << endl;

    if (!runOne(run)) return false;
  }

  return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool ProfilingRunner::runOne(const ProfilingRun run)
{
  FilesystemNode imageFile(run.romFile);

  if (!imageFile.isFile()) {
    cout << "ERROR: " << run.romFile << " is not a ROM image" << endl;
    return false;
  }

  BytePtr image;
  uInt32 size = imageFile.read(image);
  if (size == 0) {
    cout << "ERROR: unable to read " << run.romFile << endl;
    return false;
  }

  string md5 = MD5::hash(image, size);
  string type = "";
  unique_ptr<Cartridge> cartridge = CartDetector::create(imageFile, image, size, md5, type, mySettings);

  if (!cartridge) {
    cout << "ERROR: unable to determine cartridge type" << endl;
    return false;
  }

  IO consoleIO;
  Random rng(0);
  Event event;
  DummyFrameManager frameManager;

  M6502 cpu(mySettings);
  M6532 riot(consoleIO, mySettings);
  TIA tia(consoleIO, []() { return ConsoleTiming::ntsc; }, mySettings);
  System system(rng, cpu, riot, tia, *cartridge);

  consoleIO.myLeftControl = make_unique<Joystick>(Controller::Left, event, system);
  consoleIO.myRightControl = make_unique<Joystick>(Controller::Right, event, system);
  consoleIO.mySwitches = make_unique<Switches>(event, myProps, mySettings);

  tia.setFrameManager(&frameManager);
  tia.bindToControllers();
  cartridge->setStartBankFromPropsFunc([]() { return -1; });

  system.initialize();
  system.reset();

  uInt64 cycles = 0;
  uInt64 cyclesTarget = run.runtime * cyclesPerSecond;

  DispatchResult dispatchResult;
  dispatchResult.setOk(0);

  uInt32 percent = 0;
  (cout << "0%").flush();

  time_point<high_resolution_clock> tp = high_resolution_clock::now();

  while (cycles < cyclesTarget && dispatchResult.getStatus() == DispatchResult::Status::ok) {
    tia.update(dispatchResult);
    cycles += dispatchResult.getCycles();

    uInt32 percentNow = std::min((100 * cycles) / cyclesTarget, static_cast<uInt64>(100));
    updateProgress(percent, percentNow);

    percent = percentNow;
  }

  double realtimeUsed = duration_cast<duration<double>>(high_resolution_clock::now () - tp).count();

  if (dispatchResult.getStatus() != DispatchResult::Status::ok) {
    cout << endl << "ERROR: emulation failed after " << cycles << " cycles";
    return false;
  }

  (cout << "100%" << endl).flush();
  cout << "real time: " << realtimeUsed << " seconds" << endl;

  return true;
}
