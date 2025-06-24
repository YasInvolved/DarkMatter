#ifndef _DM_IRENDERER_H_INCLUDED_
#define _DM_IRENDERER_H_INCLUDED_

namespace DarkMatter
{
   class IRenderer
   {
   public:
      virtual ~IRenderer() = default;

      virtual void Init() = 0;
      virtual void Shutdown() = 0;
      
      virtual void BeginFrame() = 0;
      virtual void EndFrame() = 0;

      virtual void Resize(uint32_t w, uint32_t h) = 0;
      
      // TODO: Introduce renderable interfaces etc
      // virtual void DrawMesh() = 0;
   };
}

#endif