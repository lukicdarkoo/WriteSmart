#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"

#include "Background.h"
#include "Sprite.h"
#include "Question.h"

#include "StartWindow.h"

#include "EndWindow.h"

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

#define WINDOW_PLAYING 1
#define WINDOW_START 2
#define WINDOW_END 3
#define WINDOW_END_ANIMATION 4


class PlayGround {
	public:
		SDL_Surface *screen;
		KeyStates keysDown;
		void start();
		~PlayGround();

		int window;
		Config config;

	private:
        int points;

		bool running;

		//glavni prozor
		Sprite sprite;
		Question question;
		Background background;

		//uvodni
		StartWindow startWindow;

		//zavrsni
		EndWindow endWindow;

		void initObjects();

		void gameEnd();
		void newGame();
};
