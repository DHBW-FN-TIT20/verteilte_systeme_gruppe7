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

/*************************************************************************************************
 * Unit tests
 *************************************************************************************************/
void TestPublishTopic() {
  PUBLISHER tempPublisher;
  const string tempTopicName = "test-topic-name";
  const string tempMessage = "This is a test message";

  tempPublisher.publishTopic(tempTopicName, tempMessage);
}

int main() {
  TestPublishTopic();

  std::cout << "All tests for class PUBLISHER passed" << std::endl;
  return 0;
}
