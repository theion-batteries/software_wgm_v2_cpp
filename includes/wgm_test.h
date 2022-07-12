/**
 * @file wgm_test.h
 * @author sami dhiab (sami@theion.de)
 * @brief faking a hardware device
 * @version 0.1
 * @date 2022-07-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <iostream>
#include "feedback_management.h"

namespace wgm_test
{
     class hw_mocking
    {
        private:
            wgm_feedbacks::hw_feedback hw_feed;
    
        public:
            wgm_feedbacks::enum_hw_feedback hw_run ();
    
    };
    
    
      wgm_feedbacks::enum_hw_feedback hw_mocking::hw_run ()
    {
          return wgm_feedbacks::enum_hw_feedback::hw_success;
    }
    
    
}