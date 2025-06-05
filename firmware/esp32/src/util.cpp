#include "util.h"

// Thread-safe setter for go_command
void setGoCommand(bool value) {
    xSemaphoreTake(xSharedDataMutex, portMAX_DELAY);
    go_command = value;
    xSemaphoreGive(xSharedDataMutex);
}

// Thread-safe getter for go_command
bool getGoCommand() {
    xSemaphoreTake(xSharedDataMutex, portMAX_DELAY);
    bool value = go_command;
    xSemaphoreGive(xSharedDataMutex);
    return value;
}