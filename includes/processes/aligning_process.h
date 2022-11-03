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
    
    /****************** interface cnt alignment process*******************/
    class Ialigning_process : public Iprocesses_managment
    {
    public:
        Ialigning_process();
        virtual ~Ialigning_process();
        virtual void start_process() = 0;
        virtual void stop_process() = 0;
        virtual std::string get_name() = 0;
        virtual bool is_proc_success() = 0;
    };
    /******************* implementation cnt alignment process ***************/
    class aligning_process : public Ialigning_process
    {
    private:
        wgm_feedbacks::proc_feedback process_feedback;
        wgm_monitoring::Itime_monitor* process_timer;
        wgm_monitoring::Ivoltage_monitor* process_volt_monitor;
        wgm_monitoring::Icurrent_monitor* process_curr_monitor;
        cnt_alignment_system::Icnt_aligning_controller* aligning_sys;
        std::string process_name = "aligning process";

    public:
        aligning_process();
        virtual ~aligning_process();
        virtual void start_process();
        virtual void stop_process();
        virtual std::string get_name();
        virtual bool is_proc_success();

    };

}


