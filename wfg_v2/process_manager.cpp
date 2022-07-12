/**
 * @file process_manager.cpp
 * @author sami dhiab
 * @brief
 * @version 0.1
 * @date 2022-07-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "process_manager.h"

namespace wgm_processes
{
    /******* heating process ************/
    heating_process::heating_process()
    {
        heating_sys = new sulfur_heating_system::sulfur_heating_controller();
        process_timer = new wgm_monitoring::time_monitor();
        process_temp_monitor = new wgm_monitoring::heat_monitor(heating_sys);
    }
    heating_process::~heating_process()
    {
        std::cout << "deleting heating process " << std::endl;
        delete heating_sys;
        delete process_timer;
        delete process_temp_monitor;
    }
    void heating_process::start_process()
    {
        std::cout << "execute " << process_name << std::endl;
        // start timer
        process_timer->start_monitoring();
        // start system
        heating_sys->turn_on_heating();
        // report feedback

        // stop timer
        process_timer->stop_monitoring();
        // start temp monitor
        process_temp_monitor->start_monitoring();
    }
    void heating_process::stop_process()
    {
        std::cout << "finish " << process_name << std::endl;
        heating_sys->turn_off_heating();
        process_temp_monitor->stop_monitoring();
    }
    /******* sinking process ************/
    sinking_process::sinking_process() {
            sinking_sys = new wafer_holder_motion_system::wafer_motion_controller();
            process_timer = new wgm_monitoring::time_monitor();
            process_dist_monitor = new wgm_monitoring::distance_monitor(sinking_sys);
        }
    sinking_process::~sinking_process()
        {
            std::cout << "deleting sinking process " << std::endl;
            delete sinking_sys;
            delete process_timer;
            delete process_dist_monitor;
        }
    void sinking_process::start_process()
    {
        std::cout << "execute " << process_name << std::endl;
        process_timer->start_monitoring();
        sinking_sys->set_distance_to_surface_contact(30);
        sinking_sys->insert_wafer_in_ml();
        // feedback
        process_timer->stop_monitoring();
        process_dist_monitor->start_monitoring();
    }
    void sinking_process::stop_process()
    {
        std::cout << "finish " << process_name << std::endl;
        process_dist_monitor->stop_monitoring();
    }
    /******** aligning process **********/
        aligning_process::aligning_process() {
            std::cout << "creating aligning process " << std::endl;
            aligning_sys = new cnt_alignment_system::cnt_aligning_controller();
            process_timer = new wgm_monitoring::time_monitor();
            process_curr_monitor = new wgm_monitoring::current_monitor(aligning_sys);
            process_volt_monitor = new wgm_monitoring::voltage_monitor(aligning_sys);
        }
        aligning_process:: ~aligning_process()
        {
            std::cout << "deleting aligning process " << std::endl;
            delete aligning_sys;
            delete process_timer;
            delete process_curr_monitor;
            delete process_volt_monitor;
        }
    void aligning_process::start_process()
    {
        std::cout << "execute " << process_name << std::endl;
        process_timer->start_monitoring();
        aligning_sys->start_aligning();
        // feedback
        process_timer->stop_monitoring();
        process_curr_monitor->start_monitoring();
        process_volt_monitor->start_monitoring();
    }
    void aligning_process::stop_process()
    {
        std::cout << "finish " << process_name << std::endl;
        aligning_sys->stop_aligning();
        process_curr_monitor->stop_monitoring();
        process_volt_monitor->stop_monitoring();
    }



} // namespace name
