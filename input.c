/***************************************************************************//**
  @file     +input.c+
  @brief    +Definicion de funciones y estructuras que utiliza el main para leer entrada de mouse y teclado+
  @author   +Grupo 1+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "input.h"




/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
//HITBOXES
#define HITBOXP(x,y) (((x) >= BOTONCX + DISTXBOTONESCE)  && ((x) <= BOTONCX + DISTXBOTONESCE+ ANCHOBOTC) && ((y) >= BOTONCY)  && ((y) <= BOTONCY+ALTOBOTC))
#define HITBOXI(x,y) (((x) >= BOTONCX + DISTXBOTONESCE)  && ((x) <= BOTONCX + DISTXBOTONESCE+ ANCHOBOTC) && ((y) >= BOTONCY + DISTYBOTONESCE)  && ((y) <= BOTONCY + DISTYBOTONESCE+ ALTOBOTC))
#define HITBOXC(x,y) (((x) >= BOTONCX)  && ((x) <= BOTONCX+ANCHOBOTC) && ((y) >= BOTONCY)  && ((y) <= BOTONCY+ALTOBOTC))
#define HITBOXE(x,y) (((x) >= BOTONCX)  && ((x) <= BOTONCX+ANCHOBOTC) && ((y) >= BOTONCY + DISTYBOTONESCE)  && ((y) <= BOTONCY + DISTYBOTONESCE+ALTOBOTC))
#define HITBOXQ(x,y) (((x) >= ANCHODELDISPLAY - DISTYBOTONESCE)  && ((x) <= ANCHODELDISPLAY - DISTYBOTONESCE+ANCHOBOTC) && ((y) >= 10)  && ((y) <= 10+ALTOBOTC))
#define HITBOXPA(x,y) (((x) >= PUERTOAX) && ((x) <= PUERTOAX+ANCHOPUERTOA) && ((y) >= PUERTOAY)  && ( (y) <= PUERTOAY + ALTOPUERTOA))
#define HITBOXPB(x,y) (((x) >= PUERTOAX + ANCHOPUERTOA) && ((x) <= PUERTOAX + 2*ANCHOPUERTOA) && ((y) >= PUERTOAY) && ((y) <= PUERTOAY+ALTOPUERTOA))
#define HITBOXSOUND(x,y) (((x) >= SOUNDICNX)  && ((x) <= (SOUNDICNX + 36) && ((y) >= SOUNDICNY)  && ((y) <= SOUNDICNY + 36)))
#define HITBOXBIT0(x,y) (((x) >= BOTONBITSX)  && ((x) <= BOTONBITSX+LADODEUNBIT) && ((y) >= BOTONBITSY)  && ((y) <= BOTONBITSY+LADODEUNBIT))
#define HITBOXBIT1(x,y) (((x) >= BOTONBITSX+LADODEUNBIT+ESPACIOENTREBIT)  && ((x) <= BOTONBITSX+2*LADODEUNBIT + ESPACIOENTREBIT) && ((y) >= BOTONBITSY)  && ((y) <= BOTONBITSY+LADODEUNBIT))
#define HITBOXBIT2(x,y) (((x) >= BOTONBITSX+2*(LADODEUNBIT + ESPACIOENTREBIT))  && ((x) <= BOTONBITSX+3*LADODEUNBIT+2*ESPACIOENTREBIT) && ((y) >= BOTONBITSY)  && ((y) <= BOTONBITSY+LADODEUNBIT))
#define HITBOXBIT3(x,y) (((x) >= BOTONBITSX+3*(LADODEUNBIT + ESPACIOENTREBIT))  && ((x) <= BOTONBITSX+4*LADODEUNBIT+3*ESPACIOENTREBIT) && ((y) >= BOTONBITSY)  && ((y) <= BOTONBITSY+LADODEUNBIT))
#define HITBOXBIT4(x,y) (((x) >= BOTONBITSX+4*(LADODEUNBIT + ESPACIOENTREBIT))  && ((x) <= BOTONBITSX+5*LADODEUNBIT+4*ESPACIOENTREBIT) && ((y) >= BOTONBITSY)  && ((y) <= BOTONBITSY+LADODEUNBIT))
#define HITBOXBIT5(x,y) (((x) >= BOTONBITSX+5*(LADODEUNBIT + ESPACIOENTREBIT))  && ((x) <= BOTONBITSX+6*LADODEUNBIT+5*ESPACIOENTREBIT) && ((y) >= BOTONBITSY)  && ((y) <= BOTONBITSY+LADODEUNBIT))
#define HITBOXBIT6(x,y) (((x) >= BOTONBITSX+6*(LADODEUNBIT + ESPACIOENTREBIT))  && ((x) <= BOTONBITSX+7*LADODEUNBIT+6*ESPACIOENTREBIT) && ((y) >= BOTONBITSY)  && ((y) <= BOTONBITSY+LADODEUNBIT))
#define HITBOXBIT7(x,y) (((x) >= BOTONBITSX+7*(LADODEUNBIT + ESPACIOENTREBIT))  && ((x) <= BOTONBITSX+8*LADODEUNBIT+7*ESPACIOENTREBIT) && ((y) >= BOTONBITSY)  && ((y) <= BOTONBITSY+LADODEUNBIT))

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
enum keys { KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7,
KEY_Q, KEY_E, KEY_P, KEY_C, KEY_I, KEY_A, KEY_B  
};

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static char puertoSeleccionado = PUERTOA;
static bool mute = 0;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
int mouseChanges(int evMouseX, int evMouseY){
    
    int salida = 0;
    
    if ( HITBOXPA(evMouseX, evMouseY) ){
            puertoSeleccionado = PUERTOA;
    }                          //HITBOX PUERTOA
    else if ( HITBOXPB(evMouseX, evMouseY) ){
            puertoSeleccionado = PUERTOB;
    }        //HITBOX PUERTOB
    else if ( HITBOXBIT0(evMouseX, evMouseY) ){
            bitToggle(puertoSeleccionado, 0);
    }                       //HITBOX BIT0
    else if ( HITBOXBIT1(evMouseX, evMouseY) ){
            bitToggle(puertoSeleccionado, 1);
    }         //HITBOX BIT1
    else if ( HITBOXBIT2(evMouseX, evMouseY) ){
            bitToggle(puertoSeleccionado, 2);            
    }       //HITBOX BIT2
    else if ( HITBOXBIT3(evMouseX, evMouseY) ){
            bitToggle(puertoSeleccionado, 3);            
    }       //HITBOX BIT3
    else if ( HITBOXBIT4(evMouseX, evMouseY) ){
            bitToggle(puertoSeleccionado, 4);            
    }       //HITBOX BIT4
    else if (HITBOXBIT5(evMouseX, evMouseY)){
            bitToggle(puertoSeleccionado, 5);            
    }       //HITBOX BIT5
    else if ( HITBOXBIT6(evMouseX, evMouseY) ){
            bitToggle(puertoSeleccionado, 6);            
    }       //HITBOX BIT6
    else if ( HITBOXBIT7(evMouseX, evMouseY) ){
            bitToggle(puertoSeleccionado, 7);            
    }       //HITBOX BIT7
    else if ( HITBOXC(evMouseX, evMouseY) ){
            maskOff(puertoSeleccionado, 0xFF);            
    }                               //HITBOX BOTONC
    else if ( HITBOXP(evMouseX, evMouseY) ){         //HITBOX BOTONP
            salida = 1;
    } //HITBOX BOTONP
    else if ( HITBOXE(evMouseX, evMouseY) ){
            maskOn(puertoSeleccionado, 0xFF);
    }                               //HITBOX BOTONE
    else if ( HITBOXI(evMouseX, evMouseY) ){
            maskToggle(puertoSeleccionado, 0xFF);
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
                    bitToggle(puertoSeleccionado,0);
                key_pressed[KEY_0] = true;
                break;

            case ALLEGRO_KEY_1:
                if(key_pressed[KEY_1] == false)
                    bitToggle(puertoSeleccionado,1);
                key_pressed[KEY_1] = true;
                break;

            case ALLEGRO_KEY_2:
                if(key_pressed[KEY_2] == false)
                    bitToggle(puertoSeleccionado,2);
                key_pressed[KEY_2] = true;
                break;

            case ALLEGRO_KEY_3:
                if(key_pressed[KEY_3] == false)
                    bitToggle(puertoSeleccionado,3);
                key_pressed[KEY_3] = true;
                break;

            case ALLEGRO_KEY_4:
                if(key_pressed[KEY_4] == false)
                    bitToggle(puertoSeleccionado,4);
                key_pressed[KEY_4] = true;
                break;

            case ALLEGRO_KEY_5:
                if(key_pressed[KEY_5] == false)
                    bitToggle(puertoSeleccionado,5);
                key_pressed[KEY_5] = true;
                break;

            case ALLEGRO_KEY_6:
                if(key_pressed[KEY_6] == false)
                    bitToggle(puertoSeleccionado,6);
                key_pressed[KEY_6] = true;
                break;

            case ALLEGRO_KEY_7:
                if(key_pressed[KEY_7] == false)
                    bitToggle(puertoSeleccionado,7);
                key_pressed[KEY_7] = true;
                break;

            case ALLEGRO_KEY_Q:
                if(key_pressed[KEY_Q] == false)
                    salida=2;
                key_pressed[KEY_Q] = true;
                break;

            case ALLEGRO_KEY_E:
                if(key_pressed[KEY_E] == false)
                    maskOn(puertoSeleccionado,255);
                key_pressed[KEY_E] = true;
                break;

            case ALLEGRO_KEY_P:
                key_pressed[KEY_P] = true;
                salida=1;
                break;

            case ALLEGRO_KEY_C:
                if(key_pressed[KEY_C] == false)
                    maskOff(puertoSeleccionado,255);
                key_pressed[KEY_C] = true;
                break;

            case ALLEGRO_KEY_I:
                if(key_pressed[KEY_I] == false)
                    maskToggle(puertoSeleccionado,255);
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
    puertoSeleccionado = puerto;
}

char getSelectedPort(void){
    return puertoSeleccionado;
}

void setMute(bool modo){
    mute = modo;
}

bool getMute(void){
    return mute;
}
