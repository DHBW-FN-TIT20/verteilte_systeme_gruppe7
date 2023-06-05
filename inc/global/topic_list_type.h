<<<<<<< HEAD
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
=======
<<<<<<<< HEAD:inc/global/topic_name_list_type.h
/**************************************************************************************************
  * @file    action_enum.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    01-June-2023
========
/**
  *************************************************************************************************
  * @file    topic_list_type.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    05-June-2023
>>>>>>>> 2381ea8 (:label: update file names to match naming convention):inc/global/topic_list_type.h
  * @brief   
  ************************************************************************************************/
>>>>>>> 2381ea8 (:label: update file names to match naming convention)

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
<<<<<<< HEAD
#include <map>
#include <string>
#include "topic_type.h"
=======
#include <vector>
<<<<<<<< HEAD:inc/global/topic_name_list_type.h
#include <string>
========
#include "topic_type.h"
>>>>>>>> 2381ea8 (:label: update file names to match naming convention):inc/global/topic_list_type.h
>>>>>>> 2381ea8 (:label: update file names to match naming convention)

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
<<<<<<< HEAD
typedef std::map<std::string, T_Topic>  T_TopicList;    /*!< type definition for list of topics */
=======
struct T_TopicNameList {
  std::vector<std::string> TopicNameList;

  std::string toString() {
    std::string result;
    for(size_t i = 0; i < TopicNameList.size(); i++) {
      result += TopicNameList.at(i);
      result += (i != TopicNameList.size() - 1) ? ", " : ";";
    }
    return result;
  }
};
>>>>>>> 2381ea8 (:label: update file names to match naming convention)
