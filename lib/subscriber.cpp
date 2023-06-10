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

void Subscriber::updateTopic(const std::string &topicName, const std::string &msg, const std::time_t &timestamp) {
  std::cout << mLogger.getTimestampString() << "received topic >>" << topicName << "<<" << std::endl;
  std::cout << "> Topic message: " << msg << std::endl;
  std::cout << "> Timestamp: " << timestamp << std::endl << std::endl;
}

/* public member functions */
Subscriber::Subscriber(const std::string &address, const std::string &port) : mServerEndpoint(T_Endpoint{address, port}), mMessageParser(), mLogger(LOG_FILE_NAME), mTcpClient(std::make_shared<TcpClient>(mServerEndpoint, messageHandler)), mOwnEndpoint(T_Endpoint{mTcpClient->socket().local_endpoint().address().to_string(), std::to_string(mTcpClient->socket().local_endpoint().port())}) {
  instance = this;
  signal(SIGINT, signalHandler);
  mTcpClient->run();
}

Subscriber::~Subscriber() {
  instance = nullptr;
}

void Subscriber::subscribeTopic(const std::string &topicName) {
  RequestType request(ActionType::SUBSCRIBE_TOPIC, {{"topicName", topicName}});

  (void)network::sendRequestWithoutResponse(mTcpClient, request);

  /* successfully subscribed */
  std::cout << "Successfully subscribed to topic >>" << topicName << "<<" << std::endl;
  mLogger.addLogEntry(mOwnEndpoint.toString() + ": subscribed to topic >>" + topicName + "<<");
}

void Subscriber::listTopics(void) {
  RequestType request(ActionType::LIST_TOPICS, {});

  std::vector<std::string> topicList = network::sendRequest<std::vector<std::string>>(mTcpClient, request);

  /* topic list received */
  if(topicList.size() > 0) {
    std::cout << "Existing topics:" << std::endl;
    for(auto& topic : topicList) {
      std::cout << "- " << topic << std::endl;
    }
    std::cout << std::endl;
  } else {
    std::cout << "No topics exist. You can publish one and try again." << std::endl;
  }
  
}

void Subscriber::messageHandler(const std::string message) {
  /* parse message */
  RequestType request = mMessageParser.decodeObject<RequestType>(message);

  /* extract relevant information from response */
  const std::string topicName = request.mParameterList.at("topicName");
  const std::string topicMessage = request.mParameterList.at("message");
  std::time_t topicTimestamp;
  try {
    topicTimestamp = static_cast<std::time_t>(std::stol(request.mParameterList.at("timestamp")));
  } catch(const std::invalid_argument &ia) {
    std::cerr << "Invalid timestamp: " << ia.what() << std::endl;
  } catch(const std::out_of_range &oor) {
    std::cerr << "Timestamp out of range: " << oor.what() << std::endl;
  }

  /* update topic member function call */
  updateTopic(topicName, topicMessage, topicTimestamp);  
}

void Subscriber::signalHandler(int signum) {
  if(instance) {
    instance->mTcpClient->close();
    std::cout << "TCP-Client closed" << std::endl;
    exit(signum);
  }
}
