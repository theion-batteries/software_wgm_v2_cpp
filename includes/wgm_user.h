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

#include "process_manager.h"
#include "wgm_experiment.h"
/****************** user code ********************/
namespace wgm_user
{

    class user {
    private:
        std::string user_name;
        std::string user_passowrd;
        static inline int id=0;
        static inline Idatabase* userData=new userDB("userTable");

    public:
    user();
        user(std::string name, std::string password);
        std::string getUserName();
        std::string getUserPassowrd();
        void setUserName(std::string name);
        void setUserPassowrd(std::string password);
        static bool login(std::string username, std::string password);
        static void logout();
        ~user();
    };



} // namespace wgm_user

