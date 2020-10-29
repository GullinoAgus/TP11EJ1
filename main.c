

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
    
    return salida;
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