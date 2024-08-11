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
// Copyright (c) 1995-2024 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//============================================================================

#include <sstream>

#ifdef DUMP_ELF
#include <ofstream>
#endif

#include "System.hxx"
#include "ElfLinker.hxx"
#include "ElfEnvironment.hxx"
#include "Logger.hxx"
#include "Props.hxx"
#include "Settings.hxx"
#include "exception/FatalEmulationError.hxx"

#include "CartELF.hxx"

#define DUMP_ELF

using namespace elfEnvironment;

namespace {
  constexpr size_t TRANSACTION_QUEUE_CAPACITY = 16384;
  constexpr uInt32 ARM_RUNAHED_MIN = 3;
  constexpr uInt32 ARM_RUNAHED_MAX = 6;

#ifdef DUMP_ELF
  void dumpElf(const ElfFile& elf)
  {
    cout << "\nELF sections:\n\n";

    size_t i = 0;
    for (const auto& section: elf.getSections()) {
      if (section.type != 0x00) cout << i << " " << section << '\n';
      i++;
    }

    auto symbols = elf.getSymbols();
    cout << "\nELF symbols:\n\n";
    if (!symbols.empty()) {
      i = 0;
      for (auto& symbol: symbols)
        cout << (i++) << " " << symbol << '\n';
    }

    i = 0;
    for (const auto& section: elf.getSections()) {
      auto rels = elf.getRelocations(i++);
      if (!rels) continue;

      cout
        << "\nELF relocations for section "
        << section.name << ":\n\n";

      for (auto& rel: *rels) cout << rel << '\n';
    }
  }

  void dumpLinkage(const ElfParser& parser, const ElfLinker& linker)
  {
    cout << std::hex << std::setfill('0');

    cout
      << "\ntext segment size: 0x" << std::setw(8) << linker.getSegmentSize(ElfLinker::SegmentType::text)
      << "\ndata segment size: 0x" << std::setw(8) << linker.getSegmentSize(ElfLinker::SegmentType::data)
      << "\nrodata segment size: 0x" << std::setw(8) << linker.getSegmentSize(ElfLinker::SegmentType::rodata)
      << '\n';

    cout << "\nrelocated sections:\n\n";

    const auto& sections = parser.getSections();
    const auto& relocatedSections = linker.getRelocatedSections();

    for (size_t i = 0; i < sections.size(); i++) {
      if (!relocatedSections[i]) continue;

      cout
        << sections[i].name
        << " @ 0x"<< std::setw(8)
        << (relocatedSections[i]->offset + linker.getSegmentBase(relocatedSections[i]->segment))
        << " size 0x" << std::setw(8) << sections[i].size << '\n';
    }

    cout << "\nrelocated symbols:\n\n";

    const auto& symbols = parser.getSymbols();
    const auto& relocatedSymbols = linker.getRelocatedSymbols();

    for (size_t i = 0; i < symbols.size(); i++) {
      if (!relocatedSymbols[i]) continue;

      cout
        << symbols[i].name
        << " = 0x" << std::setw(8) << relocatedSymbols[i]->value;

      if (relocatedSymbols[i]->segment) {
        switch (*relocatedSymbols[i]->segment) {
          case ElfLinker::SegmentType::text:
            cout << " (text)";
            break;

          case ElfLinker::SegmentType::data:
            cout << " (data)";
            break;

          case ElfLinker::SegmentType::rodata:
            cout << " (rodata)";
            break;
        }
      } else {
        cout << " (abs)";
      }

      cout << '\n';
    }

    const auto& initArray = linker.getInitArray();
    const auto& preinitArray = linker.getPreinitArray();

    if (!initArray.empty()) {
      cout << "\ninit array:\n\n";

      for (const uInt32 address: initArray)
        cout << " * 0x" << std::setw(8) <<  address << '\n';
    }

    if (!preinitArray.empty()) {
      cout << "\npreinit array:\n\n";

      for (const uInt32 address: preinitArray)
        cout << " * 0x" << std::setw(8) <<  address << '\n';
    }

    cout << std::dec;
  }

