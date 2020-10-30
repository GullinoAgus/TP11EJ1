/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "input.h"

static char PuertoSeleccionado = PUERTOA;
static bool mute = 0;



botones_t Botoncitos = {true, true, true, true, true, true, true, true, true}; 

int mouseChanges(int evMouseX, int evMouseY, ALLEGRO_SAMPLE* click){
    
    int salida = 0;
    
    if ( HITBOXPA(evMouseX, evMouseY) ){
            PuertoSeleccionado = PUERTOA;
    }                          //HITBOX PUERTOA
    else if ( HITBOXPB(evMouseX, evMouseY) ){
            PuertoSeleccionado = PUERTOB;
    }        //HITBOX PUERTOB
    else if ( HITBOXBIT0(evMouseX, evMouseY) ){
            bitToggle(PuertoSeleccionado, 0);
    }                       //HITBOX BIT0
    else if ( HITBOXBIT1(evMouseX, evMouseY) ){
            bitToggle(PuertoSeleccionado, 1);
    }         //HITBOX BIT1
    else if ( HITBOXBIT2(evMouseX, evMouseY) ){
            bitToggle(PuertoSeleccionado, 2);            
    }       //HITBOX BIT2
    else if ( HITBOXBIT3(evMouseX, evMouseY) ){
            bitToggle(PuertoSeleccionado, 3);            
    }       //HITBOX BIT3
    else if ( HITBOXBIT4(evMouseX, evMouseY) ){
            bitToggle(PuertoSeleccionado, 4);            
    }       //HITBOX BIT4
    else if (HITBOXBIT5(evMouseX, evMouseY)){
            bitToggle(PuertoSeleccionado, 5);            
    }       //HITBOX BIT5
    else if ( HITBOXBIT6(evMouseX, evMouseY) ){
            bitToggle(PuertoSeleccionado, 6);            
    }       //HITBOX BIT6
    else if ( HITBOXBIT7(evMouseX, evMouseY) ){
            bitToggle(PuertoSeleccionado, 7);            
    }       //HITBOX BIT7
    else if ( HITBOXC(evMouseX, evMouseY) ){
            maskOff(PuertoSeleccionado, 0xFF);            
    }                               //HITBOX BOTONC
    else if ( HITBOXP(evMouseX, evMouseY) ){         //HITBOX BOTONP
            salida = 1;
    } //HITBOX BOTONP
    else if ( HITBOXE(evMouseX, evMouseY) ){
            maskOn(PuertoSeleccionado, 0xFF);
    }                               //HITBOX BOTONE
    else if ( HITBOXI(evMouseX, evMouseY) ){
            maskToggle(PuertoSeleccionado, 0xFF);
    } //HITBOX BOTONI
    else if ( HITBOXQ(evMouseX, evMouseY) ){
            salida = 2;
    } //HITBOX BOTONQ
    else if (HITBOXSOUND(evMouseX, evMouseY)){
            mute = !mute;
    } //HITBOX BOTONMUTE
                   

    return salida;
}

int keyboardChanges (bool accion, int tecla){
    
    bool key_pressed[15] = { 0 };
    int salida=0;
            
    if(accion == false) {
        switch(tecla) {
            case ALLEGRO_KEY_0:
                if(key_pressed[KEY_0] == false)
                    bitToggle(PuertoSeleccionado,0);
                key_pressed[KEY_0] = true;
                break;

            case ALLEGRO_KEY_1:
                if(key_pressed[KEY_1] == false)
                    bitToggle(PuertoSeleccionado,1);
                key_pressed[KEY_1] = true;
                break;

            case ALLEGRO_KEY_2:
                if(key_pressed[KEY_2] == false)
                    bitToggle(PuertoSeleccionado,2);
                key_pressed[KEY_2] = true;
                break;

            case ALLEGRO_KEY_3:
                if(key_pressed[KEY_3] == false)
                    bitToggle(PuertoSeleccionado,3);
                key_pressed[KEY_3] = true;
                break;

            case ALLEGRO_KEY_4:
                if(key_pressed[KEY_4] == false)
                    bitToggle(PuertoSeleccionado,4);
                key_pressed[KEY_4] = true;
                break;

            case ALLEGRO_KEY_5:
                if(key_pressed[KEY_5] == false)
                    bitToggle(PuertoSeleccionado,5);
                key_pressed[KEY_5] = true;
                break;

            case ALLEGRO_KEY_6:
                if(key_pressed[KEY_6] == false)
                    bitToggle(PuertoSeleccionado,6);
                key_pressed[KEY_6] = true;
                break;

            case ALLEGRO_KEY_7:
                if(key_pressed[KEY_7] == false)
                    bitToggle(PuertoSeleccionado,7);
                key_pressed[KEY_7] = true;
                break;

            case ALLEGRO_KEY_Q:
                if(key_pressed[KEY_Q] == false)
                    salida=-1;
                key_pressed[KEY_Q] = true;
                break;

            case ALLEGRO_KEY_E:
                if(key_pressed[KEY_E] == false)
                    maskOn(PuertoSeleccionado,255);
                key_pressed[KEY_E] = true;
                break;

            case ALLEGRO_KEY_P:
                key_pressed[KEY_P] = true;
                salida=-2;
                break;

            case ALLEGRO_KEY_C:
                if(key_pressed[KEY_C] == false)
                    maskOff(PuertoSeleccionado,255);
                key_pressed[KEY_C] = true;
                break;

            case ALLEGRO_KEY_I:
                if(key_pressed[KEY_I] == false)
                    maskToggle(PuertoSeleccionado,255);
                key_pressed[KEY_I] = true;
                break;

            case ALLEGRO_KEY_A:
                if(key_pressed[KEY_A] == false)
                    setSelectedPort(PUERTOA);
                key_pressed[KEY_A] = true;
                break;

            case ALLEGRO_KEY_B:
                if(key_pressed[KEY_B] == false)
                    setSelectedPort(PUERTOB);
                key_pressed[KEY_B] = true;
                break;
        }
    }
    else {
        switch(tecla) {
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

            case ALLEGRO_KEY_E:
                key_pressed[KEY_E] = false;
                break;

            case ALLEGRO_KEY_P:
                key_pressed[KEY_P] = false;
                break;

            case ALLEGRO_KEY_C:
                key_pressed[KEY_C] = false;
                break;

            case ALLEGRO_KEY_I:
                key_pressed[KEY_I] = false;
                break;

            case ALLEGRO_KEY_A:
                key_pressed[KEY_A] = false;
                break;

            case ALLEGRO_KEY_B:
                key_pressed[KEY_B] = false;
                break;
        }
    }
    return salida;
}

void setSelectedPort(char puerto){
    PuertoSeleccionado = puerto;
}

char getSelectedPort(void){
    return PuertoSeleccionado;
}

void setMute(bool modo){
    mute = modo;
}

bool getMute(void){
    return mute;
}
