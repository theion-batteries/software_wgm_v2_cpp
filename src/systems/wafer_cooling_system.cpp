/**
 * @file wafer_cooling_system.cpp
 * @author sami dhiab (sami@theion.de)
 * @brief wafer cooling system package
 * @version 0.1
 * @date 2022-07-04
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "wafer_cooling_system.h"
using enum wgm_feedbacks::enum_sys_feedback;
using enum wgm_feedbacks::enum_sub_sys_feedback;

wafer_cooling_system::Icooling_controller::Icooling_controller()
{
  std::cout << "creating cooling controller" << "\n";
}
wafer_cooling_system::Icooling_controller::  ~Icooling_controller()
{
  std::cout << "deleting cooling controller" << "\n";
}

wafer_cooling_system::cooling_controller::cooling_controller()
{
  ph_sys_control_shared_ptr = std::make_shared<ph_cooling_controller>();
      registerAlgorithms();

}

wafer_cooling_system::cooling_controller:: ~cooling_controller()
{

}

wgm_feedbacks::enum_sys_feedback wafer_cooling_system::cooling_controller::start_cooling()
{
  stopped = false;
    std::cout << "start cooling algorithms" << "\n";

  for ( auto & algo: phAlgorithms)
  {
    if (algo() == sub_error || stopped) return sys_error;
  }
  return sys_success;
}
wgm_feedbacks::enum_sys_feedback wafer_cooling_system::cooling_controller::stop_cooling()
{
  stopped = true;
  return sys_error;}

void wafer_cooling_system::cooling_controller::connect_ph_trigger()
{
  ph_sys_control_shared_ptr->get_trigger_ptr()->connect();
}
void wafer_cooling_system::cooling_controller::connect_xy_motion_axis()
{
  ph_sys_control_shared_ptr->get_xy_axis_ptr()->connect();
}
void wafer_cooling_system::cooling_controller::connect_ph()
{
  ph_sys_control_shared_ptr->get_ph_ptr()->connect();
}
std::shared_ptr<ph_cooling_controller> wafer_cooling_system::cooling_controller::getSubSysController()
{
  return ph_sys_control_shared_ptr;
}
bool wafer_cooling_system::cooling_controller::getSubSysStatus(std::string Subsystem)
{
  if (Subsystem == "axis_motion") return ph_sys_control_shared_ptr->get_linear_mover_status();
  else if (Subsystem == "rotation_motion") return ph_sys_control_shared_ptr->get_linear_mover_status();
  else if (Subsystem == "ph") return ph_sys_control_shared_ptr->get_ph_status();
  else if (Subsystem == "controller") return ph_sys_control_shared_ptr->get_ph_cooling_controller_status();
  else return false;
}



void wafer_cooling_system::cooling_controller::registerAlgorithms()
{
  phAlgorithms.push_back(std::bind(&ph_cooling_controller::ph_controller_connect, ph_sys_control_shared_ptr));
  phAlgorithms.push_back(std::bind(&ph_cooling_controller::ph_motion_home_all, ph_sys_control_shared_ptr));
  phAlgorithms.push_back(std::bind(&ph_cooling_controller::ph_motion_move_offset,ph_sys_control_shared_ptr, 50));
  phAlgorithms.push_back(std::bind(&ph_cooling_controller::ph_rotate_to,ph_sys_control_shared_ptr,90));
  phAlgorithms.push_back(std::bind(&ph_cooling_controller::ph_motion_move_offset,ph_sys_control_shared_ptr,135));
  phAlgorithms.push_back(std::bind(&ph_cooling_controller::ph_rotate_and_print, ph_sys_control_shared_ptr));
  phAlgorithms.push_back(std::bind(&ph_cooling_controller::ph_motion_home_all, ph_sys_control_shared_ptr));
  phAlgorithms.push_back(std::bind(&ph_cooling_controller::ph_motion_move_offset, ph_sys_control_shared_ptr,2));
// TODO disconnect
}
