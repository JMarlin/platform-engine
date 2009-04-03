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

#ifndef PLATFORM_ENGINE_CPP
#define PLATFORM_ENDINE_CPP

#include <iostream>

#include "SDL.h"

#include "PlatformEngine.h"
#include "GameState.h"
#include "luainc.h"

using std::cerr;

PlatformEngine::PlatformEngine() {
	mainScreen = NULL;
}

/**********************************************************//**
 *   The Init function sets up the game assets; aside from  
 * just initializing the SDL subsystems, it also loads any 
 * configuration scripts.
 *
 * \param title C-string with the game title, or main window text.
 *************************************************************/
void PlatformEngine::Init( const char* title ) {

	lua_State *L = luaL_newstate();

	luaL_openlibs( L );
	
	lua_close( L );

	if ( SDL_Init( SDL_INIT_VIDEO 
			| SDL_INIT_TIMER ) == -1 ) {
		cerr << "Failed to initialize subsystems; "
			<< SDL_GetError() << std::endl;
	}

	SDL_WM_SetCaption( title, NULL );

	mainScreen = SDL_SetVideoMode( 640, 480, 32, 
				       SDL_HWSURFACE 
					| SDL_DOUBLEBUF );

}

/**********************************************************//**
 *   This function's main purpose is to call the drawing 
 * function of the current state.
 *************************************************************/
void PlatformEngine::Draw() {
	if ( !stateStack.empty() ) {
		GameState* topState = stateStack.top();
		if ( topState != NULL ) topState->Draw( this );
	}
}

/**********************************************************//**
 *   This function's main purpose is to call the update 
 * function of the current state.
 *************************************************************/
void PlatformEngine::Update() {
	if ( !stateStack.empty() ) {
		GameState* topState = stateStack.top();
		if ( topState != NULL ) topState->Update( this );
	}
}

/**********************************************************//**
 *   This function's main purpose is to call the event 
 * handling function of the current state.
 *************************************************************/
void PlatformEngine::HandleEvents() {
	SDL_Event event;

	while( SDL_PollEvent( &event ) ) {

		if ( !stateStack.empty() ) {
			GameState* topState= stateStack.top();
			if ( topState!= NULL ) {
				topState->HandleEvents( this, event );
				continue;
			}
		}

		switch( event.type ) {
			case SDL_KEYDOWN:
				switch ( event.key.keysym.sym ) {
					case SDLK_ESCAPE:
						running = false;
						break;
				}

				break;
			case SDL_QUIT:
				running = false;
				break;
		}
	}
}

/**********************************************************//**
 *   This function cleans up any of the remaining global 
 * assets of the engine. This mostly consists of open surfaces 
 * and states remaining on the stack.
 *************************************************************/
void PlatformEngine::Cleanup() {
	if ( mainScreen != NULL ) {
		SDL_FreeSurface( mainScreen );
	}

	SDL_Quit();
}

/**********************************************************//**
 *   This function takes a reference to a state and then 
 * pushes it onto the top of the engine's state stack. That 
 * then becomes the active stack for the engine.
 *
 * \param state Pointer to the newly-created state being pushed
 *************************************************************/
void PlatformEngine::PushState( GameState* state ) {
	stateStack.push( state );
}

/**********************************************************//**
 *   This function pops a state pointer off the top of the 
 * stack. It's operation is ordered such that the state first 
 * becomes inactive and then is deleted from memory, 
 * effectively preventing segmentation errors.
 *************************************************************/
void PlatformEngine::PopState() {
	if ( !stateStack.empty() ) {
		if ( stateStack.top() != NULL ) {
			GameState* tempState = stateStack.top();
			stateStack.pop();
			delete tempState;
		}
		else stateStack.pop();
	}
}

/**********************************************************//**
 *   The engine state is explicitly changed by calling this 
 * function with a new state that you wish to be the 
 * executed state. It actually passess both the new state and 
 * a reference to the engine to the current top state's 
 * equivalent function, allowing for customized transitions.
 *************************************************************/
void PlatformEngine::ChangeState( GameState* state ) {
	if ( !stateStack.empty() ) {
		if ( stateStack.top() != NULL ) {
			GameState* topState = stateStack.top();
			topState->ChangeState( this, state );
		}
	}
}

#endif
