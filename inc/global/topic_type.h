<<<<<<< HEAD
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
=======
/**
  *************************************************************************************************
<<<<<<<< HEAD:inc/global/topic_list_type.h
  * @file    topic_list_type.h
========
  * @file    topic_type.h
>>>>>>>> 2381ea8 (:label: update file names to match naming convention):inc/global/topic_type.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    05-June-2023
  * @brief   
  *************************************************************************************************
  */
>>>>>>> 2381ea8 (:label: update file names to match naming convention)

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
<<<<<<< HEAD
#include <string>
<<<<<<<< HEAD:inc/global/topic_type.h
#include "request_type.h"
========
>>>>>>>> 2381ea8 (:label: update file names to match naming convention):inc/global/topic_subscriber_list_type.h
#include "subscriber_list_type.h"
=======
#include <map>
#include <string>
#include "topic_type.h"
>>>>>>> 2381ea8 (:label: update file names to match naming convention)

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
<<<<<<< HEAD
struct T_Topic {
  std::string       TopicName;
  RequestType       Request;
  T_SubscriberList  SubscriberList;
};  /*!< type definition for topic */
=======
typedef std::map<std::string, T_Topic>  T_TopicList;    /*!< type definition for list of topics */
>>>>>>> 2381ea8 (:label: update file names to match naming convention)
