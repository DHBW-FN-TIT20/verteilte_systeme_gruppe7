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
bool Broker::isTopicExistent(std::string topicName) const {
  return mTopicList.count(topicName) > 0U;
}

ActionStatusType Broker::subscribeTopic(std::string topicName, T_Endpoint subscriber) {
  //check if topic exists
    //yes: add endpoint of subscriber to subscriber list of the topic
    //no: return respective error type
}

ActionStatusType Broker::unsubscribeTopic(std::string topicName, T_Endpoint subscriber) {
  //check if topic exists
    //yes: check if subscriber exists in subscriber list of the topic
      //yes: delete subscriber from the list, return success
      //no: return respective error type
    //no: return respective error type
}

ActionStatusType Broker::publishTopic(std::string topicName, std::string &message) const {
  //check if topic exists
    //yes: generate timestamp and call update topic(), then return success
    //no: return respective error type
}

std::vector<std::string> Broker::listTopics() const {
  std::vector<std::string> keys;
  keys.reserve(mTopicList.size());

  for (const auto& pair : mTopicList) {
      keys.push_back(pair.first);
  }
  return keys;
}

T_TopicStatus Broker::getTopicStatus(std::string topicName) const {
  //check if topic exists
    //yes: return T_Topic object from topic list that matches given topicName
    //no: return respective error type
}

void Broker::updateTopic(std::string topicName, std::string &message, std::time_t timestamp) const {
  //send request (RequestType) with topicName, message and timestamp to every subscriber
  //in the subscriber list of the given topic using udp!
}

/* public member functions */
Broker::Broker(void) {}

Broker::Broker(const T_TopicList& topicList) : mTopicList(topicList) {}

Broker::~Broker(void) {}

void Broker::messageHandler(std::shared_ptr<TcpConnection> conn, const std::string message) {
  tcp::endpoint endpoint = conn->socket().remote_endpoint();
  T_Endpoint clientEndpoint {
    endpoint.address().to_string(),
    std::to_string(endpoint.port())
  };

  //parse message
  
  //decide which function to call based on the message's body

  //call the function

  //encode the return value of the function; add the action status; add delimiter and "\n" at the end of the response message

  //send the response back to the client
}
