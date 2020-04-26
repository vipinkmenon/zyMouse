/*
 * zyMouse.h
 *
 *  Created on: Apr 25, 2020
 *      Author: VIPIN
 */

#ifndef SRC_ZYMOUSE_H_
#define SRC_ZYMOUSE_H_

#include "xil_types.h"
#include "xscugic.h"

#define ControlRegOffset 0
#define IntrStatRegOffset 4
#define IntrEnableRegOffset 8
#define posRegOffset 12
#define maxCountRegOffset 16
#define maxCoordinateRegOffset 20

#define ButtonPressInterruptMask 1
#define MotionInterruptMask 2
#define AllInterruptMask 3

#define pressHandler 0
#define moveHandler 1

typedef void (*myCallBack) (void *callBack);

typedef struct{
	u32 baseAddress;
	myCallBack moveCallBack; //one style of declaring member function pointer
	void (*pressCallBack)(void *callBack);//one style of declaring member function pointer

}zyMouse;

int initZyMouse(zyMouse* zyMouseInst,u32 baseAddress);
void setInterruptZyMouse(zyMouse* zyMouseInst,u32 interruptMask);
void setCoordinateZyMouse(zyMouse* zyMouseInst,u32 cord);
void setTimerZymouse(zyMouse* zyMouseInst,u32 timerValue);
void startZymouse(zyMouse* zyMouseInst);
u32 setupZymouseInterrupt(zyMouse *zyMouseInst, XScuGic *IntcInstancePtr,u32 IRQ);
u32 setZymouseCallBack(zyMouse *zyMouseInst,u32 HandlerType,void (*callBackFunc)(void *callBackRef));
#endif /* SRC_ZYMOUSE_H_ */
