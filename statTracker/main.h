#pragma once

#include <string>
#include <vector>
#include <list>
#include "statTracker.h"

#define MAX_LOADSTRING 100
#define MAX_NAME_LENGTH 30
#define MAX_NUMBER_DIGITS 2


// Global Variables:
HBITMAP courtPic = NULL;						//the court image
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

HWND g_hToolbar = NULL;
std::vector<HWND> arrInGamePlayerButton; //these will be all the buttons for active players
std::vector<HWND> arrSubPlayerButton; //these will be all the buttons for the subs
std::vector<int> inGamePlayer; //the slots they players use for the buttons


HBITMAP madeShotSpots;
HBITMAP missedShotSpots;
static HWND hwndEdit;							//a text window for editing shit
static HWND subButton;
static HWND comboBox;

//pic size is 540x301
int courtX = 50,courtY =50;
int courtW = 540, courtH = 301;
//team entry controls
char  strNameEntry[30];


CStatTracker stats;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	PlayerNameEntry(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	SubPlayer(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	createTeamProc(HWND, UINT, WPARAM, LPARAM); 
