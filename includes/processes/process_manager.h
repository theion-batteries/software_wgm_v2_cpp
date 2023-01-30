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
        virtual void start_process() = 0;
        virtual void stop_process() = 0;
        virtual void start_process(Iprocess_manager* process){};
        virtual void stop_process(Iprocess_manager* process){};
        virtual void add_process_to_scheduler(Iprocess_manager* process);

        virtual void delete_last_process_from_scheduler();
        virtual void stop_all();
        virtual void start_all();

        virtual std::string get_name() = 0; // or id
        virtual bool is_proc_success() = 0;
        virtual ~Iprocess_manager();

    };

    /******************** implementation process management ************/
    /**
     * @brief implementation process managemnt
     * add new process inside constructor
     * later will be possible to add new processes from interface method
     * add and delete from delete method
     */
    class process_manager : public Iprocess_manager
    {
    private:
        const std::string process_name = "process scheduler";
        std::vector<Iprocess_manager*> processesvector;
        wgm_feedbacks::proc_feedback process_feedback;
    public:
        process_manager() ;
        // clean up destruction
        virtual ~process_manager() ;
        virtual void start_process();
        virtual void stop_process();
        virtual void start_process(Iprocess_manager* process) ;
        virtual void stop_process(Iprocess_manager* process) ;
        virtual void start_all();
        virtual void stop_all();
        virtual void add_process_to_scheduler(Iprocess_manager* process);
        virtual void delete_last_process_from_scheduler();
        virtual std::string get_name() ;
        virtual bool is_proc_success() ;
    };
}


