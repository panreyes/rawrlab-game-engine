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

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xctype.h"

int dos_chars = 0;

/* CP850 to ISO8859-1 character conversion table */
unsigned char cp850_to_iso88591[256] = {
    0,   1,   2,   3,   4,   5,   6,   7,   8,   9,       // 0-9
    10,  11,  12,  13,  14,  15,  16,  17,  18,  19,      // 10-19
    20,  21,  22,  23,  24,  25,  26,  27,  28,  29,      // 20-29
    30,  31,  32,  33,  34,  35,  36,  37,  38,  39,      // 30-39
    40,  41,  42,  43,  44,  45,  46,  47,  48,  49,      // 40-49
    50,  51,  52,  53,  54,  55,  56,  57,  58,  59,      // 50-59
    60,  61,  62,  63,  64,  65,  66,  67,  68,  69,      // 60-69
    70,  71,  72,  73,  74,  75,  76,  77,  78,  79,      // 70-79
    80,  81,  82,  83,  84,  85,  86,  87,  88,  89,      // 80-89
    90,  91,  92,  93,  94,  95,  96,  97,  98,  99,      // 90-99
    100, 101, 102, 103, 104, 105, 106, 107, 108, 109,     // 100-109
    110, 111, 112, 113, 114, 115, 116, 117, 118, 119,     // 110-119
    120, 121, 122, 123, 124, 125, 126, 127, 199, 252,     // 120-129
    233, 226, 228, 224, 229, 231, 234, 235, 232, 239,     // 130-139
    238, 236, 196, 197, 201, 230, 198, 244, 246, 242,     // 140-149
    251, 249, 255, 214, 220, 248, 163, 216, 215, 131,     // 150-159
    225, 237, 243, 250, 241, 209, 170, 186, 191, 174,     // 160-169
    172, 189, 188, 161, 171, 187, 166, 166, 166, 166,     // 170-179
    166, 193, 194, 192, 169, 166, 166, 43,  43,  162,     // 180-189
    165, 43,  43,  45,  45,  43,  45,  43,  227, 195,     // 190-199
    43,  43,  45,  45,  166, 45,  43,  164, 240, 208,     // 200-209
    202, 203, 200, 105, 205, 206, 207, 43,  43,  166,     // 210-219
    95,  166, 204, 175, 211, 223, 212, 210, 245, 213,     // 220-229
    181, 254, 222, 218, 219, 217, 253, 221, 175, 180,     // 230-239
    173, 177, 61,  190, 182, 167, 247, 184, 176, 168,     // 240-249
    183, 185, 179, 178, 166, 160};                        // 250-255

/* ISO 8859-1 to CP850 character conversion table */
unsigned char iso88591_to_cp850[256] = {
    0,   1,   2,   3,   4,   5,   6,   7,   8,   9,        // 0-9
    10,  11,  12,  13,  14,  15,  16,  17,  18,  19,       // 10-19
    20,  21,  22,  23,  24,  25,  26,  27,  28,  29,       // 20-29
    30,  31,  32,  33,  34,  35,  36,  37,  38,  39,       // 30-39
    40,  41,  42,  43,  44,  45,  46,  47,  48,  49,       // 40-49
    50,  51,  52,  53,  54,  55,  56,  57,  58,  59,       // 50-59
    60,  61,  62,  63,  64,  65,  66,  67,  68,  69,       // 60-69
    70,  71,  72,  73,  74,  75,  76,  77,  78,  79,       // 70-79
    80,  81,  82,  83,  84,  85,  86,  87,  88,  89,       // 80-89
    90,  91,  92,  93,  94,  95,  96,  97,  98,  99,       // 90-99
    100, 101, 102, 103, 104, 105, 106, 107, 108, 109,      // 100-109
    110, 111, 112, 113, 114, 115, 116, 117, 118, 119,      // 110-119
    120, 121, 122, 123, 124, 125, 126, 127, 128, 129,      // 120-129
    130, 159, 132, 133, 134, 135, 136, 137, 138, 139,      // 130-139
    140, 141, 142, 143, 144, 145, 146, 147, 148, 149,      // 140-149
    150, 151, 152, 153, 154, 155, 156, 157, 158, 159,      // 150-159
    255, 173, 189, 156, 207, 190, 254, 245, 249, 184,      // 160-169
    166, 174, 170, 240, 169, 238, 248, 241, 253, 252,      // 170-179
    239, 230, 244, 250, 247, 251, 167, 175, 172, 171,      // 180-189
    243, 168, 183, 181, 182, 199, 142, 143, 146, 128,      // 190-199
    212, 144, 210, 211, 222, 214, 215, 216, 209, 165,      // 200-209
    227, 224, 226, 229, 153, 158, 157, 235, 233, 234,      // 210-219
    154, 237, 232, 225, 133, 160, 131, 198, 132, 134,      // 220-229
    145, 135, 138, 130, 136, 137, 141, 161, 140, 139,      // 230-239
    208, 164, 149, 162, 147, 228, 148, 246, 155, 151,      // 240-249
    163, 150, 129, 236, 231, 152};                         // 250-255

