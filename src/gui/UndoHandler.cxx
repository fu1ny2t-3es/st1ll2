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

#include "UndoHandler.hxx"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
UndoHandler::UndoHandler(size_t size)
  : mySize{size}
{
  reset();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void UndoHandler::reset()
{
  myBuffer.clear();
  myCharMode = false;
  myRedoCount = 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void UndoHandler::doChar()
{
  myCharMode = true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool UndoHandler::endChars(string_view text)
{
  if(myCharMode)
  {
    doo(text);

    return true;
  }
  return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void UndoHandler::doo(string_view text)
{
  // clear redos
  for(; myRedoCount; myRedoCount--)
    myBuffer.pop_front();

  // limit buffer size
  if(myBuffer.size() == mySize)
    myBuffer.pop_back();

  // add text to buffer
  myBuffer.emplace_front(text);
  myCharMode = false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool UndoHandler::undo(string& text)
{
  if(myBuffer.size() > myRedoCount + 1)
  {
    text = myBuffer[++myRedoCount];

    return true;
  }
  return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool UndoHandler::redo(string& text)
{
  if(myRedoCount)
  {
    text = myBuffer[--myRedoCount];

    return true;
  }
  return false;
}
