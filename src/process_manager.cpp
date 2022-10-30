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

#include "process_manager.h"

 // process managment interface
wgm_processes::Iprocesses_managment::Iprocesses_managment() {}
void wgm_processes::Iprocesses_managment::add_process_to_scheduler(Iprocesses_managment* process) {};
void wgm_processes::Iprocesses_managment::delete_last_process_from_scheduler() {};
void wgm_processes::Iprocesses_managment::stop_all() {};
void wgm_processes::Iprocesses_managment::start_all() {};
wgm_processes::Iprocesses_managment::~Iprocesses_managment() {};

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
  auto heating_feedback = enum_sys_feedback::sys_error;
  // feedback
  if (heating_feedback == enum_sys_feedback::sys_error)
  {
    process_timer->stop_monitoring();
    process_feedback.setFeedback(wgm_feedbacks::enum_proc_feedback::proc_error);
  }
  else if (heating_feedback == enum_sys_feedback::sys_success)
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

// interface sink process
wgm_processes::Isinking_process::Isinking_process()
{

  std::cout << "creating sinking process " << std::endl;
}
wgm_processes::Isinking_process::~Isinking_process() {}

// sink process implemnt
std::string wgm_processes::sinking_process::get_name() { return process_name; };
bool wgm_processes::sinking_process::is_proc_success() { return process_feedback.report_feedback(); };

wgm_processes::sinking_process::sinking_process() {
  sinking_sys = new wafer_holder_motion_system::wafer_motion_controller();
  process_timer = new wgm_monitoring::time_monitor();
  process_dist_monitor = new wgm_monitoring::distance_monitor(sinking_sys);
}
wgm_processes::sinking_process::~sinking_process()
{
  std::cout << "deleting sinking process " << std::endl;
  delete sinking_sys;
  delete process_timer;
  delete process_dist_monitor;
}
void wgm_processes::sinking_process::start_process()
{
  std::cout << "execute " << process_name << std::endl;
  process_timer->start_monitoring();
  auto sinking_feedback = sinking_sys->insert_wafer_in_ml();
  //auto sinking_feedback = enum_sys_feedback::sys_error;
  // feedback
  if (sinking_feedback == enum_sys_feedback::sys_error)
  {
    stop_process();
    process_feedback.setFeedback(wgm_feedbacks::enum_proc_feedback::proc_error);
  }
  else if (sinking_feedback == enum_sys_feedback::sys_success)
  {
    process_feedback.setFeedback(wgm_feedbacks::enum_proc_feedback::proc_success);
    process_dist_monitor->start_monitoring();
  }
  // 

}
void wgm_processes::sinking_process::stop_process()
{
  std::cout << "finish " << process_name << std::endl;
  process_dist_monitor->stop_monitoring();
  process_timer->stop_monitoring();
}
wafer_holder_motion_system::Iwafer_motion_controller* wgm_processes::sinking_process::get_sys_obj()
{
  return sinking_sys;
}

 long wgm_processes::sinking_process::get_elapsed_time()
 {
    return process_timer->get_elapsed_time();
 }


/****************** interface cnt alignment process*******************/
wgm_processes::Ialigning_process::Ialigning_process()
{
}
wgm_processes::Ialigning_process:: ~Ialigning_process()
{
}

/******************* implementation cnt alignment process ***************/
std::string wgm_processes::aligning_process::get_name() { return process_name; };
bool wgm_processes::aligning_process::is_proc_success() { return process_feedback.report_feedback(); };


wgm_processes::aligning_process::aligning_process() {
  std::cout << "creating aligning process " << std::endl;
  aligning_sys = new cnt_alignment_system::cnt_aligning_controller();
  process_timer = new wgm_monitoring::time_monitor();
  process_curr_monitor = new wgm_monitoring::current_monitor(aligning_sys);
  process_volt_monitor = new wgm_monitoring::voltage_monitor(aligning_sys);
}
wgm_processes::aligning_process:: ~aligning_process()
{
  std::cout << "deleting aligning process " << std::endl;
  delete aligning_sys;
  delete process_timer;
  delete process_curr_monitor;
  delete process_volt_monitor;
}
void wgm_processes::aligning_process::start_process()
{
  std::cout << "execute " << process_name << std::endl;
  process_timer->start_monitoring();
  aligning_sys->start_aligning();
  // feedback
  process_timer->stop_monitoring();
  process_curr_monitor->start_monitoring();
  process_volt_monitor->start_monitoring();
}
void wgm_processes::aligning_process::stop_process()
{
  std::cout << "finish " << process_name << std::endl;
  aligning_sys->stop_aligning();
  process_curr_monitor->stop_monitoring();
  process_volt_monitor->stop_monitoring();
}

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

/******************** implementation process management ************/
wgm_processes::process_management::process_management() {
  std::cout << "creating process manager" << std::endl;
  //processes_monitor = new wgm_monitoring::monitor_managment();
  /********************* add new processes *************************/
  /***** add heating process ***/
  Iheating_process* heating_proc = new heating_process();
  processesvector.push_back(heating_proc);
  std::cout << "added heating process to process scheduler" << std::endl;

  /***** add insertion process ***/
  Isinking_process* insertion_proc = new sinking_process();
  processesvector.push_back(insertion_proc);
  std::cout << "added wafer insertion process to process scheduler" << std::endl;

  /***** add aligning process ***/
  Ialigning_process* aligning_proc = new aligning_process();
  processesvector.push_back(aligning_proc);
  std::cout << "added aligning process to process scheduler" << std::endl;

  /***** add cooling process ***/
  Icooling_process* cooling_proc = new cooling_process();
  processesvector.push_back(cooling_proc);
  std::cout << "added cooling process to process scheduler" << std::endl;

  /***** add insertion process ***/
  Iextracting_process* extraction_proc = new extracting_process(insertion_proc->get_sys_obj());
  processesvector.push_back(extraction_proc);
  std::cout << "added wafer extracting process to process scheduler" << std::endl;
}

wgm_processes::process_management:: ~process_management() {
  std::cout << "deleting process scheduler" << std::endl;
  for (auto process : processesvector)
  {
    if (process != nullptr)
    {
      delete process;
    }
    else
    {
      std::cout << "can't free memory" << std::endl;
      break;
    }
  }
}

void wgm_processes::process_management::start_process()
{
  std::cout << "process started" << std::endl;
}
void wgm_processes::process_management::stop_process()
{
  std::cout << "process stopped" << std::endl;
}
void wgm_processes::process_management::start_all()
{
  std::cout << "executing all processes" << std::endl;
  for (auto process : processesvector)
  {
    if (process != nullptr)
    {
      process->start_process();
      if (process->is_proc_success()) continue;
      break;
    }
    else std::cout << "empty process scheduler" << std::endl;
  }
}
void wgm_processes::process_management::stop_all()
{
  std::cout << "stopping all processes" << std::endl;

  for (auto process : processesvector)
  {
    if (process != nullptr)
    {
      process->stop_process();
    }
    else std::cout << "empty process scheduler" << std::endl;
  }
}
void wgm_processes::process_management::add_process_to_scheduler(Iprocesses_managment* process)
{
  processesvector.push_back(process);

}
void wgm_processes::process_management::delete_last_process_from_scheduler()
{
  processesvector.pop_back();

}
std::string wgm_processes::process_management::get_name() { return process_name; };
bool wgm_processes::process_management::is_proc_success() { return process_feedback.report_feedback(); };
