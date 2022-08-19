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
    Iheater()
    {
      std::cout << "creating heater" << std::endl;
    }

    virtual ~Iheater()
    {
      std::cout << "deleting heater" << std::endl;
    }
  };
  // implement
  class Heater : public Iheater
  {
  protected:
    virtual void start_heater();
    virtual void shutdown_heater();
  };
  void Heater::start_heater()
  {
    std::cout << "starting heater" << std::endl;
  }
  void Heater::shutdown_heater()
  {
    std::cout << "stopping heater" << std::endl;
  }
  /*********** temp sensor ************/
  class Itemperature_sensor
  {
  public:
    Itemperature_sensor()
    {
      std::cout << "creating temp sensor" << std::endl;
    }
    virtual ~Itemperature_sensor()
    {
      std::cout << "deleting temp sensor" << std::endl;
    }
    virtual double get_current_value() = 0;
  };
  // implement
  class temperature_sensor : public Itemperature_sensor {
  protected:
    virtual double get_current_value();
    double current_val;
  };
  double temperature_sensor::get_current_value()
  {
    std::cout << "reading value temp sensor" << std::endl;
    return current_val;
  }
  /*********** heating controller *************/
  class Isulfur_heating_controller
  {
  public:
    Isulfur_heating_controller() 
    {
      std::cout << "creating heating controller" << std::endl;
    }
    virtual ~Isulfur_heating_controller()
    {
      std::cout << "deleting heating controller" << std::endl;
    }
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
    sulfur_heating_controller() {
      tempe_sensor = new temperature_sensor();
      heater = new Heater();
    }
    virtual ~sulfur_heating_controller()
    {
      delete heater;
      delete tempe_sensor;
    }
    virtual double getSensorReading();
    virtual void turn_off_heating();
    virtual void turn_on_heating();
    virtual void controll_heating();

  };

  double sulfur_heating_controller::getSensorReading()
  {
    std::cout << "controller get sensor value" << std::endl;
    return tempe_sensor->get_current_value();
  }

  void sulfur_heating_controller::turn_off_heating()
  {
    std::cout << "controller turn off heater" << std::endl;
    heater->shutdown_heater();
  }

  void sulfur_heating_controller::turn_on_heating()
  {
    std::cout << "controller turn on heater " << std::endl;
    heater->start_heater();
  }

  void sulfur_heating_controller::controll_heating()
  {
    std::cout << "controller regulate" << std::endl;
    getSensorReading();
  }

}

/*********** client **********************/
class client {
private:
  sulfur_heating_system::Isulfur_heating_controller* controllerInterface;

public:
  client()
  {
    std::cout << "user started heating system" << std::endl;

    controllerInterface = new sulfur_heating_system::sulfur_heating_controller();
  }
  void run_heating_system()
  {
    controllerInterface->turn_on_heating();
    controllerInterface->controll_heating();
  }
  void close_heating_system()
  {
    controllerInterface->turn_off_heating();
  }
  ~client()
  {
    std::cout << "user stopped heating system" << std::endl;
    delete controllerInterface;
  }
};

