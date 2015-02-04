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

#ifndef IO_SYSTEMINTERFACE_H
#define IO_SYSTEMINTERFACE_H

namespace io {

template<int Val>
    struct NullFunctor
    {
        static constexpr unsigned short value = 0;
    };
    
    
    
    class SystemInterface
    {
        
        static constexpr const char* baseGPIOFile = "/sys/class/gpio";
        
        static constexpr const char* exportFile = "/sys/class/gpio/export";
        static constexpr const char* unexportFile = "/sys/class/gpio/unexport";
        
        static constexpr int fileTimeout = 500;
        
        static std::array<unsigned short, 18> UserCounts;
        static std::array<std::mutex, 18> mutexes_;
        
        const unsigned char pin_;
        std::string strPin_;
        
    public:
        
        SystemInterface(unsigned char pin) throw(io_exception);
        
        SystemInterface(const SystemInterface& other) throw(io_exception);
        
        SystemInterface& operator=(const SystemInterface& other) = delete;
        
        template<template<class> class Direction>
        void init() const throw(io_exception);
        
        void set(PinState value) const throw(io_exception);
        
        PinState read() const throw(io_exception); 
        
        ~SystemInterface();
      
    };
}

#include "../tpl/systeminterface.cpp"

#endif // IO_SYSTEMINTERFACE_H
