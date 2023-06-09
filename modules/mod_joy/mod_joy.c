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
/* Thanks Sandman for suggest on openjoys at initialization time               */
/* --------------------------------------------------------------------------- */
/* Credits SplinterGU/Sandman 2007-2009                                        */
/* --------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --------------------------------------------------------------------------- */

#include "pxtdl.h"
#include "pxtrtm.h"

#include "libjoy.h"

/* --------------------------------------------------------------------------- */
/**
 * JOY_NUMBER()
 * JOY_NUMJOYSTICKS()
 * NUMBER_JOY()
 *
 * Returns the number of joysticks present in the system
 *
 **/

int modjoy_num(INSTANCE *my, int *params) {
    return (libjoy_num());
}

/* --------------------------------------------------------------------------- */
/**
 * JOY_NAME (int JOY)
 *
 * Returns the name for a given joystick present in the system
 *
 **/

int modjoy_name(INSTANCE *my, int *params) {
    return (libjoy_name(params[0]));
}

/* --------------------------------------------------------------------------- */
/**
 * JOY_SELECT (int JOY)
 * SELECT_JOY(int JOY)
 *
 * Returns the selected joystick number
 *
 **/

int modjoy_select(INSTANCE *my, int *params) {
    return (libjoy_select(params[0]));
}

/* --------------------------------------------------------------------------- */
/**
 * JOY_BUTTONS ()
 * JOY_NUMBUTTONS ()
 *
 * Returns the selected joystick total buttons
 *
 **/

int modjoy_buttons(INSTANCE *my, int *params) {
    return (libjoy_buttons());
}

/* --------------------------------------------------------------------------- */
/**
 * JOY_AXES ()
 * JOY_NUMAXES()
 *
 * Returns the selected joystick total axes
 *
 **/

int modjoy_axes(INSTANCE *my, int *params) {
    return (libjoy_axes());
}

/* --------------------------------------------------------------------------- */
/**
 * JOY_GETBUTTON (int button)
 * GET_JOY_BUTTON (int button)
 *
 * Returns the selected joystick state for the given button
 *
 **/

int modjoy_get_button(INSTANCE *my, int *params) {
    return (libjoy_get_button(params[0]));
}

/* --------------------------------------------------------------------------- */
/**
 * JOY_GETAXIS (int axis)
 * JOY_GETPOSITION (int axis)
 * GET_JOY_POSITION (int axis)
 *
 * Returns the selected joystick state for the given axis
 *
 **/

int modjoy_get_position(INSTANCE *my, int *params) {
    return (libjoy_get_position(params[0]));
}

/* --------------------------------------------------------------------------- */
/**
 * JOY_NUMHATS ()
 *
 * Returns the total number of POV hats of the current selected joystick
 *
 **/

int modjoy_hats(INSTANCE *my, int *params) {
    return (libjoy_hats());
}

/* --------------------------------------------------------------------------- */
/**
 * JOY_GETHAT (int HAT)
 *
 * Returns the state of the specfied hat on the current selected joystick
 *
 **/

int modjoy_get_hat(INSTANCE *my, int *params) {
    return (libjoy_get_hat(params[0]));
}

/* --------------------------------------------------------------------------- */

int modjoy_get_accel(INSTANCE *my, int *params) {
    return (libjoy_get_accel((int *)params[0], (int *)params[1], (int *)params[2]));
}

/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------- */
/**
 * JOY_BUTTONS (int JOY)
 * JOY_NUMBUTTONS (int JOY)
 *
 * Returns the selected joystick total buttons
 *
 **/

int modjoy_buttons_specific(INSTANCE *my, int *params) {
    return (libjoy_buttons_specific(params[0]));
}

/* --------------------------------------------------------------------------- */
/**
 * JOY_AXES (int JOY)
 * JOY_NUMAXES (int JOY)
 *
 * Returns the selected joystick total axes
 *
 **/

int modjoy_axes_specific(INSTANCE *my, int *params) {
    return (libjoy_axes_specific(params[0]));
}

/* --------------------------------------------------------------------------- */
/**
 * JOY_GETBUTTON (int JOY, int button)
 * GET_JOY_BUTTON (int JOY, int button)
 *
 * Returns the selected joystick state for the given button
 *
 **/

int modjoy_get_button_specific(INSTANCE *my, int *params) {
    return (libjoy_get_button_specific(params[0], params[1]));
}

/* --------------------------------------------------------------------------- */
/**
 * JOY_GETAXIS (int JOY, int axis)
 * JOY_GETPOSITION (int JOY, int axis)
 * GET_JOY_POSITION (int JOY, int axis)
 *
 * Returns the selected joystick state for the given axis
 *
 **/

int modjoy_get_position_specific(INSTANCE *my, int *params) {
    return (libjoy_get_position_specific(params[0], params[1]));
}

/* --------------------------------------------------------------------------- */
/* Added by Sandman */
/* --------------------------------------------------------------------------- */
/**
 * JOY_NUMHATS (int JOY)
 *
 * Returns the total number of POV hats of the specified joystick
 *
 **/

int modjoy_hats_specific(INSTANCE *my, int *params) {
    return (libjoy_hats_specific(params[0]));
}

/* --------------------------------------------------------------------------- */
/**
 * JOY_GETHAT (int JOY, int HAT)
 *
 * Returns the state of the specfied hat on the specified joystick
 *
 **/

int modjoy_get_hat_specific(INSTANCE *my, int *params) {
    return (libjoy_get_hat_specific(params[0], params[1]));
}

/* --------------------------------------------------------------------------- */

int modjoy_get_accel_specific(INSTANCE *my, int *params) {
    return (libjoy_get_accel_specific(params[0], (int *)params[1], (int *)params[2], (int *)params[3]));
}

/* ---------------------------------------------------------------------- */
/**
 * JOY_RUMBLE (int JOY, int low_frequency_rumble, int high_frequency_rumble, int duration_ms)
 *
 * Rumble the given joystick. Returns 0 on success, -1 otherwise
 *
 *  PARAMS:
 *      id of the controller, as returned by modgamecontroller_open
 *      intensity of the low frequency (left) rumble motor, from 0 to 255
 *      intensity of the high frequency (right) rumble motor, from 0 to 255
 *      duration of the rumble effect, in milliseconds
 *
 **/
int modjoy_rumble(INSTANCE *my, int *params) {
    return (libjoy_rumble(params[0], params[1], params[2], params[3]));
}

/* ---------------------------------------------------------------------- */