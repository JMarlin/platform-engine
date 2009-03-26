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

#include "PlatformEngine.h"

class GameState {
	public:
		virtual void Init() = 0;
		virtual void Cleanup() = 0;

		virtual void Pause() = 0;
		virtual void Resume() = 0;

		virtual void HandleEvents( PlatformEngine* game ) = 0;
		virtual void Update( 	   PlatformEngine* game ) = 0;
		virtual void Draw( 	   PlatformEngine* game ) = 0;

		void ChangeState(	PlatformEngine* game,
			       		GameState* state ) {
			game->ChangeState( state );
		}

	protected:
		GameState() { }
};
