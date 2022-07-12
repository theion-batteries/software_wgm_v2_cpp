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
    Imonitor_management() {}
    virtual void start_monitoring() = 0;
    virtual void stop_monitoring() = 0;
    virtual void add_to_monitor_list(Imonitor_management* param_monitor){};
    virtual void delete_last_from_monitor_list(){};
    virtual ~Imonitor_management() {}
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
  class Itime_monitor :public Imonitor_management
  {
  public:
    Itime_monitor()
    {
      std::cout << "creating time monitor " << std::endl;
    }

    virtual ~Itime_monitor()
    {
    }
    virtual void start_monitoring() = 0;
    virtual void stop_monitoring() = 0;
  };
  /************* implementation time monitor************/
  class time_monitor : public Itime_monitor
    /**
     * @brief process time monitor. track the duration
     *
     */
  {
  public:
    time_monitor() {

    }
    virtual ~time_monitor()
    {
      std::cout << "deleting heating process " << std::endl;
    }
  protected:
    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> end;
  protected:
    virtual void start_monitoring();
    virtual void stop_monitoring();
  };
  void time_monitor::start_monitoring()
  {
    std::cout << "process time monitoring started " << std::endl;
    start = std::chrono::steady_clock::now();
  }
  void time_monitor::stop_monitoring()
  {
    end = std::chrono::steady_clock::now();
    std::cout
      << "process ended: took "
      << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "µs ≈ "
      << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms ≈ " // almost equivalent form of the above, but
      << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "s.\n";  // using milliseconds and seconds accordingly
  }
  /****************** interface distance monitor *****************/
  class Idistance_monitor :public Imonitor_management
  {
  public:
    Idistance_monitor()
    {
      std::cout << "creating distance monitor " << std::endl;
    }
    virtual ~Idistance_monitor()
    {
    }
    virtual void start_monitoring() = 0;
    virtual void stop_monitoring() = 0;
  };
  /****************** implementation distance monitor *****************/
  class distance_monitor :public Idistance_monitor
  {
  private:
    wafer_holder_motion_system::Iwafer_motion_controller* param_distance;
  public:
    distance_monitor(wafer_holder_motion_system::Iwafer_motion_controller* ptr_to_system) {
      param_distance = ptr_to_system;
    }
    virtual ~distance_monitor()
    {
      std::cout << "deleting sinking process " << std::endl;
      //delete param_distance;
    }
  protected:
    virtual void start_monitoring();
    virtual void stop_monitoring();
  };
  void distance_monitor::start_monitoring()
  {
    std::cout << "process distance monitoring started " << std::endl;
    param_distance->get_current_value();
  }
  void distance_monitor::stop_monitoring()
  {
    std::cout << "process distance monitoring stopped " << std::endl;
  }
  /****************** interface temperature monitor *****************/
  class Iheat_monitor :public Imonitor_management
  {
  public:
    Iheat_monitor()
    {
      std::cout << "creating temperature monitor " << std::endl;
    }
    virtual ~Iheat_monitor()
    {
    }
    virtual void start_monitoring() = 0;
    virtual void stop_monitoring() = 0;
  };
  /****************** implementation temperature monitor *****************/
  class heat_monitor : public Iheat_monitor
  {
  private:
    sulfur_heating_system::Isulfur_heating_controller* param_temp;
  public:
    heat_monitor(sulfur_heating_system::Isulfur_heating_controller* ptr_to_system) {
      param_temp = ptr_to_system;
    }
    virtual ~heat_monitor()
    {
      std::cout << "deleting temperature monitor " << std::endl;
      //delete param_temp;
    }
  protected:
    virtual void start_monitoring();
    virtual void stop_monitoring();
  };
  void heat_monitor::start_monitoring()
  {
    std::cout << "process temperature monitoring started " << std::endl;
    param_temp->getSensorReading();
  }
  void heat_monitor::stop_monitoring()
  {
    std::cout << "process temperature monitoring stopped " << std::endl;
  }
  /****************** interface current monitor *****************/
  class Ivoltage_monitor :public Imonitor_management
  {
  public:
    Ivoltage_monitor()
    {
      std::cout << "creating voltage monitor" << std::endl;
    }
    virtual ~Ivoltage_monitor()
    {
    }
    virtual void start_monitoring() = 0;
    virtual void stop_monitoring() = 0;
  };
  /****************** implementation current monitor *****************/
  class voltage_monitor : public Ivoltage_monitor
  {
  private:
    cnt_alignment_system::Icnt_aligning_controller* param_voltage;
  protected:
    virtual void start_monitoring();
    virtual void stop_monitoring();
  public:
    voltage_monitor(cnt_alignment_system::Icnt_aligning_controller* ptr_to_system) {
      param_voltage = ptr_to_system;
    }
    virtual ~voltage_monitor()
    {
      std::cout << "deleting voltage monitor" << std::endl;
      //delete param_voltage;
    }
  };

  void voltage_monitor::start_monitoring()
  {
    std::cout << "process voltage monitoring started " << std::endl;
    auto Voltage_data = param_voltage->get_voltage_struct();
    std::cout << "input voltage:  " << Voltage_data.Vin << "output voltage: " << Voltage_data.Vout << std::endl;
  }
  void voltage_monitor::stop_monitoring()
  {
    std::cout << "process voltage monitoring stopped " << std::endl;
  }
  /****************** interface voltage monitor *****************/
  class Icurrent_monitor :public Imonitor_management
  {
  public:
    Icurrent_monitor()
    {
      std::cout << "creating current monitor " << std::endl;
    }
    virtual ~Icurrent_monitor()
    {
    }
    virtual void start_monitoring() = 0;
    virtual void stop_monitoring() = 0;
  };
  /****************** implementation voltage monitor *****************/
  class current_monitor : public Icurrent_monitor
  {
  private:
    cnt_alignment_system::Icnt_aligning_controller* param_current;
  public:
    current_monitor(cnt_alignment_system::Icnt_aligning_controller* ptr_to_system) {
      param_current = ptr_to_system;
    }
    virtual ~current_monitor()
    {
      std::cout << "deleting current monitor" << std::endl;
      //delete param_current;
    }

  protected:
    virtual void start_monitoring();
    virtual void stop_monitoring();

  };
  void current_monitor::start_monitoring()
  {
    std::cout << "process current monitoring started " << std::endl;
    auto Current_data = param_current->get_current_struct();
    std::cout << "input current:  " << Current_data.Cin << "output current: " << Current_data.Cout << std::endl;
  }
  void current_monitor::stop_monitoring()
  {
    std::cout << "process current monitoring stopped " << std::endl;
  }

  /****************** implementation monitor management*****************/
    /******************** implementation process management ************/
    /**
     * @brief implementation monitor managemnt
     * add new monitor inside constructor
     * later will be possible to add new monitors from interface method
     * add and delete from delete method
     */
  class monitor_managment : public Imonitor_management
  {
  private:
    std::vector<Imonitor_management*> monitor_list;
   public:
        monitor_managment() {
            std::cout << "creating monitor manager" << std::endl;
        }
        virtual ~monitor_managment() {
            std::cout << "deleting monitor manager" << std::endl;
            for (auto monitor : monitor_list)
            {
                if (monitor != nullptr)
                {
                    delete monitor;
                }
                else
                {
                    std::cout << "can't free memory" << std::endl;
                    break;
                }
            }
        }
  protected:
    virtual void start_monitoring();
    virtual void stop_monitoring();
    virtual void add_to_monitor_list(Imonitor_management* param_monitor);
    virtual void delete_last_from_monitor_list();
  };
  void monitor_managment::start_monitoring()
  {
        std::cout << "monitor started" << std::endl;
        for (auto monitor : monitor_list)
        {
            if (monitor != nullptr)
            {
                monitor->start_monitoring();
            }
            else std::cout << "empty vector" << std::endl;
        }
  }
  void monitor_managment::stop_monitoring()
  {
        std::cout << "monitor stopped" << std::endl;
        for (auto monitor : monitor_list)
        {
            if (monitor != nullptr)
            {
                monitor->stop_monitoring();
            }
            else std::cout << "empty vector" << std::endl;
        }
  }
  void monitor_managment::add_to_monitor_list(Imonitor_management* param_monitor)
  {
      monitor_list.push_back(param_monitor);
  }
  void monitor_managment::delete_last_from_monitor_list()
  {
      monitor_list.pop_back();
  }

}
