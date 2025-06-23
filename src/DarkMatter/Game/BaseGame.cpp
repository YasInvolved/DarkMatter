#include <DarkMatter/Game/BaseGame.h>
#include <SDL3/SDL.h>

using BaseGame = DarkMatter::Game::BaseGame;

BaseGame::BaseGame()
   : m_window()
{

}

BaseGame::~BaseGame()
{

}

void BaseGame::run()
{
   while (m_isRunning)
   {
      SDL_Event event;
      while (SDL_PollEvent(&event))
      {
         if (event.type == SDL_EVENT_QUIT)
            m_isRunning = false;
      }
   }
}