#include "TETRIS.h"

void gotoxy(int x,int y)
{
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

void Clean_Cussor()	// Ä¿¼­¸¦ Áö¿ì´Â ÇÔ¼ö 
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void setcolor(int color, int bgcolor) 
{
    color &= 0xf;
    bgcolor &= 0xf;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}

cl_GameManger::cl_GameManger() : DownKey(false), iStage(1)
{
	OutPrintIntro();
	ResetMap();
	//OutPrintBlock();
}

void cl_GameManger::SetPosFirst(int Ypos)	// ºí·ÏÁÂÇ¥¸¦ ½ÃÀÛÁöÁ¡À¸·Î ¿Å±â´Â ÇÔ¼ö 
{
	iThisXpos = 3;
	iThisYpos = Ypos;
	return; 
}
 
void cl_GameManger::ResetMap()
{
	PauseCheck = false;
	bFirstStart = false;
	First = false;
	iScore = 0;
	iScoreTemp = 1;
	Saving = false;
	for(int i = 0; i < 7; i++)
		iNumberBlock[i] = i + 1;
	for(int i = 0; i < 24; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			if(i == 3)
			{
				cMap[i][j] = BC_MapCircle;
				cTempMap[i][j] = BC_MapCircle;
				cEndMap[i][j] = BC_MapCircle;
				cThisBlockMap[i][j] = BC_MapCircle;
				cEmpty[i][j] = BC_MapCircle;
				continue;
			}
			cMap[i][j] = BC_NONE;
			cTempMap[i][j] = BC_NONE;
			cEndMap[i][j] = BC_NONE;
			cThisBlockMap[i][j] = BC_NONE;
			cEmpty[i][j] = BC_NONE;
		}
	}	
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			cNEXT[i][j] = BC_NONE;
			cThisBlock[i][j] = BC_NONE;
			cRotationBlock[i][j] = BC_NONE;
			cSaveBlock[i][j] = BC_NONE;
		}
	}
	iNextBlock = BS_NONE;
	iThisBlock = BS_NONE; 
	iSaveBlock = BS_NONE; 
	iTempSave = BS_NONE;
	iTempNEXT = BS_NONE;
}

void cl_GameManger::SetIntroColor(int Word, int Color)	// ÀÎÆ®·Î ±ÛÀÚ¸¦ Ãâ·ÂÇÏ´Â ÇÔ¼ö 
{
	setcolor(Color, 0);
	switch(Word)
	{
		case WS_T1:
			gotoxy(4,2);	cout <<  "¡á¡á¡á¡á¡á¡á";
			gotoxy(4,3);	cout <<  "¡á¡á¡á¡á¡á¡á";
			gotoxy(4,4);	cout <<  "¡¡¡¡¡á¡á¡¡¡¡";
			gotoxy(4,5);	cout <<  "¡¡¡¡¡á¡á¡¡¡¡";
			gotoxy(4,6);	cout <<  "¡¡¡¡¡á¡á¡¡¡¡";
			gotoxy(4,7);	cout <<  "¡¡¡¡¡á¡á¡¡¡¡";
			gotoxy(4,8); 	cout <<  "¡¡¡¡¡á¡á¡¡¡¡";
			gotoxy(4,9); 	cout <<  "¡¡¡¡¡á¡á¡¡¡¡";
			gotoxy(4,10); 	cout <<  "¡¡¡¡¡á¡á¡¡¡¡";
			gotoxy(4,11); 	cout <<  "¡¡¡¡¡á¡á¡¡¡¡";
			break;                               
		case WS_E:                            
			gotoxy(18,2);	cout <<	"¡á¡á¡á¡á¡á";
			gotoxy(18,3);	cout <<	"¡á¡á¡á¡á¡á";
			gotoxy(18,4);	cout <<	"¡á¡á¡¡¡¡¡¡";
			gotoxy(18,5);	cout <<	"¡á¡á¡¡¡¡¡¡";
			gotoxy(18,6);	cout <<	"¡á¡á¡á¡á¡á";
			gotoxy(18,7);	cout <<	"¡á¡á¡á¡á¡á";
			gotoxy(18,8); 	cout <<	"¡á¡á¡¡¡¡¡¡";
			gotoxy(18,9); 	cout <<	"¡á¡á¡¡¡¡¡¡";
			gotoxy(18,10); 	cout <<	"¡á¡á¡á¡á¡á";
			gotoxy(18,11); 	cout <<	"¡á¡á¡á¡á¡á";
			break;                               
		case WS_T2:                           
			gotoxy(30,2);	cout <<  "¡á¡á¡á¡á¡á¡á";
			gotoxy(30,3);	cout <<  "¡á¡á¡á¡á¡á¡á";
			gotoxy(30,4);	cout <<  "¡¡¡¡¡á¡á¡¡¡¡";
			gotoxy(30,5);	cout <<  "¡¡¡¡¡á¡á¡¡¡¡";
			gotoxy(30,6);	cout <<  "¡¡¡¡¡á¡á¡¡¡¡";
			gotoxy(30,7);	cout <<  "¡¡¡¡¡á¡á¡¡¡¡";
			gotoxy(30,8); 	cout <<  "¡¡¡¡¡á¡á¡¡¡¡";
			gotoxy(30,9); 	cout <<  "¡¡¡¡¡á¡á¡¡¡¡";
			gotoxy(30,10); 	cout <<  "¡¡¡¡¡á¡á¡¡¡¡";
			gotoxy(30,11); 	cout <<  "¡¡¡¡¡á¡á¡¡¡¡";
			break;                               
		case WS_R:                            
			gotoxy(44,2);	cout <<	"¡á¡á¡á¡á¡á¡¡¡¡";
			gotoxy(44,3);	cout <<	"¡á¡á¡á¡á¡á¡á¡¡";
			gotoxy(44,4);	cout <<	"¡á¡á¡¡¡¡¡á¡á¡¡";
			gotoxy(44,5);	cout <<	"¡á¡á¡¡¡¡¡á¡á¡¡";
			gotoxy(44,6);	cout <<	"¡á¡á¡á¡á¡á¡á¡¡";
			gotoxy(44,7);	cout <<	"¡á¡á¡á¡á¡á¡¡¡¡";
			gotoxy(44,8); 	cout <<	"¡á¡á¡¡¡á¡á¡¡¡¡";
			gotoxy(44,9); 	cout <<	"¡á¡á¡¡¡¡¡á¡á¡¡";
			gotoxy(44,10); 	cout <<	"¡á¡á¡¡¡¡¡¡¡á¡á";
			gotoxy(44,11); 	cout <<	"¡á¡á¡¡¡¡¡¡¡á¡á";
			break;                               
		case WS_I:
			gotoxy(60,2);	cout <<	"¡á¡á¡á¡á¡á¡á";
			gotoxy(60,3);	cout <<	"¡á¡á¡á¡á¡á¡á";
			gotoxy(60,4);	cout <<	"¡¡¡¡¡á¡á¡¡¡¡";
			gotoxy(60,5);	cout <<	"¡¡¡¡¡á¡á¡¡¡¡";
			gotoxy(60,6);	cout <<	"¡¡¡¡¡á¡á¡¡¡¡";
			gotoxy(60,7);	cout <<	"¡¡¡¡¡á¡á¡¡¡¡";
			gotoxy(60,8); 	cout <<	"¡¡¡¡¡á¡á¡¡¡¡";
			gotoxy(60,9); 	cout <<	"¡¡¡¡¡á¡á¡¡¡¡";
			gotoxy(60,10); 	cout <<	"¡á¡á¡á¡á¡á¡á";
			gotoxy(60,11); 	cout <<	"¡á¡á¡á¡á¡á¡á";
			break;
		case WS_S:
			gotoxy(74,2);	cout <<	"¡¡¡á¡á¡á¡á¡á";
			gotoxy(74,3);	cout <<	"¡á¡á¡á¡á¡á¡á";
			gotoxy(74,4);	cout <<	"¡á¡á¡¡¡¡¡¡¡¡";
			gotoxy(74,5);	cout <<	"¡á¡á¡¡¡¡¡¡¡¡";
			gotoxy(74,6);	cout <<	"¡á¡á¡á¡á¡á¡¡";
			gotoxy(74,7);	cout <<	"¡¡¡á¡á¡á¡á¡á";
			gotoxy(74,8); 	cout <<	"¡¡¡¡¡¡¡¡¡á¡á";
			gotoxy(74,9); 	cout <<	"¡¡¡¡¡¡¡¡¡á¡á";
			gotoxy(74,10); 	cout <<	"¡á¡á¡á¡á¡á¡á";
			gotoxy(74,11); 	cout <<	"¡á¡á¡á¡á¡á¡¡";
			break;
	}
	setcolor(0, 0);
	//Clean_Cussor();
}

