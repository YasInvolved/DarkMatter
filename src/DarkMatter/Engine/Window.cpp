#include <DarkMatter/Engine/Window.h>

using Window = DarkMatter::Window;
using Event = DarkMatter::Events::Event;
using EventType = DarkMatter::Events::EventType;

Window::Window(const std::string& title)
   : m_title(title), m_window(nullptr)
{
   SDL_Init(SDL_INIT_VIDEO);
}

Window::~Window()
{
   SDL_Quit();
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
   SDL_Event sdlEvent;
   while (SDL_PollEvent(&sdlEvent))
   {
      // TODO: Event Translation
      DarkMatter::Events::Event event;
      bool recognized = TranslateSDLEvent(sdlEvent, event);
      
      if (recognized) 
         m_callback(event);
   }
}

void Window::setEventCallback(EventCallback cb)
{
   m_callback = cb;
}

bool Window::TranslateSDLEvent(const SDL_Event& sdlEvent, DarkMatter::Events::Event& outEvent)
{
   auto fillMouseBtnData = [&sdlEvent, &outEvent]()
      {
         outEvent.mouseEvent.button = sdlEvent.button.button;
         outEvent.mouseEvent.x = sdlEvent.button.x;
         outEvent.mouseEvent.y = sdlEvent.button.y;
      };

   switch (sdlEvent.type)
   {
   case SDL_EVENT_QUIT:
      outEvent.type = EventType::QUIT;
      return true;
   case SDL_EVENT_KEY_DOWN:
      outEvent.type = EventType::KEY_DOWN;
      outEvent.keyEvent.keyCode = sdlEvent.key.scancode;
      return true;
   case SDL_EVENT_KEY_UP:
      outEvent.type = EventType::KEY_UP;
      outEvent.keyEvent.keyCode = sdlEvent.key.scancode;
      return true;
   case SDL_EVENT_MOUSE_MOTION:
      outEvent.type = EventType::MOUSE_MOVE;
      outEvent.mouseEvent.x = sdlEvent.motion.x;
      outEvent.mouseEvent.y = sdlEvent.motion.y;
      return true;
   case SDL_EVENT_MOUSE_BUTTON_DOWN:
      outEvent.type = EventType::MOUSE_BTN_DOWN;
      fillMouseBtnData();
      return true;
   case SDL_EVENT_MOUSE_BUTTON_UP:
      outEvent.type = EventType::MOUSE_BTN_UP;
      fillMouseBtnData();
      return true;
   case SDL_EVENT_WINDOW_RESIZED:
      outEvent.type = EventType::WINDOW_RESIZE;
      outEvent.windowResizeEvent.w = sdlEvent.window.data1;
      outEvent.windowResizeEvent.h = sdlEvent.window.data2;
      return true;
   default:
      return false;
   }
}