/*
 * Convert character code to glyph index
 * PixTudio uses DOS-Latin-1 (CP850) codes internally,
 * If we want to convert those to UTF-8 code, we need a
 * correspondance table.
 * Wikipedia has a list of unicode character codes here:
 * https://en.wikipedia.org/wiki/List_of_Unicode_characters
 * (We want the "Decimal" column)
 * Microsoft has a document on the CP850 charset at:
 * https://msdn.microsoft.com/en-us/library/cc195064.aspx
 */	  
uint16_t cp850_to_utf8[256] = {
    0,    1,    2,    3,    4,    5,    6,    7,    8,    9,    // 0-9
    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,   // 10-19
    20,   21,   22,   23,   24,   25,   26,   27,   28,   29,   // 20-29
    30,   31,   32,   33,   34,   35,   36,   37,   38,   39,   // 30-39
    40,   41,   42,   43,   44,   45,   46,   47,   48,   49,   // 40-49
    50,   51,   52,   53,   54,   55,   56,   57,   58,   59,   // 50-59
    60,   61,   62,   63,   64,   65,   66,   67,   68,   69,   // 60-69
    70,   71,   72,   73,   74,   75,   76,   77,   78,   79,   // 70-79
    80,   81,   82,   83,   84,   85,   86,   87,   88,   89,   // 80-89
    90,   91,   92,   93,   94,   95,   96,   97,   98,   99,   // 90-99
    100,  101,  102,  103,  104,  105,  106,  107,  108,  109,  // 100-109
    110,  111,  112,  113,  114,  115,  116,  117,  118,  119,  // 110-119
    120,  121,  122,  123,  124,  125,  126,  169,  199,  252,  // 120-129
    233,  226,  228,  224,  229,  231,  234,  235,  232,  239,  // 130-139
    238,  236,  196,  197,  201,  198,  198,  212,  214,  210,  // 140-149
    219,  217,  255,  214,  220,  216,  163,  216,  215,  401,  // 150-159
    225,  237,  243,  250,  241,  209,  65,   79,   191,  174,  // 160-169
    172,  189,  188,  161,  171,  187,  9617, 9618, 9619, 9474, // 170-179
    9508, 193,  194,  192,  169,  9571, 9553, 9559, 9565, 162,  // 180-189
    165,  9488, 9492, 9524, 9516, 9500, 9472, 9532, 195,  195,  // 190-199
    9562, 9556, 9577, 9574, 9568, 9552, 9580, 164,  208,  208,  // 200-209
    234,  203,  200,  305,  205,  206,  207,  9496, 9484, 9608, // 210-219
    9604, 166,  204,  9600, 211,  223,  212,  210,  213,  213,  // 220-229
    181,  222,  222,  218,  219,  217,  221,  221,  175,  180,   // 230-239
    173,  177,  906,  190,  182,  167,  247,  184,  176,  168,   // 240-249
    183,  185,  179,  178,  9632, 160};                          // 250-255

/* Tipos de caracter */

char c_type[256];
unsigned char c_upper[256];
unsigned char c_lower[256];

int c_type_initialized = 0;

unsigned char convert(unsigned char c) {
    return dos_chars ? c : iso88591_to_cp850[c];
}

