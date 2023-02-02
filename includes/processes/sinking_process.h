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

#include "Iprocess_manager.h"


namespace wgm_processes
{
  
    /******************* interface wafer insertion process***************/
    class Isinking_process : public Iprocess_manager
    {
    public:
        Isinking_process();
        virtual ~Isinking_process();
        virtual wgm_feedbacks::enum_proc_feedback start_process() = 0;
        virtual void stop_process() = 0;
        virtual std::string get_name() = 0;
        virtual bool is_proc_success() = 0;
        virtual wafer_holder_motion_system::Iwafer_motion_controller* get_sys_ptr() = 0;
        virtual long long get_elapsed_time()=0;
        virtual int get_id() = 0;

    };
    /**************** implementation wafer insertion process ************/
    class sinking_process : public Isinking_process
    {
    private:
        wgm_feedbacks::proc_feedback process_feedback;
        wgm_monitoring::Itime_monitor* process_timer;
       wafer_holder_motion_system::Iwafer_motion_controller* sinking_sys;
        wgm_monitoring::Idistance_monitor* process_dist_monitor;
        std::string process_name = "Sinking";
        int proc_id = 1;

    public:
        sinking_process();
        virtual ~sinking_process();
        virtual wgm_feedbacks::enum_proc_feedback start_process();
        virtual void stop_process();
        virtual std::string get_name();
        virtual bool is_proc_success(); 
        virtual wafer_holder_motion_system::Iwafer_motion_controller* get_sys_ptr();
        virtual long long get_elapsed_time();
        virtual int get_id(){return proc_id;};

    };
 
  
}


