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

#include "PlayGround.h"

void PlayGround::start() {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	screen = SDL_SetVideoMode(Config::ScreenWidth, Config::ScreenHeight, 32, SDL_SWSURFACE);

	initObjects();

	Uint32 start;
	running = true;
	while (running) {
		start = SDL_GetTicks();

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					running = false;
				break;

				case SDL_KEYDOWN:
					keysDown.set(event.key.keysym.sym);
				break;

				case SDL_MOUSEBUTTONDOWN:
					//malo improvizacije ako se bude portovalo na android :)
					if (event.button.x < Config::ScreenWidth / 2)
						keysDown.Left = true;
					else keysDown.Right = true;
				break;
			}
		}

		background.update();

		if (window == WINDOW_START && keysDown.Enter) {
		    keysDown.Enter = false;
			window = WINDOW_PLAYING;
		}


		if (window == WINDOW_PLAYING) {
			question.update();
			sprite.update();

			if (question.readyToCheck) {
                if (!(question.safeXFrom <= sprite.x && question.safeXTo >= sprite.x)) {
                    window = WINDOW_END_ANIMATION;

                } else points += (int) (config.BackgroundSpeed * 10);
			}

			if (sprite.x < 65 || sprite.x > 410)
                window = WINDOW_END_ANIMATION;
		}

		else if (window == WINDOW_END_ANIMATION) {
            if (sprite.endAnimationUpdate() == 0)
                window = WINDOW_END;
		}

		else if (window == WINDOW_START) {
			startWindow.update();
		}

		else if (window == WINDOW_END) {
		    endWindow.update();

		    if (keysDown.Enter) {
		        keysDown.Enter = false;
                newGame();
		    }
		}


		SDL_Flip(screen);

		if (1000/Config::FPS > SDL_GetTicks() - start)
			SDL_Delay(1000/Config::FPS - (SDL_GetTicks() - start));
	}
}

void PlayGround::initObjects() {
    window = WINDOW_START;
	points = 0;
	keysDown.setAllToFalse();
	config.BackgroundSpeed = Config::LevelSpeeds[0];

	sprite.init();
	sprite.screen = screen;
	sprite.keysDown = &keysDown;

	background.init();
	background.screen = screen;
	background.config = &config;
	background.points = &points;

	question.init();
	question.screen = screen;
	question.config = &config;


	startWindow.init();
	startWindow.screen = screen;
	startWindow.keysDown = &keysDown;
	startWindow.config = &config;

	endWindow.init();
	endWindow.screen = screen;
	endWindow.keysDown = &keysDown;
	endWindow.points = &points;
}



void PlayGround::gameEnd() {
	window = WINDOW_END;


}

void PlayGround::newGame() {
    points = 0;
    initObjects();
}

PlayGround::~PlayGround() {
	SDL_FreeSurface(screen);
}
