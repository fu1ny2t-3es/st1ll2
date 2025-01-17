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
// Copyright (c) 1995-2025 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//============================================================================

#ifndef JSON_DEFINITIONS_HXX
#define JSON_DEFINITIONS_HXX

// NOLINTBEGIN: NLOHMANN_JSON_SERIALIZE_ENUM
//   warning: use c++17 style variable templates [modernize-type-traits]

#include "EventHandlerConstants.hxx"
#include "Event.hxx"
#include "json_lib.hxx"
#include "StellaKeys.hxx"

NLOHMANN_JSON_SERIALIZE_ENUM(JoyAxis, {
  {JoyAxis::NONE, nullptr},
  {JoyAxis::X, "x"},
  {JoyAxis::Y, "y"},
  {JoyAxis::Z, "z"},
  {JoyAxis::A3, "a3"},
  {JoyAxis::A4, "a4"},
  {JoyAxis::A5, "a5"},
  {JoyAxis::A6, "a6"},
  {JoyAxis::A7, "a7"}
})

NLOHMANN_JSON_SERIALIZE_ENUM(JoyDir, {
  {JoyDir::NONE, nullptr},
  {JoyDir::ANALOG, "analog"},
  {JoyDir::NEG, "negative"},
  {JoyDir::POS, "positive"},
  // converted mappings
  {JoyDir::POS, "position"},
})

NLOHMANN_JSON_SERIALIZE_ENUM(JoyHatDir, {
  {JoyHatDir::CENTER, "center"},
  {JoyHatDir::DOWN, "down"},
  {JoyHatDir::LEFT, "left"},
  {JoyHatDir::RIGHT, "right"},
  {JoyHatDir::UP, "up"}
})

NLOHMANN_JSON_SERIALIZE_ENUM(EventMode, {
  {EventMode::kEditMode, "kEditMode"},
  {EventMode::kPromptMode, "kPromptMode"},
  {EventMode::kMenuMode, "kMenuMode"},
  {EventMode::kEmulationMode, "kEmulationMode"},
  {EventMode::kJoystickMode, "kJoystickMode"},
  {EventMode::kPaddlesMode, "kPaddlesMode"},
  {EventMode::kKeyboardMode, "kKeyboardMode"},
  {EventMode::kDrivingMode, "kDrivingMode"},
  {EventMode::kCompuMateMode, "kCompuMateMode"},
  {EventMode::kCommonMode, "kCommonMode"},
  {EventMode::kNumModes, "kNumModes"},
  // converted mappings
  {EventMode::kKeyboardMode, "kKeypadMode"},
})

