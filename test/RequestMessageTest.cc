#include "RequestMessage.h"
#include "PeerMessageUtil.h"
#include <cppunit/extensions/HelperMacros.h>

using namespace std;

class RequestMessageTest:public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(RequestMessageTest);
  CPPUNIT_TEST(testCreate);
  CPPUNIT_TEST(testGetMessage);
  CPPUNIT_TEST_SUITE_END();
private:

public:
  void setUp() {
  }

  void testCreate();
  void testGetMessage();
};


CPPUNIT_TEST_SUITE_REGISTRATION(RequestMessageTest);

void RequestMessageTest::testCreate() {
  char msg[17];
  PeerMessageUtil::createPeerMessageString(msg, sizeof(msg), 13, 6);
  PeerMessageUtil::setIntParam(&msg[5], 12345);
  PeerMessageUtil::setIntParam(&msg[9], 256);
  PeerMessageUtil::setIntParam(&msg[13], 1024);
  RequestMessage* pm = RequestMessage::create(&msg[4], 13);
  CPPUNIT_ASSERT_EQUAL(6, pm->getId());
  CPPUNIT_ASSERT_EQUAL(12345, pm->getIndex());
  CPPUNIT_ASSERT_EQUAL(256, pm->getBegin());
  CPPUNIT_ASSERT_EQUAL(1024, pm->getLength());

  // case: payload size is wrong
  try {
    char msg[18];
    PeerMessageUtil::createPeerMessageString(msg, sizeof(msg), 14, 6);
    RequestMessage::create(&msg[4], 14);
    CPPUNIT_FAIL("exception must be threw.");
  } catch(...) {
  }
  // case: id is wrong
  try {
    char msg[17];
    PeerMessageUtil::createPeerMessageString(msg, sizeof(msg), 13, 7);
    RequestMessage::create(&msg[4], 13);
    CPPUNIT_FAIL("exception must be threw.");
  } catch(...) {
  }
}

void RequestMessageTest::testGetMessage() {
  RequestMessage msg;
  msg.setIndex(12345);
  msg.setBegin(256);
  msg.setLength(1024);
  char data[17];
  PeerMessageUtil::createPeerMessageString(data, sizeof(data), 13, 6);
  PeerMessageUtil::setIntParam(&data[5], 12345);
  PeerMessageUtil::setIntParam(&data[9], 256);
  PeerMessageUtil::setIntParam(&data[13], 1024);
  CPPUNIT_ASSERT(memcmp(msg.getMessage(), data, 17) == 0);
}
