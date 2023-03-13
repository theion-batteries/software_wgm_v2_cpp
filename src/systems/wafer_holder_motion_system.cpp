/**
 * @file wafer_holder_motion_system.cpp
 * @author sami dhiab (sami@theion.de)
 * @brief wafer motion system package
 * @version 0.1
 * @date 2022-07-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "wafer_holder_motion_system.h"


wafer_holder_motion_system::Iwafer_motion_controller::Iwafer_motion_controller()
{
  std::cout << "creating system wafer Imotion Interface " << "\n";
}
wafer_holder_motion_system::Iwafer_motion_controller:: ~Iwafer_motion_controller()
{
  std::cout << "deleting wafer Imotion Interface" << "\n";

}

wafer_holder_motion_system::wafer_motion_controller::wafer_motion_controller() {
  wafer_sys_control_shared_ptr = std::make_shared<whs_controller>();
  registerAlgorithms();
}
wafer_holder_motion_system::wafer_motion_controller:: ~wafer_motion_controller()
{
}
wgm_feedbacks::enum_sys_feedback wafer_holder_motion_system::wafer_motion_controller::start_sinking()
{
    stopped = false;

  std::cout << "start sinking algorithms" << "\n";
  for (auto& algo : whsAlgorithms)
  {
    if (algo() == sub_error || stopped) return sys_error;
  }
  return sys_success;
}
wgm_feedbacks::enum_sys_feedback wafer_holder_motion_system::wafer_motion_controller::stop_sinking()
{
  stopped = true;
  return sys_error;
}
wgm_feedbacks::enum_sys_feedback wafer_holder_motion_system::wafer_motion_controller::start_extracting()
{
    stopped = false;
  std::cout << "start extracting algorithms" << "\n";
  if (whsAlgorithms[1]() != sub_success || stopped) return sys_error;
  return sys_success;

}
wgm_feedbacks::enum_sys_feedback wafer_holder_motion_system::wafer_motion_controller::stop_extracting()
{
  stopped = true;
  return sys_error;
}
wgm_feedbacks::enum_sys_feedback wafer_holder_motion_system::wafer_motion_controller::insert_wafer_in_ml()
{
  std::cout << "start sinking algorithms" << "\n";
  for (auto& algo : whsAlgorithms)
  {
    if (algo() == sub_error || stopped) return sys_error;
  }
  return sys_success;
}
wgm_feedbacks::enum_sys_feedback wafer_holder_motion_system::wafer_motion_controller::extract_wafer_from_ml()
{
  std::cout << "extracting wafer" << "\n";
  if (whsAlgorithms[1]() != sub_success) return sys_error;
  return sys_success;
}

void wafer_holder_motion_system::wafer_motion_controller::connect_sensor()
{
  wafer_sys_control_shared_ptr->get_dist_ptr()->connect();
}

void wafer_holder_motion_system::wafer_motion_controller::connect_motion_axis()
{
  wafer_sys_control_shared_ptr->get_axis_ptr()->connect();
}

void wafer_holder_motion_system::wafer_motion_controller::calibrate()
{
  wafer_sys_control_shared_ptr->monitor_and_calibrate();
}
void wafer_holder_motion_system::wafer_motion_controller::move_up()
{
  wafer_sys_control_shared_ptr->get_axis_ptr()->move_home();
}
double wafer_holder_motion_system::wafer_motion_controller::get_current_value(uint16_t sensor_head)
{
  return wafer_sys_control_shared_ptr->get_dist_ptr()->getMesuredValue();
}


bool wafer_holder_motion_system::wafer_motion_controller::getSubSysStatus(std::string Subsystem)
{
  if (Subsystem == "axis_motion") return wafer_sys_control_shared_ptr->get_axis_ptr()->getStatus();
  else if (Subsystem == "distance_sensor") return wafer_sys_control_shared_ptr->get_dist_ptr()->getStatus();
  else if (Subsystem == "controller") return wafer_sys_control_shared_ptr->get_whs_controller_status();
  else return false;
}

std::shared_ptr<whs_controller> wafer_holder_motion_system::wafer_motion_controller::getSubSysController()
{
  return wafer_sys_control_shared_ptr;
}

void wafer_holder_motion_system::wafer_motion_controller::registerAlgorithms()
{

  whsAlgorithms.push_back(std::bind(&whs_controller::connect_controller, wafer_sys_control_shared_ptr));
  whsAlgorithms.push_back(std::bind(&whs_controller::extract_move_home, wafer_sys_control_shared_ptr));
  whsAlgorithms.push_back(std::bind(&whs_controller::move_down_until_data_availble, wafer_sys_control_shared_ptr));
  whsAlgorithms.push_back(std::bind(&whs_controller::move_down_to_surface, wafer_sys_control_shared_ptr));
  whsAlgorithms.push_back(std::bind(&whs_controller::deep_wafer_holder_desired_thickness, wafer_sys_control_shared_ptr));
  whsAlgorithms.push_back(std::bind(&whs_controller::monitor_and_calibrate, wafer_sys_control_shared_ptr));

}