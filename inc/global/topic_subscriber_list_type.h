<<<<<<<< HEAD:inc/global/topic_type.h
/**************************************************************************************************
  * @file    topic_type.h
========
/**
  *************************************************************************************************
  * @file    topic_subscriber_list_type.h
>>>>>>>> 2381ea8 (:label: update file names to match naming convention):inc/global/topic_subscriber_list_type.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    05-June-2023
  * @brief   
  ************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <string>
<<<<<<<< HEAD:inc/global/topic_type.h
#include "request_type.h"
========
>>>>>>>> 2381ea8 (:label: update file names to match naming convention):inc/global/topic_subscriber_list_type.h
#include "subscriber_list_type.h"

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
struct T_Topic {
  std::string       TopicName;
  RequestType       Request;
  T_SubscriberList  SubscriberList;
};  /*!< type definition for topic */
