/**
  *************************************************************************************************
  * @file    test_subscriber.cpp
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    30-May-2023
  * @brief   Unit tests for class Subscriber
  *************************************************************************************************
  */

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "subscriber.cpp"
#include <iostream>
#include <cassert>
#include <sstream>

/**************************************************************************************************
 * Macros
 *************************************************************************************************/
#define EXAMPLE_ADDRESS (std::string)("127.0.0.1")
#define EXAMPLE_PORT    (int)(8080)

/**************************************************************************************************
 * Test class
 *************************************************************************************************/
class TestSubscriber : public Subscriber {
  public:
    ACTION_STATUS_ENUM unsubscribeTopic(std::string topicName) const {
      return Subscriber::unsubscribeTopic(topicName);
    }

    void updateTopic(std::string topicName, std::string &msg, std::time_t timestamp) const {
      return Subscriber::updateTopic(topicName, msg, timestamp);
    }

    TestSubscriber(std::string address, int port) : Subscriber::Subscriber(address, port) {}
};

/**************************************************************************************************
 * Function prototypes
 *************************************************************************************************/
void TestUnsubscribeTopic(void);
void TestGetTopicStatus(void);
void TestUpdateTopic(void);
void TestConstructor(void);
void TestSubscribeTopic(void);
void TestListTopics(void);

/**************************************************************************************************
 * Unit tests
 *************************************************************************************************/

void TestUnsubscribeTopic(void) {

}

void TestUpdateTopic(void) {
  TestSubscriber testSubscriberUpdateTopic(EXAMPLE_ADDRESS, EXAMPLE_PORT);
  std::string tempTopicName = "topic name";
  std::string tempMsg = "topic msg";
  std::time_t tempTimestamp = static_cast<std::time_t>(1685428115);
  std::stringstream buffer;
  std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
  testSubscriberUpdateTopic.updateTopic(tempTopicName, tempMsg, tempTimestamp);
  std::cout.rdbuf(oldCoutBuffer);
  std::string output = buffer.str();
  assert(output == "30.05.2023 08:28:35: topic name: >>topic msg<<\n");
}

int main() {
  TestUpdateTopic();

  std::cout << "All tests for class Subscriber passed" << std::endl;
  return 0;
}