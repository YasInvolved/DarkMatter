add_executable(DarkMatterSandboxGame "main.cpp")
target_link_libraries(DarkMatterSandboxGame DarkMatter)

add_custom_command(
	OUTPUT "dm_copied.marker"
	COMMAND "${CMAKE_COMMAND}" -E echo "Copying Dark Matter library"
	COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:DarkMatter>" "$<TARGET_FILE_DIR:DarkMatterSandboxGame>"
	COMMAND "${CMAKE_COMMAND}" -E touch "dm_copied.marker"
	DEPENDS DarkMatter
	COMMENT "Copying engine library"
)

add_custom_target(copy_engine DEPENDS "dm_copied.marker")
add_dependencies(DarkMatterSandboxGame copy_engine)