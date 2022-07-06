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
        Iprocesses_managment() {
        }
        virtual void start_process() = 0;
        virtual void stop_process() = 0;
        virtual void stop_all() {};
        virtual void start_all() {};
        virtual ~Iprocesses_managment() {
        }
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
    };
    /************* implementation heating process ************/
    class heating_process : public Iheating_process
    {
    public:
        sulfur_heating_system::Isulfur_heating_controller* heating_sys;
        heating_process() {
            heating_sys = new sulfur_heating_system::sulfur_heating_controller();
        }

        virtual ~heating_process()
        {
            std::cout << "deleting heating process " << std::endl;
            delete heating_sys;
        }
        virtual void start_process();
        virtual void stop_process();
    };
    void heating_process::start_process()
    {
        heating_sys->turn_on_heating();
    }
    void heating_process::stop_process()
    {
        heating_sys->turn_off_heating();
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
    };
    /**************** implementation wafer insertion process ************/
    class sinking_process : public Isinking_process
    {
    private:
        wafer_holder_motion_system::Iwafer_motion_controller* sinking_sys;
    public:
        sinking_process() {
            sinking_sys = new wafer_holder_motion_system::wafer_motion_controller();
        }
        virtual ~sinking_process()
        {
            std::cout << "deleting sinking process " << std::endl;
            delete sinking_sys;
        }
        virtual void start_process();
        virtual void stop_process();
    };
    void sinking_process::start_process()
    {
        sinking_sys->set_distance_to_surface_contact(30);
        sinking_sys->insert_wafer_in_ml();
    }
    void sinking_process::stop_process()
    {

    }
    /****************** interface cnt alignment process*******************/
    class Ialigning_process : public Iprocesses_managment
    {
    public:
        Ialigning_process()
        {
            std::cout << "creating aligning process " << std::endl;
        }
        virtual ~Ialigning_process()
        {
        }
        virtual void start_process() = 0;
        virtual void stop_process() = 0;
    };
    /******************* implementation cnt alignment process ***************/
    class aligning_process : public Ialigning_process
    {
    private:
        cnt_alignment_system::Icnt_aligning_controller* aligning_sys;
    public:
        aligning_process() {
            aligning_sys = new cnt_alignment_system::cnt_aligning_controller();
        }
        virtual ~aligning_process()
        {
            std::cout << "deleting aligning process " << std::endl;
            delete aligning_sys;
        }
        virtual void start_process();
        virtual void stop_process();
    };
    void aligning_process::start_process()
    {
        aligning_sys->start_aligning();
    }
    void aligning_process::stop_process()
    {
        aligning_sys->stop_aligning();
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
    };
    /******************* implementation cooling process ***************/
    class cooling_process : public Icooling_process
    {
    private:
        wafer_cooling_system::Icooling_controller* cooling_sys;
    public:
        cooling_process() {
            cooling_sys = new wafer_cooling_system::cooling_controller();
        }
        virtual ~cooling_process()
        {
            std::cout << "deleting cooling process " << std::endl;
            delete cooling_sys;
        }
        virtual void start_process();
        virtual void stop_process();
    };
    void cooling_process::start_process()
    {
        cooling_sys->start_cooling();
    }
    void cooling_process::stop_process()
    {
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
    };
    /**************** implementation wafer extraction process ************/
    class extracting_process : public Iextracting_process
    {
    private:
        wafer_holder_motion_system::Iwafer_motion_controller* extracting_sys;
    public:
        extracting_process() {
            extracting_sys = new wafer_holder_motion_system::wafer_motion_controller();
        }
        virtual ~extracting_process()
        {
            std::cout << "deleting extracting process " << std::endl;
            delete extracting_sys;
        }
        virtual void start_process();
        virtual void stop_process();
    };
    void extracting_process::start_process()
    {
        extracting_sys->extract_wafer_from_ml();
    }
    void extracting_process::stop_process()
    {

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
        std::vector<Iprocesses_managment*> processesvector;
        wgm_monitoring::Imonitor_management* processes_monitor;
    public:
        process_management() {
            std::cout << "creating process manager" << std::endl;
            processes_monitor = new wgm_monitoring::monitor_managment();
            /***** add new processes *******/
            /***** add new monitors *******/

            /***** add heating process ***/
            Iheating_process* heating_proc = new heating_process();
            processesvector.push_back(heating_proc);
            std::cout << "added heating process to process vector" << std::endl;
            /***** add temperature monitor ***/
            wgm_monitoring::Imonitor_management* temp_mon = new wgm_monitoring::heat_monitor();
            processes_monitor->add_to_monitor_list(temp_mon);
            std::cout << "added temperatur to monitor list" << std::endl;

            /***** add insertion process ***/
            Isinking_process* insertion_proc = new sinking_process();
            processesvector.push_back(insertion_proc);
            std::cout << "added wafer insertion process to process vector" << std::endl;
            /***** add distance monitor ***/
            wgm_monitoring::Imonitor_management* dist_mon = new wgm_monitoring::distance_monitor();
            processes_monitor->add_to_monitor_list(dist_mon);
            std::cout << "added distance to monitor list" << std::endl;

            /***** add aligning process ***/
            Ialigning_process* aligning_proc = new aligning_process();
            processesvector.push_back(aligning_proc);
            std::cout << "added aligning process to process vector" << std::endl;
            /***** add time monitor ***/
            wgm_monitoring::Imonitor_management* time_mon = new wgm_monitoring::time_monitor();
            processes_monitor->add_to_monitor_list(time_mon);
            std::cout << "added time to monitor list" << std::endl;
            /***** add voltage monitor ***/
            wgm_monitoring::Imonitor_management* volt_mon = new wgm_monitoring::voltage_monitor();
            processes_monitor->add_to_monitor_list(volt_mon);
            std::cout << "added voltage to monitor list" << std::endl;
            /***** add current monitor ***/
            wgm_monitoring::Imonitor_management* curr_mon = new wgm_monitoring::current_monitor();
            processes_monitor->add_to_monitor_list(curr_mon);
            std::cout << "added current to monitor list" << std::endl;
            /***** add cooling process ***/
            Icooling_process* cooling_proc = new cooling_process();
            processesvector.push_back(cooling_proc);
            std::cout << "added cooling process to process vector" << std::endl;

            /***** add insertion process ***/
            Iextracting_process* extraction_proc = new extracting_process();
            processesvector.push_back(extraction_proc);
            std::cout << "added wafer extracting process to process vector" << std::endl;
        }
        // clean up destruction
        virtual ~process_management() {
            std::cout << "deleting process manager" << std::endl;
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
            // delete all monitors
            delete processes_monitor;
        }
        virtual void start_process();
        virtual void stop_process();
        virtual void start_all();
        virtual void stop_all();
        virtual void add_process();
        virtual void delete_process();
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
                processes_monitor->start_monitoring();
            }
            else std::cout << "empty vector" << std::endl;
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
                processes_monitor->stop_monitoring();
            }
            else std::cout << "empty vector" << std::endl;
        }
    }
    void process_management::add_process()
    {

    }
    void process_management::delete_process()
    {

    }

}

/****************** user code ********************/
class user {
private:
    wgm_processes::Iprocesses_managment* processInterfaces;

public:
    user()
    {
        std::cout << "user started app" << std::endl;

        processInterfaces = new wgm_processes::process_management();
    }
    void run_app()
    {
        processInterfaces->start_all();
    }
    void stop_app()
    {
        processInterfaces->stop_all();
    }
    ~user()
    {
        std::cout << "user stopped app" << std::endl;
        delete processInterfaces;
    }
};

