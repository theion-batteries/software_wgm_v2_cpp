/**
 * @file wgm_experiment.cpp
 * @author sami dhiab sami@theion.de
 * @brief
 * @version 0.1
 * @date 2022-07-12
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "wgm_experiment.h"

wgm_experiment::experiment::experiment(std::string name, int id)

{
  experiment_name=name;
  std::cout << "experiment " << name<<"with id= "<< id<<" started " << "\n";

  experiment_id=id;

}

wgm_experiment::experiment::~experiment()
{
  std::cout << "experiment stopped " << "\n";
}
std::string wgm_experiment::experiment::getexperimentName()
{
  return experiment_name;
}

void wgm_experiment::experiment::setexperimentName(std::string name)
{
  experiment_name = name;
}
