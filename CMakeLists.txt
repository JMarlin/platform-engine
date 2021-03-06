# � Copyright 2009 Patrick VanDusen
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
set( CMAKE_USE_RELATIVE_PATHS true )

#set( CMAKE_MODULE_PATH 
#	${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/" )

project( platform-engine )

set( SRCDIR "${CMAKE_SOURCE_DIR}/src/" )
set( DOCDIR "${CMAKE_SOURCE_DIR}/doc/" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/" )

find_package( PNG REQUIRED )

find_package( SDL REQUIRED )

find_package( SDL_image REQUIRED )

find_package( Lua51 REQUIRED )

find_package( Doxygen )

#set(Boost_USE_STATIC_LIBS   ON)
#set(Boost_USE_MULTITHREADED ON)
#find_package( Boost COMPONENTS filesystem REQUIRED )

set ( SOURCES
	${SRCDIR}/platform-game-main.cc
	${SRCDIR}/platform-lua-includes.h
	${SRCDIR}/platform-loop-delay.h	${SRCDIR}/platform-loop-delay.cc
	${SRCDIR}/platform-engine.h	${SRCDIR}/platform-engine.cc
	${SRCDIR}/platform-game-state.h	${SRCDIR}/platform-game-state.cc
	${SRCDIR}/platform-game-state-static-movement.h
	${SRCDIR}/platform-game-state-static-movement.cc
	${SRCDIR}/platform-game-map.h	${SRCDIR}/platform-game-map.cc
	${SRCDIR}/platform-game-map-layer.h
  ${SRCDIR}/platform-game-map-layer-background.h
  ${SRCDIR}/platform-game-map-layer-background.cc
	${SRCDIR}/platform-game-player.h
	${SRCDIR}/platform-game-player.cc
)

link_libraries (
   ${SDL_LIBRARY}
   ${SDLMAIN_LIBRARY} # Sadly not included in SDL_LIBRARY variable
   ${SDLIMAGE_LIBRARY} # if using SDL_image, obviously
   ${LUA_LIBRARIES}
)


add_executable (
   platform-engine
   WIN32
   MACOSX_BUNDLE
   ${SOURCES}
)
if ( DOXYGEN_FOUND )
	add_custom_command(
		TARGET platform-engine
		POST_BUILD
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOCDIR}/Doxyfile
	)	
endif()
