/*******************************************************************
Copyright 2014 Darko Lukic, email: lukicdarkoo@gmail.com

This file is part of WriteSmart. WriteSmart is a fun education game.
There is a question and answers which falling down and user needs to 
collect correct answer. Your sprite is influenced by unknown forses 
and you need to use arrow keys to stay on right way.

WriteSmart is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

WriteSmart is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with WriteSmart.  If not, see <http://www.gnu.org/licenses/>.

*******************************************************************/

#include "Config.h"

Config::Config() {
    BackgroundSpeed = 2.0;
    FrozenQuestion = 120; //number of frames while answers are sticket to top
}

const std::string Config::LevelNames[] = { "6.0", "7.0", "8.0", "9.0", "10.0" };
const float Config::LevelSpeeds[] = { 2.71, 3.14, 4.2, 5.0, 6.0 };
const int Config::LevelNumber = 5;
