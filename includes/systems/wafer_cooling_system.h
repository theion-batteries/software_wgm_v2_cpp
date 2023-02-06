/**
 * @file wafer_cooling_system.h
 * @author sami dhiab (sami@theion.de)
 * @brief wafer cooling system package
 * @version 0.1
 * @date 2022-07-04
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <iostream>
#include "ph_cooling_controller.h"
#include "system_feedback.h"
#include <memory>
#include <functional>

using enum wgm_feedbacks::enum_sys_feedback;
using enum wgm_feedbacks::enum_sub_sys_feedback;
namespace wafer_cooling_system
{
    
    /****** cooling controller ********/
    // interface
    class Icooling_controller
    {
    public:
        Icooling_controller();
        virtual ~Icooling_controller();
        virtual wgm_feedbacks::enum_sys_feedback start_cooling() = 0;
        virtual wgm_feedbacks::enum_sys_feedback stop_cooling() = 0;
        virtual void connect_rotation_axis() = 0;
        virtual void connect_motion_axis() = 0;
        virtual void connect_ph() = 0;
        virtual std::shared_ptr<ph_cooling_controller> getSubSysController() = 0;
        virtual bool getSubSysStatus(std::string Subsystem) = 0;
    };
    // implementation 
    class cooling_controller: public Icooling_controller
    {
    private:
    std::shared_ptr<ph_cooling_controller> ph_sys_control_shared_ptr;
     void registerAlgorithms();
    std::vector<std::function<wgm_feedbacks::enum_sub_sys_feedback()>> phAlgorithms;
    public:
        cooling_controller();
        virtual ~cooling_controller();
        void connect_rotation_axis() override;
        void connect_motion_axis() override;
        void connect_ph() override;
        std::shared_ptr<ph_cooling_controller> getSubSysController() override;
        bool getSubSysStatus(std::string Subsystem) override;
         wgm_feedbacks::enum_sys_feedback start_cooling() override;
         wgm_feedbacks::enum_sys_feedback stop_cooling() override;


    };
}

