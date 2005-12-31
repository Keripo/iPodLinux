/*
 * vstars
 *
 *   contains all of the starfield stuff
 *
 *   for now, it just draws a static starfield, but we might do more later
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
 */

#include "vstars.h"

static int motion = STAR_MOTION_STATIC;		/* default motion */

#define NUM_STARS	(32)

vstar stars[NUM_STARS];

void Star_SetStyle( int kind )
{
	motion = kind;
}

static void Star_bang( int which )
{
	/* start position */
	stars[which].x = (double)Vortex_Rand( vglob.usableW );
	stars[which].y = (double)Vortex_Rand( vglob.usableH );

	/* acceleration */
	stars[which].xa = stars[which].ya = 0;
	stars[which].xv = stars[which].yv = 0;

	/* velocity */
	if( motion == STAR_MOTION_RANDOM ) {
		stars[which].xv = ((double)(rand()&0x0ff))/255.0 - 0.5;
		stars[which].yv = ((double)(rand()&0x0ff))/255.0 - 0.5;
	}

	/* color and size */
	stars[which].c = ttk_makecol( 120 + (rand() & 0x7f),
				      120 + (rand() & 0x7f),
				      120 + (rand() & 0x7f) );
	stars[which].s = rand() & 0x0ff;
}

void Star_GenerateStars( void )
{       
        int p;
        for( p=0 ; p<NUM_STARS ; p++ ) Star_bang( p );
}

void Star_DrawStars( ttk_surface srf )
{       
        int p;
	int x,y;
        for( p=0 ; p<NUM_STARS ; p++ )
        {       
		x = (int) stars[p].x;
		y = (int) stars[p].y;

                ttk_pixel( srf, x, y, stars[p].c );
		if( stars[p].s < 32 ) {
		    /* 1/8 chance it'll be a larger square star */
		    ttk_pixel( srf, x+1, y+0, stars[p].c );
		    ttk_pixel( srf, x+1, y+1, stars[p].c );
		    ttk_pixel( srf, x+0, y+1, stars[p].c );
		} else if (stars[p].s < 48)  {
		    /* 1/16 chance it'll be a large t-shaped star */
		    ttk_pixel( srf, x+1, y+0, stars[p].c );
		    ttk_pixel( srf, x-1, y-0, stars[p].c );
		    ttk_pixel( srf, x+0, y+1, stars[p].c );
		    ttk_pixel( srf, x-0, y-1, stars[p].c );
		}
        }
}

void Star_Poll( void )
{
	int p;
	for( p=0 ; p<NUM_STARS ; p++ )
	{
		/* accelerate the star */
		stars[p].xv += stars[p].xa;
		stars[p].yv += stars[p].ya;

		/* move the star */
		stars[p].x += stars[p].xv;
		stars[p].y += stars[p].yv;

		/* regen star if it's offscreen */
		if(   (stars[p].x > vglob.usableW)
		   || (stars[p].x < 0)
		   || (stars[p].y > vglob.usableH)
		   || (stars[p].y < 0))
        		Star_bang( p );
	}
}
