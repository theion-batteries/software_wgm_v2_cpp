/**
 * @file process_manager.h
 * @author sami dhiab (sami@theion.de)
 * @brief process management package
 * @version 0.1
 * @date 2022-07-04
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include "process_manager.h"


namespace wgm_processes
{
  
    /******************* interface wafer extraction process***************/
    class Iextracting_process : public Iprocesses_managment
    {
    public:
        Iextracting_process();
        virtual ~Iextracting_process();
        virtual void start_process() = 0;
        virtual void stop_process() = 0;
        virtual std::string get_name() = 0;
        virtual bool is_proc_success() = 0;
    };
    /**************** implementation wafer extraction process ************/
    class extracting_process : public Iextracting_process
    {
    private:
        wgm_feedbacks::proc_feedback process_feedback;
        wgm_monitoring::Itime_monitor* process_timer;
        wafer_holder_motion_system::Iwafer_motion_controller* extracting_sys;
        std::string process_name = "extracting process";

    public:
        extracting_process(wafer_holder_motion_system::Iwafer_motion_controller* ptrTosys);
        virtual ~extracting_process();
        virtual void start_process();
        virtual void stop_process();
        virtual std::string get_name() ;
        virtual bool is_proc_success() ;

    };
    

}


