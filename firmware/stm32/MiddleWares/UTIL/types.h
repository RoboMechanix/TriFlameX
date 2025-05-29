#ifndef TYPES_H
#define TYPES_H

typedef enum {
    CMD_NONE, GO, STOP
} MOVECOMMAND;

typedef enum {
    MSG_NONE, MSG_DISTANCE, MSG_COMMAND
} MessageType;

typedef struct {
	MessageType type;
    float distance;
    int command; // 0 = STOP, 1 = GO
} UARTMessage;


#endif
