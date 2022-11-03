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
std::string wgm_processes::extracting_process::get_name() { return process_name; };
bool wgm_processes::extracting_process::is_proc_success() { return process_feedback.report_feedback(); };

wgm_processes::extracting_process::extracting_process(wafer_holder_motion_system::Iwafer_motion_controller* ptrTosys) {
  extracting_sys = ptrTosys;
  process_timer = new wgm_monitoring::time_monitor();

}
wgm_processes::extracting_process::~extracting_process()
{
  std::cout << "deleting extracting process " << std::endl;
  //if (extracting_sys !=nullptr ) delete extracting_sys;
  delete process_timer;
}
void wgm_processes::extracting_process::start_process()
{
  std::cout << "execute " << process_name << std::endl;
  process_timer->start_monitoring();
  extracting_sys->extract_wafer_from_ml();
  // feedback
  process_timer->stop_monitoring();
}
void wgm_processes::extracting_process::stop_process()
{
  std::cout << "finish " << process_name << std::endl;
}
