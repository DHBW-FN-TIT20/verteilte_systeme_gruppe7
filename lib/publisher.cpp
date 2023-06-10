/**************************************************************************************************
 * @file    publisher.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    05-June-2023
 * @brief   Implementation for class Publisher
 *************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "publisher.h"

/**************************************************************************************************
 * Public - Class implementation
 *************************************************************************************************/
std::string Publisher::sendRequest(const RequestType &request) const {
  return "";
}

void Publisher::publishTopic(const std::string topicName, const std::string &message) const {
  // create message object
  std::map<std::string, std::string> requestParameters = {
    {"topicName", topicName},
    {"message", message}
  };

  const RequestType request = RequestType(ActionType::PUBLISH_TOPIC, requestParameters);

  // send request
  const std::string responeMessage = sendRequest(request);
}

void Publisher::getTopicStatus(const std::string topicName) const {
  std::map<std::string, std::string> requestParameters = {
    {"topicName", topicName}
  };

  const RequestType request = RequestType(ActionType::GET_TOPIC_STATUS, requestParameters);

  // send request
  sendRequest(request);
}

Publisher::Publisher(void) : publisherTcpClient(std::make_shared<TcpClient>(T_Endpoint{"localhost", "8080"})) {}

Publisher::Publisher(const std::string brokerAddress, const std::string brokerPort) : publisherTcpClient(std::make_shared<TcpClient>(T_Endpoint{brokerAddress, brokerPort})) {
  publisherTcpClient->connect();
}

Publisher::~Publisher(void) {
  publisherTcpClient->run();
  publisherTcpClient->close();
}
