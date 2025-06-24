#include <DarkMatter/DarkMatter.h>
#include <iostream>

class Game : public DarkMatter::IGame
{
public:
   Game() = default;
   ~Game() = default;

   bool onInitialize() override
   {
      return true;
   }

   void onShutdown() override
   {

   }

   void onUpdate() override
   {

   }

   void onRender() override
   {

   }

   void onEvent(const DarkMatter::Events::Event& event) override
   {
      if (event.type == DarkMatter::Events::EventType::KEY_DOWN)
         std::cout << event.keyEvent.keyCode << " was pressed\n";
      else if (event.type == DarkMatter::Events::EventType::KEY_UP)
         std::cout << event.keyEvent.keyCode << " was released\n";
   }

   std::string getTitle() const override
   {
      return "SandboxGame";
   }
};

int main(int argc, char** argv)
{
   auto* engine = CreateEngine();
   
   engine->setGame(std::make_unique<Game>());

   if (!engine->initialize())
      return -1;
   
   engine->run();
   engine->shutdown();
   DestroyEngine(engine);

   return 0;
}