

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "emulador.h"
#include "input.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


enum textura_id {CIRCUITO = 0, Q_BUTTON, E_BUTTON, I_BUTTON, P_BUTTON, C_BUTTON, BITS_BUTTONS, BLUE_LED, YELLOW_LED, 
                 GREEN_LED, PORTA_BUTTON_NP, PORTA_BUTTON_P, PORTB_BUTTON_NP, PORTB_BUTTON_P, MICRO_BLUE_LED,
                 MICRO_RED_LED, MICRO_YELLOW_LED, SOUND_ON, SOUND_OFF};

int cargarImagenes(ALLEGRO_BITMAP *textura[]);
int inicializarAllegro();
void ActualizarDisplay(ALLEGRO_BITMAP* textura[], ALLEGRO_DISPLAY* disp, ALLEGRO_FONT* font, ALLEGRO_SAMPLE_INSTANCE* reproductor);

int main(int argc, char** argv) {

    al_init(); 
    ALLEGRO_DISPLAY* disp;
    ALLEGRO_FONT* Avenir20;
    ALLEGRO_BITMAP* textura[CANTTEXTURAS];
    ALLEGRO_BITMAP* icono = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_SAMPLE* musiquita = NULL;
    ALLEGRO_SAMPLE* click = NULL;
    uint16_t mascara = 0;
    int mouseAction = 0;
   
    //Inicializamos los addon
    if(inicializarAllegro() == 1){
        return -1;
    }
    
    //Creamos el display
    disp = al_create_display(ANCHODELDISPLAY,ALTODELDISPLAY);
    
    if(!disp){
        al_show_native_message_box(disp, "Error", "ERROR", "Error al cargar la ventana", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    
    //Cambiamos el nombre de la ventana
    al_set_window_title(disp, "Proyecto Micro");
    icono = al_load_bitmap("resources/textures/icono.png");
    if(icono){
        al_set_display_icon(disp, icono);
    }
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
    al_reserve_samples(2);
    //musiquita = al_load_sample("resources/music/Hedwig'stheme8-Bit.ogg");
    musiquita = al_load_sample("resources/music/africa-toto.wav");
    if(!musiquita){
        al_show_native_message_box(disp, "Error", "ERROR", "Error al cargar la musica", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(disp);
        al_destroy_font(Avenir20);
        al_destroy_sample(musiquita);
        return -1;
    }
    click = al_load_sample("resources/music/click_sound.wav");
    if(!musiquita){
        al_show_native_message_box(disp, "Error", "ERROR", "Error al cargar los sonidos", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(disp);
        al_destroy_font(Avenir20);
        al_destroy_sample(musiquita);
        al_destroy_sample(click);
        return -1;
    }
    ALLEGRO_SAMPLE_INSTANCE* reproductor = al_create_sample_instance(musiquita);
    al_attach_sample_instance_to_mixer(reproductor, al_get_default_mixer());
    
    event_queue = al_create_event_queue();
    if (!event_queue) {
        al_show_native_message_box(disp, "Error", "ERROR", "Error al generar cola de eventos", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    
    timer = al_create_timer(1);
    
    al_register_event_source(event_queue, al_get_display_event_source(disp));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    ALLEGRO_EVENT ev;
    
    int do_exit = 0;

    while (!do_exit) {

        ActualizarDisplay(textura, disp, Avenir20, reproductor);
        
        al_wait_for_event(event_queue, &ev); //Toma un evento de la cola, VER RETURN EN DOCUMENT.
        
        switch(ev.type){
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                do_exit = 1;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (ev.keyboard.keycode){
                    case ALLEGRO_KEY_B:
                        setSelectedPort(PUERTOB);
                        break;
                    case ALLEGRO_KEY_A:
                        setSelectedPort(PUERTOA);
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
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                al_play_sample(click, 2, 0 ,1.5 , ALLEGRO_PLAYMODE_ONCE, NULL);
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if ( (ev.mouse.button & 2) == 0){   //Solo si se presiono el click izquierdo
                    
                    mouseAction = mouseChanges(ev.mouse.x, ev.mouse.y, click);
                }
                if (mouseAction == 1){
                    
                    if(al_get_timer_started(timer)){
                            al_stop_timer(timer);
                        }
                        else{
                            al_start_timer(timer);
                        }
                        break;
                }
                else if(mouseAction == 2){
                                      
                    do_exit = 1;
                }
                break;
        }
        
    }
    
    al_destroy_font(Avenir20);
    al_destroy_display(disp);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_sample(musiquita);
    al_destroy_sample(click);
    al_destroy_bitmap(icono);
    for(int i= 0; i <= CANTTEXTURAS; i++){
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
    
    if(!al_init_acodec_addon())
    {
        al_show_native_message_box(disp, "Error", "ERROR", "Error al iniciar addon de codec de audio", NULL, ALLEGRO_MESSAGEBOX_ERROR);
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
     
    if (!al_install_audio()) {
        al_show_native_message_box(disp, "Error", "ERROR", "Error al instalar el audio", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        salida = 1;
    }
  
    return salida;   
}

    
// 0 si cargo tood bien, sino 1
int cargarImagenes(ALLEGRO_BITMAP *textura[]){
    
    char rutaEfectiva[30];
    int error = 0;
    
    for(int i = 0; !error && i <= CANTTEXTURAS; i++){
        
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


void ActualizarDisplay(ALLEGRO_BITMAP* textura[], ALLEGRO_DISPLAY* disp, ALLEGRO_FONT* font, ALLEGRO_SAMPLE_INSTANCE* reproductor){
    
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
    
    if (getSelectedPort() == PUERTOA){
        al_draw_bitmap(textura[PORTA_BUTTON_P],PUERTOAX, PUERTOAY, 0);
        al_draw_bitmap(textura[PORTB_BUTTON_NP], PUERTOAX + ANCHOPUERTOA, PUERTOAY, 0);
    }
    else if (getSelectedPort() == PUERTOB){
        al_draw_bitmap(textura[PORTA_BUTTON_NP],PUERTOAX, PUERTOAY, 0);
        al_draw_bitmap(textura[PORTB_BUTTON_P], PUERTOAX + ANCHOPUERTOA, PUERTOAY, 0);
    }
    
    uint16_t puerto = wordGet(PUERTOD);
    
    for (int i = 0; i < 16; i++){
        if(puerto%2 == 1){
            al_draw_bitmap(textura[GREEN_LED],LEDSUPX + CIRCUITOX, LEDSUPY + i*LEDSIZE + CIRCUITOY, 0);
            al_draw_bitmap(textura[MICRO_YELLOW_LED], MINILEDSUPDERX + CIRCUITOX, MINILEDSUPDERY + i*MINILEDSIZE + CIRCUITOY, 0);
        }
        puerto /= 2;
    }
    
    if(getMute() == 1){
        al_draw_bitmap(textura[18], SOUNDICNX, SOUNDICNY, 0);
        al_set_sample_instance_playing(reproductor, false);
    }
    else{
        al_draw_bitmap(textura[17], SOUNDICNX, SOUNDICNY, 0);
        al_set_sample_instance_playing(reproductor, true);
    }
    
    al_flip_display();
}
