// fo16.hpp
// Fo16 format support
// Intended compatibility: c++17
//
// Created by Alejandro Castro García on 14 April 2021
/*
Licensed under the MIT License.
 
Copyright (c) 2021 Faustic Inferno SL
 
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#ifndef fo16_hpp
#define fo16_hpp

#include "pieces.hpp"

#include <array>

namespace fauces
{

class Fo16_unit_loader : Translated_unit_loader
{
public:
    Fo16_unit_loader(const std::string& path) : path {path} {}
    bool uuid_recognized(const std::array<unsigned char, 16>& try_uuid)
    {
        static const std::array<unsigned char, 16> uuid =
        {
            0xec, 0x4b, 0x79, 0xc8, 0x57, 0xee, 0x4b, 0xad,
            0x96, 0xcf, 0x93, 0x85, 0x48, 0xa2, 0xe0, 0x4b
        };
        return try_uuid == uuid;
    }
private:
    const std::string path;
    Translated_unit load()
    {
        throw Translated_unit_error();
    }
};

}

#endif /* fo16_hpp */
