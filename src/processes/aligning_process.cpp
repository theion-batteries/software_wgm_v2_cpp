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

#include "aligning_process.h"

/****************** interface cnt alignment process*******************/
wgm_processes::Ialigning_process::Ialigning_process(){}
wgm_processes::Ialigning_process:: ~Ialigning_process(){}

/******************* implementation cnt alignment process ***************/

wgm_processes::aligning_process::aligning_process() {
  std::cout << "creating aligning process " << std::endl;
  aligning_sys = new cnt_alignment_system::cnt_aligning_controller();
  process_timer = new wgm_monitoring::time_monitor();

}
wgm_processes::aligning_process:: ~aligning_process()
{
  std::cout << "deleting aligning process " << std::endl;
  delete aligning_sys;
  delete process_timer;
}
wgm_feedbacks::enum_proc_feedback wgm_processes::aligning_process::start_process()
{
  std::cout << "execute " << process_name << std::endl;
  process_timer->start_monitoring();
  if (aligning_sys->start_aligning() == sys_error)
  {
    process_timer->stop_monitoring();
    return proc_error;
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  process_timer->stop_monitoring();
  return proc_success;
}
wgm_feedbacks::enum_proc_feedback wgm_processes::aligning_process::stop_process()
{
  std::cout << "stopping " << process_name << std::endl;
  aligning_sys->stop_aligning();
  process_timer->stop_monitoring();
  return proc_error;
}

cnt_alignment_system::Icnt_aligning_controller * wgm_processes::aligning_process::get_sys_ptr()
{
  return aligning_sys;
}

 long long wgm_processes::aligning_process::get_elapsed_time()
 {
    return process_timer->get_elapsed_time();
 }

std::string wgm_processes::aligning_process::get_name() { return process_name; };
bool wgm_processes::aligning_process::is_proc_success() { return process_feedback.report_feedback(); };
