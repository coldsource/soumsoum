cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Debug)

project(soumsoum)

aux_source_directory(src/Fluid srcFluid)
aux_source_directory(src/Volume srcVolume)
aux_source_directory(src/Vector srcVector)
aux_source_directory(src/Force srcForce)
aux_source_directory(src/Dynamic srcDynamic)
aux_source_directory(src/Submarine srcSubmarine)
aux_source_directory(src/Simulation srcSimulation)
aux_source_directory(src/Map srcMap)
aux_source_directory(src/Exception srcException)

add_executable(soumsoum
	${srcFluid}
	${srcVolume}
	${srcVector}
	${srcForce}
	${srcDynamic}
	${srcSubmarine}
	${srcSimulation}
	${srcMap}
	${srcException}
	
	src/main.cpp
	)
	
target_link_libraries(soumsoum websockets)
target_link_libraries(soumsoum pthread)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no C++11 support.")
endif()

include_directories(include /usr/include)
