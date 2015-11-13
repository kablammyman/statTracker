// statTracker.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <windows.h>
#include "commdlg.h" //used for windows OPENFILENAME
#include "resource.h"
#include "main.h"

void prepareHomeTeamPlayerButtons(HWND hWnd, int baseX)
{
	int baseY = courtY + 301 + 10;
    int buttonW = 50,buttonH = 50;
	for(int i = 0; i < 5; i++)
	{
		//char idNumber[2];
		//sprintf_s(idNumber,"%i",i);
		HWND tempButton = CreateWindowA("BUTTON", /*idNumber*/"??",  WS_VISIBLE | WS_CHILD,baseX+(i*buttonW), baseY, buttonW,buttonH,hWnd,(HMENU)(IDB_PLAYER_0+i),NULL,0);
																														
		arrInGamePlayerButton.push_back(tempButton);
		inGamePlayer.push_back(i);
	}
}

void prepareAwayTeamPlayerButtons(HWND hWnd, int baseX)
{
	int baseY = courtY + 301 + 10;
    int buttonW = 50,buttonH = 50;
	for(int i = 0; i < 5; i++)
	{
		//char idNumber[2];
		//sprintf_s(idNumber,"%i",i);
		HWND tempButton = CreateWindowA("BUTTON", /*idNumber*/"??",  WS_VISIBLE | WS_CHILD,baseX+(i*buttonW), baseY, buttonW,buttonH,hWnd,(HMENU)(IDB_PLAYER_5+i),NULL,0);
																														
		arrInGamePlayerButton.push_back(tempButton);
	}
}
void updateHomeTeamPlayerButtons()
{	
	int count = 0;

	for(stats.teamItr=stats.homeTeam.begin(); stats.teamItr != stats.homeTeam.end(); ++stats.teamItr)
	{
		CPlayer temp = *stats.teamItr;
		if(temp.inGame && count < 5)
		{
			char id[4];
			sprintf_s(id,"%i",temp.m_number);
			SetWindowTextA(arrInGamePlayerButton[count],id); //change the text on the button
			inGamePlayer[count] = temp.m_number;
			count++;
		}
		
	}
}
void updateAwayTeamPlayerButtons()
{
	for(int i = 0; i < 5; i++)
	{
		CPlayer temp;	   
		stats.teamItr=stats.awayTeam.begin();
		int count = 0;

		while(count < i && stats.teamItr != stats.awayTeam.end())
		{
			++stats.teamItr;
			count++;
		}

		temp = *stats.teamItr;

		if(temp.inGame)
		{
			char id[4];
			sprintf_s(id,"%i",temp.m_number);
			SetWindowTextA(arrInGamePlayerButton[i],id); //change the text on the button
		}
	}
}
void draw(HDC hdc, HBITMAP pic, int x, int y)
{
	BITMAP bm;
	//PAINTSTRUCT ps;
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, pic);
	GetObject(pic, sizeof(bm), &bm);
	BitBlt(hdc, x, y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);
}

