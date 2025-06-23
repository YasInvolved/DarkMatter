#include <DarkMatter/Engine/Window.h>

using Window = DarkMatter::Window;

Window::Window(const std::string& title)
   : m_title(title)
{
   SDL_Init(SDL_INIT_VIDEO);
}

Window::~Window()
{

}

bool Window::initialize()
{
   m_window = SDL_CreateWindow(m_title.data(), 1280, 720, SDL_WINDOW_VULKAN | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_RESIZABLE);
   if (m_window == nullptr)
      return false;
   
   return true;
}

void Window::handleEvents()
{
   SDL_Event event;
   while (SDL_PollEvent(&event))
   {
      // TODO: Event Translation
   }
}