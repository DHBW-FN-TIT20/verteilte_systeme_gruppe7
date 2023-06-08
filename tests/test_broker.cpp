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
 * Test class
 *************************************************************************************************/
class MockBroker : public Broker {
  public:
    MockBroker(const T_TopicList& topicList) : Broker::Broker() {
      mTopicList = topicList;
    }

    bool isTopicExistent(const std::string &topicName) const {
      return Broker::isTopicExistent(topicName);
    }

    bool hasSubscriber(const std::string &topicName, const T_Endpoint &subscriber) const {
      return Broker::hasSubscriber(topicName, subscriber);
    }

    ActionStatusType subscribeTopic(const std::string &topicName, const T_Endpoint &subscriber) {
      return Broker::subscribeTopic(topicName, subscriber);
    }

    ActionStatusType unsubscribeTopic(const std::string &topicName, const T_Endpoint &subscriber) {
      return Broker::unsubscribeTopic(topicName, subscriber);
    }

    ActionStatusType publishTopic(const std::string &topicName, const std::string &message) const {
      return Broker::publishTopic(topicName, message);
    }

    std::vector<std::string> listTopics(void) const {
      return Broker::listTopics();
    }

    T_TopicStatus getTopicStatus(const std::string &topicName) const {
      return Broker::getTopicStatus(topicName);
    }

    void updateTopic(const std::string &topicName, const std::string &message, const std::time_t &timestamp) const {
      return Broker::updateTopic(topicName, message, timestamp);
    }
};

/**************************************************************************************************
 * Unit tests
 *************************************************************************************************/
void TestIsTopicExistent(void) {
  MockBroker testIsTopicExistent({{"existingTopic", {"existingTopic", RequestType(ActionType::PUBLISH_TOPIC, {{"param1", "value1"}}), {/*subscriber list*/}}}});
  assert(testIsTopicExistent.isTopicExistent("existingTopic") == true);
  assert(testIsTopicExistent.isTopicExistent("nonExistentTopic") == false);
}

void TestHasSubscriber(void) {
  MockBroker testHasSubscriber({{"topicName", {"topicName", RequestType(ActionType::PUBLISH_TOPIC, {{"param1", "value1"}}), {{"127.0.0.1", "5000"}}}}});
  assert(testHasSubscriber.hasSubscriber("topicName", {"127.0.0.1", "5000"}) == true);
  assert(testHasSubscriber.hasSubscriber("topicName", {"0.0.0.0", "0"}) == false);
}

void TestSubscribeTopic(void) {
  MockBroker testSubscribeTopic({{"topicName", {"topicName", RequestType(ActionType::PUBLISH_TOPIC, {{"param1", "value1"}}), {/*subscriber list*/}}}});
  assert(testSubscribeTopic.subscribeTopic("wrongTopicName", {"0.0.0.0", "0"}) == ActionStatusType::TOPIC_NON_EXISTENT);
  assert(testSubscribeTopic.subscribeTopic("topicName", {"0.0.0.0", "0"}) == ActionStatusType::STATUS_OK);
  assert(testSubscribeTopic.subscribeTopic("topicName", {"0.0.0.0", "0"}) == ActionStatusType::INTERNAL_ERROR); //subscriber already exists now
}

void TestUnsubscribeTopic(void) {
  MockBroker testUnsubscribeTopic({{"topicName", {"topicName", RequestType(ActionType::PUBLISH_TOPIC, {{"param1", "value1"}}), {{"0.0.0.0", "0"}}}}});
  assert(testUnsubscribeTopic.unsubscribeTopic("wrongTopicName", {"0.0.0.0", "0"}) == ActionStatusType::TOPIC_NON_EXISTENT);
  assert(testUnsubscribeTopic.unsubscribeTopic("wrongTopicName", {"0.0.0.0", "1"}) == ActionStatusType::INTERNAL_ERROR);


}

void TestPublishTopic(void) {

}

void TestListTopics(){
  MockBroker testListTopics(
    {
      {"topicName1", {"topicName1", RequestType(ActionType::PUBLISH_TOPIC, {{"param1", "value1"}, {"param2", "value2"}}), {/*subscriber list*/}}},
      {"topicName2", {"topicName2", RequestType(ActionType::PUBLISH_TOPIC, {{"param1", "value1"}, {"param2", "value2"}}), {/*subscriber list*/}}}
    }
  );

  std::vector<std::string> expectedTopicList = {"topicName1", "topicName2"};

  std::vector<std::string> resultTopicList = testListTopics.listTopics();

  assert(resultTopicList == expectedTopicList);
}

void TestGetTopicStatus(void) {

}

void TestUpdateTopic(void) {

}

void TestMessageHandler(void) {

}

int main() {
  TestIsTopicExistent();
  TestHasSubscriber();
  TestSubscribeTopic();
  TestUnsubscribeTopic();
  TestPublishTopic();
  TestListTopics();
  TestGetTopicStatus();
  TestUpdateTopic();
  TestMessageHandler();

  std::cout << "All tests for class Broker passed" << std::endl;
  return 0;
}
