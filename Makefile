EXESLIN=minesweeper
EXESWIN=minesweeper.exe
CLASSES=Cell.cpp Field.cpp Button.cpp Menu.cpp
CFLAGS=-Wall -Wextra

all: lin win
lin: $(EXESLIN)
win: $(EXESWIN)

minesweeper: minesweeper.cpp $(CLASSES)
	g++ $(CFLAGS) -static-libgcc -static-libstdc++ -I./raylib-cpp/include/ -I./raylib-6.0_linux_amd64/include/ -L./raylib-6.0_linux_amd64/lib -o $@ $^ -l:libraylib.a -lX11 # -lopengl32 -lgdi32 -lwinmm

minesweeper.exe: minesweeper.cpp $(CLASSES)
	x86_64-w64-mingw32-g++ $(CFLAGS) -static -I./raylib-cpp/include -I./raylib-6.0_win64_mingw-w64/include/ -L./raylib-6.0_win64_mingw-w64/lib/ -o $@ $^ -l:libraylib.a -lopengl32 -lgdi32 -lwinmm


clear:
	rm $(EXES) *.tar*

share:
	git archive --prefix=minesweeper-raylib.cpp/ -o minesweeper-raylib.cpp.tar.gz HEAD