  void writeDebugBinary(const ElfLinker& linker)
  {
    constexpr size_t IMAGE_SIZE = 4L * 0x00100000;
    static const char* IMAGE_FILE_NAME = "elf_executable_image.bin";

    auto binary = make_unique<uInt8[]>(IMAGE_SIZE);
    std::memset(binary.get(), 0, IMAGE_SIZE);

    for (auto segment: {ElfLinker::SegmentType::text, ElfLinker::SegmentType::data, ElfLinker::SegmentType::rodata})
      std::memcpy(
        binary.get() + linker.getSegmentBase(segment),
        linker.getSegmentData(segment),
        linker.getSegmentSize(segment)
      );

    {
      std::ofstream binaryFile;

      binaryFile.open(IMAGE_FILE_NAME);
      binaryFile.write(reinterpret_cast<const char*>(binary.get()), 4L * 0x00100000);
    }

    cout << "wrote executable image to " << IMAGE_FILE_NAME << '\n';
  }
#endif

  SystemType determineSystemType(const Properties* props)
  {
    if (!props) return SystemType::ntsc;

    string displayFormat = props->get(PropType::Display_Format);

    if(displayFormat == "PAL" || displayFormat == "SECAM") return SystemType::pal;
    if(displayFormat == "PAL60") return SystemType::pal60;

    return SystemType::ntsc;
  }

  uInt32 getSystemTypeParam(SystemType systemType)
  {
    switch (systemType) {
      case SystemType::ntsc:
        return ST_NTSC_2600;

      case SystemType::pal:
        return ST_PAL_2600;

      case SystemType::pal60:
        return ST_PAL60_2600;

      default:
        throw runtime_error("invalid system type");
    }
  }

