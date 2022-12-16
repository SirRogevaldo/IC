# IC

Project 2:

TO RUN:
------------------------------------------------------------------
./build/imageNeg imagens\ PPM/baboon.ppm
./build/imageBright imagens\ PPM/baboon.ppm
./build/imageCopy imagens\ PPM/baboon.ppm
./build/imageRotate imagens\ PPM/baboon.ppm
./build/imageMirror imagens\ PPM/baboon.ppm
------------------------------------------------------------------
mkdir build && cd build
cmake ..
cd ..
make

g++ codecAudio/codecAudioTest.cpp -lsndfile -o codecTest

./codecTest codecAudio/sample01.wav
