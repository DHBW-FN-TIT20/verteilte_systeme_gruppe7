/**************************************************************************************************
 * @file    test_publisher.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    03-June-2023
 * @brief   Unit tests for class PUBLISHER
 *************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "publisher.cpp"
#include <iostream>
#include <cassert>

/*************************************************************************************************
 * Unit tests
 *************************************************************************************************/
const string tempPublishMessage = "This is a test message";
const string tempPublishTopicName = "test-topic-name";
const map<string, string> expectedPublishParameterList = {
  {"topicName", tempPublishTopicName},
  {"message", tempPublishMessage}
};

// mock Publisher "sendRequest" method
class MockPublishTopicPublisher : public Publisher {
  private:
    string sendRequest(const RequestType &request) const override {
      // assert correct parameters
      assert(request.mAction == ActionType::PUBLISH_TOPIC);
      assert(request.mParameterList == expectedPublishParameterList);
      assert(request.mTimestamp == std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
      return "{MockResponse}";
    }
};

void TestPublishTopic() { 
  MockPublishTopicPublisher tempPublisher; 
  tempPublisher.publishTopic(tempPublishTopicName, tempPublishMessage);
}

// test getTopicStatus
const string tempGetTopicTopicName = "test-topic-name";
const map<string, string> expectedGetTopicParameterList = {
  {"topicName", tempGetTopicTopicName},
};

// mock Publisher "sendRequest" method
class MockGetTopicPublisher : public Publisher {
  private:
    string sendRequest(const RequestType &request) const override {
      // assert correct parameters
      assert(request.mAction == ActionType::GET_TOPIC_STATUS);
      assert(request.mParameterList == expectedGetTopicParameterList);
      assert(request.mTimestamp == std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
      return "{MockResponse}";
    }
};

void TestGetTopicStatus() {
  const string tempTopicName = "test-topic-name";
  MockGetTopicPublisher tempPublisher;
  tempPublisher.getTopicStatus(tempTopicName);
}

int main() {
  TestPublishTopic();
  TestGetTopicStatus();

  std::cout << "All tests for class Publisher passed" << std::endl;
  return 0;
}
