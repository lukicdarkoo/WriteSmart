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

#pragma once
#include <string>
#include <vector>

class Config {
	public:
		static const int ScreenWidth = 480;
		static const int ScreenHeight = 700;
		static const int FPS = 60;

		float BackgroundSpeed;
		static const int BackgroundHeight = 1450;

		static const int SpriteLazzyMoveStart = 10;
		static const int SpriteLazzyMoveStep = 1;
		static const float SpriteRotationStep = 1.9;
		static const float SpriteGravityRotation = 3.5;

		static const int ChanceToChangeDirection = 100; //manji broj vece sanse
		static const float GravityMin = 1.8;
		static const float GravityMax = 3.8;

		int FrozenQuestion;

		static const std::string LevelNames[];
		static const float LevelSpeeds[];
		static const int LevelNumber;

        Config();
};
