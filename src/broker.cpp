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
Broker::Broker(const T_TopicList& topicList) : mTopicList(topicList) {}

std::vector<std::string> Broker::listTopics() const {
  std::vector<std::string> keys;
  keys.reserve(mTopicList.size());

  for (const auto& pair : mTopicList) {
      keys.push_back(pair.first);
  }

  return keys;
}