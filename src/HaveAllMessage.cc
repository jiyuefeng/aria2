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
#include "HaveAllMessage.h"
#include "DlAbortEx.h"
#include "PeerInteraction.h"
#include "PeerMessageUtil.h"

HaveAllMessage::HaveAllMessage() {}

HaveAllMessage::~HaveAllMessage() {}

HaveAllMessage* HaveAllMessage::create(const char* data, int dataLength) {
  if(dataLength != 1) {
    throw new DlAbortEx("invalid payload size for %s, size = %d. It should be %d", "have all", dataLength, 1);
  }
  int id = PeerMessageUtil::getId(data);
  if(id != ID) {
    throw new DlAbortEx("invalid ID=%d for %s. It should be %d.",
			id, "have all", ID);
  }
  HaveAllMessage* haveAllMessage = new HaveAllMessage();
  return haveAllMessage;
}

void HaveAllMessage::receivedAction() {
  if(!peer->isFastExtensionEnabled()) {
    throw new DlAbortEx("%s received while fast extension is disabled",
			toString().c_str());
  }
  peer->setAllBitfield();
}

const char* HaveAllMessage::getMessage() {
  if(!inProgress) {
    /**
     * len --- 1, 4bytes
     * id --- 14, 1byte
     * total: 5bytes
     */
    PeerMessageUtil::createPeerMessageString(msg, sizeof(msg), 1, ID);
  }
  return msg;
}

int HaveAllMessage::getMessageLength() {
  return sizeof(msg);
}

void HaveAllMessage::check() const {}

string HaveAllMessage::toString() const {
  return "have all";
}
