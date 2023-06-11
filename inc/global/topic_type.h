/**************************************************************************************************
  * @file    topic_type.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    05-June-2023
  * @brief   
  ************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <string> 
#include "request_type.h"
#include "subscriber_list_type.h"

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
struct T_Topic {
  std::string       TopicName;
  RequestType       Request;
  T_SubscriberList  SubscriberList;
};  /*!< type definition for topic */
