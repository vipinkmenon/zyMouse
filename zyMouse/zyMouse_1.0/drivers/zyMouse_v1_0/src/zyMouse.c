/*
 * zyMouse.c
 *
 *  Created on: Apr 25, 2020
 *      Author: VIPIN
 */
#include "zyMouse.h"
#include "xil_io.h"

static void Mouse_Handler(void *CallBackRef);

int initZyMouse(zyMouse *zyMouseInst,u32 baseAddress){
	zyMouseInst->baseAddress = baseAddress;
	return 0;
}

void setInterruptZyMouse(zyMouse* zyMouseInst,u32 interruptMask){
	Xil_Out32(zyMouseInst->baseAddress+IntrEnableRegOffset,interruptMask);//enable interrupts
}

void setCoordinateZyMouse(zyMouse* zyMouseInst,u32 cord){
	Xil_Out32(zyMouseInst->baseAddress+maxCoordinateRegOffset,cord);
}


void setTimerZymouse(zyMouse* zyMouseInst,u32 timerValue){
	Xil_Out32(zyMouseInst->baseAddress+maxCountRegOffset,timerValue);
}

void startZymouse(zyMouse* zyMouseInst){
	Xil_Out32(zyMouseInst->baseAddress,1);
	Xil_Out32(zyMouseInst->baseAddress,0);
}


u32 setupZymouseInterrupt(zyMouse *zyMouseInst, XScuGic *IntcInstancePtr,u32 IRQ){
	u32 Status;
	XScuGic_SetPriorityTriggerType(IntcInstancePtr,IRQ,0xA0,3);
	Status = XScuGic_Connect(IntcInstancePtr,IRQ,(Xil_InterruptHandler)Mouse_Handler,zyMouseInst);
	if (Status != XST_SUCCESS) {
		xil_printf("Failed read channel connect intc %d\r\n", Status);
		return XST_FAILURE;
	}
	XScuGic_Enable(IntcInstancePtr,IRQ);
	return XST_SUCCESS;
}

static void Mouse_Handler(void *CallBackRef){
	u32 status;
	zyMouse* zyMouseInst;
	zyMouseInst = (zyMouse*)CallBackRef;
	status = Xil_In32(zyMouseInst->baseAddress+IntrStatRegOffset);
	xil_printf("%d\n\r",status);
	if(status&0x1){
		xil_printf("Mouse pressed\n\r");
		zyMouseInst->pressCallBack(zyMouseInst);
	}
	if(status&0x2){
		xil_printf("Mouse moved\n\r");
		zyMouseInst->moveCallBack(zyMouseInst);
	}
	Xil_Out32(zyMouseInst->baseAddress+IntrStatRegOffset,status);//Clear the interrupt bits
}

u32 setZymouseCallBack(zyMouse *zyMouseInst,u32 HandlerType,void (*callBackFunc)(void *callBackRef)){
	if(HandlerType == pressHandler)
		zyMouseInst->pressCallBack = callBackFunc;
	else if(HandlerType == moveHandler)
		zyMouseInst->moveCallBack = callBackFunc;
	else
		return XST_FAILURE;
	return XST_SUCCESS;
}
