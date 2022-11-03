/**
 * @file wgm_monitoring.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-07-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "wgm_monitoring.h"

wgm_monitoring::Imonitor_management::Imonitor_management() {}
void wgm_monitoring::Imonitor_management::add_to_monitor_list(Imonitor_management* param_monitor) {};
void wgm_monitoring::Imonitor_management::delete_last_from_monitor_list() {};
wgm_monitoring::Imonitor_management::~Imonitor_management() {}

wgm_monitoring::Itime_monitor::Itime_monitor()
{
  std::cout << "creating time monitor " << std::endl;
}

wgm_monitoring::Itime_monitor:: ~Itime_monitor()
{
}

wgm_monitoring::time_monitor::time_monitor() {

}
wgm_monitoring::time_monitor:: ~time_monitor()
{
  std::cout << "deleting heating process " << std::endl;
}

void wgm_monitoring::time_monitor::start_monitoring()
{
  std::cout << "process time monitoring started " << std::endl;
  start = std::chrono::steady_clock::now();
}
void wgm_monitoring::time_monitor::stop_monitoring()
{

  end = std::chrono::steady_clock::now();
  elapsed_time=std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
  std::cout << "process time ended: took "
    //<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds "
    //<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds " // almost equivalent form of the above, but
    << elapsed_time<< " seconds"<<std::endl;  // using milliseconds and seconds accordingly
}

 double wgm_monitoring::time_monitor::get_elapsed_time()
 {
  return elapsed_time;
 }
wgm_monitoring::Idistance_monitor::Idistance_monitor()
{
  std::cout << "creating distance monitor " << std::endl;
}
wgm_monitoring::Idistance_monitor:: ~Idistance_monitor()
{
}

wgm_monitoring::distance_monitor::distance_monitor(wafer_holder_motion_system::Iwafer_motion_controller* ptr_to_system) {
  param_distance = ptr_to_system;
}
wgm_monitoring::distance_monitor:: ~distance_monitor()
{
  std::cout << "deleting sinking process " << std::endl;
  //delete param_distance;
}
void wgm_monitoring::distance_monitor::start_monitoring()
{
  std::cout << "process distance monitoring started " << std::endl;
  param_distance->get_current_value(0);
}
void wgm_monitoring::distance_monitor::stop_monitoring()
{
  std::cout << "process distance monitoring stopped " << std::endl;
}

wgm_monitoring::Iheat_monitor::Iheat_monitor()
{
  std::cout << "creating temperature monitor " << std::endl;
}
wgm_monitoring::Iheat_monitor:: ~Iheat_monitor()
{
}
wgm_monitoring::heat_monitor::heat_monitor(sulfur_heating_system::Isulfur_heating_controller* ptr_to_system) {
  param_temp = ptr_to_system;
}

wgm_monitoring::heat_monitor:: ~heat_monitor()
{
  std::cout << "deleting temperature monitor " << std::endl;
  //delete param_temp;
}

void wgm_monitoring::heat_monitor::start_monitoring()
{
  std::cout << "process temperature monitoring started " << std::endl;
  param_temp->getSensorReading();
}
void wgm_monitoring::heat_monitor::stop_monitoring()
{
  std::cout << "process temperature monitoring stopped " << std::endl;
}
wgm_monitoring::Ivoltage_monitor::Ivoltage_monitor()
{
  std::cout << "creating voltage monitor" << std::endl;
}
wgm_monitoring::Ivoltage_monitor::~Ivoltage_monitor()
{
}

wgm_monitoring::voltage_monitor::voltage_monitor(cnt_alignment_system::Icnt_aligning_controller* ptr_to_system) {
  param_voltage = ptr_to_system;
}
wgm_monitoring::voltage_monitor:: ~voltage_monitor()
{
  std::cout << "deleting voltage monitor" << std::endl;
  //delete param_voltage;
}


void wgm_monitoring::voltage_monitor::start_monitoring()
{
  std::cout << "process voltage monitoring started " << std::endl;
  auto Voltage_data = param_voltage->get_voltage_struct();
  std::cout << "input voltage:  " << Voltage_data.Vin << "output voltage: " << Voltage_data.Vout << std::endl;
}
void wgm_monitoring::voltage_monitor::stop_monitoring()
{
  std::cout << "process voltage monitoring stopped " << std::endl;
}

wgm_monitoring::Icurrent_monitor::Icurrent_monitor()
{
  std::cout << "creating current monitor " << std::endl;
}
wgm_monitoring::Icurrent_monitor:: ~Icurrent_monitor()
{
}

wgm_monitoring::current_monitor::current_monitor(cnt_alignment_system::Icnt_aligning_controller* ptr_to_system) {
  param_current = ptr_to_system;
}
wgm_monitoring::current_monitor:: ~current_monitor()
{
  std::cout << "deleting current monitor" << std::endl;
  //delete param_current;
}
void wgm_monitoring::current_monitor::start_monitoring()
{
  std::cout << "process current monitoring started " << std::endl;
  auto Current_data = param_current->get_current_struct();
  std::cout << "input current:  " << Current_data.Cin << "output current: " << Current_data.Cout << std::endl;
}
void wgm_monitoring::current_monitor::stop_monitoring()
{
  std::cout << "process current monitoring stopped " << std::endl;
}

wgm_monitoring::monitor_managment::monitor_managment() {
  std::cout << "creating monitor manager" << std::endl;
}
wgm_monitoring::monitor_managment:: ~monitor_managment() {
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

void  wgm_monitoring::monitor_managment::start_monitoring()
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
void  wgm_monitoring::monitor_managment::stop_monitoring()
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
void  wgm_monitoring::monitor_managment::add_to_monitor_list(Imonitor_management* param_monitor)
{
  monitor_list.push_back(param_monitor);
}
void  wgm_monitoring::monitor_managment::delete_last_from_monitor_list()
{
  monitor_list.pop_back();
}
