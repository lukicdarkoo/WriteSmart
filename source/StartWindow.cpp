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

#include "StartWindow.h"
#include "Config.h"
#include "Helper.h"
#include <string>
#include <vector>

#define TITLE_TEXT_COLOR 30, 30, 30
#define BOX_COLOR 0xEEEEEE
#define DESCRIPTION_TEXT_COLOR 30, 30, 30
#define LEVEL_ACTIVE_TEXT_COLOR 00, 66, 255
#define LEVEL_TEXT_COLOR 33, 33, 33


void StartWindow::init() {
	titleSurface = NULL;
	descriptionSurface = NULL;
	levelSurface = NULL;
	authorSurface = NULL;
	versionSurface = NULL;
	
	titleFont = NULL;
	descriptionFont = NULL;
	levelFont = NULL;
	authorFont = NULL;
	versionFont = NULL;
	
	//SDL_FillRect(screen, &questionBox, 0x000000);
	level = 0;
	initTitle();
	initDescription();
	initLevel();
	initAuthor();
	initVersion();
}

void StartWindow::update() {
	showTitle();
	showDescription();
	updateLevel();
	updateAuthor();
	updateVersion();
}

void StartWindow::initVersion() {
	authorHolder.x = Config::ScreenWidth - 140;
	authorHolder.y = titleBack.y + 20;
	authorFont = TTF_OpenFont("data/LiberationSans-Regular.ttf", 14);

	SDL_Color color = {99, 99, 99};
	authorSurface = TTF_RenderText_Blended(authorFont, "v0.9.4", color);
}

void StartWindow::initAuthor() {
	authorHolder.x = Config::ScreenWidth - 18 * 19 - 10;
	authorHolder.y = titleBack.y + titleBack.h - 20;
	authorFont = TTF_OpenFont("data/LiberationSans-Regular.ttf", 14);

	SDL_Color color = {99, 99, 99};
	authorSurface = TTF_RenderText_Blended(authorFont, "by Darko Lukic (lukicdarkoo@gmail.com, spespro.com)", color);
}

void StartWindow::initLevel() {
	levelHolder.x = titleHolder.x;
	levelHolder.y = titleBack.y + 180;
	levelFont = TTF_OpenFont("data/LiberationSans-Regular.ttf", 25);
}

void StartWindow::showDescription() {
    std::string description = "Procitaj pitanje, razmisli i pokupi pravi odgovor. Koristi strelice, lijevo, desno, kako bi ostao na pravom putu. Nivo, odnosno zeljenu prosjecnu ocjenu odaberi sa strelicama lijevo, desno. Pritisni [Enter] za pocetak igre. Srecno!";
	SDL_Color color = { DESCRIPTION_TEXT_COLOR };

	std::vector<std::string> descriptionRows;

	Helper::wrap(descriptionRows, description, 68);

    int i = 0;
    for (; i < descriptionRows.size(); i++) {
        SDL_Rect descriptionHolder;
        descriptionHolder.x = 20;
        descriptionHolder.y = titleBack.y + 80 + i * 20;
        descriptionHolder.w = Config::ScreenWidth;
        descriptionHolder.h = 20;

        descriptionSurface = TTF_RenderText_Blended(descriptionFont, (descriptionRows)[i].c_str(), color);
        SDL_BlitSurface(descriptionSurface, NULL, screen, &descriptionHolder);
    }
}

void StartWindow::showTitle() {
	SDL_FillRect(screen, &titleBack, BOX_COLOR);

	SDL_Color color = { TITLE_TEXT_COLOR };
	titleSurface = TTF_RenderUTF8_Blended(titleFont, "WriteSmart", color);
	SDL_BlitSurface(titleSurface, NULL, screen, &titleHolder);
}


void StartWindow::initTitle() {
	titleBack.x = 0;
	titleBack.y = 200;
	titleBack.w = Config::ScreenWidth;
	titleBack.h = 250;

	titleHolder.x = Config::ScreenWidth / 2 - 48 * 3;
	titleHolder.y = titleBack.y + 20;
	titleHolder.w = Config::ScreenWidth;
	titleHolder.h = 100;
	titleFont = TTF_OpenFont("data/LiberationSans-Regular.ttf", 48);
}

void StartWindow::initDescription() {
	descriptionFont = TTF_OpenFont("data/LiberationSans-Regular.ttf", 16);
}

void StartWindow::updateAuthor() {
    SDL_BlitSurface(authorSurface, NULL, screen, &authorHolder);
}

void StartWindow::updateVersion() {
    SDL_BlitSurface(versionSurface, NULL, screen, &versionHolder);
}

void StartWindow::updateLevel() {
    if (keysDown->Right) {
        keysDown->Right = false;
        level++;

        if (level > Config::LevelNumber - 1)
            level = 0;

        config->BackgroundSpeed = Config::LevelSpeeds[level];
    }

    if (keysDown->Left) {
        keysDown->Left = false;
        level--;

        if (level < 0)
            level = Config::LevelNumber - 1;

        config->BackgroundSpeed = Config::LevelSpeeds[level] - 1;
    }


    SDL_Color color = { LEVEL_TEXT_COLOR };
    SDL_Color activeColor = { LEVEL_ACTIVE_TEXT_COLOR };

    levelHolder.x = 20;
    levelSurface = TTF_RenderText_Blended(levelFont, "Nivo:", color);
    SDL_BlitSurface(levelSurface, NULL, screen, &levelHolder);

    int i = 0;
    for (; i < Config::LevelNumber; i++) {
        levelHolder.x = i * 60 + 120;
        levelSurface = TTF_RenderText_Blended(levelFont, levelByIndex(i).c_str(), (level == i) ? activeColor : color);
        SDL_BlitSurface(levelSurface, NULL, screen, &levelHolder);
    }
}

std::string StartWindow::levelByIndex(int index) {
    return Config::LevelNames[index];

    /*
    switch(index) {
        case 0:
            return "Za 10.0";
            break;

        case 1:
            return "Za 9.0";
            break;

        case 2:
            return "Za 8.0";
            break;

        case 3:
            return "Za 7.0";
            break;

        case 4:
            return "Samo da prodjem";
            break;
    } */
}

StartWindow::~StartWindow() {
	//jos malo improvizacije, radim na vjezbama :(
	
	if (titleSurface != NULL)
		SDL_FreeSurface(titleSurface);
		
	if (titleFont != NULL)
		TTF_CloseFont(titleFont);

	if (descriptionSurface != NULL)
		SDL_FreeSurface(descriptionSurface);
		
	if (descriptionFont != NULL)
		TTF_CloseFont(descriptionFont);

	if (levelSurface != NULL)
		SDL_FreeSurface(levelSurface);
		
	if (levelFont != NULL)
		TTF_CloseFont(levelFont);

	if (authorSurface != NULL)
		SDL_FreeSurface(authorSurface);
		
	if (authorFont != NULL)
		TTF_CloseFont(authorFont);
		
	if (versionFont != NULL)
		TTF_CloseFont(versionFont);
		
	if (versionSurface != NULL)
		SDL_FreeSurface(versionSurface);
}
