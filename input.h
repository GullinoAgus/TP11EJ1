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
#define LADODEUNBIT 37
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

enum keys { KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7,
KEY_Q, KEY_E, KEY_P, KEY_C, KEY_I, KEY_A, KEY_B  
};

int mouseChanges(int evMouseX, int evMouseY, ALLEGRO_SAMPLE* click);
int keyboardChanges (bool accion, int tecla);
void setSelectedPort(char puerto);
char getSelectedPort(void);
void setMute(bool modo);
bool getMute(void);


#endif /* INPUT_H */

