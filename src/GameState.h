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

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "PlatformEngine.h"

/**********************************************************//**
 * \brief A state of behavior for the engine
 *
 *   A Game State is a layer on top of the default engine 
 * behavior that requires a custom form of behavior for its
 * operation. In the Platform engine, the an instance of the 
 * engine stores the current state on a stack, and any newly 
 * initiated states can be placed on top of the stack. The 
 * normal engine functions will generally call the 
 * corresponding operation functions from the state at the 
 * top of the stack, so that the engine's operation is 
 * ultimately controlled by the current top state.
 *
 *   This class in particular is an abstract class, not 
 * intended for actual use. The derivative classes, which are 
 * the different kinds of states, are used in normal 
 * program operations.
 *************************************************************/
class GameState {
	public:
		//** Prepares state subsystems and scripts.
		virtual void Init() = 0;

		//** Cleans up any remaining state assets.
		virtual void Cleanup() = 0;

		//** Halts execution of the state's operations.
		virtual void Pause() = 0;

		//** Resumes state execution.
		virtual void Resume() = 0;

		//** Handles any events that are particular to the state
		virtual void HandleEvents(  PlatformEngine* game ) = 0;

		//** Updates the state's logic
		virtual void Update( 	    PlatformEngine* game ) = 0;
		
		//** Draws the visual content of the state to the engine. 
		virtual void Draw( 	    PlatformEngine* game ) = 0;
		
		//** Explicitly Switches the engine to another state.
		void ChangeState(	PlatformEngine* game,
			       		GameState* state ) {
			game->ChangeState( state );
		}

	protected:
		GameState();
};

#endif
