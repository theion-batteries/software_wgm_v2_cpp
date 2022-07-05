/**
 * @file wgm_monitoring.h
 * @author sami dhiab (sami@theion.de)
 * @brief wgm monitoring package
 * @version 0.1
 * @date 2022-07-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <list>
#include <vector>
#include <chrono>
#include "heating_system.h"
#include "cnt_alignment_system.h"
#include "wafer_holder_motion_system.h"
#include "wafer_cooling_system.h"
#include <iomanip>
#include <ctime>
#include <chrono>
namespace wgm_monitoring
{
    /************* interface monitor management **********/
    /**
     * @brief interface monitor management
     * do not modify!
     */    
     class Imonitor_management
    {
        public:
            Imonitor_management() {
        }
             virtual void start_monitoring () = 0;
             virtual void stop_monitoring () = 0;
             virtual void add_to_monitor () ;
             virtual void delete_from_monitor ();
            virtual ~Imonitor_management() {
        }     
    };
    /************* monitor interface and implementation**********/
    /**
     * @brief add parameter monitor as following:
     * create interface and inherit from Imonitor_managment.
     * create abstract methods start_monitoring and stop_monitoring
     * create the implementation class, redefine these methods
     * create the actual monitor system inside constructor
     * delete it in the destructor (virtual)
     */
     /****************** interface time monitor *****************/
     class Itime_monitor:public Imonitor_management
    {
        public:
             virtual void start_monitoring () = 0;
             virtual void stop_monitoring () = 0;
    };
    /************* implementation time monitor************/
    class time_monitor: public Itime_monitor
    /**
     * @brief monitor time for cnt dispenser
     * 
     */
    {
        protected:
        std::chrono::time_point<std::chrono::steady_clock> start;
        std::chrono::time_point<std::chrono::steady_clock> end;
        protected:
             virtual void start_monitoring ();
             virtual void stop_monitoring ();
    };
      void time_monitor::start_monitoring ()
    {
        std::cout << "process time monitoring started " << std::endl;
        start = std::chrono::steady_clock::now();    
    }
      void time_monitor::stop_monitoring ()
    {
        end = std::chrono::steady_clock::now();
    std::cout
      << "process ended: took "
      << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "µs ≈ "
      << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms ≈ " // almost equivalent form of the above, but
      << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()<< "s.\n";  // using milliseconds and seconds accordingly
    }
     /****************** interface distance monitor *****************/
     class Idistance_monitor:public Imonitor_management
    {
        public:
             virtual void start_monitoring () = 0;
             virtual void stop_monitoring () = 0;
    };     
     /****************** impleemntation distance monitor *****************/
     class distance_monitor:public Idistance_monitor
    {
        protected:
            wafer_holder_motion_system::Iwafer_motion_controller* param_distance;
    
        protected:
             virtual void start_monitoring ();
             virtual void stop_monitoring ();
    };
      void distance_monitor::start_monitoring ()
    {
    std::cout << "process distance monitoring started " << std::endl;
         
    }
    void distance_monitor::stop_monitoring ()
    {
    std::cout << "process distance monitoring stopped " << std::endl;
                   
    }
     /****************** interface temperature monitor *****************/
     class Iheat_monitor:public Imonitor_management
    {
        public:
             virtual void start_monitoring () = 0;
             virtual void stop_monitoring () = 0;
    };
     /****************** implementation temperature monitor *****************/
     class heat_monitor: public Iheat_monitor
    {
        protected:
            sulfur_heating_system::Iheater * param_temp;
    
        protected:
             virtual void start_monitoring ();
             virtual void stop_monitoring ();
    };
      void heat_monitor::start_monitoring ()
    {
    std::cout << "process temperature monitoring started " << std::endl;
                        
    }
      void heat_monitor::stop_monitoring ()
    {
    std::cout << "process temperature monitoring stopped " << std::endl;                 
    }
     /****************** interface current monitor *****************/
     class Ivoltage_monitor:public Imonitor_management
    {
        public:
             virtual void start_monitoring () = 0;
             virtual void stop_monitoring () = 0;
    };
     /****************** implementation current monitor *****************/
     class voltage_monitor: public Ivoltage_monitor
    {
        protected:
            cnt_alignment_system::Icnt_aligning_controller* param_voltage;
        protected:
             virtual void start_monitoring ();
             virtual void stop_monitoring ();
    
    };
    
      void voltage_monitor::start_monitoring ()
    {
    std::cout << "process voltage monitoring started " << std::endl;                 
    }
      void voltage_monitor::stop_monitoring ()
    {
    std::cout << "process voltage monitoring stopped " << std::endl;                                     
    }
     /****************** interface voltage monitor *****************/
     class Icurrent_monitor:public Imonitor_management
    {
        public:
             virtual void start_monitoring () = 0;
             virtual void stop_monitoring () = 0;
    }; 
     /****************** implementation voltage monitor *****************/
     class current_monitor: public Icurrent_monitor
    {
        protected:
           cnt_alignment_system::Icnt_aligning_controller* param_current;
    
        protected:
             virtual void start_monitoring ();
             virtual void stop_monitoring ();
    
    };
      void current_monitor::start_monitoring ()
    {
    std::cout << "process current monitoring started " << std::endl;                                      
    }
      void current_monitor::stop_monitoring ()
    {
    std::cout << "process current monitoring stopped " << std::endl;                                                        
    }

     /****************** implementation monitor management*****************/
     class monitor_managment: public Imonitor_management
    {
        protected:
            std::list<Imonitor_management*> monitor_list;
        protected:
             virtual void start_monitoring ();
             virtual void stop_monitoring ();
             virtual void add_to_monitor ();
             virtual void delete_from_monitor ();
    };
      void monitor_managment::start_monitoring ()
    {
                        
    }
    void monitor_managment::stop_monitoring ()
    {
                        
    }
    void monitor_managment::add_to_monitor ()
    {
                        
    }
    void monitor_managment::delete_from_monitor ()
    {
                        
    } 

}
