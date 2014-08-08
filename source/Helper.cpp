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

#include "Helper.h"
#include <string>
#include <vector>
#include <iostream>

int Helper::random(int min, int max) {
	return min + (rand() % (int)(max - min + 1));
}

void  Helper::wrap(std::vector<std::string>& rows, std::string text, int chars) {

    int j = 0;
    int i = chars;

    while (i < text.length()) {
        while (text[i] != ' ')
            i--;

        rows.push_back(text.substr(j, i - j));
        j = i + 1;

        i = j + chars;
    }

    rows.push_back(text.substr(j, i - j));
}


std::string Helper::convertInt(int number)
{
    //u komentaru algoritam sa stackoverflowa, a ovaj sto se koristi je moj :)
    //manje memorije, brzi, manje linija koda
    //konacno nesto na faksu da napisem gdje se barem malo mozak koristi

    std::string returnValue = "";

    int dev = 1;
    while (number / (dev *= 10) > 0);

    while ((dev /= 10) >= 1)
        returnValue += (number / dev) % 10 + 48;

    /*
    if (number == 0)
        return "0";
    std::string temp="";
    std::string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0;i<temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    */


    return returnValue;
}

void Helper::lastCharFix(char *text) {
    int i = 0;
    while (text[i] != 0)
        i++;

    text[--i] = 0;
}
