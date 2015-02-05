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

#ifndef IO_TRANSMITTER_H
#define IO_TRANSMITTER_H

#include <type_traits>

#include "pin.h"
#include "gpio.h"
#include "frequency.h"
#include "clock.h"

namespace io {

    template<typename FreqPolicy = timer::RuntimeFreq<unsigned long> >
    class Transmitter // : FreqPolicy
    {
        const unsigned long frequency_;
        const unsigned char startSeq_;
        const GPIO<Output> gpio_;
        const long period_;
        
        template<typename T>
        Transmitter& send( T value );
        
    public:
        
        template<typename InterfaceType>
        Transmitter(GPIO<Output, InterfaceType>& gpio, unsigned char startSeq, typename FreqPolicy::TickType frequency );

        template<typename InterfaceType>
        Transmitter(GPIO<Output, InterfaceType>&& gpio, unsigned char startSeq, typename FreqPolicy::TickType frequency );
        
        
        Transmitter(const Transmitter& other) = default;
        
        template<typename T>
        Transmitter& operator<< ( T value );
        
        ~Transmitter();
        
        template<unsigned int IntervalDivision>
        void PWM( unsigned char level );
        
        Transmitter& operator=(const Transmitter& other) = delete;
        
        bool operator==(const Transmitter& other) const = delete;
        
        
    };
    
    template<typename FreqPolicy>
    template<typename InterfaceType>
    Transmitter<FreqPolicy>::Transmitter( GPIO<Output, InterfaceType>& gpio, unsigned char startSeq, typename FreqPolicy::TickType frequency ) 
        : gpio_(gpio), startSeq_(startSeq), frequency_(frequency), 
        period_( static_cast<float>(1000000000) / ( static_cast<float>(frequency_ ) ))
    {
        std::cout << "period : " << period_ << std::endl;
    }
    
    template<typename FreqPolicy>
    template<typename InterfaceType>
    Transmitter<FreqPolicy>::Transmitter( GPIO<Output, InterfaceType>&& gpio, unsigned char startSeq, typename FreqPolicy::TickType frequency ) 
        : gpio_(gpio), startSeq_(startSeq), frequency_(frequency), 
        period_( static_cast<float>(1000000000) / ( static_cast<float>(frequency_ ) ))
    {
        std::cout << "period : " << period_ << std::endl;
    }
    
    
    template<typename FreqPolicy>
    template<typename T>
    Transmitter<FreqPolicy>& Transmitter<FreqPolicy>::operator<< ( T value )
    {
        send( startSeq_ );
        send( value );
    }

    template<typename FreqPolicy>
    template<typename T>
    Transmitter<FreqPolicy>& Transmitter<FreqPolicy>::send ( T value )
    {
        size_t s = sizeof( T ) * 8;
        std::cout << "send " << value << " od size (" << s << ")..." << std::endl;
        typename std::remove_reference<T>::type val = value;
        while( s-- )
        {
            std::cout << "(s == " << s << ") set " << (val & 0x1) << std::endl;
            gpio_.set( (val & 0x1) ? PinState::HIGH : PinState::LOW );
            val >>= 0x1;
            std::cout << "sleep " << period_ << " nano seconds" << std::endl;
            std::this_thread::sleep_for(std::chrono::nanoseconds( period_  ) );
        };
    }
    
    template<typename FreqPolicy>
    template<unsigned int IntervalDivision>
    void Transmitter<FreqPolicy>::PWM(unsigned char level)
    {
        //static Clock<>
    }

    template<typename FreqPolicy>
    Transmitter<FreqPolicy>::~Transmitter()
    {

    }
}

#endif // IO_TRANSMITTER_H
