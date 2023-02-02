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

namespace wafer_cooling_system
{
    /****** cooling rotation *******/
    // interface
    class Icooling_rotation
    {
    public:
        Icooling_rotation();
        virtual ~Icooling_rotation();
        virtual void ph_rotate() = 0;
    };
    // implementation  
    class cooling_rotation: public Icooling_rotation
    {
    protected:
        virtual void ph_rotate();
    };

    /******* cooling motion *****/
    // interface
    class Icooling_motion
    {
    public:
        Icooling_motion();
        virtual ~Icooling_motion();
        virtual void move_down_to_center() = 0;
        virtual void move_up_to_reference() = 0;
    };
    // implementation 
    class cooling_motion: public Icooling_motion
    {
        virtual void move_down_to_center();
        virtual void move_up_to_reference();
    };

    /****** cooling printing ********/
    // interface

    class Icooling_spitting
    {
    public:
        Icooling_spitting();
        virtual ~Icooling_spitting();
        virtual void ph_spit() = 0;
    };
    // implementation 
    class cooling_spitting: public Icooling_spitting
    {
        virtual void ph_spit();
    };

    /****** cooling controller ********/
    // interface
    class Icooling_controller
    {
    public:
        Icooling_controller();
        virtual ~Icooling_controller();
        virtual wgm_feedbacks::enum_sys_feedback start_cooling() = 0;
        virtual void stop_cooling() = 0;
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
        Icooling_motion* ph_motion;
        Icooling_rotation* ph_rotation;
        Icooling_spitting* ph_printing;
        std::shared_ptr<ph_cooling_controller> ph_sys_control_shared_ptr;
    public:
        void connect_rotation_axis() override;
        void connect_motion_axis() override;
        void connect_ph() override;
        std::shared_ptr<ph_cooling_controller> getSubSysController() override;
        bool getSubSysStatus(std::string Subsystem) override;
         wgm_feedbacks::enum_sys_feedback start_cooling() override;
         void stop_cooling() override;
        cooling_controller();
         ~cooling_controller();

    };


}

