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

#include "cooling_process.h"
using enum wgm_feedbacks::enum_sys_feedback;
using enum wgm_feedbacks::enum_proc_feedback;

/****************** interface cooling process *******************/
wgm_processes::Icooling_process::Icooling_process(){}
wgm_processes::Icooling_process::~Icooling_process(){}

/******************* implementation cooling process ***************/
wgm_processes::cooling_process::cooling_process() {
  std::cout << "creating cooling process " << "\n";
  cooling_sys = new wafer_cooling_system::cooling_controller();
  process_timer = new wgm_monitoring::time_monitor();
}
wgm_processes::cooling_process:: ~cooling_process()
{
  std::cout << "deleting cooling process " << "\n";
  delete cooling_sys;
  delete process_timer;
}
wgm_feedbacks::enum_proc_feedback wgm_processes::cooling_process::start_process()
{
  std::cout << "execute " << process_name << "\n";
  process_timer->start_monitoring();
  if (cooling_sys->start_cooling() == sys_error)
  {
    process_timer->stop_monitoring();
    return proc_error;
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  process_timer->stop_monitoring();
  return proc_success;
}
wgm_feedbacks::enum_proc_feedback wgm_processes::cooling_process::stop_process()
{
  std::cout << "stopping " << process_name << "\n";
  cooling_sys->stop_cooling();
  process_timer->stop_monitoring();
  return proc_error;
}

wafer_cooling_system::Icooling_controller* wgm_processes::cooling_process::get_sys_ptr()
{
  return cooling_sys;
}

 long long wgm_processes::cooling_process::get_elapsed_time()
 {
    return process_timer->get_elapsed_time();
 }

std::string wgm_processes::cooling_process::get_name() { return process_name; };
bool wgm_processes::cooling_process::is_proc_success() { return process_feedback.report_feedback(); };
