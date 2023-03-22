/*
 *  Copyright (C) 2014-2016 Joseba García Etxebarria <joseba.gar@gmail.com>
 *  Copyright (C) 2006-2012 SplinterGU (Fenix/Bennugd)
 *  Copyright (C) 2002-2006 Fenix Team (Fenix)
 *  Copyright (C) 1999-2002 José Luis Cebrián Pagüe (Fenix)
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

/* --------------------------------------------------------------------------- */

#include <SDL3/SDL.h>

#define __LIB_RENDER
#include <g_video.h>
#include <librender.h>

#include "pxtrtm.h"

#include "pxtdl.h"
#include "dlvaracc.h"

#ifndef __MONOLITHIC__
#include "libwm_symbols.h"
#else
extern DLVARFIXUP __pxtexport(libwm, globals_fixup)[];
#endif

/* --------------------------------------------------------------------------- */

#define EXIT_STATUS 0
#define WINDOW_STATUS 1
#define FOCUS_STATUS 2
#define MOUSE_STATUS 3

/* --------------------------------------------------------------------------- */
/* Gestión de eventos de ventana                                               */
/* --------------------------------------------------------------------------- */

/*
 *  FUNCTION : wm_events
 *
 *  Process all pending wm SDL events, updating all global variables
 *
 *  PARAMS :
 *      None
 *
 *  RETURN VALUE :
 *      None
 */

void wm_events() {
    SDL_Event e;

    /* Procesa los eventos de ventana pendientes */

    GLODWORD(libwm, EXIT_STATUS) = 0;

    /* Handle the plethora of events different systems can produce here */
    while (SDL_PeepEvents(&e, 1, SDL_GETEVENT, SDL_EVENT_QUIT, SDL_EVENT_WINDOW_LAST) > 0) {
        switch (e.type) {
            case SDL_EVENT_QUIT:
                /* UPDATE  exit status... initilized each frame */
                GLODWORD(libwm, EXIT_STATUS) = 1;
                break;
            case SDL_EVENT_WINDOW_FIRST ... SDL_EVENT_WINDOW_LAST:
				switch (e.window.type) {
                    case SDL_EVENT_WINDOW_MINIMIZED:
                        GLODWORD(libwm, WINDOW_STATUS) = 0;
                        break;
                    case SDL_EVENT_WINDOW_RESTORED:
                        // TODO: Is this necessary anymore?
                        gr_set_mode(screen->w, screen->h);
                        GLODWORD(libwm, WINDOW_STATUS) = 1;
                        break;
                    case SDL_EVENT_WINDOW_MOUSE_ENTER:
                        GLODWORD(libwm, MOUSE_STATUS) = 1;
                        break;
                    case SDL_EVENT_WINDOW_MOUSE_LEAVE:
                        GLODWORD(libwm, MOUSE_STATUS) = 0;
                        break;
                    case SDL_EVENT_WINDOW_HIDDEN:
                        GLODWORD(libwm, WINDOW_STATUS) = 0;
                        break;
                    case SDL_EVENT_WINDOW_SHOWN:
                        GLODWORD(libwm, WINDOW_STATUS) = 1;
                        break;
                    case SDL_EVENT_WINDOW_FOCUS_LOST:
                        GLODWORD(libwm, FOCUS_STATUS) = 0;
                        break;
                    case SDL_EVENT_WINDOW_FOCUS_GAINED:
                        GLODWORD(libwm, FOCUS_STATUS) = 1;
                        break;
                }

            case SDL_EVENT_SYSWM:
                break;
        }
    }
}

/* --------------------------------------------------------------------------- */
