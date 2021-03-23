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
#include <sstream>
#include <iostream>

int main() {
	using namespace LocalSearch;

	try {
		Application app;
		app.run();
	}
	catch (const char* err) {
		std::stringstream strStream;
		strStream << "Execution of application ended with the following error:" << std::endl;
		strStream << err;
		std::cerr << strStream.str() << std::endl;
	}

	// Avoid window closing for MSVC
	std::cin.get();

	return 0;
}