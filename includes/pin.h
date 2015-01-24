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

#ifndef IO_PIN_H
#define IO_PIN_H

#include <type_traits>


namespace io
{
     enum PinState : char
    {
        LOW = '0',
        HIGH = '1'
    };
   
    
    template<typename PinType>
    class PinContainer
    {
    public:
        using CPintype = typename std::add_const<PinType>::type;
    private:
        CPintype pin_;
    protected:
        PinContainer( PinType pin );
        typename std::add_rvalue_reference<CPintype>::type getPin() const;
        
    };
}

#include "../tpl/pin.cpp"

#endif

