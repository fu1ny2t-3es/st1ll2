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
//
//   Based on code from ScummVM - Scumm Interpreter
//   Copyright (C) 2002-2004 The ScummVM project
//============================================================================

#ifndef GUI_OBJECT_HXX
#define GUI_OBJECT_HXX

class Dialog;
class DialogContainer;
class Widget;
class OSystem;

#include "Command.hxx"
#include "Vec.hxx"

using WidgetArray = vector<Widget*>;

/**
  This is the base class for all GUI objects/widgets.

  @author  Stephen Anthony
*/
class GuiObject : public CommandReceiver
{
  friend class Widget;
  friend class DialogContainer;

  public:
    enum : uInt32 {  // NOLINT: use 32-bit, even though 16-bit is sufficient
      FLAG_ENABLED = 1 << 0,
      FLAG_INVISIBLE = 1 << 1,
      FLAG_HILITED = 1 << 2,
      FLAG_BORDER = 1 << 3,
      FLAG_CLEARBG = 1 << 4,
      FLAG_TRACK_MOUSE = 1 << 5,
      FLAG_RETAIN_FOCUS = 1 << 6,
      FLAG_WANTS_TAB = 1 << 7,
      FLAG_WANTS_RAWDATA = 1 << 8,
      FLAG_NOBG = 1 << 9,
      FLAG_MOUSE_FOCUS = 1 << 10
    };

  public:
    // The commands generated by various widgets
    enum: uInt32 {  // NOLINT: use 32-bit, even though 16-bit is sufficient
      kOKCmd           = 'OK  ',
      kCloseCmd        = 'CLOS',
      kNextCmd         = 'NEXT',
      kPrevCmd         = 'PREV',
      kDefaultsCmd     = 'DEFA',
      kSetPositionCmd  = 'SETP'
    };

  public:
    GuiObject(OSystem& osystem, DialogContainer& parent, Dialog& dialog,
              int x, int y, int w, int h)
      : myOSystem{osystem},
        myParent{parent},
        myDialog{dialog},
        _x{x}, _y{y}, _w{w}, _h{h} { }

    ~GuiObject() override = default;

    OSystem& instance() const       { return myOSystem; }
    DialogContainer& parent() const { return myParent;  }
    Dialog& dialog() const          { return myDialog;  }

    virtual int getAbsX() const     { return _x; }
    virtual int getAbsY() const     { return _y; }
    virtual int getChildX() const   { return getAbsX(); }
    virtual int getChildY() const   { return getAbsY(); }
    virtual int getWidth() const    { return _w; }
    virtual int getHeight() const   { return _h; }

    virtual void setWidth(int w)    { _w = w; }
    virtual void setHeight(int h)   { _h = h; }

    virtual bool isVisible() const = 0;

    virtual void setDirty() = 0;
    virtual void setDirtyChain() = 0;
    void clearDirty() { _dirty = false; }
    void clearDirtyChain() { _dirtyChain = false; }
    bool isDirty() const { return _dirty; }
    bool isChainDirty() const { return _dirtyChain; }

    // The GUI indicates if its underlying surface needs to be redrawn
    //  and then re-rendered
    virtual bool needsRedraw() { return isDirty() || isChainDirty(); }

    virtual void tick() = 0;

    void setFlags(uInt32 flags, bool updateDirty = true)
    {
      const uInt32 oldFlags = _flags;

      _flags |= flags;
      if(updateDirty && oldFlags != _flags)
        setDirty();
    }
    void clearFlags(uInt32 flags, bool updateDirty = true)
    {
      const uInt32 oldFlags = _flags;

      _flags &= ~flags;
      if(updateDirty && oldFlags != _flags)
        setDirty();
    }
    uInt32 getFlags() const { return _flags; }

    bool hasBorder() const { return _flags & FLAG_BORDER; }
    bool clearsBackground() const { return _flags & FLAG_CLEARBG; }
    bool hasBackground() const { return !(_flags & FLAG_NOBG); }

    /** Add given widget(s) to the focus list */
    virtual void addFocusWidget(Widget* w) = 0;
    virtual int addToFocusList(const WidgetArray& list) = 0;

    /** Return focus list for this object */
    WidgetArray& getFocusList() { return _focusList; }

    /** Redraw the focus list */
    virtual void redrawFocus() { }

    /** Special characters for menues */
    const string ELLIPSIS = "\x1d";
    const string DEGREE = "\x1c";

  protected:
    virtual void releaseFocus() = 0;
    virtual void draw() = 0;
    virtual void drawChain() = 0;

    virtual string getHelpURL() const = 0;
    virtual bool hasHelp() const = 0;

  private:
    OSystem&         myOSystem;
    DialogContainer& myParent;
    Dialog&          myDialog;

  protected:
    int         _x{0}, _y{0}, _w{0}, _h{0};
    bool        _dirty{false};
    bool        _dirtyChain{false};
    uInt32      _flags{0};

    Widget*     _firstWidget{nullptr};
    WidgetArray _focusList;

  private:
    // Following constructors and assignment operators not supported
    GuiObject() = delete;
    GuiObject(const GuiObject&) = delete;
    GuiObject(GuiObject&&) = delete;
    GuiObject& operator=(const GuiObject&) = delete;
    GuiObject& operator=(GuiObject&&) = delete;
};

#endif
