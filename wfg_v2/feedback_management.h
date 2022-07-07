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
    enum class enum_hw_feedback
    {
        hw_success = 3,
        hw_error = -2
    };
    /*********** feedback classes **************/
    /********** processes feedbacks ************/
    class proc_feedback
    {
        public:
            void report_success ();
            void report_error ();
    };
    void proc_feedback::report_success ()
    {
                        
    }
    void proc_feedback::report_error ()
    {
                        
    }
    /**************** system feedback ***************/
    class sys_feedback
    {
        private:
            sw_communication sw_com_handler;    
        public:
            void report_success ();
            void report_error ();
    };
    void sys_feedback::report_success ()
    {
            sw_com_handler.emit(enum_sys_feedback::sys_success);            
    }
    void sys_feedback::report_error ()
    {
            sw_com_handler.emit(enum_sys_feedback::sys_success);            
    }
    /************* software communication ***********/
    class sw_communication
    {
        
        public:
        template<typename T> void emit (T cmd);
        template<typename T> void parse (T data);
    };
    template<typename T> void sw_communication::emit (T cmd)
    {
                        
    }
    template<typename T> void sw_communication::parse (T data)
    {
                        
    }
    class internal_comuunication
    {
    };  
/*********** hardware specific implementation *************/
    /************** hardware feedback ************/
    class hw_feedback
    {
        private:
            hw_communication hw_com_handler;
    
        public:
            void report_success ();
            void report_error ();
    
    };
      void hw_feedback::report_success ()
    {
            hw_com_handler.emit(enum_hw_feedback::hw_success);   
    }
    
    void hw_feedback::report_error ()
    {
            hw_com_handler.emit(enum_hw_feedback::hw_error);            
    }
    /************ hardware communication *****/
    class hw_communication
    {
        public:
            template<typename T> void emit (T response);
    };
      template<typename T> void hw_communication::emit (T response)
    {
                        
    }
}


