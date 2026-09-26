#pragma once

enum { BUFFER_SIZE = 5, DECIMAL_BASE = 10 };

/**
 * Read in a small integer from the user.
 *
 * Read a maximum of three characters (plus a newline) from the user, and
 * convert this into an integer. This integer cannot be 0, and due to the
 * maximum of three characters, the integer is expected to be between -99 and
 * 999, inclusive (other than 0). Write the integer into a location
 * provided by the caller, and return a 1 or 0 to indicate success or failure.
 * If the function fails for any reason, the contents of the output are
 * undefined.
 *
 * @param output The location to write the user-provided integer to.
 * @return 1 if the integer was successfully read and 0 otherwise.
 */
int read_int(int* output);
