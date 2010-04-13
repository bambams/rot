//
// rot is a cipher utility implementing the rudimentary alphabetic rotation cipher.
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
// along with rot.  If not, see <http://www.gnu.org/licenses/>.
//

#include <Range.hpp>

Range::Range(void):
    beginning_(0),
    end_(0)
{
}

Range::Range(const char beginning, const char end):
    beginning_(beginning),
    end_(end)
{
}

char Range::getBeginning(void) const
{
    return this->beginning_;
}

char Range::getEnd(void) const
{
    return this->end_;
}

char Range::setBeginning(const char beginning)
{
    return this->beginning_ = beginning;
}

char Range::setEnd(const char end)
{
    return this->end_ = end;
}

