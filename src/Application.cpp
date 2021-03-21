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

#include <Application.hpp>
#include <array>
#include <tuple>
#include <iostream>
#include <random>
#include <cmath>

using namespace LocalSearch;

/**
 * Euler's number
 */
static const double e = std::exp(1.0);

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
 * Performs the simulated annealing algorithm
 * 
 * @param initBoard the initial board
 * @param decayRate the decay rate
 * @param T_Threshold The t threshold to reteurn at
 * @returns The solution to the program
 */
Board* LocalSearch::Application::simulatedAnnealing(const Board& initBoard, double decayRate, double T_Threshold) const {
	double T = 100.0;

	Board* current = new Board(initBoard);
	current->h = static_cast<double>(current->numAttackingQueens());

	while (current->h != 0.0) {
		T = T * decayRate;
		if (T <= T_Threshold)
			return current;
		std::vector<Board*> successors = current->getSuccessorStates();
		Board* next = getRandom(successors);
		next->h = static_cast<double>(next->numAttackingQueens());
		double delta = current->h - next->h;
		bool successorChosen = false;
		if (delta > 0) {
			Board* temp = current;
			current = next;
			delete temp;
			successorChosen = true;
		}
		else {
			double prob = 100.0 * pow(e, delta / T);
			unsigned int rand_num = randomNum(1, 100);
			if (static_cast<double>(rand_num) < prob) {
				Board* temp = current;
				current = next;
				delete temp;
				successorChosen = true;
			}
		}
		// Free resources
		for (Board* successor : successors) {
			if (successorChosen && successor == next)
				continue;
			else
				delete successor;
		}
	}

	return current;
}

/**
* Gets a random successor from the list
* 
* @param successors The list of all available successors
* @returns The chosen successor
*/
Board* LocalSearch::Application::getRandom(const std::vector<Board*>& successors) const {
	return successors[randomNum(0, successors.size()-1)];
}

/**
 * Runs the application
 */
void LocalSearch::Application::run() const {
	std::array<std::tuple<double, double>, 3> settings = {
		std::tuple<double, double>(0.9, 0.000001),
		std::tuple<double, double>(0.75, 0.0000001),
		std::tuple<double, double>(0.5, 0.00000001)
	};

	std::array<unsigned int, 4> boardSizes = {4, 8, 16, 32};

	for (const unsigned int& boardSize : boardSizes) {
		std::cout << std::endl << "##################################################################" << std::endl;
		std::cout << "Now running simulations for board size of " << boardSize << std::endl;
		std::cout << "##################################################################" << std::endl;

		for (const std::tuple<double, double>& setting : settings) {
			double decayRate = std::get<0>(setting);
			double tThreshold = std::get<1>(setting);

			std::cout << std::endl << "Now running simulations for Decay Rate of " << decayRate
				<< " and T Threshold of " << tThreshold << std::endl << std::endl;
			
			double avgH = 0.0;

			for (int i = 1; i <= 10; i++) {
				Board board(boardSize);
				board.randomize();
				std::cout << "Simulation number " << i << " with initial H = "
					<< board.numAttackingQueens() << " - Initial State:" << std::endl;
				board.printBoard();

				Board* final = simulatedAnnealing(board, decayRate, tThreshold);
				std::cout << "Final state of (H = " << final->h << "):" << std::endl;
				avgH += final->h / 10;
				final->printBoard();
				std::cout << std::endl;
			}

			std::cout << "Average H value of final solutions throughout 10 runs is " << avgH << std::endl;
		}
	}
}