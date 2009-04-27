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

#ifndef GAMENAVIGATIONSTATE_CPP
#define GAMENAVIGATIONSTATE_CPP

#include <iostream>
#include <cstring>

#include "GamePlayer.h"
#include "GameNavigationState.h"
#include "luainc.h"

using std::cout;
using std::cerr;
using std::endl;

GameNavigationState::GameNavigationState() {
	theMap = NULL;
	thePlayer = NULL;
	stateScriptPath = NULL;
}

/**********************************************************//**
 *   Configures assets specific to this state; particularly 
 * assets involved with map construction.
 *************************************************************/
void GameNavigationState::Init( const char* theScript ) {

	/**
	 * The function first loads the script that has been
	 * passed to it.
	 **/
	if ( theScript != NULL ) {
		
		stateScriptPath = new char[ 32 ];
		
		strcpy( stateScriptPath, theScript );
		
		lua_State* L = luaL_newstate();

		if ( luaL_loadfile( L, stateScriptPath ) 
		|| lua_pcall( L, 0, 0, 0 ) ) {
			cerr << "Failed to load " << stateScriptPath 
				<< endl;
		}
		
		/**
		 * The 'player' entity is then loaded based 
		 * on the specifications in the script.
		 **/
		
		char* imagePath = NULL;
//		cout << "&imagePath = " << imagePath << endl;
		lua_getglobal( L, "playerImage" );

		if ( !lua_isstring( L, 1 ) ) {
			cerr << "'playerImage' should be a string. - "
				<< stateScriptPath << endl;
		}
		else {
			imagePath = new char[64];

			cout << "&imagePath = " << imagePath << endl;
			
			strcpy( imagePath, "../../img/\0" );
			
			cout << "imagePath = ";
			for ( int i = 0 ; imagePath[i] != NULL ; i++ )
				cout << imagePath[i];
			cout << endl;
			
			strcat( imagePath, lua_tostring( L, 1 ) );
			
			cout << "final imagePath = ";
			for ( int i = 0 ; imagePath[i] != NULL ; i++ )
				cout << imagePath[i];
			cout << endl;

		}
		cout << "&thePlayer = " <<  thePlayer << endl;
		thePlayer = new GamePlayer;
		cout << "new &thePlayer = " << thePlayer << endl;
		thePlayer->Init( imagePath );
	
		if ( imagePath != NULL ) {
			delete imagePath;
			imagePath = NULL;
		}

	}

	/**
	 * None of the above will occur if no script is passed; 
	 * however, the state will still be pushed into a 
	 * 'running' state.
	 **/

	running = true;
	cout << "thePlayer now = " << thePlayer << endl;
}

/**********************************************************//**
 *   Does any last-minute operations before the termination of 
 * the navigation state.
 *************************************************************/
void GameNavigationState::Cleanup() {
	if ( theMap != NULL ) {
		delete theMap;
		theMap = NULL;
	}

	if ( thePlayer != NULL ) {
		delete thePlayer;
		thePlayer = NULL;
	}

	if ( stateScriptPath != NULL ) {
		delete [] stateScriptPath;
		stateScriptPath = NULL; 
	}
}

/**********************************************************//**
 *   Handles event triggers for this state, including the 
 * movement of the player within the map.
 * 
 * \param game A pointer to the game engine
 * \param event Reference to the last polled SDL_Event
 *************************************************************/
bool GameNavigationState::HandleEvents( PlatformEngine* game,
					SDL_Event& event ) {
	if ( running ) {
		switch( event.type ) {
			case SDL_KEYDOWN:
				switch ( event.key.keysym.sym ) {
					case SDLK_q:
						game->Quit();
						return true;
						break;
				}

				break;
		}

	return false;
	}
}

/**********************************************************//**
 *   Does any necessary logic updates to bring the game's data 
 * up to date with the actions of the player or anything else 
 * in the game.
 *
 * \param game A pointer to the game engine
 *************************************************************/
void GameNavigationState::Update( PlatformEngine* game ) {
	if ( running ) {
		return;
	}
}

/**********************************************************//**
 *   Draws the contents of the state, including the map and 
 * the player, to the engine's main screen.
 *
 * \param mainScreen A pointer to the primary game display surface
 *************************************************************/
void GameNavigationState::Draw( SDL_Surface* mainScreen ) {
	if ( theMap != NULL ) {
		theMap->Draw( mainScreen );
	}
	cout << "2 " << mainScreen << " " << thePlayer<< endl;
//	if ( thePlayer != NULL ) {
		thePlayer->Draw( mainScreen );
//	}
}

/**********************************************************//**
 *   Gives the impression of the player moving in some direction 
 * on the map by moving everything else in the opposite 
 * direction, and possibly triggering a movement animation for 
 * the player's image. Fails if there is a collision between the 
 * player and a map object.
 * 
 * \param delta 2-dimensional shift in movement
 * \return True if the movement succeeds, false if there is collision
 *************************************************************/
bool GameNavigationState::MovePlayer( SDL_Rect& delta ) {
	return false;
}

#endif