void cl_GameManger::OutPrintIntro()	// ÀÎÆ®·Î¸¦ Ãâ·ÂÇÏ´Â ÇÔ¼ö 
{
	Clean_Cussor();
	system("mode con cols=91 lines=18");
	setcolor(15, 0);gotoxy(37,14);cout << "- Press AnyKey -";
	int COLOR[6] = {10, 11, 12, 13, 14, 15};
	gotoxy(4,13);	cout << "¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡MADE BY GarryMilk";
	while(true)
	{
		SetIntroColor(WS_T1, COLOR[0]);
		SetIntroColor(WS_E, COLOR[1]);
		SetIntroColor(WS_T2, COLOR[2]);
		SetIntroColor(WS_R, COLOR[3]);
		SetIntroColor(WS_I, COLOR[4]);
		SetIntroColor(WS_S, COLOR[5]);
		for(int i = 0; i < 6; i++)
		{
			COLOR[i]--;
			if(COLOR[i] < 10)COLOR[i] = 15;
		}
		if(kbhit())break;
		Sleep(120);
	}
	system("cls");
	while(kbhit())getch();
	setcolor(7, 0);
	return;
}

void cl_GameManger::OutPrintMap()	// ¸ÊÀ» ¸ÊÀ» Ãâ·ÂÇÏ´Â ÇÔ¼ö
{
	// xÁÂÇ¥ : 3 ~ 22	YÁÂÇ¥ : 1 ~ 20 	ºí·Ï ½ÃÀÛ ÁÂÇ¥ :  x(8), y(1)
	// NEXT ÁÂÇ¥ : x 24 ~ 30	y 2 ~ 5
	// SAVE ÁÂÇ¥ : x 24 ~ 30	y 9 ~ 12
	system("mode con cols=61 lines=22");
	cout << "¡á¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡á¡¡NEXT¡¡¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡" << endl;
	cout << "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡á¡á¡á¡á¡¡¡¡¡¡¡¡ºí·Ï µ¹¸®±â¡¡¡¡¡¡ " << endl;
	cout << "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡" << endl;
	cout << "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡¡¡¡¡¡¡¡â¡¡¡¡¡¡¡¡¡¡¡¡" << endl;
	cout << "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡" << endl;
	cout << "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡¿ÞÂÊ¡¡¢·¡¡¡¡¡¡¢¹¡¡¿À¸¥ÂÊ" << endl;
	cout << "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡á¡á¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡" << endl;
	cout << "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡¡SAVE¡¡¡á¡¡¡¡¡¡¡¡¡¡¡¡¡ä¡¡¡¡¡¡¡¡¡¡¡¡" << endl;
	cout << "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡á¡á¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡" << endl;
	cout << "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡¡¡»¡¸® ³»¸®±â¡¡¡¡¡¡ " << endl;
	cout << "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡¡¡¡¡ ¡¡¡¡¡¡¡¡¡¡¡¡¡¡ " << endl;
	cout << "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡¡¡ SPACE BAR¡¡¡¡" << endl;
	cout << "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡ ÇÑ¹ø¿¡ ³»¸®±â" << endl;
	cout << "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡á¡á¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡" << endl;
	cout << "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡S  ºí·Ï ÀúÀåÇÏ±â ¡¡ " << endl;
	cout << "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡¡LEVEL ¡¡¡¡¡¡ "<< endl;
	cout << "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡¡¡¡" << iStage << "¡¡¡¡¡¡ ¡¡D  ºí·Ï ºÒ·¯¿À±â" << endl;
	cout << "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡" << endl;
	cout << "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡P¡¡°ÔÀÓ ¸ØÃß±â¡¡" << endl;
	cout << "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡¡SCORE¡¡ ¡¡¡¡ " << endl;
	cout << "¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡K¡¡°ÔÀÓ Á¾·áÇÏ±â¡¡" << endl;
	cout << "¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡";                               
}         

