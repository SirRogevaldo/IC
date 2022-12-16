cmake_minimum_required(VERSION 3.16)
project(project2)

find_package(OpenCV REQUIRED)

SET (CMAKE_BUILD_TYPE "Release")
#SET (CMAKE_BUILD_TYPE "Debug")

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17 -pthread")
SET (CMAKE_CXX_FLAGS_RELEASE "-O3")
SET (CMAKE_CXX_FLAGS_DEBUG "-g3 -fsanitize=address")

add_executable( imageCopy imageCode/imageCopy.cpp )
target_link_libraries( imageCopy ${OpenCV_LIBS})

add_executable( imageNeg imageCode/imageNeg.cpp )
target_link_libraries( imageNeg ${OpenCV_LIBS} )

add_executable( imageRotate imageCode/imageRotate.cpp )
target_link_libraries( imageRotate ${OpenCV_LIBS} )

add_executable( imageBright imageCode/imageBright.cpp )
target_link_libraries( imageBright ${OpenCV_LIBS} )

add_executable( imageMirror imageCode/imageMirror.cpp )
target_link_libraries( imageMirror ${OpenCV_LIBS} )

add_executable( codecAudioTest codecAudio/codecAudioTest.cpp )
target_link_libraries( codecAudioTest sndfile )
