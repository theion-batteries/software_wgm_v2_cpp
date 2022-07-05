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
namespace cnt_alignment_system
{
    /********** cnt dispensing **************/
    class Icnt_dispensing
    {
    public:
        virtual void start_vibrating() = 0;
        virtual void stop_vibrating() = 0;
    Icnt_dispensing()
    {
      std::cout << "creating cnt dispenser" << std::endl;
    }

    virtual ~Icnt_dispensing()
    {
      std::cout << "deleting cnt dispenser" << std::endl;
    }
    };
    // implement 
    class cnt_dispensing: public Icnt_dispensing
    {
        protected:
        virtual void start_vibrating();
        virtual void stop_vibrating();
    };
    void cnt_dispensing::start_vibrating()
    {
    std::cout << "starting vibration" << std::endl;
    }
    void cnt_dispensing::stop_vibrating()
    {
    std::cout << "stopping vibration" << std::endl;
    }
    /****************** cnt motion ******************/
    class Icnt_motion
    {
    public:
        virtual void move_down_to_center() = 0;
        virtual void move_back_to_reference() = 0;
    Icnt_motion()
    {
      std::cout << "creating cnt motion" << std::endl;
    }
    virtual ~Icnt_motion()
    {
      std::cout << "deleting cnt motion" << std::endl;
    }
    };
    //implement
    class cnt_motion: public Icnt_motion
    {
        protected:
        virtual void move_down_to_center();
        virtual void move_back_to_reference();
    };
    void cnt_motion::move_down_to_center()
    {
    std::cout << "cnt moving down to centre" << std::endl;
    }
    void cnt_motion::move_back_to_reference()
    {
    std::cout << "cnt moving back to refrence" << std::endl;
    }
    /****************** hv controller ******************/
    class Ihv_controller
    {
    public:
        virtual void start_hv() = 0;
        virtual void stop_hv() = 0;
        virtual double get_input_voltage()=0;
        virtual double get_output_voltage()=0;
        virtual double get_input_current()=0;
        virtual double get_output_current()=0;
    Ihv_controller() 
    {
      std::cout << "creating hv controller" << std::endl;
    }
    virtual ~Ihv_controller()
    {
      std::cout << "deleting hv controller" << std::endl;
    }
    };
    // implement
    class hv_controller: public Ihv_controller
    {
        protected:
        virtual void start_hv();
        virtual void stop_hv();
        virtual double get_input_voltage();
        virtual double get_output_voltage();
        virtual double get_input_current();
        virtual double get_output_current();

        private:
          double input_voltage;
          double output_voltage;
          double input_current;
          double output_current;
        
    };

    void hv_controller::start_hv()
    {
      std::cout << "starting hv controller" << std::endl;
    }
    void hv_controller::stop_hv()
    {
      std::cout << "stopping hv controller" << std::endl;
    }
    // external system calls
    double hv_controller::get_input_voltage()
    {
        return input_voltage;
    }
    double hv_controller::get_input_current()
    {
        return input_current;
    }
    double hv_controller::get_output_voltage()
    {
        return output_current;
    }
    double hv_controller::get_output_current()
    {
        return output_voltage;
    }
    /*********** cnt controller ************/
    class Icnt_aligning_controller
    {
    public:
    Icnt_aligning_controller() 
    {
      std::cout << "creating cnt_aligning_controller" << std::endl;
    }
    virtual ~Icnt_aligning_controller()
    {
      std::cout << "deleting cnt_aligning_controller" << std::endl;
    }
      virtual void start_aligning() = 0;
      virtual void stop_aligning() = 0;
      virtual cnt_aligning_controller::voltage get_voltage_struct() = 0;
      virtual cnt_aligning_controller::current get_current_struct() = 0;

    };
    //implement
    class cnt_aligning_controller: public Icnt_aligning_controller
    {
    private:
        Icnt_dispensing* cnt_dispenser;
        Icnt_motion* cnt_motion_controller;
        Ihv_controller* hv_controll;
        public:
        cnt_aligning_controller() 
        {
        cnt_dispenser = new cnt_dispensing();
        cnt_motion_controller = new cnt_motion();
        hv_controll = new hv_controller();
        }
        virtual ~cnt_aligning_controller()
        {
        delete cnt_dispenser;
        delete cnt_motion_controller;
        delete hv_controll;
        }
        public:
        struct voltage
        {
          double Vin; //voltage
          double Vout;
        };
        struct current
        {
          double Cin; //current
          double Cout; 
        };
        protected:
        voltage V;
        current C;
        virtual void start_aligning();
        virtual void stop_aligning();
      virtual cnt_aligning_controller::voltage get_voltage_struct();
      virtual cnt_aligning_controller::current get_current_struct();

    };
    void cnt_aligning_controller::start_aligning()
    {
        hv_controll->start_hv();
        cnt_motion_controller->move_down_to_center();
        cnt_dispenser->start_vibrating();
    }

    void cnt_aligning_controller::stop_aligning()
    {
        cnt_dispenser->stop_vibrating();  
        cnt_motion_controller->move_back_to_reference();
        hv_controll->stop_hv();
    }
    cnt_aligning_controller::voltage cnt_aligning_controller::get_voltage_struct()
    {
        V.Vin= hv_controll->get_input_voltage();
        V.Vout= hv_controll->get_output_voltage();
        return V;
    }
    cnt_aligning_controller::current cnt_aligning_controller::get_current_struct()
    {
        C.Cin= hv_controll->get_input_voltage();
        C.Cout= hv_controll->get_output_voltage();
        return C;
    }
}

