/**
 * @file wgm_user.h
 * @author sami dhiab
 * @brief user code
 * @version 0.1
 * @date 2022-07-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "process_manager.h"
#pragma once

/****************** user code ********************/
namespace wgm_user
{
    
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



} // namespace wgm_user

