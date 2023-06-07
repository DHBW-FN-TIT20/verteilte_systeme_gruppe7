/**************************************************************************************************
 * @file    test_broker.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    06-June-2023
 * @brief   Unit tests for class Broker
 *************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <iostream>
#include <cassert>
#include "broker.h"
#include "topic_list_type.h"
#include "action_type.h"

/**************************************************************************************************
 * Unit tests
 *************************************************************************************************/
class MockBroker : public Broker {
  public:
    MockBroker(const T_TopicList& topicList) : Broker::Broker(topicList) {}

    std::vector<std::string> listTopics() {
      return Broker::listTopics();
    }
};

void TestListTopics(){
  MockBroker tempBroker(
    {
      {"topicName1", {"topicName1", RequestType(ActionType::PUBLISH_TOPIC, {{"param1", "value1"}, {"param2", "value2"}})}},
      {"topicName2", {"topicName2", RequestType(ActionType::PUBLISH_TOPIC, {{"param1", "value1"}, {"param2", "value2"}})}}
    }
  );

  std::vector<std::string> expectedTopicList = {"topicName1", "topicName2"};

  std::vector<std::string> resultTopicList = tempBroker.listTopics();

  assert(resultTopicList == expectedTopicList);
}

int main() {
  TestListTopics();

  std::cout << "All tests for class Broker passed" << std::endl;
  return 0;
}
