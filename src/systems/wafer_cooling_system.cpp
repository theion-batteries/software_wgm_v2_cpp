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
wafer_cooling_system::Icooling_rotation::Icooling_rotation()
{
  std::cout << "creating cooling rotation " << std::endl;
}

wafer_cooling_system::Icooling_rotation::~Icooling_rotation()
{
  std::cout << "deleting cooling rotation " << std::endl;
}

void wafer_cooling_system::cooling_rotation::ph_rotate()
{
  std::cout << "start rotating " << std::endl;
}

wafer_cooling_system::Icooling_motion::Icooling_motion()
{
  std::cout << "creating cooling motion" << std::endl;
}
wafer_cooling_system::Icooling_motion::~Icooling_motion()
{
  std::cout << "deleting cooling motion" << std::endl;
}

void wafer_cooling_system::cooling_motion::move_down_to_center()
{
  std::cout << "cooling sys moving down to center" << std::endl;

}
void wafer_cooling_system::cooling_motion::move_up_to_reference()
{
  std::cout << "cooling sys moving back to refernce " << std::endl;

}

wafer_cooling_system::Icooling_spitting::Icooling_spitting()
{
  std::cout << "creating cooling printing" << std::endl;
}
wafer_cooling_system::Icooling_spitting::  ~Icooling_spitting()
{
  std::cout << "deleting cooling printing" << std::endl;
}


void wafer_cooling_system::cooling_spitting::ph_spit()
{
  std::cout << "printhead spitting" << std::endl;

}

wafer_cooling_system::Icooling_controller::Icooling_controller()
{
  std::cout << "creating cooling controller" << std::endl;
}
wafer_cooling_system::Icooling_controller::  ~Icooling_controller()
{
  std::cout << "deleting cooling controller" << std::endl;
}

wafer_cooling_system::cooling_controller::cooling_controller()
{
  ph_sys_control_shared_ptr = std::make_shared<ph_cooling_controller>();
  ph_motion = new cooling_motion();
  ph_rotation = new cooling_rotation();
  ph_printing = new cooling_spitting();
}

wafer_cooling_system::cooling_controller:: ~cooling_controller()
{
  delete ph_motion;
  delete ph_rotation;
  delete ph_printing;
}

void wafer_cooling_system::cooling_controller::start_cooling()
{
  ph_motion->move_down_to_center();
  ph_rotation->ph_rotate();
  ph_printing->ph_spit();
}
void wafer_cooling_system::cooling_controller::stop_cooling()
{
  ph_motion->move_up_to_reference();
}


void wafer_cooling_system::cooling_controller::connect_rotation_axis()
{
  ph_sys_control_shared_ptr->get_rotary_axis_ptr()->connect();
}
void wafer_cooling_system::cooling_controller::connect_motion_axis()
{
  ph_sys_control_shared_ptr->get_axis_ptr()->connect();
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
