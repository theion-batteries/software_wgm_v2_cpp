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
#include "heating_system.h"
#include "cnt_alignment_system.h"
#include "wafer_holder_motion_system.h"
#include "wafer_cooling_system.h"
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
        Iprocesses_managment() {}
        virtual void start_process() = 0;
        virtual void stop_process() = 0;
        virtual void add_process_to_scheduler(Iprocesses_managment* process) {};
        virtual void delete_last_process_from_scheduler() {};
        virtual void stop_all() {};
        virtual void start_all() {};
        virtual std::string get_name() = 0;
        virtual bool is_proc_success() = 0;
        virtual ~Iprocesses_managment() {};
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
        Iheating_process()
        {
            std::cout << "creating heating process " << std::endl;
        }

        virtual ~Iheating_process()
        {
        }
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
        virtual std::string get_name() { return process_name; };
        virtual bool is_proc_success() { return process_feedback.report_feedback(); };
    };
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

    /******************* interface wafer insertion process***************/
    class Isinking_process : public Iprocesses_managment
    {
    public:
        Isinking_process()
        {
            std::cout << "creating sinking process " << std::endl;
        }
        virtual ~Isinking_process()
        {
        }
        virtual void start_process() = 0;
        virtual void stop_process() = 0;
        virtual std::string get_name() = 0;
        virtual bool is_proc_success() = 0;
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
        virtual std::string get_name() { return process_name; };
        virtual bool is_proc_success() { return process_feedback.report_feedback(); };
    };
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
    /****************** interface cnt alignment process*******************/
    class Ialigning_process : public Iprocesses_managment
    {
    public:
        Ialigning_process()
        {
        }
        virtual ~Ialigning_process()
        {
        }
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
        virtual std::string get_name() { return process_name; };
        virtual bool is_proc_success() { return process_feedback.report_feedback(); };

    };
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
    /****************** interface cooling process *******************/
    class Icooling_process : public Iprocesses_managment
    {
    public:
        Icooling_process()
        {
            std::cout << "creating cooling process " << std::endl;
        }
        virtual ~Icooling_process()
        {
        }
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
        cooling_process() {
            cooling_sys = new wafer_cooling_system::cooling_controller();
            process_timer = new wgm_monitoring::time_monitor();
        }
        virtual ~cooling_process()
        {
            std::cout << "deleting cooling process " << std::endl;
            delete cooling_sys;
            delete process_timer;
        }
        virtual void start_process();
        virtual void stop_process();
        virtual std::string get_name() { return process_name; };
        virtual bool is_proc_success() { return process_feedback.report_feedback(); };
    };
    void cooling_process::start_process()
    {
        std::cout << "execute " << process_name << std::endl;
        process_timer->start_monitoring();
        cooling_sys->start_cooling();
        // feedback
        process_timer->stop_monitoring();
    }
    void cooling_process::stop_process()
    {
        std::cout << "finish " << process_name << std::endl;
        cooling_sys->stop_cooling();

    }
    /******************* interface wafer extraction process***************/
    class Iextracting_process : public Iprocesses_managment
    {
    public:
        Iextracting_process()
        {
            std::cout << "creating extracting process " << std::endl;
        }
        virtual ~Iextracting_process()
        {
        }
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
        extracting_process() {
            extracting_sys = new wafer_holder_motion_system::wafer_motion_controller();
            process_timer = new wgm_monitoring::time_monitor();

        }
        virtual ~extracting_process()
        {
            std::cout << "deleting extracting process " << std::endl;
            delete extracting_sys;
            delete process_timer;
        }
        virtual void start_process();
        virtual void stop_process();
        virtual std::string get_name() { return process_name; };
        virtual bool is_proc_success() { return process_feedback.report_feedback(); };

    };
        void extracting_process::start_process()
        {
            std::cout << "execute " << process_name << std::endl;
            process_timer->start_monitoring();
            extracting_sys->extract_wafer_from_ml();
            // feedback
            process_timer->stop_monitoring();
        }
        void extracting_process::stop_process()
        {
            std::cout << "finish " << process_name << std::endl;
        }


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
            process_management() {
                std::cout << "creating process manager" << std::endl;
                //processes_monitor = new wgm_monitoring::monitor_managment();
                /********************* add new processes *************************/
                /***** add heating process ***/
                Iheating_process* heating_proc = new heating_process();
                processesvector.push_back(heating_proc);
                std::cout << "added heating process to process scheduler" << std::endl;

                /***** add insertion process ***/
                Isinking_process* insertion_proc = new sinking_process();
                processesvector.push_back(insertion_proc);
                std::cout << "added wafer insertion process to process scheduler" << std::endl;

                /***** add aligning process ***/
                Ialigning_process* aligning_proc = new aligning_process();
                processesvector.push_back(aligning_proc);
                std::cout << "added aligning process to process scheduler" << std::endl;

                /***** add cooling process ***/
                Icooling_process* cooling_proc = new cooling_process();
                processesvector.push_back(cooling_proc);
                std::cout << "added cooling process to process scheduler" << std::endl;

                /***** add insertion process ***/
                Iextracting_process* extraction_proc = new extracting_process();
                processesvector.push_back(extraction_proc);
                std::cout << "added wafer extracting process to process scheduler" << std::endl;
            }
            // clean up destruction
            virtual ~process_management() {
                std::cout << "deleting process scheduler" << std::endl;
                for (auto process : processesvector)
                {
                    if (process != nullptr)
                    {
                        delete process;
                    }
                    else
                    {
                        std::cout << "can't free memory" << std::endl;
                        break;
                    }
                }

            }
            virtual void start_process();
            virtual void stop_process();
            virtual void start_all();
            virtual void stop_all();
            virtual void add_process_to_scheduler(Iprocesses_managment* process);
            virtual void delete_last_process_from_scheduler();
            virtual std::string get_name() { return process_name; };
            virtual bool is_proc_success() { return process_feedback.report_feedback(); };

        };


        void process_management::start_process()
        {
            std::cout << "process started" << std::endl;
        }
        void process_management::stop_process()
        {
            std::cout << "process stopped" << std::endl;
        }
        void process_management::start_all()
        {
            std::cout << "executing all processes" << std::endl;
            for (auto process : processesvector)
            {
                if (process != nullptr)
                {
                    process->start_process();
                    if (process->is_proc_success()) continue;
                    break;
                }
                else std::cout << "empty process scheduler" << std::endl;
            }
        }
        void process_management::stop_all()
        {
            std::cout << "stopping all processes" << std::endl;

            for (auto process : processesvector)
            {
                if (process != nullptr)
                {
                    process->stop_process();
                }
                else std::cout << "empty process scheduler" << std::endl;
            }
        }
        void process_management::add_process_to_scheduler(Iprocesses_managment* process)
        {
            processesvector.push_back(process);

        }
        void process_management::delete_last_process_from_scheduler()
        {
            processesvector.pop_back();

        }

    }


