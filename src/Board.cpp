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

#include <Board.hpp>
#include <sstream>
#include <iostream>
#include <random>
#include <vector>

using namespace LocalSearch;

/**
 * Creates a new board
 */
LocalSearch::Board::Board(unsigned int numRowsCols) : numRows(numRowsCols), numCols(numRowsCols) {
	data = new bool[numRows * numCols];

	for (unsigned int i = 0; i < numRows * numCols; i++) {
		data[i] = false;
	}
}

/**
 * Copy constructor
 */
LocalSearch::Board::Board(const Board& other) : numRows(other.numRows), numCols(other.numCols), h(other.h) {
	data = new bool[numRows * numCols];
	for (unsigned int i = 0; i < numCols * numRows; i++)
		data[i] = other.data[i];
}

/**
 * Frees resources
 */
LocalSearch::Board::~Board() {
	delete[] data;
}

/**
 * Gets the data at a position
 * 
 * @throws A string if the index/indices are out of bounds
 * @param x The x position
 * @param y The y position
 * @returns A reference to the data at the position
 */
inline bool& LocalSearch::Board::getData(unsigned int x, unsigned int y) {
	return data[y * numRows + x];
}

/**
 * Gets the data at a position
 * 
 * @throws A string if the index/indices are out of bounds
 * @param x The x position
 * @param y The y position
 * @returns A reference to the data at the position
 */
inline const bool& LocalSearch::Board::getData(unsigned int x, unsigned int y) const {
	return data[y * numRows + x];
}

/**
 * Prints the board to the console
 */
void LocalSearch::Board::printBoard() const {
	std::stringstream outStr;
	for (unsigned int x = 0; x < numRows; x++) {
		for (unsigned int y = 0; y < numCols; y++) {
			outStr << (getData(y, x) ? "1 " : "0 ");
		}
		outStr << std::endl;
	}
	std::cout << outStr.str();
}

/**
 * Helper method to get a random number in a range
 */
static unsigned int randomNum(unsigned int min, unsigned int max) {
	std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<> distr(min, max);

	return static_cast<unsigned int>(distr(generator));
}

/**
 * Randomizes the board
 */
void LocalSearch::Board::randomize() {
	for (unsigned int i = 0; i < numRows * numCols; i++) {
		data[i] = false;
	}

	for (unsigned int y = 0; y < numCols; y++) {
		unsigned int x = randomNum(0, numRows-1);
		getData(x, y) = true;
	}
}

/**
 * Swaps two locations on the board
 * 
 * @param a The first position to swap
 * @param b The second position to swap 
 */
void LocalSearch::Board::swapLocations(const Loc<unsigned int>& a, const Loc<unsigned int>& b) {
	const bool temp = getData(a.x, a.y);
	getData(a.x, a.y) = getData(b.x, b.y);
	getData(b.x, b.y) = temp;
}

/**
 * Cost function for the board
 */
unsigned int LocalSearch::Board::numAttackingQueens() const {
	std::vector<Loc<unsigned int>> locs;

	for (unsigned int row = 0; row < numRows; row++)
		for (unsigned int col = 0; col < numCols; col++)
			if (getData(col, row))
				locs.push_back({col, row});

	unsigned int result = 0;

	for (const Loc<unsigned int>& loc : locs) {
		std::vector<const Loc<unsigned int>*> others;
		others.reserve(locs.size() - 1);

		for (const Loc<unsigned int>& loc2 : locs)
			if (loc != loc2)
				others.push_back(&loc2);
		
		unsigned int count = 0;

		for (const Loc<unsigned int>*& otherPtr : others) {

			const Loc<unsigned int>& other = *otherPtr;
			Loc<int> difference = {
				static_cast<int>(other.x) - static_cast<int>(loc.x),
				static_cast<int>(other.y) - static_cast<int>(loc.y)
			};

			if (loc.x == other.x || loc.y == other.y || abs(difference.x) == abs(difference.y))
				count += 1;
		}

		result += count;
	}

	return result;
}

/**
 * Move any queen to another square in the same column
 * successors all the same
 * 
 * @returns Successor states (All states are heap allocated)
 */
std::vector<Board*> LocalSearch::Board::getSuccessorStates() const {
	std::vector<Board*> result;

	for (unsigned int row = 0; row < numRows; row++) {
		// Get the column the queen is on in this row
        // [0] because list comprehension returns a list, even if only one element
        // This line will crash if the board has not been initialized with rand() or some other method
		unsigned int i_queen;

		for (unsigned int col = 0; col < numCols; col++)
			if (getData(col, row))
				i_queen = col;

		for (unsigned int col = 0; col < numCols; col++) {
			if (!getData(col, row)) {
				Board* boardTemp = new Board(*this); // Explicitly call copy constructor to heap allocate
				boardTemp->swapLocations({col, row}, {i_queen, row});
				result.push_back(boardTemp);
			}
		}
	}

	return result;
}