/* <!-- copyright */
/*
 * aria2 - a simple utility for downloading files faster
 *
 * Copyright (C) 2006 Tatsuhiro Tsujikawa
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
/* copyright --> */
#ifndef _D_CANCEL_MESSAGE_H_
#define _D_CANCEL_MESSAGE_H_

#include "SimplePeerMessage.h"
#include "TorrentMan.h"

class CancelMessage : public SimplePeerMessage {
private:
  int index;
  int begin;
  int length;
  // for check
  int pieces;
  int pieceLength;

  char msg[17];
public:
  CancelMessage():SimplePeerMessage(),
		  index(0), begin(0), length(0),
		  pieces(0), pieceLength(0) {}

  virtual ~CancelMessage() {}

  enum ID {
    ID = 8
  };

  int getIndex() const { return index; }
  void setIndex(int index) { this->index = index; }
  int getBegin() const { return begin; }
  void setBegin(int begin) { this->begin = begin; }
  int getLength() const { return length; }
  void setLength(int length) { this->length = length; }

  void setPieces(int pieces) {
    this->pieces = pieces;
  }
  int getPieces() const { return pieces;}

  void setPieceLength(int pieceLength) {
    this->pieceLength = pieceLength;
  }
  int getPieceLength() const { return pieceLength;}

  static CancelMessage* create(const char* data, int dataLength);

  virtual int getId() const { return ID; }
  virtual void receivedAction();
  virtual const char* getMessage();
  virtual int getMessageLength();
  virtual void check() const;
  virtual string toString() const;
};

#endif // _D_CANCEL_MESSAGE_H_
