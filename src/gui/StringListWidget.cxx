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
// Copyright (c) 1995-2020 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//============================================================================

#include "bspf.hxx"
#include "Dialog.hxx"
#include "FBSurface.hxx"
#include "Settings.hxx"
#include "ScrollBarWidget.hxx"
#include "StringListWidget.hxx"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
StringListWidget::StringListWidget(GuiObject* boss, const GUI::Font& font,
                                   int x, int y, int w, int h, bool hilite,
                                   bool useScrollbar)
  : ListWidget(boss, font, x, y, w, h, useScrollbar),
    _hilite(hilite)
{
  _bgcolorlo = kDlgColor;


  if(_font.getFontHeight() < 24)
  {
    _textOfs = 3;
  }
  else
  {
    _textOfs = 5;
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void StringListWidget::setList(const StringList& list)
{
  _list = list;

  ListWidget::recalc();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int StringListWidget::getToolTipIndex(const Common::Point& pos) const
{
  int idx = (pos.y - getAbsY()) / _lineHeight + _currentPos;

  if(idx >= int(_list.size()))
    return -1;
  else
    return idx;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
string StringListWidget::getToolTip(const Common::Point& pos) const
{
  Common::Rect rect = getEditRect();
  int idx = getToolTipIndex(pos);

  if(idx < 0)
    return EmptyString;

  const string value = _list[idx];

  if(uInt32(_font.getStringWidth(value)) > rect.w())
    return _toolTipText + value;
  else
    return _toolTipText;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool StringListWidget::changedToolTip(const Common::Point& oldPos,
                                      const Common::Point& newPos) const
{
  return getToolTipIndex(oldPos) != getToolTipIndex(newPos)
    && getToolTip(oldPos) != getToolTip(newPos);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void StringListWidget::drawWidget(bool hilite)
{
  FBSurface& s = _boss->dialog().surface();
  int i, pos, len = int(_list.size());

  // Draw a thin frame around the list.
  s.frameRect(_x, _y, _w + 1, _h, hilite && _hilite ? kWidColorHi : kColor);

  if (!isEnabled())
    s.fillRect(_x + 1, _y + 1, _w - 1, _h - 2, kDlgColor);

  // Draw the list items
  for (i = 0, pos = _currentPos; i < _rows && pos < len; i++, pos++)
  {
    const int y = _y + 2 + _lineHeight * i;
    ColorId textColor = kTextColor;

    // Draw the selected item inverted, on a highlighted background.
    if (_selectedItem == pos && _hilite)
    {
      if(_hasFocus && !_editMode)
      {
        s.fillRect(_x + 1, _y + 1 + _lineHeight * i, _w - 1, _lineHeight, kTextColorHi);
        textColor = kTextColorInv;
      }
      else
        s.frameRect(_x + 1, _y + 1 + _lineHeight * i, _w - 1, _lineHeight, kWidColorHi);
    }

    Common::Rect r(getEditRect());
    if (_selectedItem == pos && _editMode)
    {
      adjustOffset();

      s.drawString(_font, editString(), _x + r.x(), y, r.w(), textColor,
                   TextAlign::Left, -_editScrollOffset, false);
    }
    else
      s.drawString(_font, _list[pos], _x + r.x(), y, r.w(), textColor);
  }

  // Only draw the caret while editing, and if it's in the current viewport
  if(_editMode &&
     (!_useScrollbar ||
     ((_selectedItem >= _scrollBar->_currentPos) &&
      (_selectedItem < _scrollBar->_currentPos + _rows))))
    drawCaretSelection();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Common::Rect StringListWidget::getEditRect() const
{
  const int offset = std::max(0, (_selectedItem - _currentPos) * _lineHeight);
  return Common::Rect(_textOfs, 1 + offset, _w - _textOfs, _lineHeight + offset);
}
