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
#include "send_request.hpp"

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

  RequestType request = RequestType(ActionType::PUBLISH_TOPIC, requestParameters);

  // send request
  network::sendRequestWithoutResponse(publisherTcpClient, request);
}

T_TopicStatus Publisher::getTopicStatus(const std::string topicName) const {
  std::map<std::string, std::string> requestParameters = {
    {"topicName", topicName}
  };

  RequestType request = RequestType(ActionType::GET_TOPIC_STATUS, requestParameters);

  // send request
  return network::sendRequest<T_TopicStatus>(publisherTcpClient, request);
}

void Publisher::signalHandler(int signalNumber) {
  if(!instance) return;

  instance->~Publisher();
  std::cout << "TCP-Client closed" << std::endl;
  exit(signalNumber);
}

Publisher::Publisher(void) : publisherTcpClient(std::make_shared<TcpClient>(T_Endpoint{"localhost", "8080"})) {}

Publisher::Publisher(const std::string brokerAddress, const std::string brokerPort) : publisherTcpClient(std::make_shared<TcpClient>(T_Endpoint{brokerAddress, brokerPort})) {
  instance = this;
  publisherTcpClient->connect();
  signal(SIGINT, signalHandler);
  publisherTcpClient->run();
}

Publisher::~Publisher(void) {
  publisherTcpClient->close();
}
