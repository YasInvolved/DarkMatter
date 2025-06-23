set(DM_GAME_SOURCES "Game/BaseGame.cpp" "Game/Window.cpp")

add_library(DarkMatter SHARED ${DM_GAME_SOURCES} )
target_include_directories(DarkMatter PUBLIC "${DM_ROOT_PATH}/include")

target_compile_definitions(DarkMatter PRIVATE DM_EXPORT_SYMBOLS)

target_link_libraries(DarkMatter PRIVATE SDL3::SDL3)

# Copy Dependencies (dlls)
add_custom_command(TARGET DarkMatter POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:SDL3::SDL3>" "$<TARGET_FILE_DIR:DarkMatter>"
)