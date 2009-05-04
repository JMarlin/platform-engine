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

#ifndef PLATFORM_GAME_MAP_LAYER_BACKGROUND
#define PLATFORM_GAME_MAP_LAYER_BACKGROUND

#include "SDL.h"
#include "platform-game-map-layer-background.h"

namespace Platform {

GameMapBackgroundLayer::GameMapBackgroundLayer(){
  //blank
}
  
GameMapBackgroundLayer::~GameMapBackgroundLayer() {
  //blank
}

void GameMapBackgroundLayer::Init( 
    SDL_Surface* theDisplay, 
    char*        imagePath, 
    bool         verticalScrolling ) {
  return;
}

void GameMapBackgroundLayer::Draw() {
  return;
}

} // namespace Platform

#endif
