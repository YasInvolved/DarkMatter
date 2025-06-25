#include <DarkMatter/DarkMatter.h>

class Game : public DarkMatter::IGame
{
   const DarkMatter::IEngine* m_engine = nullptr;
public:
   Game() = default;
   ~Game() = default;

   bool onInitialize(const DarkMatter::IEngine& engine) override
   {
      m_engine = &engine;
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
      auto& gameLogger = m_engine->getLoggerManager().getLoggerByName(getTitle());

      if (event.type == DarkMatter::Events::EventType::KEY_DOWN)
         gameLogger.info("{} was pressed", event.keyEvent.keyCode);
      else if (event.type == DarkMatter::Events::EventType::KEY_UP)
         gameLogger.info("{} was released", event.keyEvent.keyCode);
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