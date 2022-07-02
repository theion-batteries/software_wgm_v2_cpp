
#include "heating_system.h"
namespace wgm_processes
{
    class Iprocesses_managment
    {
    public:
        Iprocesses_managment() {
        }
        virtual void start_process() = 0;
        virtual void stop_process() = 0;
        virtual void stop_all() {};
        virtual void start_all() {};
        virtual ~Iprocesses_managment() {
        }
    };
    class Iheating_process : public Iprocesses_managment
    {
    public:
        Iheating_process()
        {
            std::cout << "creating heating process " << std::endl;
        }

        virtual ~Iheating_process()
        {
        }
        virtual void start_process() = 0;
        virtual void stop_process() = 0;
    };
    class heating_process : public Iheating_process
    {
    public:
        sulfur_heating_system::Isulfur_heating_controller* heating_sys;
        heating_process() {
            heating_sys = new sulfur_heating_system::sulfur_heating_controller();
        }
        virtual void start_process();
        virtual void stop_process();
        virtual ~heating_process()
        {
            std::cout << "deleting heating process " << std::endl;
            delete heating_sys;
        }
    };
    class process_management : public Iprocesses_managment
    {
    private:
        Iheating_process* h_proc;
        std::list<Iprocesses_managment*> processesList;
    public:
        process_management() {
            std::cout << "creating process manager" << std::endl;
            h_proc = new heating_process();
            processesList.push_back(h_proc);
            std::cout << "added heating process to process list" << std::endl;
        }
        virtual ~process_management() {
            std::cout << "deleting process manager" << std::endl;
            for (auto process : processesList)
            {
                if (process != nullptr)
                {
                    delete process;
                }
                else 
                {
                    std::cout << "can't free memory" << std::endl;
                    break;
                }
            }
        }
        virtual void start_process();
        virtual void stop_process();
        virtual void start_all();
        virtual void stop_all();
        virtual void add_process();
        virtual void delete_process();
    };
    void process_management::start_process()
    {
        std::cout << "process started" << std::endl;
    }
    void process_management::stop_process()
    {
        std::cout << "process stopped" << std::endl;
    }
    void process_management::start_all()
    {
        std::cout << "executing all processes" << std::endl;
        for (auto process : processesList)
        {
            if (process != nullptr)
            {
                h_proc->start_process();
            }
            else std::cout << "empty list" << std::endl;
        }
    }
    void process_management::stop_all()
    {      
        std::cout << "stopping all processes" << std::endl;
 
        for (auto process : processesList)
        {
            if (process != nullptr)
            {
                h_proc->stop_process();
            }
            else std::cout << "empty list" << std::endl;
        }
    }
    void process_management::add_process()
    {

    }
    void process_management::delete_process()
    {

    }
    void heating_process::start_process()
    {
        heating_sys->turn_on_heating();
    }
    void heating_process::stop_process()
    {
        heating_sys->turn_off_heating();
    }
}

class user {
private:
    wgm_processes::Iprocesses_managment* processInterfaces;

public:
    user()
    {
        std::cout << "user started app" << std::endl;

        processInterfaces = new wgm_processes::process_management();
    }
    void run_app()
    {
        processInterfaces->start_all();
    }
    void stop_app()
    {
        processInterfaces->stop_all();
    }
    ~user()
    {
        std::cout << "user stopped app" << std::endl;
        delete processInterfaces;
    }
};

