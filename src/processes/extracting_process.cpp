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

#include "extracting_process.h"


 /******************* interface wafer extraction process***************/
wgm_processes::Iextracting_process::Iextracting_process()
{
  std::cout << "creating extracting process " << std::endl;
}
wgm_processes::Iextracting_process::~Iextracting_process()
{
}

/**************** implementation wafer extraction process ************/

wgm_processes::extracting_process::extracting_process(wafer_holder_motion_system::Iwafer_motion_controller* ptrTosys) {
  extracting_sys = ptrTosys;
  process_timer = new wgm_monitoring::time_monitor();

}
wgm_processes::extracting_process::~extracting_process()
{
  std::cout << "deleting extracting process " << std::endl;
  delete process_timer;
}
wgm_feedbacks::enum_proc_feedback wgm_processes::extracting_process::start_process()
{
  std::cout << "execute " << process_name << std::endl;
  process_timer->start_monitoring();
 if( extracting_sys->extract_wafer_from_ml() == sys_error )
 {
  process_timer->stop_monitoring();
  return proc_error;
 }
  std::this_thread::sleep_for(std::chrono::milliseconds(2500));
  process_timer->stop_monitoring();
  return proc_success;
}
wgm_feedbacks::enum_proc_feedback wgm_processes::extracting_process::stop_process()
{
  std::cout << "finish " << process_name << std::endl;
  process_timer->stop_monitoring();
  return proc_success;
}

long long wgm_processes::extracting_process::get_elapsed_time()
{
  return process_timer->get_elapsed_time();
}

wafer_holder_motion_system::Iwafer_motion_controller* wgm_processes::extracting_process::get_sys_ptr()
{
  return extracting_sys;
}

std::string wgm_processes::extracting_process::get_name() { return process_name; };
bool wgm_processes::extracting_process::is_proc_success() { return process_feedback.report_feedback(); };
