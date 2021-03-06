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
#include <gpioio.h>
#endif

namespace io 
{
    template<typename InterfacePolicy>
    Input<InterfacePolicy>::Input ( unsigned char pin ) : PinContainer< unsigned char >(pin), interface(pin)
    {
        interface.template init<Input>();
    }

    template<typename InterfacePolicy>
    Output<InterfacePolicy>::Output ( unsigned char pin ) : PinContainer< unsigned char >(pin), interface(pin)
    {
        interface.template init<Output>();
    }


    template<typename InterfacePolicy>
    PinState Input<InterfacePolicy>::read() const
    {
        return interface.template read<Input>();
    }

    template<typename InterfacePolicy>
    void Output<InterfacePolicy>::set ( PinState value ) const
    {
        interface.template set<Output>( value);
    }
}