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
#include <iostream>
#pragma once

namespace wgm_feedbacks
{
    /********* enumeration classes ***********/
    enum class enum_proc_feedback
    {
        proc_success = 1,
        proc_error = 0
    };
    enum class enum_sys_feedback
    {
        sys_success = 2,
        sys_error = -1
    };
    enum class enum_sub_sys_feedback
    {
        sys_success = 3,
        sys_error = -2
    };
    enum class enum_hw_feedback
    {
        hw_success = 4,
        hw_error = -3
    };
    /*********** hardware specific implementation *************/
        /************** hardware feedback ************/
     class hw_feedback
    {
        private:
            enum_hw_feedback hw_feed_val;
    
        public:
            void report_feedback (enum_hw_feedback& feedback);
    };
     class sub_sys_feedback
    {
        private:
            enum_sub_sys_feedback sub_sys_feed_val;
            hw_feedback* hw_feed;
    };
     class sys_feedback
    {
        private:
            enum_sys_feedback sys_feed_val;
            sub_sys_feedback* sub_feed;
    
    };
     class proc_feedback
    {
        private:
            enum_proc_feedback proc_feed_val;
            sys_feedback* sys_feed;
        public:
            bool report_feedback();
    };

}


