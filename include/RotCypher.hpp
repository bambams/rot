//
// rot is a cypher utility implementing the rudimentary alphabetic rotation cypher.
// Copyright (C) 2009 Brandon McCaig
//
// This file is part of rot.
//
// rot is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// rot is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with rot.  If not, see <http:#www.gnu.org/licenses/>.
//

#ifndef ROTCYPHER_HPP
    #define ROTCYPHER_HPP

    #include <cctype>
    #include <vector>

class RotCypher;

    #include <Range.hpp>

class RotCypher
{
protected:
    unsigned int numPlaces_;
    std::vector<Range> ranges_;
public:
    RotCypher(void);
    RotCypher(const unsigned int);
    ~RotCypher(void);

    unsigned int getNumPlaces(void) const;
    std::vector<Range> getRanges(void) const;
    unsigned int setNumPlaces(const unsigned int);
    std::vector<Range> setRanges(const std::vector<Range> &);

    char decypher(const char & c) const;
    char encypher(const char & c) const;
};


#endif

