set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/examples)

file(
	GLOB EXAMPLES_SRC
	*.cpp
)

foreach(example_path ${EXAMPLES_SRC})
	get_filename_component(example_name ${example_path} NAME_WE)
	add_executable(
		${example_name}
		${example_path}
	)
	target_link_libraries(
		${example_name}
		PRIVATE
		${PROJECT_NAME}
	)
endforeach()


