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
wgm_processes::Iprocess_manager::Iprocess_manager() {}
void wgm_processes::Iprocess_manager::add_process_to_scheduler(Iprocess_manager* process) {};
void wgm_processes::Iprocess_manager::delete_last_process_from_scheduler() {};
void wgm_processes::Iprocess_manager::stop_all() {};
void wgm_processes::Iprocess_manager::start_all(std::function<void(int)> callback) {};
wgm_processes::Iprocess_manager::~Iprocess_manager() {};

/******************** implementation process management ************/
wgm_processes::process_manager::process_manager() {
  std::cout << "creating process manager" << "\n";
  //processes_monitor = new wgm_monitoring::monitor_managment();
  /********************* add new processes *************************/
  /***** add heating process ***/
  Iheating_process* heating_proc = new heating_process();
  processesvector.push_back(heating_proc);
  std::cout << "added heating process to process scheduler" << "\n";

  /***** add insertion process ***/
  Isinking_process* insertion_proc = new sinking_process();
  processesvector.push_back(insertion_proc);
  std::cout << "added wafer insertion process to process scheduler" << "\n";

  /***** add aligning process ***/
  Ialigning_process* aligning_proc = new aligning_process();
  processesvector.push_back(aligning_proc);
  std::cout << "added aligning process to process scheduler" << "\n";

  /***** add cooling process ***/
  Icooling_process* cooling_proc = new cooling_process();
  processesvector.push_back(cooling_proc);
  std::cout << "added cooling process to process scheduler" << "\n";

  /***** add extract process ***/
  Iextracting_process* extraction_proc = new extracting_process(insertion_proc->get_sys_ptr());
  processesvector.push_back(extraction_proc);
  std::cout << "added wafer extracting process to process scheduler" << "\n";
}

wgm_processes::process_manager:: ~process_manager() {
  std::cout << "deleting process scheduler" << "\n";
  for (auto process : processesvector)
  {
    if (process != nullptr)
    {
      delete process;
    }
    else
    {
      std::cout << "can't free memory" << "\n";
      break;
    }
  }
}

wgm_feedbacks::enum_proc_feedback wgm_processes::process_manager::start_process()
{
  std::cout << "process started" << "\n";
  return wgm_feedbacks::enum_proc_feedback::proc_success;

}
wgm_feedbacks::enum_proc_feedback wgm_processes::process_manager::stop_process()
{
  std::cout << "process stopped" << "\n";
  return wgm_feedbacks::enum_proc_feedback::proc_success;
}
void wgm_processes::process_manager::start_process(Iprocess_manager* process)
{
  std::cout << "process " << process->get_name() << " started" << "\n";
  process->start_process();
  proc_time = process->get_elapsed_time();

}
void wgm_processes::process_manager::stop_process(Iprocess_manager* process)
{
  std::cout << "process " << process->get_name() << " stopped" << "\n";
  process->stop_process();
  proc_time = process->get_elapsed_time();

}


void wgm_processes::process_manager::start_process(std::string processName)
{
  auto it = std::find_if(processesvector.begin(), processesvector.end(), [processName](Iprocess_manager* proc) {return proc->get_name() == processName;});
  if (it != processesvector.end())
  {
    std::cout << (*it)->get_name() << " started" << "\n";
    (*it)->start_process();
    proc_time = (*it)->get_elapsed_time();

  }
}
void wgm_processes::process_manager::stop_process(std::string processName)
{
  auto it = std::find_if(processesvector.begin(), processesvector.end(), [processName](Iprocess_manager* proc) {return proc->get_name() == processName;});
  if (it != processesvector.end())
  {
    std::cout << (*it)->get_name() << " started" << "\n";
    (*it)->stop_process();
    proc_time = (*it)->get_elapsed_time();

  }
}

void wgm_processes::process_manager::start_process(int processID)
{
  auto it = std::find_if(processesvector.begin(), processesvector.end(), [processID](Iprocess_manager* proc) {return proc->get_id() == processID;});
  if (it != processesvector.end())
  {
    std::cout << (*it)->get_name() << " started" << "\n";
    (*it)->start_process();
    proc_time = (*it)->get_elapsed_time();
  }

}
void wgm_processes::process_manager::stop_process(int processID)
{
  auto it = std::find_if(processesvector.begin(), processesvector.end(), [processID](Iprocess_manager* proc) {return proc->get_id() == processID;});
  if (it != processesvector.end())
  {
    std::cout << (*it)->get_name() << " started" << "\n";
    (*it)->stop_process();
    proc_time = (*it)->get_elapsed_time();

  }
}












void wgm_processes::process_manager::start_all(std::function<void(int)> callback)
{
  proc_time = 0;
  std::cout << "executing all processes" << "\n";
  for (auto process : processesvector)
  {
    if (process != nullptr)
    {
      if (process->start_process() == wgm_feedbacks::enum_proc_feedback::proc_error)
      {
        callback(process->get_id());
        proc_time += process->get_elapsed_time();
        break;
      }
      callback(process->get_id());
      proc_time += process->get_elapsed_time();
    }
    else std::cout << "empty process scheduler" << "\n";
  }
}
void wgm_processes::process_manager::stop_all()
{
  std::cout << "stopping all processes" << "\n";

  for (auto process : processesvector)
  {
    if (process != nullptr)
    {
      process->stop_process();
    }
    else std::cout << "empty process scheduler" << "\n";
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
