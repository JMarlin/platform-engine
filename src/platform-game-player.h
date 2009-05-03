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

#include "platform-engine.h"
#include "SDL.h"

namespace Platform {

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
		void Init( SDL_Surface* theDisplay, const char* image = NULL );

		//** Draws the player to the engine screen
		void Draw();
		
		//** Calculates any necessary player logic
		void Update();

		//** Sets the player to either move left or not
		void SetMoveLeft( const bool& flag );

		//** Sets the player to either move right or not
		void SetMoveRight( const bool& flag );

		//** Sets the player to either move up or not
		void SetMoveUp( const bool& flag );

		//** Sets the player to either move down or not
		void SetMoveDown( const bool& flag );

	private:
		//** Path to an image representing the object
		char* imagePath;

		//** Flag controlling player upward movement
		bool moveUp;

		//** Flag controlling player downward movement
		bool moveDown;

		//** Flag controlling player leftward movement
		bool moveLeft;

		//** Flag controlling player rightward movement
		bool moveRight;

		//** Position and size information for the Player object
		SDL_Rect dimensions;

		//** Surface holding the player's image
		SDL_Surface* playerSurface;

    SDL_Surface* mainScreen;
};

} // namespace Platform
#endif
