/*
 *  Copyright (C) 2014-2016 Joseba García Etxebarria <joseba.gar@gmail.com>
 *  Copyright (C) 2006-2012 SplinterGU (Fenix/Bennugd)
 *
 *  This file is part of PixTudio
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty. In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *     1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *
 *     2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *
 *     3. This notice may not be removed or altered from any source
 *     distribution.
 *
 */

#include "pxtdl.h"

#include <SDL3/SDL.h>

#ifndef __MONOLITHIC__
#include "libsdlhandler_symbols.h"
#endif

/* ----------------------------------------------------------------- */
/* Public functions                                                  */

void dump_new_events() {
    /* Remove all pendings events */

    /* We can't return -1, just return 0 (no event) on error */
    // We'll only discard events that no module knows how to handle here...
    // Otherwise some events seem to get discarded
	
    SDL_FlushEvents(SDL_EVENT_SYSWM, SDL_EVENT_SYSWM);
    SDL_FlushEvents(SDL_EVENT_TEXT_EDITING, SDL_EVENT_TEXT_INPUT);
    SDL_FlushEvents(SDL_EVENT_JOYSTICK_ADDED, SDL_EVENT_GAMEPAD_REMAPPED);
    SDL_FlushEvents(SDL_DOLLARGESTURE, SDL_EVENT_LAST);
	SDL_FlushEvents(SDL_EVENT_JOYSTICK_AXIS_MOTION,SDL_EVENT_JOYSTICK_REMOVED);
    SDL_FlushEvents(SDL_EVENT_GAMEPAD_AXIS_MOTION, SDL_EVENT_GAMEPAD_REMAPPED);
	
    /* Get new events */
    SDL_PumpEvents();
}

/* ----------------------------------------------------------------- */
