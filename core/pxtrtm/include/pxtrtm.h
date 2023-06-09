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

#pragma once

#include <stdint.h>

#include <commons_defs.h>

#include "arrange.h"
#include "i_procdef.h"
#include "files.h"
#include "dcb.h"
#include "xctype.h"
#include "instance.h"

/* --------------------------------------------------------------------------- */

#ifdef __NINTENDO_SWITCH__
    #include <SDL3/SDL_log.h>
    
    #define PXTRTM_LOG(...) SDL_Log(__VA_ARGS__)
    #define PXTRTM_LOGERROR(...) SDL_Log(__VA_ARGS__)
#else
    #ifdef __ANDROID__
        #include <SDL3/SDL_log.h>

        #define PXTRTM_LOG(...) SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, __VA_ARGS__)
        #define PXTRTM_LOGERROR(...) SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, __VA_ARGS__)
    #else
        #define PXTRTM_LOG(...) fprintf(stdout, __VA_ARGS__)
        #define PXTRTM_LOGERROR(...) fprintf(stderr, __VA_ARGS__)
    #endif 
#endif

/* --------------------------------------------------------------------------- */

extern void *globaldata;
extern void *localdata;
extern int local_size;
extern int *localstr;
extern int local_strings;

extern PROCDEF *procs;
extern PROCDEF *mainproc;
extern int procdef_count;

extern char *appname;
extern char *appexename;
extern char *appexepath;
extern char *appexefullpath;

extern int debug_DCB;  /* 1 if running in debug mode to dump DCB output */
extern int debug;      /* 1 if the user set the debug arg (-d) on PXTP */

/* Trace */
extern int debug_mode;

extern int exit_value;
extern int must_exit;

extern int force_debug;
extern int debug_next;

extern int trace_sentence;
extern INSTANCE *trace_instance;

/* --------------------------------------------------------------------------- */
extern int pxtrtm_strncmpi(char *str1, char *str2, int sz);

extern int dcb_load(const char *filename);
extern int dcb_load_from(file *fp, const char *dcbname, int offset);

extern char *getid_name(unsigned int code);

extern void mnemonic_dump(int i, int param);

/* --------------------------------------------------------------------------- */

extern void pxtrtm_entry(int argc, char *argv[]);
extern void pxtrtm_exit(int exit_code);

/* --------------------------------------------------------------------------- */

