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

#ifndef GAMEMAPLAYER_H
#define GAMEMAPLAYER_H

#include "SDL.h"

#include "platform-engine.h"

#include <stack>

namespace Platform {

using std::stack;

/**********************************************************//**
 * \brief A section of the map object
 *
 *   This is an abstract class representing a layer of the map 
 * object used by the Navigation State. It is not meant to be 
 * used, but is the ancestor of several specific types of map 
 * layers.
 *************************************************************/
class GameMapLayer {
	public:
    //** Draws the content of the layer to the engine screen

    virtual void Init( SDL_Surface* theDisplay = NULL, 
          char*        imagePath = NULL, 
          bool         verticalScrolling = false ) = 0;

    virtual void Update() = 0;

    virtual void Draw() = 0; 

	protected:
    //** The image of the layer
    SDL_Surface* layerImage;

    SDL_Surface* mainScreen;

    bool goVertical;
};

}

#endif
