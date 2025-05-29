#ifndef TYPES_H
#define TYPES_H
#include"stm32f103xb.h"

typedef enum {
    CMD_NONE, GO, STOP
} MOVECOMMAND;

typedef enum {
    MSG_NONE, MSG_COMMAND_DISTANCE, MSG_ANGLE
} MessageType;

typedef struct {
	MessageType type;
	uint16_t distance;
    int command; // 0 = STOP, 1 = GO
    int angle;   // signed angle (-127 to 127)
} UARTMessage;


#endif
