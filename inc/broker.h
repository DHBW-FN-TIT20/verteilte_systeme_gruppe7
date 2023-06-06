/**************************************************************************************************
 * @file    broker.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    06-June-2023
 * @brief   Prototype for class Broker
 *************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
/* C++ Libs */
#include <vector>

/* Own Libs / datatypes */
#include "topic_list_type.h"

/**************************************************************************************************
 * Public - Class prototype
 *************************************************************************************************/
class Broker{
  protected:
    T_TopicList mTopicList;

    /**
     * @brief lists all available topics
    */
    std::vector<std::string> listTopics() const;


  public:
    Broker(const T_TopicList& topicList);
};
