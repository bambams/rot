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

#include <RotCypher.hpp>

RotCypher::RotCypher(void):
    numPlaces_(0)
{
}

RotCypher::RotCypher(const unsigned int numPlaces):
    numPlaces_(numPlaces)
{
}

RotCypher::~RotCypher(void) {}

unsigned int RotCypher::getNumPlaces(void) const
{
    return this->numPlaces_;
}

std::vector<Range> RotCypher::getRanges(void) const
{
    return this->ranges_;
}

unsigned int RotCypher::setNumPlaces(const unsigned int value)
{
    return this->numPlaces_ = value;
}

std::vector<Range> RotCypher::setRanges(const std::vector<Range> & value)
{
    return this->ranges_ = value;
}

char RotCypher::decypher(const char & c) const
{
    for(std::vector<Range>::const_iterator it=this->ranges_.begin();
            it!=this->ranges_.end();
            it++)
    {
        int b, e, l;
        int shifted;
        const Range & r = *it;

        b = (int)r.getBeginning();
        e = (int)r.getEnd();
        l = e - b + 1;

        if(c < b || c > e)
            continue;

        shifted = (int)c - b - this->getNumPlaces();

        if(shifted < 0)
            shifted = l + shifted;

        return shifted % l + b;
    }

    return c;
}

char RotCypher::encypher(const char & c) const
{
    for(std::vector<Range>::const_iterator it=this->ranges_.begin();
            it!=this->ranges_.end();
            it++)
    {
        int b, e, l;
        const Range & r = *it;

        b = (int)r.getBeginning();
        e = (int)r.getEnd();
        l = e - b + 1;

        if(c < b || c > e)
            continue;

        return ((int)c - b + this->getNumPlaces()) % l + b;
    }

    return c;
}

