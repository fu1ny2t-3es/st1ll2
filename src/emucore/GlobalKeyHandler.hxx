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
// Copyright (c) 1995-2021 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//============================================================================

#ifndef GLOBALKEYHANDLER_HXX
#define GLOBALKEYHANDLER_HXX

#include "EventHandler.hxx"

/**
  This class takes care of event handling of global hotkeys.

  @author  Thomas Jentzsch
*/
class GlobalKeyHandler
{
  public:
    GlobalKeyHandler(OSystem& osystem);

  public:
    enum class Setting
    {
      NONE = -1,
      // *** Audio & Video group ***
      VOLUME,
      ZOOM,
      FULLSCREEN,
    #ifdef ADAPTABLE_REFRESH_SUPPORT
      ADAPT_REFRESH,
    #endif
      OVERSCAN,
      TVFORMAT,
      VCENTER,
      ASPECT_RATIO,
      VSIZE,
      // Palette adjustables
      PALETTE,
      PALETTE_PHASE,
      PALETTE_RED_SCALE,
      PALETTE_RED_SHIFT,
      PALETTE_GREEN_SCALE,
      PALETTE_GREEN_SHIFT,
      PALETTE_BLUE_SCALE,
      PALETTE_BLUE_SHIFT,
      PALETTE_HUE,
      PALETTE_SATURATION,
      PALETTE_CONTRAST,
      PALETTE_BRIGHTNESS,
      PALETTE_GAMMA,
      // NTSC filter adjustables
      NTSC_PRESET,
      NTSC_SHARPNESS,
      NTSC_RESOLUTION,
      NTSC_ARTIFACTS,
      NTSC_FRINGING,
      NTSC_BLEEDING,
      // Other TV effects adjustables
      PHOSPHOR,
      SCANLINES,
      INTERPOLATION,
      // *** Input group ***
      DEADZONE,
      ANALOG_DEADZONE,
      ANALOG_SENSITIVITY,
      ANALOG_LINEARITY,
      DEJITTER_AVERAGING,
      DEJITTER_REACTION,
      DIGITAL_SENSITIVITY,
      AUTO_FIRE,
      FOUR_DIRECTIONS,
      MOD_KEY_COMBOS,
      SA_PORT_ORDER,
      USE_MOUSE,
      PADDLE_SENSITIVITY,
      TRACKBALL_SENSITIVITY,
      DRIVING_SENSITIVITY,
      MOUSE_CURSOR,
      GRAB_MOUSE,
      LEFT_PORT,
      RIGHT_PORT,
      SWAP_PORTS,
      SWAP_PADDLES,
      PADDLE_CENTER_X,
      PADDLE_CENTER_Y,
      MOUSE_CONTROL,
      MOUSE_RANGE,
      // *** Debug group ***
      STATS,
      P0_ENAM,
      P1_ENAM,
      M0_ENAM,
      M1_ENAM,
      BL_ENAM,
      PF_ENAM,
      ALL_ENAM,
      P0_CX,
      P1_CX,
      M0_CX,
      M1_CX,
      BL_CX,
      PF_CX,
      ALL_CX,
      FIXED_COL,
      COLOR_LOSS,
      JITTER,
      // *** Only used via direct hotkeys ***
      STATE,
      PALETTE_ATTRIBUTE,
      NTSC_ATTRIBUTE,
      CHANGE_SPEED,
      // *** Ranges ***
      NUM_ADJ,
      START_AV_ADJ = VOLUME,
      END_AV_ADJ = INTERPOLATION,
      START_INPUT_ADJ = DEADZONE,
      END_INPUT_ADJ = MOUSE_RANGE,
      START_DEBUG_ADJ = STATS,
      END_DEBUG_ADJ = JITTER,
    };

  public:
    bool handleEvent(const Event::Type event, bool pressed, bool repeated);
    void setSetting(const Setting setting);
    void setDirectSetting(const Setting setting);

  private:
    using Function = std::function<void(int)>;

    enum class Group
    {
      AV,
      INPUT,
      DEBUG,
      NUM_GROUPS
    };

    struct GroupData
    {
      Setting start{Setting::NONE};
      string  name{EmptyString};
    };

    struct SettingData
    {
      bool     repeated{true};
      Function function{nullptr};
    };

  private:
    // Get group based on given setting
    Group getGroup() const;
    // Cycle settings using given direction (can be 0)
    const Function cycleSetting(int direction);
    // Get adjustment function and if it is repeated
    SettingData getSettingData(const Setting setting) const;

    PhysicalJoystickHandler& joyHandler() const { return myOSystem.eventHandler().joyHandler(); }
    PhysicalKeyboardHandler& keyHandler() const { return myOSystem.eventHandler().keyHandler(); }

    // Check if controller type is used (skips related input settings if not)
    bool isJoystick(const Controller& controller) const;
    bool isPaddle(const Controller& controller) const;
    bool isTrackball(const Controller& controller) const;

    // Check if a currently non-relevant adjustment can be skipped
    bool skipAVSetting() const;
    bool skipInputSetting() const;
    bool skipDebugSetting() const;

  private:
    // Global OSystem object
    OSystem& myOSystem;

    // If true, the setting's message is visible and its value can be changed
    bool mySettingActive{false};

    // Currently selected setting
    Setting mySetting{Setting::VOLUME};

    // Currently selected direct setting (0 if none). These settings are not
    //  selected using global hotkeys, but direct hotkeys only. Nevertheless
    //  they can be changed with global hotkeys while their message is still
    //  displayed
    Setting myDirectSetting{Setting::NONE};
};

#endif
