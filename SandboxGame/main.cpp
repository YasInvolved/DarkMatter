#include <DarkMatter/DarkMatter.h>

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