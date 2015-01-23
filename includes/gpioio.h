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

#ifndef IO_GPIOIO_H
#define IO_GPIOIO_H

#include "pin.h"

namespace io
{
    template<typename InterfacePolicy>
    class Input : public PinContainer<unsigned char>
    {
        const InterfacePolicy interface;
        
    protected:
        
        Input(unsigned char pin);
    public:
        PinState read();
    };
    
    template<typename InterfacePolicy>
    class Output : public PinContainer<unsigned char>
    {
        const InterfacePolicy interface;
    protected:
        
        Output(unsigned char pin);
    public:
        void set( PinState value);
    };
    
    
    template<template<class> class DirectionPolicy>
    struct StrDirectionTrait
    {
        static constexpr const char* value = "in";
    };
    
    template<>
    struct StrDirectionTrait<Output>
    {
        static constexpr const char* value = "out";
    };
}

#include "../tpl/gpioio.cpp"

#endif

