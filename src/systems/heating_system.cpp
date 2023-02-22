/**
 * @file heating_system.cpp
 * @author sami dhiab (sami@theion.de)
 * @brief heating system package
 * @version 0.1
 * @date 2022-07-04
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "heating_system.h"


sulfur_heating_system::Isulfur_heating_controller::Isulfur_heating_controller()
{
}
sulfur_heating_system::Isulfur_heating_controller::~Isulfur_heating_controller()
{
}
sulfur_heating_system::sulfur_heating_controller::sulfur_heating_controller() 
{
  std::cout << "creating heating controller" << std::endl;
    registerAlgorithms();

}
sulfur_heating_system::sulfur_heating_controller::~sulfur_heating_controller()
{
  std::cout << "deleting heating controller" << std::endl;

}
double sulfur_heating_system::sulfur_heating_controller::getSulfurTemperatur()
{
  std::cout << "controller get sulfur temp value" << std::endl;
  return heatControl.get_heating_sulfur_temperature();
}
void sulfur_heating_system::sulfur_heating_controller::setSulfurTemperatur(double targetTemp)
{
  std::cout << "controller get sulfur temp value" << std::endl;
   heatControl.heating_controller_settemperature( targetTemp);
}
void sulfur_heating_system::sulfur_heating_controller::turn_off_heating()
{
  std::cout << "controller turn off heater" << std::endl;
  heatControl.heating_controller_deactivate();
}

void sulfur_heating_system::sulfur_heating_controller::turn_on_heating()
{
  std::cout << "controller turn on heater " << std::endl;
  heatControl.heating_controller_activate();
}

void sulfur_heating_system::sulfur_heating_controller::controll_heating()
{
  std::cout << "controller regulate" << std::endl;
  getSulfurTemperatur();
}

heating_controller& sulfur_heating_system::sulfur_heating_controller::getSubSysController()
{
  return heatControl;
}
bool sulfur_heating_system::sulfur_heating_controller::getSubSysStatus(std::string Subsystem)
{
 if (Subsystem == "controller") return heatControl.get_heating_controller_status();
 return false;
}

wgm_feedbacks::enum_sys_feedback sulfur_heating_system::sulfur_heating_controller::start_heating_sys() 
{
    stopped = false;

  std::cout << "start heating algorithms" << std::endl;
  for ( auto & algo: heatAlgorithms)
  {
    if (algo() == sub_error || stopped) return sys_error;
  }
return wgm_feedbacks::enum_sys_feedback::sys_success;
}
wgm_feedbacks::enum_sys_feedback sulfur_heating_system::sulfur_heating_controller::stop_heating_sys() 
{
  stopped = true;
  return sys_error;
}

void sulfur_heating_system::sulfur_heating_controller::registerAlgorithms()
{
  heatAlgorithms.push_back(std::bind(&heating_controller::heating_controller_connect, &heatControl));
  heatAlgorithms.push_back(std::bind(&heating_controller::heating_controller_activate, &heatControl));
}
