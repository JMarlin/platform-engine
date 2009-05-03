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
#include "platform-lua-includes.h"
//#include "boost/filesystem.hpp"

#include "platform-engine.h"
#include "platform-game-state.h"
#include "platform-game-state-static-movement.h"

#include <cstring>

namespace Platform {

using std::cout;
using std::cerr;
using std::endl;

PlatformEngine::PlatformEngine() {
  mainScreen = NULL;
  fullTitle = NULL;
  running = false;
}

/**********************************************************//**
 *   The Init function sets up the game assets; aside from  
 * just initializing the SDL subsystems, it also loads any 
 * configuration scripts.
 *************************************************************/
void PlatformEngine::Init() {
	
	/**
	 *   The script file, "init.lua", is loaded as a state by this
	 * function.
	 **/

	const char* initPath = "../../scripts/init.lua\0";

	lua_State *L = luaL_newstate();
	
	fullTitle = new char[ 64 ];

	if ( luaL_loadfile( L, initPath ) || lua_pcall( L, 0, 0, 0 ) ) {
		cerr << "Failed to load " << initPath << endl;
	}

	/**
	 *   The variables related to identifying the program revision 
	 * are then loaded from the config file. "title" refers to the 
	 * actual name of the program; by default this says something like 
	 * "Platform Test", but in a game release this should contain the 
	 * name of the game itself. "version" is the major revision, and 
	 * normally should only be incremented in a major rewrite, or when
	 * going from pre-release to release. "release" refers to an 
	 * upgrade release, involving new features or enhancements. 
	 * "subrelease" refers to small changes, and should probably 
	 * only be used for bugfixes. "status" is an appended title, and it 
	 * can either be used for codenames, or to indicate development 
	 * status; for example, "Beta", "Release Candidate" or "Final".
	 **/
	
	lua_getglobal( L, "title" );
	lua_getglobal( L, "version" );
	lua_getglobal( L, "release" );
	lua_getglobal( L, "subrelease" );
	lua_getglobal( L, "status" );

	if ( !lua_isstring( L, 1 ) ) {
		cerr << initPath << " - 'title' should be a string.\n";
	}
	else {
		char* title = new char[ 32 ];
		strcpy( title, lua_tostring( L, 1 ) );
		strcpy( fullTitle, title );
		delete [] title;

	}

	if ( !lua_isnumber( L, 2 ) ) {
		cerr << initPath << " - 'version' should be a number.\n";
	}
	else {
		char* major = new char[ 4 ];
		strcpy( major, lua_tostring( L, 2 ) );
		char space[] = " \n";
		strcat( fullTitle, space );
		strcat( fullTitle, major );
		delete [] major;
	}
	
	if ( !lua_isnumber( L, 3 ) ) {
		cerr << initPath << " - 'release' should be a number.\n";
	}
	else {
		char* minor = new char[ 4 ];
		strcpy( minor, lua_tostring( L, 3 ) );
		char decpoint[] = ".\n";
		strcat( fullTitle, decpoint );
		strcat( fullTitle, minor );
		delete [] minor;
	}
	
	if ( !lua_isnumber( L, 4 ) ) {
		cerr << initPath << " - 'subrelease' should be a number.\n";
	}
	else {
		char* subminor = new char[ 4 ];
		strcpy( subminor, lua_tostring( L, 4 ) );
		char decpoint[] = ".\n";
		strcat( fullTitle, decpoint );
		strcat( fullTitle, subminor );
		delete [] subminor;
	}
	
	if ( !lua_isstring( L, 5 ) ) {
		cerr << initPath << " - 'status' should be a string.\n";
	}
	else {
		char* status = new char[ 32 ];
		strcpy( status, lua_tostring( L, 5 ) );
		char space[] = " \n";
		strcat( fullTitle, space );
		strcat( fullTitle, status );
		delete [] status;
	}

	for ( int i = 0 ; i < 5 ; ++i ) lua_pop( L, 1 );

	/**
	 *   The SDL subsystems are then initialized. The Platform engine 
	 * uses the video and timer subsystems.
	 **/
	if ( SDL_Init( SDL_INIT_VIDEO 
			| SDL_INIT_TIMER ) == -1 ) {
		cerr << "Failed to initialize subsystems; "
			<< SDL_GetError() << std::endl;
		return;
	}

	/**
	 *   The window of the main screen should contain all of the 
	 * previously entered release identification information.
	 **/

	SDL_WM_SetCaption( fullTitle, NULL );
	
	/**
	 *   Next, the global variables for display configuration are 
	 * parsed. "screenWidth" and "screenHeight" represent the 
	 * horizontal and vertical dimensions of the display screen. 
	 * "screenBits" represents the bit depth of the screen.
	 **/ 

	lua_getglobal( L, "screenWidth" );
	lua_getglobal( L, "screenHeight" );
	lua_getglobal( L, "screenBits" );
	
	/**
	 *   The next set of variables represent SDL flags that specify
	 * the way the screen display will operate. These include, for 
	 * example, "useHardwareMemory" and "useDoubleBuffering." Most of 
	 * these are self-explanatory. If you do not understand the 
	 * meaning of these flags, it is probably safest to leave them at 
	 * the default settings.
	 **/

	lua_getglobal( L, "useHardwareMemory" );
	lua_getglobal( L, "useDoubleBuffering" );
	lua_getglobal( L, "fullScreenModeOn" );
	
	/**
	 *   After being parsed, the flags are then used in the generation 
	 * of the display screen.
	 **/

	int width, height, bits;
	Uint32 videoModeFlags = 0;
	
	if ( !lua_isnumber( L, 1 ) ) {
		cerr << initPath 
			<< " - 'screenWidth' should be a number.\n";
		width = 640;
	}
	else {
		width = lua_tointeger( L, 1 );
	}

	if ( !lua_isnumber( L, 2 ) ) {
		cerr << initPath
			<< " - 'screenHeight' should be a number.\n";
		height = 480;
	}
	else {
		height = lua_tointeger( L, 2 );
	}

	if ( !lua_isnumber( L, 3 ) ) {
		cerr << initPath 
			<< " - 'screenBits' should be a number.\n";
		bits = 32;
	}
	else {
		bits = lua_tointeger( L, 3 );
	}

	if ( !lua_isboolean( L, 4 ) ) {
		cerr << initPath 
			<< " - 'useHardwareMemory' should be a boolean.\n";
	}
	else {
		if ( lua_toboolean( L, 4 ) )
			videoModeFlags = videoModeFlags | SDL_HWSURFACE;
		else
			videoModeFlags = videoModeFlags | SDL_SWSURFACE;
	}

	if ( !lua_isboolean( L, 5 ) ) {
		cerr << initPath
			<< " - 'useDoubleBuffering' should be a boolean.\n";
	}
	else {
		if ( lua_toboolean( L, 5 ) )
			videoModeFlags = videoModeFlags | SDL_DOUBLEBUF;
	}

	if ( !lua_isboolean( L, 6 ) ) {
		cerr << initPath
			<< " - 'fullScreenModeOn' should be a boolean.\n";
	}
	else{
		if ( lua_toboolean( L, 6 ) )
			videoModeFlags = videoModeFlags | SDL_FULLSCREEN;
	}

	for ( int i = 0 ; i < 6 ; ++i ) lua_pop( L, 1 );

	mainScreen = SDL_SetVideoMode( width, height, bits, 
					videoModeFlags );
	
	/**
	 *   Once the screen has been created, an engine flag indicating 
	 * that the engine is ready to run is set to "true", the lua script 
	 * state is closed, and the program can now begin its primary loop 
	 * of operation.
	 **/

	StartState();

	running = true;

	lua_close( L );

	SDL_ShowCursor( SDL_DISABLE );
}

/**********************************************************//**
 *   This function cleans up any of the remaining global 
 * assets of the engine. This mostly consists of open surfaces 
 * and states remaining on the stack.
 *************************************************************/
void PlatformEngine::Cleanup() {
	if ( mainScreen != NULL ) {
		SDL_FreeSurface( mainScreen );
		mainScreen = NULL;
	}

	while ( !stateStack.empty() ) PopState();

	SDL_Quit();

	if ( fullTitle != NULL ) {
		delete [] fullTitle;
		fullTitle = NULL;
	}
}

/**********************************************************//**
 *   This function uses a prewritten lua script to initiate a 
 * state. This is intended to be the first state that is run by 
 * the engine.
 *************************************************************/
void PlatformEngine::StartState() {

	/**
	 * First, the state is loaded from the hard-coded preset
	 * path of the 'beginstate.lua' script. This path is
	 * "./scripts/beginstate.lua".
	 **/
	lua_State* L = luaL_newstate();
	
	const char* scriptPath = "../../scripts/beginstate.lua\0";

	if ( luaL_loadfile( L, scriptPath ) || lua_pcall( L, 0, 0, 0 ) ) {
		cerr << "Failed to load " << scriptPath << endl;
	}
	else {
		/**
	 	* The engine then retrieves the type of state from the
	 	* script and creates that state.
	 	**/

		lua_getglobal( L, "stateType" );

		if ( !lua_isstring( L, 1 ) ) {
			cerr << scriptPath 
				<< " - 'stateType' should be a string.\n";

		}
		else {
			char* type = new char[ 32 ];
	
			strcpy( type, lua_tostring( L, 1 ) );

			if ( strncmp( type, "Static Movement\n", 8 ) == 0 ){
				GameState* state 
					= new GameStaticMovementState;
			
				/**
				 * After creation, the state is pushed onto
				 * the engine's state stack, and then it is
				 * initiated.
				 **/

				PushState( state );
				state->Init( mainScreen, scriptPath );
			}

			delete type;
		}
	

		lua_pop( L, 1 );
	}
	lua_close( L );
	L = NULL;
}

/**********************************************************//**
 *   This function's main purpose is to call the drawing 
 * function of the current state.
 *************************************************************/
void PlatformEngine::Draw() {
	if ( !stateStack.empty() ) {
		SDL_FillRect( mainScreen, 
				NULL, 
				SDL_MapRGB( mainScreen->format, 0, 0, 0 ) 
				);
		GameState* topState = stateStack.top();
	//	cout << "1 " << mainScreen << topState << endl;
		if ( topState != NULL ) topState->Draw();
	}

	SDL_UpdateRect( mainScreen, 0, 0, mainScreen->w, mainScreen->h );
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
			if ( topState != NULL ) {
				if ( topState->HandleEvents( this, event )
						== true ) 
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
 *   This function takes a reference to a state and then 
 * pushes it onto the top of the engine's state stack. That 
 * then becomes the active stack for the engine.
 *
 * \param state Pointer to the newly-created state being pushed
 * \param scriptPath The path to the state's configuration script
 *************************************************************/
void PlatformEngine::PushState( GameState* state, char* scriptPath ){
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

} // namespace Platform

#endif
