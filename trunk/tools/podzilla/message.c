/*
 * Copyright (C) 2004 Bernard Leach
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <stdlib.h>
#include <string.h>

#include "pz.h"

static GR_TIMER_ID timer_id;
static GR_WINDOW_ID msg_wid;
static GR_GC_ID msg_gc;
static GR_SCREEN_INFO screen_info;
static char *msg_message;

static void msg_do_draw(GR_EVENT * event)
{
	GR_SIZE width, height, base;

	GrGetGCTextSize(msg_gc, msg_message, -1, GR_TFASCII, &width, &height, &base);

	GrRect(msg_wid, msg_gc, 1, 1, width + 8, height + 8);
	GrText(msg_wid, msg_gc, 5, base + 5, msg_message, -1, GR_TFASCII);
}

static int msg_do_keystroke(GR_EVENT * event)
{
	int ret = 1;
	switch (event->type) {
	case GR_EVENT_TYPE_TIMER:
	case GR_EVENT_TYPE_KEY_DOWN:
		pz_close_window(msg_wid);
		free(msg_message);
	}

	return ret;
}

void new_message_window(char *message)
{
	GR_SIZE width, height, base;

	msg_message = strdup(message);

	GrGetScreenInfo(&screen_info);

	msg_gc = GrNewGC();
	GrSetGCUseBackground(msg_gc, GR_FALSE);
	GrSetGCForeground(msg_gc, BLACK);

	GrGetGCTextSize(msg_gc, message, -1, GR_TFASCII, &width, &height, &base);

	msg_wid = pz_new_window((screen_info.cols - (width + 10)) >> 1,
		(screen_info.rows - (height + 10)) >> 1,
		width + 10, height + 10, msg_do_draw, msg_do_keystroke);

	GrSelectEvents(msg_wid, GR_EVENT_MASK_EXPOSURE|GR_EVENT_MASK_KEY_DOWN|GR_EVENT_MASK_TIMER);

	GrMapWindow(msg_wid);

	/* window will auto-close after 6 seconds */
	timer_id = GrCreateTimer(msg_wid, 6000);
}

