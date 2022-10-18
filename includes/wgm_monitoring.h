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
    Imonitor_management();
    virtual void start_monitoring() = 0;
    virtual void stop_monitoring() = 0;
    virtual void add_to_monitor_list(Imonitor_management* param_monitor);
    virtual void delete_last_from_monitor_list();
    virtual ~Imonitor_management();
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
    Itime_monitor();

    virtual ~Itime_monitor();
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
    time_monitor();
    virtual ~time_monitor();
  protected:
    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> end;
  protected:
    virtual void start_monitoring();
    virtual void stop_monitoring();
  };

  /****************** interface distance monitor *****************/
  class Idistance_monitor :public Imonitor_management
  {
  public:
    Idistance_monitor();
    virtual ~Idistance_monitor();
    virtual void start_monitoring() = 0;
    virtual void stop_monitoring() = 0;
  };
  /****************** implementation distance monitor *****************/
  class distance_monitor :public Idistance_monitor
  {
  private:
    wafer_holder_motion_system::Iwafer_motion_controller* param_distance;
  public:
    distance_monitor(wafer_holder_motion_system::Iwafer_motion_controller* ptr_to_system);
    virtual ~distance_monitor();
  protected:
    virtual void start_monitoring();
    virtual void stop_monitoring();
  };

  /****************** interface temperature monitor *****************/
  class Iheat_monitor :public Imonitor_management
  {
  public:
    Iheat_monitor();
    virtual ~Iheat_monitor();
    virtual void start_monitoring() = 0;
    virtual void stop_monitoring() = 0;
  };
  /****************** implementation temperature monitor *****************/
  class heat_monitor : public Iheat_monitor
  {
  private:
    sulfur_heating_system::Isulfur_heating_controller* param_temp;
  public:
    heat_monitor(sulfur_heating_system::Isulfur_heating_controller* ptr_to_system);
    virtual ~heat_monitor();
  protected:
    virtual void start_monitoring();
    virtual void stop_monitoring();
  };

  /****************** interface current monitor *****************/
  class Ivoltage_monitor :public Imonitor_management
  {
  public:
    Ivoltage_monitor();
    virtual ~Ivoltage_monitor();
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
    voltage_monitor(cnt_alignment_system::Icnt_aligning_controller* ptr_to_system);
    virtual ~voltage_monitor();
  };

  /****************** interface voltage monitor *****************/
  class Icurrent_monitor :public Imonitor_management
  {
  public:
    Icurrent_monitor();
    virtual ~Icurrent_monitor();
    virtual void start_monitoring() = 0;
    virtual void stop_monitoring() = 0;
  };
  /****************** implementation voltage monitor *****************/
  class current_monitor : public Icurrent_monitor
  {
  private:
    cnt_alignment_system::Icnt_aligning_controller* param_current;
  public:
    current_monitor(cnt_alignment_system::Icnt_aligning_controller* ptr_to_system);
    virtual ~current_monitor();

  protected:
    virtual void start_monitoring();
    virtual void stop_monitoring();

  };


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
    monitor_managment();
    virtual ~monitor_managment();
  protected:
    virtual void start_monitoring();
    virtual void stop_monitoring();
    virtual void add_to_monitor_list(Imonitor_management* param_monitor);
    virtual void delete_last_from_monitor_list();
  };

}
