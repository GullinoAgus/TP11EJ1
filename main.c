

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


#define CANTTEXTURAS 16
#define CIRCUITOX 20
#define CIRCUITOY 80
#define PUERTOAX 465
#define PUERTOAY 100
#define BOTONBITSX 488
#define BOTONBITSY 200
#define BOTONCX 488
#define BOTONCY 280



enum textura_id {CIRCUITO, Q_BUTTON, E_BUTTON, I_BUTTON, P_BUTTON, C_BUTTON, BITS_BUTTONS, BLUE_LED, YELLOW_LED, 
                 GREEN_LED, PORTA_BUTTON_NP, PORTA_BUTTON_P, PORTB_BUTTON_NP, PORTB_BUTTON_P, MICRO_BLUE_LED, MICRO_RED_LED, MICRO_YELLOW_LED};

int cargarImagenes(ALLEGRO_BITMAP *textura[]);
int inicializarAllegro();

int main(int argc, char** argv) {

    al_init(); 
    ALLEGRO_DISPLAY* disp;
    ALLEGRO_FONT* font;
    ALLEGRO_BITMAP* textura[CANTTEXTURAS];
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    int aux;

    
    //Inicializamos los addon
    if(inicializarAllegro() == 1){
        return 1;
    }
    
    //Creamos el display
    disp = al_create_display(850,480);
    if(!disp){
        printf("couldn't create display\n");
        return 1;
    }
    
    //Cambiamos el nombre de la ventana
    al_set_window_title(disp, "Proyecto Micro");
    
    
    //Cargamos las texturas
    if(cargarImagenes(textura) == 1){
        return 1;
    }
    
    //Pintamos el fondo
    al_clear_to_color(al_map_rgb(181, 224, 186));
    
    
    
    
    //Dibujamos la interfaz de ususario
    al_draw_bitmap(textura[CIRCUITO], CIRCUITOX, CIRCUITOY, 0);
    
    al_draw_bitmap(textura[PORTA_BUTTON_NP], PUERTOAX, PUERTOAY, 0);

    aux = al_get_bitmap_width(textura[PORTA_BUTTON_NP]);
    al_draw_bitmap(textura[PORTB_BUTTON_NP], PUERTOAX+aux, PUERTOAY, 0);
    
    al_draw_bitmap(textura[BITS_BUTTONS], BOTONBITSX, BOTONBITSY, 0);
    
    al_draw_bitmap(textura[C_BUTTON], BOTONCX, BOTONCY, 0);
    
    al_draw_bitmap(textura[E_BUTTON], BOTONCX, BOTONCY+60, 0);
    
    al_draw_bitmap(textura[P_BUTTON], BOTONCX+163, BOTONCY, 0);
            
    al_draw_bitmap(textura[I_BUTTON], BOTONCX+163, BOTONCY+60, 0);
    
    
    //al_draw_bitmap(textura[Q_BUTTON], interfaz.botonX, interfaz.botonY+60, 0);
    
    int w, h;
            
    
    w = al_get_bitmap_width(textura[Q_BUTTON]);
    h = al_get_bitmap_height(textura[Q_BUTTON]);
    al_draw_scaled_bitmap(textura[Q_BUTTON], 0, 0, w, h, 790, 10, w, h, 0);
    
    
    char* str1 = "resources/fonts/Avenir_Next.ttc";
    font = al_load_font(str1, 20, 0);
    if (!font) {
        fprintf(stderr, "failed to load font\n");
        al_destroy_font(font);
        return 1;
     }
    
    al_draw_text(font, al_map_rgb(0, 0, 0), 530, 312, 0, "Apagar");
    al_draw_text(font, al_map_rgb(0, 0, 0), 530, 370, 0, "Encender");
    al_draw_text(font, al_map_rgb(0, 0, 0), 700, 312, 0, "Parpadear");
    al_draw_text(font, al_map_rgb(0, 0, 0), 700, 370, 0, "Invertir");

   
    al_flip_display();
    
    
    
    
    
    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");;
        return 1;
    }
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    
    int do_exit = 0;
    
    while (!do_exit) {
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
        {
            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_Q:
                    do_exit = 1;
                    break;
            }
        }
    }
    
    
    
    
    al_destroy_font(font);
    al_destroy_display(disp);
    for(int i= 0; i < CANTTEXTURAS; i++){
        al_destroy_bitmap(textura[i]);
    }
    
    return (EXIT_SUCCESS);
}

int inicializarAllegro(){
    
    int salida = 0;
    
    if(!al_init_image_addon())
    {
        printf("couldn't initialize image addon\n");
        salida = 1;
    }
    
    if(!al_init_font_addon())
    {
        printf("couldn't initialize image addon\n");
        salida = 1;
    }
    
    if(!al_init_ttf_addon())
    {
        printf("couldn't initialize image addon\n");
        salida = 1;
    }
    
    if (!al_install_keyboard()) {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        salida = 1;
    }
    
<<<<<<< HEAD
    return salida;
=======
    al_destroy_display(disp);
    al_destroy_bitmap(textura[0]);

    
    return (EXIT_SUCCESS);
    
    /* a partir de aca es lo que agrego alvaro sobre el teclado
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
    return 0;*/
>>>>>>> origin/main
}

// 0 si cargo tood bien, sino 1
int cargarImagenes(ALLEGRO_BITMAP *textura[]){
    
    char rutaEfectiva[30];
    int error = 0;
    
    for(int i = 0; !error && i < CANTTEXTURAS; i++){
        
        int size = sprintf(rutaEfectiva, "resources/textures/%d.png", i);
        textura[i] = al_load_bitmap(rutaEfectiva);
        
        if(!textura[i])
        {
            printf("couldn't load %s\n", rutaEfectiva);
            error = 1;
        }
    }
    
    return error;
}
