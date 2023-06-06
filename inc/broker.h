/**
 *************************************************************************************************
 * @file    broker.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    06-June-2023
 * @brief   
 *************************************************************************************************
 */

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <vector>
#include "topic_list_type.h"

/*************************************************************************************************
 * Public - Class prototype
 *************************************************************************************************/
class Broker{
  protected:
    T_TopicList mTopicList;
    /**
     * @brief lists all available topics
    */
    std::vector<std::string> listTopics() const;

    Broker(const T_TopicList& topicList);
};