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
#ifndef _D_REQUEST_MESSAGE_H_
#define _D_REQUEST_MESSAGE_H_

#include "SimplePeerMessage.h"
#include "TorrentMan.h"

class RequestMessage : public SimplePeerMessage {
private:
  int index;
  int begin;
  int length;
  int blockIndex;
  // for check
  int pieces;
  int pieceLength;
  
  char msg[17];
public:
  RequestMessage():SimplePeerMessage(),
		   index(0), begin(0), length(0), blockIndex(0),
		   pieces(0), pieceLength(0) {}
  virtual ~RequestMessage() {}

  enum ID {
    ID = 6
  };

  int getIndex() const { return index; }
  void setIndex(int index) { this->index = index; }
  int getBegin() const { return begin; }
  void setBegin(int begin) { this->begin = begin; }
  int getLength() const { return length; }
  void setLength(int length) { this->length = length; }
  int getBlockIndex() const { return blockIndex; }
  void setBlockIndex(int blockIndex) { this->blockIndex = blockIndex; }

  void setPieces(int pieces) {
    this->pieces = pieces;
  }
  int getPieces() const { return pieces;}

  void setPieceLength(int pieceLength) {
    this->pieceLength = pieceLength;
  }
  int getPieceLength() const { return pieceLength;}

  static RequestMessage* create(const char* data, int dataLength);

  virtual int getId() const { return ID; }
  virtual void receivedAction();
  virtual const char* getMessage();
  virtual int getMessageLength();
  virtual void check() const;
  virtual string toString() const;
};

#endif // _D_REQUEST_MESSAGE_H_
