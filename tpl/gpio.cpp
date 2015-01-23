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

namespace io
{

    template<template<class> class DirectionPolicy, typename InterfacePolicy>
    GPIO<DirectionPolicy, InterfacePolicy>::GPIO(unsigned short pin) : DirectionPolicy<InterfacePolicy>(pin)
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




    SystemInterface::SystemInterface ( unsigned char pin )
    {
        std::stringstream ss;
        ss << static_cast<short>(pin);
        strPin_ = ss.str();
        
        std::cout << "Create pin " << strPin_ << std::endl;
        
        std::ofstream fos( exportFile );
        fos << strPin_;
        fos.close();
    }


    template<template<class> class Direction>
    void SystemInterface::init (  ) const
    {
        std::ofstream fos( baseGPIOFile + strPin_ + "/direction" );
        fos << StrDirectionTrait<Direction>::value;
        fos.close();
        
    }

    PinState SystemInterface::read (  ) const
    {
        std::ifstream fis( "/sys/class/gpio/gpio" + strPin_ + "/value" );
        char val;
        fis >> val;
        fis.close();
        return static_cast<PinState>( val );
    }


    void SystemInterface::set ( PinState value ) const
    {
        std::ofstream fos( "/sys/class/gpio/gpio" + strPin_ + "/value" );
        fos << static_cast<char>( value );
        fos.close();
    }

    SystemInterface::~SystemInterface()
    {
        std::ofstream fos( unexportFile );
        fos << strPin_;
        fos.close();
    }

}










