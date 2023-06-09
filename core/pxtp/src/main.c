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

/*
 * INCLUDES
 */

#ifdef _WIN32
#define _WIN32_WINNT 0x0500
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "pxtp.h"
#include "pxtrtm.h"
#include "xstrings.h"
#include "dirs.h"

#include <SDL3/SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

/* ---------------------------------------------------------------------- */

static char *dcb_exts[] = {".dcb", ".dat", ".bin", NULL};

static int standalone = 0; /* 1 only if this is an standalone interpreter (exe name: pxtp)  */
static int embedded   = 0; /* 1 only if this is a stub with an embedded DCB */

/* ---------------------------------------------------------------------- */

/*
 *  FUNCTION : main
 *
 *  Main function
 *
 *  PARAMS:
 *      INT n: ERROR LEVEL to return to OS
 *
 *  RETURN VALUE:
 *      No value
 *
 */
 
#ifdef __NINTENDO_SWITCH__

    #include "nintendo_switch_main.inc.c"
    
#else

int main(int argc, char *argv[]) {
    char *filename = NULL, dcbname[__MAX_PATH], *ptr;
    int i, j, ret  = -1;
    file *fp       = NULL;
    dcb_signature signature;
    
    /* get my executable name */
    ptr = argv[0] + strlen(argv[0]);
    while (ptr > argv[0] && ptr[-1] != '\\' && ptr[-1] != '/') {
        ptr--;
    }
    appexename = strdup(ptr);
    
    /* get executable full pathname  */
    appexefullpath = getfullpath(argv[0]);
    if ((!strchr(argv[0], '\\') && !strchr(argv[0], '/')) && !file_exists(appexefullpath)) {
        char *p = whereis(appexename);
        if (p) {
            char *tmp = calloc(1, strlen(p) + strlen(appexename) + 2);
            free(appexefullpath);
            sprintf(tmp, "%s/%s", p, appexename);
            appexefullpath = getfullpath(tmp);
            free(tmp);
        }
    }

    /* get pathname of executable */
    ptr        = strstr(appexefullpath, appexename);
    appexepath = calloc(1, ptr - appexefullpath + 1);
    strncpy(appexepath, appexefullpath, ptr - appexefullpath);

#ifdef _WIN32
    appname = calloc(1, strlen(appexename) - 3);
    strncpy(appname, appexename, strlen(appexename) - 4);
#else
    appname = strdup(appexename);
#endif

#ifndef FORCE_USE_MAIN_DCB
    standalone = (pxtrtm_strncmpi(appexename, "pxtp", 4) == 0);
#endif

    /* add binary path */
    file_addp(appexepath);

    if (!standalone) {
        /* Hand-made interpreter: search for DCB at EOF */
        fp = file_open(argv[0], "rb0");
        if (fp) {
            file_seek(fp, -(int)sizeof(signature), SEEK_END);
            file_read(fp, &signature, sizeof(signature));

            if (strcmp(signature.magic, DCB_STUB_MAGIC) == 0) {
                ARRANGE_DWORD(&signature.dcb_offset);
                embedded = 1;
            }
        }

        filename = appname;
    } else {
        /* Calling PXTP binary so we must get all command line params */
        for (i = 1; i < argc; i++) {
            if (argv[i][0] == '-') {
                j = 1;
                while (argv[i][j]) {
                    if (argv[i][j] == 'c') {
                        PXTRTM_LOG(PXTP_VERSION "\n\n"
                                   "PixTudio is OSS brought to you thanks to the work of many people\n"
                                   "Its main contributors are listed below:\n"
                                   "  Copyright (C) 2009-2016 Joseba García Etxebarria (PixTudio/BennuGD)\n"
                                   "  Copyright (C) 2006-2012 SplinterGU (Fenix/BennuGD)\n"
                                   "  Copyright (C) 2002-2006 Fenix Team (Fenix)\n"
                                   "  Copyright (C) 1999-2002 José Luis Cebrián Pagüe (Fenix)\n\n"
                                   "PixTudio comes with ABSOLUTELY NO WARRANTY\n\n"
                                   "This software is provided 'as-is', without any express or implied\n"
                                   "warranty. In no event will the authors be held liable for any damages\n"
                                   "arising from the use of this software.\n"
                                   "\n"
                                   "Permission is granted to anyone to use this software for any purpose,\n"
                                   "including commercial applications, and to alter it and redistribute it\n"
                                   "freely, subject to the following restrictions:\n"
                                   "\n"
                                   "   1. The origin of this software must not be misrepresented; you must not\n"
                                   "   claim that you wrote the original software. If you use this software\n"
                                   "   in a product, an acknowledgment in the product documentation would be\n"
                                   "   appreciated but is not required.\n"
                                   "\n"
                                   "   2. Altered source versions must be plainly marked as such, and must not be\n"
                                   "   misrepresented as being the original software.\n"
                                   "\n"
                                   "   3. This notice may not be removed or altered from any source\n"
                                   "   distribution.\n");
                        exit(0);
                    }

                    if (argv[i][j] == 'd') {
                        debug_DCB = 1;
                        debug = 1;
                    }

                    if (argv[i][j] == 'i') {
                        if (argv[i][j + 1] == 0) {
                            if (i == argc - 1) {
                                PXTRTM_LOGERROR("You must provide a directory");
                                exit(1);
                            }
                            file_addp(argv[i + 1]);
                            i++;
                            break;
                        }
                        file_addp(&argv[i][j + 1]);
                        break;
                    }
                    j++;
                }
            } else {
                if (!filename) {
                    filename = argv[i];
                    if (i < argc - 1)
                        memmove(&argv[i], &argv[i + 1], sizeof(char *) * (argc - i - 1));
                    argc--;
                    i--;
                }
            }
        }

        if (!filename) {
            PXTRTM_LOG(PXTP_VERSION "\n"
                       "Pixtudio comes with ABSOLUTELY NO WARRANTY\n"
                       "See COPYING for copyright details\n\n"
                       "Usage: %s [options] <data code block file>[.dcb]\n\n"
                       "   -c       Show credit information and quit\n"
                       "   -d       Activate DEBUG mode\n"
                       "   -i dir   Adds the directory to the PATH\n",
                       argv[0]);
            return -1;
        }
    }

    /* Initialization (modules needed before dcb_load) */

    string_init();
    init_c_type();
    
#ifdef FORCE_USE_MAIN_DCB
    filename = "main.dcb";
#endif

    /* Init application title for windowed modes */

    strcpy(dcbname, filename);

    if (appname && filename != appname) {
        free(appname);
        appname = strdup(filename);
    }

    if (!embedded) {
        /* First try to load directly (we expect myfile.dcb) */
        if (!dcb_load(dcbname)) {
            char **dcbext = dcb_exts;
            int dcbloaded = 0;

            while (dcbext && *dcbext) {
                strcpy(dcbname, filename);
                strcat(dcbname, *dcbext);
                if ((dcbloaded = dcb_load(dcbname)))
                    break;
                dcbext++;
            }

            if (!dcbloaded) {
                PXTRTM_LOGERROR("%s: doesn't exist or isn't version %d DCB compatible\n", filename,
                                DCB_VERSION >> 8);
                return -1;
            }
        }
    } else {
        dcb_load_from(fp, dcbname, signature.dcb_offset);
    }

    /* If the dcb is not in debug mode, deactivate it */
    if (dcb.data.NSourceFiles == 0) {
        debug_DCB = 0;
    }

    /* Initialization (modules needed after dcb_load) */

    sysproc_init();

#ifdef _WIN32
    HWND hWnd = /*GetForegroundWindow()*/ GetConsoleWindow();
    DWORD dwProcessId;
    GetWindowThreadProcessId(hWnd, &dwProcessId);
    if (dwProcessId == GetCurrentProcessId())
        ShowWindow(hWnd, SW_HIDE);
#endif

    argv[0] = filename;
    pxtrtm_entry(argc, argv);

    if (mainproc) {
        instance_new(mainproc, NULL);
        #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(instance_go_all, 25, 0);
        return 0;
        #else
        ret = instance_go_all();
        #endif
    }

    #ifdef __EMSCRIPTEN__
    pxtrtm_exit(0);
    #else
    pxtrtm_exit(ret);
    #endif

    free(appexename);
    free(appexepath);
    free(appexefullpath);
    free(appname);

    return ret;
}

#endif