SRCDIR=src/
BUILDDIR=build/

EXESLIN=minesweeper minesweeper-for-appimage
EXESWIN=minesweeper.exe
CLASSES=$(SRCDIR)Cell.cpp $(SRCDIR)Field.cpp $(SRCDIR)Button.cpp $(SRCDIR)Menu.cpp
MAINFILE=$(SRCDIR)minesweeper.cpp
CFLAGS=-Wall -Wextra

CCLIN=g++                                                 # Linux compiler
CCWIN=x86_64-w64-mingw32-g++                              # Windows compiler

RAYLIBCPP_INCLUDE=-I./raylib-cpp/include/                 # raylib cpp bindings include

RAYLIBLIN_INCLUDE=-I./raylib-6.0_linux_amd64/include/     # raylib for Linux include
RAYLIBLIN_LIB=-L./raylib-6.0_linux_amd64/lib              # raylib for Linux lib

RAYLIBWIN_INCLUDE=-I./raylib-6.0_win64_mingw-w64/include/ # raylib for Windows include
RAYLIBWIN_LIB=-L./raylib-6.0_win64_mingw-w64/lib/         # raylib for Windows lib


all: lin win
lin: $(EXESLIN)
win: $(EXESWIN)

minesweeper: $(MAINFILE) $(CLASSES) | build_dir
	$(CCLIN) $(CFLAGS) -static-libgcc -static-libstdc++ $(RAYLIBCPP_INCLUDE) $(RAYLIBLIN_INCLUDE) $(RAYLIBLIN_LIB) -o $(BUILDDIR)$@ $^ -l:libraylib.a -lX11

minesweeper.exe: $(MAINFILE) $(CLASSES) | build_dir
	$(CCWIN) $(CFLAGS) -static $(RAYLIBCPP_INCLUDE) $(RAYLIBWIN_INCLUDE) $(RAYLIBWIN_LIB) -o $(BUILDDIR)$@ $^ -l:libraylib.a -lopengl32 -lgdi32 -lwinmm

minesweeper-for-appimage: $(MAINFILE) $(CLASSES) | build_dir
	$(CCLIN) $(CFLAGS) -static-libgcc -static-libstdc++ -Wl,--disable-new-dtags,-rpath,'../lib' $(RAYLIBCPP_INCLUDE) $(RAYLIBLIN_INCLUDE) $(RAYLIBLIN_LIB) -L../lib/ -o $(BUILDDIR)$@ $^ -l:libraylib.a -lX11

build_dir:
	make $(BUILDDIR)

clear:
	rm $(EXES) *.tar*

share:
	git archive --prefix=minesweeper-raylib.cpp/ -o minesweeper-raylib.cpp.tar.gz HEAD
