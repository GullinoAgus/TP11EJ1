/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   input.h
 * Author: grupo1
 *
 * Created on 29 de octubre de 2020, 19:22
 */

#ifndef INPUT_H
#define INPUT_H

#include "emulador.h"
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>


#define CANTTEXTURAS 18
#define CIRCUITOX 20
#define CIRCUITOY 90
#define PUERTOAX 465
#define PUERTOAY 100
#define ANCHOPUERTOA 174
#define ALTOPUERTOA 49
#define BOTONBITSX 488
#define BOTONBITSY 200
#define LADODEUNBIT 35
#define ESPACIOENTREBIT 3
#define BOTONCX 488
#define BOTONCY 280
#define ANCHOBOTC 45
#define ALTOBOTC 49
#define DISTYBOTONESCE 60
#define DISTXBOTONESCE 163
#define LEDSUPX 380
#define LEDSUPY 34
#define LEDSIZE 14
#define MINILEDSUPIZQX 166
#define MINILEDSUPIZQY 38
#define MINILEDSUPDERX 272
#define MINILEDSUPDERY 38
#define MINILEDSIZE 14
#define ANCHODELDISPLAY 850
#define ALTODELDISPLAY  480
#define SOUNDICNX 20
#define SOUNDICNY 20

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


typedef struct{
    
    bool botQ;
    bool botP;
    bool botI;
    bool botE;
    bool botC;
    bool botPortA;
    bool botPortB;
    bool botBits;
    bool botMute;
    
} botones_t;

extern botones_t Botoncitos;

int mouseChanges(int evMouseX, int evMouseY, ALLEGRO_SAMPLE* click);
void setSelectedPort(char puerto);
char getSelectedPort(void);
void setMute(bool modo);
bool getMute(void);


#endif /* INPUT_H */

