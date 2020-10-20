#include <iostream>
#include <memory>

#include "MatchGame.h"


int main(int argc, char* argv[]) {

	std::unique_ptr<MatchGame> game (new MatchGame); 

	if (!game->Init()){
		
		std::cout << "Error launching matchgame!" << std::endl;
		return 0;
	}

	return game->Run();

}