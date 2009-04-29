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

#ifndef GAMESTATICMOVEMENTSTATE_CPP
#define GAMESTATICMOVEMENTSTATE_CPP

#include "GameStaticMovementState.h"
#include "luainc.h"

#include <iostream>

using std::cerr;
using std::endl;

GameStaticMovementState::GameStaticMovementState() {
	theMap = NULL;
	thePlayer = NULL;
	stateScriptPath = NULL;
	running = false;
}

GameStaticMovementState::~GameStaticMovementState() {
	Cleanup();
}

/**********************************************************//**
 *   The state is not initialized automatically when it is 
 * created. In order for the state to operate in any realistic
 * way, it must be initialized with this function, along with 
 * a lua script giving the details of its operation.
 *
 * \param theScript A path to the lua script that configures 
 *        the initialization.
 *************************************************************/
void GameStaticMovementState::Init( const char* theScript ) {

	/**
	 * First, the engine removes the paths of any previous
	 * scripts, assuming they exist, before loading the 
	 * script that has been passed to it.
	 **/
	if ( stateScriptPath != NULL ) delete stateScriptPath;

	stateScriptPath = new char[ 64 ];
	strcpy( stateScriptPath, theScript );
	
	/**
	 * The state then loads a lua interpreter to read the 
	 * script file. If no script is
	 * passed, then the function will only mark the
	 * state as "running", while effectively having no
	 * assets defined.
	 **/
	lua_State* L = luaL_newstate();

	if ( theScript != NULL ) {
	
		if ( luaL_loadfile( L, stateScriptPath ) 
		|| lua_pcall( L, 0, 0, 0 ) ) {
			cerr << "Failed to load " << stateScriptPath 
				<< endl;
		}
		
		/**
		 * The function loads the variable "playerImage" from
		 * the script, and then retains the path of the image
		 * as a string.
		 **/

		lua_getglobal( L, "playerImage" );

		char* image = new char[ 64 ];
		strcpy( image, "../../img/\0" );
		strcat( image, lua_tostring( L, 1 ) );
		
		/**
		 * A new GamePlayer entity is then created, and it is 
		 * initialized using the image that was loaded from the
		 * script.
		 **/
		thePlayer = new GamePlayer;
		thePlayer->Init( image );
		
	}

	/**
	 * The state is then set as "running" so that normal operation 
	 * can begin.
	 **/
	running = true;
}

/**********************************************************//**
 *   This will draw any of the visible entities being used 
 * by this state to the primary display screen.
 *
 * \param mainScreen A pointer to the primary display screen.
 *************************************************************/
void GameStaticMovementState::Draw( SDL_Surface* mainScreen ) {
	if ( theMap != NULL )
		theMap->Draw( mainScreen );

	if ( thePlayer != NULL )
		thePlayer->Draw( mainScreen );
}

/**********************************************************//**
 *   For mostly memory management-related purposes, this will 
 * remove any assets remaining in the state. 
 *
 *   This function is automatically called upon deletion of the
 * state it is a member of. Thus, unless you are using the state
 * in a nonstandard way, it should never be necessary to 
 * explicitly call this function.
 *
 * \param theScript A path to the lua script that configures 
 *        the initialization.
 *************************************************************/
void GameStaticMovementState::Cleanup() {
	if ( theMap != NULL ) {
		delete theMap;
	}
	if ( thePlayer != NULL ) {
		delete thePlayer;
	}
	if ( stateScriptPath != NULL ) {
		delete stateScriptPath;
	}
}

/**********************************************************//**
 *   Handles the events used by the state. An event that was 
 * previously polled by the engine is analyzed by this function 
 * to execute the appropriate action for that event.
 *
 * \param game A pointer to the game engine.
 * \param event The event that is being analyzed.
 *************************************************************/
bool GameStaticMovementState::HandleEvents( PlatformEngine*  game, 
					SDL_Event& event ) {
	switch ( event.type ) {
		case SDL_KEYDOWN:
			switch ( event.key.keysym.sym ) {
				case SDLK_UP:
				case SDLK_w: {
					SDL_Rect delta;
					
					delta.x = 0;
					delta.y = -10;

					thePlayer->Move( delta );
					}
					return true;
				case SDLK_DOWN:
				case SDLK_s: {
					SDL_Rect delta;

					delta.x = 0;
					delta.y = 10;

					thePlayer->Move( delta );
					}
					return true;
				case SDLK_LEFT:
				case SDLK_a: {
					SDL_Rect delta;

					delta.x = -10;
					delta.y = 0;

					thePlayer->Move( delta );
					}
					return true;
				case SDLK_RIGHT:
				case SDLK_d: {
					SDL_Rect delta;

					delta.x = 10;
					delta.y = 0;

					thePlayer->Move( delta );
					}
					return true;
			}
			break;
		default:
			return false;
	}
	return false;
}

/**********************************************************//**
 *   Any calculations necessary to be regularly done for the 
 * engine logic are done.
 *
 * \param game A pointer to the game engine.
 *************************************************************/
void GameStaticMovementState::Update( PlatformEngine* game ) {
	return;
}

#endif
