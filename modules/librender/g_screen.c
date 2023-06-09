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

#include <stdlib.h>
#include <string.h>

#define __LIB_RENDER
#include "librender.h"

/* --------------------------------------------------------------------------- */

/* Not used anymore */
// static int updaterects_count = 0;
// static REGION updaterects[DIRTYCOLS * DIRTYROWS];

/* --------------------------------------------------------------------------- */
/*
 *  FUNCTION : gr_draw_screen
 *
 *  Draw the current screen, using the given restore_type / dump_type parameters
 *
 *  PARAMS :
 *      dest            Destination graphic (MUST have a correct size)
 *
 *      restore_type
 *          -1          No background restore
 *           0          Partial (old process bounding box) background restore
 *           1          Full background restore
 *
 *      dump_type
 *           0          Partial (new process bounding box) drawing
 *           1          Full drawing
 *
 *  RETURN VALUE :
 *      None
 */

void gr_draw_screen(GRAPH *dest, int restore_type, int dump_type) {
    int x, y, scalex, scaley;
    
    /* Update the object list */
    gr_update_objects_mark_rects(restore_type, dump_type);
    
    scalex = 100 + GLOINT32(librender, SCREENOFFSETSIZEX);
    scaley = 100 + GLOINT32(librender, SCREENOFFSETSIZEY);
    x = ((int) background->width / 2) - ((((int) background->width / 2) - GLOINT32(librender, SCREENOFFSETX)) * scalex / 100);
    y = ((int) background->height / 2) - ((((int) background->height / 2) - GLOINT32(librender, SCREENOFFSETY)) * scaley / 100);
    
    /* Blit the background map */
    //gr_blit(scrbitmap, NULL, GLOINT32(librender, SCREENOFFSETX), GLOINT32(librender, SCREENOFFSETY), B_NOCOLORKEY, 255, 255, 255, background, 0);
    gr_rotated_blit(scrbitmap, NULL, x, y, B_NOCOLORKEY, 0, scalex, scaley,	255, 255, 255, background, 0);
    
    /* Dump everything */
    gr_draw_objects_complete();
}

/* --------------------------------------------------------------------------- */

static int screen_locked = 0;

int gr_lock_screen() {
    if (screen_locked)
        return 1;

    screen_locked = 1;

    if (!scrbitmap || !(scrbitmap->info_flags & GI_EXTERNAL_DATA)) {
        if (scrbitmap)
            bitmap_destroy(scrbitmap);
        scrbitmap = bitmap_new_ex(0, screen->w, screen->h, screen->format->BitsPerPixel,
                                  screen->pixels, screen->pitch);
        bitmap_add_cpoint(scrbitmap, 0, 0);
    }

    SDL_RenderClear(renderer);

    return 1;
}

/* --------------------------------------------------------------------------- */

void gr_unlock_screen() {
    if (!screen_locked || !screen->pixels)
        return;

    screen_locked = 0;

    SDL_SetRenderClipRect(renderer, NULL);
    SDL_RenderPresent(renderer);
}

/* --------------------------------------------------------------------------- */
