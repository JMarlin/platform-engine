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

#ifndef GAMEMAP_CPP
#define GAMEMAP_CPP

#include "GameMap.h"
#include "SDL.h"

GameMap::GameMap() {
	//blank
}

/**********************************************************//**
 *   Moves the apparent position of the map on the screen,
 * using the dimensions in the delta as modifiers of the 
 * map's original positioning.
 *
 * \param delta The 2D movement vectors of the map on screen
 *************************************************************/
void GameMap::MoveMap( SDL_Rect& delta ) {
	return;
}

/**********************************************************//**
 *   Draws the map to the screen by drawing each of its layers 
 * to the screen, from 'bottom' to 'top', in sequence.
 *
 * \param mainScreen The surface that the map is to be drawn to.
 *************************************************************/
void GameMap::Draw( SDL_Surface* mainScreen ) {
	return;
}

#endif
