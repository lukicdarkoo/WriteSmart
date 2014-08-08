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
#include "SDL/SDL_ttf.h"
#include <string>
#include "KeyStates.h"
#include "Config.h"

class StartWindow {
	public:
		SDL_Surface *screen;

		~StartWindow();
		void update();
		void init();
		KeyStates *keysDown;
		Config *config;

	private:
		SDL_Rect questionBox;

		TTF_Font *titleFont;
		SDL_Surface *titleSurface;
		SDL_Rect titleHolder;
		SDL_Rect titleBack;


		TTF_Font *descriptionFont;
		SDL_Surface *descriptionSurface;
		SDL_Rect descriptionHolder;

        TTF_Font *levelFont;
		SDL_Surface *levelSurface;
		SDL_Rect levelHolder;

        TTF_Font *authorFont;
		SDL_Surface *authorSurface;
		SDL_Rect authorHolder;

		TTF_Font *versionFont;
		SDL_Surface *versionSurface;
		SDL_Rect versionHolder;

		void showTitle();
		void showDescription();
		void initTitle();
		void initVersion();
		void initDescription();
		void initLevel();
		void initAuthor();
		void updateLevel();
		void updateAuthor();
		void updateVersion();
		std::string levelByIndex(int);
		int level;

		//TTL_Font *answerFont;
		//SDL_Surface *answersText[3];
};
