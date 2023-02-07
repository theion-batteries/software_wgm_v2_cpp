/**
 * @file cnt_alignment_system.h
 * @author sami dhiab (sami@theion.de)
 * @brief cnt alignment system package
 * @version 0.1
 * @date 2022-07-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <iostream>
#include "cnt_controller.h"
#include "system_feedback.h"
#include <functional>
#include <memory>

using enum wgm_feedbacks::enum_sys_feedback;
using enum wgm_feedbacks::enum_sub_sys_feedback;

namespace cnt_alignment_system
{
  /*********** cnt controller ************/
  class Icnt_aligning_controller
  {
  public:
    virtual ~Icnt_aligning_controller() {};
    virtual wgm_feedbacks::enum_sys_feedback start_aligning() = 0;
    virtual wgm_feedbacks::enum_sys_feedback stop_aligning() = 0;
    virtual void connect_dispenser() = 0;
    virtual void connect_motion_axis() = 0;
    virtual void connect_hv() = 0;
    virtual cnt_controller getSubSysController() = 0;
    virtual bool getSubSysStatus(std::string Subsystem) = 0;
  };
  //implement
  class cnt_aligning_controller: public Icnt_aligning_controller
  {
  private:
     void registerAlgorithms();
    cnt_controller controller;
    std::vector<std::function<wgm_feedbacks::enum_sub_sys_feedback()>> cntAlgorithms;
    bool stopped = false;
  public:
    cnt_aligning_controller();
    virtual ~cnt_aligning_controller();
    void connect_dispenser() override;
    void connect_motion_axis() override;
    void connect_hv() override;
    cnt_controller getSubSysController() override;
    bool getSubSysStatus(std::string Subsystem) override;
    virtual wgm_feedbacks::enum_sys_feedback start_aligning();
    virtual wgm_feedbacks::enum_sys_feedback stop_aligning();

  };

}

