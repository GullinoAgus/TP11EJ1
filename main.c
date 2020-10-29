

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "emulador.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


#define CANTTEXTURAS 16
#define CIRCUITOX 20
#define CIRCUITOY 80
#define PUERTOAX 465
#define PUERTOAY 100
#define ANCHOPUERTOA 174
#define ALTOPUERTOA 49
#define BOTONBITSX 488
#define BOTONBITSY 200
#define BOTONCX 488
#define BOTONCY 280
#define ANCHOBOTC 45
#define ALTOBOTC 49
#define DISTYBOTONESCE 60
#define DISTXBOTONESCE 163
#define LEDSUPX 380
#define LEDSUPY 34
#define LEDSIZE 14
#define MINILEDSUPIZQX 166
#define MINILEDSUPIZQY 38
#define MINILEDSUPDERX 272
#define MINILEDSUPDERY 38
#define MINILEDSIZE 14

enum textura_id {CIRCUITO = 0, Q_BUTTON, E_BUTTON, I_BUTTON, P_BUTTON, C_BUTTON, BITS_BUTTONS, BLUE_LED, YELLOW_LED, 
                 GREEN_LED, PORTA_BUTTON_NP, PORTA_BUTTON_P, PORTB_BUTTON_NP, PORTB_BUTTON_P, MICRO_BLUE_LED, MICRO_RED_LED, MICRO_YELLOW_LED};

int cargarImagenes(ALLEGRO_BITMAP *textura[]);
int inicializarAllegro();
void ActualizarDisplay(ALLEGRO_BITMAP* textura[], ALLEGRO_DISPLAY* disp, ALLEGRO_FONT* font);

char PuertoSeleccionado = PUERTOA;