NLOHMANN_JSON_SERIALIZE_ENUM(Event::Type, {
  {Event::NoType, "NoType"},
  {Event::ConsoleColor, "ConsoleColor"},
  {Event::ConsoleBlackWhite, "ConsoleBlackWhite"},
  {Event::ConsoleColorToggle, "ConsoleColorToggle"},
  {Event::Console7800Pause, "Console7800Pause"},
  {Event::ConsoleLeftDiffA, "ConsoleLeftDiffA"},
  {Event::ConsoleLeftDiffB, "ConsoleLeftDiffB"},
  {Event::ConsoleLeftDiffToggle, "ConsoleLeftDiffToggle"},
  {Event::ConsoleRightDiffA, "ConsoleRightDiffA"},
  {Event::ConsoleRightDiffB, "ConsoleRightDiffB"},
  {Event::ConsoleRightDiffToggle, "ConsoleRightDiffToggle"},
  {Event::ConsoleSelect, "ConsoleSelect"},
  {Event::ConsoleReset, "ConsoleReset"},
  {Event::LeftJoystickUp, "LeftJoystickUp"},
  {Event::LeftJoystickDown, "LeftJoystickDown"},
  {Event::LeftJoystickLeft, "LeftJoystickLeft"},
  {Event::LeftJoystickRight, "LeftJoystickRight"},
  {Event::LeftJoystickFire, "LeftJoystickFire"},
  {Event::LeftJoystickFire5, "LeftJoystickFire5"},
  {Event::LeftJoystickFire9, "LeftJoystickFire9"},
  {Event::RightJoystickUp, "RightJoystickUp"},
  {Event::RightJoystickDown, "RightJoystickDown"},
  {Event::RightJoystickLeft, "RightJoystickLeft"},
  {Event::RightJoystickRight, "RightJoystickRight"},
  {Event::RightJoystickFire, "RightJoystickFire"},
  {Event::RightJoystickFire5, "RightJoystickFire5"},
  {Event::RightJoystickFire9, "RightJoystickFire9"},
  {Event::QTJoystickThreeUp, "QTJoystickThreeUp"},
  {Event::QTJoystickThreeDown, "QTJoystickThreeDown"},
  {Event::QTJoystickThreeLeft, "QTJoystickThreeLeft"},
  {Event::QTJoystickThreeRight, "QTJoystickThreeRight"},
  {Event::QTJoystickThreeFire, "QTJoystickThreeFire"},
  {Event::QTJoystickFourUp, "QTJoystickFourUp"},
  {Event::QTJoystickFourDown, "QTJoystickFourDown"},
  {Event::QTJoystickFourLeft, "QTJoystickFourLeft"},
  {Event::QTJoystickFourRight, "QTJoystickFourRight"},
  {Event::QTJoystickFourFire, "QTJoystickFourFire"},
  {Event::LeftPaddleADecrease, "LeftPaddleADecrease"},
  {Event::LeftPaddleAIncrease, "LeftPaddleAIncrease"},
  {Event::LeftPaddleAAnalog, "LeftPaddleAAnalog"},
  {Event::LeftPaddleAFire, "LeftPaddleAFire"},
  {Event::LeftPaddleBDecrease, "LeftPaddleBDecrease"},
  {Event::LeftPaddleBIncrease, "LeftPaddleBIncrease"},
  {Event::LeftPaddleBAnalog, "LeftPaddleBAnalog"},
  {Event::LeftPaddleBFire, "LeftPaddleBFire"},
  {Event::RightPaddleADecrease, "RightPaddleADecrease"},
  {Event::RightPaddleAIncrease, "RightPaddleAIncrease"},
  {Event::RightPaddleAAnalog, "RightPaddleAAnalog"},
  {Event::RightPaddleAFire, "RightPaddleAFire"},
  {Event::RightPaddleBDecrease, "RightPaddleBDecrease"},
  {Event::RightPaddleBIncrease, "RightPaddleBIncrease"},
  {Event::RightPaddleBAnalog, "RightPaddleBAnalog"},
  {Event::RightPaddleBFire, "RightPaddleBFire"},
  {Event::QTPaddle3AFire, "QTPaddle3AFire"},
  {Event::QTPaddle3BFire, "QTPaddle3BFire"},
  {Event::QTPaddle4AFire, "QTPaddle4AFire"},
  {Event::QTPaddle4BFire, "QTPaddle4BFire"},
  {Event::LeftKeyboard1, "LeftKeyboard1"},
  {Event::LeftKeyboard2, "LeftKeyboard2"},
  {Event::LeftKeyboard3, "LeftKeyboard3"},
  {Event::LeftKeyboard4, "LeftKeyboard4"},
  {Event::LeftKeyboard5, "LeftKeyboard5"},
  {Event::LeftKeyboard6, "LeftKeyboard6"},
  {Event::LeftKeyboard7, "LeftKeyboard7"},
  {Event::LeftKeyboard8, "LeftKeyboard8"},
  {Event::LeftKeyboard9, "LeftKeyboard9"},
  {Event::LeftKeyboardStar, "LeftKeyboardStar"},
  {Event::LeftKeyboard0, "LeftKeyboard0"},
  {Event::LeftKeyboardPound, "LeftKeyboardPound"},
  {Event::RightKeyboard1, "RightKeyboard1"},
  {Event::RightKeyboard2, "RightKeyboard2"},
  {Event::RightKeyboard3, "RightKeyboard3"},
  {Event::RightKeyboard4, "RightKeyboard4"},
  {Event::RightKeyboard5, "RightKeyboard5"},
  {Event::RightKeyboard6, "RightKeyboard6"},
  {Event::RightKeyboard7, "RightKeyboard7"},
  {Event::RightKeyboard8, "RightKeyboard8"},
  {Event::RightKeyboard9, "RightKeyboard9"},
  {Event::RightKeyboardStar, "RightKeyboardStar"},
  {Event::RightKeyboard0, "RightKeyboard0"},
  {Event::RightKeyboardPound, "RightKeyboardPound"},
  {Event::LeftDrivingCCW, "LeftDrivingCCW"},
  {Event::LeftDrivingCW, "LeftDrivingCW"},
  {Event::LeftDrivingFire, "LeftDrivingFire"},
  {Event::LeftDrivingAnalog, "LeftDrivingAnalog"},
  {Event::RightDrivingCCW, "RightDrivingCCW"},
  {Event::RightDrivingCW, "RightDrivingCW"},
  {Event::RightDrivingFire, "RightDrivingFire"},
  {Event::RightDrivingAnalog, "RightDrivingAnalog"},
  {Event::CompuMateFunc, "CompuMateFunc"},
  {Event::CompuMateShift, "CompuMateShift"},
  {Event::CompuMate0, "CompuMate0"},
  {Event::CompuMate1, "CompuMate1"},
  {Event::CompuMate2, "CompuMate2"},
  {Event::CompuMate3, "CompuMate3"},
  {Event::CompuMate4, "CompuMate4"},
  {Event::CompuMate5, "CompuMate5"},
  {Event::CompuMate6, "CompuMate6"},
  {Event::CompuMate7, "CompuMate7"},
  {Event::CompuMate8, "CompuMate8"},
  {Event::CompuMate9, "CompuMate9"},
  {Event::CompuMateA, "CompuMateA"},
  {Event::CompuMateB, "CompuMateB"},
  {Event::CompuMateC, "CompuMateC"},
  {Event::CompuMateD, "CompuMateD"},
  {Event::CompuMateE, "CompuMateE"},
  {Event::CompuMateF, "CompuMateF"},
  {Event::CompuMateG, "CompuMateG"},
  {Event::CompuMateH, "CompuMateH"},
  {Event::CompuMateI, "CompuMateI"},
  {Event::CompuMateJ, "CompuMateJ"},
  {Event::CompuMateK, "CompuMateK"},
  {Event::CompuMateL, "CompuMateL"},
  {Event::CompuMateM, "CompuMateM"},
  {Event::CompuMateN, "CompuMateN"},
  {Event::CompuMateO, "CompuMateO"},
  {Event::CompuMateP, "CompuMateP"},
  {Event::CompuMateQ, "CompuMateQ"},
  {Event::CompuMateR, "CompuMateR"},
  {Event::CompuMateS, "CompuMateS"},
  {Event::CompuMateT, "CompuMateT"},
  {Event::CompuMateU, "CompuMateU"},
  {Event::CompuMateV, "CompuMateV"},
  {Event::CompuMateW, "CompuMateW"},
  {Event::CompuMateX, "CompuMateX"},
  {Event::CompuMateY, "CompuMateY"},
  {Event::CompuMateZ, "CompuMateZ"},
  {Event::CompuMateComma, "CompuMateComma"},
  {Event::CompuMatePeriod, "CompuMatePeriod"},
  {Event::CompuMateEnter, "CompuMateEnter"},
  {Event::CompuMateSpace, "CompuMateSpace"},
  {Event::CompuMateQuestion, "CompuMateQuestion"},
  {Event::CompuMateLeftBracket, "CompuMateLeftBracket"},
  {Event::CompuMateRightBracket, "CompuMateRightBracket"},
  {Event::CompuMateMinus, "CompuMateMinus"},
  {Event::CompuMateQuote, "CompuMateQuote"},
  {Event::CompuMateBackspace, "CompuMateBackspace"},
  {Event::CompuMateEquals, "CompuMateEquals"},
  {Event::CompuMatePlus, "CompuMatePlus"},
  {Event::CompuMateSlash, "CompuMateSlash"},

  {Event::DecreaseDeadzone, "DecreaseDeadzone"},
  {Event::IncreaseDeadzone, "IncreaseDeadzone"},
  {Event::DecAnalogDeadzone, "DecAnalogDeadzone"},
  {Event::IncAnalogDeadzone, "IncAnalogDeadzone"},
  {Event::DecAnalogSense, "DecAnalogSense"},
  {Event::IncAnalogSense, "IncAnalogSense"},
  {Event::DecAnalogLinear, "DecAnalogLinear"},
  {Event::IncAnalogLinear, "IncAnalogLinear"},
  {Event::DecDejtterAveraging, "DecDejtterAveraging"},
  {Event::IncDejtterAveraging, "IncDejtterAveraging"},
  {Event::DecDejtterReaction, "DecDejtterReaction"},
  {Event::IncDejtterReaction, "IncDejtterReaction"},
  {Event::DecDigitalSense, "DecDigitalSense"},
  {Event::IncDigitalSense, "IncDigitalSense"},
  {Event::ToggleFourDirections, "ToggleFourDirections"},
  {Event::ToggleKeyCombos, "ToggleKeyCombos"},
  {Event::ToggleSAPortOrder, "ToggleSAPortOrder"},

  {Event::PrevMouseAsController, "PrevMouseAsController"},
  {Event::NextMouseAsController, "NextMouseAsController"},
  {Event::DecMousePaddleSense, "DecMousePaddleSense"},
  {Event::IncMousePaddleSense, "IncMousePaddleSense"},
  {Event::DecMouseTrackballSense, "DecMouseTrackballSense"},
  {Event::IncMouseTrackballSense, "IncMouseTrackballSense"},
  {Event::DecreaseDrivingSense, "DecreaseDrivingSense"},
  {Event::IncreaseDrivingSense, "IncreaseDrivingSense"},
  {Event::PreviousCursorVisbility, "PreviousCursorVisbility"},
  {Event::NextCursorVisbility, "NextCursorVisbility"},
  {Event::ToggleGrabMouse, "ToggleGrabMouse"},

  {Event::PreviousLeftPort, "PreviousLeftPort"},
  {Event::NextLeftPort, "NextLeftPort"},
  {Event::PreviousRightPort, "PreviousRightPort"},
  {Event::NextRightPort, "NextRightPort"},
  {Event::ToggleSwapPorts, "ToggleSwapPorts"},
  {Event::ToggleSwapPaddles,"ToggleSwapPaddles"},
  {Event::DecreasePaddleCenterX, "DecreasePaddleCenterX"},
  {Event::IncreasePaddleCenterX, "IncreasePaddleCenterX"},
  {Event::DecreasePaddleCenterY, "DecreasePaddleCenterY"},
  {Event::IncreasePaddleCenterY, "IncreasePaddleCenterY"},
  {Event::PreviousMouseControl, "PreviousMouseControl"},
  {Event::NextMouseControl, "NextMouseControl"},
  {Event::DecreaseMouseAxesRange, "DecreaseMouseAxesRange"},
  {Event::IncreaseMouseAxesRange, "IncreaseMouseAxesRange"},

  {Event::Combo1, "Combo1"},
  {Event::Combo2, "Combo2"},
  {Event::Combo3, "Combo3"},
  {Event::Combo4, "Combo4"},
  {Event::Combo5, "Combo5"},
  {Event::Combo6, "Combo6"},
  {Event::Combo7, "Combo7"},
  {Event::Combo8, "Combo8"},
  {Event::Combo9, "Combo9"},
  {Event::Combo10, "Combo10"},
  {Event::Combo11, "Combo11"},
  {Event::Combo12, "Combo12"},
  {Event::Combo13, "Combo13"},
  {Event::Combo14, "Combo14"},
  {Event::Combo15, "Combo15"},
  {Event::Combo16, "Combo16"},
  {Event::UIUp, "UIUp"},
  {Event::UIDown, "UIDown"},
  {Event::UILeft, "UILeft"},
  {Event::UIRight, "UIRight"},
  {Event::UIHome, "UIHome"},
  {Event::UIEnd, "UIEnd"},
  {Event::UIPgUp, "UIPgUp"},
  {Event::UIPgDown, "UIPgDown"},
  {Event::UISelect, "UISelect"},
  {Event::UINavPrev, "UINavPrev"},
  {Event::UINavNext, "UINavNext"},
  {Event::UIOK, "UIOK"},
  {Event::UICancel, "UICancel"},
  {Event::UIPrevDir, "UIPrevDir"},
  {Event::UITabPrev, "UITabPrev"},
  {Event::UITabNext, "UITabNext"},
  {Event::UIHelp, "UIHelp"},
  {Event::ToggleUIPalette,  "ToggleUIPalette" },
  {Event::MouseAxisXMove, "MouseAxisXMove"},
  {Event::MouseAxisYMove, "MouseAxisYMove"},
  {Event::MouseAxisXValue, "MouseAxisXValue"},
  {Event::MouseAxisYValue, "MouseAxisYValue"},
  {Event::MouseButtonLeftValue, "MouseButtonLeftValue"},
  {Event::MouseButtonRightValue, "MouseButtonRightValue"},
  {Event::Quit, "Quit"},
  {Event::ReloadConsole, "ReloadConsole"},
  {Event::Fry, "Fry"},
  {Event::TogglePauseMode, "TogglePauseMode"},
  {Event::StartPauseMode, "StartPauseMode"},
  {Event::OptionsMenuMode, "OptionsMenuMode"},
  {Event::CmdMenuMode, "CmdMenuMode"},
  {Event::HighScoresMenuMode, "HighScoresMenuMode"},
  {Event::PlusRomsSetupMode, "PlusRomsSetupMode"},
  {Event::DebuggerMode, "DebuggerMode"},
  {Event::ExitMode, "ExitMode"},
  {Event::TakeSnapshot, "TakeSnapshot"},
  {Event::ToggleContSnapshots, "ToggleContSnapshots"},
  {Event::ToggleContSnapshotsFrame, "ToggleContSnapshotsFrame"},
  {Event::ToggleTurbo, "ToggleTurbo"},
  {Event::NextState, "NextState"},
  {Event::PreviousState, "PreviousState"},
  {Event::LoadState, "LoadState"},
  {Event::SaveState, "SaveState"},
  {Event::SaveAllStates, "SaveAllStates"},
  {Event::LoadAllStates, "LoadAllStates"},
  {Event::ToggleAutoSlot, "ToggleAutoSlot"},
  {Event::ToggleTimeMachine, "ToggleTimeMachine"},
  {Event::TimeMachineMode, "TimeMachineMode"},
  {Event::Rewind1Menu, "Rewind1Menu"},
  {Event::Rewind10Menu, "Rewind10Menu"},
  {Event::RewindAllMenu, "RewindAllMenu"},
  {Event::Unwind1Menu, "Unwind1Menu"},
  {Event::Unwind10Menu, "Unwind10Menu"},
  {Event::UnwindAllMenu, "UnwindAllMenu"},
  {Event::RewindPause, "RewindPause"},
  {Event::UnwindPause, "UnwindPause"},
  {Event::FormatDecrease, "FormatDecrease"},
  {Event::FormatIncrease, "FormatIncrease"},
  {Event::PaletteDecrease, "PaletteDecrease"},
  {Event::PaletteIncrease, "PaletteIncrease"},
  {Event::ToggleColorLoss, "ToggleColorLoss"},
  {Event::PreviousPaletteAttribute, "PreviousPaletteAttribute"},
  {Event::NextPaletteAttribute, "NextPaletteAttribute"},
  {Event::PaletteAttributeDecrease, "PaletteAttributeDecrease"},
  {Event::PaletteAttributeIncrease, "PaletteAttributeIncrease"},
  {Event::ToggleFullScreen, "ToggleFullScreen"},
  {Event::VidmodeDecrease, "VidmodeDecrease"},
  {Event::VidmodeIncrease, "VidmodeIncrease"},
  {Event::VCenterDecrease, "VCenterDecrease"},
  {Event::VCenterIncrease, "VCenterIncrease"},
  {Event::VSizeAdjustDecrease, "VSizeAdjustDecrease"},
  {Event::VSizeAdjustIncrease, "VSizeAdjustIncrease"},
  {Event::OverscanDecrease, "OverscanDecrease"},
  {Event::OverscanIncrease, "OverscanIncrease"},
  {Event::VidmodeStd, "VidmodeStd"},
  {Event::VidmodeRGB, "VidmodeRGB"},
  {Event::VidmodeSVideo, "VidmodeSVideo"},
  {Event::VidModeComposite, "VidModeComposite"},
  {Event::VidModeBad, "VidModeBad"},
  {Event::VidModeCustom, "VidModeCustom"},
  {Event::PreviousVideoMode, "PreviousVideoMode"},
  {Event::NextVideoMode, "NextVideoMode"},
  {Event::PreviousAttribute, "PreviousAttribute"},
  {Event::NextAttribute, "NextAttribute"},
  {Event::DecreaseAttribute, "DecreaseAttribute"},
  {Event::IncreaseAttribute, "IncreaseAttribute"},
  {Event::PreviousScanlineMask, "PreviousScanlineMask"},
  {Event::NextScanlineMask, "NextScanlineMask"},
  {Event::ScanlinesDecrease, "ScanlinesDecrease"},
  {Event::ScanlinesIncrease, "ScanlinesIncrease"},
  {Event::PhosphorDecrease, "PhosphorDecrease"},
  {Event::PhosphorIncrease, "PhosphorIncrease"},
  {Event::TogglePhosphor, "TogglePhosphor"},
  {Event::PhosphorModeDecrease, "PhosphorModeDecrease"},
  {Event::PhosphorModeIncrease, "PhosphorModeIncrease"},
  {Event::ToggleDeveloperSet, "ToggleDeveloperSet"},
  {Event::ToggleInter, "ToggleInter"},
  {Event::JitterSenseDecrease, "JitterSenseDecrease"},
  {Event::JitterSenseIncrease, "JitterSenseIncrease"},
  {Event::JitterRecDecrease, "JitterRecDecrease"},
  {Event::JitterRecIncrease, "JitterRecIncrease"},
  {Event::ToggleJitter, "ToggleJitter"},
  {Event::VolumeDecrease, "VolumeDecrease"},
  {Event::VolumeIncrease, "VolumeIncrease"},
  {Event::SoundToggle, "SoundToggle"},
  {Event::ToggleP0Collision, "ToggleP0Collision"},
  {Event::ToggleP0Bit, "ToggleP0Bit"},
  {Event::ToggleP1Collision, "ToggleP1Collision"},
  {Event::ToggleP1Bit, "ToggleP1Bit"},
  {Event::ToggleM0Collision, "ToggleM0Collision"},
  {Event::ToggleM0Bit, "ToggleM0Bit"},
  {Event::ToggleM1Collision, "ToggleM1Collision"},
  {Event::ToggleM1Bit, "ToggleM1Bit"},
  {Event::ToggleBLCollision, "ToggleBLCollision"},
  {Event::ToggleBLBit, "ToggleBLBit"},
  {Event::TogglePFCollision, "TogglePFCollision"},
  {Event::TogglePFBit, "TogglePFBit"},
  {Event::ToggleCollisions, "ToggleCollisions"},
  {Event::ToggleBits, "ToggleBits"},
  {Event::ToggleFixedColors, "ToggleFixedColors"},
  {Event::ToggleFrameStats, "ToggleFrameStats"},
  {Event::ToggleBezel, "ToggleBezel"},
  {Event::ExitGame, "ExitGame"},
  {Event::SettingDecrease, "SettingDecrease"},
  {Event::SettingIncrease, "SettingIncrease"},
  {Event::PreviousSetting, "PreviousSetting"},
  {Event::NextSetting, "NextSetting"},
  {Event::ToggleAdaptRefresh, "ToggleAdaptRefresh"},
  {Event::PreviousMultiCartRom, "PreviousMultiCartRom"},
  {Event::PreviousSettingGroup, "PreviousSettingGroup"},
  {Event::NextSettingGroup, "NextSettingGroup"},
  {Event::TogglePlayBackMode, "TogglePlayBackMode"},
  {Event::ToggleAutoFire, "ToggleAutoFire"},
  {Event::DecreaseAutoFire, "DecreaseAutoFire"},
  {Event::IncreaseAutoFire, "IncreaseAutoFire"},
  {Event::DecreaseSpeed, "DecreaseSpeed"},
  {Event::IncreaseSpeed, "IncreaseSpeed"},
  {Event::ToggleCorrectAspectRatio, "ToggleCorrectAspectRatio"},
  {Event::MoveLeftChar, "MoveLeftChar"},
  {Event::MoveRightChar, "MoveRightChar"},
  {Event::MoveLeftWord, "MoveLeftWord"},
  {Event::MoveRightWord, "MoveRightWord"},
  {Event::MoveHome, "MoveHome"},
  {Event::MoveEnd, "MoveEnd"},
  {Event::SelectLeftChar, "SelectLeftChar"},
  {Event::SelectRightChar, "SelectRightChar"},
  {Event::SelectLeftWord, "SelectLeftWord"},
  {Event::SelectRightWord, "SelectRightWord"},
  {Event::SelectHome, "SelectHome"},
  {Event::SelectEnd, "SelectEnd"},
  {Event::SelectAll, "SelectAll"},
  {Event::Delete, "Delete"},
  {Event::DeleteLeftWord, "DeleteLeftWord"},
  {Event::DeleteRightWord, "DeleteRightWord"},
  {Event::DeleteHome, "DeleteHome"},
  {Event::DeleteEnd, "DeleteEnd"},
  {Event::Backspace, "Backspace"},
  {Event::Cut, "Cut"},
  {Event::Copy, "Copy"},
  {Event::Paste, "Paste"},
  {Event::Undo, "Undo"},
  {Event::Redo, "Redo"},
  {Event::AbortEdit, "AbortEdit"},
  {Event::EndEdit, "EndEdit"},
  {Event::LastType, "LastType"},
  // converted mappings
  {Event::LeftJoystickUp, "JoystickZeroUp"},
  {Event::LeftJoystickDown, "JoystickZeroDown"},
  {Event::LeftJoystickLeft, "JoystickZeroLeft"},
  {Event::LeftJoystickRight, "JoystickZeroRight"},
  {Event::LeftJoystickFire, "JoystickZeroFire"},
  {Event::LeftJoystickFire5, "JoystickZeroFire5"},
  {Event::LeftJoystickFire9, "JoystickZeroFire9"},
  {Event::RightJoystickUp, "JoystickOneUp"},
  {Event::RightJoystickDown, "JoystickOneDown"},
  {Event::RightJoystickLeft, "JoystickOneLeft"},
  {Event::RightJoystickRight, "JoystickOneRight"},
  {Event::RightJoystickFire, "JoystickOneFire"},
  {Event::RightJoystickFire5, "JoystickOneFire5"},
  {Event::RightJoystickFire9, "JoystickOneFire9"},
  {Event::QTJoystickThreeUp, "JoystickTwoUp"},
  {Event::QTJoystickThreeDown, "JoystickTwoDown"},
  {Event::QTJoystickThreeLeft, "JoystickTwoLeft"},
  {Event::QTJoystickThreeRight, "JoystickTwoRight"},
  {Event::QTJoystickThreeFire, "JoystickTwoFire"},
  {Event::QTJoystickFourUp, "JoystickThreeUp"},
  {Event::QTJoystickFourDown, "JoystickThreeDown"},
  {Event::QTJoystickFourLeft, "JoystickThreeLeft"},
  {Event::QTJoystickFourRight, "JoystickThreeRight"},
  {Event::QTJoystickFourFire, "JoystickThreeFire"},
  {Event::LeftPaddleADecrease, "PaddleZeroDecrease"},
  {Event::LeftPaddleAIncrease, "PaddleZeroIncrease"},
  {Event::LeftPaddleAAnalog, "PaddleZeroAnalog"},
  {Event::LeftPaddleAFire, "PaddleZeroFire"},
  {Event::LeftPaddleBDecrease, "PaddleOneDecrease"},
  {Event::LeftPaddleBIncrease, "PaddleOneIncrease"},
  {Event::LeftPaddleBAnalog, "PaddleOneAnalog"},
  {Event::LeftPaddleBFire, "PaddleOneFire"},
  {Event::RightPaddleADecrease, "PaddleTwoDecrease"},
  {Event::RightPaddleAIncrease, "PaddleTwoIncrease"},
  {Event::RightPaddleAAnalog, "PaddleTwoAnalog"},
  {Event::RightPaddleAFire, "PaddleTwoFire"},
  {Event::RightPaddleBDecrease, "PaddleThreeDecrease"},
  {Event::RightPaddleBIncrease, "PaddleThreeIncrease"},
  {Event::RightPaddleBAnalog, "PaddleThreeAnalog"},
  {Event::RightPaddleBFire, "PaddleThreeFire"},
  {Event::QTPaddle3AFire, "PaddleFourFire"},
  {Event::QTPaddle3BFire, "PaddleFiveFire"},
  {Event::QTPaddle4AFire, "PaddleSixFire"},
  {Event::QTPaddle4BFire, "PaddleSevenFire"},
  {Event::LeftKeyboard1, "KeyboardZero1"},
  {Event::LeftKeyboard2, "KeyboardZero2"},
  {Event::LeftKeyboard3, "KeyboardZero3"},
  {Event::LeftKeyboard4, "KeyboardZero4"},
  {Event::LeftKeyboard5, "KeyboardZero5"},
  {Event::LeftKeyboard6, "KeyboardZero6"},
  {Event::LeftKeyboard7, "KeyboardZero7"},
  {Event::LeftKeyboard8, "KeyboardZero8"},
  {Event::LeftKeyboard9, "KeyboardZero9"},
  {Event::LeftKeyboardStar, "KeyboardZeroStar"},
  {Event::LeftKeyboard0, "KeyboardZero0"},
  {Event::LeftKeyboardPound, "KeyboardZeroPound"},
  {Event::RightKeyboard1, "KeyboardOne1"},
  {Event::RightKeyboard2, "KeyboardOne2"},
  {Event::RightKeyboard3, "KeyboardOne3"},
  {Event::RightKeyboard4, "KeyboardOne4"},
  {Event::RightKeyboard5, "KeyboardOne5"},
  {Event::RightKeyboard6, "KeyboardOne6"},
  {Event::RightKeyboard7, "KeyboardOne7"},
  {Event::RightKeyboard8, "KeyboardOne8"},
  {Event::RightKeyboard9, "KeyboardOne9"},
  {Event::RightKeyboardStar, "KeyboardOneStar"},
  {Event::RightKeyboard0, "KeyboardOne0"},
  {Event::RightKeyboardPound, "KeyboardOnePound"},

})

