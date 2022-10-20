/**
 * @file feedback_management.cpp
 * @author sami dhiab (sami@theion.de)
 * @brief feedback managment file
 * @version 0.1
 * @date 2022-07-07
 * @copyright Copyright (c) 2022
 */
#include "feedback_management.h"

void wgm_feedbacks::hw_feedback::report_feedback(enum_hw_feedback& feedback)
{
  if (feedback == enum_hw_feedback::hw_success) hw_feed_val = enum_hw_feedback::hw_success;
  else hw_feed_val = enum_hw_feedback::hw_error;
}

bool wgm_feedbacks::proc_feedback::report_feedback()
{
  
  if (proc_feed_val == enum_proc_feedback::proc_success)
  {
    std::cout<< "--------- process success, executing next process ---------- "<< std::endl;
    return true;
  } 
  std::cout<< "process failed "<< std::endl;
  return false;
}
void wgm_feedbacks::proc_feedback::setFeedback(enum_proc_feedback feedback)
{
      proc_feed_val=feedback;
}
