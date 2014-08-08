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

#include "Question.h"
#include "Config.h"
#include "Helper.h"
#include <stdio.h>
#include <stdlib.h>

#define ANSWER_WIDTH 120
#define ANSWER_Y 50

#define QUESTION_BACKGROUND_COLOR 0xEEEEEE
#define QUESTION_TEXT_COLOR 33, 33, 33
#define ANSWERS_BACKGROUND_COLORS 0xa0b2b9, 0xd6ac71, 0x976055
#define ANSWERS_TEXT_COLORS {255, 255, 255}, {255, 255, 255}, {255, 255, 255}


Question::Question() {
	questionBox.x = 0;
	questionBox.y = 0;
	questionBox.w = Config::ScreenWidth;
	questionBox.h = 50;
}

void Question::init() {
	questionText = NULL;
	questionFont = NULL;
	answersFont = NULL;
	
    activeQuestion = 0;
    frozenQuestionFrames = 0;
    boxesDroped = false;
    readyToCheck = false;

    getFromFile();

	initQuestionText();
	initAnswers();

	setActiveQuestion();
}

void Question::setActiveQuestion() {
    activeQuestion = Helper::random(0, questionString.size() - 1);


    //shuffle answers
    int i = 0;
    for (; i < 5; i++) {
        int replaceIndexFirst, replaceIndexSecond;
        replaceIndexFirst = Helper::random(0, 2);
        replaceIndexSecond = Helper::random(0, 2);

        std::string temp = answersString.at(activeQuestion).at(replaceIndexFirst);
        answersString.at(activeQuestion).at(replaceIndexFirst) = answersString.at(activeQuestion).at(replaceIndexSecond);
        answersString.at(activeQuestion).at(replaceIndexSecond) = temp;

        if (replaceIndexFirst == correctAnswers.at(activeQuestion))
            correctAnswers.at(activeQuestion) = replaceIndexSecond;

        else if (replaceIndexSecond == correctAnswers.at(activeQuestion))
            correctAnswers.at(activeQuestion) = replaceIndexFirst;
    }

    setAnswersText();
    //updateTextQuestion();


    //set safe zone
    safeXFrom = answersRects[correctAnswers[activeQuestion]].x;
    safeXTo = safeXFrom + ANSWER_WIDTH;
}

void Question::getFromFile() {
    FILE *pf;
    pf = fopen("data/Questions.txt", "r");


    char questionBuffer[50];
    char answerBuffer[10];


    while (fgets(questionBuffer, sizeof(questionBuffer), pf) != NULL) {
        Helper::lastCharFix(questionBuffer);
        questionString.push_back(questionBuffer);


        //add answers
        std::vector<std::string> answerString;

        fgets(answerBuffer, sizeof(answerBuffer), pf);
        Helper::lastCharFix(answerBuffer);
        answerString.push_back(answerBuffer);

        fgets(answerBuffer, sizeof(answerBuffer), pf);
        Helper::lastCharFix(answerBuffer);
        answerString.push_back(answerBuffer);

        fgets(answerBuffer, sizeof(answerBuffer), pf);
        Helper::lastCharFix(answerBuffer);
        answerString.push_back(answerBuffer);

        answersString.push_back(answerString);

        //add correct answer
        fgets(answerBuffer, sizeof(answerBuffer), pf);
        correctAnswers.push_back(atoi(answerBuffer));
    }


    fclose(pf);
}

void Question::initAnswers() {
    int i = 0;
    for (; i < 3; i++) {
        SDL_Rect answersRect;
        answersRect.x = 50 + i * (ANSWER_WIDTH + 3);
        answersRect.y = ANSWER_Y;
        answersRect.w = ANSWER_WIDTH;
        answersRect.h = 30;

        SDL_Rect answersHolder;
        answersHolder.x = 50 + i * (ANSWER_WIDTH + 6) + 6;
        answersHolder.y = ANSWER_Y + 2;
        answersHolder.w = ANSWER_WIDTH;
        answersHolder.h = 30;

        answersRects.push_back(answersRect);
        answersHolders.push_back(answersHolder);

        SDL_Surface *surface;
        answersText.push_back(surface);
    }

    answersFont = TTF_OpenFont("data/LiberationSans-Regular.ttf", 18);

    setAnswersText();
}

void Question::update() {
    //update question
	SDL_FillRect(screen, &questionBox, QUESTION_BACKGROUND_COLOR);
	updateTextQuestion();


    //update answers
    //readyToCheck = false;

    //realise boxes after x frames
    if (!boxesDroped && ++frozenQuestionFrames >= config->FrozenQuestion) {
        boxesDroped = true;
        frozenQuestionFrames = 0;
    }

    //boxes move
    if (boxesDroped) {
        int i = 0;
        for (; i < 3; i++) {
            answersRects.at(i).y += config->BackgroundSpeed;
            answersHolders.at(i).y += config->BackgroundSpeed;
        }

        if (answersRects.at(0).y >= Config::ScreenHeight - 35) {

            if (readyToCheck) {
                setActiveQuestion();
                boxesDroped = false;
                readyToCheck = false;
            }

            if (boxesDroped)
                readyToCheck = true;
        }

    } else {
        int i = 0;
        for (; i < 3; i++) {
            answersRects.at(i).y = ANSWER_Y;
            answersHolders.at(i).y = ANSWER_Y + 2;
        }
    }


    //print boxes on new locatios
    int answerColors[] = {  ANSWERS_BACKGROUND_COLORS };
    int i = 0;
    for (; i < 3; i++) {
        SDL_FillRect(screen, &answersRects.at(i), answerColors[i]);
        SDL_BlitSurface(answersText.at(i), NULL, screen, &answersHolders.at(i));
    }
}

void Question::setAnswersText() {
    SDL_Color textColors[] = { ANSWERS_TEXT_COLORS };

    int i = 0;
    for (; i < 3; i++) {
        answersText.at(i) = TTF_RenderText_Blended(answersFont, answersString[activeQuestion][i].c_str(), textColors[i]);
    }
}

void Question::updateTextQuestion() {
	SDL_Color questionTextColor = { QUESTION_TEXT_COLOR };
	questionText = TTF_RenderText_Blended(questionFont, questionString[activeQuestion].c_str(), questionTextColor);
	SDL_BlitSurface(questionText, NULL, screen, &questionTextHolder);
}

void Question::initQuestionText() {
	questionTextHolder.x = 10;
	questionTextHolder.y = 10;
	questionTextHolder.w = Config::ScreenWidth;
	questionTextHolder.h = 100;
	questionFont = TTF_OpenFont("data/LiberationSans-Regular.ttf", 24);
}

Question::~Question() {
	if (questionText != NULL)
		SDL_FreeSurface(questionText);
	
	if (questionFont != NULL)
		TTF_CloseFont(questionFont);

	if (answersFont != NULL)
		TTF_CloseFont(answersFont);
	
	int i = 0;
	for (; i < answersText.size(); i++)
		SDL_FreeSurface(answersText[i]);
}
