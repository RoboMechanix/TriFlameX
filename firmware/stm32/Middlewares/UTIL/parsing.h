#ifndef PARSING_H
#define PARSING_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"

float parse_distance_message(const char *msg);
MOVECOMMAND parse_command_message(const char *msg);

#endif
