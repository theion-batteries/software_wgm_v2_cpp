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
wgm_user::user::user()
{

}
wgm_user::user::user(std::string name, std::string password)
{
  std::cout << "user " << name << " created" << "\n";
  user_name = name;
  user_passowrd = password;
  id=userData->getLastRowID();
  id++;
  std::string rowValues = "(, '" + name +"','" + password + "');";
  auto ID = std::to_string(id);
  rowValues.insert(1,ID.c_str()) ;
  std::cout << "inserting row values " << rowValues << " in users database" << "\n";
  userData->insertDBTableRow(userData->getTableHandle().Table_name, rowValues);
  // debug db: query
  userData->queryDBTable(userData->getTableHandle().Table_name);

}

wgm_user::user::~user()
{
  std::cout << "user destructed" << "\n";
  //delete userData;
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

bool wgm_user::user::login(std::string username, std::string password)
{
  return userData->searchDBRowValues(userData->getTableHandle().Table_name,"name",  username,"password", password);
}
void wgm_user::user::logout()
{

}