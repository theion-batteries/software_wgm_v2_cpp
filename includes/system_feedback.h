/**
 * @file feedback_management.h
 * @author sami dhiab (sami@theion.de)
 * @brief feedback managment file
 * @version 0.1
 * @date 2022-07-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <iostream>
#include "subsystem_feedback.h"

namespace wgm_feedbacks
{
    /********* enumeration classes ***********/
 
    enum class enum_sys_feedback
    {
        sys_success = 2,
        sys_error = -1
    };
 
    /*********** feedback classes *************/
  
   
     class sys_feedback
    {
        private:
            enum_sys_feedback sys_feed_val;
            sub_sys_feedback* sub_feed;
    
    };
  

}


