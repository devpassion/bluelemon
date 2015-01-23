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
#define IO_GPIO_H

namespace io 
{
    
    enum PinState : char
    {
        LOW = '0',
        HIGH = '1'
    };
    
    
    template<typename InterfacePolicy>
    class Input
    {
        
        const unsigned char pin_;
        const InterfacePolicy interface;
        
    protected:
        
        Input(unsigned char pin);
    public:
        PinState read();
    };
    
    template<typename InterfacePolicy>
    class Output
    {
        const unsigned char pin_;
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
    
    class SystemInterface
    {
        
        static constexpr const char* baseGPIOFile = "/sys/class/gpio";
        
        static constexpr const char* exportFile = "/sys/class/gpio/export";
        static constexpr const char* unexportFile = "/sys/class/gpio/unexport";
        
        std::string strPin_;
        
    public:
        
        SystemInterface(unsigned char pin);
        
        template<template<class> class Direction>
        void init() const;
        
        void set(PinState value) const;
        
        PinState read() const;
        
        ~SystemInterface();
      
    };
    
    
    
    template<template<class> class DirectionPolicy, typename InterfacePolicy = SystemInterface>
    class GPIO : public DirectionPolicy<InterfacePolicy>
    {
        using SelfType = GPIO<DirectionPolicy, InterfacePolicy>;
        
    public:
        GPIO(unsigned short pin);
        
        GPIO(const GPIO& other) = delete;

        GPIO& operator=(const GPIO& other) = delete;
        
        ~GPIO();
        
        bool operator==(const GPIO& other) const;
    };
}

#endif // IO_GPIO_H


#include "../tpl/gpio.cpp"