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
        std::string user_name;
        std::string user_passowrd;

    public:
        user();
        void run_app();
        void stop_app();
        std::string getUserName();
        std::string getUserPassowrd();
        void setUserName(std::string name);
        void setUserPassowrd(std::string password);
        void login();
        void logout();
        ~user();
    };



} // namespace wgm_user

