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

#include <Board.hpp>
#include <fstream>

/**
 * Main namespace for local search related code
 */
namespace LocalSearch {

	/**
	 * Main application class
	 */
	class Application {

	private:

		/**
		 * Performs the simulated annealing algorithm
		 * 
		 * @param initBoard the initial board
		 * @param decayRate the decay rate
		 * @param T_Threshold The t threshold to reteurn at
		 * @returns The solution to the program
		 */
		Board* simulatedAnnealing(const Board& initBoard, double decayRate, double T_Threshold) const;
		
		/**
		 * Gets a random successor from the list
		 * 
		 * @param successors The list of all available successors
		 * @returns The chosen successor
		 */
		Board* getRandom(const std::vector<Board*>& successors) const;

	public:

		/**
		 * Runs the application
		 */
		void run() const;
	};
}