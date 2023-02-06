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
#pragma once

#include <iostream>
#include "system_feedback.h"
#include "heating_controller.h"
#include <functional>
using enum wgm_feedbacks::enum_sys_feedback;
using enum wgm_feedbacks::enum_sub_sys_feedback;
namespace sulfur_heating_system
{
  /*********** heating controller *************/
  class Isulfur_heating_controller
  {
  public:
    Isulfur_heating_controller();
    virtual ~Isulfur_heating_controller();
    virtual void turn_off_heating() = 0;
    virtual void controll_heating() = 0;
    virtual void turn_on_heating() = 0;
    virtual double getSulfurTemperatur() = 0;
    virtual void setSulfurTemperatur(double targetTemp) = 0;
    virtual wgm_feedbacks::enum_sys_feedback stop_heating_sys() =0;
    virtual wgm_feedbacks::enum_sys_feedback start_heating_sys() =0;
    virtual heating_controller getSubSysController() = 0;
    virtual bool getSubSysStatus(std::string Subsystem) = 0;
  };
  // implement
  class sulfur_heating_controller: public Isulfur_heating_controller
  {
  private:
    heating_controller heatControl;
    std::vector<std::function<wgm_feedbacks::enum_sub_sys_feedback()>> heatAlgorithms;
     void registerAlgorithms();

  public:
    sulfur_heating_controller();
    virtual ~sulfur_heating_controller();
    double getSulfurTemperatur() override;
    void turn_off_heating() override;
    void turn_on_heating() override;
    void controll_heating() override;
    void setSulfurTemperatur(double targetTemp) override;
    virtual wgm_feedbacks::enum_sys_feedback stop_heating_sys() ;
    virtual wgm_feedbacks::enum_sys_feedback start_heating_sys() ;
    heating_controller getSubSysController() override;
    bool getSubSysStatus(std::string Subsystem) override;
  };

}


