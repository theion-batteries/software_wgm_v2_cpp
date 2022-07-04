#pragma once
#include <iostream>
#include <list>
namespace sulfur_heating_system
{
    /*********** classes *************/
class Isulfur_heating_controller
{
    public:
        Isulfur_heating_controller(){
               std::cout<<"creating heating controller"<<std::endl;

        }
         virtual void turn_off_heating ()=0;
         virtual void controll_heating ()=0;
         virtual void turn_on_heating ()=0;
         virtual ~Isulfur_heating_controller()
         {
               std::cout<<"deleting heating controller"<<std::endl;
         }

};


class Itemperature_sensor
{
    public:
         Itemperature_sensor()
         {
               std::cout<<"creating temp sensor"<<std::endl;
         }

         virtual ~Itemperature_sensor()
         {
               std::cout<<"deleting sensor"<<std::endl;
         }
         virtual void get_current_value() =0;

};


class Iheater
{
    public:

         virtual void start_heater ()=0;
         virtual void shutdown_heater ()=0;
         Iheater()
         {
               std::cout<<"creating heater"<<std::endl;
         }

         virtual ~Iheater()
         {
               std::cout<<"deleting heater"<<std::endl;
         }
};



  class temperature_sensor: public Itemperature_sensor {
  public:
    virtual void get_current_value ();

  };
  void temperature_sensor::get_current_value ()
  {
    std::cout<<"reading value sensor"<<std::endl;
  }
  class Heater: public Iheater
  {
  public:
    virtual void start_heater ();
    virtual void shutdown_heater ();

  };


  void Heater::start_heater ()
  {
    std::cout<<"starting heater"<<std::endl;

  }

  void Heater::shutdown_heater ()
  {
    std::cout<<"stopping heater"<<std::endl;

  }

  class sulfur_heating_controller: public Isulfur_heating_controller
  {
  private:
    //temperature_sensor tempe_sensor;
    Itemperature_sensor* tempe_sensor;
    Iheater* heater;

  public:
  sulfur_heating_controller(){
      tempe_sensor = new temperature_sensor();
      heater = new Heater();
  }
    void getSensorReading ();
    virtual void turn_off_heating ();
    virtual void turn_on_heating ();
    virtual void controll_heating ();
    virtual ~sulfur_heating_controller()
    {
        delete heater;
        delete tempe_sensor;
    }
  };


  void sulfur_heating_controller::getSensorReading ()
  {
    std::cout<<"controller get sensor value"<<std::endl;
    tempe_sensor->get_current_value();
  }

  void sulfur_heating_controller::turn_off_heating ()
  {
    std::cout<<"controller turn off heater"<<std::endl;
    heater->shutdown_heater();
  }

  void sulfur_heating_controller::turn_on_heating ()
  {
    std::cout<<"controller turn on heater "<<std::endl;
    heater->start_heater();
  }

  void sulfur_heating_controller::controll_heating ()
  {
    std::cout<<"controller regulate"<<std::endl;
    getSensorReading();
  }

}
class client{
    private: 
    sulfur_heating_system::Isulfur_heating_controller* controllerInterface ;
    
    public:
    client()
    {
    std::cout<<"user started heating system"<<std::endl;

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
    std::cout<<"user stopped heating system"<<std::endl;
       delete controllerInterface;
    } 
};

