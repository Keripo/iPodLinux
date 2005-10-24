/*
 * Copyright (c) 2005 Joshua Oreman, Bernard Leach, and Courtney Cavin
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "pz.h"

/* compat globals */
t_GR_SCREEN_INFO screen_info;
long hw_version;

/* static stuff */
static int usb_connected = 0;
static int fw_connected = 0;
static ttk_timer connection_timer = 0;
static int bl_forced_on = 0;

/* Set to tell ipod.c not to actually set the wheel debounce,
 * since we don't want it set *while we're setting it*.
 */
int pz_setting_debounce = 0;

/* Is hold on? */
int pz_hold_is_on = 0;

static void check_connection() 
{
    int temp;
    
    if (((temp = pz_usb_is_connected()) && !usb_connected) ||
	((temp = pz_fw_is_connected()) && !fw_connected))
    {
	const char *title;
	if (pz_usb_is_connected()) title = _("USB Connect");
	else title = _("FireWire Connect");

	if (pz_dialog (title, _("Go to disk mode?"), 2, 10, "No", "Yes") == 1) {
	    pz_ipod_go_to_diskmode();
	}
    }

    usb_connected = pz_ipod_usb_is_connected();
    fw_connected = pz_ipod_fw_is_connected();
    connection_timer = ttk_create_timer (1000, check_connection);
}

static ttk_timer bloff_timer = 0;
static int bl_forced_on = 0;

static void backlight_off() { if (!bl_forced_on) pz_ipod_set (BACKLIGHT, 0); bloff_timer = 0; }
static void backlight_on()  { pz_ipod_set (BACKLIGHT, 1); }

void pz_set_backlight_timer (int sec) 
{
    static int last = PZ_BL_OFF;
    if (sec != PZ_BL_RESET) last = sec;

    if (last == PZ_BL_OFF) {
	if (bloff_timer) ttk_destroy_timer (bloff_timer);
	bloff_timer = 0;
	backlight_off();
    } else if (last == PZ_BL_ON) {
	if (bloff_timer) ttk_destroy_timer (bloff_timer);
	bloff_timer = 0;
	backlight_on();
    } else {
	if (bloff_timer) ttk_destroy_timer (bloff_timer);
	bloff_timer = ttk_create_timer (1000*last, backlight_off);
	backlight_on();
    }
}

void backlight_toggle() 
{
    bl_forced_on = !bl_forced_on;
    pz_handled_hold ('m');
}

static int held_times[128] = { ['m'] = 500 }; // key => ms
static void (*held_handlers[128])() = { ['m'] = backlight_toggle };
static int (*unused_handlers[128])(int, int);

static int held_ignores[128]; // set a char to 1 = ignore its UP event once.
static ttk_timer held_timers[128]; // the timers

void pz_register_global_hold_button (char ch, int ms, void (*handler)()) 
{
    held_times[ch] = ms;
    held_handlers[ch] = handler;
}
void pz_unregister_global_hold_button (char ch) 
{
    held_times[ch] = held_handlers[ch] = 0;
}

void pz_register_global_unused_handler (char ch, void (*handler)(int, int)) 
{
    unused_handlers[ch] = handler;
}
void pz_unregister_global_unused_handler (char ch) 
{
    unused_handlers[ch] = 0;
}

void pz_handled_hold (char ch) 
{
    held_timers[ch] = 0;
    held_ignores[ch]++;
}

