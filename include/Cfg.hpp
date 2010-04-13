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
// along with rot.  If not, see <http:#www.gnu.org/licenses/>.
//

#ifndef CFG_HPP
    #define CFG_HPP

    #include <getopt.h>
    #include <iostream>
    #include <sstream>
    #include <stdexcept>
    #include <string>
    #include <vector>

class Cfg;

    #include <CipherMode.hpp>
    #include <InputMode.hpp>
    #include <Range.hpp>

class Cfg
{
protected:
    static const CipherMode DEFAULT_CIPHER_MODE;
    static const InputMode DEFAULT_INPUT_MODE;

    bool printHelp_;
    unsigned int numPlaces_;
    CipherMode cipherMode_;
    InputMode inputMode_;
    std::string file_;
    std::vector<std::string> args_;
    std::vector<Range> ranges_;

    void assertInputSourceUnset(void) const;
    void assertNumPlacesUnset(void) const;

    CipherMode setCipherMode(const CipherMode);
    std::string setFile(const std::string);
    InputMode setInputMode(const InputMode);
    unsigned int setNumPlaces(const unsigned int);
public:
    Cfg(void);

    operator bool(void) const;

    void addRange(const std::string);
    std::vector<std::string> getArgs(void) const;
    CipherMode getCipherMode(void) const;
    std::string getFile(void) const;
    InputMode getInputMode(void) const;
    unsigned int getNumPlaces(void) const;
    std::vector<Range> getRanges(void) const;

    void parseOpts(int argc, char * argv[]);
    bool printHelp(void) const;
};

#endif

