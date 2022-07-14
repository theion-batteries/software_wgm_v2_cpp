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
namespace wafer_holder_motion_system
{
    /****** delta motion ******/
    // interface
    class Idelta_motion
    {
    public:
        virtual void move(int direction) = 0;
        virtual void set_speed_to_minimum() = 0;

        Idelta_motion()
        {
            std::cout << "creating delta motion" << std::endl;
        }

        virtual ~Idelta_motion()
        {
            std::cout << "deleting delta motion" << std::endl;
        }
    };
    // implementation
    class delta_motion :public Idelta_motion
    {
    protected:
        virtual void move(int direction);
        virtual void set_speed_to_minimum();
    };
    void delta_motion::move(int direction)
    {
        if (direction == 1) // up
            std::cout << "move delta up" << std::endl;
        else if (direction == 0)
            std::cout << "move delta down" << std::endl;
        else std::cout << "direction unkown" << std::endl;
    }
    void delta_motion::set_speed_to_minimum()
    {
        std::cout << "setting speed to lowest" << std::endl;
    }
    /****** distance sensor******/
    // interface    
    class Idistance_sensor
    {
    public:
        Idistance_sensor()
        {
            std::cout << "creating distance sensor" << std::endl;
        }
        virtual ~Idistance_sensor()
        {
            std::cout << "deleting distance sensor" << std::endl;
        }
        virtual double read_values() = 0;
    };
    // implementation
    class distance_sensor :public Idistance_sensor
    {
    protected:
        virtual double read_values();
    };
    double distance_sensor::read_values()
    {
        std::cout << "reading value distance sensor" << std::endl;
        return 30;
    }
    /****** wafer motion controller ******/
    // interface    
    class Iwafer_motion_controller
    {
    public:
        Iwafer_motion_controller()
        {
            std::cout << "creating wafer motion controller" << std::endl;
        }
        virtual ~Iwafer_motion_controller()
        {
            std::cout << "deleting wafer motion controller" << std::endl;
        }
        virtual void move_down() = 0;
        virtual void calibrate() = 0;
        virtual void move_up() = 0;
        virtual double get_current_value() = 0;
        virtual void insert_wafer_in_ml() = 0;
        virtual void extract_wafer_from_ml() = 0;
        virtual void set_distance_to_surface_contact(double distance) = 0;
        virtual void slow_down() = 0;


    };
    // implementation
    class wafer_motion_controller :public Iwafer_motion_controller
    {
    public:
        wafer_motion_controller() {
            delta_mover = new delta_motion();
            dist_sensor = new distance_sensor();
        }
        virtual ~wafer_motion_controller()
        {
            delete delta_mover;
            delete dist_sensor;
        }
    protected:
        virtual void move_down();
        virtual void calibrate();
        virtual void move_up();
        virtual double get_current_value();
        virtual void insert_wafer_in_ml();
        virtual void extract_wafer_from_ml();
        virtual void set_distance_to_surface_contact(double distance);
        virtual void slow_down();

    private:
        Idelta_motion* delta_mover;
        Idistance_sensor* dist_sensor;
        double distance_to_surface_contact; // distance where wafer holder extact with ML surface
        double distance_to_slow_down = 30; //30mm=3cm: distance from where the speed of delta motion slow down
    };
    void wafer_motion_controller::move_down()
    {
        delta_mover->move(0);
    }
    void wafer_motion_controller::calibrate()
    {

    }
    void wafer_motion_controller::move_up()
    {
        delta_mover->move(1);
    }
    double wafer_motion_controller::get_current_value()
    {
        return dist_sensor->read_values();
    }
    void wafer_motion_controller::insert_wafer_in_ml()
    {
        std::cout << "start sinking" << std::endl;
        // to start process distance must be set before
        if (distance_to_surface_contact != 0)
        {
            while (get_current_value() != distance_to_surface_contact)
            {
                if (get_current_value() == distance_to_slow_down)
                {
                    slow_down();
                }
                move_down();

            }
        }
        else std::cout << "error: please set distance to surface contact with ml" << std::endl;
    }
    void wafer_motion_controller::extract_wafer_from_ml()
    {
        std::cout << "extracting wafer" << std::endl;
        move_up();
    }
    void wafer_motion_controller::set_distance_to_surface_contact(double distance)
    {
        distance_to_surface_contact = distance;
    }
    void wafer_motion_controller::slow_down()
    {
        std::cout << "reaching critical area, switching mode" << std::endl;
        delta_mover->set_speed_to_minimum();
    }
}

