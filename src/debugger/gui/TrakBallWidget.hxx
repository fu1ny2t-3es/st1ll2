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

#ifndef TRAKBALL_WIDGET_HXX
#define TRAKBALL_WIDGET_HXX

class Controller;

#include "PointingDeviceWidget.hxx"

class TrakBallWidget : public PointingDeviceWidget
{
  public:
    TrakBallWidget(GuiObject* boss, const GUI::Font& font, int x, int y,
                   Controller& controller);

    ~TrakBallWidget() override = default;

  private:
    static constexpr std::array<uInt8, 4> myGrayCodeTable = {
      0b00, 0b10, 0b01, 0b11
    };

    uInt8 getGrayCodeTable(int index, int direction) const override;

    // Following constructors and assignment operators not supported
    TrakBallWidget() = delete;
    TrakBallWidget(const TrakBallWidget&) = delete;
    TrakBallWidget(TrakBallWidget&&) = delete;
    TrakBallWidget& operator=(const TrakBallWidget&) = delete;
    TrakBallWidget& operator=(TrakBallWidget&&) = delete;
};

#endif
