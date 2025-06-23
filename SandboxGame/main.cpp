#include <DarkMatter/DarkMatter.h>

int main(int argc, char** argv)
{
   DarkMatter::Game::BaseGame* game = new DarkMatter::Game::BaseGame();
   game->run();
   delete game;

   return 0;
}