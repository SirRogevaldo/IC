# Project3

******

## Directory Organization

- **test** contains tests to certain source modules

- **src** contains the implemented source code

## Compiling the code
--------------------------------------------------------------------------------------------------------------------------
g++ lang.cpp -o la
./la ../SampleTexts/dummyENG.txt ../SampleTexts/dummyENG.txt
./la ../SampleTexts/LusiadasPT.txt ../SampleTexts/dummyENG.txt
./la ../SampleTexts/akumaJPN.txt ../SampleTexts/dummyENG.txt
./la ../SampleTexts/sherlockHolmesENG.txt ../SampleTexts/dummyENG.txt
--------------------------------------------------------------------------------------------------------------------------
g++ findlang.cpp -o la
./la ../SampleTexts/LusiadasPT3kModel.txt ../SampleTexts/dummyENG3kModel.txt ../SampleTexts/LusiadasPT.txt
./la ../SampleTexts/LusiadasPT3kModel.txt ../SampleTexts/dummyENG3kModel.txt  ../SamplesTexts/sherlockHolmesENG.txt ../SamplesTexts/akumaJPN.txt ../SampleTexts/LusiadasPT.txt


******
