#include <DarkMatter/Game/Window.h>
#include <SDL3/SDL.h>

using Window = DarkMatter::Game::Window;

Window::Window()
{
   SDL_Init(SDL_INIT_VIDEO);
   m_handle = SDL_CreateWindow("GameWindow", 1280, 720, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
}

Window::~Window()
{
   SDL_DestroyWindow(reinterpret_cast<SDL_Window*>(m_handle));
   SDL_Quit();
}