/**
  *************************************************************************************************
  * @file    topic_type.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    05-June-2023
  * @brief   
  *************************************************************************************************
  */

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
typedef struct {
  std::string       TopicName;
  RequestType       Request;
  T_SubscriberList  SubscriberList;
} T_Topic;  /*!< type definition for topic */
