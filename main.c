

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#define MAXTEXTURES 20

int main(int argc, char** argv) {

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

    
    return (EXIT_SUCCESS);
}
