/**
 * @file cnt_alignment_system.cpp
 * @author sami dhiab (sami@theion.de)
 * @brief cnt alignment system package
 * @version 0.1
 * @date 2022-07-04
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "cnt_alignment_system.h"

/*********** cnt controller ************/
cnt_alignment_system::cnt_aligning_controller::cnt_aligning_controller()
{
    std::cout << "creating cnt system " << std::endl;

    registerAlgorithms();

}
cnt_alignment_system::cnt_aligning_controller:: ~cnt_aligning_controller()
{
    std::cout << "deleting cnt system" << std::endl;

}
// methods implmenetation
wgm_feedbacks::enum_sys_feedback cnt_alignment_system::cnt_aligning_controller::start_aligning()
{
  stopped = false;
  std::cout << "start aligning algorithms" << std::endl;
  for ( auto & algo: cntAlgorithms)
  {
    if (algo() == sub_error || stopped) return sys_error;
  }
  return sys_success;
}

wgm_feedbacks::enum_sys_feedback cnt_alignment_system::cnt_aligning_controller::stop_aligning()
{
  stopped = true;
  return sys_error;

}

void cnt_alignment_system::cnt_aligning_controller::connect_dispenser()
{
  controller.cnt_dispenser_connect();
}
void cnt_alignment_system::cnt_aligning_controller::connect_motion_axis()
{
  controller.cnt_motion_connect();
}
void cnt_alignment_system::cnt_aligning_controller::connect_hv()
{
  controller.cnt_hvac_connect();
}
cnt_controller& cnt_alignment_system::cnt_aligning_controller::getSubSysController()
{
  return controller;
}
bool cnt_alignment_system::cnt_aligning_controller::getSubSysStatus(std::string Subsystem)
{
  if (Subsystem == "axis_motion") return controller.get_motion_status();
  else if (Subsystem == "dispenser") return controller.get_dispenser_status();
  else if (Subsystem == "hv") return controller.get_hvac_status();
  else if (Subsystem == "controller") return controller.get_cnt_controller_status();
  else return false;
}

void cnt_alignment_system::cnt_aligning_controller::registerAlgorithms()
{
  cntAlgorithms.push_back(std::bind(&cnt_controller::cnt_controller_connect, &controller));
  cntAlgorithms.push_back(std::bind(&cnt_controller::cnt_motion_move_home, &controller));
  cntAlgorithms.push_back(std::bind(&cnt_controller::cnt_motion_move_target_position, &controller));
  cntAlgorithms.push_back(std::bind(&cnt_controller::cnt_dispenser_activate, &controller));
  cntAlgorithms.push_back(std::bind(&cnt_controller::hvac_start, &controller));
  cntAlgorithms.push_back(std::bind(&cnt_controller::hvac_stop, &controller));
  cntAlgorithms.push_back(std::bind(&cnt_controller::cnt_dispenser_deactivate, &controller));
  cntAlgorithms.push_back(std::bind(&cnt_controller::cnt_motion_move_home, &controller));
// TODO disconnect
}
