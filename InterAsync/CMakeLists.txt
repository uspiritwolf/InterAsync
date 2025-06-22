
file(
	GLOB_RECURSE
	IA_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

add_library(InterAsync)

target_sources(InterAsync PRIVATE ${IA_SOURCE_FILES})
target_include_directories(InterAsync
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_property(TARGET InterAsync PROPERTY CXX_STANDARD 23)
set_property(TARGET InterAsync PROPERTY CXX_EXTENSIONS ON)
set_property(TARGET InterAsync PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET InterAsync PROPERTY CXX_SCAN_FOR_MODULES OFF)
