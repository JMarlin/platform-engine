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

#ifndef GAMENAVIGATIONSTATE_H
#define GAMENAVIGATIONSTATE_H

#include "GameState.h"
#include "GameMap.h"

/**********************************************************//**
 * \brief The state in which game world navigation takes place
 *
 *   While in this state, the game's operation revolves around 
 * the movement of a player sprite on some sort of visual 
 * map, or 'world'. It does this by making use of an entirely 
 * separate 'mapping' system, which controls the movement and 
 * rendering of the world map itself, while having player 
 * and event controls done internally.
 *************************************************************/
class GameNavigationState : public GameState {
	public:
		GameNavigationState();

		//** Prepares state subsystems and scripts.
		void Init();

		//** Cleans up any remaining state assets.
		void Cleanup();

		//** Halts execution of the state's operations.
		void Pause();

		//** Resumes state execution.
		void Resume();

		//** Handles any events that are particular to the state
		void HandleEvents(  PlatformEngine* game,
			       SDL_Event& event	);

		//** Updates the state's logic
		void Update( 	    PlatformEngine* game );
		
		//** Draws the visual content of the state to the engine. 
		void Draw( 	    PlatformEngine* game );
		
		//** Acts as if the Player is moving 'upward'
		bool MovePlayerUp();

		//** Acts as if the Player is moving 'downward'
		bool MovePlayerDown();

		//** Acts as if the Player is moving 'to the left'
		bool MovePlayerLeft();

		//** Acts as if the Player is moving 'to the right'
		bool MovePlayerRight();

	protected:
		
		//** Object representing the entire map used in this state
		GameMap* theMap;
};

#endif
