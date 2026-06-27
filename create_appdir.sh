#!/bin/env bash

mkdir -p build/minesweeper-cpp-raylib.AppDir/
mkdir -p build/minesweeper-cpp-raylib.AppDir/usr/
mkdir -p build/minesweeper-cpp-raylib.AppDir/usr/bin/
mkdir -p build/minesweeper-cpp-raylib.AppDir/usr/lib/
#
echo "#!/bin/env bash"                                >  build/minesweeper-cpp-raylib.AppDir/AppRun
echo "exec \$APPDIR/usr/bin/minesweeper-for-appimage" >> build/minesweeper-cpp-raylib.AppDir/AppRun
chmod +x build/minesweeper-cpp-raylib.AppDir/AppRun
#
echo "[Desktop Entry]"               >  build/minesweeper-cpp-raylib.AppDir/minesweeper-cpp-raylib.desktop
echo "Type=Application"              >> build/minesweeper-cpp-raylib.AppDir/minesweeper-cpp-raylib.desktop
echo "Name=minesweeper-for-appimage" >> build/minesweeper-cpp-raylib.AppDir/minesweeper-cpp-raylib.desktop
echo "Exec=minesweeper-for-appimage" >> build/minesweeper-cpp-raylib.AppDir/minesweeper-cpp-raylib.desktop
echo "Icon=minesweeper-cpp-raylib"   >> build/minesweeper-cpp-raylib.AppDir/minesweeper-cpp-raylib.desktop
echo "Categories=Game;"              >> build/minesweeper-cpp-raylib.AppDir/minesweeper-cpp-raylib.desktop
#
cp  ./minesweeper-cpp-raylib-logo.png build/minesweeper-cpp-raylib.AppDir/minesweeper-cpp-raylib.png
#
cp /usr/lib/libX11.so.6            build/minesweeper-cpp-raylib.AppDir/usr/lib/
cp /usr/lib/libm.so.6              build/minesweeper-cpp-raylib.AppDir/usr/lib/
cp /usr/lib/libc.so.6              build/minesweeper-cpp-raylib.AppDir/usr/lib/
cp /usr/lib64/ld-linux-x86-64.so.2 build/minesweeper-cpp-raylib.AppDir/usr/lib/
cp /usr/lib/libxcb.so.1            build/minesweeper-cpp-raylib.AppDir/usr/lib/
cp /usr/lib/libXau.so.6            build/minesweeper-cpp-raylib.AppDir/usr/lib/
cp /usr/lib/libXdmcp.so.6          build/minesweeper-cpp-raylib.AppDir/usr/lib/
