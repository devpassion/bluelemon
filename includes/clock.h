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

#ifndef CLOCK_H
#define CLOCK_H

#include <chrono>
#include <type_traits>

#include "frequency.h"

namespace timer
{
    
    
    class ProgramExecution
    {
        void setExecuteFunction( std::function<void()> functor );
        
        void start();
        
        void stop();
    };
    
    class InterruptExecution
    {
        void setExecuteFunction( std::function<void()> functor );
        
        void start();
        
        void stop();
    };
    
    template<typename FreqPolicy, typename ExecutionPolicy>
    class Clock : FreqPolicy, ExecutionPolicy
    {
        public:
        
        //template<typename TickType>
        Clock(typename FreqPolicy::TickType ticksPerSecond);
        
        /*template<int n, int d>
        Clock( typename std::enable_if<std::is_same<FreqPolicy,CompileTimeFreq>::value,std::ratio<n,d>>::type ticksPerSecond );*/
        
        Clock(const Clock& other);
        ~Clock();
        
        inline void setExecuteFunction( std::function<void()> functor );
        
        inline void start();
        
        inline void stop();
        
        Clock& operator=(const Clock& other);
        bool operator==(const Clock& other) const;
    };

    
    /*template<typename FreqPolicy, typename ExecutionPolicy>
    template<typename TickType>
    Clock<FreqPolicy, ExecutionPolicy>::Clock( typename std::enable_if<std::is_arithmetic<TickType>::value, TickType>::type ticksPerSecond ) : FreqPolicy(ticksPerSecond) {}
    */
    
    template<typename FreqPolicy, typename ExecutionPolicy>
    Clock<FreqPolicy, ExecutionPolicy>::Clock( typename FreqPolicy::TickType ticksPerSecond ) : FreqPolicy(ticksPerSecond) {}
   
    
    // sniff, can't partial specialize class
    /*template<typename FreqPolicy, typename ExecutionPolicy>
    template<int n, int d>
    Clock<FreqPolicy, ExecutionPolicy>::Clock( typename std::enable_if<std::is_same<FreqPolicy,CompileTimeFreq>::value,std::ratio<n,d>>::type ticksPerSecond ) : FreqPolicy( ticksPerSecond ) {}
    */
    
}
#endif // CLOCK_H
