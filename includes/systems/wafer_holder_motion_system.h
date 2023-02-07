/**
 * @file wafer_holder_motion_system.h
 * @author sami dhiab (sami@theion.de)
 * @brief wafer motion system package
 * @version 0.1
 * @date 2022-07-04
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <iostream>
#include <whs_controller.h>
#include <yaml-cpp/yaml.h>
#include <memory>
#include "system_feedback.h"
#include <vector>
#include <functional>
#include <algorithm>

using enum wgm_feedbacks::enum_sys_feedback;
using enum wgm_feedbacks::enum_sub_sys_feedback;

namespace wafer_holder_motion_system
{

    /****** wafer motion controller ******/
    // interface    
    class Iwafer_motion_controller
    {
    public:
        Iwafer_motion_controller();
        virtual ~Iwafer_motion_controller();
        virtual wgm_feedbacks::enum_sys_feedback start_sinking()=0;
        virtual wgm_feedbacks::enum_sys_feedback stop_sinking()=0;
        virtual wgm_feedbacks::enum_sys_feedback start_extracting()=0;
        virtual wgm_feedbacks::enum_sys_feedback stop_extracting()=0;
        virtual wgm_feedbacks::enum_sys_feedback insert_wafer_in_ml() = 0;
        virtual wgm_feedbacks::enum_sys_feedback extract_wafer_from_ml() = 0;
        virtual void calibrate() = 0;
        virtual void move_up() = 0;
        virtual double get_current_value(uint16_t sensor_head) = 0;
        virtual void connect_sensor() = 0;
        virtual void connect_motion_axis() = 0;
        virtual std::shared_ptr<whs_controller> getSubSysController() = 0;
        virtual bool getSubSysStatus(std::string Subsystem) = 0;
    };
    // implementation
    class wafer_motion_controller:public Iwafer_motion_controller
    {
    private:
        void registerAlgorithms();
        std::shared_ptr<whs_controller> wafer_sys_control_shared_ptr;
        std::vector<std::function<wgm_feedbacks::enum_sub_sys_feedback()>> whsAlgorithms;
        bool stopped = false;
    public:
        wafer_motion_controller();
        virtual ~wafer_motion_controller();
        virtual wgm_feedbacks::enum_sys_feedback insert_wafer_in_ml();
        virtual wgm_feedbacks::enum_sys_feedback start_sinking();
        virtual wgm_feedbacks::enum_sys_feedback stop_sinking();
        virtual wgm_feedbacks::enum_sys_feedback start_extracting();
        virtual wgm_feedbacks::enum_sys_feedback stop_extracting();
        virtual wgm_feedbacks::enum_sys_feedback extract_wafer_from_ml();
        virtual void calibrate();
        virtual void move_up();
        virtual double get_current_value(uint16_t sensor_head);
        virtual void connect_sensor();
        virtual void connect_motion_axis();
        virtual bool getSubSysStatus(std::string Subsystem);
        virtual std::shared_ptr<whs_controller> getSubSysController();


    };

}

