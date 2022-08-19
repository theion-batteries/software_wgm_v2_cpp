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


wafer_holder_motion_system::Idelta_motion::Idelta_motion()
{
  std::cout << "creating delta motion" << std::endl;
}

wafer_holder_motion_system::Idelta_motion:: ~Idelta_motion()
{
  std::cout << "deleting delta motion" << std::endl;
}

void wafer_holder_motion_system::delta_motion::move(int direction)
{
  if (direction == 1) // up
    std::cout << "move delta up" << std::endl;
  else if (direction == 0)
    std::cout << "move delta down" << std::endl;
  else std::cout << "direction unkown" << std::endl;
}
void wafer_holder_motion_system::delta_motion::set_speed_to_minimum()
{
  std::cout << "setting speed to lowest" << std::endl;
}

wafer_holder_motion_system::Idistance_sensor::Idistance_sensor()
{
  std::cout << "creating distance sensor" << std::endl;
}
wafer_holder_motion_system::Idistance_sensor:: ~Idistance_sensor()
{
  std::cout << "deleting distance sensor" << std::endl;
}
double wafer_holder_motion_system::distance_sensor::read_values()
{
  std::cout << "reading value distance sensor" << std::endl;
  return 30;
}

wafer_holder_motion_system::Iwafer_motion_controller::Iwafer_motion_controller()
{
  std::cout << "creating wafer motion controller" << std::endl;
}
wafer_holder_motion_system::Iwafer_motion_controller:: ~Iwafer_motion_controller()
{
  std::cout << "deleting wafer motion controller" << std::endl;
}

wafer_holder_motion_system::wafer_motion_controller::wafer_motion_controller() {
  delta_mover = new delta_motion();
  dist_sensor = new distance_sensor();
}
wafer_holder_motion_system::wafer_motion_controller:: ~wafer_motion_controller()
{
  delete delta_mover;
  delete dist_sensor;
}

void wafer_holder_motion_system:: wafer_motion_controller::move_down()
{
  delta_mover->move(0);
}
void wafer_holder_motion_system:: wafer_motion_controller::calibrate()
{

}
void wafer_holder_motion_system:: wafer_motion_controller::move_up()
{
  delta_mover->move(1);
}
double wafer_holder_motion_system:: wafer_motion_controller::get_current_value()
{
  return dist_sensor->read_values();
}
void wafer_holder_motion_system:: wafer_motion_controller::insert_wafer_in_ml()
{
  std::cout << "start sinking" << std::endl;
  // to start process distance must be set before
  if (distance_to_surface_contact != 0)
  {
    while (get_current_value() != distance_to_surface_contact)
    {
      if (get_current_value() == distance_to_slow_down)
      {
        slow_down();
      }
      move_down();

    }
  }
  else std::cout << "error: please set distance to surface contact with ml" << std::endl;
}
void wafer_holder_motion_system:: wafer_motion_controller::extract_wafer_from_ml()
{
  std::cout << "extracting wafer" << std::endl;
  move_up();
}
void wafer_holder_motion_system:: wafer_motion_controller::set_distance_to_surface_contact(double distance)
{
  distance_to_surface_contact = distance;
}
void wafer_holder_motion_system:: wafer_motion_controller::slow_down()
{
  std::cout << "reaching critical area, switching mode" << std::endl;
  delta_mover->set_speed_to_minimum();
}