/**************************************************************************************************
 * @file    broker.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    15-June-2023
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
        mTopicList.at(topicName).StopHeartbeat = true;
        mTopicList.at(topicName).HeartbeatCondition.notify_one();
        mTopicList.at(topicName).HeartbeatThread.join();
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
    mTopicList.at(topicName).HeartbeatCondition.notify_one();
  } else {
    T_Topic &newTopic = mTopicList[topicName];
    newTopic.TopicName = topicName;
    newTopic.Request = requestFromPublisher;
    newTopic.HeartbeatThread = std::thread([this, &newTopic]() {
      std::unique_lock<std::mutex> lock(newTopic.HeartbeatMutex);
      while(!newTopic.StopHeartbeat) {
        if(newTopic.HeartbeatCondition.wait_for(lock, std::chrono::seconds(HEARTBEAT_DURATION_SEC)) == std::cv_status::timeout) {
          this->updateTopic(newTopic.Request);
        }
      }
    });
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
  return {0, {}};
}

void Broker::updateTopic(RequestType &requestToSubscriber) {
  /* send the request to every subscriber in the subscriber list of the topic using the open tcp connection */
  std::string response = mMessageParser.encodeObject(requestToSubscriber);
  T_SubscriberList currentSubscriberList = mTopicList.at(requestToSubscriber.mParameterList.at("topicName")).SubscriberList;
  bool isHeartbeat = false;

  if(mTopicList.at(requestToSubscriber.mParameterList.at("topicName")).Request == requestToSubscriber) {  //Heartbeat
    if(currentSubscriberList.empty()) {
      std::cout << "Heartbeat: no subscribers found for topic >>" << requestToSubscriber.mParameterList.at("topicName") << "<<" << std::endl;
      return;
    } else {
      std::cout << "Heartbeat for topic >>" << requestToSubscriber.mParameterList.at("topicName") << "<< sent to:" << std::endl;
      isHeartbeat = true;
    }
  } else { //new message
    if(currentSubscriberList.empty()) {
      std::cout << "No subscribers have subscribed to this topit yet" << std::endl;
      return;
    } else {
      std::cout << "Message sent to:" << std::endl;
    }
  }

  for(T_Subscriber subscriber : currentSubscriberList) {
    subscriber.connection->sendResponse(response);
    std::cout << "- " << subscriber.endpoint.toString() << std::endl;
  }
  if(isHeartbeat) std::cout << std::endl;
}


/* public member functions */
Broker::Broker(const std::string address, const std::string port) : mOwnEndpoint({address, port}), mLogger(LOG_FILE_NAME), mMessageParser(), brokerTcpServer(mOwnEndpoint, [this](std::shared_ptr<TcpConnection> conn, const std::string message) {this->messageHandler(conn, message);}) {
  instance = this;
  signal(SIGINT, signalHandler);
  std::cout << "Broker started with endpoint: " << mOwnEndpoint.toString() << ". Accepting clients..." << std::endl;
  mLogger.addLogEntry("Broker started with endpoint: " + mOwnEndpoint.toString());
  brokerTcpServer.run();
}

Broker::Broker() : mOwnEndpoint({"localhost", "8080"}), mLogger(LOG_FILE_NAME), mMessageParser(), brokerTcpServer(mOwnEndpoint, [this](std::shared_ptr<TcpConnection> conn, const std::string message) {this->messageHandler(conn, message);}) {
  instance = this;
}

Broker::~Broker() {
  instance = nullptr;
}

void Broker::messageHandler(std::shared_ptr<TcpConnection> conn, const std::string message) {
  tcp::endpoint endpoint = conn->socket().remote_endpoint();
  T_Endpoint clientEndpoint {
    endpoint.address().to_string(),
    std::to_string(endpoint.port())
  };

  /* display request on terminal */
  std::cout << "\n" << mLogger.getTimestampString() << clientEndpoint.toString() << std::endl << "Client request: " << message << std::endl;
  mLogger.addLogEntry("Broker on " + mOwnEndpoint.toString() + ": received request >>" + message + "<< from " + clientEndpoint.toString());

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
      if(topicStatus = getTopicStatus(request.mParameterList.at("topicName")); topicStatus.Timestamp != 0){
        actionStatus = ActionStatusType::STATUS_OK;
        response = mMessageParser.encodeObject(actionStatus) + ";" + mMessageParser.encodeObject(topicStatus);
      } else {
        actionStatus = ActionStatusType::TOPIC_NON_EXISTENT;
        response = mMessageParser.encodeObject(actionStatus);
      }
      break;
    default:
      actionStatus = ActionStatusType::INTERNAL_ERROR;
      response = mMessageParser.encodeObject(actionStatus);
      break;
  }

  conn->sendResponse(response + "\n");

  std::cout << "Response sent: " << response << std::endl << std::endl;
  mLogger.addLogEntry("Broker on " + mOwnEndpoint.toString() + ": response >>" + response + "<< sent to " + clientEndpoint.toString());
}

void Broker::signalHandler(int signum) {
  if(instance) {
    instance->brokerTcpServer.close();
    std::cout << "TCP-Server closed" << std::endl;
    exit(signum);
  }
}
