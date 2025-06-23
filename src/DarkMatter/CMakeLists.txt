set(DM_GAME_SOURCES "Game/BaseGame.cpp")

add_library(DarkMatter SHARED ${DM_GAME_SOURCES} )
target_include_directories(DarkMatter PUBLIC "${DM_ROOT_PATH}/include")

target_compile_definitions(DarkMatter PRIVATE DM_EXPORT_SYMBOLS)