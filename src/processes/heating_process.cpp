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

#include "heating_process.h"

// interface heating proc
wgm_processes::Iheating_process::Iheating_process(){}
wgm_processes::Iheating_process:: ~Iheating_process() {}

// implememnt heating proc

wgm_processes::heating_process::heating_process()
{
  std::cout << "creating heating process " << std::endl;
  heating_sys = new sulfur_heating_system::sulfur_heating_controller();
  process_timer = new wgm_monitoring::time_monitor();
}
wgm_processes::heating_process::~heating_process()
{
  std::cout << "deleting heating process " << std::endl;
  delete heating_sys;
  delete process_timer;
}
wgm_feedbacks::enum_proc_feedback wgm_processes::heating_process::start_process()
{
  std::cout << "execute process" << process_name << std::endl;
  process_timer->start_monitoring();
  if (heating_sys->start_heating_sys() == sys_error)
  {
  std::cout << "error heat sys, aborting process " << process_name << std::endl;
    process_timer->stop_monitoring();

    return proc_error;
  }
 // std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  process_timer->stop_monitoring();
  std::cout << "finish process " << process_name << std::endl;

  return proc_success;
}
wgm_feedbacks::enum_proc_feedback wgm_processes::heating_process::stop_process()
{
  std::cout << "finish " << process_name << std::endl;
  heating_sys->stop_heating_sys();
  process_timer->stop_monitoring();
  return proc_error;

}


sulfur_heating_system::Isulfur_heating_controller* wgm_processes::heating_process::get_sys_ptr()
{
  return heating_sys;
}

 long long wgm_processes::heating_process::get_elapsed_time()
 {
    return process_timer->get_elapsed_time();
 }

std::string wgm_processes::heating_process::get_name() { return process_name; };
bool wgm_processes::heating_process::is_proc_success() { return process_feedback.report_feedback(); };
