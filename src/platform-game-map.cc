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


#include "platform-game-map.h"

#include <cstring>
#include <iostream>

#include "SDL.h"

#include "platform-lua-includes.h"
#include "platform-game-map-layer.h"
#include "platform-game-map-layer-background.h"

namespace Platform {

using std::vector;
using std::cerr;
using std::endl;

GameMap::GameMap() {
	mapScript = NULL;
}

GameMap::~GameMap() {
  Cleanup();
}

void GameMap::Init( SDL_Surface* theDisplay, char* aScript ) {
  mainScreen = theDisplay;
  
  mapScript = new char[ 64 ];
  strcpy( mapScript, aScript );

  if ( mapScript != NULL ) {
    lua_State* L = luaL_newstate();

    if ( luaL_loadfile( L, mapScript ) || lua_pcall( L, 0, 0, 0 ) ) {
      cerr << "Failed to load " << mapScript << endl;
    }

    lua_getglobal( L, "layerOneType" );
    lua_getglobal( L, "backgroundImage" );
    lua_getglobal( L, "verticalScrolling" );

    if ( !lua_isstring( L, 1 ) ) {
      cerr << "layerOneType is not a string. - ";
      for ( int n = 0 ; mapScript[ n ] != '\n' ; ++n ) 
        cerr << mapScript[ n ];
      cerr << endl;  
    }
    else {
      char* theType = new char[ 32 ];
      strcpy( theType, lua_tostring( L, 1 ) );

      if ( strncmp( theType, "Background\n", 8 ) == 0 ) {
        if ( !lua_isstring( L, 2 ) ) {
          cerr << "backgroundImage is not a string. - ";
          for ( int n = 0 ; mapScript[ n ] != '\n' ; ++n ) 
            cerr << mapScript[ n ];
          cerr << endl;
        }
        else {
          char* imagePath = new char[ 64 ];
          strcpy( imagePath, "../../\0" );
          strcat( imagePath, lua_tostring( L, 2 ) );

          if ( !lua_isboolean( L, 3 ) ) {
            cerr << "verticalScrolling is not a boolean. - ";
            for ( int n = 0 ; mapScript[ n ] != '\n' ; ++n ) 
              cerr << mapScript[ n ];
            cerr << endl;
          }
          else {
            bool verticalScrolling = lua_toboolean( L, 3 );
            GameMapLayer* newLayer = new GameMapBackgroundLayer;
            newLayer->Init( mainScreen, imagePath, verticalScrolling );
            layerList.push_back( newLayer );
          }

          delete imagePath;
          imagePath = NULL;
        }
        char* imagePath = new char[ 64 ];
        strcpy( imagePath, "../../\0" );

      }

      delete theType;
      theType = NULL;
    }
  }
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
	vector< GameMapLayer* >::iterator i;

	for ( i = layerList.begin() ; i != layerList.end() ; ++i ) {
		(*i)->Draw();
	}

	return;
}

void GameMap::Cleanup() {
  if ( mapScript != NULL )
    delete mapScript;

  if ( !layerList.empty() ) {
    vector< GameMapLayer* >::iterator i;
    for ( i = layerList.begin() ; i != layerList.end() ; ++i ) {
      delete *i;
    }
    while ( !layerList.empty() ) layerList.pop_back();
  }

  mainScreen = NULL;
}

} // namespace Platform

#endif
