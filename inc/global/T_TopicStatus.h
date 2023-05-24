/**
  *************************************************************************************************
  * @file    T_TopicStatus.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    24-May-2023
  * @brief   
  *************************************************************************************************
  */

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include "T_SubscriberList.h"

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
typedef struct {
  bool                IsTopicExistent;
  int32_t             Timestamp;
  T_SubscriberList    SubscriberList_t;
} T_TopicStatus;
