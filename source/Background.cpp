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

#include "Background.h"
#include "Helper.h"

Background::Background() {
	y = Config::BackgroundHeight - Config::ScreenHeight;
	background.w = Config::ScreenWidth;
	background.h = Config::ScreenHeight;
	background.x = 0;
	background.y = 0;
}

void Background::update() {
	move();
	updatePoints();
}

void Background::init() {
	pointsText = NULL;
	pointsFont = NULL;
	
	backgroundImage = IMG_Load("data/bg.png");

	pointsHolder.x = 20;
	pointsHolder.y = Config::ScreenHeight - 40;
	pointsHolder.w = 50;
	pointsHolder.h = 50;
	pointsFont = TTF_OpenFont("data/LiberationSans-Regular.ttf", 32);
}

void Background::updatePoints() {
    SDL_Color color = {255, 255, 255};
    pointsText = TTF_RenderText_Blended(pointsFont, Helper::convertInt(*points).c_str(), color);
    SDL_BlitSurface(pointsText, NULL, screen, &pointsHolder);
}

void Background::move() {
	//SDL_FillRect(screen, &screen->clip_rect, 0xffffff);

	//y -= config->BackgroundSpeed;
	background.y -= config->BackgroundSpeed;

	if (background.y < 0)
		background.y = Config::BackgroundHeight - Config::ScreenHeight;

	//background.y = (int)y;

	SDL_BlitSurface(backgroundImage, &background, screen, NULL);


    /*
	if (++points_i >= 60) {
        points++;
        points_i = 0;
	}
	*/
}

Background::~Background() {
	SDL_FreeSurface(backgroundImage);
	
	if (pointsText != NULL)
		SDL_FreeSurface(pointsText);
	
	if (pointsFont != NULL)
		TTF_CloseFont(pointsFont);
}
