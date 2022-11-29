cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

SET (BASE_DIR ${CMAKE_SOURCE_DIR} )
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BASE_DIR}/bin)

add_executable( imageCopy imageCopy.cpp )
target_link_libraries( imageCopy ${OpenCV_LIBS} )

add_executable( imageNeg imageNeg.cpp )
target_link_libraries( imageNeg ${OpenCV_LIBS} )

add_executable( imageRotate imageRotate.cpp )
target_link_libraries( imageRotate ${OpenCV_LIBS} )

add_executable( imageBright imageBright.cpp )
target_link_libraries( imageBright ${OpenCV_LIBS} )

# include_directories(${CMAKE_SOURCE_DIR}/inc)
# link_directories(${CMAKE_SOURCE_DIR}/lib)

# add_executable(foo ${FOO_SRCS})
# target_link_libraries(foo bar) # libbar.so is found in ${CMAKE_SOURCE_DIR}/lib