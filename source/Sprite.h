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

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include "KeyStates.h"
#include <math.h>

class Sprite {
	public:
		~Sprite();
		SDL_Surface *screen;
		KeyStates *keysDown;
		void update();
		int endAnimationUpdate();

		void init();

		void move();

		int gravity;

		int x;

	private:
		SDL_Rect sprite;
		SDL_Surface *spriteImageSource;
		SDL_Surface *spriteImage;
		int spriteMoveToEnd;

		float currentRotation;
		float toRotate;
		float spriteSize;
		void rotate();
};
