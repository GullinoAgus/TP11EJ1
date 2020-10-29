#include <stdio.h>
#include <allegro5/allegro.h>

#define bool int    //Las agrego porque no me las reconoce
#define true 1
#define false 0

#define FPS    60.0
#define SCREEN_W  640
#define SCREEN_H  480
#define CUADRADITO_SIZE 32


int main(int argc, char **argv) {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *cuadradito = NULL;
    
    ALLEGRO_BITMAP *botondeprueba = NULL; //PRUEBA

    bool redraw = false;
    bool do_exit = false;
    float cuadradito_x = SCREEN_W / 2.0 - CUADRADITO_SIZE / 2.0;
    float cuadradito_y = SCREEN_H / 2.0 - CUADRADITO_SIZE / 2.0;
    
    float botonx = 450; //PRUEBA
    float botony = 100; //PRUEBA
    unsigned char cuadraditoColor= 255;
    
    int mouseclick_x = 0;    // inicializo dos variables que contengan las coordenadas del mouse x e y, para el momento del click
    int mouseclick_y = 0;    

    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    if (!al_install_mouse()) {
        fprintf(stderr, "failed to initialize the mouse!\n");
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer);
        return -1;
    }

    cuadradito = al_create_bitmap(CUADRADITO_SIZE, CUADRADITO_SIZE);
    if (!cuadradito) {
        fprintf(stderr, "failed to create cuadradito bitmap!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
    
    botondeprueba = al_create_bitmap(100, 45);    //PRUEBA
        if (!botondeprueba) {
            fprintf(stderr, "failed to create cuadradito bitmap!\n");
            al_destroy_display(display);
            al_destroy_timer(timer);
            return -1;
        }           //prueba

    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_bitmap(cuadradito);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    al_set_target_bitmap(cuadradito); //Setea el bitmap a dibujar, por defecto se setea al ultimo display creado

    al_clear_to_color(al_map_rgb(cuadraditoColor, cuadraditoColor, cuadraditoColor)); //Rellena el bitmap del cuadradito de violeta
    
    al_set_target_bitmap(botondeprueba);    //PRUEBA
    al_clear_to_color(al_map_rgb(255, 0, 0));   //PRUEBA
    

    al_set_target_bitmap(al_get_backbuffer(display)); //Setea el bitmap a dibujar nuevamente en el display

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(timer);
    

    while (!do_exit) // idem anterior
    {
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
        {
            if (ev.type == ALLEGRO_EVENT_TIMER) // por que tenemos un timer para redibujar?
                redraw = true;

            else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                do_exit = true;
            
            else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                
                mouseclick_x = ev.mouse.x;
                mouseclick_y = ev.mouse.y;
                
                printf("Coordenadas del ultimo click x=%d, y=%d\n", mouseclick_x, mouseclick_y);
            }

            else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {

                //Aca podriamos hacer algo con el movimiento del mouse, creo que no sirve para nada.
                
            }
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));
            //cuadradito_x = mouseclick_x;
            //cuadradito_y = mouseclick_y;
            
            if ( (mouseclick_x >= 450) && (mouseclick_x <= 550) ){
                
                if( (mouseclick_y >= 100) && (mouseclick_y <= 200) ){
                    
                    cuadraditoColor -= 1;
                    al_set_target_bitmap(cuadradito); 
                    al_clear_to_color(al_map_rgb(cuadraditoColor, cuadraditoColor, cuadraditoColor)); 
                }
            }
            al_set_target_bitmap(al_get_backbuffer(display)); 
            al_draw_bitmap(cuadradito, cuadradito_x, cuadradito_y, 0);
            al_draw_bitmap(botondeprueba, 450, 100, 0);
            al_flip_display();
        }

    }

    al_destroy_bitmap(cuadradito);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
