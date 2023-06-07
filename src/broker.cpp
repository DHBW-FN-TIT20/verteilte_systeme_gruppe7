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
bool Broker::isTopicExistent(std::string &topicName) const {
  return mTopicList.count(topicName) > 0U;
}

bool Broker::hasSubscriber(std::string &topicName, T_Endpoint &subscriber) const {
  T_SubscriberList subscriberList = mTopicList.at(topicName).SubscriberList;
  return std::find(subscriberList.begin(), subscriberList.end(), subscriber) != subscriberList.end();
}

ActionStatusType Broker::subscribeTopic(std::string topicName, T_Endpoint subscriber) {
  std::lock_guard<std::mutex> lock(mTopicListMutex);

  if(isTopicExistent(topicName)) {
    mTopicList.at(topicName).SubscriberList.push_back(subscriber);
  } else {
    return ActionStatusType::TOPIC_NON_EXISTENT;
  }
  return ActionStatusType::STATUS_OK;
}

ActionStatusType Broker::unsubscribeTopic(std::string topicName, T_Endpoint subscriber) {
  std::lock_guard<std::mutex> lock(mTopicListMutex);

  if(isTopicExistent(topicName)) {
    if(hasSubscriber(topicName, subscriber)) {
      T_SubscriberList &subscriberList = mTopicList.at(topicName).SubscriberList;
      subscriberList.erase(std::remove(subscriberList.begin(), subscriberList.end(), subscriber), subscriberList.end());
      if(subscriberList.empty()) {
        mTopicList.erase(topicName);
      }
      return ActionStatusType::STATUS_OK;     //Subscriber successfully unsubscribed; topic removed if applicable
    } else {
      return ActionStatusType::INTERNAL_ERROR;  //subscriber was not in the subscriber list of the respective topic
    }
  } else {
    return ActionStatusType::TOPIC_NON_EXISTENT;    //topic was not in the topic list of the broker
  }

}

ActionStatusType Broker::publishTopic(std::string topicName, [[maybe_unused]]std::string &message) const {
  std::lock_guard<std::mutex> lock(mTopicListMutex);

  if(isTopicExistent(topicName)) {
    //generate timestamp and call update topic(), then return success
  } else {
    return ActionStatusType::TOPIC_NON_EXISTENT;
  }
  return ActionStatusType::STATUS_OK;
}

std::vector<std::string> Broker::listTopics() const {
  std::lock_guard<std::mutex> lock(mTopicListMutex);
  std::vector<std::string> keys;
  
  keys.reserve(mTopicList.size());

  for (const auto& pair : mTopicList) {
      keys.push_back(pair.first);
  }
  return keys;
}

T_TopicStatus Broker::getTopicStatus([[maybe_unused]]std::string topicName) const {
  std::lock_guard<std::mutex> lock(mTopicListMutex);
  //check if topic exists
    //yes: return T_Topic object from topic list that matches given topicName
    //no: return respective error type
  
  return {1,{},ActionStatusType::STATUS_OK};
}

void Broker::updateTopic([[maybe_unused]]std::string topicName, [[maybe_unused]]std::string &message, [[maybe_unused]]std::time_t timestamp) const {
  //send request (RequestType) with topicName, message and timestamp to every subscriber
  //in the subscriber list of the given topic using udp!
}

/* public member functions */
Broker::Broker(void) {}

Broker::Broker(const T_TopicList &topicList) : mTopicList(topicList) {}

Broker::~Broker(void) {}

void Broker::messageHandler(std::shared_ptr<TcpConnection> conn, [[maybe_unused]]const std::string message) {
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
