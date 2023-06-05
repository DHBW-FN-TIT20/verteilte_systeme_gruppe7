/**************************************************************************************************
  * @file    subscriber.cpp
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    29-May-2023
  * @brief   Implementation for class Subscriber
  ************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "subscriber.h"

/**************************************************************************************************
 * Public - Class implementation
 *************************************************************************************************/

/* private/protected member functions */
void Subscriber::unsubscribeTopic(std::string topicName) {
  std::string logEntry;
  const RequestType requestUnsubscribeTopic(ActionType::UNSUBSCRIBE_TOPIC, {{"topicName", topicName}});
  //const std::string response = sendRequest(requestUnsubscribeTopic);

  //if(!(response == "")) {
  //  std::cout << response << std::endl;
  //  logEntry = "Subscriber on port: " + std::to_string(mPort) + ": unsubscribed from topic >>" + topicName + "<<";
  //  mLogger.addLogEntry(logEntry);
  //  exit(EXIT_FAILURE);
  //} else {
  //  std::cout << "Successfully unsubscribed from topic >>" << topicName << "<<" << std::endl;
  //  logEntry = "Subscriber on port: " + std::to_string(mPort) + ": unsubscribed from topic >>" + topicName + "<<";
  //  mLogger.addLogEntry(logEntry);
  //}
}

void Subscriber::updateTopic(std::string topicName, std::string &msg, std::time_t timestamp) {
  std::tm* timeinfo = std::localtime(&timestamp);

  /* print timestamp in format: DD.MM.YY HH:MM:SS: */
  std::cout << std::setfill('0');
  std::cout << std::setw(2) << timeinfo->tm_mday << ".";
  std::cout << std::setw(2) << (timeinfo->tm_mon + 1) << ".";
  std::cout << (timeinfo->tm_year + 1900) << " ";
  std::cout << std::setw(2) << timeinfo->tm_hour << ":";
  std::cout << std::setw(2) << timeinfo->tm_min << ":";
  std::cout << std::setw(2) << timeinfo->tm_sec << ": ";

  /* print topic name */
  std::cout << topicName << ": ";

  /* print topic message */
  std::cout << ">>" << msg << "<<" << std::endl;
}

//std::string Subscriber::sendRequest(const RequestType& request) const {
//  return "";
//}

/* public member functions */
Subscriber::Subscriber(std::string address, int port) : mAddress(address), mPort(port), mMessageParser(), mLogger(LOG_FILE_NAME) {}

Subscriber::~Subscriber() {}

void Subscriber::subscribeTopic(std::string topicName) {
  std::string logEntry;
  const RequestType requestSubscribeTopic(ActionType::SUBSCRIBE_TOPIC, {{"topicName", topicName}});

  //const std::string response = sendRequest(requestSubscribeTopic);

  //if(response == "") {
  //  std::cout << response << std::endl;
  //  logEntry = "Subscriber on port: " + std::to_string(mPort) + ": " + response;
  //  mLogger.addLogEntry(logEntry);
  //  exit(EXIT_FAILURE);
  //} else {
  //  std::cout << "Successfully subscribed to topic >>" << topicName << "<<" << std::endl;
  //  logEntry = "Subscriber on port: " + std::to_string(mPort) + ": subscribed to topic >>" + topicName + "<<";
  //  mLogger.addLogEntry(logEntry);
  //}
}

void Subscriber::listTopics(void) {
  RequestType requestListTopics(ActionType::LIST_TOPICS, {});

  //const std::string response = sendRequest(requestListTopics);

}

int Subscriber::messageHandler(void) {
  return 0U;
}