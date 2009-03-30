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

#ifndef PLATFORMENGINE_H
#define PLATFORMENGINE_H

#include <stack>

#include "SDL.h"

// Forward reference to GameState class.
class GameState;

using std::stack;

/**********************************************************//**
 * \brief The game engine instance
 *
 *   This class represents the game engine. It encompasses the 
 * major subprocesses; Initialization, State control, Event 
 * Handling, Updating, and Drawing. 
 *************************************************************/
class PlatformEngine {
	public:
		//** Prepares engine subsystems and assets
		void Init( const char* title );

		//** Clears up any engine assets before the program ends.
		void Cleanup();
		
		//** Explicitly changes the state of the engine.
		void ChangeState( GameState* state );
		
		//** Puts a new state onto the engine state stack.
		void PushState( GameState* state );

		//** Ends the top state on the engine stack.
		void PopState();
		
		//** Processes user input events.
		void HandleEvents();

		//** Brings the game logic up-to-date.
		void Update();

		//** Draws necessary surfaces to the screen.
		void Draw();
		
		//** Returns whether or not the game loop is running.
		bool Running() { return running; }

		//** Halts the game loop.
		void Quit() { running = false; }

	private:
		//** Stack of game states. The top state is the active one.
		stack< GameState* > stateStack;
		
		//** The primary SDL_Surface that images are drawn to.
		SDL_Surface* mainScreen;
		
		//** Controls whether or not the game loop is active.
		bool running;
};

#endif
