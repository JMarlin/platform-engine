/***************************************************************************
    � Copyright 2009 Patrick VanDusen

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

#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "PlatformEngine.h"
#include "GameMapLayer.h"

#include <stack>

using std::stack;

/**********************************************************//**
 * \brief The map being used by the navigation state.
 *
 *   This is a 'map', or a 'world', that can be navigated and 
 * interacted with in the game navigation state. It consists of 
 * a stack of layers, which have a number of different types 
 * that can be used for different purposes. The map contains 
 * functions that specify where on the screen grid the layers 
 * it contains should be drawn, which is how it is told by the 
 * GameNavigationState which direction it should move in order 
 * to give the impression that the Player is moving about in 
 * the map.
 *************************************************************/
class GameMap {
	public:
		GameMap();
		
		//** Moves the onscreen position of the map upward
		void MoveMapUp();
		
		//** Moves the onscreen position of the map downward
		void MoveMapDown();

		//** Moves the onscreen position of the map to the left
		void MoveMapLeft();

		//** Moves the onscreen position of the map to the right
		void MoveMapRight();

		//** Draws the map to the engine's main screen
		void Draw( PlatformEngine* game );

	private:
		//** The stack of layers 
		stack< GameMapLayer* > layerStack;
		
		//** The size and on-screen positioning of the map
		SDL_Rect mapDimensions;

};


#endif
