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
wgm_processes::Iheating_process::Iheating_process()
{
  std::cout << "creating heating process " << std::endl;
}
wgm_processes::Iheating_process:: ~Iheating_process() {}

// implememnt hreating proc
std::string wgm_processes::heating_process::get_name() { return process_name; };
bool wgm_processes::heating_process::is_proc_success() { return process_feedback.report_feedback(); };

wgm_processes::heating_process::heating_process()
{
  heating_sys = new sulfur_heating_system::sulfur_heating_controller();
  process_timer = new wgm_monitoring::time_monitor();
  process_temp_monitor = new wgm_monitoring::heat_monitor(heating_sys);
}
wgm_processes::heating_process::~heating_process()

{
  std::cout << "deleting heating process " << std::endl;
  delete heating_sys;
  delete process_timer;
  delete process_temp_monitor;
}
void wgm_processes::heating_process::start_process()
{
  std::cout << "execute " << process_name << std::endl;
  // start timer
  process_timer->start_monitoring();
  // start system
  heating_sys->turn_on_heating();
  // report feedback
  auto heating_feedback = wgm_feedbacks::enum_sys_feedback::sys_error;
  // feedback
  if (heating_feedback == wgm_feedbacks::enum_sys_feedback::sys_error)
  {
    process_timer->stop_monitoring();
    process_feedback.setFeedback(wgm_feedbacks::enum_proc_feedback::proc_error);
  }
  else if (heating_feedback == wgm_feedbacks::enum_sys_feedback::sys_success)
  {
    process_feedback.setFeedback(wgm_feedbacks::enum_proc_feedback::proc_success);
  process_temp_monitor->start_monitoring();
  }

}
void wgm_processes::heating_process::stop_process()
{
  std::cout << "finish " << process_name << std::endl;
  heating_sys->turn_off_heating();
  process_temp_monitor->stop_monitoring();
}
