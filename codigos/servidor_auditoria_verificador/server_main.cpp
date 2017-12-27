#include <iostream>
#include <string>
#include <stdlib.h>
#include "json.hpp"
#include <stdio.h>
#include <string.h>
#include "Game.h"


int main ( int argc, char** argv ){   
	Game* game = new Game(atoi(argv[1]));
    return 0;
}