bool cl_GameManger::CheckingMap()	// ¸ÊÀ» ºñ±³ ¹× ÀçÃâ·ÂÇÏ´Â ÇÔ¼ö                                   
{
	if(OutPrintScore() == false)
	{
		return true;
	}
	ReprintNextSave();	// ´ÙÀ½ºí·Ï°ú ÀúÀåºí·ÏÀ» Ãâ·ÂÇÏ´Â ÇÔ¼ö
	for(int i = 3; i < 24; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			if(i == 3 && cMap[i][j] == cTempMap[i][j] && cMap[i][j] == BC_NONE)
			{
				//cout << cMap[3][j];
				//cMap[i][j] = BC_MapCircle;
				//cTempMap[i][j] = BC_MapCircle;
				RePrintStartLine(j);
			}
			if(cMap[i][j] != cTempMap[i][j] || PauseCheck == true)	// ±âÁ¸¿¡ ÀúÀåµÈ ¸ÊÀÌ ¹Ù²ñ¸Ê°ú ´Ù¸£¸é ÀçÃâ·Â 
			{
				//cout <<"i:" << i <<"	" <<"j :" << j;
				RePrintMap(j, i);	// ¹è¿­ÀÇ °ªÀ» º¸³»¼­ À§Ä¡¸¦ Ç¥½ÃÇÏ´Â ¹æ½ÄÀÓ.. 
				cMap[i][j] = cTempMap[i][j];			// ¿ø·¡¸ÊÀ¸·Î µ¹·Á³õ´Â´Ù. 
			}
		}
	}
	return false;
}

void cl_GameManger::RePrintMap(int Xpos, int Ypos)	// ¸ÊÀ» ´Ù½Ã Ãâ·ÂÇÏ´Â ÇÔ¼ö
{
	// xÁÂÇ¥ : 3 ~ 22	YÁÂÇ¥ : 1 ~ 20 	ºí·Ï ½ÃÀÛ ÁÂÇ¥ :  x(8), y(1)
	// NEXT ÁÂÇ¥ : x 24 ~ 30	y 2 ~ 5
	// SAVE ÁÂÇ¥ : x 24 ~ 30	y 9 ~ 12
	gotoxy(Xpos * 2 + 2, Ypos - 3);
	//cout << "y :" << Ypos;
	ColorBlockPrint(cTempMap[Ypos][Xpos]);
}

void cl_GameManger::ReprintNextSave()	// ´ÙÀ½ºí·Ï°ú ÀúÀåºí·ÏÀ» Ãâ·ÂÇÏ´Â ÇÔ¼ö 
{
//	static bool First = false;
	int xPos, yPos;
	// NEXT ÁÂÇ¥ : x 24 ~ 30	y 2 ~ 5
	// SAVE ÁÂÇ¥ : x 24 ~ 30	y 9 ~ 12
	if(iNextBlock != iTempNEXT || First == false || PauseCheck == true)
	{
		xPos = 24;
		yPos = 2;
		for(int i = 0; i < 4; i++)
		{
			gotoxy(xPos, yPos);
			for(int j = 0; j < 4; j++)
			{ 
				ColorBlockPrint(cNEXT[i][j]);
			}
			yPos++;
		}
		iTempNEXT = iNextBlock;
	}
	if(iSaveBlock != iTempSave || PauseCheck == true)
	{
		xPos = 24;
		yPos = 9;
		for(int i = 0; i < 4; i ++)
		{
			gotoxy(xPos, yPos);
			for(int j = 0; j < 4; j++)
			{
				ColorBlockPrint(cSaveBlock[i][j]);
			}
			yPos++;
		}
		iTempSave = iSaveBlock;
	}
			
	if(First == false)First = true;
}

void cl_GameManger::ChangeNextBlock()	// ´ÙÀ½ºí·ÏÀ» Á¤ÇÏ´Â ÇÔ¼ö
{
	srand((unsigned int)time(NULL));
	
	bBlockCheck = true;	// ´ÙÀ½ºí·ÏÀÌ È£ÃâµÇ¸é ÇöÀçºí·ÏÀ» È°¼ºÈ­ÇÑ´Ù 
	bBlockActive = false;	// ¹èÁ¤µÌ´Ù´Â°Ç ¾ÆÁ÷ ¸Ê¿¡ ºí·ÏÀÌ ¼ÒÈ¯ÀÌ µÇÁö¾Ê¾ÑÀ¸´Ï ¼¼ÆÃÇØÁØ´Ù. 
	
	if(bFirstStart == false)	// Ã³À½ È£ÃâµÇ¸é ´ÙÀ½ºí·ÏÀ» ÃÊ±âÈ­ÇÑ´Ù 
	{
		iNextBlock = rand() % 7 + 1;
		bFirstStart = true;
	}
	iTempNEXT = iNextBlock;	// Àüºí·Ï¿¡ ÃÊ±âÈ­Àü ºí·Ï ÀÔ·Â 
	iThisBlock = iNextBlock;	// ÇöÀçºí·Ï¿¡ ÃÊ±âÈ­Àü ºí·Ï ÀÔ·Â 
	SetBlock(cThisBlock, iNextBlock, BT_0);
	eBlock_Turn = BT_0;
	
	int iDex1, iDex2, iTemp;
	for(int i = 0 ; i < 10; i++)
	{
		// iDex1,2 °ª¿¡ 45 ÀÌÇÏÀÇ ·£´ý°ª ºÎ¿©
		iDex1 = rand() % 7;
		iDex2 = rand() % 7;
		
		// ¼­·Î ¹Ù²ãÁØ´Ù
		iTemp = iNumberBlock[iDex1];
		iNumberBlock[iDex1] = iNumberBlock[iDex2];
		iNumberBlock[iDex2] = iTemp;
	}
	iNextBlock = iNumberBlock[rand() % 7];	// ´ÙÀ½ºí·Ï ÃÊ±âÈ­ 
	SetBlock(cNEXT, iNextBlock, BT_0);
	return;
}

