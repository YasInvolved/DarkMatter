function(dm_check_if_clangcl RESULT_VAR)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC")
		set(${RESULT_VAR} TRUE PARENT_SCOPE)
	else()
		set(${RESULT_VAR} FALSE PARENT_SCOPE)
	endif()
endfunction()

macro(dm_add_compiler_flags_per_config)
	dm_check_if_clangcl(IS_CLANGCL)

	if (MSVC OR IS_CLANGCL)
		add_compile_options(
			$<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:/Zi>
			$<$<CONFIG:Release>:/O2>
		)
	endif()

	# TODO: Add flags for more compilers
endmacro()