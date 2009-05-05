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

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "platform-game-map-layer-background.h"

using std::cout;
using std::cerr;
using std::endl;

namespace Platform {

GameMapBackgroundLayer::GameMapBackgroundLayer(){
  layerImage = NULL;
  mainScreen = NULL;
}
  
GameMapBackgroundLayer::~GameMapBackgroundLayer() {
  if (layerImage != NULL) SDL_FreeSurface(layerImage);
  mainScreen = NULL;
}

void GameMapBackgroundLayer::Init( 
    SDL_Surface* theDisplay, 
    char*        imagePath, 
    bool         verticalScrolling) {
  if (imagePath != NULL) {
    mainScreen = theDisplay;
    goVertical = verticalScrolling;
    SDL_Surface* tileImage = IMG_Load(imagePath);
    
    if ( tileImage == NULL ) {
      cerr << "Image not found - " << imagePath << endl;
    }
    else {
      tileSize.w = tileImage->w;
      tileSize.h = tileImage->h;
      layerImage = SDL_CreateRGBSurface(
          mainScreen->flags,
          (mainScreen->w + tileSize.w),
          (mainScreen->h + tileSize.h),
          mainScreen->format->BitsPerPixel,
          mainScreen->format->Rmask,
          mainScreen->format->Gmask,
          mainScreen->format->Bmask,
          mainScreen->format->Amask);
      if ( layerImage == NULL ) {
        cerr << "Failed to create layerImage; " << SDL_GetError() << endl;
      }
      else {
        for (int i=0; i < layerImage->w; i += tileSize.w) {
          for (int j=0; j < layerImage->h; j+= tileSize.h) {
            SDL_Rect position;
            position.x = i;
            position.y = j;
  
            SDL_BlitSurface(tileImage, NULL, layerImage, &position);
          }
        }

        drawDimensions.w = mainScreen->w;
        drawDimensions.h = mainScreen->h;
        drawDimensions.x = 0;
        drawDimensions.y = tileSize.h;

        SDL_FreeSurface(tileImage);
      }
    }
  }
}

void GameMapBackgroundLayer::Draw() {
  if (mainScreen != NULL)
    if (layerImage != NULL) {
      SDL_BlitSurface(layerImage, &drawDimensions, mainScreen, NULL);
    }
}

void GameMapBackgroundLayer::Update() {
  if ( mainScreen != NULL ) {
    if ( layerImage != NULL ) {
      if ( goVertical ) {
        if (drawDimensions.y <= 0)
          drawDimensions.y = tileSize.h;
        else
          --drawDimensions.y;
      }
    }
  }
}

} // namespace Platform

#endif
