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
#include "heating_process.h"
#include "sinking_process.h"
#include "aligning_process.h"
#include "cooling_process.h"
#include "extracting_process.h"

 // process managment interface
wgm_processes::Iprocesses_managment::Iprocesses_managment() {}
void wgm_processes::Iprocesses_managment::add_process_to_scheduler(Iprocesses_managment* process) {};
void wgm_processes::Iprocesses_managment::delete_last_process_from_scheduler() {};
void wgm_processes::Iprocesses_managment::stop_all() {};
void wgm_processes::Iprocesses_managment::start_all() {};
wgm_processes::Iprocesses_managment::~Iprocesses_managment() {};

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
  Iextracting_process* extraction_proc = new extracting_process(insertion_proc->get_sys_ptr());
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
