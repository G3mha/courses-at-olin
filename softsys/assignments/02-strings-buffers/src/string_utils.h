/**
 * String utilities similar to functions offered in Python.
 */
#pragma once

#include <string.h>

static const char WHITESPACE[] = " \f\n\r\t\v";

/**
 * Replace this line with your documentation comment.
 */
int startswith(const char* str, const char* substr);

/**
 * Replace this line with your documentation comment.
 */
int endswith(const char* str, const char* substr);

/**
 * Replace this line with your documentation comment.
 */
size_t count(const char* str, const char* substr);

/**
 * Strip a set of characters from the start and end of a string.
 *
 * Given a source string, destination buffer, and set of characters to strip
 * from the start (left) and end (right) of the string, write a copy of the
 * source string with the appropriate characters removed into the destination
 * buffer. If the set of characters to strip is empty, the string is copied into
 * the destination buffer as is. If the set of characters to strip is the null
 * pointer, whitespace characters (i.e., those that would be considered by
 * isspace in strings.h) are stripped instead.
 *
 * Both the source string and destination buffer are assumed to be non-null
 * pointers, and the source string is assumed to be null-terminated. If
 * non-null, the set of characters to strip is also assumed to be
 * null-terminated. The destination buffer is assumed to be large enough to hold
 * the stripped copy of the source string, and is guaranteed to be a
 * null-terminated (but possibly empty) string after the function runs.
 *
 * @param src The string to strip (null-terminated, cannot be NULL).
 * @param dst A buffer to write the stripped copy of src to (cannot be NULL).
 * @param chars The characters to strip (null-terminated).
 */
void strip(const char* src, char* dst, const char* chars);

/**
 * Split a string into substrings based on a given delimiter.
 *
 * Given a source string, destination array, and string representing a
 * delimiter, "split" the source string by the delimiter and copy the resulting
 * substrings into the destination array, in order. The delimiter must be a
 * nonempty string, or NULL. In the latter case, split the source string using
 * any consecutive whitespace (with whitespace determined by isspace in
 * strings.h).
 *
 * The source string is assumed to be a non-null pointer, and the destination
 * array is assumed to be large enough to hold all substrings (in both
 * dimensions), plus a terminating null pointer to indicate the end of the
 * array. After the function runs, the destination array is guaranteed to end
 * with a null pointer, and each entry in the array is guaranteed to be a
 * null-terminated string (with the exception of the terminating null pointer).
 *
 * @param src The string to split (null-terminated, non-NULL).
 * @param dst An array of strings to write the split strings into (non-NULL).
 * @param sep The split delimiter (non-empty and null-terminated, or NULL).
 */
void split(const char* src, char* dst[], const char* sep);