void drawCurPlayerStats(HDC hdc, int startX, int startY)
{
	int newLineSize = 50, wordSpacing = 50, nexCol = wordSpacing*3;
	char temp[6];

	TextOutA(hdc,startX,startY,stats.curPlayer->name.c_str(),stats.curPlayer->name.size());

	sprintf_s(temp,"%1.1f",stats.curPlayer->calcShootingPercentage());
	TextOutA(hdc,startX,startY+newLineSize,"fg%: ",4);
	TextOutA(hdc,startX+wordSpacing,startY+newLineSize,temp,strlen(temp));

	sprintf_s(temp,"%i",stats.curPlayer->m_offReb);
	TextOutA(hdc,startX,startY+newLineSize*2,"O-Rebs: ",10);
	TextOutA(hdc,startX+wordSpacing,startY+newLineSize*2,temp,strlen(temp));

	sprintf_s(temp,"%i",stats.curPlayer->m_asst);
	TextOutA(hdc,startX,startY+newLineSize*3,"asst: ",6);
	TextOutA(hdc,startX+wordSpacing,startY+newLineSize*3,temp,strlen(temp));

	sprintf_s(temp,"%i",stats.curPlayer->m_turnOver);
	TextOutA(hdc,startX,startY+newLineSize*4,"TO: ",10);
	TextOutA(hdc,startX+wordSpacing,startY+newLineSize*4,temp,strlen(temp));

//---------------------------------------------------------------------------
	startX += nexCol;
	sprintf_s(temp,"%i",stats.curPlayer->m_defReb);
	TextOutA(hdc,startX,startY+newLineSize,"D-Rebs: ",10);
	TextOutA(hdc,startX+wordSpacing,startY+newLineSize,temp,strlen(temp));

	sprintf_s(temp,"%i",stats.curPlayer->m_steal);
	TextOutA(hdc,startX,startY+newLineSize*2,"steals: ",8);
	TextOutA(hdc,startX+wordSpacing,startY+newLineSize*2,temp,strlen(temp));

	sprintf_s(temp,"%i",stats.curPlayer->m_steal);
	TextOutA(hdc,startX,startY+newLineSize*3,"blocks: ",8);
	TextOutA(hdc,startX+wordSpacing,startY+newLineSize*3,temp,strlen(temp));

	sprintf_s(temp,"%i",stats.curPlayer->m_foul);
	TextOutA(hdc,startX,startY+newLineSize*4,"fouls: ",7);
	TextOutA(hdc,startX+wordSpacing,startY+newLineSize*4,temp,strlen(temp));
}


BOOL CALLBACK ToolDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				/*case IDC_PRESS:
					//MessageBox uses unicode, MessageBoxA is normal chars!
					MessageBoxA(NULL, "Hi!", "This is a message", MB_OK | MB_ICONEXCLAMATION);
				break;
				case IDC_OTHER:
					//MessageBox uses unicode, MessageBoxA is normal chars!
					MessageBoxA(NULL, "Bye!", "This is also a message", MB_OK | MB_ICONEXCLAMATION);
				break;
				*/
			case IDC_OFFREB:
				if(stats.curPlayer != NULL)
				stats.curPlayer->m_offReb++;
				break;
			case IDC_DEFREB:
				if(stats.curPlayer != NULL)
				stats.curPlayer->m_defReb++;
				break;
			case IDC_ASST:
				if(stats.curPlayer != NULL)
				stats.curPlayer->m_asst++;
				break;
			case IDC_TURNOVER:
				if(stats.curPlayer != NULL)
				stats.curPlayer->m_turnOver++;
				break;
			case IDC_STEAL:
				if(stats.curPlayer != NULL)
				stats.curPlayer->m_steal++;
				break;
			case IDC_BLOCK:
				if(stats.curPlayer != NULL)
				stats.curPlayer->m_block++;
				break;
			case IDC_FOUL:
				if(stats.curPlayer != NULL)
				stats.curPlayer->m_foul++;
				break;
			case IDC_MAKE:
				if(stats.curPlayer != NULL)
				{
					stats.curPlayer->m_freeThrowsAttempted++;
					stats.curPlayer->m_freeThrowsMade++;
				}
				break;
			case IDC_MISS:
				if(stats.curPlayer != NULL)
				stats.curPlayer->m_freeThrowsAttempted++;
				break;
			case IDC_AND_1:
				if(stats.curPlayer != NULL)
				stats.curPlayer->m_and1++;
				break;

			}
		break;
		default:
			return FALSE;
	}
	return TRUE;
}

