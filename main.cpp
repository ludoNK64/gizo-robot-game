#include <iostream>
#include <exception>
#include <cstdlib>

#include "Game.h"

using namespace std;

int main(int argc, char *argv[])
{
    try 
    {
        Game::init();
        Game::mainloop();
        Game::quit();
    }
    catch(const exception& e)
    {
        cerr << e.what() << endl;
        Game::quit();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
