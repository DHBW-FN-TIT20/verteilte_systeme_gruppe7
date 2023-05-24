/**
  *************************************************************************************************
  * @file    T_TopicSubscriberList.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    24-May-2023
  * @brief   
  *************************************************************************************************
  */

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <map>
#include <string>
#include "T_SubscriberList.h"

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
typedef std::map<std::string, T_SubscriberList>   T_TopicSubscriberList;    /*!< type definition for list of topics with all their respective subscribers */
