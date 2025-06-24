set(DM_ENGINE_SOURCES
	"Engine/Engine.cpp"
	"Engine/Engine.h"
	"Engine/Window.h" 
	"Engine/Window.cpp"
)

set(DM_RENDERER_SOURCES
	 "Renderer/IRenderer.h"
	 "Renderer/VulkanRenderer.h"
	 "Renderer/VulkanRenderer.cpp"
	 "Renderer/Renderer.h"
     "Renderer/Renderer.cpp"
)

add_library(DarkMatter SHARED ${DM_ENGINE_SOURCES} ${DM_RENDERER_SOURCES} "pch.cpp")
target_include_directories(DarkMatter 
	PUBLIC "${DM_ROOT_PATH}/include"
	PRIVATE "${DM_ROOT_PATH}/src"
)

target_compile_definitions(DarkMatter PRIVATE DM_EXPORT_SYMBOLS)
target_precompile_headers(DarkMatter PRIVATE "pch.h")
target_link_libraries(DarkMatter PRIVATE SDL3::SDL3)

# Copy Dependencies (dlls)
add_custom_command(TARGET DarkMatter POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:SDL3::SDL3>" "$<TARGET_FILE_DIR:DarkMatter>"
)