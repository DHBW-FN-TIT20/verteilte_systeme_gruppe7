/**************************************************************************************************
 * @file    test_publisher.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    31-May-2023
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
const string tempMessage = "This is a test message";
const string tempTopicName = "test-topic-name";
const map<string, string> expectedParameterList = {
  {"topicName", tempTopicName},
  {"message", tempMessage}
};

// mock Publisher "sendRequest" method
class MockPublisher : public Publisher {
  private:
    string sendRequest(const RequestType &request) const override {
      // assert correct parameters
      assert(request.mAction == ACTION_ENUM::PUBLISH_TOPIC);
      assert(request.mParameterList == expectedParameterList);
      assert(request.mTimestamp == std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
      return "{MockResponse}";
    }
};

void TestPublishTopic() { 
  MockPublisher tempPublisher; 
  tempPublisher.publishTopic(tempTopicName, tempMessage);
}

int main() {
  TestPublishTopic();

  std::cout << "All tests for class Publisher passed" << std::endl;
  return 0;
}
