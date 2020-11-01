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

#define HITBOX(mx,my,x,xw,y,yh) ((( (x) <= (mx) && (mx) <= (xw) )  && ( (y) <= (my) && (my) <= (yh) ) ) ? 1 : 0)

//BORRAR ANTES DE ENTREGAR

//#define HITBOXP(x,y) (((x) >= BOTONCX + DISTXBOTONESCE)  && ((x) <= BOTONCX + DISTXBOTONESCE+ ANCHOBOTC) && ((y) >= BOTONCY)  && ((y) <= BOTONCY+ALTOBOTC))
//#define HITBOXI(x,y) (((x) >= BOTONCX + DISTXBOTONESCE)  && ((x) <= BOTONCX + DISTXBOTONESCE+ ANCHOBOTC) && ((y) >= BOTONCY + DISTYBOTONESCE)  && ((y) <= BOTONCY + DISTYBOTONESCE+ ALTOBOTC))
//#define HITBOXC(x,y) (((x) >= BOTONCX)  && ((x) <= BOTONCX+ANCHOBOTC) && ((y) >= BOTONCY)  && ((y) <= BOTONCY+ALTOBOTC))
//#define HITBOXE(x,y) (((x) >= BOTONCX)  && ((x) <= BOTONCX+ANCHOBOTC) && ((y) >= BOTONCY + DISTYBOTONESCE)  && ((y) <= BOTONCY + DISTYBOTONESCE+ALTOBOTC))
//#define HITBOXQ(x,y) (((x) >= ANCHODELDISPLAY - DISTYBOTONESCE)  && ((x) <= ANCHODELDISPLAY - DISTYBOTONESCE+ANCHOBOTC) && ((y) >= 10)  && ((y) <= 10+ALTOBOTC))
//#define HITBOXPA(x,y) (((x) >= PUERTOAX) && ((x) <= PUERTOAX+ANCHOPUERTOA) && ((y) >= PUERTOAY)  && ( (y) <= PUERTOAY + ALTOPUERTOA))
//#define HITBOXPB(x,y) (((x) >= PUERTOAX + ANCHOPUERTOA) && ((x) <= PUERTOAX + 2*ANCHOPUERTOA) && ((y) >= PUERTOAY) && ((y) <= PUERTOAY+ALTOPUERTOA))
//#define HITBOXSOUND(x,y) (((x) >= SOUNDICNX)  && ((x) <= (SOUNDICNX + 36) && ((y) >= SOUNDICNY)  && ((y) <= SOUNDICNY + 36)))
//#define HITBOXBIT0(x,y) (((x) >= BOTONBITSX)  && ((x) <= BOTONBITSX+LADODEUNBIT) && ((y) >= BOTONBITSY)  && ((y) <= BOTONBITSY+LADODEUNBIT))
//#define HITBOXBIT1(x,y) (((x) >= BOTONBITSX+LADODEUNBIT+ESPACIOENTREBIT)  && ((x) <= BOTONBITSX+2*LADODEUNBIT + ESPACIOENTREBIT) && ((y) >= BOTONBITSY)  && ((y) <= BOTONBITSY+LADODEUNBIT))
//#define HITBOXBIT2(x,y) (((x) >= BOTONBITSX+2*(LADODEUNBIT + ESPACIOENTREBIT))  && ((x) <= BOTONBITSX+3*LADODEUNBIT+2*ESPACIOENTREBIT) && ((y) >= BOTONBITSY)  && ((y) <= BOTONBITSY+LADODEUNBIT))
//#define HITBOXBIT3(x,y) (((x) >= BOTONBITSX+3*(LADODEUNBIT + ESPACIOENTREBIT))  && ((x) <= BOTONBITSX+4*LADODEUNBIT+3*ESPACIOENTREBIT) && ((y) >= BOTONBITSY)  && ((y) <= BOTONBITSY+LADODEUNBIT))
//#define HITBOXBIT4(x,y) (((x) >= BOTONBITSX+4*(LADODEUNBIT + ESPACIOENTREBIT))  && ((x) <= BOTONBITSX+5*LADODEUNBIT+4*ESPACIOENTREBIT) && ((y) >= BOTONBITSY)  && ((y) <= BOTONBITSY+LADODEUNBIT))
//#define HITBOXBIT5(x,y) (((x) >= BOTONBITSX+5*(LADODEUNBIT + ESPACIOENTREBIT))  && ((x) <= BOTONBITSX+6*LADODEUNBIT+5*ESPACIOENTREBIT) && ((y) >= BOTONBITSY)  && ((y) <= BOTONBITSY+LADODEUNBIT))
//#define HITBOXBIT6(x,y) (((x) >= BOTONBITSX+6*(LADODEUNBIT + ESPACIOENTREBIT))  && ((x) <= BOTONBITSX+7*LADODEUNBIT+6*ESPACIOENTREBIT) && ((y) >= BOTONBITSY)  && ((y) <= BOTONBITSY+LADODEUNBIT))
//#define HITBOXBIT7(x,y) (((x) >= BOTONBITSX+7*(LADODEUNBIT + ESPACIOENTREBIT))  && ((x) <= BOTONBITSX+8*LADODEUNBIT+7*ESPACIOENTREBIT) && ((y) >= BOTONBITSY)  && ((y) <= BOTONBITSY+LADODEUNBIT))


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static char puertoSeleccionado = PUERTOA;
static bool mute = 0;
static bool key_pressed[15];

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
int mouseChanges(bool estado, int evMouseX, int evMouseY){
    
    int salida = 0;
    
    if(estado == PRESSED){
        if ( HITBOX(evMouseX,evMouseY,PUERTOAX,PUERTOAX+ANCHOPUERTOA,PUERTOAY,PUERTOAY + ALTOPUERTOA) ){
                key_pressed[KEY_A] = !key_pressed[KEY_A];
                puertoSeleccionado = PUERTOA;
        }                 //HITBOX PUERTOA
        else if ( HITBOX(evMouseX,evMouseY,PUERTOAX + ANCHOPUERTOA,PUERTOAX + 2*ANCHOPUERTOA,PUERTOAY,PUERTOAY+ALTOPUERTOA) ){
                key_pressed[KEY_B] = !key_pressed[KEY_B];
                puertoSeleccionado = PUERTOB;
        }        //HITBOX PUERTOB
        else if ( HITBOX(evMouseX,evMouseY,BOTONBITSX,BOTONBITSX+LADODEUNBIT,BOTONBITSY,BOTONBITSY+LADODEUNBIT) ){
                key_pressed[KEY_0] = !key_pressed[KEY_0];
                bitToggle(puertoSeleccionado, 0);
        }                       //HITBOX BIT0
        else if ( HITBOX(evMouseX,evMouseY,BOTONBITSX+LADODEUNBIT+ESPACIOENTREBIT,BOTONBITSX+2*LADODEUNBIT + ESPACIOENTREBIT,BOTONBITSY,BOTONBITSY+LADODEUNBIT) ){
                key_pressed[KEY_1] = !key_pressed[KEY_1];
                bitToggle(puertoSeleccionado, 1);
        }      //HITBOX BIT1
        else if ( HITBOX(evMouseX,evMouseY,BOTONBITSX+2*(LADODEUNBIT+ESPACIOENTREBIT),BOTONBITSX+3*LADODEUNBIT+2*ESPACIOENTREBIT,BOTONBITSY,BOTONBITSY+LADODEUNBIT) ){
                key_pressed[KEY_2] = !key_pressed[KEY_2];
                bitToggle(puertoSeleccionado, 2);            
        }  //HITBOX BIT2
        else if ( HITBOX(evMouseX,evMouseY,BOTONBITSX+3*(LADODEUNBIT+ESPACIOENTREBIT),BOTONBITSX+4*LADODEUNBIT+3*ESPACIOENTREBIT,BOTONBITSY,BOTONBITSY+LADODEUNBIT) ){
                key_pressed[KEY_3] = !key_pressed[KEY_3];
                bitToggle(puertoSeleccionado, 3);            
        }   //HITBOX BIT3
        else if ( HITBOX(evMouseX,evMouseY,BOTONBITSX+4*(LADODEUNBIT+ESPACIOENTREBIT),BOTONBITSX+5*LADODEUNBIT+4*ESPACIOENTREBIT,BOTONBITSY,BOTONBITSY+LADODEUNBIT )){
                key_pressed[KEY_4] = !key_pressed[KEY_4];
                bitToggle(puertoSeleccionado, 4);            
        }       //HITBOX BIT4
        else if ( HITBOX(evMouseX,evMouseY,BOTONBITSX+5*(LADODEUNBIT+ESPACIOENTREBIT),BOTONBITSX+6*LADODEUNBIT+5*ESPACIOENTREBIT,BOTONBITSY,BOTONBITSY+LADODEUNBIT)){
                key_pressed[KEY_5] = !key_pressed[KEY_5];
                bitToggle(puertoSeleccionado, 5);            
        }    //HITBOX BIT5
        else if ( HITBOX(evMouseX,evMouseY,BOTONBITSX+6*(LADODEUNBIT+ESPACIOENTREBIT),BOTONBITSX+7*LADODEUNBIT+6*ESPACIOENTREBIT,BOTONBITSY,BOTONBITSY+LADODEUNBIT) ){
                key_pressed[KEY_6] = !key_pressed[KEY_6];
                bitToggle(puertoSeleccionado, 6);            
        }    //HITBOX BIT6
        else if ( HITBOX(evMouseX,evMouseY,BOTONBITSX+7*(LADODEUNBIT+ESPACIOENTREBIT),BOTONBITSX+8*LADODEUNBIT+7*ESPACIOENTREBIT,BOTONBITSY,BOTONBITSY+LADODEUNBIT) ){
                key_pressed[KEY_7] = !key_pressed[KEY_7];
                bitToggle(puertoSeleccionado, 7);            
        }    //HITBOX BIT7
        else if ( HITBOX(evMouseX,evMouseY,BOTONCX,BOTONCX+ANCHOBOTC,BOTONCY,BOTONCY+ALTOBOTC) ){
                key_pressed[KEY_C] = !key_pressed[KEY_C];
                maskOff(puertoSeleccionado, 0xFF);            
        }                               //HITBOX BOTONC
        else if ( HITBOX(evMouseX,evMouseY,BOTONCX + DISTXBOTONESCE,BOTONCX + DISTXBOTONESCE+ ANCHOBOTC,BOTONCY,BOTONCY+ALTOBOTC) ){         //HITBOX BOTONP
                key_pressed[KEY_P] = !key_pressed[KEY_P];
                salida = 1;
        } //HITBOX BOTONP
        else if ( HITBOX(evMouseX,evMouseY,BOTONCX,BOTONCX+ANCHOBOTC,BOTONCY + DISTYBOTONESCE,BOTONCY + DISTYBOTONESCE+ALTOBOTC) ){
                key_pressed[KEY_E] = !key_pressed[KEY_E];
                maskOn(puertoSeleccionado, 0xFF);
        }          //HITBOX BOTONE
        else if ( HITBOX(evMouseX,evMouseY,BOTONCX + DISTXBOTONESCE,BOTONCX + DISTXBOTONESCE+ ANCHOBOTC,BOTONCY + DISTYBOTONESCE,BOTONCY + DISTYBOTONESCE+ ALTOBOTC) ){
                key_pressed[KEY_I] = !key_pressed[KEY_I];
                maskToggle(puertoSeleccionado, 0xFF);
        } //HITBOX BOTONI
        else if ( HITBOX(evMouseX,evMouseY,ANCHODELDISPLAY - DISTYBOTONESCE,ANCHODELDISPLAY - DISTYBOTONESCE+ANCHOBOTC,10,10+ALTOBOTC) ){
                key_pressed[KEY_Q] = !key_pressed[KEY_Q];
                salida = 2;
        } //HITBOX BOTONQ
        else if ( HITBOX(evMouseX,evMouseY,SOUNDICNX,SOUNDICNX+36,SOUNDICNY,SOUNDICNY+36) ){
                mute = !mute;
        } //HITBOX BOTONMUTE
    }
    else{
        for(int i = KEY_0; i <= KEY_B; i++)
        {
            key_pressed[i] = NOPRESSED;
        }
    }

    return salida;
}

