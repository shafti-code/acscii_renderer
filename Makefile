main: src/main.cpp
	zig c++ src/main.cpp -o build/macos/bin -lncurses -d

run: main
	./build/macos/bin
