const int blackSq = 0x769656;
const int whiteSq = 0xEBEBD3;
bool playingAs;

// INCLUDES

#include <tchar.h>
#include <windows.h>
#include <windowsx.h>

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <tuple>
#include <string>
#include <map>

// MY FILESW
#include "helpers/boardDef.cpp"
Board* boardG;

#include "helpers/pixel.cpp"
#include "helpers/coordinates.cpp"

#include "helpers/ppmImageReader.cpp"

#include "helpers/square.cpp"
#include "pieces/piece.cpp"

#include "helpers/board.cpp"

#include "pieces/pawn.cpp"
#include "pieces/rook.cpp"
#include "pieces/knight.cpp"
#include "pieces/bishop.cpp"
#include "pieces/queen.cpp"
#include "pieces/king.cpp"

#include "helpers/pieceExtra.cpp"
#include "helpers/squareExtra.cpp"

bool running = true;

BITMAPINFO buffer_bitmap_info;

void* buffer_memory;
int buffer_height;
int buffer_width;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch(uMsg) {
        case WM_DESTROY: {
            running = false;
        } break;

        case WM_SIZE: {
            RECT windowSize;

            GetClientRect(hwnd, &windowSize);

            buffer_height = windowSize.bottom - windowSize.top;
            buffer_width = windowSize.right - windowSize.left;

            std::cout << buffer_height;
            std::cout << " ";
            std::cout << buffer_width;
            std::cout << "\n";

            int buffer_size = buffer_width * buffer_height * sizeof(unsigned int);

            if(buffer_memory) VirtualFree(buffer_memory, 0, MEM_RELEASE);
            buffer_memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

            buffer_bitmap_info.bmiHeader.biSize = sizeof(buffer_bitmap_info.bmiHeader);
            buffer_bitmap_info.bmiHeader.biWidth = buffer_width;
            buffer_bitmap_info.bmiHeader.biHeight = buffer_height;
            buffer_bitmap_info.bmiHeader.biPlanes = 1;
            buffer_bitmap_info.bmiHeader.biBitCount = 32;
            buffer_bitmap_info.bmiHeader.biCompression = BI_RGB;
        } break;

        case WM_LBUTTONUP: {
          Square* clickedSq = boardG -> GetSquareFromCoordPixels(Coordinates{GET_X_LPARAM(lParam), buffer_height - GET_Y_LPARAM(lParam)});
          Square* oldClickedSq = boardG -> GetClicked();

          if(clickedSq == oldClickedSq) break; // If same square is clicked do nothing

          if(boardG -> HasClicked()) oldClickedSq -> GetPiece() -> ToggleHighlightLegal(); // If there was a square clicked before, untoggle the legal-moves-highlights

          if(!(boardG -> SetClicked(clickedSq))) break; // If click fails (square has no piece) break

          clickedSq -> GetPiece() -> ToggleHighlightLegal();

          std::cout << "Okay, I got here" << "\n";

        } break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

inline void Simulate() {
  // Simulate

  unsigned int* pixel = (unsigned int*) buffer_memory;

  for(int y = 0; y < buffer_height; y++) {
    for(int x = 0; x < buffer_width; x++) {
      Coordinates pixelCoords = {x,y};
      Square* sq = boardG -> GetSquareFromCoordPixels(pixelCoords);
      int sqClr = sq -> GetColor();

      if(sq -> HasPiece()) {
        Coordinates relative_coord = sq -> GetRelative(pixelCoords);

        *pixel++ = sq -> GetPiece() -> DrawPixel(relative_coord);
        continue;
      }

      *pixel++ = sqClr;
    }
  }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
    // Register the window class.
    const TCHAR CLASS_NAME[]  = TEXT("ChessMainWindow");
    const TCHAR WINDOW_TITLE[] = TEXT("ChessBot Beta");

    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        WINDOW_TITLE,                   // Window text
        WS_OVERLAPPED | WS_SYSMENU,            // Window style

        // Size and position
        10, 10, 656, 679,

        NULL,       // Parent window
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    HDC hdc = GetDC(hwnd);

    // GAME SETUP

    reader = new PPMImageReader();

    srand((unsigned int) time(NULL));

    playingAs = ((std::rand() % 2) == 0);

    boardG = new Board();
    boardG -> PrintBoard();

    // Run the message loop.
    MSG msg;

    while(running) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Simulate
        Simulate();

        // Render
        StretchDIBits(hdc, 0, 0,
          buffer_width, buffer_height,
          0, 0, buffer_width, buffer_height,
          buffer_memory,
          &buffer_bitmap_info,
          DIB_RGB_COLORS,
          SRCCOPY
        );

        Sleep(100);
    }

    return 0;
}
