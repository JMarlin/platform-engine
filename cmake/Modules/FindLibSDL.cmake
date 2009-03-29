# FindLibSDL.cmake
# by Patrick VanDusen( patrick@pdusen.com )
# Originally made on 03/29/2009
#
#   This is a modified FindSDL package. The original included with the 
# CMake distribution had many weaknesses, particularly on Windows systems, 
# that required a great deal of manual intervention. I have written this 
# modified version to require a great deal less manual intervention in 
# these instances. More details can be read below.
#
#   To automatically locate SDL on your system, set the following
# environment variables:
#
#	SDLDIR -- The root SDL folder on your system. Should contain the
#		folders 'include' and 'src'. 
#		Example: "C:/prog/SDL/" on Windows.
#	SDL_COMPILE_MODE -- Specifically to indicate to CMake whether you 
#		are using Release or Debug libraries. Mostly useful on
#		Windows systems using Visual Studio.
#		Examples: The only choices are DEBUG and RELEASE.
#		

FIND_PATH( SDL_INCLUDE_DIR SDL.h
	HINTS
	$ENV{SDLDIR}
	PATH_SUFFIXES include
	PATHS
	$ENV{SDLDIR}/include
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local/include/SDL
	/usr/include/SDL
	/usr/local/include/SDL12
	/usr/local/include/SDL11 # FreeBSD ports
	/usr/include/SDL12
	/usr/include/SDL11
	/usr/local/include
	/usr/include
	/sw/include/SDL # Fink
	/sw/include
	/opt/local/include/SDL # DarwinPorts
	/opt/local/include
	/opt/csw/include/SDL # Blastwave
	/opt/csw/include 
	/opt/include/SDL
	/opt/include
)
MESSAGE("SDL_INCLUDE_DIR is ${SDL_INCLUDE_DIR}")

#   The SDL Documentation specifies that, when compiling SDL libraries 
# manually from source using Visual Studio, the Visual Studio project files 
# should be unzipped from the ${SDLDIR}/VisualC.zip file into the
# ${SDLDIR}/VisualC/ directory.
#
#   Inside the ${SDLDIR}/VisualC/ directory are subdirectories for the 
# separate SDL and SDLmain libraries.
#
#   Inside each of these folders, Visual C will, by default, compile the
# libraries inside either a Release or a Debug folder, depending on the 
# project settings.
#
#   In keeping with these defaults, and in order to minimize the necessity 
# for manual intervention by the developer, I have made it trivial for this 
# package to automatically locate these libraries using the environment 
# variables $ENV{SDLDIR} and $ENV{SDL_COMPILE_MODE} as part of the path
# names.

FIND_LIBRARY (SDL_LIBRARY_TEMP
	NAMES SDL SDL-1.1 SDL.lib
	HINTS
	$ENV{SDLDIR}
	PATH_SUFFIXES lib64 lib $ENV{SDL_COMPILE_MODE}
	PATHS
	$ENV{SDLDIR}/VisualC/SDL/$ENV{SDL_COMPILE_MODE} # For Visual Studio
	/usr/local
	/usr
	/sw
	/opt/local
	/opt/csw
	/opt
)
MESSAGE( "SDL_LIBRARY_TEMP is ${SDL_LIBRARY_TEMP}" )

IF(NOT SDL_BUILDING_LIBRARY)
	IF(NOT ${SDL_INCLUDE_DIR} MATCHES ".framework")
    # Non-OS X framework versions expect you to also dynamically link to 
    # SDLmain. This is mainly for Windows and OS X. Other (Unix) platforms 
    # seem to provide SDLmain for compatibility even though they don't
    # necessarily need it.
    FIND_LIBRARY(SDLMAIN_LIBRARY 
	    NAMES SDLmain SDLmain-1.1 SDLMain.lib
	    HINTS
	    $ENV{SDLDIR}
	    PATH_SUFFIXES lib64 lib $ENV{SDL_COMPILE_MODE}
	    PATHS
	    $ENV{SDLDIR}/VisualC/SDLmain/$ENV{SDL_COMPILE_MODE} # For Visual Studio
	    /usr/local
	    /usr
	    /sw
	    /opt/local
	    /opt/csw
	    /opt
	)
	ENDIF(NOT ${SDL_INCLUDE_DIR} MATCHES ".framework")
ENDIF(NOT SDL_BUILDING_LIBRARY)

# SDL may require threads on your system.
# The Apple build may not need an explicit flag because one of the 
# frameworks may already provide it. 
# But for non-OSX systems, I will use the CMake Threads package.
IF(NOT APPLE)
  FIND_PACKAGE(Threads)
ENDIF(NOT APPLE)

# MinGW needs an additional library, mwindows
# It's total link flags should look like -lmingw32 -lSDLmain -lSDL -lmwindows
# (Actually on second look, I think it only needs one of the m* libraries.)
IF(MINGW)
  SET(MINGW32_LIBRARY mingw32 CACHE STRING "mwindows for MinGW")
ENDIF(MINGW)

IF(SDL_LIBRARY_TEMP)
  # For SDLmain
  IF(NOT SDL_BUILDING_LIBRARY)
    IF(SDLMAIN_LIBRARY)
      SET(SDL_LIBRARY_TEMP ${SDLMAIN_LIBRARY} ${SDL_LIBRARY_TEMP})
    ENDIF(SDLMAIN_LIBRARY)
  ENDIF(NOT SDL_BUILDING_LIBRARY)

  # For OS X, SDL uses Cocoa as a backend so it must link to Cocoa.
  # CMake doesn't display the -framework Cocoa string in the UI even 
  # though it actually is there if I modify a pre-used variable.
  # I think it has something to do with the CACHE STRING.
  # So I use a temporary variable until the end so I can set the 
  # "real" variable in one-shot.
  IF(APPLE)
    SET(SDL_LIBRARY_TEMP ${SDL_LIBRARY_TEMP} "-framework Cocoa")
  ENDIF(APPLE)
    
  # For threads, as mentioned Apple doesn't need this.
  # In fact, there seems to be a problem if I used the Threads package
  # and try using this line, so I'm just skipping it entirely for OS X.
  IF(NOT APPLE)
    SET(SDL_LIBRARY_TEMP ${SDL_LIBRARY_TEMP} ${CMAKE_THREAD_LIBS_INIT})
  ENDIF(NOT APPLE)

  # For MinGW library
  IF(MINGW)
    SET(SDL_LIBRARY_TEMP ${MINGW32_LIBRARY} ${SDL_LIBRARY_TEMP})
  ENDIF(MINGW)

  # Set the final string here so the GUI reflects the final state.
  SET(SDL_LIBRARY ${SDL_LIBRARY_TEMP} CACHE STRING "Where the SDL Library can be found")
  # Set the temp variable to INTERNAL so it is not seen in the CMake GUI
  SET(SDL_LIBRARY_TEMP "${SDL_LIBRARY_TEMP}" CACHE INTERNAL "")

  SET(SDL_FOUND "YES")
ENDIF(SDL_LIBRARY_TEMP)

MESSAGE("SDL_LIBRARY is ${SDL_LIBRARY}")

