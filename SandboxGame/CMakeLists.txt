add_executable(DarkMatterSandboxGame "main.cpp")
target_link_libraries(DarkMatterSandboxGame DarkMatter)

add_custom_command(TARGET DarkMatterSandboxGame POST_BUILD
	COMMAND "${CMAKE_COMMAND}" -E copy_directory_if_different "$<TARGET_FILE_DIR:DarkMatter>" "$<TARGET_FILE_DIR:DarkMatterSandboxGame>"
)