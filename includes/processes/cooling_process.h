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

#include "process_manager.h"


namespace wgm_processes
{
  
    /****************** interface cooling process *******************/
    class Icooling_process : public Iprocesses_managment
    {
    public:
        Icooling_process();
        virtual ~Icooling_process();
        virtual void start_process() = 0;
        virtual void stop_process() = 0;
        virtual std::string get_name() = 0;
        virtual bool is_proc_success() = 0;
    };
    /******************* implementation cooling process ***************/
    class cooling_process : public Icooling_process
    {
    private:
        wgm_feedbacks::proc_feedback process_feedback;
        wgm_monitoring::Itime_monitor* process_timer;
        wafer_cooling_system::Icooling_controller* cooling_sys;
        std::string process_name = "cooling process";

    public:
        cooling_process() ;
        virtual ~cooling_process();
        virtual void start_process();
        virtual void stop_process();
        virtual std::string get_name() ;
        virtual bool is_proc_success() ;
    };
 
}


