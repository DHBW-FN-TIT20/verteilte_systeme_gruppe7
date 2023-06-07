/**************************************************************************************************
 * @file    broker.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
<<<<<<< HEAD
 * @date    08-June-2023
=======
 * @date    07-June-2023
>>>>>>> 9631a70 (:truck: move class implementations to lib folder)
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
<<<<<<< HEAD
bool Broker::isTopicExistent(const std::string &topicName) const {
  return mTopicList.count(topicName) > 0U;
}

bool Broker::hasSubscriber(const std::string &topicName, const T_Subscriber &subscriber) const {
=======
bool Broker::isTopicExistent(std::string &topicName) const {
  return mTopicList.count(topicName) > 0U;
}

bool Broker::hasSubscriber(std::string &topicName, T_Endpoint &subscriber) const {
>>>>>>> 9631a70 (:truck: move class implementations to lib folder)
  T_SubscriberList subscriberList = mTopicList.at(topicName).SubscriberList;
  return std::find(subscriberList.begin(), subscriberList.end(), subscriber) != subscriberList.end();
}

<<<<<<< HEAD
ActionStatusType Broker::subscribeTopic(const std::string &topicName, const T_Subscriber &subscriber) {
  std::lock_guard<std::mutex> lock(mTopicListMutex);

  if(isTopicExistent(topicName)) {
    if(!hasSubscriber(topicName, subscriber)) {
      mTopicList.at(topicName).SubscriberList.push_back(subscriber);
    } else {
      return ActionStatusType::INTERNAL_ERROR;  //subscriber already subscribed to this topic
    }
=======
ActionStatusType Broker::subscribeTopic(std::string topicName, T_Endpoint subscriber) {
  std::lock_guard<std::mutex> lock(mTopicListMutex);

  if(isTopicExistent(topicName)) {
    mTopicList.at(topicName).SubscriberList.push_back(subscriber);
>>>>>>> 9631a70 (:truck: move class implementations to lib folder)
  } else {
    return ActionStatusType::TOPIC_NON_EXISTENT;
  }
  return ActionStatusType::STATUS_OK;
}

<<<<<<< HEAD
ActionStatusType Broker::unsubscribeTopic(const std::string &topicName, const T_Subscriber &subscriber) {
=======
ActionStatusType Broker::unsubscribeTopic(std::string topicName, T_Endpoint subscriber) {
>>>>>>> 9631a70 (:truck: move class implementations to lib folder)
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

<<<<<<< HEAD
ActionStatusType Broker::publishTopic(RequestType &requestFromPublisher) {
  std::lock_guard<std::mutex> lock(mTopicListMutex);

  std::string topicName = requestFromPublisher.mParameterList.at("topicName");
  if(isTopicExistent(topicName)) {
    mTopicList.at(topicName).Request = requestFromPublisher;  //update request of topic in topic list
    requestFromPublisher.mAction = ActionType::UPDATE_TOPIC;  //change action to udpate topic
    updateTopic(requestFromPublisher);  //publish updated topic
  } else {
    mTopicList.insert(std::pair<std::string, T_Topic>(topicName, {topicName, requestFromPublisher, {}}));   //add new topic to list
=======
ActionStatusType Broker::publishTopic(std::string topicName, [[maybe_unused]]std::string &message) const {
  std::lock_guard<std::mutex> lock(mTopicListMutex);

  if(isTopicExistent(topicName)) {
    //generate timestamp and call update topic(), then return success
  } else {
    return ActionStatusType::TOPIC_NON_EXISTENT;
>>>>>>> 9631a70 (:truck: move class implementations to lib folder)
  }
  return ActionStatusType::STATUS_OK;
}

<<<<<<< HEAD
std::vector<std::string> Broker::listTopics(void) const {
=======
std::vector<std::string> Broker::listTopics() const {
>>>>>>> 9631a70 (:truck: move class implementations to lib folder)
  std::lock_guard<std::mutex> lock(mTopicListMutex);
  std::vector<std::string> keys;
  
  keys.reserve(mTopicList.size());

  for (const auto& pair : mTopicList) {
      keys.push_back(pair.first);
  }
  return keys;
}

<<<<<<< HEAD
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

void Broker::updateTopic(RequestType &requestToSubscriber) {
  //send the request to every subscriber in the subscriber list of the topic using the open tcp connection
  std::string response = mMessageParser.encodeObject(requestToSubscriber);

  for(T_Subscriber subscriber : mTopicList.at(requestToSubscriber.mParameterList.at("topicName")).SubscriberList) {
    subscriber.connection->sendResponse(response);
  }
}


/* public member functions */
Broker::Broker(const std::string address, const std::string port) : mOwnEndpoint({address, port}), mLogger("log.txt"), mMessageParser(), brokerTcpServer(mOwnEndpoint, [this](std::shared_ptr<TcpConnection> conn, const std::string message) {this->messageHandler(conn, message);}) {
  instance = this;
  signal(SIGINT, signalHandler);
  brokerTcpServer.run();
}

