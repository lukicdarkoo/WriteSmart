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
#include <vector>
#include "Config.h"

class Question {
	public:
		SDL_Surface *screen;

		Question();
		~Question();
		void update();
		void init();

        //safe zone
		int safeXFrom;
		int safeXTo;

		//if ready to check if sprite is in safe zone
		bool readyToCheck;

        Config *config;

	private:
		SDL_Rect questionBox;

		TTF_Font *questionFont;
		SDL_Surface *questionText;
		SDL_Rect questionTextHolder;

		void initQuestionText();
		void updateTextQuestion();
		void initAnswers();
		void setAnswersText();
		void getFromFile();
		void setActiveQuestion();

        std::vector<std::string> questionString;
        std::vector< std::vector<std::string> > answersString;
        std::vector<int> correctAnswers;
        int activeQuestion;


		TTF_Font *answersFont;
		std::vector<SDL_Surface *> answersText;
		std::vector<SDL_Rect> answersRects;
		std::vector<SDL_Rect> answersHolders;

		bool boxesDroped;
		int frozenQuestionFrames;
};
