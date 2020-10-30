/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mouse.h
 * Author: damian
 *
 * Created on 29 de octubre de 2020, 19:22
 */

#ifndef MOUSE_H
#define MOUSE_H

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

int mouseChanges(int evMouseX, int evMouseY, ALLEGRO_SAMPLE* click);
void setSelectedPort(char puerto);
char getSelectedPort(void);
void setMute(bool modo);
bool getMute(void);
//DEVUELVE 0 SI HACE EL CAMBIO SIN HACER NADA
//DEVUELVE 1 SI PONE A PARPADEAR A LOS BITS
//DEVUELVE 2 SI TERMINA EL PROGRAMA

#endif /* MOUSE_H */

