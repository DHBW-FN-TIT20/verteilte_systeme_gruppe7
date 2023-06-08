/**************************************************************************************************
 * @file    broker.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    08-June-2023
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
bool Broker::isTopicExistent(const std::string &topicName) const {
  return mTopicList.count(topicName) > 0U;
}

bool Broker::hasSubscriber(const std::string &topicName, const T_Subscriber &subscriber) const {
  T_SubscriberList subscriberList = mTopicList.at(topicName).SubscriberList;
  return std::find(subscriberList.begin(), subscriberList.end(), subscriber) != subscriberList.end();
}

ActionStatusType Broker::subscribeTopic(const std::string &topicName, const T_Subscriber &subscriber) {
  std::lock_guard<std::mutex> lock(mTopicListMutex);

  if(isTopicExistent(topicName)) {
    if(!hasSubscriber(topicName, subscriber)) {
      mTopicList.at(topicName).SubscriberList.push_back(subscriber);
    } else {
      return ActionStatusType::INTERNAL_ERROR;  //subscriber already subscribed to this topic
    }
  } else {
    return ActionStatusType::TOPIC_NON_EXISTENT;
  }
  return ActionStatusType::STATUS_OK;
}

ActionStatusType Broker::unsubscribeTopic(const std::string &topicName, const T_Subscriber &subscriber) {
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

ActionStatusType Broker::publishTopic(RequestType &requestFromPublisher) {
  std::lock_guard<std::mutex> lock(mTopicListMutex);

  std::string topicName = requestFromPublisher.mParameterList.at("topicName");
  if(isTopicExistent(topicName)) {
    mTopicList.at(topicName).Request = requestFromPublisher;  //update request of topic in topic list
    requestFromPublisher.mAction = ActionType::UPDATE_TOPIC;  //change action to udpate topic
    updateTopic(requestFromPublisher);  //publish updated topic
  } else {
    mTopicList.insert(std::pair<std::string, T_Topic>(topicName, {topicName, requestFromPublisher, {}}));   //add new topic to list
  }
  return ActionStatusType::STATUS_OK;
}

std::vector<std::string> Broker::listTopics(void) const {
  std::lock_guard<std::mutex> lock(mTopicListMutex);
  std::vector<std::string> keys;
  
  keys.reserve(mTopicList.size());

  for (const auto& pair : mTopicList) {
      keys.push_back(pair.first);
  }
  return keys;
}

T_TopicStatus Broker::getTopicStatus(const std::string &topicName) const {
  std::lock_guard<std::mutex> lock(mTopicListMutex);
  if(isTopicExistent(topicName)) {
    T_TopicStatus topicStatus;
    topicStatus.Timestamp = mTopicList.at(topicName).Request.mTimestamp;
    topicStatus.SubscriberList = mTopicList.at(topicName).SubscriberList;
    return topicStatus;
  }
  return {};
}

void Broker::updateTopic(const RequestType &requestToSubscriber) const {
  //send the request to every subscriber in the subscriber list of the topic using the open tcp connection
}

/* public member functions */
Broker::Broker(const std::string address, const std::string port) : mOwnEndpoint({address, port}), mLogger("log.txt"), mMessageParser() {}

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
