# © Copyright 2009 Patrick VanDusen
# 
# This file is part of the Platform 2D Game Engine, 
# also referred to as Platform.
#
# Platform is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as 
# published by the Free Software Foundation, either version 3 of the 
# License, or (at your option) any later version.
#
# Platform is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public License
# along with Platform.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required( VERSION 2.6 )

set( CMAKE_MODULE_PATH 
	${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/" )

project( platform-engine )

set( SRCDIR "${CMAKE_SOURCE_DIR}/src/" )
set( DOCDIR "${CMAKE_SOURCE_DIR}/doc/" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/" )

find_package( SDL REQUIRED )

find_package( Lua51 REQUIRED )

set ( SOURCES
	${SRCDIR}/main.cpp
	${SRCDIR}/luainc.h
	${SRCDIR}/GameLoopDelay.h	${SRCDIR}/GameLoopDelay.cpp
	${SRCDIR}/PlatformEngine.h	${SRCDIR}/PlatformEngine.cpp
	${SRCDIR}/GameState.h		${SRCDIR}/GameState.cpp
	${SRCDIR}/GameNavigationState.h	${SRCDIR}/GameNavigationState.cpp
	${SRCDIR}/GameMap.h
	${SRCDIR}/GameMapLayer.h
)

link_libraries (
   ${SDL_LIBRARY}
   #   ${SDLIMAGE_LIBRARY} # if using SDL_image, obviously
   ${SDLMAIN_LIBRARY} # Sadly not included in SDL_LIBRARY variable
)

add_executable (
   platform-engine
   WIN32
   MACOSX_BUNDLE
   ${SOURCES}
)

