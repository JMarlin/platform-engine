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

#ifndef GAMESTATE_CPP
#define GAMESTATE_CPP

#include "platform-game-state.h"

namespace Platform {

/**********************************************************//**
 *   Pauses the execution of this state until further notice, 
 * assuming it is currently running. If it is already paused, 
 * this has no effect.
 *************************************************************/
void GameState::Pause() {
	running = false;
}

/**********************************************************//**
 *   Resumes the execution of this state, if it has been 
 * paused previously; otherwise it has no effect.
 *************************************************************/
void GameState::Resume() {
	running = true;
}

} // namespace Platform

#endif
