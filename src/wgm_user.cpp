/**
 * @file wgm_user.cpp
 * @author your name (you@domain.com)
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