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
// Copyright (c) 1995-2006 by Bradford W. Mott and the Stella team
//
// See the file "license" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//
// $Id: SettingsPSP.cxx,v 1.5 2006-12-08 16:49:38 stephena Exp $
//============================================================================

#include "bspf.hxx"
#include "Settings.hxx"
#include "SettingsPSP.hxx"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
SettingsPSP::SettingsPSP(OSystem* osystem)
  : Settings(osystem)
{
  set("accurate", "false");
  set("zoom", "1");
  set("romdir", "ms0:/stella/roms/");
  set("ssdir", "ms0:/stella/snapshots/");
  set("sound", "true");
  set("pspoverclock", "false");
  set("joymouse", "true");
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
SettingsPSP::~SettingsPSP()
{
}
