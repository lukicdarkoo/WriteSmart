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

#include "KeyStates.h"

KeyStates::KeyStates() {
	setAllToFalse();
}

void KeyStates::set(int event) {
	switch (event) {
		case SDLK_UP:
			Up = true;
		break;

		case SDLK_DOWN:
			Down = true;
		break;

		case SDLK_LEFT:
			Left = true;
		break;

		case SDLK_RIGHT:
			Right = true;
		break;

		case SDLK_SPACE:
			Space = true;
		break;

		case SDLK_BACKSPACE:
            Backspace = true;
        break;

        case SDLK_RETURN:
            Enter = true;
        break;
	}



	Character = 0;

	if ((event >= 'a' && event <= 'z') ||
     (event >= 'A' && event <= 'Z') ||
     event == ' ') {
        Character = event;
     }
}

void KeyStates::setAllToFalse() {
	Up = false;
	Down = false;
	Space = false;
	Left = false;
	Right = false;
	Backspace = false;
	Enter = false;
}
