"""
Model for 2048 in-line game.
"""

import numpy as np
import random

class Board:  
    """
    Board for 2048 with basic implementation.
    """  
    def __init__(self):
        self.board = np.zeros((4, 4), dtype=int)
        self.score = 0
        self.add_random_tile()
        self.add_random_tile()

    def copy(self):
        """
        Returns a complete copy of the current board state
        """
        board_copy = Board()
        board_copy.board = self.board.copy()
        board_copy.score = self.score
        return board_copy


    def add_random_tile(self):
        """
        Adds a random tile to the 2048 board.

        There is a 90% chance to generate a 2 and a 10% chance to generate a 4.
        """
        # Create an array containing the coordinates of the blank tiles
        empty_tiles = []
        for r in range(4):
            for c in range(4): 
                if self.board[r, c] == 0:
                    empty_tiles.append((r, c))
        if empty_tiles:
            r, c = random.choice(empty_tiles)

            # 90% chance to generate a 2, 10% change of 4
            tile_prob = random.random()
            if tile_prob < 0.9:
                self.board[r, c] = 2
            else: 
                self.board[r, c] = 4

    def left_pressed(self):
        """
        Shifts board over to the left, completing all merges where necessary.
        """
        for r in range(4):
            row = self.board[r]
            row = row[row != 0] # Remove/ignore zeros

            # Merge adjacent tiles with the same value
            for c in range(len(row) - 1):
                if row[c] == row[c + 1]:
                    row[c] *= 2
                    self.score += row[c]
                    row[c + 1] = 0
            self.board[r] = np.append(row[row != 0], [0] * (4 - len(row[row != 0])))

    def right_pressed(self):
        """
        Shifts board over to the right, completing all merges where necessary.
        """
        for r in range(4):
            # Reverses row & implements left shift function
            row = self.board[r][::-1]
            row = row[row != 0] # Remove/ignore zeros
            for c in range(len(row) - 1):
                if row[c] == row[c + 1]:
                    row[c] *= 2
                    self.score += row[c]
                    row[c + 1] = 0
            # Reverses row back when adding updates to the board
            self.board[r] = np.append(row[row != 0], [0] * (4 - len(row[row != 0])))[::-1]

    def up_pressed(self):
        """
        Shifts board up, completing all merges where necessary.
        """
        # Transposes board & handles it like a left direction
        self.board = self.board.T
        self.left_pressed()
        self.board = self.board.T

    def down_pressed (self): 
        """
        Shifts board down, completing all merges where necessary.
        """
        # Transposes board & handles it like a right direction
        self.board = self.board.T
        self.right_pressed()
        self.board = self.board.T

    def move(self, direction):
        """
        Depending on the given direction, moves the tiles to match.

        Args:
            direction = A string representing the direction to shift the tiles
                in.

        Returns:
            True if move was successful; otherwise, False.
        """
        match(direction):
            case 'w':
                self.up_pressed()
            case 'a':
                self.left_pressed()
            case 's': 
                self.down_pressed()
            case 'd':
                self.right_pressed()
            case default:
                return False
        return True

    def has_valid_moves(self):
        """
        Checks if there are any valid moves on the board.

        Returns: 
            True if there are more valid moves; otherwise, False.
        """
        if 0 in self.board:
            return True
        for r in range(4):
            for c in range(4):
                # Checks if any row merges can be done
                if (r > 0 and self.board[r, c] == self.board[r-1, c]):
                    return True
                # Checks if any column merges can be done
                if (c > 0 and self.board[r, c] == self.board [r, c-1]):
                    return True
        return False

    def play_turn(self, direction):
        """
        Completes a turn, given a direction.

        Args:
            direction = A string representing the direction to shift the tiles
                in.
        Returns:
            True if move is valid; otherwise, False.
        """
        new_board = self.board.copy()

        # Skip invalid move
        if not self.move(direction):
            return False
        
        # Only add tile if board changes
        if not np.array_equal(new_board, self.board):
            self.add_random_tile()
        return True

    def display(self):
        """
        Displays the current state of the game, including the score and the
        board.
        """
        print(f"Score: {self.score}")
        print(self.board)

def run_2048():
    """
    Main game loop for the 2048 game; runs until there are no more valid moves.
    """
    game = Board()
    while True:
        game.display()
        if not game.has_valid_moves():
            print("Final Score: ", game.score)
            break
        move_direction = input("Enter move (w, a, s, or d): ").strip().lower()
        if move_direction not in ['w', 'a', 's', 'd']:
            print("Invalid move. Use w (up), a (left), s (down), d (right).")
            continue
        if not game.play_turn(move_direction):
            print("Invalid move; try again.")

if __name__ == "__main__":
    run_2048()
