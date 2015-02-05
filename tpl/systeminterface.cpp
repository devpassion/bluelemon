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

#include "systeminterface.h"

#include <sstream>
#include <fstream>
#include <thread>

#include "gpioio.h"
#include "io_exception.h"


using namespace io;



template<typename InType>
void SystemInterface::sendToFile( std::string file, InType str, std::string errorMsg ) throw(io_exception)
{
    std::ofstream fos( file );
    if( !fos )
    {
        throw io_exception( errorMsg + "file : " + file );
    }
    fos << str;
    fos.close();
}

template<typename OutType>
OutType SystemInterface::readFromFile( std::string file, std::string errorMsg ) throw(io_exception)
{
    std::ifstream fis( file );
    if( !fis )
    {
        throw io_exception( errorMsg + "(at read input value)" );
    }
    char val;
    fis >> val;
    fis.close();
    return static_cast<OutType>( val );
}


SystemInterface::SystemInterface ( unsigned char pin ) throw(io_exception) : pin_(pin) 
{
    
    std::stringstream ss;
    ss << static_cast<short>(pin);
    strPin_ = ss.str();
    
    std::clog << "create one instance for pin " << strPin_ << std::endl;
    
    mutexes_[pin].lock();
    
    if( UserCounts[pin] == 0 )
    {
        std::ofstream fos( exportFile );
        auto start = std::chrono::steady_clock::now();  
        while( !fos )
        {
            auto elapsed = std::chrono::steady_clock::now() - start;
            if( elapsed.count() >  fileTimeout)
            {
                throw io_exception( "Pin " + strPin_ + " (at export)" );
            }
        }
        fos << strPin_;
        fos.close();
    }
    
    UserCounts[pin]++;
    mutexes_[pin].unlock();
}


template<template<class> class Direction>
void SystemInterface::init (  )  const throw(io_exception)
{
    // just for test !
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    sendToFile( baseGPIOFile + std::string("/gpio") + strPin_ + "/direction", StrDirectionTrait<Direction>::value, "Pin " + strPin_ + "(at direction set)" );
    /*std::string file(baseGPIOFile + std::string("/gpio") + strPin_ + "/direction");
    std::ofstream fos( file );
    if( !fos )
    {
        throw io_exception( "Pin " + strPin_ + "(at direction set), file :" + file );
    }
    fos << StrDirectionTrait<Direction>::value;
    fos.close();*/
    
}

SystemInterface::SystemInterface ( const SystemInterface& other ) throw(io_exception) : SystemInterface(other.pin_)
{

}


template<template<class> class Direction>
typename std::enable_if< std::is_same_tpl<Direction,Input>::value,PinState>::type SystemInterface::read (  ) const throw(io_exception)
{
    return readFromFile<PinState>(  "/sys/class/gpio/gpio" + strPin_ + "/value", "Pin " + strPin_ );
    /*std::ifstream fis( "/sys/class/gpio/gpio" + strPin_ + "/value" );
    if( !fis )
    {
        throw io_exception( "Pin " + strPin_ + "(at read input value)" );
    }
    char val;
    fis >> val;
    fis.close();
    return static_cast<PinState>( val );*/
}


template<template<class> class Direction>
typename std::enable_if< std::is_same_tpl<Direction,Output>::value>::type SystemInterface::set ( PinState value ) const throw(io_exception)
{
    
    sendToFile( "/sys/class/gpio/gpio" + strPin_ + "/value", static_cast<char>( value ), "Pin " + strPin_ + "(at write output value)" );
    
    /*std::ofstream fos( "/sys/class/gpio/gpio" + strPin_ + "/value" );
    if( !fos )
    {
        throw io_exception( "Pin " + strPin_ + "(at write output value)" );
    }
    fos << static_cast<char>( value );
    fos.close();*/
}



SystemInterface::~SystemInterface()
{
    // std::clog << "delete one instance (pin " << strPin_ << ")" << std::endl;
    mutexes_[pin_].lock();
    UserCounts[pin_]--;
    if( UserCounts[pin_] == 0 )
    {
        sendToFile( unexportFile, strPin_, "ERROR : Pin " + strPin_ + "(at unexport)" );
    
        //std::clog << "delete file" << std::endl;
        
        /*std::ofstream fos( unexportFile );
        if( !fos )
        {
            std::cerr <<  "ERROR : Pin " + strPin_ + "(at unexport)";
        }
        fos << strPin_;
        fos.close();*/
    }
    mutexes_[pin_].unlock();
}