void cl_GameManger::SetBlock(char cBlock[5][5], int iBlock, Block_Turn iBlock_s)		// ºí·Ï ¸ð¾çÀ» º¯¼ö¿¡ ÀÔ·ÂÇÏ´Â ÇÔ¼ö 
{
	switch(iBlock)
	{
		case BS_SQUARE:
		//	iThisBlock = BS_SQUARE;
			INPUT_BLOCK(cBlock, Block_Square, iBlock_s);	// INPUT_BLOCK() ¸ÞÅ©·Î value.h 
			break;
			
		case BS_STICK:
		//	iThisBlock = BS_STICK;
			INPUT_BLOCK(cBlock, Block_Stick, iBlock_s);
			break;
			
		case BS_ZIGZAG_L:
		//	iThisBlock = BS_ZIGZAG_L;
			INPUT_BLOCK(cBlock, Block_Zigzag_L, iBlock_s);
			break;
			
		case BS_ZIGZAG_R:
		//	iThisBlock = BS_ZIGZAG_R;
			INPUT_BLOCK(cBlock, Block_Zigzag_R, iBlock_s);
			break;
			
		case BS_POINT:
		//	iThisBlock = BS_POINT;
			INPUT_BLOCK(cBlock, Block_Point, iBlock_s);
			break;
			
		case BS_LBLOCK_L:
		//	iThisBlock = BS_LBLOCK_L;
			INPUT_BLOCK(cBlock, Block_Lblock_L, iBlock_s);
			break;
			
		case BS_LBLOCK_R:
		//	iThisBlock = BS_LBLOCK_R;
			INPUT_BLOCK(cBlock, Block_Lblock_R, iBlock_s);
			break;
	}
}

void cl_GameManger::BlockRePosition()	// ÇöÀçºí·Ï À§Ä¡¸¦ ´Ù½Ã ³ªÅ¸³»´Â ÇÔ¼ö
{
	for(int i = 0; i < 24; i++)		// ºí·Ï ÀÎ½Ä ¸ÊÀº ºí·ÏÀÌ ³»·Á¿Ã‹š ±âÁ¸¸Ê¿¡ ÀÖ´ø ºí·ÏÀ» Áö¿î´Ù. 
	{
		for(int j = 0; j < 10; j++)
		{
			cTempMap[i][j] = cEndMap[i][j];
		}
	}
	MAP_RESET(cThisBlockMap);
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(cThisBlock[i][j] != BC_NONE) 	// ¸¸¾à ºóÄ­ÀÌ ¾Æ´Ï¸é ´ëÀÔ 
			{
				cTempMap[iThisYpos + i][iThisXpos + j] = cThisBlock[i][j];	
				cThisBlockMap[iThisYpos + i][iThisXpos + j] = cThisBlock[i][j];	
			}
		}
	}
}

void cl_GameManger::ColorBlockPrint(char Color)
{
	switch(Color)
	{
		case '0':
			cout << "¡¡";
			break;
		case '1':
			setcolor(11, 0);
			cout << "¡á";
			break;
		case '2':
			setcolor(12, 0);
			cout << "¡á";
			break;
		case '3':
			setcolor(9, 0);
			cout << "¡á";
			break;
		case '4':
			setcolor(2, 0);
			cout << "¡á";
			break;
		case '5':
			setcolor(13, 0);
			cout << "¡á";
			break;
		case '6':
			setcolor(14, 0);
			cout << "¡á";
			break;
		case '7':
			setcolor(10, 0);
			cout << "¡á";
			break;
		case '8':
			cout << "¡£";
			break;
	}
	setcolor(7, 0);
}

void cl_GameManger::RePrintStartLine(int Xpos)
{
	gotoxy(Xpos*2 + 2, 0);
	cout << "¡£";
	return;
}

bool cl_GameManger::OutPrintScore()	// Á¡¼öÈ­¸éÀ» Ãâ·ÂÇÏ´Â ÇÔ¼ö
{
	if(iScore >= 2500 + (2500 * iStage))
	{
		gotoxy(25, 20);
		cout << iScore;
		return false;
	}
	if(iScore != iScoreTemp) 
	{
		if(iScore < 10)
			gotoxy(30, 20);
		else if(iScore >= 10 && iScore < 100)
			gotoxy(29, 20);
		else if(iScore >= 100 && iScore < 1000)
			gotoxy(28, 20);
		else if(iScore >= 1000 && iScore < 10000)
			gotoxy(27, 20);
		else if(iScore >= 10000 && iScore < 100000)
			gotoxy(26, 20);
		else if(iScore >= 100000 && iScore < 1000000)
			gotoxy(25, 20);	
		cout << iScore;
		iScoreTemp = iScore;
	}
	return true;
}

