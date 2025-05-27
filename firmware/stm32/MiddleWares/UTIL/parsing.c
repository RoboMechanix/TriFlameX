#include "parsing.h"


/*float parse_distance_message(const char *msg) {
    // Expected format: "Distance: 123.45 cm"
    const char *prefix = "Distance: ";
    const char *suffix = " cm";

    if (strncmp(msg, prefix, strlen(prefix)) == 0) {
        const char *number_start = msg + strlen(prefix);
        char *cm_pos = strstr(number_start, suffix);

        if (cm_pos != NULL) {
            char number_str[16];
            size_t len = cm_pos - number_start;
            if (len < sizeof(number_str)) {
                strncpy(number_str, number_start, len);
                number_str[len] = '\0';
               return atof(number_str);  // Convert to float
            }
        }
    }
    return 0.9f;
}
*/
MOVECOMMAND parse_command_message(const char *msg) {
	if (strcmp(msg, "GO") == 0) return GO;
	if (strcmp(msg, "STOP") == 0) return STOP;
	return CMD_NONE;
}