Broker::Broker() : mOwnEndpoint({"localhost", "8080"}), mLogger("log.txt"), mMessageParser(), brokerTcpServer(mOwnEndpoint, [this](std::shared_ptr<TcpConnection> conn, const std::string message) {this->messageHandler(conn, message);}) {
  instance = this;
}

Broker::~Broker(void) {
  instance = nullptr;
}

void Broker::messageHandler(std::shared_ptr<TcpConnection> conn, const std::string message) {
=======
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
>>>>>>> 9631a70 (:truck: move class implementations to lib folder)
  tcp::endpoint endpoint = conn->socket().remote_endpoint();
  T_Endpoint clientEndpoint {
    endpoint.address().to_string(),
    std::to_string(endpoint.port())
  };

<<<<<<< HEAD
  /* display request on terminal */
  std::cout << mLogger.getTimestampString() << clientEndpoint.toString() << " >>" << message << "<<" << std::endl;

  /* parse message */
  RequestType request = mMessageParser.decodeObject<RequestType>(message);

  /* decide which function to call based on the request */
  ActionStatusType actionStatus;
  std::vector<std::string> topicList;
  T_TopicStatus topicStatus;
  std::string response;

  switch(request.mAction) {
    case ActionType::SUBSCRIBE_TOPIC:
      actionStatus = subscribeTopic(request.mParameterList.at("topicName"), {clientEndpoint, conn});
      response = mMessageParser.encodeObject(actionStatus);
      break;
    case ActionType::UNSUBSCRIBE_TOPIC:
      actionStatus = unsubscribeTopic(request.mParameterList.at("topicName"), {clientEndpoint, conn});
      response = mMessageParser.encodeObject(actionStatus);
      break;
    case ActionType::PUBLISH_TOPIC:
      actionStatus = publishTopic(request);
      response = mMessageParser.encodeObject(actionStatus);
      break;
    case ActionType::LIST_TOPICS:
      topicList = listTopics();
      actionStatus = ActionStatusType::STATUS_OK;
      response = mMessageParser.encodeObject(actionStatus) + ";" + mMessageParser.encodeObject(topicList);
      break;
    case ActionType::GET_TOPIC_STATUS:
      topicStatus = getTopicStatus(request.mParameterList.at("topicName"));
      actionStatus = ActionStatusType::STATUS_OK;
      response = mMessageParser.encodeObject(actionStatus) + ";" + mMessageParser.encodeObject(topicStatus);
      break;
    default:
      actionStatus = ActionStatusType::INTERNAL_ERROR;
      response = mMessageParser.encodeObject(actionStatus);
      break;
  }

  if(request.mAction != ActionType::SUBSCRIBE_TOPIC) {
    response += "\n";
  }
  
  conn->sendResponse(response);

  if(request.mAction != ActionType::SUBSCRIBE_TOPIC) {
    std::cout << "Response sent: " << response << std::endl;
  } else {
    std::cout << "Response sent: " << response << std::endl << std::endl;
  }
}

void Broker::signalHandler(int signum) {
  if(instance) {
    instance->brokerTcpServer.close();
    std::cout << "TCP-Server closed" << std::endl;
    exit(signum);
  }
=======
  //parse message

  //decide which function to call based on the message's body

  //call the function

  //encode the return value of the function; add the action status; add delimiter and "\n" at the end of the response message

  //send the response back to the client
>>>>>>> 9631a70 (:truck: move class implementations to lib folder)
}
