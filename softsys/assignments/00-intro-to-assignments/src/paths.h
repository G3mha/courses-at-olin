/**
 * Select a path from Olin.
 */
#pragma once

/**
 * Print a message based on a given numerical choice.
 * 
 * Given an integer, print the following different messages. If the selection is
 * 1, print "You go left. You end up in downtown Needham." If the selection is
 * 2, print "You go right. You end up at the Wellesley dump." If the selection
 * is 3, print "You go straight. You end up in a strangely quiet Needham
 * street." For any other selection, print "Choices are hard. You go back to
 * campus."
 * 
 * @param selection An integer representing the path selected.
 */
void select_path(int selection);
