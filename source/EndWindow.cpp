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

#include "EndWindow.h"
#include <stdlib.h>
#include "Helper.h"
#include "Config.h"

#define HS_ACTIVE_TEXT_COLOR 00, 66, 255
#define HS_TEXT_COLOR 33, 33, 33
#define DESCRIPTION_TEXT_COLOR 33, 33, 33
#define BACKGROUND_COLOR 0xEEEEEE
#define TITLE_TEXT_COLOR 33, 33, 33

void EndWindow::insertPlayerInList(int i) {
    playersRank = i;

    names.insert(names.begin() + i, "???");
    results.insert(results.begin() + i, *points);
}

void EndWindow::initFirstFrame() {
    keysDown->Character = 0;

    int i = 0;
    for (; i < 5; i++) {
        SDL_Rect scoreNameHolder;
        scoreNameHolder.x = backRect.x + 50;
        scoreNameHolder.y = titleHolder.y + 50 + i*20;

        scoreNamesHolder.push_back(scoreNameHolder);

        SDL_Surface *surface;
        scoreNamesSurface.push_back(surface);
    }

    bool playerInserted = false;
    i = 0;
    for (; i < names.size() && i < 5; i++)
        if (*points >= results.at(i)) {
            insertPlayerInList(i);
            playerInserted = true;
            break;
        }

    if (names.size() < 5 && !playerInserted)
        insertPlayerInList(i);
}

void EndWindow::updateScoreName() {
    if (playersRank != -1) {
        if (keysDown->Character != 0) {
            names.at(playersRank) += keysDown->Character - ((keysDown->Character != ' ') ? 32 : 0);
            keysDown->Character = 0;
        }

        if (keysDown->Backspace) {
            if (names.at(playersRank).length() > 0)
                names.at(playersRank) = names.at(playersRank).substr(0, names.at(playersRank).length() - 1);

            keysDown->Backspace = false;
        }
    }
}

void EndWindow::saveScoreBoard() {
    FILE *pf = fopen("data/Results.txt", "w");

    int i = 0;
    for (; i < 5 && i < names.size(); i++) {
        fputs(names.at(i).c_str(), pf);
        fputs("\n", pf);
        fputs(Helper::convertInt(results.at(i)).c_str(), pf);
        fputs("\n", pf);
    }

    fclose(pf);
}

void EndWindow::updateHighScoreBoard() {
    int i = 0;
    for (; i < 5 && i < names.size(); i++) {
        std::string row = Helper::convertInt(i + 1) + ". " + names.at(i) + " (" + Helper::convertInt(results.at(i)) + ")";

        SDL_Color activeColor = { HS_ACTIVE_TEXT_COLOR };
		SDL_Color color = { HS_TEXT_COLOR };

        scoreNamesSurface.at(i) = TTF_RenderText_Blended(scoreNamesFont, 
												row.c_str(), 
												(playersRank == i) ? activeColor : color
											);

        SDL_BlitSurface(scoreNamesSurface.at(i), NULL, screen, &scoreNamesHolder.at(i));
    }
}

void EndWindow::update() {
    if (!firstAppear) {
        firstAppear = true;
        initFirstFrame();
    }

    SDL_FillRect(screen, &backRect, BACKGROUND_COLOR);
    SDL_BlitSurface(titleSurface, NULL, screen, &titleHolder);



    SDL_Color color = { DESCRIPTION_TEXT_COLOR };
    descriptionSurface = TTF_RenderText_Blended(descriptionFont,
                                                ((playersRank == -1) ?
                                                 "Pritisni [Enter] za novu igru." :
                                                 "Upisi ime i pritisni [Enter] za potvrdu imena."),
                                                 color);
    SDL_BlitSurface(descriptionSurface, NULL, screen, &descriptionHolder);


    updateScoreName();
    updateHighScoreBoard();

    if (keysDown->Enter && playersRank >= 0) {
        saveScoreBoard();
        keysDown->Enter = false;
        playersRank = -1;
    }
}

void EndWindow::init() {
	titleSurface = NULL;
	descriptionSurface = NULL;
	titleFont = NULL;
	descriptionFont = NULL;
	scoreNamesFont = NULL;
	
    backRect.w = Config::ScreenWidth;
    backRect.h = 200;
    backRect.x = 0;
    backRect.y = 200;

    titleFont = TTF_OpenFont("data/LiberationSans-Regular.ttf", 36);
    titleHolder.x = Config::ScreenWidth / 2 - 28 * 4;
    titleHolder.y = backRect.y + 10;
    SDL_Color color = { TITLE_TEXT_COLOR };
    titleSurface = TTF_RenderText_Blended(titleFont, "KRAJ IGRE", color);

    descriptionFont = TTF_OpenFont("data/LiberationSans-Regular.ttf", 18);
    descriptionHolder.x = 10;
    descriptionHolder.y = backRect.y + backRect.h - 30;

    scoreNamesFont = TTF_OpenFont("data/LiberationSans-Regular.ttf", 16);

    firstAppear = false;
    playersRank = -1;

    prepareResults();
}

void EndWindow::prepareResults() {
    char buffer[50];

    FILE *pf = fopen("data/Results.txt", "r");

    while (fgets(buffer, sizeof(buffer), pf) != NULL) {
        Helper::lastCharFix(buffer);
        names.push_back(buffer);

        fgets(buffer, sizeof(buffer), pf);
        Helper::lastCharFix(buffer);
        results.push_back(atoi(buffer));
    }

    fclose(pf);
}

EndWindow::~EndWindow() {
	if (titleSurface != NULL)
		SDL_FreeSurface(titleSurface);
		
	if (titleFont != NULL)
		TTF_CloseFont(titleFont);

	if (descriptionSurface != NULL)
		SDL_FreeSurface(descriptionSurface);
	
	if (descriptionFont != NULL)
		TTF_CloseFont(descriptionFont);
	
	if (scoreNamesFont != NULL)
		TTF_CloseFont(scoreNamesFont);

	int i = 0;
	for (; i < scoreNamesSurface.size(); i++)
		SDL_FreeSurface(scoreNamesSurface[i]);
}
