cmake_minimum_required( VERSION 2.6 )

project ( platform-engine )

set ( SOURCES
   main.cpp
   PlatformEngine.h
   GameState.h
)

# REQUIRED does not work in CMake <=2.4.6 for SDL
Find_Package ( SDL REQUIRED )
#Find_Package ( SDL_image REQUIRED ) # if using SDL_image

# Workaround for the non-working REQUIRED flag
if ( NOT SDL_FOUND )
   message ( FATAL_ERROR "SDL not found!" )
endif ( NOT SDL_FOUND )

link_libraries (
   ${SDL_LIBRARY}
   #   ${SDLIMAGE_LIBRARY} # if using SDL_image, obviously
   ${SDLMAIN_LIBRARY} # Sadly not included in SDL_LIBRARY variable
)

add_executable (
   platform-engine
   WIN32 # Only if you don't want the DOS prompt to appear in the background in Windows
   MACOSX_BUNDLE
   ${SOURCES} # We could've listed the source files here directly instead of using a variable to store them
)

