
#include "sinking_process.h"

// interface sink process
wgm_processes::Isinking_process::Isinking_process()
{

  std::cout << "creating sinking process " << "\n";
}
wgm_processes::Isinking_process::~Isinking_process() {}

/******************* implementation sinking process ***************/

wgm_processes::sinking_process::sinking_process() {
  sinking_sys = new wafer_holder_motion_system::wafer_motion_controller();
  process_timer = new wgm_monitoring::time_monitor();
}
wgm_processes::sinking_process::~sinking_process()
{
  std::cout << "deleting sinking process " << "\n";
  delete sinking_sys;
  delete process_timer;
}
wgm_feedbacks::enum_proc_feedback wgm_processes::sinking_process::start_process()
{
  std::cout << "execute " << process_name << "\n";
  process_timer->start_monitoring();
  if (sinking_sys->start_sinking() == sys_error)
  {
    process_timer->stop_monitoring();
    return proc_error;
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  process_timer->stop_monitoring();
  return proc_success;
}
wgm_feedbacks::enum_proc_feedback wgm_processes::sinking_process::stop_process()
{
  std::cout << "stopping " << process_name << "\n";
sinking_sys->stop_sinking();
  process_timer->stop_monitoring();
  return proc_error;
}
wafer_holder_motion_system::Iwafer_motion_controller* wgm_processes::sinking_process::get_sys_ptr()
{
  return sinking_sys;
}

long long wgm_processes::sinking_process::get_elapsed_time()
{
  return process_timer->get_elapsed_time();
}


// sink process implemnt
std::string wgm_processes::sinking_process::get_name() { return process_name; };
bool wgm_processes::sinking_process::is_proc_success() { return process_feedback.report_feedback(); };