int main(int argc, char** argv) {

    al_init(); 
    ALLEGRO_DISPLAY* disp;
    ALLEGRO_FONT* Avenir20;
    ALLEGRO_BITMAP* textura[CANTTEXTURAS];
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    uint16_t mascara = 0;
   
    //Inicializamos los addon
    if(inicializarAllegro() == 1){
        return -1;
    }
    
    //Creamos el display
    disp = al_create_display(850,480);
    
    if(!disp){
        al_show_native_message_box(disp, "Error", "ERROR", "Error al cargar la ventana", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    
    //Cambiamos el nombre de la ventana
    al_set_window_title(disp, "Proyecto Micro");
    
    
    //Cargamos las texturas
    if(cargarImagenes(textura) == 1){
        al_show_native_message_box(disp, "Error", "ERROR", "Error al cargar las texturas", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(disp);
        return -1;
    }
    
    Avenir20 = al_load_font("resources/fonts/Avenir_Next.ttc", 20, 0);
    if (!Avenir20) {
        al_show_native_message_box(disp, "Error", "ERROR", "Error al cargar las fuentes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(disp);
        al_destroy_font(Avenir20);
        return -1;
     }
    
    event_queue = al_create_event_queue();
    if (!event_queue) {
        al_show_native_message_box(disp, "Error", "ERROR", "Error al generar cola de eventos", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    
    timer = al_create_timer(1);
    
    al_register_event_source(event_queue, al_get_display_event_source(disp));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    ALLEGRO_EVENT ev;
    
    int do_exit = 0;
    maskOn(PUERTOD, 0xA0B1);
    while (!do_exit) {

        ActualizarDisplay(textura, disp, Avenir20);
        
        al_wait_for_event(event_queue, &ev); //Toma un evento de la cola, VER RETURN EN DOCUMENT.
        
        switch(ev.type){
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                do_exit = 1;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (ev.keyboard.keycode){
                    case ALLEGRO_KEY_B:
                        PuertoSeleccionado = PUERTOB;
                        break;
                    case ALLEGRO_KEY_A:
                        PuertoSeleccionado = PUERTOA;
                        break;
                    case ALLEGRO_KEY_P:
                        if(al_get_timer_started(timer)){
                            al_stop_timer(timer);
                        }
                        else{
                            al_start_timer(timer);
                        }
                        break;
                }
                break;
            case ALLEGRO_EVENT_TIMER:
                mascara = (wordGet(PUERTOD) == 0) ? mascara : wordGet(PUERTOD);
                maskToggle(PUERTOD, mascara);
                break;
        }
        
    }
    
    al_destroy_font(Avenir20);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    for(int i= 0; i < CANTTEXTURAS; i++){
        al_destroy_bitmap(textura[i]);
    }
    
    return (EXIT_SUCCESS);
}

int inicializarAllegro(ALLEGRO_DISPLAY* disp){
    
    int salida = 0;
    
    if(!al_init_image_addon())
    {
        al_show_native_message_box(disp, "Error", "ERROR", "Error al iniciar addon de imagenes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        salida = 1;
    }
    
    if(!al_init_font_addon())
    {
        al_show_native_message_box(disp, "Error", "ERROR", "Error al iniciar addon fuentes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        salida = 1;
    }
    
    if(!al_init_ttf_addon())
    {
        al_show_native_message_box(disp, "Error", "ERROR", "Error al iniciar addon de lectura de fuentes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        salida = 1;
    }
    
    if (!al_install_keyboard()) {
        al_show_native_message_box(disp, "Error", "ERROR", "Error al instalar el teclado", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        salida = 1;
    }
    
    if (!al_install_mouse()) {
        al_show_native_message_box(disp, "Error", "ERROR", "Error al instalar el mouse", NULL, ALLEGRO_MESSAGEBOX_ERROR);
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


void ActualizarDisplay(ALLEGRO_BITMAP* textura[], ALLEGRO_DISPLAY* disp, ALLEGRO_FONT* font){
    
    al_clear_to_color(al_map_rgb(181, 224, 186));
    
    al_draw_bitmap(textura[CIRCUITO], CIRCUITOX, CIRCUITOY, 0);

    al_draw_bitmap(textura[BITS_BUTTONS], BOTONBITSX, BOTONBITSY, 0);
    
    al_draw_bitmap(textura[C_BUTTON], BOTONCX, BOTONCY, 0);
    
    al_draw_bitmap(textura[E_BUTTON], BOTONCX, BOTONCY + DISTYBOTONESCE, 0);
    
    al_draw_bitmap(textura[P_BUTTON], BOTONCX + DISTXBOTONESCE, BOTONCY, 0);
            
    al_draw_bitmap(textura[I_BUTTON], BOTONCX + DISTXBOTONESCE, BOTONCY + DISTYBOTONESCE, 0);
    
    al_draw_bitmap(textura[Q_BUTTON], al_get_display_width(disp) - DISTYBOTONESCE, 10, 0);
    
    al_draw_bitmap(textura[MICRO_BLUE_LED], MINILEDSUPIZQX + CIRCUITOX, MINILEDSUPIZQY + 2*MINILEDSIZE + CIRCUITOY, 0);
    
    al_draw_text(font, al_map_rgb(0, 0, 0), BOTONCX + ANCHOBOTC + 10, BOTONCY + 9, 0, "Apagar");
    
    al_draw_text(font, al_map_rgb(0, 0, 0), BOTONCX + ANCHOBOTC + 10, BOTONCY + DISTYBOTONESCE + 9, 0, "Encender");
    
    al_draw_text(font, al_map_rgb(0, 0, 0), BOTONCX + DISTXBOTONESCE + ANCHOBOTC + 10, BOTONCY + 9, 0, "Parpadear");
    
    al_draw_text(font, al_map_rgb(0, 0, 0), BOTONCX + DISTXBOTONESCE + ANCHOBOTC + 10, BOTONCY + DISTYBOTONESCE + 9, 0, "Invertir");
    
    if (PuertoSeleccionado == PUERTOA){
        al_draw_bitmap(textura[PORTA_BUTTON_P],PUERTOAX, PUERTOAY, 0);
        al_draw_bitmap(textura[PORTB_BUTTON_NP], PUERTOAX + ANCHOPUERTOA, PUERTOAY, 0);
    }
    else if (PuertoSeleccionado == PUERTOB){
        al_draw_bitmap(textura[PORTA_BUTTON_NP],PUERTOAX, PUERTOAY, 0);
        al_draw_bitmap(textura[PORTB_BUTTON_P], PUERTOAX + ANCHOPUERTOA, PUERTOAY, 0);
    }
    
    uint16_t puerto = wordGet(PUERTOD);
    
    for (int i = 0; i < 16; i++){
        if(puerto%2 == 1){
            al_draw_bitmap(textura[GREEN_LED],LEDSUPX + CIRCUITOX, LEDSUPY + i*LEDSIZE + CIRCUITOY, 0);
            al_draw_bitmap(textura[MICRO_RED_LED], MINILEDSUPDERX + CIRCUITOX, MINILEDSUPDERY + i*MINILEDSIZE + CIRCUITOY, 0);
        }
        puerto /= 2;
    }
    
    
    al_flip_display();
}
