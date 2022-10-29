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

 // idelta
wafer_holder_motion_system::Idelta_motion::Idelta_motion()
{
  std::cout << "creating Idelta motion" << std::endl;
}

wafer_holder_motion_system::Idelta_motion:: ~Idelta_motion()
{
  std::cout << "deleting Idelta motion" << std::endl;
}
// delta

wafer_holder_motion_system::delta_motion::delta_motion(std::shared_ptr<whs_controller> shared_controller)
{
  // delta
  wafer_delta_shared_ptr = shared_controller; //pass shared pointer
}


void wafer_holder_motion_system::delta_motion::move(int direction)
{
  if (direction == 1) // up
    std::cout << "move delta up" << std::endl;


  else if (direction == 0) //down
    std::cout << "move delta down" << std::endl;

  else std::cout << "direction unkown" << std::endl;
}
// idistance
wafer_holder_motion_system::Idistance_sensor::Idistance_sensor()
{
  std::cout << "creating Idistance sensor" << std::endl;
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
  return wafer_dist_shared_ptr->keyence_client_get_value_output0(); //ready
}

wafer_holder_motion_system::Iwafer_motion_controller::Iwafer_motion_controller()
{
  std::cout << "creating wafer Imotion Interface " << std::endl;
}
wafer_holder_motion_system::Iwafer_motion_controller:: ~Iwafer_motion_controller()
{
  std::cout << "deleting wafer Imotion Interface" << std::endl;
}

wafer_holder_motion_system::wafer_motion_controller::wafer_motion_controller() {
  wafer_sys_control_shared_ptr = std::make_shared<whs_controller>();
  wafer_sys_control_shared_ptr->run_delta_subprocess();

}
wafer_holder_motion_system::wafer_motion_controller:: ~wafer_motion_controller()
{
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
  wafer_sys_control_shared_ptr->move_delta_home();
}
double wafer_holder_motion_system::wafer_motion_controller::get_current_value(uint16_t sensor_head)
{
  switch (sensor_head)
  {
  case 0:
    return wafer_sys_control_shared_ptr->keyence_client_get_value_output0();
    break;
  case 1:
    return wafer_sys_control_shared_ptr->keyence_client_get_value_output1();
    break;
  case 2:
    return wafer_sys_control_shared_ptr->keyence_client_get_value_output2();
    break;
  default:
    break;
  }
}
enum_sys_feedback wafer_holder_motion_system::wafer_motion_controller::insert_wafer_in_ml()
{
  std::cout << "start sinking" << std::endl;
  enum_sub_sys_feedback delta_sub_feedback = wafer_sys_control_shared_ptr->connect_to_delta_server(); // ready
  if (delta_sub_feedback == enum_sub_sys_feedback::sub_error)
  {
    enum_sys_feedback whms_feedback = enum_sys_feedback::sys_error;
    std::cout << "error wafer holder motion system due to delta sub system connection error" << std::endl;
    std::cout << "aborting process" << std::endl;
    return whms_feedback;
  }
  enum_sub_sys_feedback Keyence_sub_feedback = wafer_sys_control_shared_ptr->keyence_client_connect();
  if (Keyence_sub_feedback == enum_sub_sys_feedback::sub_error)
  {
    enum_sys_feedback whms_feedback = enum_sys_feedback::sys_error;
    std::cout << "error wafer holder motion system due to keyence sub system connection error" << std::endl;
    std::cout << "aborting process" << std::endl;
    return whms_feedback;
  }
  wafer_sys_control_shared_ptr->move_delta_home();
  wafer_sys_control_shared_ptr->move_down_until_data_availble();
  wafer_sys_control_shared_ptr->move_down_to_surface();
  wafer_sys_control_shared_ptr->deep_wafer_holder_desired_thickness();

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
