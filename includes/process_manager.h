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

#include <vector>
#include "wgm_monitoring.h"
#include "feedback_management.h"


namespace wgm_processes
{
    /************* interface process management **********/
    /**
     * @brief interface process managemnt for user
     * do not modify!
     */
    class Iprocesses_managment
    {
    public:
        Iprocesses_managment();
        virtual void start_process() = 0;
        virtual void stop_process() = 0;
        virtual void add_process_to_scheduler(Iprocesses_managment* process);

        virtual void delete_last_process_from_scheduler();

        virtual void stop_all();

        virtual void start_all();

        virtual std::string get_name() = 0;
        virtual bool is_proc_success() = 0;
        virtual ~Iprocesses_managment();

    };
    /************* processes interface and implementation**********/
    /**
     * @brief add system processes as following:
     * create interface and inherit from Iprocesses_managment.
     * create abstract methods start_process and stop_process
     * create the implementation class, redefine these methods
     * create the actual process system inside constructor
     * delete it in the destructor (virtual)
     */
     /****************** interface heating process *****************/
    class Iheating_process : public Iprocesses_managment
    {
    public:
        Iheating_process();
        virtual ~Iheating_process();
        virtual void start_process() = 0;
        virtual void stop_process() = 0;
        virtual std::string get_name() = 0;
        virtual bool is_proc_success() = 0;
    };
    /************* implementation heating process ************/
    class heating_process : public Iheating_process
    {
    private:
        sulfur_heating_system::Isulfur_heating_controller* heating_sys;
        wgm_monitoring::Itime_monitor* process_timer;
        wgm_monitoring::Iheat_monitor* process_temp_monitor;
        wgm_feedbacks::proc_feedback process_feedback;
        std::string process_name = "heating process";
    public:
        heating_process();
        virtual ~heating_process();
        virtual void start_process();
        virtual void stop_process();
        virtual std::string get_name();
        virtual bool is_proc_success();
    };
    /******************* interface wafer insertion process***************/
    class Isinking_process : public Iprocesses_managment
    {
    public:
        Isinking_process();
        virtual ~Isinking_process();
        virtual void start_process() = 0;
        virtual void stop_process() = 0;
        virtual std::string get_name() = 0;
        virtual bool is_proc_success() = 0;
        virtual wafer_holder_motion_system::Iwafer_motion_controller* get_sys_obj() = 0;
    };
    /**************** implementation wafer insertion process ************/
    class sinking_process : public Isinking_process
    {
    private:
        wgm_feedbacks::proc_feedback process_feedback;
        wgm_monitoring::Itime_monitor* process_timer;
       wafer_holder_motion_system::Iwafer_motion_controller* sinking_sys;
        wgm_monitoring::Idistance_monitor* process_dist_monitor;
        std::string process_name = "sinking process";

    public:
        sinking_process();
        virtual ~sinking_process();
        virtual void start_process();
        virtual void stop_process();
        virtual std::string get_name();
        virtual bool is_proc_success(); 
        virtual wafer_holder_motion_system::Iwafer_motion_controller* get_sys_obj();

    };
 
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
    /******************** implementation process management ************/
    /**
     * @brief implementation process managemnt
     * add new process inside constructor
     * later will be possible to add new processes from interface method
     * add and delete from delete method
     */
    class process_management : public Iprocesses_managment
    {
    private:
        const std::string process_name = "process scheduler";
        std::vector<Iprocesses_managment*> processesvector;
        wgm_feedbacks::proc_feedback process_feedback;
    public:
        process_management() ;
        // clean up destruction
        virtual ~process_management() ;
        
        virtual void start_process();
        virtual void stop_process();
        virtual void start_all();
        virtual void stop_all();
        virtual void add_process_to_scheduler(Iprocesses_managment* process);
        virtual void delete_last_process_from_scheduler();
        virtual std::string get_name() ;
        virtual bool is_proc_success() ;

    };

}


