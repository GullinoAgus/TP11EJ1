

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include "emulador.h"

#define MAXTEXTURES 20

typedef struct{
    ALLEGRO_BITMAP* micro;
    ALLEGRO_BITMAP* LEDportA0;
    ALLEGRO_BITMAP* LEDportA1;
    ALLEGRO_BITMAP* LEDportA2;
    ALLEGRO_BITMAP* LEDportA3;
    /*ALLEGRO_BITMAP* LEDportA0;
    ALLEGRO_BITMAP* LEDportA0;
    ALLEGRO_BITMAP* LEDportA0;
    ALLEGRO_BITMAP* LEDportA0;
    ALLEGRO_BITMAP* LEDportA0;
    ALLEGRO_BITMAP* LEDportA0;
    ALLEGRO_BITMAP* LEDportA0;
    ALLEGRO_BITMAP* LEDportA0;
    ALLEGRO_BITMAP* LEDportA0;
    ALLEGRO_BITMAP* LEDportA0;
    ALLEGRO_BITMAP* LEDportA0;*/
    
} screenLED;


char PuertoSeleccionado = 'A';

int main(int argc, char** argv) {

    al_init(); 
    ALLEGRO_DISPLAY* disp = al_create_display(1280,720);
    ALLEGRO_BITMAP* textura[MAXTEXTURES];
    al_install_keyboard();
    al_install_audio();
    al_init_acodec_addon();
    
    if(!al_init_image_addon())
    {
        printf("couldn't initialize image addon\n");
        return 1;
    }
   
    textura[0] = al_load_bitmap("textures/transparent_circuit_resize.png");
    textura[1] = al_load_bitmap("textures/green_led_on.png");
    textura[2] = al_load_bitmap("textures/portA_button1.bmp");
    textura[3] = al_load_bitmap("textures/portB_button2.bmp");
    textura[4] = al_load_bitmap("textures/portA_button2.bmp");
    textura[5] = al_load_bitmap("textures/portB_button1.bmp");
    
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_EVENT event;
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_keyboard_event_source());
    ALLEGRO_SAMPLE *music = al_load_sample("textures/Faded.wav");
    ALLEGRO_SAMPLE_INSTANCE* musica = al_create_sample_instance(music);
    ALLEGRO_MIXER* mixer = al_create_mixer(44100 , ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
    if (!mixer)
        al_show_native_message_box(disp, "hola", "hola", "hola","hola",NULL);
    ALLEGRO_VOICE* voz = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
    if (!voz)
        al_show_native_message_box(disp, "holas", "hola", "hola","hola",NULL);
    al_attach_mixer_to_voice(mixer, voz);
    al_set_sample_instance_playing(musica, true);

    while(!(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)){
        
        al_wait_for_event(queue, &event);
        al_set_target_backbuffer(disp);
        al_clear_to_color(al_map_rgb(255,255,255));
        al_draw_bitmap(textura[0], 0, 0,0);// al_get_bitmap_width(textura[0]),al_get_bitmap_height(textura[0]),0,0,2*al_get_bitmap_width(textura[0]),2*al_get_bitmap_height(textura[0]),0);
        
        if (event.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(event.keyboard.keycode){
                case(ALLEGRO_KEY_A):
                    PuertoSeleccionado = PUERTOA;
                    break;
                case(ALLEGRO_KEY_B):
                    PuertoSeleccionado = PUERTOB;
                    break;
            }
        }
        
        switch(PuertoSeleccionado){
            case(PUERTOA):
                al_draw_bitmap(textura[4],400,100,0);
                al_draw_bitmap(textura[5],400,200,0);
                break;
            case(PUERTOB):
                al_draw_bitmap(textura[2],400,100,0);
                al_draw_bitmap(textura[3],400,200,0);
                break;
        }
        
        
        
        al_draw_scaled_bitmap(textura[1],0,0 ,8,8,2*(211-21), 2*(155-33), 2*8,2*8,0);


        al_flip_display();
        
    }
    
    al_destroy_display(disp);
    al_destroy_bitmap(textura[0]);

    return (EXIT_SUCCESS);
}
