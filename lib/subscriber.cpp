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
void Subscriber::unsubscribeTopic(const std::string &topicName) const {
  RequestType request(ActionType::UNSUBSCRIBE_TOPIC, {{"topicName", topicName}});

  //(void)sendRequestWithoutResponse(subscriberTcpClient, request);

  /* successfully unsubscribed */
  std::cout << "Successfully unsubscribed from topic >>" << topicName << "<<" << std::endl;
  //log

}

void Subscriber::updateTopic(const std::string &topicName, const std::string &msg, const std::time_t &timestamp) const {
  
}

/* public member functions */
Subscriber::Subscriber(const std::string &address, const std::string &port) : mServerEndpoint(T_Endpoint{address, port}), mMessageParser(), mLogger(LOG_FILE_NAME), mTcpClient(std::make_shared<TcpClient>(mServerEndpoint, messageHandler)) {}

Subscriber::~Subscriber() {}

void Subscriber::subscribeTopic(const std::string &topicName) {

}

void Subscriber::listTopics(void) {

}

void Subscriber::messageHandler(const std::string message) const {
  
}

void Subscriber::signalHandler(int signum) {
  if(instance) {
    mTcpClient->close();
    std::cout << "TCP-Client closed" << std::endl;
    exit(signum);
  }
}
