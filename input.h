/***************************************************************************//**
  @file     +emulador.h+
  @brief    +Header del modulo emulador de puerto de un microcontrolador.+
  @author   +Grupo 1+
 ******************************************************************************/

#ifndef INPUT_H
#define INPUT_H

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "emulador.h"
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define PRESSED 1
#define NOPRESSED 0
#define CANTTEXTURAS 24

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

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
enum keys { KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7,
KEY_Q, KEY_E, KEY_P, KEY_C, KEY_I, KEY_A, KEY_B  
};

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

int mouseChanges(bool estado, int evMouseX, int evMouseY);
/**
 * @brief mouseChanges es la funcion encargada de procesar la informacion que viene del mouse, para saber detectar cual de las teclas se presiono 
 * @param evMouseX, es la coordenada del mouse en el eje X del momento que se clickeo
 * @param evMouseY, es la coordenada del mouse en el eje Y del momento que se clickeo
 * @return retorna 1 si se presiono la tecla P , retorna 2 si se presiono la tecla Q, y retorna 0 en cualquier otro caso
*/
int keyboardChanges (bool estado, int tecla);
/**
 * @brief keyboardChanges es la funcion encargada de manejar los eventos de teclado y realizar las acciones correspondientes
 * @param estado, es el estado de la tecla: PRESSED o NOPRESSED
 * @param tecla, es el evento de teclado correspondiente a una tecla en particular
 * @return retorna 2 si se presionó la tecla Q, retorna 1 si se presionó la tecla P, en cualquier otro caso retorna 0.
*/
void setSelectedPort(char puerto);
/**
 * @brief setSelectedPort cambia el puerto principal sobre el que se realizan cambios
 * @param  puerto, es el nuevo puerto a seleccionar
 * @return no se devuelve ningun parametro
*/
char getSelectedPort(void);
/**
 * @brief getSelectedPort devuelve el nombre del puerto principal sobre el que se realizan cambios
 * @return devuelve el nobre del puerto: PUERTOA o PUERTOB
*/
void setMute(bool modo);
/**
 * @brief 
 * @param 
 * @return 
*/
bool getMute(void);
/**
 * @brief 
 * @return 
*/

bool getKeyState(int boton);
/**
 * @brief getKeyState devuelve esl estado actual de una tecla
 * @param boton, tecla de la que se quiere saber el estado (KEY_1, etc.)
 * @return devuelve el estado de la tecla: PRESSED o NOPRESSED
*/

#endif /* INPUT_H */

