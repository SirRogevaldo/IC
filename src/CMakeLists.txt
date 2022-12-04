cmake_minimum_required(VERSION 3.16)
project( project2 )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

SET (BASE_DIR ${CMAKE_SOURCE_DIR} )
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BASE_DIR}/bin)

add_executable( imageCopy imageCopy.cpp )
target_link_libraries( imageCopy ${OpenCV_LIBS})

add_executable( imageNeg imageNeg.cpp )
target_link_libraries( imageNeg ${OpenCV_LIBS} )

add_executable( imageRotate imageRotate.cpp )
target_link_libraries( imageRotate ${OpenCV_LIBS} )

add_executable( imageBright imageBright.cpp )
target_link_libraries( imageBright ${OpenCV_LIBS} )

add_executable( imageMirror imageMirror.cpp )
target_link_libraries( imageMirror ${OpenCV_LIBS} )