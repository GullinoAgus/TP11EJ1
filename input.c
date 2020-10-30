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
