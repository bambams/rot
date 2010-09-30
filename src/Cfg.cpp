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

#include <Cfg.hpp>

const CipherMode Cfg::DEFAULT_CIPHER_MODE = ENCIPHER;
const InputMode Cfg::DEFAULT_INPUT_MODE = FILEIO;

Cfg::Cfg(void):
    printHelp_(false),
    numPlaces_(0),
    cipherMode_(DEFAULT_CIPHER_MODE),
    inputMode_(DEFAULT_INPUT_MODE)
{
}

Cfg::operator bool(void) const
{
    return true;
}

void Cfg::addRange(const std::string r)
{
    std::stringstream ss;
    int beginning = -1;
    int end = -1;

    if(r.length() != 4)
    {
        throw std::runtime_error(
                std::string("Invalid range '")
                + r
                + "' detected. Expected 4 digit hex number.");
    }

    ss << r.substr(0, 2);
    ss << ' ';
    ss << r.substr(2);

    ss << std::hex;

    ss >> beginning;
    ss >> end;

    if(beginning == -1)
    {
        throw std::runtime_error(
                std::string("Invalid range detected. Failed to parse ")
                        + "beginning character code '"
                        + r.substr(0, 2)
                        + "'.");
    }

    if(end == -1)
    {
        throw std::runtime_error(
                std::string("Invalid range detected. Failed to parse ")
                        + "end character code '"
                        + r.substr(2)
                        + "'.");
    }

    this->ranges_.push_back(Range(beginning, end));
}

void Cfg::assertInputSourceUnset(void) const
{
    if(this->getInputMode() != DEFAULT_INPUT_MODE
            || this->getFile() != "")
    {
        throw std::runtime_error(
                "Conflicting option detected. The input source has "
                "already been specified.");
    }
}

void Cfg::assertNumPlacesUnset(void) const
{
    if(this->getNumPlaces() != 0)
    {
        throw std::runtime_error(
                "Conflicting option detected. The number of "
                "places has already been specified.");
    }
}

std::vector<std::string> Cfg::getArgs(void) const
{
    return this->args_;
}

std::string Cfg::getFile(void) const
{
    return this->file_;
}

CipherMode Cfg::getCipherMode(void) const
{
    return this->cipherMode_;
}

InputMode Cfg::getInputMode(void) const
{
    return this->inputMode_;
}

unsigned int Cfg::getNumPlaces(void) const
{
    return this->numPlaces_;
}

std::vector<Range> Cfg::getRanges(void) const
{
    return this->ranges_;
}

void Cfg::parseOpts(int argc, char * argv[])
{
    int i;
    static struct option long_options[] = {
            {"13",         no_argument,       0, 'C'},
            {"26",         no_argument,       0, '2'},
            {"47",         no_argument,       0, '4'},
            {"argv",       no_argument,       0, 'a'},
            {"decipher",   no_argument,       0, 'd'},
            {"file",       required_argument, 0, 'F'},
            {"help",       no_argument,       0, 'h'},
            {"num-places", required_argument, 0, 'N'},
            {"range",      required_argument, 0, 'R'},
            {0, 0, 0, 0}
        };
    static const char * const short_options = "aCdF:hN:R:";

    while(true)
    {
        int c = getopt_long(argc, argv, short_options, long_options, &i);

        if(c == -1)
            break;

        switch(c)
        {
            case '2':
                this->setNumPlaces(26);
                this->ranges_.clear();
                break;
            case '4':
                this->setNumPlaces(47);
                this->ranges_.clear();
                this->addRange("217E");
                break;
            case 'a':
                this->setInputMode(ARGV);
                break;
            case 'C':
                this->setNumPlaces(13);
                break;
            case 'd':
                this->setCipherMode(DECIPHER);
                break;
            case 'F':
                this->setFile(optarg);
                break;
            case 'h':
                this->printHelp_ = true;
                return;
            case 'N':
                {
                    unsigned int n;
                    std::istringstream ss(optarg);

                    if(!(ss >> n))
                    {
                        throw std::runtime_error(
                                "Failed to parse the number of places.");
                    }

                    this->setNumPlaces(n);
                }
                break;
            case 'R':
                this->addRange(optarg);
                break;
            default:
                throw std::runtime_error(
                        "Unknown option detected. See --help.");
        }
    }

    if(this->getInputMode() != ARGV && optind != argc)
    {
        throw std::runtime_error(
                std::string("Unknown argument: '") + argv[optind] + "'. See "
                "--argv.");
    }

    if(optind < argc)
        for(int i=optind; i<argc; i++)
            this->args_.push_back(argv[i]);

    if(this->getInputMode() == FILEIO && this->getFile() == "")
        this->setFile("-");

    if(this->ranges_.size() == 0)
    {
        this->addRange("415A");
        this->addRange("617A");
    }
}

bool Cfg::printHelp(void) const
{
    return this->printHelp_;
}

CipherMode Cfg::setCipherMode(const CipherMode cipherMode)
{
    return this->cipherMode_ = cipherMode;
}

std::string Cfg::setFile(const std::string file)
{
    this->assertInputSourceUnset();

    return this->file_ = file;
}

InputMode Cfg::setInputMode(const InputMode inputMode)
{
    this->assertInputSourceUnset();

    return this->inputMode_ = inputMode;
}

unsigned int Cfg::setNumPlaces(const unsigned int n)
{
    this->assertNumPlacesUnset();

    return this->numPlaces_ = n;
}

