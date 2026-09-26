#pragma once

// Set the maximum input size that shout can read.
enum { BUFFER_SIZE = 32 };

/**
 * Reprint a line from stdin with lowercase letters replaced by uppercase.
 *
 * Read a single line from stdin, up to a maximum of BUFFER_SIZE characters.
 * Reprint that line (up to the maximum read characters) to stdout, but with all
 * lowercase characters replaced with their uppercase equivalents.
 *
 * The term "lowercase characters" here refers to the letters a through z in the
 * English alphabet; lowercase characters with diacritic marks or in other
 * languages are not included.
 */
void shout(void);
