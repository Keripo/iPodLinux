/*** The stuff in this file needs to be updated! ***/

/*
 * Copyright (c) 2005, James Jacobsson
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
 * Neither the name of the organization nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior
 * written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdio.h>
#include <assert.h>

#include "hotdog.h"

void HD_Primitive_Render(hd_engine *eng,hd_object *obj, int cx, int cy, int cw, int ch) {
  int32 x,y;
  int32 startx,starty,endx,endy;

  if(  obj->x+cx     <                  0 ) startx = 0; else startx = obj->x + cx;
  if( (obj->x+cx+cw) >  eng->screen.width ) endx   = eng->screen.width; else endx = obj->x + cx + cw;
  if(  obj->y+cy     <                  0 ) starty = 0; else starty = obj->y + cy;
  if( (obj->y+cy+ch) > eng->screen.height ) endy   = eng->screen.height; else endy = obj->y + cy + ch;


  for(y=starty;y<endy;y++) {
    for(x=startx;x<endx;x++) {
      
      BLEND_ARGB8888_ON_ARGB8888( eng->buffer[ y * eng->screen.width + x ], obj->sub.prim->color );
      
    }
  }

#if 0
  for(y=obj->y;y<(obj->y+obj->h);y++) {
    for(x=obj->x;x<(obj->x+obj->h);x++) {
      
      BLEND_ARGB8888_ON_ARGB8888( eng->buffer[ y * eng->screen.width + x ], obj->sub.prim->color );
      
    }
  }
#endif

}
