/*
 * Vortex - A Tempest-like game
 * Copyright (C) 2005 Scott Lawrence
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 *  $Id: $
 *
 *  $Log: $
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "../pz.h"
#include "levels.h"

extern void Vortex_resetGlobals( void );

/* colors */

#ifdef DARKBG
#define	VORTEX_COLOR_BG		BLACK
#define VORTEX_COLOR_SCORE	WHITE
#define VORTEX_COLOR_WEBFRONT	WHITE
#define VORTEX_COLOR_WEBARM	LTGRAY
#define VORTEX_COLOR_WEBREAR	GRAY
#else
#define	VORTEX_COLOR_BG		WHITE
#define VORTEX_COLOR_SCORE	BLACK
#define VORTEX_COLOR_WEBFRONT	BLACK
#define VORTEX_COLOR_WEBARM	GRAY
#define VORTEX_COLOR_WEBREAR	LTGRAY
#endif

#define VORTEX_STATE_PLAY (1)
#define VORTEX_STATE_EXIT (2)

typedef struct {
	/* window stuff */
	GR_TIMER_ID	timer_id;
	    /* main window */
	GR_WINDOW_ID	display_wid;	/* this gets copied to the screen */
	GR_WINDOW_ID	wid;		/* this gets drawn to by the app */
	GR_GC_ID	gc;
	    /* top window */
	GR_WINDOW_ID	twid;
	GR_GC_ID	tgc;
	GR_SCREEN_INFO	screen_info;

	/* helpers */
	int width;
	int height;

	/* game control stuff */
	int gameState;
	int currentLevel;
	int lives;
	int score;
	int superzapper;

	int minx, maxx, miny, maxy;
	float xscale;
	int xskew;
	int xoffs;
	int xcenter;
	float yscale;
	int yskew;
	int yoffs;
	int ycenter;

	LEVELDATA * ld;
} VORTEX_GLOBALS;

extern VORTEX_GLOBALS Vortex_globals;

/* these should be somewhere common... */
#define MIN(A,B) (((A)>(B))?(B):(A))
#define MAX(A,B) (((A)<(B))?(B):(A))