NLOHMANN_JSON_SERIALIZE_ENUM(StellaKey, {
  {StellaKey::KBDK_UNKNOWN, "unknown"},
  {StellaKey::KBDK_A, "a"},
  {StellaKey::KBDK_B, "b"},
  {StellaKey::KBDK_C, "c"},
  {StellaKey::KBDK_D, "d"},
  {StellaKey::KBDK_E, "e"},
  {StellaKey::KBDK_F, "f"},
  {StellaKey::KBDK_G, "g"},
  {StellaKey::KBDK_H, "h"},
  {StellaKey::KBDK_I, "i"},
  {StellaKey::KBDK_J, "j"},
  {StellaKey::KBDK_K, "k"},
  {StellaKey::KBDK_L, "l"},
  {StellaKey::KBDK_M, "m"},
  {StellaKey::KBDK_N, "n"},
  {StellaKey::KBDK_O, "o"},
  {StellaKey::KBDK_P, "p"},
  {StellaKey::KBDK_Q, "q"},
  {StellaKey::KBDK_R, "r"},
  {StellaKey::KBDK_S, "s"},
  {StellaKey::KBDK_T, "t"},
  {StellaKey::KBDK_U, "u"},
  {StellaKey::KBDK_V, "v"},
  {StellaKey::KBDK_W, "w"},
  {StellaKey::KBDK_X, "x"},
  {StellaKey::KBDK_Y, "y"},
  {StellaKey::KBDK_Z, "z"},
  {StellaKey::KBDK_1, "1"},
  {StellaKey::KBDK_2, "2"},
  {StellaKey::KBDK_3, "3"},
  {StellaKey::KBDK_4, "4"},
  {StellaKey::KBDK_5, "5"},
  {StellaKey::KBDK_6, "6"},
  {StellaKey::KBDK_7, "7"},
  {StellaKey::KBDK_8, "8"},
  {StellaKey::KBDK_9, "9"},
  {StellaKey::KBDK_0, "0"},
  {StellaKey::KBDK_RETURN, "return"},
  {StellaKey::KBDK_ESCAPE, "escape"},
  {StellaKey::KBDK_BACKSPACE, "backspace"},
  {StellaKey::KBDK_TAB, "tab"},
  {StellaKey::KBDK_SPACE, "space"},
  {StellaKey::KBDK_MINUS, "minus"},
  {StellaKey::KBDK_EQUALS, "equals"},
  {StellaKey::KBDK_LEFTBRACKET, "leftbracket"},
  {StellaKey::KBDK_RIGHTBRACKET, "rightbracket"},
  {StellaKey::KBDK_BACKSLASH, "backslash"},
  {StellaKey::KBDK_NONUSHASH, "nonushash"},
  {StellaKey::KBDK_SEMICOLON, "semicolon"},
  {StellaKey::KBDK_APOSTROPHE, "apostrophe"},
  {StellaKey::KBDK_GRAVE, "grave"},
  {StellaKey::KBDK_COMMA, "comma"},
  {StellaKey::KBDK_PERIOD, "period"},
  {StellaKey::KBDK_SLASH, "slash"},
  {StellaKey::KBDK_CAPSLOCK, "capslock"},
  {StellaKey::KBDK_F1, "f1"},
  {StellaKey::KBDK_F2, "f2"},
  {StellaKey::KBDK_F3, "f3"},
  {StellaKey::KBDK_F4, "f4"},
  {StellaKey::KBDK_F5, "f5"},
  {StellaKey::KBDK_F6, "f6"},
  {StellaKey::KBDK_F7, "f7"},
  {StellaKey::KBDK_F8, "f8"},
  {StellaKey::KBDK_F9, "f9"},
  {StellaKey::KBDK_F10, "f10"},
  {StellaKey::KBDK_F11, "f11"},
  {StellaKey::KBDK_F12, "f12"},
  {StellaKey::KBDK_PRINTSCREEN, "printscreen"},
  {StellaKey::KBDK_SCROLLLOCK, "scrolllock"},
  {StellaKey::KBDK_PAUSE, "pause"},
  {StellaKey::KBDK_INSERT, "insert"},
  {StellaKey::KBDK_HOME, "home"},
  {StellaKey::KBDK_PAGEUP, "pageup"},
  {StellaKey::KBDK_DELETE, "delete"},
  {StellaKey::KBDK_END, "end"},
  {StellaKey::KBDK_PAGEDOWN, "pagedown"},
  {StellaKey::KBDK_RIGHT, "right"},
  {StellaKey::KBDK_LEFT, "left"},
  {StellaKey::KBDK_DOWN, "down"},
  {StellaKey::KBDK_UP, "up"},
  {StellaKey::KBDK_NUMLOCKCLEAR, "numlockclear"},
  {StellaKey::KBDK_KP_DIVIDE, "kp_divide"},
  {StellaKey::KBDK_KP_MULTIPLY, "kp_multiply"},
  {StellaKey::KBDK_KP_MINUS, "kp_minus"},
  {StellaKey::KBDK_KP_PLUS, "kp_plus"},
  {StellaKey::KBDK_KP_ENTER, "kp_enter"},
  {StellaKey::KBDK_KP_1, "kp_1"},
  {StellaKey::KBDK_KP_2, "kp_2"},
  {StellaKey::KBDK_KP_3, "kp_3"},
  {StellaKey::KBDK_KP_4, "kp_4"},
  {StellaKey::KBDK_KP_5, "kp_5"},
  {StellaKey::KBDK_KP_6, "kp_6"},
  {StellaKey::KBDK_KP_7, "kp_7"},
  {StellaKey::KBDK_KP_8, "kp_8"},
  {StellaKey::KBDK_KP_9, "kp_9"},
  {StellaKey::KBDK_KP_0, "kp_0"},
  {StellaKey::KBDK_KP_PERIOD, "kp_period"},
  {StellaKey::KBDK_NONUSBACKSLASH, "nonusbackslash"},
  {StellaKey::KBDK_APPLICATION, "application"},
  {StellaKey::KBDK_POWER, "power"},
  {StellaKey::KBDK_KP_EQUALS, "kp_equals"},
  {StellaKey::KBDK_F13, "f13"},
  {StellaKey::KBDK_F14, "f14"},
  {StellaKey::KBDK_F15, "f15"},
  {StellaKey::KBDK_F16, "f16"},
  {StellaKey::KBDK_F17, "f17"},
  {StellaKey::KBDK_F18, "f18"},
  {StellaKey::KBDK_F19, "f19"},
  {StellaKey::KBDK_F20, "f20"},
  {StellaKey::KBDK_F21, "f21"},
  {StellaKey::KBDK_F22, "f22"},
  {StellaKey::KBDK_F23, "f23"},
  {StellaKey::KBDK_F24, "f24"},
  {StellaKey::KBDK_EXECUTE, "execute"},
  {StellaKey::KBDK_HELP, "help"},
  {StellaKey::KBDK_MENU, "menu"},
  {StellaKey::KBDK_SELECT, "select"},
  {StellaKey::KBDK_STOP, "stop"},
  {StellaKey::KBDK_AGAIN, "again"},
  {StellaKey::KBDK_UNDO, "undo"},
  {StellaKey::KBDK_CUT, "cut"},
  {StellaKey::KBDK_COPY, "copy"},
  {StellaKey::KBDK_PASTE, "paste"},
  {StellaKey::KBDK_FIND, "find"},
  {StellaKey::KBDK_MUTE, "mute"},
  {StellaKey::KBDK_VOLUMEUP, "volumeup"},
  {StellaKey::KBDK_VOLUMEDOWN, "volumedown"},
  {StellaKey::KBDK_KP_COMMA, "kp_comma"},
  {StellaKey::KBDK_KP_EQUALSAS400, "kp_equalsas400"},
  {StellaKey::KBDK_INTERNATIONAL1, "international1"},
  {StellaKey::KBDK_INTERNATIONAL2, "international2"},
  {StellaKey::KBDK_INTERNATIONAL3, "international3"},
  {StellaKey::KBDK_INTERNATIONAL4, "international4"},
  {StellaKey::KBDK_INTERNATIONAL5, "international5"},
  {StellaKey::KBDK_INTERNATIONAL6, "international6"},
  {StellaKey::KBDK_INTERNATIONAL7, "international7"},
  {StellaKey::KBDK_INTERNATIONAL8, "international8"},
  {StellaKey::KBDK_INTERNATIONAL9, "international9"},
  {StellaKey::KBDK_LANG1, "lang1"},
  {StellaKey::KBDK_LANG2, "lang2"},
  {StellaKey::KBDK_LANG3, "lang3"},
  {StellaKey::KBDK_LANG4, "lang4"},
  {StellaKey::KBDK_LANG5, "lang5"},
  {StellaKey::KBDK_LANG6, "lang6"},
  {StellaKey::KBDK_LANG7, "lang7"},
  {StellaKey::KBDK_LANG8, "lang8"},
  {StellaKey::KBDK_LANG9, "lang9"},
  {StellaKey::KBDK_ALTERASE, "alterase"},
  {StellaKey::KBDK_SYSREQ, "sysreq"},
  {StellaKey::KBDK_CANCEL, "cancel"},
  {StellaKey::KBDK_CLEAR, "clear"},
  {StellaKey::KBDK_PRIOR, "prior"},
  {StellaKey::KBDK_RETURN2, "return2"},
  {StellaKey::KBDK_SEPARATOR, "separator"},
  {StellaKey::KBDK_OUT, "out"},
  {StellaKey::KBDK_OPER, "oper"},
  {StellaKey::KBDK_CLEARAGAIN, "clearagain"},
  {StellaKey::KBDK_CRSEL, "crsel"},
  {StellaKey::KBDK_EXSEL, "exsel"},
  {StellaKey::KBDK_KP_00, "kp_00"},
  {StellaKey::KBDK_KP_000, "kp_000"},
  {StellaKey::KBDK_THOUSANDSSEPARATOR, "thousandsseparator"},
  {StellaKey::KBDK_DECIMALSEPARATOR, "decimalseparator"},
  {StellaKey::KBDK_CURRENCYUNIT, "currencyunit"},
  {StellaKey::KBDK_CURRENCYSUBUNIT, "currencysubunit"},
  {StellaKey::KBDK_KP_LEFTPAREN, "kp_leftparen"},
  {StellaKey::KBDK_KP_RIGHTPAREN, "kp_rightparen"},
  {StellaKey::KBDK_KP_LEFTBRACE, "kp_leftbrace"},
  {StellaKey::KBDK_KP_RIGHTBRACE, "kp_rightbrace"},
  {StellaKey::KBDK_KP_TAB, "kp_tab"},
  {StellaKey::KBDK_KP_BACKSPACE, "kp_backspace"},
  {StellaKey::KBDK_KP_A, "kp_a"},
  {StellaKey::KBDK_KP_B, "kp_b"},
  {StellaKey::KBDK_KP_C, "kp_c"},
  {StellaKey::KBDK_KP_D, "kp_d"},
  {StellaKey::KBDK_KP_E, "kp_e"},
  {StellaKey::KBDK_KP_F, "kp_f"},
  {StellaKey::KBDK_KP_XOR, "kp_xor"},
  {StellaKey::KBDK_KP_POWER, "kp_power"},
  {StellaKey::KBDK_KP_PERCENT, "kp_percent"},
  {StellaKey::KBDK_KP_LESS, "kp_less"},
  {StellaKey::KBDK_KP_GREATER, "kp_greater"},
  {StellaKey::KBDK_KP_AMPERSAND, "kp_ampersand"},
  {StellaKey::KBDK_KP_DBLAMPERSAND, "kp_dblampersand"},
  {StellaKey::KBDK_KP_VERTICALBAR, "kp_verticalbar"},
  {StellaKey::KBDK_KP_DBLVERTICALBAR, "kp_dblverticalbar"},
  {StellaKey::KBDK_KP_COLON, "kp_colon"},
  {StellaKey::KBDK_KP_HASH, "kp_hash"},
  {StellaKey::KBDK_KP_SPACE, "kp_space"},
  {StellaKey::KBDK_KP_AT, "kp_at"},
  {StellaKey::KBDK_KP_EXCLAM, "kp_exclam"},
  {StellaKey::KBDK_KP_MEMSTORE, "kp_memstore"},
  {StellaKey::KBDK_KP_MEMRECALL, "kp_memrecall"},
  {StellaKey::KBDK_KP_MEMCLEAR, "kp_memclear"},
  {StellaKey::KBDK_KP_MEMADD, "kp_memadd"},
  {StellaKey::KBDK_KP_MEMSUBTRACT, "kp_memsubtract"},
  {StellaKey::KBDK_KP_MEMMULTIPLY, "kp_memmultiply"},
  {StellaKey::KBDK_KP_MEMDIVIDE, "kp_memdivide"},
  {StellaKey::KBDK_KP_PLUSMINUS, "kp_plusminus"},
  {StellaKey::KBDK_KP_CLEAR, "kp_clear"},
  {StellaKey::KBDK_KP_CLEARENTRY, "kp_clearentry"},
  {StellaKey::KBDK_KP_BINARY, "kp_binary"},
  {StellaKey::KBDK_KP_OCTAL, "kp_octal"},
  {StellaKey::KBDK_KP_DECIMAL, "kp_decimal"},
  {StellaKey::KBDK_KP_HEXADECIMAL, "kp_hexadecimal"},
  {StellaKey::KBDK_LCTRL, "lctrl"},
  {StellaKey::KBDK_LSHIFT, "lshift"},
  {StellaKey::KBDK_LALT, "lalt"},
  {StellaKey::KBDK_LGUI, "lgui"},
  {StellaKey::KBDK_RCTRL, "rctrl"},
  {StellaKey::KBDK_RSHIFT, "rshift"},
  {StellaKey::KBDK_RALT, "ralt"},
  {StellaKey::KBDK_RGUI, "rgui"},
  {StellaKey::KBDK_MODE, "mode"},
  {StellaKey::KBDK_AUDIONEXT, "audionext"},
  {StellaKey::KBDK_AUDIOPREV, "audioprev"},
  {StellaKey::KBDK_AUDIOSTOP, "audiostop"},
  {StellaKey::KBDK_AUDIOPLAY, "audioplay"},
  {StellaKey::KBDK_AUDIOMUTE, "audiomute"},
  {StellaKey::KBDK_MEDIASELECT, "mediaselect"},
  {StellaKey::KBDK_WWW, "www"},
  {StellaKey::KBDK_MAIL, "mail"},
  {StellaKey::KBDK_CALCULATOR, "calculator"},
  {StellaKey::KBDK_COMPUTER, "computer"},
  {StellaKey::KBDK_AC_SEARCH, "ac_search"},
  {StellaKey::KBDK_AC_HOME, "ac_home"},
  {StellaKey::KBDK_AC_BACK, "ac_back"},
  {StellaKey::KBDK_AC_FORWARD, "ac_forward"},
  {StellaKey::KBDK_AC_STOP, "ac_stop"},
  {StellaKey::KBDK_AC_REFRESH, "ac_refresh"},
  {StellaKey::KBDK_AC_BOOKMARKS, "ac_bookmarks"},
  {StellaKey::KBDK_BRIGHTNESSDOWN, "brightnessdown"},
  {StellaKey::KBDK_BRIGHTNESSUP, "brightnessup"},
  {StellaKey::KBDK_DISPLAYSWITCH, "displayswitch"},
  {StellaKey::KBDK_KBDILLUMTOGGLE, "kbdillumtoggle"},
  {StellaKey::KBDK_KBDILLUMDOWN, "kbdillumdown"},
  {StellaKey::KBDK_KBDILLUMUP, "kbdillumup"},
  {StellaKey::KBDK_EJECT, "eject"},
  {StellaKey::KBDK_SLEEP, "sleep"},
  {StellaKey::KBDK_APP1, "app1"},
  {StellaKey::KBDK_APP2, "app2"},
  {StellaKey::KBDK_LAST, "last"}
})

NLOHMANN_JSON_SERIALIZE_ENUM(StellaMod, {
  {StellaMod::KBDM_NONE, "none"},
  {StellaMod::KBDM_LSHIFT, "lshift"},
  {StellaMod::KBDM_RSHIFT, "rshift"},
  {StellaMod::KBDM_LCTRL, "lctrl"},
  {StellaMod::KBDM_RCTRL, "rctrl"},
  {StellaMod::KBDM_LALT, "lalt"},
  {StellaMod::KBDM_RALT, "ralt"},
  {StellaMod::KBDM_LGUI, "lgui"},
  {StellaMod::KBDM_RGUI, "rgui"},
  {StellaMod::KBDM_NUM, "num"},
  {StellaMod::KBDM_CAPS, "caps"},
  {StellaMod::KBDM_MODE, "mode"},
  {StellaMod::KBDM_RESERVED, "reserved"},
  {StellaMod::KBDM_CTRL, "ctrl"},
  {StellaMod::KBDM_SHIFT, "shift"},
  {StellaMod::KBDM_ALT, "alt"},
  {StellaMod::KBDM_GUI, "gui"}
})

// NOLINTEND

#endif // JSON_DEFINITIONS_HXX
