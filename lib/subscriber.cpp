/**************************************************************************************************
  * @file    subscriber.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    10-June-2023
  * @brief   Implementation for class Subscriber
  ************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "subscriber.h"

/**************************************************************************************************
 * Class implementation
 *************************************************************************************************/
/* private/protected member functions */
void Subscriber::unsubscribeTopic(const std::string &topicName) {
  RequestType request(ActionType::UNSUBSCRIBE_TOPIC, {{"topicName", topicName}});

  (void)network::sendRequestWithoutResponse(mTcpClient, request);

  /* successfully unsubscribed */
  std::cout << "Successfully unsubscribed from topic >>" << topicName << "<<" << std::endl;
  mLogger.addLogEntry(mOwnEndpoint.toString() + ": unsubscribed from topic >>" + topicName + "<<");
}

/* public member functions */
Subscriber::Subscriber(const T_Endpoint &endpoint, std::function<void(const std::string)> callback) : mServerEndpoint(endpoint), mMessageParser(), mLogger(LOG_FILE_NAME), mTcpClient(std::make_shared<TcpClient>(mServerEndpoint, [callback](const std::string message) {callback(message);})) {
  instance = this;
  signal(SIGINT, signalHandler);
  mTcpClient->connect();
  mOwnEndpoint = T_Endpoint{mTcpClient->socket().local_endpoint().address().to_string(), std::to_string(mTcpClient->socket().local_endpoint().port())};
  mTcpClient->run();
}

Subscriber::~Subscriber() {
  if(mTopicName != "") {
    unsubscribeTopic(mTopicName);
  }
  mTcpClient->close();
  instance = nullptr;
}

void Subscriber::subscribeTopic(const std::string &topicName) {
  mTopicName = topicName;
  RequestType request(ActionType::SUBSCRIBE_TOPIC, {{"topicName", topicName}});

  (void)network::sendRequestWithoutResponse(mTcpClient, request);

  /* successfully subscribed */
  mLogger.addLogEntry(mOwnEndpoint.toString() + ": subscribed to topic >>" + topicName + "<<");
}

T_TopicNameList Subscriber::listTopics(void) {
  RequestType request(ActionType::LIST_TOPICS, {});

  T_TopicNameList topicList = network::sendRequest<T_TopicNameList>(mTcpClient, request);

  /* topic list received */
  mLogger.addLogEntry(mOwnEndpoint.toString() + ": received topic list >>" + topicList.toString() + "<<");
  return topicList;
}

void Subscriber::signalHandler(int signum) {
  if(instance) {
    instance->~Subscriber();
    std::cout << "TCP-Client closed" << std::endl;
    exit(signum);
  }
}
