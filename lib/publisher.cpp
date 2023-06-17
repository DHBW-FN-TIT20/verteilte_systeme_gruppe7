/**************************************************************************************************
 * @file    publisher.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    14-June-2023
 * @brief   Implementation for class Publisher
 *************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "publisher.h"
#include "send_request.h"

/**************************************************************************************************
 * Public - Class implementation
 *************************************************************************************************/
Publisher::Publisher(const T_Endpoint &endpoint) : mLogger(LOG_FILE_NAME), mTcpClient(std::make_shared<TcpClient>(endpoint)) {
  instance = this;
  signal(SIGINT, signalHandler);
  mTcpClient->connect();
  mOwnEndpoint = T_Endpoint{mTcpClient->socket().local_endpoint().address().to_string(), std::to_string(mTcpClient->socket().local_endpoint().port())};
  mTcpClient->run();
}

Publisher::~Publisher(void) {
  mTcpClient->close();
  instance = nullptr;
}

void Publisher::publishTopic(const std::string topicName, const std::string &message) {
  // create message object
  std::map<std::string, std::string> requestParameters = {
    {"topicName", topicName},
    {"message", message}
  };

  RequestType request = RequestType(ActionType::PUBLISH_TOPIC, requestParameters);

  // send request
  network::sendRequestWithoutResponse(mTcpClient, request);

  /* topic successfully published */
  mLogger.addLogEntry(mOwnEndpoint.toString() + ": published on topic >>" + topicName + "<< with message >>" + message + "<<");
}

T_TopicStatus Publisher::getTopicStatus(const std::string topicName) {
  std::map<std::string, std::string> requestParameters = {
    {"topicName", topicName}
  };

  RequestType request = RequestType(ActionType::GET_TOPIC_STATUS, requestParameters);

  // send request
  T_TopicStatus topicStatus = network::sendRequest<T_TopicStatus>(mTcpClient, request);

  /* topic status received */
  mLogger.addLogEntry(mOwnEndpoint.toString() + ": received topic status >>" + topicStatus.toString() + "<<");

  return topicStatus;
}

void Publisher::signalHandler(int signalNumber) {
  if(instance) {
    instance->~Publisher();
    std::cout << "TCP-Client closed" << std::endl;
  }
  exit(signalNumber);
}