static void set_c_range(int first, int last, int type) {
    while (first <= last) {
        c_type[first++] |= type;
    }
}

static void set_c_from(const unsigned char *chars, int type) {
    if (dos_chars) {
        while (*chars) {
            c_type[iso88591_to_cp850[*chars++]] |= type;
        }
    } else {
        while (*chars) {
            c_type[*chars++] |= type;
        }
    }
}

static void set_c_as(int prev_type, int type) {
    int n;

    for (n = 0; n < 256; n++) {
        if (c_type[n] & prev_type) {
            c_type[n] |= type;
        }
    }
}

static void set_c_upper(const unsigned char *from, const unsigned char *to) {
    if (dos_chars) {
        while (*from) {
            c_upper[iso88591_to_cp850[*from++]] = iso88591_to_cp850[*to++];
        }
    } else {
        while (*from) {
            c_upper[*from++] = *to++;
        }
    }
}

static void set_c_lower(const unsigned char *from, const unsigned char *to) {
    if (dos_chars) {
        while (*from) {
            c_lower[iso88591_to_cp850[*from++]] = iso88591_to_cp850[*to++];
        }
    } else {
        while (*from) {
            c_lower[*from++] = *to++;
        }
    }
}

void init_c_type() {
    uint32_t c;

    memset(c_type, 0, sizeof(c_type));

    if (dos_chars) {
        for (c = 0; c < 256; c++) {
            c_lower[c] = c_upper[c] = iso88591_to_cp850[c];
        }
    } else {
        for (c = 0; c < 256; c++) {
            c_lower[c] = c_upper[c] = (unsigned char)c;
        }
    }

    set_c_upper((const unsigned char *)"abcdefghijklmnopqrstuvwxyz",
                (const unsigned char *)"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    set_c_lower((const unsigned char *)"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
                (const unsigned char *)"abcdefghijklmnopqrstuvwxyz");
#ifdef RESPETAR_ACENTOS
    set_c_upper((const unsigned char *)"áéíóúñçàèìòùäëïöüýâêîôûæãåõ",
                (const unsigned char *)"ÁÉÍÓÚÑÇÀÈÌÒÙÄËÏÖÜÝÂÊÎÔÛÆÃÅÕ");
    set_c_lower((const unsigned char *)"ÁÉÍÓÚÑÇÀÈÌÒÙÄËÏÖÜÝÂÊÎÔÛÆÃÅÕ",
                (const unsigned char *)"áéíóúñçàèìòùäëïöüýâêîôûæãåõ");
#else
    set_c_upper((const unsigned char *)"áéíóúñÑçÇàèìòùäëïöüýâêîôûæãåõÁÉÍÓÚ",
                (const unsigned char *)"AEIOUNNCCAEIOUAEIOUYAEIOUÆAAOAEIOU");
    set_c_lower((const unsigned char *)"áéíóúñÑçÇàèìòùäëïöüýâêîôûæãåõÁÉÍÓÚ",
                (const unsigned char *)"aeiounnccaeiouaeiouyaeiouÆaaoaeiou");
#endif

    set_c_from((const unsigned char *)" \t\n\r", CTYPE_SPACE);

    set_c_range('0', '9', CTYPE_NUM);

    set_c_range('0', '9', CTYPE_ALNUM);
    set_c_range('A', 'F', CTYPE_ALNUM);
    set_c_range('a', 'f', CTYPE_ALNUM);

    set_c_range('A', 'Z', CTYPE_ALPHA);
    set_c_range('a', 'z', CTYPE_ALPHA);
    set_c_from((const unsigned char *)"áéíóúÁÉÍÓÚñÑçÇàèìòùÀÈÌÒÙäëïöüÄËÏÖÜÿýâêîôûÂÊÎÔÛ"
                                      "æÆãåðõªºÃÅÐÕØ",
               CTYPE_ALPHA);

    set_c_as(CTYPE_ALPHA, CTYPE_WORDCHAR);
    set_c_from((const unsigned char *)"_", CTYPE_WORDCHAR);
    set_c_as(CTYPE_WORDCHAR, CTYPE_WORDFIRST);

    set_c_range('0', '9', CTYPE_WORDCHAR);

    c_type_initialized = 1;
}
