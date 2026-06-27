SRCDIR=src/
BUILDDIR=build/
APPTOOL=$(BUILDDIR)appimagetool-x86_64.AppImage
APPDIR=$(BUILDDIR)minesweeper-cpp-raylib.AppDir/

EXELIN=$(BUILDDIR)minesweeper
EXELIN_APP=$(BUILDDIR)minesweeper-cpp-raylib.AppImage
APPEXE=$(APPDIR)usr/bin/minesweeper-for-appimage
EXEWIN=$(BUILDDIR)minesweeper.exe
CLASSES=$(SRCDIR)Cell.cpp $(SRCDIR)Field.cpp $(SRCDIR)Button.cpp $(SRCDIR)Menu.cpp
MAINFILE=$(SRCDIR)minesweeper.cpp
CFLAGS=-Wall -Wextra

CCLIN=g++#                                                # Linux compiler
CCWIN=x86_64-w64-mingw32-g++#                             # Windows compiler

RAYLIBCPP_INCLUDE=-I./raylib-cpp-master/include/#         # raylib cpp bindings include

RAYLIBLIN_INCLUDE=-I./raylib-6.0_linux_amd64/include/#    # raylib for Linux include
RAYLIBLIN_LIB=-L./raylib-6.0_linux_amd64/lib#             # raylib for Linux lib

RAYLIBWIN_INCLUDE=-I./raylib-6.0_win64_mingw-w64/include/## raylib for Windows include
RAYLIBWIN_LIB=-L./raylib-6.0_win64_mingw-w64/lib/#        # raylib for Windows lib


all: lin win
lin: $(EXELIN)
lin-app: $(EXELIN_APP)
win: $(EXEWIN)

$(EXELIN): $(MAINFILE) $(CLASSES) | $(BUILDDIR)
	$(CCLIN) $(CFLAGS) -static-libgcc -static-libstdc++ $(RAYLIBCPP_INCLUDE) $(RAYLIBLIN_INCLUDE) $(RAYLIBLIN_LIB) -o $@ $^ -l:libraylib.a -lX11

$(EXEWIN): $(MAINFILE) $(CLASSES) | $(BUILDDIR)
	$(CCWIN) $(CFLAGS) -static $(RAYLIBCPP_INCLUDE) $(RAYLIBWIN_INCLUDE) $(RAYLIBWIN_LIB) -o $@ $^ -l:libraylib.a -lopengl32 -lgdi32 -lwinmm

$(EXELIN_APP): $(APPDIR) | $(APPEXE)
	ARCH=x86_64 ./$(APPTOOL) ./$^ ./$@


$(APPEXE): $(MAINFILE) $(CLASSES) | $(BUILDDIR) $(APPTOOL) $(APPDIR)
	$(CCLIN) $(CFLAGS) -static-libgcc -static-libstdc++ -Wl,--disable-new-dtags,-rpath,'../lib' $(RAYLIBCPP_INCLUDE) $(RAYLIBLIN_INCLUDE) $(RAYLIBLIN_LIB) -L../lib/ -o $@ $^ -l:libraylib.a -lX11

$(BUILDDIR):
	mkdir -p $@

$(APPDIR):
	./create_appdir.sh

$(APPTOOL):
	curl -L https://github.com/AppImage/appimagetool/releases/download/continuous/appimagetool-x86_64.AppImage -o $@
	chmod +x $(APPTOOL)

download: raylib-cpp-master raylib-6.0_win64_mingw-w64 raylib-6.0_linux_amd64


raylib-6.0_win64_mingw-w64:
	curl -L https://github.com/raysan5/raylib/releases/download/6.0/raylib-6.0_win64_mingw-w64.zip -o $@.zip
	#
	unzip $@.zip
	#
	rm -rf $@.zip

raylib-6.0_linux_amd64:
	curl -L https://github.com/raysan5/raylib/releases/download/6.0/raylib-6.0_linux_amd64.tar.gz -o $@.tar.gz
	#
	tar -xvf $@.tar.gz
	#
	rm -rf $@.tar.gz

raylib-cpp-master:
	curl -L https://github.com/RobLoach/raylib-cpp/archive/refs/heads/master.tar.gz -o $@.tar.gz
	#
	tar -xf $@.tar.gz
	#
	rm -rf $@.tar.gz

clear:
	rm -rf $(BUILDDIR)

share:
	git archive --prefix=minesweeper-raylib.cpp/ -o minesweeper-raylib.cpp.tar.gz HEAD
