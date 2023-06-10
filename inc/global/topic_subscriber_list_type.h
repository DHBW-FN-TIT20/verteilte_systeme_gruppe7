/**************************************************************************************************
  * @file    topic_subscriber_list_type.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    05-June-2023
  * @brief   
  ************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <map>
#include <string>
#include "subscriber_list_type.h"

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
typedef std::map<std::string, T_SubscriberList>   T_TopicSubscriberList;    /*!< type definition for list of topics with all their respective subscribers */
