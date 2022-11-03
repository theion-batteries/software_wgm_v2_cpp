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
#include "feedback_management.h"
 /*
 enum class wgm_feedbacks::enum_sys_feedback
 {
     sys_success = 2,
     sys_error = -1
 };*/
namespace wafer_holder_motion_system
{
    // axis motion

    class Iaxis_motion
    {
    public:
        virtual void move(int direction) = 0;

        Iaxis_motion();

        virtual ~Iaxis_motion();
    };
    // implementation
    class axis_motion :public Iaxis_motion
    {
    public:
        explicit axis_motion(std::shared_ptr<whs_controller> shared_controller);

    protected:

        virtual void move(int direction);
    private:
        std::shared_ptr<whs_controller>   wafer_motion_shared_ptr;

    };

    /****** distance sensor******/
    // interface    
    class Idistance_sensor
    {
    public:
        Idistance_sensor();
        virtual ~Idistance_sensor();
        virtual double read_values() = 0;
    };
    // implementation
    class distance_sensor :public Idistance_sensor
    {
    public:
        explicit distance_sensor(std::shared_ptr<whs_controller> shared_controller);
    protected:
        virtual double read_values();
    private:
        std::shared_ptr<whs_controller>   wafer_dist_shared_ptr;

    };

    /****** wafer motion controller ******/
    // interface    
    class Iwafer_motion_controller
    {
    public:
        Iwafer_motion_controller();
        virtual ~Iwafer_motion_controller();
        virtual void move_down() = 0;
        virtual void calibrate() = 0;
        virtual void move_up() = 0;
        virtual double get_current_value(uint16_t sensor_head) = 0;
        virtual wgm_feedbacks::enum_sys_feedback insert_wafer_in_ml() = 0;
        virtual void extract_wafer_from_ml() = 0;
        virtual void set_distance_to_surface_contact(double distance) = 0;
        virtual void connect_sensor() = 0;
        virtual std::shared_ptr<whs_controller> getSubSysController() = 0;
        virtual bool getSubSysStatus(std::string Subsystem) = 0;


    };
    // implementation
    class wafer_motion_controller :public Iwafer_motion_controller
    {
    public:
        explicit wafer_motion_controller();
        virtual ~wafer_motion_controller();
    protected:
        virtual void move_down();
        virtual void calibrate();
        virtual void move_up();
        virtual double get_current_value(uint16_t sensor_head);
        virtual wgm_feedbacks::enum_sys_feedback insert_wafer_in_ml();
        virtual void extract_wafer_from_ml();
        virtual void set_distance_to_surface_contact(double distance);
        virtual void connect_sensor();
        virtual bool getSubSysStatus(std::string Subsystem);
        virtual std::shared_ptr<whs_controller> getSubSysController();

    private:
        std::unique_ptr< Iaxis_motion> axis_mover;
        std::unique_ptr<Idistance_sensor> dist_sensor;
        std::shared_ptr<whs_controller> wafer_sys_control_shared_ptr;// = std::make_shared<whs_controller>();
        double distance_to_surface_contact; // distance where wafer holder extact with ML surface
        double distance_to_slow_down = 30; //30mm=3cm: distance from where the speed of delta motion slow down
    };

}