void DoFileOpen(HWND hwnd, std::string &name)
{
	OPENFILENAME ofn;
	//HANDLE hf;              // file handle

	TCHAR szFileName[MAX_PATH];


	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFileName;
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFileName);
	ofn.lpstrFilter = _T("All\0*.*\0Text\0*.TXT\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


	if(GetOpenFileName(&ofn))
	{
		name = szFileName;
	}
	
}
void DoFileSave(HWND hwnd, std::string &name)
{
	OPENFILENAME ofn;
	TCHAR szFileName[MAX_PATH];

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = _T("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = _T("txt");
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

	if(GetSaveFileName(&ofn))
	{
		//HWND hEdit = GetDlgItem(hwnd, IDC_MAIN_EDIT);
		//SaveTextFileFromEdit(hEdit, szFileName);
		 name = szFileName;
	}
}
void FillListBox(HWND hwndList)
{
/*
	TCHAR *pVarName[] = {"Item1", "Item2", "Item3", "Item4", "Item5"};
	for(int i=0; i<5; i++)
		SendMessage(hwndList, CB_ADDSTRING, 0, (LPARAM)pVarName[i]);
	*/
	
	for(stats.teamItr=stats.homeTeam.begin(); stats.teamItr != stats.homeTeam.end(); ++stats.teamItr)
	{
		CPlayer temp = *stats.teamItr;
		if(!temp.inGame)
			SendMessage(hwndList, CB_ADDSTRING, 0, (LPARAM)temp.name.c_str());
	}
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_STATTRACKER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STATTRACKER));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STATTRACKER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_STATTRACKER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	int cxChar,cyChar;

	switch (message)
	{
	case WM_CREATE:
		g_hToolbar = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_STATS_TOOLBAR), hWnd, ToolDlgProc);

		prepareHomeTeamPlayerButtons(hWnd,courtX); //create the buttons for the home team (0-4)
		prepareAwayTeamPlayerButtons(hWnd,courtX+300); //create the buttons for the visotor team (5-9)

			  
		courtPic = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_COURT));
		madeShotSpots = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_MADE_SHOT_PIC));
		missedShotSpots = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_MISSED_SHOT_PIC));

		subButton = CreateWindowA("BUTTON", "Sub Current Player",  WS_VISIBLE | WS_CHILD,(courtX + courtW -150) /2 , courtY + courtH + 100, 
								  150,50,hWnd,(HMENU)(IDB_SUB_PLAYER),NULL,0);


		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());
	//	cxChar = GetLastError();

		//Set a Default Selection
		SendMessage(hWnd, CB_SETCURSEL, 0, 0);
		//GetWindowText(hwndList, pVarName, 30);
		//SetWindowText(hwndText, pVarName);


		if(courtPic == NULL)
				MessageBoxA(hWnd, "Could not load IDB_COURT!", "Error", MB_OK | MB_ICONEXCLAMATION);

		if(g_hToolbar != NULL)
		{
			ShowWindow(g_hToolbar, SW_SHOW);
		}
		else
		{  //MessageBox uses unicode, MessageBoxA is normal chars!
			MessageBoxA(hWnd, "CreateDialog returned NULL", "Warning!",	MB_OK | MB_ICONINFORMATION);
		}
	break;

	//case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN: 
	{
		// Retrieve mouse screen position
		int x=(short)LOWORD(lParam);
		int y=(short)HIWORD(lParam);

		if(stats.curPlayer!= NULL)
		{
			if(x > courtX && x < courtX+courtW &&
			   y > courtY && y < courtY+courtH)//make sure we are within the curt boundries
				stats.curPlayer->shoot( x,  y, true); 

			UpdateWindow(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	break;
	case WM_RBUTTONDOWN: 
	{
		// Retrieve mouse screen position
		int x=(short)LOWORD(lParam);
		int y=(short)HIWORD(lParam);
		if(stats.curPlayer!= NULL)
		{
			if(x > courtX && x < courtX+courtW &&
			   y > courtY && y < courtY+courtH)//make sure we are within the curt boundries
				stats.curPlayer->shoot( x,  y, false);

			UpdateWindow(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	break;
	/*case ID_EDIT:
                           
       if(HIWORD(wParam) == EN_ERRSPACE || HIWORD(wParam) == EN_MAXTEXT)
          MessageBoxA(hWnd, "Edit control out of space!","no app name", MB_OK | MB_ICONSTOP);
          
          if(HIWORD(wParam) == EN_UPDATE)
             {
                GetWindowTextA(hwndEdit, tempText, 15-1);//15 = size of array, "- 1" is for idunno
                InvalidateRect(hWnd, NULL, TRUE);
             }
       break;*/
	
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		//loop thru all buttons on the main window
		switch(wParam)
		{
			case IDB_PLAYER_0:
				stats.curPlayer = stats.getHomeTeamPlayer(inGamePlayer[0]);
				UpdateWindow(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
				break;
			case IDB_PLAYER_1:
				stats.curPlayer = stats.getHomeTeamPlayer(inGamePlayer[1]);
				UpdateWindow(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
				break;
			case IDB_PLAYER_2:
				stats.curPlayer = stats.getHomeTeamPlayer(inGamePlayer[2]);
				UpdateWindow(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
				break;
			case IDB_PLAYER_3:
				stats.curPlayer = stats.getHomeTeamPlayer(inGamePlayer[3]);
				UpdateWindow(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
				break;
			case IDB_PLAYER_4:
				stats.curPlayer = stats.getHomeTeamPlayer(inGamePlayer[4]);
				UpdateWindow(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
				break;

			case IDB_SUB_PLAYER:
				if(stats.curPlayer != NULL && !stats.homeTeam.empty())
					DialogBox(hInst, MAKEINTRESOURCE(IDD_SUB_PLAYER_BOX), hWnd, SubPlayer);
				break;

		}
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ADD_HOME_PLAYER:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ADD_PLAYER_BOX), hWnd, PlayerNameEntry);
			break;
		case IDM_CREATE_TEAM:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_CREATE_TEAM_BOX), hWnd, createTeamProc);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE( IDD_ABOUTBOX ), hWnd, About);
			break;
		case ID_FILE_ROSTER_OPEN:
			{
				std::string fileName;
				DoFileOpen(hWnd,fileName);
				//HWND hEdit = GetDlgItem(hwnd, IDC_MAIN_EDIT);
				if(stats.loadHomeTeamFromFile(fileName))
					updateHomeTeamPlayerButtons();
				else 
				{	
					MessageBoxA(hWnd, "Could not load team data, make it yourself!", "Error", MB_OK | MB_ICONEXCLAMATION);
					stats.homeTeam.clear(); //remove any junk data thats was in the list from bad file
				}
	
			}
			break;
		case ID_FILE_STATS_SAVEAS:
			{
				std::string fileName;
				DoFileSave(hWnd,fileName); 
				if(stats.saveHomeTeamStats(fileName))
					updateHomeTeamPlayerButtons();
				else 
					MessageBoxA(hWnd, "Could not save team stats!", "Error", MB_OK | MB_ICONEXCLAMATION);
				
			}
			break;
		case ID_FILE_ROSTER_SAVEAS:
			{
				std::string fileName;
				DoFileSave(hWnd,fileName); 
				if(!stats.saveHomeTeamToFile(fileName))
					MessageBoxA(hWnd, "Could not save team!", "Error", MB_OK | MB_ICONEXCLAMATION);
			}
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	break;
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			
			
			//HDC hdc = BeginPaint(hWnd, &ps);
				
			draw( hdc,courtPic, courtX, courtY);

			TextOutA(hdc,courtX,courtY-20 ,stats.homeTeamName.c_str(),stats.homeTeamName.size());
			//12 is font size, i think...
			TextOutA(hdc,courtX + (stats.homeTeamName.size()*12),courtY-20 ,stats.awayTeamName.c_str(),stats.awayTeamName.size());
			
			if(stats.curPlayer != NULL)
			{
				if(!stats.curPlayer->m_arrShots.empty() )
				{
					stats.curPlayer->itr = stats.curPlayer->m_arrShots.begin();
					while( stats.curPlayer->itr != stats.curPlayer->m_arrShots.end() ) 
					{
						if(stats.curPlayer->itr->madeShot)
							draw( hdc,madeShotSpots, stats.curPlayer->itr->x, stats.curPlayer->itr->y);
						else
							draw( hdc,missedShotSpots, stats.curPlayer->itr->x, stats.curPlayer->itr->y);
						++stats.curPlayer->itr;
					}//end draw makes and misses
				}//end we shot some shots

				drawCurPlayerStats(hdc,  courtX+courtW+100,  50);
			}
			EndPaint(hWnd, &ps);
		}
		break;

	case WM_DESTROY:
		DeleteObject(courtPic);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for add home player box.
INT_PTR CALLBACK PlayerNameEntry(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	//UNREFERENCED_PARAMETER(lParam);
	 HWND  hNameEntry, hNumberEntry;

	 hNameEntry  = GetDlgItem(hDlg, IDC_GET_PLAYER_NAME);
	 hNumberEntry = GetDlgItem(hDlg, IDC_GET_PLAYER_NUMBER);

	switch (message)
	{
	case WM_INITDIALOG:
		
		SetWindowTextA(hNameEntry, " ");
		SetWindowTextA(hNumberEntry, "0");
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch(wParam)
		{
			/*case IDC_PROCESS_BTN:
				break;*/
			
			case IDCANCEL:
				break;
			case IDOK: 
			{
				GetWindowTextA(hNameEntry, strNameEntry, MAX_NAME_LENGTH);
				char strNumber[3];
				int number;

				GetWindowTextA(hNumberEntry, strNumber, MAX_NUMBER_DIGITS);
                number = atoi(strNumber);


				stats.addNameToHomeTeam(strNameEntry,number);

				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
				break;
		}//end switch command
	
	}
	return (INT_PTR)FALSE;
}


// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// Message handler for subbing
INT_PTR CALLBACK SubPlayer(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	int cxChar,cyChar;
	TCHAR pVarName[30];

	//IDD_SUB_PLAYER_BOX
	switch (message)
	{
	case WM_INITDIALOG:
		//Create ComboBox
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());

		comboBox = CreateWindow(TEXT("COMBOBOX"),TEXT("Reserve Players"),  WS_CHILD | WS_VISIBLE |
		LBS_STANDARD, cxChar, cyChar*3,
		cxChar*16 + GetSystemMetrics(SM_CXVSCROLL),
		cyChar*5, hDlg, (HMENU)ID_RESERVE_LIST,
		(HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE),NULL);

		if(comboBox != NULL)
			ShowWindow(comboBox, SW_SHOW);
		else
			MessageBoxA(hDlg, "comboBox returned NULL", "Warning!",	MB_OK | MB_ICONINFORMATION);

		//Populate ComboBox
		FillListBox(comboBox);

		
		SendMessage(comboBox, CB_SETCURSEL, 0, 0);
		GetWindowText(comboBox, pVarName, 30);
		SetWindowText(comboBox, pVarName);
		
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		//if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		switch(wParam)
		{
			case IDD_SUB_PLAYER_BOX: // If the combo box sent the message,
            switch(HIWORD(wParam)) // Find out what message it was
            {
				case CBN_DROPDOWN: // This means that the list is about to display
					MessageBox(hDlg, TEXT("A request to display the list has been made"),TEXT("Display Notification"), MB_OK);
					break;
            }
			break;

			case IDCANCEL:
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			case IDOK:
				{
					GetWindowText(comboBox, pVarName, 30);
					CPlayer *temp = stats.getHomeTeamPlayer((char)pVarName);
					if(temp == NULL)
						break;
					temp->inGame = true;
					stats.curPlayer->inGame = false;
					stats.curPlayer = stats.getHomeTeamPlayer((char)pVarName);
					updateHomeTeamPlayerButtons();
					SendMessage(comboBox, CB_RESETCONTENT, 0, 0);
					EndDialog(hDlg, LOWORD(wParam));
				}
				break;
		}

	/*	if( LOWORD(wParam)==ID_LIST && HIWORD(wParam)==CBN_SELCHANGE)
		{
			//Get Selection from Combo Box
			GetWindowText(comboBox, pVarName, 30);
			//Show Text in Display Window
			SetWindowText(comboBox, pVarName);
		}*/
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK createTeamProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_INITDIALOG:
			// This is where we set up the dialog box, and initialise any default values

			SetDlgItemText(hwnd, IDC_CREATE_TEAM_NAME, TEXT("Team Name"));
			SetDlgItemText(hwnd, IDC_CREATE_TEAM_PLAYER, TEXT("Player Name"));
			SetDlgItemInt(hwnd, IDC_CREATE_TEAM_NUMBER, 0, FALSE);
		break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case IDOK: 
				EndDialog(hwnd, 0);
			break;

			case IDC_CREATE_TEAM_ADD:
				{
					BOOL bSuccess;
					int number = GetDlgItemInt(hwnd, IDC_CREATE_TEAM_NUMBER, &bSuccess, FALSE);
					if(bSuccess) 
					{
						int len = GetWindowTextLength(GetDlgItem(hwnd, IDC_CREATE_TEAM_PLAYER));
						if(len > 0)
						{
							// Now we allocate, and get the string into our buffer
							TCHAR* buf;

							buf = (TCHAR*)GlobalAlloc(GPTR, len + 1); 
							GetDlgItemText(hwnd, IDC_CREATE_TEAM_PLAYER, buf, len + 1);
							std::string temp = (char *)buf;
							char id[6];
							sprintf_s(id,", %i",number);
							temp += id;

							int index = SendDlgItemMessage(hwnd, IDC_CREATE_TEAM_LIST, LB_ADDSTRING, 0, (LPARAM)temp.c_str());

							// Dont' forget to free the memory!
							GlobalFree((HANDLE)buf);
						}
						else // player name string is empty
							MessageBox(hwnd, TEXT("You didn't enter anything!"), TEXT("Warning"), MB_OK);
						
					}
					else //the number entered didnt make sense
						MessageBox(hwnd, TEXT("Couldn't translate that number :("), TEXT("Warning"), MB_OK);
					
				}
				break;
				case IDC_CREATE_TEAM_REMOVE:
				{
					// When the user clicks the Remove button, we first get the number
					// of selected items

					HWND hList = GetDlgItem(hwnd, IDC_CREATE_TEAM_NAME);
					int count = SendMessage(hList, LB_GETSELCOUNT, 0, 0);
					if(count != LB_ERR)
					{
						if(count != 0)
						{
							// And then allocate room to store the list of selected items.

							int i;
							int *buf = (int*)GlobalAlloc(GPTR, sizeof(int) * count);
							SendMessage(hList, LB_GETSELITEMS, (WPARAM)count, (LPARAM)buf);
							
							// Now we loop through the list and remove each item that was
							// selected.  

							// WARNING!!!  
							// We loop backwards, because if we removed items
							// from top to bottom, it would change the indexes of the other
							// items!!!

							for(i = count - 1; i >= 0; i--)
							{
								SendMessage(hList, LB_DELETESTRING, (WPARAM)buf[i], 0);
							}

							GlobalFree(buf);
						}
						else 
						{
							MessageBox(hwnd, TEXT("No items selected."), TEXT("Warning"), MB_OK);
						}
					}
					else
					{
						MessageBox(hwnd, TEXT("Error counting items :("), TEXT("Warning"), MB_OK);
					}
				}
				break;
				case IDC_CREATE_TEAM_CLEAR:
					SendDlgItemMessage(hwnd, IDC_CREATE_TEAM_LIST, LB_RESETCONTENT, 0, 0);
				break;
				case IDC_CREATE_TEAM_LIST:
					switch(HIWORD(wParam))
					{
						case LBN_SELCHANGE:
						{
							// Get the number of items selected.

							HWND hList = GetDlgItem(hwnd, IDC_CREATE_TEAM_LIST);
							int count = SendMessage(hList, LB_GETSELCOUNT, 0, 0);
							if(count != LB_ERR)
							{
								// We only want to continue if one and only one item is
								// selected.

								if(count == 1)
								{
									// Since we know ahead of time we're only getting one
									// index, there's no need to allocate an array.

									int index;
									int err = SendMessage(hList, LB_GETSELITEMS, (WPARAM)1, (LPARAM)&index);
									if(err != LB_ERR)
									{
										// Get the data we associated with the item above
										// (the number of times it was added)

										int data = SendMessage(hList, LB_GETITEMDATA, (WPARAM)index, 0);

									//	SetDlgItemInt(hwnd, IDC_SHOWCOUNT, data, FALSE);
									}
									else 
									{
										MessageBox(hwnd, TEXT("Error getting selected item :("), TEXT("Warning"), MB_OK);
									}
								}
								else 
								{
									// No items selected, or more than one
									// Either way, we aren't going to process this.
									//SetDlgItemText(hwnd, IDC_SHOWCOUNT, "-");
								}
							}
							else
							{
								MessageBox(hwnd, TEXT("Error counting items :("), TEXT("Warning"), MB_OK);
							}
						}
						break;
					}
				break;
			}
		break;
		
		case WM_CLOSE:
			EndDialog(hwnd, 0);
		break;
		default:
			return FALSE;
	}
	return TRUE;
}