/***************************************************************************
    © Copyright 2009 Patrick VanDusen

    This file is part of the Platform 2D Game Engine, 
    also referred to as Platform.

    Platform is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as 
    published by the Free Software Foundation, either version 3 of the 
    License, or (at your option) any later version.

    Platform is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Platform.  If not, see <http://www.gnu.org/licenses/>.
***************************************************************************/

#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H

#include "PlatformEngine.h"
#include "SDL.h"

/**********************************************************//**
 * \brief The player character entity
 *
 *   GamePlayer is an entity representing the avatar of the 
 * human player on the screen. It is usually the center focus 
 * of the player's attention and the proxy through which the 
 * player expects to operate.
 *************************************************************/
class GamePlayer {
	public:
		GamePlayer();
		~GamePlayer();
		
		//** Initialize the player class
		void Init( const char* image = NULL );

		//** Draws the player to the engine screen
		void Draw( SDL_Surface* mainScreen );

		void Update();

		void SetMoveLeft( const bool& flag );

		void SetMoveRight( const bool& flag );

		void SetMoveUp( const bool& flag );

		void SetMoveDown( const bool& flag );

	private:
		//** Path to an image representing the object
		char* imagePath;

		bool moveUp;

		bool moveDown;

		bool moveLeft;

		bool moveRight;

		SDL_Rect dimensions;

		//** Surface holding the player's image
		SDL_Surface* playerSurface;
};

#endif
