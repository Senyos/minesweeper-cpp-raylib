EXES=minesweeper
CLASSES=Cell.cpp Field.cpp

all: $(EXES)

minesweeper: minesweeper.cpp $(CLASSES)
	g++ -Wall -Wextra -ggdb -I./raylib-cpp/include/ -I./raylib-6.0_linux_amd64/include/ -L./raylib-6.0_linux_amd64/lib -o $@ $^ -l:libraylib.a -lX11 # -lopengl32 -lgdi32 -lwinmm

clear:
	rm $(EXES) *.tar*

share:
	git archive --prefix=minesweeper-raylib.cpp/ -o minesweeper-raylib.cpp.tar.gz HEAD
