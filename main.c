

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
                 MICRO_RED_LED, MICRO_YELLOW_LED, SOUND_ON, SOUND_OFF, Q_BUTTON_PRESSED, E_BUTTON_PRESSED, I_BUTTON_PRESSED, 
                 P_BUTTON_PRESSED, C_BUTTON_PRESSED};

/*Funcion para cargar todas las texturas y manejarlas con un arreglo de punteros a ellas, ordenado segun el enum textura_id*/
int cargarImagenes(ALLEGRO_BITMAP *textura[]);
/*Inicializacion de todos los componentes necesarios del programa*/
int inicializarAllegro();
/*Funcion que actualiza el display de acuerdo a la informacion que leea del puerto en el emulador*/
void actualizarDisplay(ALLEGRO_BITMAP* textura[], ALLEGRO_DISPLAY* disp, ALLEGRO_FONT* font, ALLEGRO_SAMPLE_INSTANCE* reproductor, ALLEGRO_TIMER* timerP);

int actionHandler(int action, uint16_t* mascara, ALLEGRO_TIMER* timerP);

int main(int argc, char** argv) {

    al_init(); 
    ALLEGRO_DISPLAY* disp;
    ALLEGRO_FONT* avenir20;
    ALLEGRO_BITMAP* textura[CANTTEXTURAS];
    ALLEGRO_BITMAP* icono = NULL;
    ALLEGRO_EVENT_QUEUE * colaEventos = NULL;
    ALLEGRO_EVENT evento;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_SAMPLE* musiquita = NULL;
    ALLEGRO_SAMPLE* click = NULL;
    ALLEGRO_SAMPLE_INSTANCE* reproductor = NULL;
    
    int do_exit = 0;        //Variable para salida de loop
    uint16_t mascara = 0;   //mascara para controlar el parpadeo
    int accion = 0;         //Variable para evaluar la accion a realizar segun la entrada
   
    //Inicializamos los addon
    if(inicializarAllegro() == 1){
        al_destroy_font(avenir20);
        al_destroy_display(disp);
        al_destroy_event_queue(colaEventos);
        al_destroy_timer(timer);
        al_destroy_sample(musiquita);
        al_destroy_sample(click);
        al_destroy_bitmap(icono);
        for(int i= 0; i <= CANTTEXTURAS; i++){
            al_destroy_bitmap(textura[i]);
        }
        return -1;
    }
    
    //Creamos el display
    disp = al_create_display(ANCHODELDISPLAY,ALTODELDISPLAY);
    if(!disp){
        al_show_native_message_box(disp, "Error", "ERROR", "Error al cargar la ventana", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    
    //Cambiamos el nombre de la ventana y el icono
    al_set_window_title(disp, "Proyecto Micro");
    icono = al_load_bitmap("resources/textures/icono.png");
    if(icono){    //Si el icono se cargo correctamente lo aplicamos, en caso contrario se destruye el puntero a bitmap y continua el programa
        al_set_display_icon(disp, icono);
    }
    else{
        al_destroy_bitmap(icono);
    }
    //Cargamos las texturas
    if(cargarImagenes(textura) == 1){                       //Si ocurre un problema, destruyo todos los punteros anteriores y termina el programa
        al_show_native_message_box(disp, "Error", "ERROR", "Error al cargar las texturas", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(disp);
        al_destroy_bitmap(icono);
        return -1;
    }
    
    avenir20 = al_load_font("resources/fonts/Avenir_Next.ttc", 20, 0);
    if (!avenir20) {                                                //Si ocurre un problema, destruyo todos los punteros anteriores y termina el programa
        al_show_native_message_box(disp, "Error", "ERROR", "Error al cargar las fuentes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(disp);
        al_destroy_bitmap(icono);
        for(int i= 0; i <= CANTTEXTURAS; i++){
            al_destroy_bitmap(textura[i]);
        }
        return -1;
     }
    al_reserve_samples(2);
    if(al_show_native_message_box(disp, "Seleccione cancion", "Pregunta:"
            , "Quiere escuchar Harry Potter? En caso de No se reproducira Africa ToTo"
            , NULL, ALLEGRO_MESSAGEBOX_QUESTION + ALLEGRO_MESSAGEBOX_YES_NO) == 2){
        musiquita = al_load_sample("resources/music/africa-toto.wav");
    }
    else{
        musiquita = al_load_sample("resources/music/Hedwig'stheme8-Bit.ogg");
    }
    if(!musiquita){                                                //Si ocurre un problema, destruyo todos los punteros anteriores y termina el programa
        al_show_native_message_box(disp, "Error", "ERROR", "Error al cargar la musica", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(disp);
        al_destroy_font(avenir20);
        al_destroy_bitmap(icono);        
        for(int i= 0; i <= CANTTEXTURAS; i++){
            al_destroy_bitmap(textura[i]);
        }
        return -1;
    }
    click = al_load_sample("resources/music/click_sound.wav"); //Cargo el sonido de click
    if(!click){                                                //Si ocurre un problema, destruyo todos los punteros anteriores y termina el programa
        al_show_native_message_box(disp, "Error", "ERROR", "Error al cargar los sonidos", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(disp);
        al_destroy_font(avenir20);
        al_destroy_sample(musiquita);
        al_destroy_bitmap(icono); 
        for(int i= 0; i <= CANTTEXTURAS; i++){
            al_destroy_bitmap(textura[i]);
        }
        return -1;
    }
    
    colaEventos = al_create_event_queue();  //genero mi cola de eventos
    if (!colaEventos) {//Si ocurre un problema, destruyo todos los punteros anteriores y termina el programa
        al_show_native_message_box(disp, "Error", "ERROR", "Error al generar cola de eventos", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(disp);
        al_destroy_font(avenir20);
        al_destroy_sample(musiquita);
        al_destroy_sample(click);
        al_destroy_bitmap(icono);
        for(int i= 0; i <= CANTTEXTURAS; i++){
            al_destroy_bitmap(textura[i]);
        }
        return -1;
    }
    
    
    timer = al_create_timer(1);     //Genero mi timer para el parpadeo
    if (!timer) {                   //Si ocurre un problema, destruyo todos los punteros anteriores y termina el programa
        al_show_native_message_box(disp, "Error", "ERROR", "Error al generar cola de eventos", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(disp);
        al_destroy_font(avenir20);
        al_destroy_sample(musiquita);
        al_destroy_sample(click);
        al_destroy_bitmap(icono);
        for(int i= 0; i <= CANTTEXTURAS; i++){
            al_destroy_bitmap(textura[i]);
        }
    }
    
    /*Inicializo un mixer default para permitir reproducir la musica con mayor facilidad*/
    reproductor = al_create_sample_instance(musiquita);
    al_attach_sample_instance_to_mixer(reproductor, al_get_default_mixer());
    
    al_register_event_source(colaEventos, al_get_display_event_source(disp));
    al_register_event_source(colaEventos, al_get_keyboard_event_source());
    al_register_event_source(colaEventos, al_get_mouse_event_source());
    al_register_event_source(colaEventos, al_get_timer_event_source(timer));

    while (!do_exit) {
  
        al_wait_for_event(colaEventos, &evento); //Espera que ocurra un evento
        accion = 0;
        
        switch(evento.type){                    //Se evalua el evento ocurrido y se actua acordemente
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                do_exit = 1;
                break;
                
            case ALLEGRO_EVENT_KEY_DOWN:
                accion = keyboardChanges (PRESSED, evento.keyboard.keycode);
                do_exit = actionHandler(accion, &mascara, timer);
                break;
                
            case ALLEGRO_EVENT_KEY_UP:   
                keyboardChanges (NOPRESSED, evento.keyboard.keycode);
                break;
                
            case ALLEGRO_EVENT_TIMER:
                    
                if(wordGet(PUERTOD) == 0){
                    maskOn(PUERTOD, mascara);
                }
                else{
                    mascara = mascara | wordGet(PUERTOD);
                    maskOff(PUERTOD, 65535);
                }
                break;
                
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
               
                if ( evento.mouse.button & 1){   //Solo si se presiono el click izquierdo
                    al_play_sample(click, 2, 0 ,1 , ALLEGRO_PLAYMODE_ONCE, NULL);
                }
                
                accion = mouseChanges(PRESSED, evento.mouse.x, evento.mouse.y);
                do_exit = actionHandler(accion, &mascara, timer);
                break;
                
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if ( evento.mouse.button & 1){   //Solo si se presiono el click izquierdo
                    accion = mouseChanges(NOPRESSED, evento.mouse.x, evento.mouse.y);
                }
                break;
        }
        
        actualizarDisplay(textura, disp, avenir20, reproductor, timer);   //Actualizo el display antes de esperar el proximo evento

    }
    /*Destruyo todas las estructuras que lo requieren*/
    al_destroy_font(avenir20);
    al_destroy_display(disp);
    al_destroy_event_queue(colaEventos);
    al_destroy_timer(timer);
    al_destroy_sample(musiquita);
    al_destroy_sample(click);
    al_destroy_bitmap(icono);
    for(int i= 0; i <= CANTTEXTURAS; i++){
        al_destroy_bitmap(textura[i]);
    }
    
    return (EXIT_SUCCESS);
}

int actionHandler(int action, uint16_t* mascara, ALLEGRO_TIMER* timerP){
    
    int exit = 0;
    
    if(action == 1){
        
        if(al_get_timer_started(timerP)){
            al_stop_timer(timerP);
        }
        else{
            al_start_timer(timerP);
            *mascara = wordGet(PUERTOD);
        }
    }
    else if(action == 2){
        exit = 1;
    }
    
    return exit;
}

int inicializarAllegro(ALLEGRO_DISPLAY* disp){
    
    int salida = 0;
    
    if(!al_init_image_addon())     //Inicializo el addon para manejo de imagenes, en caso de error muestro un mensaje
    {
        al_show_native_message_box(disp, "Error", "ERROR", "Error al iniciar addon de imagenes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        salida = 1;
    }
    
    if(!al_init_font_addon())       //Inicializo el addon para manejo de fuentes, en caso de error muestro un mensaje
    {
        al_show_native_message_box(disp, "Error", "ERROR", "Error al iniciar addon fuentes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        salida = 1;
    }
    
    if(!al_init_ttf_addon())       //Inicializo el addon para manejo de archivos .ttf de fuentes, en caso de error muestro un mensaje
    {
        al_show_native_message_box(disp, "Error", "ERROR", "Error al iniciar addon de lectura de fuentes", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        salida = 1;
    }
    
    if(!al_init_acodec_addon())       //Inicializo el addon para manejo de archivos de audio, en caso de error muestro un mensaje
    {
        al_show_native_message_box(disp, "Error", "ERROR", "Error al iniciar addon de codec de audio", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        salida = 1;
    }
    
    if (!al_install_keyboard()) {       //Inicializo el teclado, en caso de error muestro un mensaje
        al_show_native_message_box(disp, "Error", "ERROR", "Error al instalar el teclado", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        salida = 1;
    }
    
    if (!al_install_mouse()) {          //Inicializo el mouse, en caso de error muestro un mensaje
        al_show_native_message_box(disp, "Error", "ERROR", "Error al instalar el mouse", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        salida = 1;
    }
     
    if (!al_install_audio()) {          //Inicializo el audio, en caso de error muestro un mensaje
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

void actualizarDisplay(ALLEGRO_BITMAP* textura[], ALLEGRO_DISPLAY* disp, ALLEGRO_FONT* font, ALLEGRO_SAMPLE_INSTANCE* reproductor, ALLEGRO_TIMER* timerP){
    
    al_clear_to_color(al_map_rgb(181, 224, 186));               //Pinto el fondo color verde bonito
    
    al_draw_bitmap(textura[CIRCUITO], CIRCUITOX, CIRCUITOY, 0); //Dibujo la imagen del circuito segun las coordenadas seteadas en constantes

    al_draw_bitmap(textura[BITS_BUTTONS], BOTONBITSX, BOTONBITSY, 0);   //dibujado de la barra de botones de control de bits
    

    
    if(getKeyState(KEY_C) == PRESSED){
        al_draw_bitmap(textura[C_BUTTON_PRESSED], BOTONCX, BOTONCY, 0);     //Dibujo el boton C para apagar los leds
    }
    else{
        al_draw_bitmap(textura[C_BUTTON], BOTONCX, BOTONCY, 0);     //Dibujo el boton C para apagar los leds
    }
    
    
    if(getKeyState(KEY_E) == PRESSED){
        al_draw_bitmap(textura[E_BUTTON_PRESSED], BOTONCX, BOTONCY + DISTYBOTONESCE, 0);  //Dibujo el boton E para encender los leds
    }
    else{
        al_draw_bitmap(textura[E_BUTTON], BOTONCX, BOTONCY + DISTYBOTONESCE, 0);  //Dibujo el boton E para encender los leds
    }
    
    
    if(getKeyState(KEY_P) == PRESSED){
        al_draw_bitmap(textura[P_BUTTON_PRESSED], BOTONCX + DISTXBOTONESCE, BOTONCY, 0);  //Dibujo el boton P para comenzar el parpadeo
    }
    else{
        al_draw_bitmap(textura[P_BUTTON], BOTONCX + DISTXBOTONESCE, BOTONCY, 0);  //Dibujo el boton P para comenzar el parpadeo
    }
    
    
    if(getKeyState(KEY_I) == PRESSED){
        al_draw_bitmap(textura[I_BUTTON_PRESSED], BOTONCX + DISTXBOTONESCE, BOTONCY + DISTYBOTONESCE, 0);  //Dibujo el boton I para hacer un toggle a los leds
    }
    else{
        al_draw_bitmap(textura[I_BUTTON], BOTONCX + DISTXBOTONESCE, BOTONCY + DISTYBOTONESCE, 0);  //Dibujo el boton I para hacer un toggle a los leds
    }
    
    
    if(getKeyState(KEY_Q) == PRESSED){
        al_draw_bitmap(textura[Q_BUTTON_PRESSED], al_get_display_width(disp) - DISTYBOTONESCE, 10, 0);  //Dibujo el boton Qpara salir del programa
    }
    else{
        al_draw_bitmap(textura[Q_BUTTON], al_get_display_width(disp) - DISTYBOTONESCE, 10, 0);  //Dibujo el boton Qpara salir del programa
    }
    
    
    if (getSelectedPort() == PUERTOA){              //De acuerdo al puerto seleccionado dibujo los botones de puerto A y puerto B segun corresponda
        al_draw_bitmap(textura[PORTA_BUTTON_P],PUERTOAX, PUERTOAY, 0);                  //Puerto A presionado
        al_draw_bitmap(textura[PORTB_BUTTON_NP], PUERTOAX + ANCHOPUERTOA, PUERTOAY, 0);
    }
    else if (getSelectedPort() == PUERTOB){
        al_draw_bitmap(textura[PORTA_BUTTON_NP],PUERTOAX, PUERTOAY, 0);                 //Puerto B presionado
        al_draw_bitmap(textura[PORTB_BUTTON_P], PUERTOAX + ANCHOPUERTOA, PUERTOAY, 0);
    }
    
    /*Escribo el texto para los botones*/
    al_draw_text(font, al_map_rgb(0, 0, 0), BOTONCX + ANCHOBOTC + 10, BOTONCY + 9, 0, "Apagar");
    
    al_draw_text(font, al_map_rgb(0, 0, 0), BOTONCX + ANCHOBOTC + 10, BOTONCY + DISTYBOTONESCE + 9, 0, "Encender");
    
    al_draw_text(font, al_map_rgb(0, 0, 0), BOTONCX + DISTXBOTONESCE + ANCHOBOTC + 10, BOTONCY + 9, 0, "Parpadear");
    
    al_draw_text(font, al_map_rgb(0, 0, 0), BOTONCX + DISTXBOTONESCE + ANCHOBOTC + 10, BOTONCY + DISTYBOTONESCE + 9, 0, "Invertir");
    
    
    /*Tomo el valor del puerto D del modulo emulador, y de acuerdo a los valores de los bits 
     dibujo los leds encendidos o apagados segun corresponda*/
    uint16_t puerto = wordGet(PUERTOD);
    
    //!al_get_timer_started(timerP)
    for (int i = 0; 1  && i < 16; i++){
        if(puerto%2 == 1){
            al_draw_bitmap(textura[GREEN_LED],LEDSUPX + CIRCUITOX, LEDSUPY + i*LEDSIZE + CIRCUITOY, 0);
            al_draw_bitmap(textura[MICRO_YELLOW_LED], MINILEDSUPDERX + CIRCUITOX, MINILEDSUPDERY + i*MINILEDSIZE + CIRCUITOY, 0);
        }
        puerto /= 2;
    }
    
    /*Segun si el programa se encuentra muteado dibujo el boton de muteo o desmuteo segun corresponda*/
    if(getMute() == 1){
        al_draw_bitmap(textura[SOUND_OFF], SOUNDICNX, SOUNDICNY, 0);
        al_set_sample_instance_playing(reproductor, false);
    }
    else{
        al_draw_bitmap(textura[SOUND_ON], SOUNDICNX, SOUNDICNY, 0);
        al_draw_bitmap(textura[MICRO_BLUE_LED], MINILEDSUPIZQX + CIRCUITOX, MINILEDSUPIZQY + 2*MINILEDSIZE + CIRCUITOY, 0);
        al_set_sample_instance_playing(reproductor, true);
    }
    
    al_flip_display();    //Doy vuelta el display mostrando el backbuffer que se dibujo con las actualizaciones
}
