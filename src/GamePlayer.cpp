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

#ifndef GAMEPLAYER_CPP
#define GAMEPLAYER_CPP

#include <iostream>
#include <cstring>

#include "GamePlayer.h"
#include "SDL_image.h"

using std::cout;
using std::cerr;
using std::endl;

GamePlayer::GamePlayer() {
	imagePath = NULL;
	playerSurface = NULL;
	
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
void GamePlayer::Init( const char* image ) {
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
 *
 * \param mainScreen The surface that the image is to be drawn to
 *************************************************************/
void GamePlayer::Draw( SDL_Surface* mainScreen ) {
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

void GamePlayer::Update() {
	if ( moveUp ) dimensions.y -= 1;
	if ( moveDown ) dimensions.y += 1;
	if ( moveLeft ) dimensions.x -= 1;
	if ( moveRight ) dimensions.x += 1;
}

/**********************************************************//**
 *   Moves the player by changing its position on the 2D grid,
 * using the dimensions passed in the delta as modifiers.
 *
 * \param delta The 2D movement vectors of the player
 *************************************************************/
void GamePlayer::SetMoveUp( const bool& flag ) {
	moveUp = flag;
}

void GamePlayer::SetMoveDown( const bool& flag ) {
	moveDown = flag;
}

void GamePlayer::SetMoveLeft( const bool& flag ) {
	moveLeft = flag;
}

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

#endif
