# - Locate SDL_mixer library
# This module defines:
#  SDL3_MIXER_LIBRARIES, the name of the library to link against
#  SDL3_MIXER_INCLUDE_DIRS, where to find the headers
#  SDL3_MIXER_FOUND, if false, do not try to link against
#  SDL3_MIXER_VERSION_STRING - human-readable string containing the version of SDL_mixer
#
# For backward compatiblity the following variables are also set:
#  SDLMIXER_LIBRARY (same value as SDL3_MIXER_LIBRARIES)
#  SDLMIXER_INCLUDE_DIR (same value as SDL3_MIXER_INCLUDE_DIRS)
#  SDLMIXER_FOUND (same value as SDL3_MIXER_FOUND)
#
# $SDLDIR is an environment variable that would
# correspond to the ./configure --prefix=$SDLDIR
# used in building SDL.
#
# Created by Eric Wing. This was influenced by the FindSDL.cmake
# module, but with modifications to recognize OS X frameworks and
# additional Unix paths (FreeBSD, etc).

#=============================================================================
# Copyright 2005-2009 Kitware, Inc.
# Copyright 2012 Benjamin Eikel
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(SDL3_ARCH_64 TRUE)
  set(SDL3_PROCESSOR_ARCH "x64")
else()
  set(SDL3_ARCH_64 FALSE)
  set(SDL3_PROCESSOR_ARCH "x86")
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)

SET(SDL3_SEARCH_PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw # Fink
    /opt/local # DarwinPorts
    /opt/csw # Blastwave
    /opt
	../../3rdparty/SDL3_mixer
	../../../3rdparty/SDL3_mixer
	../../../../3rdparty/SDL3_mixer
)

if(NOT SDL3_MIXER_INCLUDE_DIR AND SDL3MIXER_INCLUDE_DIR)
  set(SDL3_MIXER_INCLUDE_DIR ${SDL3MIXER_INCLUDE_DIR} CACHE PATH "directory cache
entry initialized from old variable name")
endif()
find_path(SDL3_MIXER_INCLUDE_DIR SDL3/SDL_mixer.h
  HINTS
    ENV SDL3MIXERDIR
    ENV SDL3DIR
  PATH_SUFFIXES include
  PATHS ${SDL3_SEARCH_PATHS}
)

if(NOT SDL3_MIXER_LIBRARY AND SDL3MIXER_LIBRARY)
  set(SDL3_MIXER_LIBRARY ${SDL3MIXER_LIBRARY} CACHE FILEPATH "file cache entry
initialized from old variable name")
endif()
find_library(SDL3_MIXER_LIBRARY
  NAMES SDL3_mixer
  HINTS
    ENV SDL3MIXERDIR
    ENV SDL3DIR
  PATH_SUFFIXES lib64 lib lib/i386-linux-gnu build-mingw-x86
  PATHS ${SDL3_SEARCH_PATHS}
)

if(SDL3_MIXER_INCLUDE_DIR AND EXISTS "${SDL3_MIXER_INCLUDE_DIR}/SDL_mixer.h")
  file(STRINGS "${SDL3_MIXER_INCLUDE_DIR}/SDL_mixer.h" SDL3_MIXER_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL_MIXER_MAJOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL3_MIXER_INCLUDE_DIR}/SDL_mixer.h" SDL3_MIXER_VERSION_MINOR_LINE REGEX "^#define[ \t]+SDL_MIXER_MINOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${SDL3_MIXER_INCLUDE_DIR}/SDL_mixer.h" SDL3_MIXER_VERSION_PATCH_LINE REGEX "^#define[ \t]+SDL_MIXER_PATCHLEVEL[ \t]+[0-9]+$")
  string(REGEX REPLACE "^#define[ \t]+SDL_MIXER_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL3_MIXER_VERSION_MAJOR "${SDL3_MIXER_VERSION_MAJOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_MIXER_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL3_MIXER_VERSION_MINOR "${SDL3_MIXER_VERSION_MINOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SDL_MIXER_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" SDL3_MIXER_VERSION_PATCH "${SDL3_MIXER_VERSION_PATCH_LINE}")
  set(SDL3_MIXER_VERSION_STRING ${SDL3_MIXER_VERSION_MAJOR}.${SDL3_MIXER_VERSION_MINOR}.${SDL3_MIXER_VERSION_PATCH})
  unset(SDL3_MIXER_VERSION_MAJOR_LINE)
  unset(SDL3_MIXER_VERSION_MINOR_LINE)
  unset(SDL3_MIXER_VERSION_PATCH_LINE)
  unset(SDL3_MIXER_VERSION_MAJOR)
  unset(SDL3_MIXER_VERSION_MINOR)
  unset(SDL3_MIXER_VERSION_PATCH)
endif()

set(SDL3_MIXER_LIBRARIES ${SDL3_MIXER_LIBRARY})
set(SDL3_MIXER_INCLUDE_DIRS ${SDL3_MIXER_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL3_mixer
                                  REQUIRED_VARS SDL3_MIXER_LIBRARIES SDL3_MIXER_INCLUDE_DIRS
                                  VERSION_VAR SDL3_MIXER_VERSION_STRING)

# for backward compatiblity
set(SDL3MIXER_LIBRARY ${SDL3_MIXER_LIBRARIES})
set(SDL3MIXER_INCLUDE_DIR ${SDL3_MIXER_INCLUDE_DIRS})
set(SDL3MIXER_FOUND ${SDL3_MIXER_FOUND})

mark_as_advanced(SDL3_MIXER_LIBRARY SDL3_MIXER_INCLUDE_DIR)
