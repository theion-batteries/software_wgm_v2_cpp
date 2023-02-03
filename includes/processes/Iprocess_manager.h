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
#include <vector>
#include "wgm_monitoring.h"
#include "process_feedback.h"
#include <algorithm> 
#include <functional>
using enum wgm_feedbacks::enum_sub_sys_feedback;
using enum wgm_feedbacks::enum_proc_feedback;

namespace wgm_processes
{
    /************* interface process management **********/
    /**
     * @brief interface process managemnt for user
     * do not modify!
     */
    class Iprocess_manager
    {
    public:
        Iprocess_manager();
        virtual wgm_feedbacks::enum_proc_feedback start_process() = 0;
        virtual void stop_process() = 0;

        virtual void start_process(Iprocess_manager* process) {};
        virtual void stop_process(Iprocess_manager* process) {};

        virtual void start_process(std::string processName) {};
        virtual void stop_process(std::string processName) {};

        virtual void start_process(int processID) {};
        virtual void stop_process(int processID) {};

        virtual void add_process_to_scheduler(Iprocess_manager* process);

        virtual void delete_last_process_from_scheduler();
        virtual void stop_all();
        virtual void start_all(std::function<void( int)> callback);

        virtual std::string get_name() = 0; // or id

        virtual int get_id() = 0;
        virtual long long get_elapsed_time()=0;

        virtual bool is_proc_success() = 0;
        virtual ~Iprocess_manager();

    };

}


