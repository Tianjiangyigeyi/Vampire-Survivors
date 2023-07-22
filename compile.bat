cd assets/voice
gcc play.cpp -o play -LWinMM.Lib -lwinmm -lstdc++
cd ..
cd ..

mingw32-make -j