void cl_GameManger::OutPrintBlock()
{
	for(int t= 0; t < 7; t++)
	{
			for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				for(int p = 0; p < 4; p++)
				{
					switch(t)
					{
						case 0:
							ColorBlockPrint(Block_Square[i][j][p]);
							break;
						case 1:
							ColorBlockPrint(Block_Stick[i][j][p]);
							break;
						case 2:
							ColorBlockPrint(Block_Zigzag_L[i][j][p]);
							break;
						case 3:
							ColorBlockPrint(Block_Zigzag_R[i][j][p]);
							break;
						case 4:
							ColorBlockPrint(Block_Point[i][j][p]);
							break;
						case 5:
							ColorBlockPrint(Block_Lblock_L[i][j][p]);
							break;
						case 6:
							ColorBlockPrint(Block_Lblock_R[i][j][p]);
							break;
					}
				}
				cout << endl;
			}
			cout << endl;
		}
	}
	
	system("pause");
}

bool cl_GameManger::PrintBlock() 	// ºí·ÏÀ» ±×¸®´Â ÇÔ¼ö 
{
	// xÁÂÇ¥ : 3 ~ 22	YÁÂÇ¥ : 1 ~ 20 	ºí·Ï ½ÃÀÛ ÁÂÇ¥ :  x(8), y(1)
	// NEXT ÁÂÇ¥ : x 24 ~ 30	y 2 ~ 5
	// SAVE ÁÂÇ¥ : x 24 ~ 30	y 9 ~ 12
	switch(iThisBlock)
	{
		case BS_STICK:
			SetPosFirst();
			break;
		case BS_SQUARE:
		case BS_ZIGZAG_L:
		case BS_ZIGZAG_R:
		case BS_POINT:
		case BS_LBLOCK_L:
		case BS_LBLOCK_R:
			SetPosFirst(2);
			break;
	}
	
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(cThisBlock[i][j] != BC_NONE) 	// ¸¸¾à ºóÄ­ÀÌ ¾Æ´Ï¸é ´ëÀÔ 
			{
				if(!(cTempMap[iThisYpos + i][iThisXpos + j] == BC_NONE || cTempMap[iThisYpos + i][iThisXpos + j] == BC_MapCircle))	// ½ÃÀÛÄ­¿¡ ºí·ÏÀÌ ÀÖÀ¸¸é °ÔÀÓ¿À¹ö 
					return false;
				cTempMap[iThisYpos + i][iThisXpos + j] = cThisBlock[i][j];	
				cThisBlockMap[iThisYpos + i][iThisXpos + j] = cThisBlock[i][j];				
			}

		}
	}
	bBlockActive = true;
	return true;
}

 bool cl_GameManger::BlockDown()	// ºí·ÏÀÌ ³»·Á°¡´Â ÇÔ¼ö 
{
	static int iLate = 0;	// ºí·ÏÀÌ ³»·Á¿À´Â ½Ã°£ 
	if(iLate != iStageSpeed)
	{
		iLate++;
		return true;
	}
	else iLate = 0;	// ºí·ÏÀÌ ³»·Á¿À´Â ½Ã°£ 
	
	
	if(BlockCollisoinCheck())	// ºí·ÏÀÌ Ãæµ¹ÇÏ¸é
	{
		for(int i = 0; i < 24; i++)		// ºí·Ï ÀÎ½Ä ¸ÊÀº ºí·ÏÀÌ ³»·Á¿Ã‹š ±âÁ¸¸Ê¿¡ ÀÖ´ø ºí·ÏÀ» Áö¿î´Ù. 
		{
			for(int j = 0; j < 10; j++)
			{
				cEndMap[i][j] = cTempMap[i][j];
				cThisBlockMap[i][j] = BC_NONE;
			}
		}
		return false; 	
	}
	iThisYpos++;	// Y°ªÀ» Áõ°¡½ÃÄÑ¼­ ÁÂÇ¥¸¦ ÇÑÄ­ ³»¸°´Ù.
	
	for(int i = 0; i < 24; i++)		// ºí·Ï ÀÎ½Ä ¸ÊÀº ºí·ÏÀÌ ³»·Á¿Ã‹š ±âÁ¸¸Ê¿¡ ÀÖ´ø ºí·ÏÀ» Áö¿î´Ù. 
	{
		for(int j = 0; j < 10; j++)
		{
			cTempMap[i][j] = cEndMap[i][j];
		}
	}
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(cThisBlock[i][j] != BC_NONE) 	// ¸¸¾à ºóÄ­ÀÌ ¾Æ´Ï¸é ´ëÀÔ 
			{
				cTempMap[iThisYpos + i][iThisXpos + j] = cThisBlock[i][j];	
				cThisBlockMap[iThisYpos + i][iThisXpos + j] = cThisBlock[i][j];	
			}
		}
	}
	return true;
}

bool cl_GameManger::BlockCollisoinCheck()	// ºí·Ï Ãæµ¹ Ã¼Å© ºí·ÏÀÌ Ãæµ¹ÇÏ¸é true ¹ÝÈ¯ 
{
	for(int i = 0; i < 4; i++) 
	{
		for(int j = 0; j < 4; j++)
		{
			if(!(cThisBlockMap[iThisYpos + i][iThisXpos + j] == BC_NONE || cThisBlockMap[iThisYpos + i][iThisXpos + j] == BC_MapCircle) && iThisYpos + i < 24)	
			{
				//cout << "i : " << i << " j : " << j;
				if(iThisYpos + i == 23 && iThisXpos + j < 10)	// ºí·ÏºÎºÐÀÌ ¶¥¿¡´êÀ¸¸é 
				{
				//	cout << "bug" << iThisYpos + i ;
					return true; 
				}
				if(!(cEndMap[iThisYpos + i + 1][iThisXpos + j] == BC_NONE || cEndMap[iThisYpos + i + 1][iThisXpos + j] == BC_MapCircle) && iThisXpos + j < 10)	// ¹Ì¸® ½×¿©ÀÖ´Â ºí·ÏÀÌ ÀÖÀ¸¸é 
				{
					//cout << iThisYpos + i + 1  << "  " << iThisXpos + j;
					return true;					
				}

			} 
		}
	}
	return false;
}

