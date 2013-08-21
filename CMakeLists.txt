project (yTriangle)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set (yTriangle_SRCS
	src/main.cpp
	src/Application.cpp
)

add_executable(tsum ${yTriangle_SRCS})