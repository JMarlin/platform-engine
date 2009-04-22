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
	theMap = NULL;
	//thePlayer = NULL;
}

/**********************************************************//**
 *   Configures assets specific to this state; particularly 
 * assets involved with map construction.
 *************************************************************/
void GameNavigationState::Init() {
	running = true;
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
/*
	if ( thePlayer != NULL ) {
		delete thePlayer;
		thePlayer = NULL;
	}*/
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
 * \param game A pointer to the game engine
 *************************************************************/
void GameNavigationState::Draw( PlatformEngine* game ) {
	return;
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
