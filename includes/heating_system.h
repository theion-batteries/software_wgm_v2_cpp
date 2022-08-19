/**
 * @file heating_system.h
 * @author sami dhiab (sami@theion.de)
 * @brief heating system package
 * @version 0.1
 * @date 2022-07-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#pragma once

namespace sulfur_heating_system
{
  /*********** heater ***************/
  class Iheater
  {
  public:
    virtual void start_heater() = 0;
    virtual void shutdown_heater() = 0;
    Iheater();
    virtual ~Iheater();
  };
  // implement
  class Heater : public Iheater
  {
  protected:
    virtual void start_heater();
    virtual void shutdown_heater();
  };
  /*********** temp sensor ************/
  class Itemperature_sensor
  {
  public:
    Itemperature_sensor();
    virtual ~Itemperature_sensor();
    virtual double get_current_value() = 0;
  };
  // implement
  class temperature_sensor : public Itemperature_sensor {
  protected:
    virtual double get_current_value();
    double current_val;
  };
  /*********** heating controller *************/
  class Isulfur_heating_controller
  {
  public:
    Isulfur_heating_controller() ;
    virtual ~Isulfur_heating_controller();
    virtual void turn_off_heating() = 0;
    virtual void controll_heating() = 0;
    virtual void turn_on_heating() = 0;
    virtual double getSensorReading() = 0;
  };
  // implement
  class sulfur_heating_controller : public Isulfur_heating_controller
  {
  private:
    Itemperature_sensor* tempe_sensor;
    Iheater* heater;

  public:
    sulfur_heating_controller();
    virtual ~sulfur_heating_controller();
    virtual double getSensorReading();
    virtual void turn_off_heating();
    virtual void turn_on_heating();
    virtual void controll_heating();

  };

}


