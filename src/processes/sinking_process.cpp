
#include "sinking_process.h"

// interface sink process
wgm_processes::Isinking_process::Isinking_process()
{

  std::cout << "creating sinking process " << std::endl;
}
wgm_processes::Isinking_process::~Isinking_process() {}

/******************* implementation sinking process ***************/

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
wgm_feedbacks::enum_proc_feedback wgm_processes::sinking_process::start_process()
{
  std::cout << "execute " << process_name << std::endl;
  process_timer->start_monitoring();
  //auto sinking_feedback = sinking_sys->insert_wafer_in_ml();
  ////auto sinking_feedback = wgm_feedbacks::enum_sys_feedback::sys_error;
  //// feedback
  //if (sinking_feedback == wgm_feedbacks::enum_sys_feedback::sys_error)
  //{
  //  stop_process();
  //  process_feedback.setFeedback(wgm_feedbacks::enum_proc_feedback::proc_error);
//
  //}
  //else if (sinking_feedback == wgm_feedbacks::enum_sys_feedback::sys_success)
  //{
  //  process_feedback.setFeedback(wgm_feedbacks::enum_proc_feedback::proc_success);
  //  process_dist_monitor->start_monitoring();
  //}
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

  process_timer->stop_monitoring();

  return wgm_feedbacks::enum_proc_feedback::proc_success;

}
void wgm_processes::sinking_process::stop_process()
{
  std::cout << "stopping " << process_name << std::endl;
  process_dist_monitor->stop_monitoring();
  process_timer->stop_monitoring();
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
