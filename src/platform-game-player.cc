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

#ifndef GAMEPLAYER_CPP
#define GAMEPLAYER_CPP

#include <iostream>
#include <cstring>

#include "platform-game-player.h"
#include "SDL_image.h"

namespace Platform {

using std::cout;
using std::cerr;
using std::endl;

GamePlayer::GamePlayer() {
	imagePath = NULL;
	playerSurface = NULL;
  mainScreen = NULL;
	
	moveUp = false;
	moveDown = false;
	moveLeft = false;
	moveRight = false;
}

/**********************************************************//**
 *   Initiates the player object by loading the relevant 
 * image and dimension information.
 *
 * \param image The full path to the file to be used as the player image
 *************************************************************/
void GamePlayer::Init( SDL_Surface* theDisplay, const char* image ) {
  mainScreen = theDisplay;

  if ( image != NULL ) {
		imagePath = new char[32];

		strcpy( imagePath, image );

		playerSurface = IMG_Load( imagePath );
		
		if ( playerSurface == NULL ) {
			cerr << "Couldn't load " << imagePath << " - "
				<< SDL_GetError() << endl;
			return;
		}
		else {
			if ( SDL_SetColorKey( 
					playerSurface,
					SDL_SRCCOLORKEY,
					SDL_MapRGB( 
						playerSurface->format,
						255,
						0,
						255 )
				       ) == -1 ) {
				cerr << "Failed to set transparency on "
					<< imagePath << "; - "
					<< SDL_GetError() << endl;
			}

			dimensions.w = playerSurface->w;
			dimensions.h = playerSurface->h;
		}


	}
}

/**********************************************************//**
 *   Draws the image of the player to the indicated surface, 
 * usually the primary display screen of the engine. This 
 * function is dependent upon the existance of both the 
 * player image and the screen.
 *************************************************************/
void GamePlayer::Draw() {
	if ( mainScreen != NULL ) {
		if ( imagePath != NULL ) {
			
			if ( SDL_BlitSurface( playerSurface, 
						NULL, 
						mainScreen, 
						&dimensions ) < 0 )
				cerr << "BlitSurface error - "
					<< SDL_GetError() << endl;
		}
	}
}

/**********************************************************//**
 *   Does the regular recalculations required by the state, 
 * usually in reaction to user input, such as moving the player 
 * entity.
 *************************************************************/
void GamePlayer::Update() {
  if ( moveUp )
    if ( dimensions.y > 0 )
      dimensions.y -= 1;

  if ( moveDown )
    if ( dimensions.y + dimensions.h < mainScreen->h )
      dimensions.y += 1;

  if ( moveLeft )
    if ( dimensions.x > 0 )
      dimensions.x -= 1;
  
  if ( moveRight )
    if ( dimensions.x + dimensions.w < mainScreen->w )
      dimensions.x += 1;
}

/**********************************************************//**
 *   Is used to change the value of the flag that dictates 
 * whether or not the GamePlayer instance is moving "upward" 
 * on the display.
 *
 * /param flag True if the player is moving upward, otherwise false.
 *************************************************************/
void GamePlayer::SetMoveUp( const bool& flag ) {
	moveUp = flag;
}

/**********************************************************//**
 *   Is used to change the value of the flag that dictates 
 * whether or not the GamePlayer instance is moving "downward" 
 * on the display.
 *
 * /param flag True if the player is moving down, otherwise false.
 *************************************************************/
void GamePlayer::SetMoveDown( const bool& flag ) {
	moveDown = flag;
}

/**********************************************************//**
 *   Is used to change the value of the flag that dictates 
 * whether or not the GamePlayer instance is moving "left" 
 * on the display.
 *
 * /param flag True if the player is moving left, otherwise false.
 *************************************************************/
void GamePlayer::SetMoveLeft( const bool& flag ) {
	moveLeft = flag;
}

/**********************************************************//**
 *   Is used to change the value of the flag that dictates 
 * whether or not the GamePlayer instance is moving "right" 
 * on the display.
 *
 * /param flag True if the player is moving right, otherwise false.
 *************************************************************/
void GamePlayer::SetMoveRight( const bool& flag ) {
	moveRight = flag;
}

GamePlayer::~GamePlayer() {
	cout << "DYING! " << this << endl;
	if ( imagePath != NULL ) {
		delete [] imagePath;
		imagePath = NULL;
	}

	if ( playerSurface != NULL ) {
		SDL_FreeSurface( playerSurface );
	}
	cout << "dead. " << this << endl;
}

} // namespace Platform

#endif