int pz_event_handler (int ev, int earg, int time)
{
    static int vtswitched = 0;

    pz_set_backlight_timer (PZ_BL_RESET);

    /* unset setting_debounce if we're not anymore */
    if (pz_setting_debounce && (ttk_windows->w->focus->draw != ttk_slider_draw)) {
	pz_setting_debounce = 0;
	pz_ipod_set (WHEEL_DEBOUNCE, pz_get_int_setting (pz_global_config, WHEEL_DEBOUNCE));
    }

    switch (ev) {
    case TTK_BUTTON_DOWN:
	switch (earg) {
	case TTK_BUTTON_HOLD:
	    pz_hold_is_on = 1;
	    pz_header_fix_hold();
	    break;
	case TTK_BUTTON_MENU:
	    vtswitched = 0;
	    break;
	}
	if (held_times[earg] && held_handlers[earg]) {
	    if (held_timers[earg]) ttk_destroy_timer (held_timers[earg]);
	    held_timers[earg] = ttk_create_timer (held_times[earg], held_handlers[earg]);
	}
	break;
    case TTK_BUTTON_UP:
	if (held_timers[earg]) {
	    ttk_destroy_timer (held_timers[earg]);
	    held_timers[earg] = 0;
	}
	if (held_ignores[earg]) {
	    held_ignores[earg] = 0;
	    return 1;
	}
	switch (earg) {
	case TTK_BUTTON_HOLD:
	    hold_is_on = 0;
	    header_fix_hold();
	    break;
	case TTK_BUTTON_PREVIOUS:
	    if (pz_has_secret ("vtswitch") &&
		ttk_button_pressed (TTK_BUTTON_MENU) && ttk_button_pressed (TTK_BUTTON_PLAY)) {
		// vt switch code <<
		printf ("VT SWITCH <<\n");
		vtswitched = 1;
		return 1;
	    } else if (pz_has_secret ("vtswitch") &&
		       ttk_button_pressed (TTK_BUTTON_MENU) && ttk_button_pressed (TTK_BUTTON_NEXT)) {
		// vt switch code [0]
		printf ("VT SWITCH 0 (N-P)\n");
		vtswitched = 1;
		return 1;
	    } else if (pz_has_secret ("window") && ttk_button_pressed (TTK_BUTTON_MENU) && !vtswitched) {
		TWindowStack *lastwin = ttk_windows;
		while (lastwin->next) lastwin = lastwin->next;
		if (lastwin->w != ttk_windows->w) {
		    ttk_move_window (lastwin->w, 0, TTK_MOVE_ABS);
		    printf ("WINDOW CYCLE >>\n");
		} else
		    printf ("WINDOW CYCLE >> DIDN'T\n");
		return 1;
	    }
	    break;
	case TTK_BUTTON_NEXT:
	    if (pz_has_secret ("vtswitch") &&
		ttk_button_pressed (TTK_BUTTON_MENU) && ttk_button_pressed (TTK_BUTTON_PLAY)) {
		// vt switch code >>
		printf ("VT SWITCH >>\n");
		vtswitched = 1;
		return 1;
	    } else if (pz_has_secret ("vtswitch") &&
		       ttk_button_pressed (TTK_BUTTON_MENU) && ttk_button_pressed (TTK_BUTTON_PREVIOUS)) {
		// vt switch code [0]
		printf ("VT SWITCH 0 (P-N)\n");
		vtswitched = 1;
		return 1;
	    } else if (pz_has_secret ("window") && ttk_button_pressed (TTK_BUTTON_MENU) && !vtswitched) {
		printf ("WINDOW CYCLE <<\n");
		if (ttk_windows->next) {
		    ttk_move_window (ttk_windows->w, 0, TTK_MOVE_END);
		    return 1;
		}
	    }
	    break;
	case TTK_BUTTON_PLAY:
	    if (pz_has_secret ("window") && ttk_button_pressed (TTK_BUTTON_MENU) && !vtswitched) {
		printf ("WINDOW MINIMIZE\n");
		if (ttk_windows->next) {
		    ttk_windows->minimized = 1;
		    return 1;
		}
	    }
	}
	break;
    }
    return 0; // keep event
}


int pz_unused_handler (int ev, int earg, int time) 
{
    switch (ev) {
    case TTK_BUTTON_UP:
	if (unused_handlers[earg])
	    return unused_handlers[earg](earg, time);
	break;
    }
    return 0;
}


void pz_set_time_from_file(void)
{
#ifdef IPOD
	struct timeval tv_s;
	struct stat statbuf;

	/* find the last modified time of the settings file */
	stat( IPOD_SETTINGS_FILE, &statbuf );

	/* convert timespec to timeval */
	tv_s.tv_sec  = statbuf.st_mtime;
	tv_s.tv_usec = 0;

	settimeofday( &tv_s, NULL );
#endif
}


int
main(int argc, char **argv)
{
	TWindow *first;
	if ((first = ttk_init()) == 0) {
		fprintf(stderr, _("ttk_init failed"));
		exit(1);
	}
	ttk_hide_window (first);
	atexit (ttk_quit);
	atexit (pz_ipod_touch_settings);

	ttk_set_global_event_handler (pz_event_handler);
	ttk_set_global_unused_handler (pz_unused_handler);

#ifdef LOCALE
	setlocale(LC_ALL, "");
	bindtextdomain("podzilla", LOCALEDIR);
	textdomain("podzilla");
#endif

	root_gc = ttk_new_gc();
	ttk_set_gc_usebg(root_gc, GR_FALSE);
	ttk_set_gc_foreground(root_gc, BLACK);
	t_GrGetScreenInfo(&screen_info);

	hw_version = pz_ipod_get_hw_version();

	if( hw_version && hw_version < 0x30000 ) { /* 1g/2g only */
		pz_set_time_from_file();
	}

	pz_ipod_fix_settings ((pz_global_settings = pz_load_config ("/etc/podzilla/podzilla.conf")));
	pz_font_load(); // in fonts.c
	pz_secrets_init();
	pz_header_init();
	ttk_add_window (pz_menu_init());

	/**** XXX load modules here ****/

	connection_timer = ttk_create_timer (1000, check_connection);
	usb_connected = usb_is_connected();
	fw_connected = fw_is_connected();

	return ttk_run();
}
