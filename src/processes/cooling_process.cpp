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

/****************** interface cooling process *******************/
wgm_processes::Icooling_process::Icooling_process()
{
  std::cout << "creating cooling process " << std::endl;
}
wgm_processes::Icooling_process::~Icooling_process()
{
}
/******************* implementation cooling process ***************/
wgm_processes::cooling_process::cooling_process() {
  cooling_sys = new wafer_cooling_system::cooling_controller();
  process_timer = new wgm_monitoring::time_monitor();
}
wgm_processes::cooling_process:: ~cooling_process()
{
  std::cout << "deleting cooling process " << std::endl;
  delete cooling_sys;
  delete process_timer;
}
void wgm_processes::cooling_process::start_process()
{
  std::cout << "execute " << process_name << std::endl;
  process_timer->start_monitoring();
  cooling_sys->start_cooling();
  // feedback
  process_timer->stop_monitoring();
}
void wgm_processes::cooling_process::stop_process()
{
  std::cout << "finish " << process_name << std::endl;
  cooling_sys->stop_cooling();

}
std::string wgm_processes::cooling_process::get_name() { return process_name; };
bool wgm_processes::cooling_process::is_proc_success() { return process_feedback.report_feedback(); };
