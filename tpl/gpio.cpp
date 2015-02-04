/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2015  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef IO_GPIO_H
#include <gpio.h>
#endif

#include <sstream>
#include <fstream>
#include <iostream>

#include "gpioio.h"
#include "io_exception.h"



#include <chrono>
#include <thread>

namespace io
{

    
    std::array<unsigned short, 18> SystemInterface::UserCounts = 
            arccos::mptools::make_interval< 0, 17 >::type::ToStaticArray<unsigned short,NullFunctor>::ARR;
    
    std::array<std::mutex, 18> SystemInterface::mutexes_;
            
    template<template<class> class DirectionPolicy, typename InterfacePolicy>
    GPIO<DirectionPolicy, InterfacePolicy>::GPIO(unsigned short pin) : DirectionPolicy<InterfacePolicy>(pin)
    {
        
    }
    
    template<template<class> class DirectionPolicy, typename InterfacePolicy>
    GPIO<DirectionPolicy, InterfacePolicy>::GPIO ( const GPIO<DirectionPolicy, InterfacePolicy>& other ) : GPIO(other.getPin())
    {

    }

 



//     template<template<class> class DirectionPolicy, typename InterfacePolicy>
//     GPIO<DirectionPolicy, InterfacePolicy>::GPIO ( const GPIO& other ) 
//     {
//         
//     }

    template<template<class> class DirectionPolicy, typename InterfacePolicy>
    GPIO<DirectionPolicy, InterfacePolicy>::~GPIO()
    {
        
    }

    // template<template<class> class DirectionPolicy, typename InterfacePolicy>
    // GPIO<DirectionPolicy, InterfacePolicy>& GPIO<DirectionPolicy, InterfacePolicy>::operator= ( const GPIO& other )
    // {
    // 
    // }


    template<template<class> class DirectionPolicy, typename InterfacePolicy>
    bool GPIO<DirectionPolicy, InterfacePolicy>::operator== ( const GPIO& other ) const
    {
        return DirectionPolicy<InterfacePolicy>::pin_ == other.pin_;
    }




    

}










