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

#include "SDL.h"

#include "PlatformEngine.h"
#include "GameLoopDelay.h"
#include "GameNavigationState.h"

//const char* title = "Platform Engine Test v0.0.1 Pre-Alpha\0";

int main( int argc, char* argv[] ) {

	PlatformEngine game;

	game.Init();
	
	nextTime = SDL_GetTicks() + TICK_INTERVAL;

	// When written, the next line will initialize the intro state.
	game.PushState( new GameNavigationState );

	while ( game.Running() ) {
		
		game.HandleEvents();
		game.Update();
		game.Draw();

		SDL_Delay( time_left() );
		nextTime += TICK_INTERVAL;
	}

	game.Cleanup();	

	return 0;
}
