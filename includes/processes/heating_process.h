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
 
     /****************** interface heating process *****************/
    class Iheating_process : public Iprocess_manager
    {
    public:
        Iheating_process();
        virtual ~Iheating_process();
        virtual wgm_feedbacks::enum_proc_feedback start_process() = 0;
        virtual wgm_feedbacks::enum_proc_feedback stop_process() = 0;
        virtual std::string get_name() = 0;
        virtual bool is_proc_success() = 0;
        virtual int get_id() = 0;
        virtual long long get_elapsed_time()=0;
        virtual sulfur_heating_system::Isulfur_heating_controller* get_sys_ptr() = 0;

    };
    /************* implementation heating process ************/
    class heating_process : public Iheating_process
    {
    private:
        sulfur_heating_system::Isulfur_heating_controller* heating_sys;
        wgm_monitoring::Itime_monitor* process_timer;
        wgm_monitoring::Iheat_monitor* process_temp_monitor;
        wgm_feedbacks::proc_feedback process_feedback;
        std::string process_name = "Heating";
        int proc_id = 0;

    public:
        heating_process();
        virtual ~heating_process();
         wgm_feedbacks::enum_proc_feedback start_process() override;
         wgm_feedbacks::enum_proc_feedback stop_process() override;
         std::string get_name() override;
         bool is_proc_success() override;
         long long get_elapsed_time() override;
         sulfur_heating_system::Isulfur_heating_controller* get_sys_ptr() override;
        virtual int get_id(){return proc_id;};

    };
    

}


