# add test scripts here
SCRIPTS=lang

CPP=g++
DEPS=src/fcm.hpp

all: ${SCRIPTS}

lang: src/lang.cpp
	@ mkdir -p ./bin
	$(CPP) -o ./bin/lang src/lang.cpp src/fcm.hpp

clean:
	rm -f bin/lang