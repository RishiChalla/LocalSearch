/*
   Copyright 2021 Rishi Challa

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#pragma once

#include <vector>

/**
 * Main namespace for local search related code
 */
namespace LocalSearch {

	/**
	 * Simple position structure
	 */
	template <typename T> struct Loc {

		/**
		 * The x position
		 */
		T x;

		/**
		 * The y position
		 */
		T y;
	};

	/**
	 * Operator for checking equality
	 * 
	 * @param other Loc to check for equality
	 * @returns Whether or not the two are equal
	 */
	template <typename T> bool operator==(const Loc<T>& first, const Loc<T>& second) {
		return first.x == second.x && first.y == second.y;
	}

	/**
	 * Operator for checking equality
	 * 
	 * @param other Loc to check for equality
	 * @returns Whether or not the two are not equal
	 */
	template <typename T> bool operator!=(const Loc<T>& first, const Loc<T>& second) {
		return first.x != second.x || first.y != second.y;
	}

	/**
	 * Main board class
	 */
	class Board {
	private:

		/**
		 * The number of rows in the grid
		 */
		unsigned int numRows;

		/**
		 * The number of columns in the grid
		 */
		unsigned int numCols;

		/**
		 * Pointer to raw heap allocated condensed memory
		 * Size of memory will always be (numRows * numCols)
		 */
		bool* data;

		/**
		 * Gets the data at a position
		 * 
		 * @throws A string if the index/indices are out of bounds
		 * @param x The x position
		 * @param y The y position
		 * @returns A reference to the data at the position
		 */
		inline bool& getData(unsigned int x, unsigned int y);

		/**
		 * Gets the data at a position
		 * 
		 * @throws A string if the index/indices are out of bounds
		 * @param x The x position
		 * @param y The y position
		 * @returns A reference to the data at the position
		 */
		inline const bool& getData(unsigned int x, unsigned int y) const;

	public:

		/**
		 * Negative value for initial h to check whether unset
		 */
		double h = -1;

		/**
		 * Creates a new board
		 */
		Board(unsigned int numRowsCols);

		/**
		 * Copy constructor
		 */
		Board(const Board& other);

		/**
		 * Frees resources
		 */
		~Board();

		/**
		 * Prints the board to the console
		 */
		void printBoard() const;

		/**
		 * Randomizes the board
		 */
		void randomize();

		/**
		 * Swaps two locations on the board
		 * 
		 * @param a The first position to swap
		 * @param b The second position to swap 
		 */
		void swapLocations(const Loc<unsigned int>& a, const Loc<unsigned int>& b);

		/**
		 * Cost function for the board
		 */
		unsigned int numAttackingQueens() const;

		/**
		 * Move any queen to another square in the same column
		 * successors all the same
		 * 
		 * @returns Successor states (All states are heap allocated)
		 */
		std::vector<Board*> getSuccessorStates() const;
	};
}