  uInt32 get6502SpeedHz(ConsoleTiming timing) {
    switch (timing) {
      case ConsoleTiming::ntsc:
        return 262 * 76 * 60;

      case ConsoleTiming::pal:
      case ConsoleTiming::secam:
        return 312 * 76 * 50;

      default:
        throw runtime_error("invalid console timing");
    }
  }
}  // namespace

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
CartridgeELF::CartridgeELF(const ByteBuffer& image, size_t size, string_view md5,
                           const Settings& settings)
  : Cartridge(settings, md5), myImageSize(size), myTransactionQueue(TRANSACTION_QUEUE_CAPACITY),
    myVcsLib(myTransactionQueue)
{
  myImage = make_unique<uInt8[]>(size);
  std::memcpy(myImage.get(), image.get(), size);

  myLastPeekResult = make_unique<uInt8[]>(0x1000);
  std::fill_n(myLastPeekResult.get(), 0x1000, 0);

  createRomAccessArrays(0x1000);

  parseAndLinkElf();
  allocationSections();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
CartridgeELF::~CartridgeELF() = default;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CartridgeELF::reset()
{
  const bool devMode = mySettings.getBool("dev.settings");
  const bool strictMode = devMode && mySettings.getBool("dev.thumb.trapfatal");
  const uInt32 mips = devMode ? mySettings.getInt("dev.arm.mips") : MIPS_MAX;

  std::fill_n(myLastPeekResult.get(), 0x1000, 0);
  myIsBusDriven = false;
  myDriveBusValue = 0;
  myArmCyclesOffset = 0;
  myArmCyclesPer6502Cycle = (mips * 1000000) / get6502SpeedHz(myConsoleTiming);

  mySystemType = determineSystemType(myProperties);
  myLinker->relink(externalSymbols(mySystemType));

  std::memset(mySectionStack.get(), 0, STACK_SIZE);
  std::memset(mySectionText.get(), 0, TEXT_SIZE);
  std::memset(mySectionData.get(), 0, DATA_SIZE);
  std::memset(mySectionRodata.get(), 0, RODATA_SIZE);
  std::memset(mySectionTables.get(), 0, TABLES_SIZE);

  std::memcpy(mySectionText.get(), myLinker->getSegmentData(ElfLinker::SegmentType::text),
                                   myLinker->getSegmentSize(ElfLinker::SegmentType::text));
  std::memcpy(mySectionData.get(), myLinker->getSegmentData(ElfLinker::SegmentType::data),
                                   myLinker->getSegmentSize(ElfLinker::SegmentType::data));
  std::memcpy(mySectionRodata.get(), myLinker->getSegmentData(ElfLinker::SegmentType::rodata),
                                     myLinker->getSegmentSize(ElfLinker::SegmentType::rodata));
  std::memcpy(mySectionTables.get(), LOOKUP_TABLES, sizeof(LOOKUP_TABLES));

  setupMemoryMap(strictMode);
  myCortexEmu.reset();

  myTransactionQueue
    .reset()
	  .injectROMAt(0x00, 0x1ffc)
	  .injectROM(0x10)
    .setNextInjectAddress(0x1000);

  myVcsLib.reset();

  myVcsLib.vcsCopyOverblankToRiotRam();
  myVcsLib.vcsStartOverblank();
  myVcsLib.vcsEndOverblank();
  myVcsLib.vcsNop2n(1024);

  myExecutionStage = ExecutionStage::boot;
  myInitFunctionIndex = 0;

  switchExecutionStage();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CartridgeELF::install(System& system)
{
  mySystem = &system;

  for (uInt16 addr = 0; addr < 0x1000; addr += System::PAGE_SIZE) {
    System::PageAccess access(this, System::PageAccessType::READ);
    access.romPeekCounter = &myRomAccessCounter[addr];
    access.romPokeCounter = &myRomAccessCounter[addr];

    mySystem->setPageAccess(0x1000 + addr, access);
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool CartridgeELF::save(Serializer& out) const
{
  return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool CartridgeELF::load(Serializer& in)
{
  return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
uInt8 CartridgeELF::peek(uInt16 address)
{
  // The actual handling happens in overdrivePeek
  return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
uInt8 CartridgeELF::peekOob(uInt16 address)
{
  return myLastPeekResult[address & 0xfff];
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool CartridgeELF::poke(uInt16 address, uInt8 value)
{
  return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CartridgeELF::consoleChanged(ConsoleTiming timing)
{
  myConsoleTiming = timing;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
const ByteBuffer& CartridgeELF::getImage(size_t& size) const
{
  size = myImageSize;
  return myImage;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
uInt8 CartridgeELF::overdrivePeek(uInt16 address, uInt8 value)
{
  value = driveBus(address, value);

  if (address & 0x1000) {
    if (!myIsBusDriven) value = mySystem->getDataBusState();
    myLastPeekResult[address & 0xfff] = value;
  }

  return value;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
uInt8 CartridgeELF::overdrivePoke(uInt16 address, uInt8 value)
{
  return driveBus(address, value);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
CortexM0::err_t CartridgeELF::BusFallbackDelegate::fetch16(
  uInt32 address, uInt16& value, uInt8& op, CortexM0& cortex
) {
  if (address == (RETURN_ADDR & ~1)) return CortexM0::errCustom(ERR_RETURN);

  return handleError("fetch16", address, CortexM0::ERR_UNMAPPED_FETCH16, cortex);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
CortexM0::err_t CartridgeELF::BusFallbackDelegate::read8(uInt32 address, uInt8& value, CortexM0& cortex)
{
  return handleError("read8", address, CortexM0::ERR_UNMAPPED_READ8, cortex);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
CortexM0::err_t CartridgeELF::BusFallbackDelegate::read16(uInt32 address, uInt16& value, CortexM0& cortex)
{
  return handleError("read16", address, CortexM0::ERR_UNMAPPED_READ16, cortex);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
CortexM0::err_t CartridgeELF::BusFallbackDelegate::read32(uInt32 address, uInt32& value, CortexM0& cortex)
{
  return handleError("read32", address, CortexM0::ERR_UNMAPPED_READ32, cortex);
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
CortexM0::err_t CartridgeELF::BusFallbackDelegate::write8(uInt32 address, uInt8 value, CortexM0& cortex)
{
  return handleError("write8", address, CortexM0::ERR_UNMAPPED_WRITE8, cortex);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
CortexM0::err_t CartridgeELF::BusFallbackDelegate::write16(uInt32 address, uInt16 value, CortexM0& cortex)
{
  return handleError("write16", address, CortexM0::ERR_UNMAPPED_WRITE16, cortex);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
CortexM0::err_t CartridgeELF::BusFallbackDelegate::write32(uInt32 address, uInt32 value, CortexM0& cortex)
{
  return handleError("write32", address, CortexM0::ERR_UNMAPPED_WRITE32, cortex);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CartridgeELF::BusFallbackDelegate::setErrorsAreFatal(bool fatal)
{
  myErrorsAreFatal = fatal;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
CortexM0::err_t CartridgeELF::BusFallbackDelegate::handleError(
  string_view accessType, uInt32 address, CortexM0::err_t err, CortexM0& cortex
) const {
  if (myErrorsAreFatal) return CortexM0::errIntrinsic(err, address);

  stringstream s;

  s
    << "invalid " << accessType << " access to 0x"
    << std::hex << std::setw(8) << std::setfill('0') << address
    << " (PC = 0x"
    << std::hex << std::setw(8) << std::setfill('0') << cortex.getRegister(15)
    << ")";

  Logger::error(s.str());

  return CortexM0::ERR_NONE;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
inline uInt64 CartridgeELF::getArmCycles() const
{
  return myCortexEmu.getCycles() + myArmCyclesOffset;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
inline uInt8 CartridgeELF::driveBus(uInt16 address, uInt8 value)
{
  auto* nextTransaction = myTransactionQueue.getNextTransaction(address,
    mySystem->cycles() * myArmCyclesPer6502Cycle - myArmCyclesOffset);
  if (nextTransaction) {
    nextTransaction->setBusState(myIsBusDriven, myDriveBusValue);
    myArmCyclesOffset = mySystem->cycles() * myArmCyclesPer6502Cycle - nextTransaction->timestamp;
  }

  if (myIsBusDriven) value |= myDriveBusValue;

  myVcsLib.updateBus(address, value);

  runArm();

  return value;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CartridgeELF::parseAndLinkElf()
{
  try {
    myElfParser.parse(myImage.get(), myImageSize);
  } catch (ElfParser::ElfParseError& e) {
    throw runtime_error("failed to initialize ELF: " + string(e.what()));
  }

#ifdef DUMP_ELF
  dumpElf(myElfParser);
#endif

  myLinker = make_unique<ElfLinker>(ADDR_TEXT_BASE, ADDR_DATA_BASE, ADDR_RODATA_BASE, myElfParser);
  try {
    myLinker->link(externalSymbols(SystemType::ntsc));
  } catch (const ElfLinker::ElfLinkError& e) {
    throw runtime_error("failed to link ELF: " + string(e.what()));
  }

  try {
    myArmEntrypoint = myLinker->findRelocatedSymbol("elf_main").value;
  } catch (const ElfLinker::ElfSymbolResolutionError& e) {
    throw runtime_error("failed to resolve ARM entrypoint" + string(e.what()));
  }

  if (myLinker->getSegmentSize(ElfLinker::SegmentType::text) > TEXT_SIZE)
    throw runtime_error("text segment too large");

  if (myLinker->getSegmentSize(ElfLinker::SegmentType::data) > DATA_SIZE)
    throw runtime_error("data segment too large");

  if (myLinker->getSegmentSize(ElfLinker::SegmentType::rodata) > RODATA_SIZE)
    throw runtime_error("rodata segment too large");

#ifdef DUMP_ELF
  dumpLinkage(myElfParser, *myLinker);

  cout
    << "\nARM entrypoint: 0x"
    << std::hex << std::setw(8) << std::setfill('0') << myArmEntrypoint
    << std::dec << '\n';

  writeDebugBinary(*myLinker);
#endif
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CartridgeELF::allocationSections()
{
  mySectionStack = make_unique<uInt8[]>(STACK_SIZE);
  mySectionText = make_unique<uInt8[]>(TEXT_SIZE);
  mySectionData = make_unique<uInt8[]>(DATA_SIZE);
  mySectionRodata = make_unique<uInt8[]>(RODATA_SIZE);
  mySectionTables = make_unique<uInt8[]>(TABLES_SIZE);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CartridgeELF::setupMemoryMap(bool strictMode)
{
  myCortexEmu
    .resetMappings()
    .mapRegionData(ADDR_STACK_BASE / CortexM0::PAGE_SIZE,
                   STACK_SIZE / CortexM0::PAGE_SIZE, false, mySectionStack.get())
    .mapRegionCode(ADDR_TEXT_BASE / CortexM0::PAGE_SIZE,
                   TEXT_SIZE / CortexM0::PAGE_SIZE, strictMode, mySectionText.get())
    .mapRegionData(ADDR_DATA_BASE / CortexM0::PAGE_SIZE,
                   DATA_SIZE / CortexM0::PAGE_SIZE, false, mySectionData.get())
    .mapRegionData(ADDR_RODATA_BASE / CortexM0::PAGE_SIZE,
                   RODATA_SIZE / CortexM0::PAGE_SIZE, strictMode, mySectionRodata.get())
    .mapRegionData(ADDR_TABLES_BASE / CortexM0::PAGE_SIZE,
                   TABLES_SIZE / CortexM0::PAGE_SIZE, strictMode, mySectionTables.get())
    .mapRegionDelegate(ADDR_STUB_BASE / CortexM0::PAGE_SIZE,
                       STUB_SIZE / CortexM0::PAGE_SIZE, true, &myVcsLib)
    .mapDefault(&myFallbackDelegate);

  myFallbackDelegate.setErrorsAreFatal(strictMode);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CartridgeELF::switchExecutionStage()
{
  constexpr uInt32 sp = ADDR_STACK_BASE + STACK_SIZE;

  if (myExecutionStage == ExecutionStage::boot) {
    myExecutionStage = ExecutionStage::preinit;
    myInitFunctionIndex = 0;
  }

  if (myExecutionStage == ExecutionStage::preinit) {
    if (myInitFunctionIndex >= myLinker->getPreinitArray().size()) {
      myExecutionStage = ExecutionStage::init;
      myInitFunctionIndex = 0;
    }
    else {
      callFn(myLinker->getPreinitArray()[myInitFunctionIndex++], sp);
      return;
    }
  }

  if (myExecutionStage == ExecutionStage::init) {
    if (myInitFunctionIndex >= myLinker->getInitArray().size()) {
      myExecutionStage = ExecutionStage::main;
    }
    else {
      callFn(myLinker->getInitArray()[myInitFunctionIndex++], sp);
      return;
    }
  }

  callMain();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CartridgeELF::callFn(uInt32 ptr, uInt32 sp)
{
  myCortexEmu
    .setRegister(0, sp)
    .setRegister(13, sp)
    .setRegister(14, RETURN_ADDR)
    .setPc(ptr);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CartridgeELF::callMain()
{
  if (!mySystem) throw runtime_error("cartridge not installed");

  uInt32 sp = ADDR_STACK_BASE + STACK_SIZE;
  CortexM0::err_t err = 0;

  // Feature flags
  sp -= 4;
  err |= myCortexEmu.write32(sp, 0);

  sp -= 4;
  err |= myCortexEmu.write32(sp, myArmCyclesPer6502Cycle * get6502SpeedHz(myConsoleTiming));

  sp -= 4;
  err |= myCortexEmu.write32(sp, getSystemTypeParam(mySystemType));

  if (err) throw runtime_error("unable to setup main args");

  callFn(myArmEntrypoint, sp);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CartridgeELF::runArm()
{
  if (
    (getArmCycles() >= (mySystem->cycles() + ARM_RUNAHED_MIN) * myArmCyclesPer6502Cycle) ||
    myTransactionQueue.size() >= QUEUE_SIZE_LIMIT ||
    myVcsLib.isSuspended()
  )
    return;

  const auto cyclesGoal = static_cast<uInt32>(
    (mySystem->cycles() + ARM_RUNAHED_MAX) * myArmCyclesPer6502Cycle - getArmCycles());
  uInt32 cycles = 0;

  const CortexM0::err_t err = myCortexEmu.run(cyclesGoal, cycles);

  if (err) {
    if (CortexM0::getErrCustom(err) == ERR_RETURN) {
      if (myExecutionStage == ExecutionStage::main) {
        FatalEmulationError::raise("return from elf_main");
      }
      else {
        switchExecutionStage();
        return;
      }
    }

    if (CortexM0::getErrCustom(err) != ERR_STOP_EXECUTION) {
      ostringstream s;

      s
        << "error executing ARM code (PC = 0x"
        << std::hex << std::setw(8) << std::setfill('0') << myCortexEmu.getRegister(15)
        << "): " << CortexM0::describeError(err);

      FatalEmulationError::raise(s.str());
    }
  }
}
