/**
 * @file wgm_test.cpp
 * @author sami dhiab sami@theion.de
 * @brief
 * @version 0.1
 * @date 2022-07-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "wgm_test.h"


wgm_feedbacks::enum_hw_feedback wgm_test::hw_mocking::hw_run()
{
  return wgm_feedbacks::enum_hw_feedback::hw_success;
}

