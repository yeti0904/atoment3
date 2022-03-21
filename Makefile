cc  = g++
src = src/*.cc
arg = -std=c++17 -Wall -Wextra -Werror -pedantic
out = bin/atm

build:
	mkdir -p bin
	$(cc) $(src) $(arg) -s -o $(out)

debug:
	mkdir -p bin
	$(cc) $(src) $(arg) -g -o $(out)

test:
	mkdir -p bin
	$(cc) $(src) -std=c++17 -s -o $(out)

install: $(out)
	cp $(out) /usr/bin/