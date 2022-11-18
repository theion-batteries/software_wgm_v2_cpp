/**
 * @file wgm_user.cpp
 * @author sami dhiab sami@theion.de
 * @brief
 * @version 0.1
 * @date 2022-07-12
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "wgm_user.h"
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

wgm_user::user::user()
{
  std::cout << "user started app" << std::endl;

  processInterfaces = new wgm_processes::process_management();
}
void wgm_user::user::run_app()
{
  processInterfaces->start_all();
}
void wgm_user::user::stop_app()
{
  processInterfaces->stop_all();
}
wgm_user::user::~user()
{
  std::cout << "user stopped app" << std::endl;
  delete processInterfaces;
}
std::string wgm_user::user::getUserName()
{
  return user_name;
}
std::string wgm_user::user::getUserPassowrd()
{
  return user_passowrd;

}
void wgm_user::user::setUserName(std::string name)
{
  user_name = name;
}
void wgm_user::user::setUserPassowrd(std::string password)
{
  user_passowrd = password;
}

void wgm_user::user::login() 
{
  // enter user_name and passsword
}
void wgm_user::user::logout()
{

}