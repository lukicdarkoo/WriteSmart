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

#include "Sprite.h"
#include "Config.h"
#include "Helper.h"

#define MAX_ROTATE 30
#define MIN_ROTATE -30
#define ROTATE_BECAUSE_MOVE 10

void Sprite::init() {
	spriteImage = NULL;
	
    sprite.x = Config::ScreenWidth / 2 - 25;
    sprite.y = Config::ScreenHeight - 130;
    sprite.w = 100;
    sprite.h = 100;
	spriteMoveToEnd = 0;
	gravity = 1;
	spriteSize = 1;
	toRotate = 0;
	currentRotation = 0;

	spriteImageSource = IMG_Load("data/sprite.png");
	spriteImage = rotozoomSurface(spriteImageSource, 0.0, 1, 1);
}

int Sprite::endAnimationUpdate() {
    currentRotation += 6;
    spriteImage = rotozoomSurface(spriteImageSource, currentRotation, (spriteSize > 0) ? spriteSize -= 0.02 : spriteSize, 1);


    if (sprite.x > Config::ScreenWidth / 2 + 10 || sprite.x < Config::ScreenWidth / 2 - 10) {
        if (sprite.x > Config::ScreenWidth / 2)
            sprite.x -= 5;
        else if (sprite.x < Config::ScreenWidth / 2)
            sprite.x += 5;
    }

    if (sprite.y > 300)
        sprite.y -= 5;


    SDL_BlitSurface(spriteImage, NULL, screen, &sprite);

    if (currentRotation > 300)
        return 0;
    else return 1;
}

void Sprite::update() {
	if (keysDown->Left) {
		spriteMoveToEnd = Config::SpriteLazzyMoveStart;
		toRotate -= ROTATE_BECAUSE_MOVE;
		keysDown->Left = false;
	}
	else if (keysDown->Right) {
		spriteMoveToEnd = -Config::SpriteLazzyMoveStart;
		toRotate += ROTATE_BECAUSE_MOVE;
		keysDown->Right = false;
	}

	sprite.x += gravity;



	move();
	rotate();


	if (currentRotation < MIN_ROTATE)
		currentRotation = MIN_ROTATE;

	if (toRotate < MIN_ROTATE)
		toRotate = MIN_ROTATE;

	if (toRotate > MAX_ROTATE)
		toRotate = MAX_ROTATE;

	if (currentRotation > MAX_ROTATE)
		currentRotation = MAX_ROTATE;



	//SDL_FillRect(screen, &sprite, 0xFF6600);
	SDL_BlitSurface(spriteImage, NULL, screen, &sprite);


	if (Helper::random(0, Config::ChanceToChangeDirection) == 1) {
		gravity /= abs(gravity) * (-1);
		gravity *= Helper::random(Config::GravityMin * 10, Config::GravityMax * 10) / 10.0;


		toRotate = gravity * (-1) * Config::SpriteGravityRotation;
	}

	x = sprite.x + sprite.w / 2 + currentRotation / 2;
}

void Sprite::rotate() {
	if (abs(currentRotation - toRotate) > Config::SpriteRotationStep) {
		currentRotation += ((toRotate > 0) ? Config::SpriteRotationStep : (-1) * Config::SpriteRotationStep);

		spriteImage = rotozoomSurface(spriteImageSource, currentRotation, 1, 1);
	}
}

void Sprite::move() {
	if (spriteMoveToEnd > Config::SpriteLazzyMoveStep) {
		spriteMoveToEnd -= Config::SpriteLazzyMoveStep;
		sprite.x -= spriteMoveToEnd;
	}
	else if (spriteMoveToEnd < Config::SpriteLazzyMoveStep) {
		spriteMoveToEnd += Config::SpriteLazzyMoveStep;
		sprite.x -= spriteMoveToEnd;
	}
}

Sprite::~Sprite() {
	if (spriteImage != NULL)
		SDL_FreeSurface(spriteImage);
}
