/**
  *************************************************************************************************
  * @file    subscriber.cpp
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    29-May-2023
  * @brief   Implementation for class Subscriber
  *************************************************************************************************
  */

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "subscriber.h"

/**************************************************************************************************
 * Public - Class implementation
 *************************************************************************************************/

/* private/protected member functions */
ACTION_STATUS_ENUM Subscriber::unsubscribeTopic([[maybe_unused]]std::string topicName) const {
  T_Request requestUnsubscribeTopic = {
    ACTION_ENUM::UNSUBSCRIBE_TOPIC,
    {{"topicName", topicName}},
    getTimestamp()
  };
  
  if(0U == sendRequest(requestUnsubscribeTopic)) {
    return ACTION_STATUS_ENUM::STATUS_OK;
  } else {
    return ACTION_STATUS_ENUM::INTERNAL_ERROR;
  }
}

T_TopicStatus Subscriber::getTopicStatus([[maybe_unused]]std::string topicName) const {

}

void Subscriber::updateTopic(std::string topicName, std::string &msg, std::time_t timestamp) const {
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

std::time_t Subscriber::getTimestamp(void) const {
  return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

/* public member functions */
Subscriber::Subscriber([[maybe_unused]]std::string address, [[maybe_unused]]int port) {

}

Subscriber::~Subscriber() {}

ACTION_STATUS_ENUM Subscriber::subscribeTopic([[maybe_unused]]std::string topicName) const {
  
}

std::vector<std::string>* Subscriber::listTopics(void) const {

}

int Subscriber::messageHandler(void) {
  
}