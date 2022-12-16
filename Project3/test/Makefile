# add test scripts here
SCRIPTS=testFcm

all: ${SCRIPTS}

%: %.cpp
	g++ $< -o $@

clean:
	rm -f ${SCRIPTS}