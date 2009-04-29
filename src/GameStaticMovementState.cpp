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
	running = false;
}

GameStaticMovementState::~GameStaticMovementState() {
	Cleanup();
}

void GameStaticMovementState::Init( const char* theScript ) {
	lua_State* L = luaL_newstate();

	if ( theScript != NULL ) {
	
		if ( luaL_loadfile( L, theScript ) 
		|| lua_pcall( L, 0, 0, 0 ) ) {
			cerr << "Failed to load " << theScript << endl;
		}
		
		lua_getglobal( L, "playerImage" );

		char* image = new char[ 64 ];
		strcpy( image, "../../img/\0" );
		strcat( image, lua_tostring( L, 1 ) );

		thePlayer = new GamePlayer;
		thePlayer->Init( image );
		
	}

	running = true;
}

void GameStaticMovementState::Draw( SDL_Surface* mainScreen ) {
	if ( theMap != NULL )
		theMap->Draw( mainScreen );

	if ( thePlayer != NULL )
		thePlayer->Draw( mainScreen );
}

void GameStaticMovementState::Cleanup() {
	if ( theMap != NULL ) {
		delete theMap;
	}
	if ( thePlayer != NULL ) {
		delete thePlayer;
	}
}

bool GameStaticMovementState::HandleEvents( PlatformEngine*  game, 
					SDL_Event& event ) {
	switch ( event.type ) {
		case SDL_KEYDOWN:
			switch ( event.key.keysym.sym ) {
				case SDLK_q:
					game->Quit();
					return true;
			}
			break;
		default:
			return false;
	}
	return false;
}

void GameStaticMovementState::Update( PlatformEngine* game ) {
	return;
}

void Draw( SDL_Surface* mainScreen ) {
	return;
}

#endif
