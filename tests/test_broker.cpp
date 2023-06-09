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
 * Public - global variables
 *************************************************************************************************/
Broker* Broker::instance = nullptr;

/**************************************************************************************************
 * Test class
 *************************************************************************************************/
class MockBroker : public Broker {
  public:
    MockBroker(const T_TopicList& topicList) : Broker::Broker() {
      mTopicList = topicList;
    }

    /**
     * @brief Getter function for topic list of class Broker.
     * 
     * @return T_TopicList Topic list of class Broker
     */
    T_TopicList getBrokerTopicList(void) const {
      return mTopicList;
    }

    bool isTopicExistent(const std::string &topicName) const {
      return Broker::isTopicExistent(topicName);
    }

    bool hasSubscriber(const std::string &topicName, const T_Subscriber &subscriber) const {
      return Broker::hasSubscriber(topicName, subscriber);
    }

    ActionStatusType subscribeTopic(const std::string &topicName, const T_Subscriber &subscriber) {
      return Broker::subscribeTopic(topicName, subscriber);
    }

    ActionStatusType unsubscribeTopic(const std::string &topicName, const T_Subscriber &subscriber) {
      return Broker::unsubscribeTopic(topicName, subscriber);
    }

    ActionStatusType publishTopic(RequestType &requestFromPublisher) {
      return Broker::publishTopic(requestFromPublisher);
    }

    std::vector<std::string> listTopics(void) const {
      return Broker::listTopics();
    }

    T_TopicStatus getTopicStatus(const std::string &topicName) const {
      return Broker::getTopicStatus(topicName);
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
  MockBroker testHasSubscriber({{"topicName", {"topicName", RequestType(ActionType::PUBLISH_TOPIC, {{"param1", "value1"}}), {{{"127.0.0.1", "5000"}, nullptr}}}}});
  assert(testHasSubscriber.hasSubscriber("topicName", {{"127.0.0.1", "5000"}, nullptr}) == true);
  assert(testHasSubscriber.hasSubscriber("topicName", {{"0.0.0.0", "0"}, nullptr}) == false);
}

void TestSubscribeTopic(void) {
  MockBroker testSubscribeTopic({{"topicName", {"topicName", RequestType(ActionType::PUBLISH_TOPIC, {{"param1", "value1"}}), {/*subscriber list*/}}}});
  assert(testSubscribeTopic.subscribeTopic("wrongTopicName", {{"0.0.0.0", "0"}, nullptr}) == ActionStatusType::TOPIC_NON_EXISTENT);
  assert(testSubscribeTopic.subscribeTopic("topicName", {{"0.0.0.0", "0"}, nullptr}) == ActionStatusType::STATUS_OK);
  assert(testSubscribeTopic.subscribeTopic("topicName", {{"0.0.0.0", "0"}, nullptr}) == ActionStatusType::INTERNAL_ERROR); //subscriber already exists now
}

void TestUnsubscribeTopic(void) {
  MockBroker testUnsubscribeTopic({{"topicName", {"topicName", RequestType(ActionType::PUBLISH_TOPIC, {{"param1", "value1"}}), {{{"0.0.0.0", "0"}, nullptr}, {{"0.0.0.1", "0"}, nullptr}}}}});
  assert(testUnsubscribeTopic.unsubscribeTopic("wrongTopicName", {{"0.0.0.0", "0"}, nullptr}) == ActionStatusType::TOPIC_NON_EXISTENT);
  assert(testUnsubscribeTopic.unsubscribeTopic("topicName", {{"0.0.0.0", "1"}, nullptr}) == ActionStatusType::INTERNAL_ERROR);
  assert(testUnsubscribeTopic.unsubscribeTopic("topicName", {{"0.0.0.1", "0"}, nullptr}) == ActionStatusType::STATUS_OK);
  assert(testUnsubscribeTopic.unsubscribeTopic("topicName", {{"0.0.0.1", "0"}, nullptr}) == ActionStatusType::INTERNAL_ERROR); //subscriber already unsubscribed
  assert(testUnsubscribeTopic.unsubscribeTopic("topicName", {{"0.0.0.0", "0"}, nullptr}) == ActionStatusType::STATUS_OK);
  assert(testUnsubscribeTopic.unsubscribeTopic("topicName", {{"0.0.0.0", "0"}, nullptr}) == ActionStatusType::TOPIC_NON_EXISTENT); //no subscribers left -> topic got deleted
  assert(testUnsubscribeTopic.getBrokerTopicList().empty() == true); //topic list should now be empty
}

void TestPublishTopic(void) {
  MockBroker testPublishTopic({{"existingTopic", {"existingTopic", RequestType(ActionType::PUBLISH_TOPIC, {{"param1", "value1"}}), {/*subscriber list*/}}}});
  RequestType updateRequestOfExistingTopic(ActionType::PUBLISH_TOPIC, {{"topicName", "existingTopic"}, {"message", "Test message for existing topic"}}, 1234567890);
  RequestType checkUpdatedRequestOfExistingTopic(ActionType::PUBLISH_TOPIC, {{"topicName", "existingTopic"}, {"message", "Test message for existing topic"}}, 1234567890);
  RequestType requestPublishNewTopic(ActionType::PUBLISH_TOPIC, {{"topicName", "newTopic"}, {"message", "Test message for new topic"}}, 1234567890);
  RequestType updateRequestOfNewTopic(ActionType::PUBLISH_TOPIC, {{"topicName", "newTopic"}, {"message", "Updated message for new topic"}}, 12345);
  RequestType checkUpdatedRequestOfNewTopic(ActionType::PUBLISH_TOPIC, {{"topicName", "newTopic"}, {"message", "Updated message for new topic"}}, 12345);
  assert(testPublishTopic.publishTopic(updateRequestOfExistingTopic) == ActionStatusType::STATUS_OK);  //publish existing topic
  assert(testPublishTopic.getBrokerTopicList().at("existingTopic").Request == checkUpdatedRequestOfExistingTopic);   //check if request of existing topic has been updated
  assert(testPublishTopic.publishTopic(requestPublishNewTopic) == ActionStatusType::STATUS_OK);   //publish new topic
  assert(testPublishTopic.getBrokerTopicList().count("newTopic") > 0);  //check if new topic has been added to the topic list
  assert(testPublishTopic.publishTopic(updateRequestOfNewTopic) == ActionStatusType::STATUS_OK);  //publish message on new topic
  assert(testPublishTopic.getBrokerTopicList().at("newTopic").Request == checkUpdatedRequestOfNewTopic);  //check if request of new topic has been updated
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
  MockBroker testGetTopicStatus({{"topicName", {"topicName", RequestType(ActionType::PUBLISH_TOPIC, {{"param1", "value1"}}, static_cast<std::time_t>(1234567890)), {{{"0.0.0.1", "1"}, nullptr}, {{"0.0.0.2", "2"}, nullptr}}}}});
  T_TopicStatus expectedTopicStatus = {1234567890, {{{"0.0.0.1", "1"}, nullptr}, {{"0.0.0.2", "2"}, nullptr}}};
  assert(testGetTopicStatus.getTopicStatus("topicName") == expectedTopicStatus);
}

int main() {
  TestIsTopicExistent();
  TestHasSubscriber();
  TestSubscribeTopic();
  TestUnsubscribeTopic();
  TestPublishTopic();
  TestListTopics();
  TestGetTopicStatus();

  std::cout << "All tests for class Broker passed" << std::endl;
  return 0;
}
