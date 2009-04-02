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

/**********************************************************//**
 *   Configures assets specific to this state; particularly 
 * assets involved with map construction.
 *************************************************************/
void GameNavigationState::Init() {
	return;
}

/**********************************************************//**
 *   Does any last-minute operations before the termination of 
 * the navigation state.
 *************************************************************/
void GameNavigationState::Cleanup() {
	return;
}

/**********************************************************//**
 *   Pauses the execution of this state until further notice, 
 * assuming it is currently running. If it is already paused, 
 * this has no effect.
 *************************************************************/
void GameNavigationState::Pause() {
	return;
}


/**********************************************************//**
 *   Resumes the execution of this state, if it has been 
 * paused previously; otherwise it has no effect.
 *************************************************************/
void GameNavigationState::Resume() {
	return;
}

/**********************************************************//**
 *   Handles event triggers for this state, including the 
 * movement of the player within the map.
 * 
 * \param game A pointer to the game engine
 * \param event Reference to the last polled SDL_Event
 *************************************************************/
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

/**********************************************************//**
 *   Does any necessary logic updates to bring the game's data 
 * up to date with the actions of the player or anything else 
 * in the game.
 *
 * \param game A pointer to the game engine
 *************************************************************/
void GameNavigationState::Update( PlatformEngine* game ) {
	return;
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
 *   Gives the impression of the player moving "up" on the map 
 * by moving everything else downward and possibly triggering 
 * a movement animation for the player's image. Fails if there 
 * is a collision between the player and a map object.
 *
 * \return True if the movement succeeds, false if there is collision
 *************************************************************/
bool GameNavigationState::MovePlayerUp() {
	return false;
}

/**********************************************************//**
 *   Gives the impression of the player moving "down" on the map 
 * by moving everything else upward and possibly triggering 
 * a movement animation for the player's image. Fails if there 
 * is a collision between the player and a map object.
 *
 * \return True if the movement succeeds, false if there is collision
 *************************************************************/
bool GameNavigationState::MovePlayerDown() {
	return false;
}

/**********************************************************//**
 *   Gives the impression of the player moving "left" on the map 
 * by moving everything else to the right and possibly triggering 
 * a movement animation for the player's image. Fails if there 
 * is a collision between the player and a map object.
 *
 * \return True if the movement succeeds, false if there is collision
 *************************************************************/
bool GameNavigationState::MovePlayerLeft() {
	return false;
}

/**********************************************************//**
 *   Gives the impression of the player moving "right" on the map 
 * by moving everything else leftward and possibly triggering 
 * a movement animation for the player's image. Fails if there 
 * is a collision between the player and a map object.
 *
 * \return True if the movement succeeds, false if there is collision
 *************************************************************/
bool GameNavigationState::MovePlayerRight() {
	return false;
}

#endif
