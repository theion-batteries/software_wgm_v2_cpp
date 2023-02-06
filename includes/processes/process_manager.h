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
#include "heating_process.h"
#include "sinking_process.h"
#include "aligning_process.h"
#include "cooling_process.h"
#include "extracting_process.h"
namespace wgm_processes
{
   

    /******************** implementation process management ************/
    /**
     * @brief implementation process managemnt
     * add new process inside constructor
     * later will be possible to add new processes from interface method
     * add and delete from delete method
     */
    class process_manager: public Iprocess_manager
    {
    private:
        const std::string process_name = "Manager";
        std::vector<Iprocess_manager*> processesvector;
        wgm_feedbacks::proc_feedback process_feedback;
        int proc_id = 0;
        long long proc_time;
    public:
        process_manager();
        // clean up destruction
        virtual ~process_manager();
        virtual wgm_feedbacks::enum_proc_feedback start_process();
        virtual wgm_feedbacks::enum_proc_feedback stop_process();

        virtual void start_process(Iprocess_manager* process);
        virtual void stop_process(Iprocess_manager* process);
        virtual void start_process(std::string processName) ;
        virtual void stop_process(std::string processName);

        virtual void start_process(int processID);
        virtual void stop_process(int processID);
        virtual void start_all(std::function<void( int)> callback);
        virtual void stop_all();
        virtual void add_process_to_scheduler(Iprocess_manager* process);
        virtual void delete_last_process_from_scheduler();
        virtual std::string get_name();
        virtual bool is_proc_success();
        virtual int get_id() { return proc_id; };
        virtual long long get_elapsed_time();

    };
}


