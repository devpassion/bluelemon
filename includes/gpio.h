/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2015 <copyright holder> <email>
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
#define IO_GPIO_H


#include <mutex>
#include <array>
#include <arccos/mpltools/interval.h>

#include "pin.h"
#include "io_exception.h"
#include "systeminterface.h"

namespace io 
{
    
    
    template<template<class> class DirectionPolicy, typename InterfacePolicy = SystemInterface>
    class GPIO final : public DirectionPolicy<InterfacePolicy>
    {
        using SelfType = GPIO<DirectionPolicy, InterfacePolicy>;
       
        
    public:
        GPIO(unsigned short pin);
        
        GPIO(const GPIO<DirectionPolicy, InterfacePolicy>& other);
        
        GPIO& operator=(const GPIO& other) = default;
        
        ~GPIO();
        
        bool operator==(const GPIO& other) const;
    };
}

#include "../tpl/gpio.cpp"

#endif // IO_GPIO_H


