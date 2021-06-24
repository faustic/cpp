// pieces.hpp
// Classes representing the pieces used to build a program
// Intended compatibility: c++17
//
// Created by Alejandro Castro García on 13 April 2021
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


#ifndef pieces_hpp
#define pieces_hpp

#include <vector>
#include <unordered_map>
#include <string>
#include <cstdint>
#include <memory>

namespace fauces
{

using Location =  std::uint_least16_t;
using Size =  std::uint_least16_t;

enum class Ref_type
{
    two_bytes,
    four_halfbytes
};

struct Reference
{
    Ref_type type;
    Location pos;
};

enum class Sym_type
{
    code,
    data
};

struct Sym_type_bad {};
struct Ref_unresolved {};
struct Prog_nocode {};
struct Prog_toobig {};

struct Symbol
{
    Location pos;
    Size size;
    Sym_type type;
    std::vector<Reference> references_in_code;
    std::vector<Reference> references_in_data;
    bool is_external()
    {
        return pos == 0xffff && size == 0xffff;
    }
};

struct Translated_unit_error {};

struct Linked_program
{
    std::vector<unsigned char> code;
    std::vector<unsigned char> data;
    std::unordered_map<std::string, Symbol> int_symbols;
    std::unordered_map<std::string, Symbol> ext_symbols;
    
    void load_symbol(const Symbol& symbol,
                                    const std::vector<unsigned char>& origin);
};

class Linked_program_saver
{
public:
    virtual void save(Linked_program& prog) = 0;
    virtual ~Linked_program_saver() = default;
};

struct Translated_unit
{
    std::vector<unsigned char> code;
    std::vector<unsigned char> data;
    std::unordered_map<std::string, Symbol> symbols;
};

class Translated_unit_loader
{
public:
    virtual std::unique_ptr<Translated_unit> load() = 0;
    virtual ~Translated_unit_loader() = default;
};

using Instantiation_unit = Translated_unit;

class Supply
{
public:
    void add_unit(std::unique_ptr<Translated_unit> unit)
    {
        units.push_back(move(unit));
    }
    
    void clear()
    {
        units.clear();
    }
    
    Linked_program link();

private:
    std::vector<std::unique_ptr<Translated_unit>> units;
    void add_start(Linked_program& prog);
};

} // namespace fauces

#endif /* pieces_hpp */
