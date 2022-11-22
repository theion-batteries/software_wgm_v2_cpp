/**
 * @file wgm_experiment.h
 * @author sami dhiab
 * @brief experiment code
 * @version 0.1
 * @date 2022-07-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <iostream>
#include "dbIncludeAll.h"
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS


/****************** experiment code ********************/
namespace wgm_experiment
{
    class experiment {
    private:
        std::string experiment_name;
        std::string experiment_id;
        Idatabase* dbExperiment;

    public:
        experiment(std::string name, int id);
        std::string getexperimentName();
        void setexperimentName(std::string name);
        ~experiment();
    };



} // namespace wgm_experiment

