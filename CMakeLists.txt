#CMAKE FOR GLFW GLEW 
cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_NAME "Framework")
set(PROJECT_VERSION "v0.1")

project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES CXX)

#Set the output to the bin folder where cmake was executed
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Set module path for finding missing libraries
#set(CMAKE_MODULE_PATH "./CMakeFiles")

# Copy all shaders into include directory.
file(GLOB shaders ${PROJECT_SOURCE_DIR}/shader)
file(COPY ${shaders} DESTINATION ${CMAKE_BINARY_DIR}/include)

if(WIN32)
	# Copy all dll-files into build folder
	file(GLOB dlls ${CMAKE_CURRENT_SOURCE_DIR}/bin/*)
	file(COPY ${dlls} DESTINATION ${PROJECT_BINARY_DIR})
endif(WIN32)

# Copy moveset file to build directory
#file(COPY ${PROJECT_SOURCE_DIR}/resources/moves/move.yaml DESTINATION ${PROJECT_BINARY_DIR}/resources/moves)

# Add all cpp files used in the program
add_executable(${PROJECT_NAME} 
	#src
	${PROJECT_SOURCE_DIR}/source/src/main.cpp 
	
	#imgui
	${PROJECT_SOURCE_DIR}/source/imgui/imgui.cpp
	${PROJECT_SOURCE_DIR}/source/imgui/imgui_draw.cpp
	${PROJECT_SOURCE_DIR}/source/imgui/imgui_impl_glfw_gl3.cpp

	#environment
	${PROJECT_SOURCE_DIR}/source/environment/Camera.cpp
	${PROJECT_SOURCE_DIR}/source/environment/LightSource.cpp

	#game
	${PROJECT_SOURCE_DIR}/source/game/Object.cpp
	${PROJECT_SOURCE_DIR}/source/game/Map.cpp
	${PROJECT_SOURCE_DIR}/source/game/Glider.cpp

	#components
	${PROJECT_SOURCE_DIR}/source/components/IComponent.cpp
	${PROJECT_SOURCE_DIR}/source/components/GraphicsComponent.cpp
	${PROJECT_SOURCE_DIR}/source/components/MapComponent.cpp

	#helpers
	${PROJECT_SOURCE_DIR}/source/helpers/errorHandler.cpp
	${PROJECT_SOURCE_DIR}/source/helpers/glfw_setup.cpp
	${PROJECT_SOURCE_DIR}/source/helpers/global_function.cpp
	
	#modeler
	${PROJECT_SOURCE_DIR}/source/modeler/Mesh.cpp
	${PROJECT_SOURCE_DIR}/source/modeler/Model.cpp
	${PROJECT_SOURCE_DIR}/source/modeler/Shader.cpp
	${PROJECT_SOURCE_DIR}/source/modeler/ShaderManager.cpp
	${PROJECT_SOURCE_DIR}/source/modeler/Texture.cpp
	${PROJECT_SOURCE_DIR}/source/helpers/global_function.cpp
)

# Find packages for linking
if (WIN32)
	# Set library include and library directories
	set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
	set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
	
	# Set library include paths
	#set(GLEW_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
	#set(glfw3_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
	#set(assimp_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
	#set(SOIL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
	
	# Add include directories
	include_directories(${INC_DIR})

	find_package(OpenGL REQUIRED)
	find_library(GLEW GLEW "${LIB_DIR}")
	find_library(glfw3 glfw3 "${LIB_DIR}")
	find_library(assimp assimp "${LIB_DIR}")
	find_library(SOIL SOIL "${LIB_DIR}")
	
	target_link_libraries(${PROJECT_NAME}
		${OPENGL_LIBRARIES}
		${GLEW_LIBRARY}
		${GLFW_LIBRARY}
		${assimp}
		${SOIL}
	)
	#target_link_libraries(${PROJECT_NAME} SOIL /usr/include/SOIL)
endif(WIN32)
if(UNIX)
	find_package(GLEW REQUIRED)
	find_package(OpenGL REQUIRED)
	find_package(glfw3 3.2 REQUIRED)
	find_package(assimp REQUIRED)
	find_library(SOIL SOIL /usr/include/SOIL)
	
	# Link the packages
	target_link_libraries(${PROJECT_NAME}
		PRIVATE ${OPENGL_LIBRARIES}
		PRIVATE ${GLEW_LIBRARY}
		PRIVATE glfw
		PRIVATE assimp
		PRIVATE ${SOIL}
	)
endif(UNIX)
if(MSVC)
	#ADD STUFF HERE!
endif(MSVC)

#find_package(assimp REQUIRED)

# Check to see if libraries was found, and report the status
#MESSAGE( STATUS "OPENGL_LIBRARIES:	" ${OPENGL_LIBRARIES})
#MESSAGE( STATUS "GLEW_LIBRARIES:	" ${GLEW_LIBRARIES})
#MESSAGE( STATUS "glfw:			" glfw3)
#MESSAGE( STATUS "assimp:		" assimp)
#MESSAGE( STATUS "SOIL:			" ${SOIL})

find_package(Doxygen)
#Set up doxygen if it is installed
if(DOXYGEN_FOUND)

	message("Setting up doxygen")
	set(DOXYGEN_IN ${PROJECT_BINARY_DIR}/CMakeDoxyfile.in)
	set(DOXYGEN_OUT ${PROJECT_BINARY_DIR}/Doxyfile)

	# Setting folders to generate documentation for
	set(DOXYGEN_EXCLUDE_PATTERNS 
		"*/.git/* */CMakeFiles/* CMakeLists.txt ${PROJECT_SOURCE_DIR}/source/imgui/*")
	set(DOXYGEN_INPUT 
		"${PROJECT_SOURCE_DIR}/source ${PROJECT_SOURCE_DIR}/doc")
	set(DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/doc)
	set(DOXYGEN_INCLUDE_GRAPH YES)

	# This first one is optional
	set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
	set(DOXYGEN_EXTRACT_ALL YES)
	set(DOXYGEN_EXTRACT_STATIC YES)

	set(DOXYGEN_EXTRACT_STATIC YES)
	set(DOXYGEN_HAVE_DOT YES)

	set(DOXYGEN_DOT_NUM_THREADS 4)
	set(DOXYGEN_CALL_GRAPH  YES)
	set(DOXYGEN_CALLER_GRAPH YES)
	set(DOXYGEN_RECURSIVE YES)

	configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

	add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_EXCLUDE_PATTERNS} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )

	#set_target_properties(doc_doxygen
	#	PROPERTIES
	#	DOXYGEN_INPUT ""
	#	DOXYGEN_OUTPUT_DIRECTORY
	#)
else()

	message("Could not find doxygen")

endif(DOXYGEN_FOUND)
