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

#include "GameNavigationState.h"

GameNavigationState::GameNavigationState() {
	return;
}

void GameNavigationState::Init() {
	return;
}

void GameNavigationState::Cleanup() {
	return;
}

void GameNavigationState::Pause() {
	return;
}

void GameNavigationState::Resume() {
	return;
}

void GameNavigationState::HandleEvents( PlatformEngine* game,
					SDL_Event& event ) {
	switch( event.type ) {
		case SDL_KEYDOWN:
			switch ( event.key.keysym.sym ) {
				case SDLK_UP:
					game->Quit();
					break;
			}

			break;
	}
}

void GameNavigationState::Update( PlatformEngine* game ) {
	return;
}

void GameNavigationState::Draw( PlatformEngine* game ) {
	return;
}

bool GameNavigationState::MovePlayerUp() {
	return false;
}

bool GameNavigationState::MovePlayerDown() {
	return false;
}

bool GameNavigationState::MovePlayerLeft() {
	return false;
}

bool GameNavigationState::MovePlayerRight() {
	return false;
}

#endif