void cl_GameManger::KeyInput(unsigned char Key)	// Å°¸¦ ÀÔ·Â¹Þ´Â ÇÔ¼ö
{
	switch(Key)
	{
		case 32:
			while(BlockDown() != false);
			bBlockCheck = false; 
			bBlockActive = false;
			break;
		case 75:
			BlockLeft();
			break;
		case 77:
			BlockRight();
			break;
		case 72:
			BlockRotation();
			break;
		case 80:
			for(int i = 0; i < 2; i++)
			if(BlockDown() == false)	// ºí·ÏÀ» ÇÑÄ­ ³»¸®°í Ãæµ¹ÇÏ¸é
			{
				bBlockCheck = false; 
				bBlockActive = false;
				DownKey = true;
			}
			break;
		case 100:
		case 68:
			BlockLoad();
			break;	
		case 115:
		case 83:
			BlockSave();
			break;	
		case 112:
		//case 80:
			GamePause();
			break;
	}
}

void cl_GameManger::BlockRotation()	// ºí·Ï È¸Àü 
{
	Block_Turn eTurnTemp = eBlock_Turn;
	switch(eBlock_Turn)	// ¹æÇâÀüÈ¯ 
	{
		case BT_0:
			eBlock_Turn = BT_90;
			break;
		case BT_90:
			eBlock_Turn = BT_180;
			break;
		case BT_180:
			eBlock_Turn = BT_270;
			break;
		case BT_270:
			eBlock_Turn = BT_0;
			break;
	}
	SetBlock(cRotationBlock, iThisBlock, eBlock_Turn);
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(cRotationBlock[i][j] != BC_NONE)
			{
				if(!(cEndMap[iThisYpos + i][iThisXpos + j] == BC_NONE || cEndMap[iThisYpos + i][iThisXpos + j] == BC_MapCircle))	// ¸¸¾à È¸ÀüµÈ ºí·Ï ÀÌ µé¾î°¥ Ä­¿¡
				{														// ´Ù¸¥ºí·ÏÀÌ ÀÖÀ¸¸é È¸ÀüÃë¼Ò 
					 eBlock_Turn = eTurnTemp;
					 return;
				}
			}
		}
	}
	SetBlock(cThisBlock, iThisBlock, eBlock_Turn);
	BlockRePosition();
}

void cl_GameManger::BlockLeft()
{
	iTempXpos = iThisXpos - 1;
	if(iTempXpos < 0)return;
	iTempYpos = iThisYpos;
	SetBlock(cRotationBlock, iThisBlock, eBlock_Turn);
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(cRotationBlock[i][j] != BC_NONE)
			{
				if(!(cEndMap[iTempYpos + i][iTempXpos + j] == BC_NONE || cEndMap[iTempYpos + i][iTempXpos + j] == BC_MapCircle))	
				{														
					 return;
				}
			}
		}
	}
	iThisXpos--;
	BlockRePosition();
}
void cl_GameManger::BlockRight()
{
	iTempXpos = iThisXpos + 1;
	if(iTempXpos > 9)return;
	iTempYpos = iThisYpos;
	SetBlock(cRotationBlock, iThisBlock, eBlock_Turn);
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(cRotationBlock[i][j] != BC_NONE)
			{
				if(!(cEndMap[iTempYpos + i][iTempXpos + j] == BC_NONE || cEndMap[iTempYpos + i][iTempXpos + j] == BC_MapCircle) || iTempXpos + j > 9)	
				{				
					 return;
				}
			}
		}
	}
	iThisXpos++;
	BlockRePosition();
}

void cl_GameManger::BlockSave()	// ºí·ÏÀ» ¼¼ÀÌºêÇÏ´Â Å° ÇÔ¼ö
{
	if(Saving == true)return;	// ÀÌ¹Ì ÀúÀåµÈ ºí·ÏÀÌ ÀÖÀ¸¸é ¸®ÅÏ 
	// ¼¼ÀÌºêºí·Ï¿¡ ÇöÀçºí·Ï ´ëÀÔ 
	eBlock_Turn = BT_0;
	Block_RESET(cSaveBlock);
	
	iSaveBlock = iThisBlock;
	SetBlock(cSaveBlock, iThisBlock, BT_0);
	//BLOCK_SUB(cSaveBlock, cThisBlock);
	Saving = true;
	
	// cTempMap ¿¡ cEndMap °ªÀ» ´ëÀÔÇÏ¸é ¸ÊÀçÃâ·Â ÇÔ¼ö¿¡¼­ ÇöÀçºí·ÏÀÌ »ç¶óÁø´Ù 
	MAP_SUB(cTempMap, cEndMap);
	MAP_RESET(cThisBlockMap);
	DownKey = true;	// ´Ù¿îÅ°¸¦ È°¼ºÈ­ÇÏ¸é RunÇÔ¼ö¿¡¼­ ÀÚµ¿À¸·Î ºí·ÏÀÌ ¸Ê¿¡¼­ ¾ø¾îÁø°ÍÀ¸·Î ÆÇÁ¤ÇÑ´Ù. 
	return;
}

void cl_GameManger::BlockLoad()	// ºí·ÏÀ» ºÒ·¯¿À´Â Å° ÇÔ¼ö 
{
	if(Saving == false)return;
	eBlock_Turn = BT_0;
	// iThisBlock -> iNextBlock
	// iSaveBlock -> iThisBlock
	iNextBlock = iThisBlock;
	BLOCK_SUB(cNEXT, cThisBlock);
	
	Block_RESET(cThisBlock);
	
	iThisBlock = iSaveBlock;
	iSaveBlock = BS_NONE;
	Block_RESET(cSaveBlock);
	
	SetBlock(cThisBlock, iThisBlock, BT_0);
	//BLOCK_SUB(cThisBlock, cSaveBlock);
	MAP_SUB(cTempMap, cEndMap);	// ÇöÀç¸Ê¿¡ÀÖ´Â ºí·ÏÀ» ¾ø¿£´Ù. 
	
	MAP_RESET(cThisBlockMap);
	
	PrintBlock();
	Saving = false;
}

