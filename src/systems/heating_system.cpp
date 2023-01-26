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

sulfur_heating_system::Iheater::Iheater()
{
  std::cout << "creating heater" << std::endl;
}

sulfur_heating_system::Iheater::~Iheater()
{
  std::cout << "deleting heater" << std::endl;
}

void sulfur_heating_system::Heater::start_heater()
{
  std::cout << "starting heater" << std::endl;
}
void sulfur_heating_system::Heater::shutdown_heater()
{
  std::cout << "stopping heater" << std::endl;
}

sulfur_heating_system::Itemperature_sensor::Itemperature_sensor()
{
  std::cout << "creating temp sensor" << std::endl;
}
sulfur_heating_system::Itemperature_sensor::~Itemperature_sensor()
{
  std::cout << "deleting temp sensor" << std::endl;
}
double sulfur_heating_system::temperature_sensor::get_current_value()
{
  std::cout << "reading value temp sensor" << std::endl;
  return current_val;
}

sulfur_heating_system::Isulfur_heating_controller::Isulfur_heating_controller()
{
  std::cout << "creating heating controller" << std::endl;
}
sulfur_heating_system::Isulfur_heating_controller::~Isulfur_heating_controller()
{
  std::cout << "deleting heating controller" << std::endl;
}
sulfur_heating_system::sulfur_heating_controller::sulfur_heating_controller() {
  tempe_sensor = new temperature_sensor();
  heater = new Heater();
}
sulfur_heating_system::sulfur_heating_controller::~sulfur_heating_controller()
{
  delete heater;
  delete tempe_sensor;
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

heating_controller sulfur_heating_system::sulfur_heating_controller::getSubSysController()
{
  return heatControl;
}
bool sulfur_heating_system::sulfur_heating_controller::getSubSysStatus(std::string Subsystem)
{
 if (Subsystem == "controller") return heatControl.get_heating_controller_status();
  else return false;
}
