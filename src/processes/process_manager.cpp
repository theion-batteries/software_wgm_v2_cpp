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
wgm_processes::Iprocess_manager::Iprocess_manager() {}
void wgm_processes::Iprocess_manager::add_process_to_scheduler(Iprocess_manager* process) {};
void wgm_processes::Iprocess_manager::delete_last_process_from_scheduler() {};
void wgm_processes::Iprocess_manager::stop_all() {};
void wgm_processes::Iprocess_manager::start_all() {};
wgm_processes::Iprocess_manager::~Iprocess_manager() {};

/******************** implementation process management ************/
wgm_processes::process_manager::process_manager() {
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

  /***** add extract process ***/
  Iextracting_process* extraction_proc = new extracting_process(insertion_proc->get_sys_ptr());
  processesvector.push_back(extraction_proc);
  std::cout << "added wafer extracting process to process scheduler" << std::endl;
}

wgm_processes::process_manager:: ~process_manager() {
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

void wgm_processes::process_manager::start_process()
{
  std::cout << "process started" << std::endl;
}
void wgm_processes::process_manager::stop_process()
{
  std::cout << "process stopped" << std::endl;
}
void wgm_processes::process_manager::start_process(Iprocess_manager* process)
{
  std::cout << "process "<< process->get_name()<< " started" << std::endl;
  process->start_process();
    proc_time = process->get_elapsed_time();

}
void wgm_processes::process_manager::stop_process(Iprocess_manager* process)
{
  std::cout << "process "<< process->get_name()<<" stopped" << std::endl;
  process->stop_process();
  proc_time = process->get_elapsed_time();

}


void wgm_processes::process_manager::start_process(std::string processName)
{
  auto it = std::find_if (processesvector.begin(), processesvector.end(), [processName](Iprocess_manager* proc){return proc->get_name()==processName;});
  if (it != processesvector.end())
  {
 std::cout << (*it)->get_name()<< " started" << std::endl;
  (*it)->start_process();
    proc_time = (*it)->get_elapsed_time();

  }
}
void wgm_processes::process_manager::stop_process(std::string processName)
{
   auto it = std::find_if (processesvector.begin(), processesvector.end(), [processName](Iprocess_manager* proc){return proc->get_name()==processName;});
  if (it != processesvector.end())
  {
 std::cout << (*it)->get_name()<< " started" << std::endl;
  (*it)->stop_process();
    proc_time = (*it)->get_elapsed_time();

  }
}

void wgm_processes::process_manager::start_process(int processID)
{
   auto it = std::find_if (processesvector.begin(), processesvector.end(), [processID](Iprocess_manager* proc){return proc->get_id()==processID;});
  if (it != processesvector.end())
  {
 std::cout << (*it)->get_name()<< " started" << std::endl;
  (*it)->start_process();
  proc_time = (*it)->get_elapsed_time();
  }
 
}
void wgm_processes::process_manager::stop_process(int processID)
{
   auto it = std::find_if (processesvector.begin(), processesvector.end(), [processID](Iprocess_manager* proc){return proc->get_id()==processID;});
  if (it != processesvector.end())
  {
 std::cout << (*it)->get_name()<< " started" << std::endl;
  (*it)->stop_process();
    proc_time = (*it)->get_elapsed_time();

  }
}












void wgm_processes::process_manager::start_all()
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
void wgm_processes::process_manager::stop_all()
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
void wgm_processes::process_manager::add_process_to_scheduler(Iprocess_manager* process)
{
  processesvector.push_back(process);

}
void wgm_processes::process_manager::delete_last_process_from_scheduler()
{
  processesvector.pop_back();

}
std::string wgm_processes::process_manager::get_name() { return process_name; };
bool wgm_processes::process_manager::is_proc_success() { return process_feedback.report_feedback(); };

long long wgm_processes::process_manager::get_elapsed_time()
{
return proc_time;
}
