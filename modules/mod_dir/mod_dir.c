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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "dirs.h"

/* WIN32 INCLUDES */
#ifdef WIN32
#include <windows.h>
#include <winbase.h>
#include <windef.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#include <glob.h>
#endif

// I need this for prefpath and basepath
#include <SDL3/SDL_filesystem.h>

#include "pxtdl.h"
#include "dlvaracc.h"
#include "files.h"
#include "xstrings.h"

#ifndef __MONOLITHIC__
#include "mod_dir_symbols.h"
#else
extern DLVARFIXUP __pxtexport(mod_dir, globals_fixup)[];
#endif

/* ----------------------------------------------------------------- */

enum {
    FILE_PATH = 0,
    FILE_NAME,
    FILE_DIRECTORY,
    FILE_HIDDEN,
    FILE_READONLY,
    FILE_SIZE,
    FILE_CREATED,
    FILE_MODIFIED,
    FILE_ACCESSED,
    FILE_STATECHG
};

/* ----------------------------------------------------------------- */
/* DIRECTORY FUNCTIONS */

int moddir_cd(INSTANCE *my, int *params) {
    char *d = dir_current();
    int r = string_new(d);
    string_use(r);
    if (d)
        free(d);
    return r;
}

int moddir_chdir(INSTANCE *my, int *params) {
    const char *d = string_get(params[0]);
    int ret = dir_change(d);
    string_discard(params[0]);
    return (ret);
}

int moddir_mkdir(INSTANCE *my, int *params) {
    const char *d = string_get(params[0]);
    int ret = dir_create(d);
    string_discard(params[0]);
    return (ret);
}

int moddir_rmdir(INSTANCE *my, int *params) {
    const char *d = string_get(params[0]);
    int ret = dir_delete(d);
    string_discard(params[0]);
    return (ret);
}

int moddir_rm(INSTANCE *my, int *params) {
    const char *d = string_get(params[0]);
    int ret = dir_deletefile(d);
    string_discard(params[0]);
    return (ret);
}

static int __moddir_read(__DIR_ST *dh) {
    __DIR_FILEINFO_ST *dif;
    char buffer[20];
    int result;

    dif = dir_read(dh);
    if (!dif) {
        result = string_new("");
        string_use(result);
        return (result);
    }

    /* discard previous strings values */
    string_discard(GLODWORD(mod_dir, FILE_NAME));
    string_discard(GLODWORD(mod_dir, FILE_PATH));
    string_discard(GLODWORD(mod_dir, FILE_CREATED));
    string_discard(GLODWORD(mod_dir, FILE_MODIFIED));
    string_discard(GLODWORD(mod_dir, FILE_ACCESSED));
    string_discard(GLODWORD(mod_dir, FILE_STATECHG));

    GLODWORD(mod_dir, FILE_NAME) = string_new(dif->filename);
    string_use(GLODWORD(mod_dir, FILE_NAME));
    GLODWORD(mod_dir, FILE_PATH) = string_new(dif->fullpath);
    string_use(GLODWORD(mod_dir, FILE_PATH));

    GLODWORD(mod_dir, FILE_DIRECTORY) = dif->attributes & DIR_FI_ATTR_DIRECTORY ? 1 : 0;
    GLODWORD(mod_dir, FILE_HIDDEN) = dif->attributes & DIR_FI_ATTR_HIDDEN ? 1 : 0;
    GLODWORD(mod_dir, FILE_READONLY) = dif->attributes & DIR_FI_ATTR_READONLY ? 1 : 0;
    GLODWORD(mod_dir, FILE_SIZE) = dif->size;

/* Store file times */
#ifdef _WIN32
    strftime(buffer, 20, "%d/%m/%Y %H:%M:S", &dif->mtime);
    GLODWORD(mod_dir, FILE_CREATED) = string_new(buffer);
    string_use(GLODWORD(mod_dir, FILE_CREATED));
#else
    GLODWORD(mod_dir, FILE_CREATED) = string_new("");
    string_use(GLODWORD(mod_dir, FILE_CREATED));
#endif

    strftime(buffer, 20, "%d/%m/%Y %H:%M:S", &dif->crtime);
    GLODWORD(mod_dir, FILE_MODIFIED) = string_new(buffer);
    string_use(GLODWORD(mod_dir, FILE_MODIFIED));

    strftime(buffer, 20, "%d/%m/%Y %H:%M:S", &dif->atime);
    GLODWORD(mod_dir, FILE_ACCESSED) = string_new(buffer);
    string_use(GLODWORD(mod_dir, FILE_ACCESSED));

#ifndef _WIN32
    strftime(buffer, 20, "%d/%m/%Y %H:%M:S", &dif->ctime);
    GLODWORD(mod_dir, FILE_STATECHG) = string_new(buffer);
    string_use(GLODWORD(mod_dir, FILE_STATECHG));
#else
    GLODWORD(mod_dir, FILE_STATECHG) = string_new("");
    string_use(GLODWORD(mod_dir, FILE_STATECHG));
#endif

    /* Return */
    result = GLODWORD(mod_dir, FILE_NAME);
    string_use(result);
    return result;
}

/*  string GLOB (STRING path)
 *
 *  Given a path with wildcards ('*' or '?' characters), returns the first
 *  file that matches and, in every next call, all matching files found
 *  until no more files exists. It then returns NIL.
 */

int moddir_glob(INSTANCE *my, int *params) {
    const char *path    = string_get(params[0]);
    static __DIR_ST *dh = NULL;
    int result;

    if (dh && strcmp(dh->path, path)) {
        dir_close(dh);
        dh = NULL;
    }

    if (!dh)
        dh = dir_open(path);

    string_discard(params[0]);

    if (!dh) {
        result = string_new("");
        string_use(result);
        return (result);
    }

    return (__moddir_read(dh));
}

/*  int DIROPEN (STRING path)
 *
 *  Open a dir for read it, returns handle id.
 *  return 0 if fail.
 */

int moddir_open(INSTANCE *my, int *params) {
    int result = (int)dir_open(string_get(params[0]));
    string_discard(params[0]);
    return result;
}

/*  int DIRCLOSE (INT handle)
 */

int moddir_close(INSTANCE *my, int *params) {
    if (params[0])
        dir_close((__DIR_ST *)params[0]);
    return 1;
}

/*  string DIRREAD (INT handle)
 *
 *  Given a path with wildcards ('*' or '?' characters), returns the first
 *  file that matches and, in every next call, all matching files found
 *  until no more files exists. It then returns NIL.
 */

int moddir_read(INSTANCE *my, int *params) {
    return (__moddir_read((__DIR_ST *)params[0]));
}

/*  string
 *
 */
int moddir_get_basepath(INSTANCE *my, int *params) {
    int code;
    char *path = SDL_GetBasePath();
    if(! path) {
        code = string_new("");
    } else {
        code = string_new(path);
        SDL_free(path);
    }
    string_use(code);

    return code;
}

int moddir_get_prefpath(INSTANCE *my, int *params) {
    int code;
    char *path = SDL_GetPrefPath(string_get(params[0]), string_get(params[1]));
    if(! path) {
        code = string_new("");
    } else {
        code = string_new(path);
        SDL_free(path);
    }
    string_use(code);

    string_discard(params[0]);
    string_discard(params[1]);

    return code;
}

/* ---------------------------------------------------------------------- */
