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
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
***************************************************************************/

#include "GameState.h"

#include <vector>

class PlatformEngine {
	public:
		void Init();
		void Cleanup();

		void ChangeState( GameState* state );
		void PushState( GameState* state );
		void PopState();

		void HandleEvents();
		void Update();
		void Draw();

		bool Running() { return running; }
		void Quit() { running = false; }

	private:
		vector< GameState* > states;

		bool running;
};
