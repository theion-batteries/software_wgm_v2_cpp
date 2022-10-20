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
#pragma once
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include "process_manager.h"

/****************** user code ********************/
namespace wgm_user
{
    
    class user {
    private:
        wgm_processes::Iprocesses_managment* processInterfaces;

    public:
        user();
        void run_app();
        void stop_app();
        ~user();
    };



} // namespace wgm_user

