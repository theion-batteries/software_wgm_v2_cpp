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
#include "system_feedback.h"
namespace wgm_feedbacks
{
    /********* enumeration classes ***********/
    enum class enum_proc_feedback
    {
        proc_success = 1,
        proc_error = 0
    };
   
    /*********** feedback classes *************/
  
     class proc_feedback
    {
        private:
            enum_proc_feedback proc_feed_val;
            sys_feedback* sys_feed;
        public:
          inline  bool report_feedback();
          inline  void setFeedback(enum_proc_feedback feedback);
    };

}


bool wgm_feedbacks::proc_feedback::report_feedback()
{
  if (proc_feed_val == enum_proc_feedback::proc_success)
  {
    std::cout<< "--------- process succeded ---------- "<< std::endl;
    return true;
  } 
  std::cout<< "process failed "<< std::endl;
  return false;
}
void wgm_feedbacks::proc_feedback::setFeedback(enum_proc_feedback feedback)
{
  proc_feed_val=feedback;
}
