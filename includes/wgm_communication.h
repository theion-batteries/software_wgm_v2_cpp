/**
 * @file wgm_communication.h
 * @author sami dhiab (sami@theion.de)
 * @brief communication package
 * @version 0.1
 * @date 2022-07-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <iostream>

namespace wgm_communication
{
     class hw_communication
    {
        public:
            template<typename T> void emit (T response);
            template<typename T> void parse (T data);
    
    };
    
    
      template<typename T> void hw_communication::emit (T response)
    {
                        
    }
    
    template<typename T> void hw_communication::parse (T data)
    {
                        
    }
    
     class sw_communication
    {
    
        template<typename T> void parse (T data);
        public:
            template<typename T> void emit (T cmd);
    
    };
    
    
      template<typename T> void sw_communication::emit (T cmd)
    {
                        
    }
    
    template<typename T> void sw_communication::parse (T data)
    {
                        
    }
    
    
}
 