void cl_GameManger::GamePause()	 // °ÔÀÓÀ» Á¤Áö½ÃÅ°´Â ÇÔ¼ö
{
	setcolor(7, 0);
	gotoxy(7, 7);	cout << "¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á";
	gotoxy(7, 8);	cout << "¡á                                            ¡á";
	gotoxy(7, 9);	cout << "¡á         G A M E          P A U S E         ¡á";
	gotoxy(7, 10);	cout << "¡á                                            ¡á";
	gotoxy(7, 11);	cout << "¡á              - Press AnyKey -              ¡á";
	gotoxy(7, 12);	cout << "¡á                                            ¡á";
	gotoxy(7, 13);	cout << "¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á";
	getch();
	
	system("cls");
	PauseCheck = true;
	
	OutPrintMap();			// ¸ÊÀçÃâ·Â 
	CheckingMap();
	 
	
	PauseCheck = false;
}

void cl_GameManger::StageClear()	// ½ºÅ×ÀÌÁö Å¬¸®¾î 
{
	if(iStage < 5)
	{
		setcolor(11, 0);
		gotoxy(7, 7);	cout << "¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á";
		gotoxy(7, 8);	cout << "¡á                                            ¡á";
		gotoxy(7, 9);	cout << "¡á        S T A G E " << iStage << "         C L E A R       ¡á";
		gotoxy(7, 10);	cout << "¡á                                            ¡á";
		gotoxy(7, 11);	cout << "¡á              - Press AnyKey -              ¡á";
		gotoxy(7, 12);	cout << "¡á                                            ¡á";
		gotoxy(7, 13);	cout << "¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á";
		getch();
	}
	else if(iStage == 5)
	{
		setcolor(11, 0);
		gotoxy(7, 7);	cout << "¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á";
		gotoxy(7, 8);	cout << "¡á                                            ¡á";
		gotoxy(7, 9);	cout << "¡á      F I N A L  S T A G E  C L E A R       ¡á";
		gotoxy(7, 10);	cout << "¡á                                            ¡á";
		gotoxy(7, 11);	cout << "¡á              - Press AnyKey -              ¡á";
		gotoxy(7, 12);	cout << "¡á                                            ¡á";
		gotoxy(7, 13);	cout << "¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á";
		getch();
	}
	
	if(iStage < 4)
	{
		setcolor(10, 0);
		gotoxy(7, 7);	cout << "¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á";
		gotoxy(7, 8);	cout << "¡á                                            ¡á";
		gotoxy(7, 9);	cout << "¡á        S T A G E " << iStage + 1<< "         S R A R T       ¡á";
		gotoxy(7, 10);	cout << "¡á                                            ¡á";
		gotoxy(7, 11);	cout << "¡á              - Press AnyKey -              ¡á";
		gotoxy(7, 12);	cout << "¡á                                            ¡á";
		gotoxy(7, 13);	cout << "¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á";
		getch();
	}
	else if(iStage == 4)
	{
		setcolor(10, 0);
		gotoxy(7, 7);	cout << "¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á";
		gotoxy(7, 8);	cout << "¡á                                            ¡á";
		gotoxy(7, 9);	cout << "¡á      F I N A L  S T A G E  S T A R T       ¡á";
		gotoxy(7, 10);	cout << "¡á                                            ¡á";
		gotoxy(7, 11);	cout << "¡á              - Press AnyKey -              ¡á";
		gotoxy(7, 12);	cout << "¡á                                            ¡á";
		gotoxy(7, 13);	cout << "¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á";
		getch();
	}
	setcolor(7, 0);	
}

void cl_GameManger::StageFail()	// ½ºÅ×ÀÌÁö ÆÐºñ
{
	setcolor(12, 0);
	gotoxy(7, 7);	cout << "¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á";
	gotoxy(7, 8);	cout << "¡á                                            ¡á";
	gotoxy(7, 9);	cout << "¡á         G A M E           O V E R          ¡á";
	gotoxy(7, 10);	cout << "¡á                                            ¡á";
	gotoxy(7, 11);	cout << "¡á              - Press AnyKey -              ¡á";
	gotoxy(7, 12);	cout << "¡á                                            ¡á";
	gotoxy(7, 13);	cout << "¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á";
	getch();
	setcolor(7, 0);
}

bool cl_GameManger::CheckingLine()	// Å×Æ®¸®½º ¶óÀÎÀ» Ã¼Å©ÇÏ´Â ÇÔ¼ö
{
	int Num = 0;
	Num = 0;
	int LINE[24] = {0, };
	for(int i = 23; i >= 0; i--)
	{
		for(int j = 0; j < 10; j++)
		{
			if(!(cEndMap[i][j] == BC_NONE || cEndMap[i][j] == BC_MapCircle))LINE[i]++;
			if(LINE[i] == 10)
			{
				setcolor(0, 15);
				gotoxy(2, i - 3);
				Num++;
				if(Num > 3)
					cout << "¡¡¡¡¡¡ TETRIS!¡¡¡¡¡¡";
				else
					cout << "¡¡¡¡¡¡"<< Num << " COMBO!¡¡¡¡¡¡";
				setcolor(7, 0);
				for(int t = 0; t < 10; t++)	// ¶óÀÎ Å¬¸®¾î ´ë¸é ÇØ´ç ¶óÀÎÀ» ´Ù °ø¹éÀ¸·Î ¸¸µç´Ù 
					cEndMap[i][t] = BC_NONE;
			}
		}
	}
	MAP_RESET(cEmpty);
	if(Num > 0) 	// ¸¸¾à ¶óÀÎÀÌ ÇÏ³ªÀÌ»ó Å¬¸®¾î µÌÀ¸¸é
	{
		bool StartLineCheck = false;
		GetScore(Num);
		Sleep(500);
		MAP_RESET(cEmpty);
		int EmptyYpos = 23;
		for(int i = 23; i >= 0; i--)
		{
			for(int j = 0; j < 10; j++)
			{
				if(LINE[i] != 10)
				{
					if(cEndMap[i][j] == BC_MapCircle)
						continue;
					cEmpty[EmptyYpos][j] = cEndMap[i][j];
					if(j == 9)EmptyYpos--;
				}
			}
		}
		for(int i =0 ; i < 10 ; i++)
			cEmpty[3][i] = BC_MapCircle;
		MAP_RESET(cEndMap);
		MAP_SUB(cEndMap, cEmpty);
		for(int i = 3 ; i < 24 ; i++)
		{
			for(int j = 0; j < 10; j++)
			{
				RePrintEndMap(j, i);
			}
		}
	} 
}

