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

#ifndef GAMESTATICMOVEMENTSTATE_H
#define	GAMESTATICMOVEMENTSTATE_H

#include "GameState.h"
#include "PlatformEngine.h"
#include "GameMap.h"
#include "GamePlayer.h"
#include "SDL.h"

/**********************************************************//**
 * \brief A state where entities move on a static playfield
 *
 *   Static Movement refers to the idea that, while there are 
 * entities moving around on the "map" area, the area itself is
 * no larger than the size of the player's screen, and therefore
 * doesn't move at all; in other words, it is "static".
 *
 *   Note that this doesn't mean that the background can't give 
 * the illusion of movement. For example, the background might 
 * be an image that constantly scrolls downward, acting as a 
 * parallax background. However, as far as the state is 
 * concerned, the activities in the background are irrelevant; 
 * the only activity the state is concerned with is that of the 
 * entities known to it, such as the player.
 *************************************************************/
class GameStaticMovementState : public GameState {
	public:
		//** Used for memory management, presets pointers to NULL.
		GameStaticMovementState();
		
		//** Enforces memory safety by forcing the Cleanup function.
		~GameStaticMovementState();

		//** Initializes the state using an external script.
		void Init( const char* theScript = NULL );

		//** Cleans up any leftover state assets, such as entities
		void Cleanup();

		//** Handles events that have been triggered by the player.
		bool HandleEvents( PlatformEngine* game,
				SDL_Event& event );

		//** Runs any new state logic necessary before continuing.
		void Update( PlatformEngine* game );

		//** Draws the state's entities to the display screen.
		void Draw( SDL_Surface* mainScreen );

	private:
		//** The background settings for this state.
		GameMap* theMap;

		//** The entity representing the player on this state.
		GamePlayer* thePlayer;
};

#endif