int keyboardChanges (bool estado, int tecla){
    
    int salida = 0;
    
    if(estado == PRESSED) {
        switch(tecla) {
            case ALLEGRO_KEY_0:
                if(key_pressed[KEY_0] == NOPRESSED)
                    bitToggle(puertoSeleccionado,0);
                key_pressed[KEY_0] = PRESSED;
                break;

            case ALLEGRO_KEY_1:
                if(key_pressed[KEY_1] == NOPRESSED)
                    bitToggle(puertoSeleccionado,1);
                key_pressed[KEY_1] = PRESSED;
                break;

            case ALLEGRO_KEY_2:
                if(key_pressed[KEY_2] == NOPRESSED)
                    bitToggle(puertoSeleccionado,2);
                key_pressed[KEY_2] = PRESSED;
                break;

            case ALLEGRO_KEY_3:
                if(key_pressed[KEY_3] == NOPRESSED)
                    bitToggle(puertoSeleccionado,3);
                key_pressed[KEY_3] = PRESSED;
                break;

            case ALLEGRO_KEY_4:
                if(key_pressed[KEY_4] == NOPRESSED)
                    bitToggle(puertoSeleccionado,4);
                key_pressed[KEY_4] = PRESSED;
                break;

            case ALLEGRO_KEY_5:
                if(key_pressed[KEY_5] == NOPRESSED)
                    bitToggle(puertoSeleccionado,5);
                key_pressed[KEY_5] = PRESSED;
                break;

            case ALLEGRO_KEY_6:
                if(key_pressed[KEY_6] == NOPRESSED)
                    bitToggle(puertoSeleccionado,6);
                key_pressed[KEY_6] = PRESSED;
                break;

            case ALLEGRO_KEY_7:
                if(key_pressed[KEY_7] == NOPRESSED)
                    bitToggle(puertoSeleccionado,7);
                key_pressed[KEY_7] = PRESSED;
                break;

            case ALLEGRO_KEY_Q:
                if(key_pressed[KEY_Q] == NOPRESSED)
                    salida = 2;
                key_pressed[KEY_Q] = PRESSED;
                break;

            case ALLEGRO_KEY_E:
                if(key_pressed[KEY_E] == NOPRESSED)
                    maskOn(puertoSeleccionado,255);
                key_pressed[KEY_E] = PRESSED;
                break;

            case ALLEGRO_KEY_P:
                key_pressed[KEY_P] = PRESSED;
                salida = 1;
                break;

            case ALLEGRO_KEY_C:
                if(key_pressed[KEY_C] == NOPRESSED)
                    maskOff(puertoSeleccionado,255);
                key_pressed[KEY_C] = PRESSED;
                break;

            case ALLEGRO_KEY_I:
                if(key_pressed[KEY_I] == NOPRESSED)
                    maskToggle(puertoSeleccionado,255);
                key_pressed[KEY_I] = PRESSED;
                break;

            case ALLEGRO_KEY_A:
                if(key_pressed[KEY_A] == NOPRESSED)
                    setSelectedPort(PUERTOA);
                key_pressed[KEY_A] = PRESSED;
                break;

            case ALLEGRO_KEY_B:
                if(key_pressed[KEY_B] == NOPRESSED)
                    setSelectedPort(PUERTOB);
                key_pressed[KEY_B] = PRESSED;
                break;
        }
    }
    else {
 
        for(int i = KEY_0; i <= KEY_B; i++)
        {
            key_pressed[i] = NOPRESSED;
        }
        
        /*
        switch(tecla) {
            case ALLEGRO_KEY_0:
                key_pressed[KEY_0] = NOPRESSED;
                break;

            case ALLEGRO_KEY_1:
                key_pressed[KEY_1] = NOPRESSED;
                break;

            case ALLEGRO_KEY_2:
                key_pressed[KEY_2] = NOPRESSED;
                break;

            case ALLEGRO_KEY_3:
                key_pressed[KEY_3] = NOPRESSED;
                break;

            case ALLEGRO_KEY_4:
                key_pressed[KEY_4] = NOPRESSED;
                break;

            case ALLEGRO_KEY_5:
                key_pressed[KEY_5] = NOPRESSED;
                break;

            case ALLEGRO_KEY_6:
                key_pressed[KEY_6] = NOPRESSED;
                break;

            case ALLEGRO_KEY_7:
                key_pressed[KEY_7] = NOPRESSED;
                break;

            case ALLEGRO_KEY_Q:
                key_pressed[KEY_Q] = NOPRESSED;
                break;

            case ALLEGRO_KEY_E:
                key_pressed[KEY_E] = NOPRESSED;
                break;

            case ALLEGRO_KEY_P:
                key_pressed[KEY_P] = NOPRESSED;
                break;

            case ALLEGRO_KEY_C:
                key_pressed[KEY_C] = NOPRESSED;
                break;

            case ALLEGRO_KEY_I:
                key_pressed[KEY_I] = NOPRESSED;
                break;

            case ALLEGRO_KEY_A:
                key_pressed[KEY_A] = NOPRESSED;
                break;

            case ALLEGRO_KEY_B:
                key_pressed[KEY_B] = NOPRESSED;
                break;
        }*/
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

bool getKeyState(int boton){
    return key_pressed[boton];
}

bool getMute(void){
    return mute;
}
