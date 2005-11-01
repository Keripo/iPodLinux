#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hotdog.h"
#include "hotdog_font.h"

#include <freetype/ft2build.h>
#include <freetype/freetype.h>

static void HD_Font_RenderGlyph(hd_font *font, FT_Bitmap *ftmap, int32 x,int32 y, int32 w, int32 h ) {
  int32 fx,fy;
  uint8 luma;
  
  if(x<0)x=0; // Silly FT2...

  for(fy=0;fy<ftmap->rows;fy++) {
    for(fx=0;fx<ftmap->width;fx++) {
      luma = (*(uint8 *)(ftmap->buffer + (fy*ftmap->pitch + fx)))&0xFF;

      font->argb[ (fy+y) * font->w + (fx+x) ] = (luma<<24) | (luma<<16) | (luma<<8) | luma;
    }
  }

}

hd_font *HD_Font_Create(char *font,uint32 height,char *text) {
  hd_font *ret;
  FT_Library library;
  FT_Face    face;
  int        error;
  int32      xsize,n,x;

  ret = (hd_font *)malloc( sizeof(hd_font) );
  assert(ret != NULL);

  error = FT_Init_FreeType( &library );
  assert(error == 0);

  error = FT_New_Face( library, font, 0, &face );
  assert(error == 0);

  error = FT_Set_Pixel_Sizes( face, 0, height );
  assert(error == 0);

  xsize = 0;
  for(n=0;n<strlen(text);n++) {
    FT_UInt glyph_index;

    glyph_index = FT_Get_Char_Index( face, text[n] );

    error = FT_Load_Glyph( face, glyph_index, FT_LOAD_DEFAULT );
    assert( error == 0 );

    error = FT_Render_Glyph( face->glyph, ft_render_mode_normal );
    assert( error == 0 );

    xsize += face->glyph->advance.x >> 6;
  }
  xsize++;

  ret->argb = (uint32 *)malloc( xsize * height * 4 );
  assert(ret->argb != NULL);

  memset(ret->argb,0,xsize * height * 4);
  ret->w = xsize;
  ret->h = height;

  x = 0;
  for(n=0;n<strlen(text);n++) {
    FT_UInt glyph_index;

    glyph_index = FT_Get_Char_Index( face, text[n] );

    error = FT_Load_Glyph( face, glyph_index, FT_LOAD_DEFAULT );
    assert( error == 0 );

    error = FT_Render_Glyph( face->glyph, ft_render_mode_normal );
    assert( error == 0 );

    HD_Font_RenderGlyph( ret, &face->glyph->bitmap,
			 x + face->glyph->bitmap_left,(height - face->glyph->bitmap_top),
			 face->glyph->advance.x >> 6,
			 height );

    x += face->glyph->advance.x >> 6;
  }

  return(ret);
}

void     HD_Font_Destroy(hd_font *font) {
  if( font->argb != NULL) free(font->argb);
}

void     HD_Font_Render(hd_engine *eng,hd_object *obj) {
	int32 fp_step_x,fp_step_y,fp_ix,fp_iy;
	int32 x,y;
	int32 startx,starty,endx,endy;
	uint32 buffOff, imgOff;
	
	fp_step_x = (obj->sub.png->w << 16) / obj->w;
	fp_step_y = (obj->sub.png->h << 16) / obj->h;

	if( (obj->x >= 0) && ((obj->x+obj->w) < eng->screen.width) &&
		(obj->y >= 0) && ((obj->y+obj->h) < eng->screen.height) ) {

		startx = obj->x;
		starty = obj->y;
		endx   = obj->x + obj->w;
		endy   = obj->y + obj->h;
	} else assert(0);


	buffOff = obj->y * eng->screen.width + obj->x;
	imgOff  = 0;
	
	fp_ix = fp_iy = 0;
	for(y=0;y<obj->h;y++) {
		fp_ix = 0;
		imgOff = (fp_iy>>16) * obj->sub.png->w;

		for(x=0;x<obj->w;x++) {
			
			BLEND_ARGB8888_ON_ARGB8888( eng->buffer[ buffOff + x ], obj->sub.png->argb[ imgOff + (fp_ix>>16) ] );
			
			fp_ix += fp_step_x;
		}
		buffOff += eng->screen.width;
		fp_iy += fp_step_y;
	}  
}