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

#ifndef GAMELOOPDELAY_CPP
#define GAMELOOPDELAY_CPP

#include "SDL.h"

#include "GameLoopDelay.h"

/**********************************************************//**
 *    In order to avoid maximizing CPU usage at all times, the 
 * engine ensures a certain number of ticks have passed before 
 * updating.  
 * 
 * \return The number of ticks remaining until the next update
 *************************************************************/
Uint32 time_left() {
	Uint32 now = SDL_GetTicks();

	if ( nextTime <= now ) return 0;
	else return nextTime - now;
}

#endif