void cl_GameManger::RePrintEndMap(const int Xpos, const int Ypos)
{
	gotoxy(Xpos * 2 + 2, Ypos - 3);
	ColorBlockPrint(cEndMap[Ypos][Xpos]);
}

void cl_GameManger::GetScore(int iNum)	// ½ºÄÚ¾î¸¦ È×µæÇÏ´Â ÇÔ¼ö 
{
	int iPlus = 0;;
	switch(iNum)
	{
		case 1:
			iPlus = 40 * iStage;
			break;
		case 2:
			iPlus = 100 * iStage;
			break;
		case 3:
			iPlus = 300 * iStage;
			break;
		case 4:
			iPlus = 1200 * iStage;
			break;
	}
	iScore += iPlus;
}

void cl_GameManger::StageDeficullty()	// ½ºÅ×ÀÌÁö ³­ÀÌµµ
{
	switch(iStage)
	{
		case 1:
			iStageSpeed = 15;
			break;
		case 2:
			iStageSpeed = 13;
			break;
		case 3:
			iStageSpeed = 11;
			break;
		case 4:
			iStageSpeed = 9;
			break;
		case 5:
			iStageSpeed = 7;
			break;
	}
}

bool cl_GameManger::CheckEnding()	// °ÔÀÓ ¿£µù ÇÔ¼ö
{
	if(iStage > 5)
	{
		system("mode con cols=141 lines=19") ;
		// YOU WIN
		gotoxy(4,2);	cout <<	"¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡á¡á¡á¡á¡á¡á¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡á¡á";
		gotoxy(4,3);	cout <<	"¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡á¡á¡á¡á¡á¡á¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡á¡¡¡á¡á";
		gotoxy(4,4);	cout <<	"¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡á¡á¡á¡á¡¡¡á¡á";
		gotoxy(4,5);	cout <<	"¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡á¡á¡¡¡á¡á";
		gotoxy(4,6);	cout << "¡¡¡¡¡á¡á¡á¡á¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡á¡á"; 
		gotoxy(4,7);	cout << "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡á¡á¡¡¡á¡á"; 
		gotoxy(4,8); 	cout << "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡á¡á¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡á¡á¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡á¡á¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡á¡á";
		gotoxy(4,9); 	cout << "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡á¡á¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡á¡á¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡á¡á¡á¡á¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡";
		gotoxy(4,10);	cout << "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡á¡á¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡á¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡á¡á¡á¡á¡¡¡á¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡á¡á";
		gotoxy(4,11);	cout << "¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡¡¡¡¡¡¡á¡á¡á¡á¡á¡á¡¡¡á¡á¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡á¡á¡¡¡á¡á";
		gotoxy(4,13);	cout << "¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡MADE BY GarryMilk¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡";
		getch();
		return false;
	}
	return true;
}

void cl_GameManger::RESET()
{
	setcolor(7, 0);
	ResetMap();
	//ReadBlock();
	return ;
}

bool cl_GameManger::RUN()	// °ÔÀÓÀ» ±¸µ¿ÇÏ´Â ÇÔ¼ö 
{
	unsigned char Key = 0;
	StageDeficullty();
	Clean_Cussor();
	system("title TETRIS");
	//OutPrintIntro();
	OutPrintMap();
	ChangeNextBlock();	// ´ÙÀ½ºí·ÏÀ» ÃÊ±âÈ­ÇÑ´Ù, Ã³À½¼±¾ð½Ã Ã³À½ºí·Ï µµ ÃÊ±âÈ­µÊ 
	while(true)
	{
		if(bBlockCheck == false)	ChangeNextBlock();	// ÇöÀç ºí·ÏÀÌ ºñÈ°¼ºÈ­µÇ¸é ´ÙÀ½ºí·ÏÀ» ÀÔ·ÂÇÑ´Ù.
		if(bBlockActive == false)	// ¸Ê¿¡ ¾ÆÁ÷ ÇöÀçºí·ÏÀÌ Ãâ·ÂµÇÁö ¾Ê¾ÑÀ¸¸é Ãâ·ÂÇØÁØ´Ù. 
		{
			if(PrintBlock() == false) // ½ÃÀÛÄ­¿¡ ºí·ÏÀÌ ÀÖÀ¸¸é ÆÐ¹è 
			{
				StageFail();
				return false;
			}
		}
		if(kbhit())
		{
			Key = getch();
			if(Key == 107 || Key == 75)
				return false;
			if(Key == 224)
				Key = getch();
			KeyInput(Key);
			while(kbhit())getch();
		}
		if(CheckingMap() == true)	// Âü°ªÀ» º¸³»¸é Á¡¼ö·ÎÀÎÇÑ ½ºÅ×ÀÌÁö Å¬¸®¾î 
		{
			StageClear();
			iStage++;
			bBlockCheck = false; 
			bBlockActive = false;
			return true;
		}
		if(DownKey == true)
		{
			bBlockCheck = false; 
			bBlockActive = false;
			DownKey = false;
		}
		else if(BlockDown() == false)	// ºí·ÏÀ» ÇÑÄ­ ³»¸®°í Ãæµ¹ÇÏ¸é 
		{
			bBlockCheck = false; 
			bBlockActive = false;
		}
		CheckingLine();
		Sleep(30);
	}
}
