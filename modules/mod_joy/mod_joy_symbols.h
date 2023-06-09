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

#ifndef __MODJOY_SYMBOLS_H
#define __MODJOY_SYMBOLS_H

#include <pxtdl.h>

#ifndef __PXTB__
extern int modjoy_axes( INSTANCE * my, int * params );
extern int modjoy_axes_specific( INSTANCE * my, int * params );
extern int modjoy_get_position( INSTANCE * my, int * params );
extern int modjoy_get_position_specific( INSTANCE * my, int * params );
extern int modjoy_buttons( INSTANCE * my, int * params );
extern int modjoy_buttons_specific( INSTANCE * my, int * params );
extern int modjoy_name( INSTANCE * my, int * params );
extern int modjoy_num( INSTANCE * my, int * params );
extern int modjoy_select( INSTANCE * my, int * params );
extern int modjoy_get_button( INSTANCE * my, int * params );
extern int modjoy_get_button_specific( INSTANCE * my, int * params );
extern int modjoy_hats( INSTANCE * my, int * params );
extern int modjoy_hats_specific( INSTANCE * my, int * params );
extern int modjoy_get_hat( INSTANCE * my, int * params );
extern int modjoy_get_hat_specific( INSTANCE * my, int * params );
extern int modjoy_get_accel( INSTANCE * my, int * params );
extern int modjoy_get_accel_specific( INSTANCE * my, int * params );
extern int modjoy_rumble( INSTANCE * my, int * params );
#endif

DLSYSFUNCS  __pxtexport( mod_joy, exported_functions )[] = {
    FUNC( "JOY_AXES"         , ""     , TYPE_INT    , modjoy_axes                  ),
    FUNC( "JOY_AXES"         , "I"    , TYPE_INT    , modjoy_axes_specific         ),
    FUNC( "JOY_NUM_AXES"     , ""     , TYPE_INT    , modjoy_axes                  ),
    FUNC( "JOY_NUM_AXES"     , "I"    , TYPE_INT    , modjoy_axes_specific         ),
    FUNC( "JOY_GET_AXIS"     , "I"    , TYPE_INT    , modjoy_get_position          ),
    FUNC( "JOY_GET_AXIS"     , "II"   , TYPE_INT    , modjoy_get_position_specific ),

    FUNC( "JOY_BUTTONS"      , ""     , TYPE_INT    , modjoy_buttons               ),
    FUNC( "JOY_BUTTONS"      , "I"    , TYPE_INT    , modjoy_buttons_specific      ),

    FUNC( "JOY_NAME"         , "I"    , TYPE_STRING , modjoy_name                  ),

    FUNC( "JOY_NUM_BUTTONS"  , ""     , TYPE_INT    , modjoy_buttons               ),
    FUNC( "JOY_NUM_BUTTONS"  , "I"    , TYPE_INT    , modjoy_buttons_specific      ),

    FUNC( "JOY_NUMBER"       , ""     , TYPE_INT    , modjoy_num                   ),

    FUNC( "JOY_SELECT"       , "I"    , TYPE_INT    , modjoy_select                ),

    FUNC( "JOY_GET_BUTTON"   , "I"    , TYPE_INT    , modjoy_get_button            ),
    FUNC( "JOY_GET_BUTTON"   , "II"   , TYPE_INT    , modjoy_get_button_specific   ),
    FUNC( "JOY_GET_POSITION" , "I"    , TYPE_INT    , modjoy_get_position          ),
    FUNC( "JOY_GET_POSITION" , "II"   , TYPE_INT    , modjoy_get_position_specific ),

    FUNC( "JOY_NUM_HATS"     , ""     , TYPE_INT    , modjoy_hats                  ),
    FUNC( "JOY_NUM_HATS"     , "I"    , TYPE_INT    , modjoy_hats_specific         ),   /* Added by Sandman */
    FUNC( "JOY_GET_HAT"      , "I"    , TYPE_INT    , modjoy_get_hat               ),
    FUNC( "JOY_GET_HAT"      , "II"   , TYPE_INT    , modjoy_get_hat_specific      ),   /* Added by Sandman */

    FUNC( "JOY_GET_ACCEL"    , "PPP"  , TYPE_INT    , modjoy_get_accel             ),
    FUNC( "JOY_GET_ACCEL"    , "IPPP" , TYPE_INT    , modjoy_get_accel_specific    ),

    FUNC( "JOY_RUMBLE"       , "IIII" , TYPE_INT    , modjoy_rumble                ),

    FUNC( 0                  , 0      , 0           , 0                            )
};

char * __pxtexport( mod_joy, module_dependencies )[] =
{
    "libjoy",
    NULL
};

#endif
