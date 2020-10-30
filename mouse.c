/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "mouse.h"

static char PuertoSeleccionado = PUERTOA;
static bool mute = 0;

int mouseChanges(int evMouseX, int evMouseY, ALLEGRO_SAMPLE* click){
    
 //   printf("x=%d , y=%d\n", evMouseX, evMouseY);  DEBUG
    
    int salida = 0;
    
    if ( (evMouseX >= PUERTOAX)  && (evMouseX <= PUERTOAX+ANCHOPUERTOA) ){
        if ( (evMouseY >= PUERTOAY)  && (evMouseY <= PUERTOAY+ALTOPUERTOA)){
            
            PuertoSeleccionado = PUERTOA;
        }
    }                          //HITBOX PUERTOA
    if ( (evMouseX > PUERTOAX + ANCHOPUERTOA)  && (evMouseX <= PUERTOAX + 2*ANCHOPUERTOA) ){
        if ( (evMouseY >= PUERTOAY)  && (evMouseY <= PUERTOAY+ALTOPUERTOA)){
            
            PuertoSeleccionado = PUERTOB;
        }
    }        //HITBOX PUERTOB
    if ( (evMouseX >= BOTONBITSX)  && (evMouseX <= BOTONBITSX+LADODEUNBIT) ){
        if ( (evMouseY >= BOTONBITSY)  && (evMouseY <= BOTONBITSY+LADODEUNBIT)){
            
            bitToggle(PuertoSeleccionado, 0);
        }
    }                       //HITBOX BIT0
    if ( (evMouseX >= BOTONBITSX+LADODEUNBIT)  && (evMouseX <= BOTONBITSX+2*LADODEUNBIT) ){
        if ( (evMouseY >= BOTONBITSY)  && (evMouseY <= BOTONBITSY+LADODEUNBIT)){
            
            bitToggle(PuertoSeleccionado, 1);
        }
    }         //HITBOX BIT1
    if ( (evMouseX >= BOTONBITSX+2*LADODEUNBIT)  && (evMouseX <= BOTONBITSX+3*LADODEUNBIT) ){
        if ( (evMouseY >= BOTONBITSY)  && (evMouseY <= BOTONBITSY+LADODEUNBIT)){
            
            bitToggle(PuertoSeleccionado, 2);            
        }
    }       //HITBOX BIT2
    if ( (evMouseX >= BOTONBITSX+3*LADODEUNBIT)  && (evMouseX <= BOTONBITSX+4*LADODEUNBIT) ){
        if ( (evMouseY >= BOTONBITSY)  && (evMouseY <= BOTONBITSY+LADODEUNBIT)){
            
            bitToggle(PuertoSeleccionado, 3);            
        }
    }       //HITBOX BIT3
    if ( (evMouseX >= BOTONBITSX+4*LADODEUNBIT)  && (evMouseX <= BOTONBITSX+5*LADODEUNBIT) ){
        if ( (evMouseY >= BOTONBITSY)  && (evMouseY <= BOTONBITSY+LADODEUNBIT)){
            
            bitToggle(PuertoSeleccionado, 4);            
       }
    }       //HITBOX BIT4
    if ( (evMouseX >= BOTONBITSX+5*LADODEUNBIT)  && (evMouseX <= BOTONBITSX+6*LADODEUNBIT) ){
        if ( (evMouseY >= BOTONBITSY)  && (evMouseY <= BOTONBITSY+LADODEUNBIT)){
            
            bitToggle(PuertoSeleccionado, 5);            
        }
    }       //HITBOX BIT5
    if ( (evMouseX >= BOTONBITSX+6*LADODEUNBIT)  && (evMouseX <= BOTONBITSX+7*LADODEUNBIT) ){
        if ( (evMouseY >= BOTONBITSY)  && (evMouseY <= BOTONBITSY+LADODEUNBIT)){
            
            bitToggle(PuertoSeleccionado, 6);            
        }
    }       //HITBOX BIT6
    if ( (evMouseX >= BOTONBITSX+7*LADODEUNBIT)  && (evMouseX <= BOTONBITSX+8*LADODEUNBIT) ){
        if ( (evMouseY >= BOTONBITSY)  && (evMouseY <= BOTONBITSY+LADODEUNBIT)){
            
            bitToggle(PuertoSeleccionado, 7);            
        }
    }       //HITBOX BIT7
    if ( (evMouseX >= BOTONCX)  && (evMouseX <= BOTONCX+ANCHOBOTC) ){
        if ( (evMouseY >= BOTONCY)  && (evMouseY <= BOTONCY+ALTOBOTC)){
            
            maskOff(PuertoSeleccionado, 0xFF);            
        }
    }                               //HITBOX BOTONC
    if ( (evMouseX >= BOTONCX + DISTXBOTONESCE)  && (evMouseX <= BOTONCX + DISTXBOTONESCE+ ANCHOBOTC) ){         //HITBOX BOTONP
        if ( (evMouseY >= BOTONCY)  && (evMouseY <= BOTONCY+ALTOBOTC)){
            
            
            salida = 1;
        }
    } //HITBOX BOTONP
    if ( (evMouseX >= BOTONCX)  && (evMouseX <= BOTONCX+ANCHOBOTC) ){
        if ( (evMouseY >= BOTONCY + DISTYBOTONESCE)  && (evMouseY <= BOTONCY + DISTYBOTONESCE+ALTOBOTC)){
            
            maskOn(PuertoSeleccionado, 0xFF);
        }
    }                               //HITBOX BOTONE
    if ( (evMouseX >= BOTONCX + DISTXBOTONESCE)  && (evMouseX <= BOTONCX + DISTXBOTONESCE+ ANCHOBOTC) ){
        if ( (evMouseY >= BOTONCY + DISTYBOTONESCE)  && (evMouseY <= BOTONCY + DISTYBOTONESCE+ ALTOBOTC)){
            
            
            maskToggle(PuertoSeleccionado, 0xFF);
        }
    } //HITBOX BOTONI
    if ( (evMouseX >= ANCHODELDISPLAY - DISTYBOTONESCE)  && (evMouseX <= ANCHODELDISPLAY - DISTYBOTONESCE+ANCHOBOTC) ){
        if ( (evMouseY >= 10)  && (evMouseY <= 10+ALTOBOTC)){
            
            
            salida = 2;
       }
    } //HITBOX BOTONQ
    if ( (evMouseX >= SOUNDICNX)  && (evMouseX <= (SOUNDICNX + 36)) ){
        if ( (evMouseY >= SOUNDICNY)  && (evMouseY <= SOUNDICNY + 36)){
            
            mute = !mute;
       }
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
