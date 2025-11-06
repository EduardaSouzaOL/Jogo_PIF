// src/winmain_shim.c
#ifdef _WIN32
#include <windows.h>

extern int main(int argc, char** argv);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow) {
    return main(__argc, __argv);
}
#endif
