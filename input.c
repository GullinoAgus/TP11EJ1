/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "input.h"

static char PuertoSeleccionado = PUERTOA;
static bool mute = 0;

int mouseChanges(int evMouseX, int evMouseY, ALLEGRO_SAMPLE* click){
    
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
