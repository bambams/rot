#
# rot is a cypher utility implementing the rudimentary alphabetic rotation cypher.
# Copyright (C) 2009 Brandon McCaig
#
# This file is part of rot.
#
# rot is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# rot is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with rot.  If not, see <http://www.gnu.org/licenses/>.
#

#ifndef RANGE_HPP
    #define RANGE_HPP

class Range
{
private:
    char beginning_;
    char end_;
public:
    Range(void);
    Range(const char, const char);

    char getBeginning(void) const;
    char getEnd(void) const;
    char setBeginning(const char);
    char setEnd(const char);
};

#endif
