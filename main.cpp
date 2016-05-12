#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <stdio.h>
#include <iostream>
#include "PixelVector.h"
#include "Mapper.h"

const int IPGM_W = 32;
const int IPGM_H = 32;
const float FPS = 60;
const bool FULLSCREEN = false;

using namespace std;

int main(int argc, char **argv) {
	ALLEGRO_DISPLAY *display;
	ALLEGRO_DISPLAY_MODE disp_data;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;
	
	bool redraw = true;
	bool paused = false;
	int screen_width;
	int screen_height;

	//-------------------------------------------------------------------------
	// Setup
	//-------------------------------------------------------------------------
	if (!al_init()) {
		cout << "Failed to init allegro." << endl;
		return -1;
	}
	if (!al_install_mouse()) {
		cout << "Failed to init mouse." << endl;
		return -1;
	}

	if (!al_install_keyboard()) {
		cout << "Failed to init mouse." << endl;
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);								// ~60 FPS
	if (!timer) {
		cout << "Failed to init timer." << endl;
		return -1;
	}

	if (FULLSCREEN) {
		al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
		al_set_new_display_flags(ALLEGRO_FULLSCREEN);
		screen_width = disp_data.width;
		screen_height = disp_data.height;
		display = al_create_display(screen_width, screen_height);
	}
	else {
		screen_width = IPGM_W;
		screen_height = IPGM_H;
		display = al_create_display(IPGM_W, IPGM_H);
	}
	if (!display) {
		cout << "Failed to create the display." << endl;
		al_destroy_timer(timer);
		return -1;
	}
	al_hide_mouse_cursor(display);

	Mapper m = Mapper(IPGM_H, IPGM_W, screen_width, screen_height);

	event_queue = al_create_event_queue();
	if (!event_queue) {
		cout << "Failed to init event queue." << endl;
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	//-------------------------------------------------------------------------
	// Registration
	//-------------------------------------------------------------------------
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_start_timer(timer);

	//-------------------------------------------------------------------------
	// Present the IPGM
	//-------------------------------------------------------------------------
	while (!m.complete()) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				break;
			}
			if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
				paused = !paused;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			paused = !paused;
		}

		if (redraw && al_is_event_queue_empty(event_queue) && !paused) {
			int count = m.getPointCount();
			for (int i = 0; i < count; i++) {
				Point p = m.getPoint(i);
				int fill = m.getFill(p);
				al_put_pixel(p.x, p.y, al_map_rgb(fill, fill, fill));
			}
			al_flip_display();
			m.step();
		}
	}
	
	//-------------------------------------------------------------------------
	// Housekeeping
	//-------------------------------------------------------------------------
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	
	return 0;
}