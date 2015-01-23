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

#ifndef IO_IO_EXCEPTION_H
#define IO_IO_EXCEPTION_H

#include <string>
#include <stdexcept>

namespace io 
{

    class io_exception : public std::runtime_error
    {
    public:
        io_exception(const std::string& msg);
        io_exception(const char* msg);
        
        
    };
}

#endif // IO_IO_EXCEPTION_H
