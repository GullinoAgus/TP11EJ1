

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#define MAXTEXTURES 20
#define FPS    60.0

enum MYKEYS {
    KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7,
    KEY_Q, KEY_S, KEY_P, KEY_C, KEY_T, KEY_A, KEY_B
};

char active_port = 'A';

int main(int argc, char** argv) {
/*
    al_init(); 
    ALLEGRO_DISPLAY* disp = al_create_display(850,480);
    ALLEGRO_BITMAP* textura[MAXTEXTURES];
    
    
    if(!al_init_image_addon())
    {
        printf("couldn't initialize image addon\n");
        return 1;
    }
   
    
    char* string = "textures/C_button.bmp";
    textura[0] = al_load_bitmap(string);
    if(!textura[0])
    {
        printf("couldn't load transparent_circuit.bmp\n");
        return 1;
    }
    
    al_draw_bitmap(textura[0], 0, 0, 0);
    al_flip_display();
    
    while(1);
    
    al_destroy_display(disp);
    al_destroy_bitmap(textura[0]);

    
    return (EXIT_SUCCESS);*/
    
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    
    bool key_pressed[15] = { 0 };
    bool redraw = false;
    bool do_exit = false;
    
    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    
    if (!al_install_keyboard()) {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }
    
    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }
    
    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_timer(timer);
        return -1;
    }
    
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    
    al_start_timer(timer);
    
    while (!do_exit) {
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
        {
            if (ev.type == ALLEGRO_EVENT_TIMER) {
                

                redraw = true;
            }
            else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
                switch (ev.keyboard.keycode) {
                    case ALLEGRO_KEY_0:
                        if(key_pressed[KEY_0] == false)
                            bitSet(active_port,0);
                        key_pressed[KEY_0] = true;
                        break;

                    case ALLEGRO_KEY_1:
                        if(key_pressed[KEY_1] == false)
                            bitSet(active_port,1);
                        key_pressed[KEY_1] = true;
                        break;

                    case ALLEGRO_KEY_2:
                        if(key_pressed[KEY_2] == false)
                            bitSet(active_port,2);
                        key_pressed[KEY_2] = true;
                        break;

                    case ALLEGRO_KEY_3:
                        if(key_pressed[KEY_3] == false)
                            bitSet(active_port,3);
                        key_pressed[KEY_3] = true;
                        break;
                        
                    case ALLEGRO_KEY_4:
                        if(key_pressed[KEY_4] == false)
                            bitSet(active_port,4);
                        key_pressed[KEY_4] = true;
                        break;
                        
                    case ALLEGRO_KEY_5:
                        if(key_pressed[KEY_5] == false)
                            bitSet(active_port,5);
                        key_pressed[KEY_5] = true;
                        break;
                        
                    case ALLEGRO_KEY_6:
                        if(key_pressed[KEY_6] == false)
                            bitSet(active_port,6);
                        key_pressed[KEY_6] = true;
                        break;
                        
                    case ALLEGRO_KEY_7:
                        if(key_pressed[KEY_7] == false)
                            bitSet(active_port,7);
                        key_pressed[KEY_7] = true;
                        break;
                        
                    case ALLEGRO_KEY_Q:
                        if(key_pressed[KEY_Q] == false)
                            do_exit=true;
                        key_pressed[KEY_Q] = true;
                        break;
                        
                    case ALLEGRO_KEY_S:
                        if(key_pressed[KEY_S] == false)
                            maskOn(active_port,255);
                        key_pressed[KEY_S] = true;
                        break;
                        
                    case ALLEGRO_KEY_P:
                        key_pressed[KEY_P] = true;
                        break;
                        
                    case ALLEGRO_KEY_C:
                        if(key_pressed[KEY_C] == false)
                            maskOff(active_port,255);
                        key_pressed[KEY_C] = true;
                        break;
                        
                    case ALLEGRO_KEY_T:
                        if(key_pressed[KEY_T] == false)
                            maskToggle(active_port,255);
                        key_pressed[KEY_T] = true;
                        break;
                        
                    case ALLEGRO_KEY_A:
                        if(key_pressed[KEY_A] == false)
                            active_port='A';
                        key_pressed[KEY_A] = true;
                        break;
                        
                    case ALLEGRO_KEY_B:
                        if(key_pressed[KEY_B] == false)
                            active_port='B';
                        key_pressed[KEY_B] = true;
                        break;
                }
            }
            else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
                switch (ev.keyboard.keycode) {
                    case ALLEGRO_KEY_0:
                        key_pressed[KEY_0] = false;
                        break;

                    case ALLEGRO_KEY_1:
                        key_pressed[KEY_1] = false;
                        break;

                    case ALLEGRO_KEY_2:
                        key_pressed[KEY_2] = false;
                        break;

                    case ALLEGRO_KEY_3:
                        key_pressed[KEY_3] = false;
                        break;
                        
                    case ALLEGRO_KEY_4:
                        key_pressed[KEY_4] = false;
                        break;
                        
                    case ALLEGRO_KEY_5:
                        key_pressed[KEY_5] = false;
                        break;
                        
                    case ALLEGRO_KEY_6:
                        key_pressed[KEY_6] = false;
                        break;
                        
                    case ALLEGRO_KEY_7:
                        key_pressed[KEY_7] = false;
                        break;
                        
                    case ALLEGRO_KEY_Q:
                        key_pressed[KEY_Q] = false;
                        break;
                        
                    case ALLEGRO_KEY_S:
                        key_pressed[KEY_S] = false;
                        break;
                        
                    case ALLEGRO_KEY_P:
                        key_pressed[KEY_P] = false;
                        break;
                        
                    case ALLEGRO_KEY_C:
                        key_pressed[KEY_C] = false;
                        break;
                        
                    case ALLEGRO_KEY_T:
                        key_pressed[KEY_T] = false;
                        break;
                        
                    case ALLEGRO_KEY_A:
                        key_pressed[KEY_A] = false;
                        break;
                        
                    case ALLEGRO_KEY_B:
                        key_pressed[KEY_B] = false;
                        break;
                }
            }
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
        }
    }

    al_destroy_timer(timer);
    return 0;
}
