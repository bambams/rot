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

#include <fstream>
#include <iostream>
#include <stdexcept>

#include <Cfg.hpp>
#include <RotCypher.hpp>

Cfg parseArgs(int argc, char * argv[]);
void printCypherLine(const RotCypher &, const CypherMode, const std::string);
void printHelp(std::ostream & = std::cout);

int main(int argc, char * argv[]) try
{
    Cfg cfg = parseArgs(argc, argv);
    RotCypher rot;

    if(!cfg)
    {
        printHelp(std::cerr);

        return 1;
    }
    else if(cfg.printHelp())
    {
        printHelp();

        return 0;
    }

    rot.setNumPlaces(cfg.getNumPlaces());
    rot.setRanges(cfg.getRanges());

    switch(cfg.getInputMode())
    {
        case ARGV:
        {
            const std::vector<std::string> & args = cfg.getArgs();
            std::ostringstream ss;

            for(std::vector<std::string>::const_iterator it = args.begin();
                    it != args.end();
                    it++)
            {
                if(it != args.begin())
                    ss << ' ';

                ss << *it;
            }

            printCypherLine(rot, cfg.getCypherMode(), ss.str());
        }
        break;
        case FILEIO:
        {
            std::string line;

            if(cfg.getFile() == "-")
            {
                while(std::getline(std::cin, line))
                    printCypherLine(rot, cfg.getCypherMode(), line);
            }
            else
            {
                std::ifstream in(cfg.getFile().c_str());

                if(!in)
                {
                    throw std::runtime_error(
                            "Failed to open input file.");
                }

                while(std::getline(in, line))
                    printCypherLine(rot, cfg.getCypherMode(), line);

                in.close();

                if(!in.eof())
                {
                    throw std::runtime_error(
                            "An error occurred while reading input "
                            "file.");
                }
            }
        }
        break;
    }

    return 0;
}
catch(std::exception & ex)
{
    std::cerr << "Unhandled exception caught: " << ex.what() << std::endl;

    return 2;
}
catch(...)
{
    std::cerr << "Unhandled exception caught. Unknown type." << std::endl;

    return 2;
}

void printCypherLine(const RotCypher & rot, const CypherMode mode,
        const std::string line)
{
    for(int i=0, l=line.length(); i<l; i++)
    {
        const char & c = line[i];

        switch(mode)
        {
            case DECYPHER:
                std::cout << rot.decypher(c);
                break;
            case ENCYPHER:
                std::cout << rot.encypher(c);
                break;
            default:
                throw std::runtime_error("Invalid CypherMode detected.");
        }
    }

    std::cout << std::endl;
}

Cfg parseArgs(int argc, char * argv[])
{
    Cfg cfg;

    cfg.parseOpts(argc, argv);

    return cfg;
}

void printHelp(std::ostream & out)
{
    const char * const HELP =
"  Takes character data as input and rotates characters a\n"
"  number of places. Can be used for rot13 and rot<N>.\n"
"\n"
"    rot { -h | --help }\n"
"    rot [ -a | --argv | -F<file> | --file=<file> ]\n"
"            [ -d | --decypher ] [ -C | --13 | -N<numPlaces>\n"
"                | --num-places=<numPlaces> ]\n"
"            [ -R<range> | --range=<range> ... ]\n"
"\n"
"    -a\n"
"    --argv                       Take input from anonymous arguments\n"
"                                 instead of stdin.\n"
"\n"
"    -C\n"
"    --13                         Rot13 mode. Same as -N13.\n"
"\n"
"    --47                         Rot47 mode. Same as -N47 -R217E.\n"
"\n"
"    -d\n"
"    --decypher                   Rotate places backwards instead of\n"
"                                 forwards.\n"
"\n"
"    -F<file>\n"
"    --file=<file>                Specify a file as input instead of\n"
"                                 stdin. stdin can also be specified\n"
"                                 with a dash (-). For a file named -,\n"
"                                 qualify it with a path\n"
"                                 (i.e., \"./-\").\n"
"\n"
"    -h\n"
"    --help                       Print this message and exit.\n"
"\n"
"    -N<numPlaces>\n"
"    --num-places=<numPlaces>     Specify the number of places to rotate\n"
"                                 alphabetic characters.\n"
"\n"
"    -R<range>\n"
"    --range=<range>              Specify the range of character codes that\n"
"                                 is rotated. Expected is a 4 digit hex\n"
"                                 number. The first two digits specify the\n"
"                                 beginning of the range and the last two\n"
"                                 digits specify the end. The default\n"
"                                 behavior, ASCII alphabet characters only,\n"
"                                 has two ranges: 415A and 617A.\n"
"\n";

    out << HELP;
}

