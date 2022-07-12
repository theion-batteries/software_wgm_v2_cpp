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
namespace wafer_cooling_system
{
    /****** cooling rotation *******/
    // interface
    class Icooling_rotation
    {
    public:
        Icooling_rotation()
        {
            std::cout << "creating cooling rotation " << std::endl;
        }

        virtual ~Icooling_rotation()
        {
            std::cout << "deleting cooling rotation " << std::endl;
        }
        virtual void ph_rotate() = 0;
    };
    // implementation  
    class cooling_rotation: public Icooling_rotation
    {
        protected:
        virtual void ph_rotate();
    };
    void cooling_rotation::ph_rotate()
    {
       std::cout << "start rotating " << std::endl; 
    }
    /******* cooling motion *****/
    // interface
    class Icooling_motion
    {
    public:
        Icooling_motion()
        {
            std::cout << "creating cooling motion" << std::endl;
        }
        virtual ~Icooling_motion()
        {
            std::cout << "deleting cooling motion" << std::endl;
        }
        virtual void move_down_to_center() = 0;
        virtual void move_up_to_reference() = 0;
    };
    // implementation 
    class cooling_motion: public Icooling_motion
    {
        virtual void move_down_to_center();
        virtual void move_up_to_reference();
    };
    void cooling_motion::move_down_to_center()
    {
        std::cout << "cooling sys moving down to center" << std::endl;
 
    }
    void cooling_motion::move_up_to_reference()
    {
        std::cout << "cooling sys moving back to refernce " << std::endl;

    }
    /****** cooling printing ********/
    // interface

    class Icooling_spitting
    {
    public:
    Icooling_spitting() 
    {
      std::cout << "creating cooling printing" << std::endl;
    }
    virtual ~Icooling_spitting()
    {
      std::cout << "deleting cooling printing" << std::endl;
    }
        virtual void ph_spit() = 0;
    };
    // implementation 
    class cooling_spitting: public Icooling_spitting
    {
        virtual void ph_spit();
    };

    void cooling_spitting::ph_spit()
    {
      std::cout << "printhead spitting" << std::endl;

    }
    /****** cooling controller ********/
    // interface
    class Icooling_controller
    {
    public:
    Icooling_controller() 
    {
      std::cout << "creating cooling controller" << std::endl;
    }
    virtual ~Icooling_controller()
    {
      std::cout << "deleting cooling controller" << std::endl;
    }
        virtual void start_cooling() = 0;
        virtual void stop_cooling() = 0;
    };
    // implementation 
    class cooling_controller: public Icooling_controller
    {
        private:
        Icooling_motion* ph_motion;
        Icooling_rotation* ph_rotation;
        Icooling_spitting* ph_printing;
        protected:
        virtual void start_cooling();
        virtual void stop_cooling();
        public:
        cooling_controller() 
        {
        ph_motion = new cooling_motion();
        ph_rotation = new cooling_rotation();
        ph_printing = new cooling_spitting();
        }
        virtual ~cooling_controller()
        {
        delete ph_motion;
        delete ph_rotation;
        delete ph_printing;
        }

    };
    void cooling_controller::start_cooling()
    {
        ph_motion->move_down_to_center();
        ph_rotation->ph_rotate();
        ph_printing->ph_spit();
    }
    void cooling_controller::stop_cooling()
    {
        ph_motion->move_up_to_reference();
    }

}

