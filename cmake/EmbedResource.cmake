# function that embeds a resource

set(DM_EMBEDDED_RESOURCES_BASE_DIR "${DM_BUILD_PATH}/embedded")
set(DM_EMBED_RESOURCE_SCRIPT "${DM_ROOT_PATH}/scripts/EmbedResource.py")

function(dm_embed_resource TARGET RESOURCE_FILE)
	get_filename_component(FILENAME ${RESOURCE_FILE} NAME)
	get_filename_component(FILE_ABSOLUTE ${RESOURCE_FILE} ABSOLUTE)
	string(REPLACE "." "_" VAR_NAME ${FILENAME})

	set(EMBED_DIR "${DM_EMBEDDED_RESOURCES_BASE_DIR}/${TARGET}/Embedded")

	set(OUT_BASE "${EMBED_DIR}/${VAR_NAME}")
	set(OUT_CPP "${OUT_BASE}.cpp")
	set(OUT_H "${OUT_BASE}.h")

	add_custom_command(
		OUTPUT ${OUT_CPP}
		COMMAND ${Python3_EXECUTABLE} ${DM_EMBED_RESOURCE_SCRIPT} ${FILE_ABSOLUTE} ${OUT_CPP} ${VAR_NAME}
		DEPENDS ${RESOURCE_FILE} ${DM_EMBED_RESOURCE_SCRIPT}
		COMMENT "Embedding resource ${FILE_ABSOLUTE}"
	)

	# generate header from template
	set(VAR_NAME ${VAR_NAME})
	configure_file(
		${CMAKE_SOURCE_DIR}/cmake/EmbeddedResource.h.inl
		${OUT_H}
		@ONLY
	)

	target_sources(${TARGET} PRIVATE ${OUT_CPP})
	target_include_directories(${TARGET} PRIVATE ${DM_EMBEDDED_RESOURCES_BASE_DIR})
endfunction()