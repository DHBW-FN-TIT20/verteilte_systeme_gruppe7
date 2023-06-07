/**************************************************************************************************
 * @file    broker.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    07-June-2023
 * @brief   Implementation for class Broker
 *************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "broker.h"

/**************************************************************************************************
 * Class implementation
 *************************************************************************************************/

/* private/protected member functions */
std::vector<std::string> Broker::listTopics() const {
  std::vector<std::string> keys;
  keys.reserve(mTopicList.size());

  for (const auto& pair : mTopicList) {
      keys.push_back(pair.first);
  }
  return keys;
}

/* public member functions */
Broker::Broker(const T_TopicList& topicList) : mTopicList(topicList) {}

Broker::Broker(void) {}

void Broker::messageHandler(std::shared_ptr<TcpConnection> conn, const std::string message) {
  //parse message
  
  //decide which function to call based on the message's body

  //call the function

  //encode the return value of the function; add the action status; add delimiter and "\n" at the end of the response message

  //send the response back to the client
}
