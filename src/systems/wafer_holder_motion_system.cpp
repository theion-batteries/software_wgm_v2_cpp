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

// axis motion

 // Iaxis
wafer_holder_motion_system::Iaxis_motion::Iaxis_motion()
{
  std::cout << "creating system Iaxis motion" << std::endl;
}

wafer_holder_motion_system::Iaxis_motion:: ~Iaxis_motion()
{
  std::cout << "deleting Iaxis motion" << std::endl;
}
// axis

wafer_holder_motion_system::axis_motion::axis_motion(std::shared_ptr<whs_controller> shared_controller)
{
  // axis
  wafer_motion_shared_ptr = shared_controller; //pass shared pointer
}


void wafer_holder_motion_system::axis_motion::move(int direction)
{
  if (direction == 1) // up
    std::cout << "move axis up" << std::endl;


  else if (direction == 0) //down
    std::cout << "move axis down" << std::endl;

  else std::cout << "direction unkown" << std::endl;
}


// idistance
wafer_holder_motion_system::Idistance_sensor::Idistance_sensor()
{
  std::cout << "creating system Idistance sensor" << std::endl;
}
wafer_holder_motion_system::Idistance_sensor:: ~Idistance_sensor()
{
  std::cout << "deleting Idistance sensor" << std::endl;
}

// distance_sensor
wafer_holder_motion_system::distance_sensor::distance_sensor(std::shared_ptr<whs_controller> shared_controller)
{
  // keyence
  wafer_dist_shared_ptr = shared_controller; //pass shared pointer
}
double wafer_holder_motion_system::distance_sensor::read_values()
{
  std::cout << "reading value distance sensor" << std::endl;
  return wafer_dist_shared_ptr->get_sensor_values(); //ready
}

wafer_holder_motion_system::Iwafer_motion_controller::Iwafer_motion_controller()
{
  std::cout << "creating system wafer Imotion Interface " << std::endl;
}
wafer_holder_motion_system::Iwafer_motion_controller:: ~Iwafer_motion_controller()
{
  std::cout << "deleting wafer Imotion Interface" << std::endl;

}

wafer_holder_motion_system::wafer_motion_controller::wafer_motion_controller() {
  wafer_sys_control_shared_ptr = std::make_shared<whs_controller>();
  axis_mover = std::make_unique< axis_motion>(wafer_sys_control_shared_ptr);
  dist_sensor = std::make_unique< distance_sensor>(wafer_sys_control_shared_ptr);

}
wafer_holder_motion_system::wafer_motion_controller:: ~wafer_motion_controller()
{
}

void wafer_holder_motion_system::wafer_motion_controller::connect_sensor()
{
  wafer_sys_control_shared_ptr->get_dist_ptr()->connect();
}
void wafer_holder_motion_system::wafer_motion_controller::move_down()
{

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
  return      wafer_sys_control_shared_ptr->get_dist_ptr()->getMesuredValue();
}
wgm_feedbacks::enum_sys_feedback wafer_holder_motion_system::wafer_motion_controller::insert_wafer_in_ml()
{
  std::cout << "start sinking" << std::endl;
  wgm_feedbacks::enum_sub_sys_feedback delta_sub_feedback = wafer_sys_control_shared_ptr->get_axis_ptr()->connect(); 
  if (delta_sub_feedback == wgm_feedbacks::enum_sub_sys_feedback::sub_error)
  {
    wgm_feedbacks::enum_sys_feedback whms_feedback = wgm_feedbacks::enum_sys_feedback::sys_error;
    std::cout << "error wafer holder motion system due to axis motion sub system connection error" << std::endl;
    std::cout << "aborting process" << std::endl;
    return whms_feedback;
  }
  wgm_feedbacks::enum_sub_sys_feedback Keyence_sub_feedback = wafer_sys_control_shared_ptr->get_dist_ptr()->connect();
  if (Keyence_sub_feedback == wgm_feedbacks::enum_sub_sys_feedback::sub_error)
  {
    wgm_feedbacks::enum_sys_feedback whms_feedback = wgm_feedbacks::enum_sys_feedback::sys_error;
    std::cout << "error wafer holder motion system due to sensor distance sub system connection error" << std::endl;
    std::cout << "aborting process" << std::endl;
    return whms_feedback;
  }
  wafer_sys_control_shared_ptr->get_axis_ptr()->move_home();
  wafer_sys_control_shared_ptr->move_down_until_data_availble();
  wafer_sys_control_shared_ptr->move_down_to_surface();
  wafer_sys_control_shared_ptr->deep_wafer_holder_desired_thickness();
  return wgm_feedbacks::enum_sys_feedback::sys_success;
  
  }
void wafer_holder_motion_system::wafer_motion_controller::extract_wafer_from_ml()
{
  std::cout << "extracting wafer" << std::endl;
  move_up();
}
void wafer_holder_motion_system::wafer_motion_controller::set_distance_to_surface_contact(double distance)
{
  distance_to_surface_contact = distance;
}


bool wafer_holder_motion_system::wafer_motion_controller::getSubSysStatus(std::string Subsystem)
{
  if (Subsystem == "axis_motion") return wafer_sys_control_shared_ptr->get_axis_ptr()->getStatus();
  else if (Subsystem == "distance_sensor") return wafer_sys_control_shared_ptr->get_dist_ptr()->getStatus();
  else if (Subsystem == "controller") return wafer_sys_control_shared_ptr->get_whs_controller_status();
}

std::shared_ptr<whs_controller> wafer_holder_motion_system::wafer_motion_controller::getSubSysController()
{
  return wafer_sys_control_shared_ptr;
}