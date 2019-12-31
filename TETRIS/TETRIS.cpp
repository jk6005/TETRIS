#include "TETRIS.h"

void gotoxy(int x,int y)
{
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

void Clean_Cussor()	// 커서를 지우는 함수 
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

void cl_GameManger::SetPosFirst(int Ypos)	// 블록좌표를 시작지점으로 옮기는 함수 
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

void cl_GameManger::SetIntroColor(int Word, int Color)	// 인트로 글자를 출력하는 함수 
{
	setcolor(Color, 0);
	switch(Word)
	{
		case WS_T1:
			gotoxy(4,2);	cout <<  "■■■■■■";
			gotoxy(4,3);	cout <<  "■■■■■■";
			gotoxy(4,4);	cout <<  "　　■■　　";
			gotoxy(4,5);	cout <<  "　　■■　　";
			gotoxy(4,6);	cout <<  "　　■■　　";
			gotoxy(4,7);	cout <<  "　　■■　　";
			gotoxy(4,8); 	cout <<  "　　■■　　";
			gotoxy(4,9); 	cout <<  "　　■■　　";
			gotoxy(4,10); 	cout <<  "　　■■　　";
			gotoxy(4,11); 	cout <<  "　　■■　　";
			break;                               
		case WS_E:                            
			gotoxy(18,2);	cout <<	"■■■■■";
			gotoxy(18,3);	cout <<	"■■■■■";
			gotoxy(18,4);	cout <<	"■■　　　";
			gotoxy(18,5);	cout <<	"■■　　　";
			gotoxy(18,6);	cout <<	"■■■■■";
			gotoxy(18,7);	cout <<	"■■■■■";
			gotoxy(18,8); 	cout <<	"■■　　　";
			gotoxy(18,9); 	cout <<	"■■　　　";
			gotoxy(18,10); 	cout <<	"■■■■■";
			gotoxy(18,11); 	cout <<	"■■■■■";
			break;                               
		case WS_T2:                           
			gotoxy(30,2);	cout <<  "■■■■■■";
			gotoxy(30,3);	cout <<  "■■■■■■";
			gotoxy(30,4);	cout <<  "　　■■　　";
			gotoxy(30,5);	cout <<  "　　■■　　";
			gotoxy(30,6);	cout <<  "　　■■　　";
			gotoxy(30,7);	cout <<  "　　■■　　";
			gotoxy(30,8); 	cout <<  "　　■■　　";
			gotoxy(30,9); 	cout <<  "　　■■　　";
			gotoxy(30,10); 	cout <<  "　　■■　　";
			gotoxy(30,11); 	cout <<  "　　■■　　";
			break;                               
		case WS_R:                            
			gotoxy(44,2);	cout <<	"■■■■■　　";
			gotoxy(44,3);	cout <<	"■■■■■■　";
			gotoxy(44,4);	cout <<	"■■　　■■　";
			gotoxy(44,5);	cout <<	"■■　　■■　";
			gotoxy(44,6);	cout <<	"■■■■■■　";
			gotoxy(44,7);	cout <<	"■■■■■　　";
			gotoxy(44,8); 	cout <<	"■■　■■　　";
			gotoxy(44,9); 	cout <<	"■■　　■■　";
			gotoxy(44,10); 	cout <<	"■■　　　■■";
			gotoxy(44,11); 	cout <<	"■■　　　■■";
			break;                               
		case WS_I:
			gotoxy(60,2);	cout <<	"■■■■■■";
			gotoxy(60,3);	cout <<	"■■■■■■";
			gotoxy(60,4);	cout <<	"　　■■　　";
			gotoxy(60,5);	cout <<	"　　■■　　";
			gotoxy(60,6);	cout <<	"　　■■　　";
			gotoxy(60,7);	cout <<	"　　■■　　";
			gotoxy(60,8); 	cout <<	"　　■■　　";
			gotoxy(60,9); 	cout <<	"　　■■　　";
			gotoxy(60,10); 	cout <<	"■■■■■■";
			gotoxy(60,11); 	cout <<	"■■■■■■";
			break;
		case WS_S:
			gotoxy(74,2);	cout <<	"　■■■■■";
			gotoxy(74,3);	cout <<	"■■■■■■";
			gotoxy(74,4);	cout <<	"■■　　　　";
			gotoxy(74,5);	cout <<	"■■　　　　";
			gotoxy(74,6);	cout <<	"■■■■■　";
			gotoxy(74,7);	cout <<	"　■■■■■";
			gotoxy(74,8); 	cout <<	"　　　　■■";
			gotoxy(74,9); 	cout <<	"　　　　■■";
			gotoxy(74,10); 	cout <<	"■■■■■■";
			gotoxy(74,11); 	cout <<	"■■■■■　";
			break;
	}
	setcolor(0, 0);
	//Clean_Cussor();
}

void cl_GameManger::OutPrintIntro()	// 인트로를 출력하는 함수 
{
	Clean_Cussor();
	system("mode con cols=91 lines=18");
	setcolor(15, 0);gotoxy(37,14);cout << "- Press AnyKey -";
	int COLOR[6] = {10, 11, 12, 13, 14, 15};
	gotoxy(4,13);	cout << "　　　　　　　　　　　　　　　　　　　　　　　　　　　　MADE BY GarryMilk";
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

void cl_GameManger::OutPrintMap()	// 맵을 맵을 출력하는 함수
{
	// x좌표 : 3 ~ 22	Y좌표 : 1 ~ 20 	블록 시작 좌표 :  x(8), y(1)
	// NEXT 좌표 : x 24 ~ 30	y 2 ~ 5
	// SAVE 좌표 : x 24 ~ 30	y 9 ~ 12
	system("mode con cols=61 lines=22");
	cout << "■。。。。。。。。。。■　NEXT　■　　　　　　　　　　　　　" << endl;
	cout << "■　　　　　　　　　　■■■■■■　　　　블록 돌리기　　　 " << endl;
	cout << "■　　　　　　　　　　■　　　　■　　　　　　　　　　　　　" << endl;
	cout << "■　　　　　　　　　　■　　　　■　　　　　　△　　　　　　" << endl;
	cout << "■　　　　　　　　　　■　　　　■　　　　　　　　　　　　　" << endl;
	cout << "■　　　　　　　　　　■　　　　■　왼쪽　◁　　　▷　오른쪽" << endl;
	cout << "■　　　　　　　　　　■■■■■■　　　　　　　　　　　　　" << endl;
	cout << "■　　　　　　　　　　■　SAVE　■　　　　　　▽　　　　　　" << endl;
	cout << "■　　　　　　　　　　■■■■■■　　　　　　　　　　　　　" << endl;
	cout << "■　　　　　　　　　　■　　　　■　　　　빨리 내리기　　　 " << endl;
	cout << "■　　　　　　　　　　■　　　　■　　　　　 　　　　　　　 " << endl;
	cout << "■　　　　　　　　　　■　　　　■　　　　 SPACE BAR　　" << endl;
	cout << "■　　　　　　　　　　■　　　　■　　　 한번에 내리기" << endl;
	cout << "■　　　　　　　　　　■■■■■■　　　　　　　　　　　" << endl;
	cout << "■　　　　　　　　　　■　　　　　　　S  블록 저장하기 　 " << endl;
	cout << "■　　　　　　　　　　■　LEVEL 　　　 "<< endl;
	cout << "■　　　　　　　　　　■　　" << iStage << "　　　 　D  블록 불러오기" << endl;
	cout << "■　　　　　　　　　　■　　　　　　　　　　" << endl;
	cout << "■　　　　　　　　　　■　　　　　　　P　게임 멈추기　" << endl;
	cout << "■　　　　　　　　　　■　SCORE　 　　 " << endl;
	cout << "■　　　　　　　　　　■　　　　　　　K　게임 종료하기　" << endl;
	cout << "■■■■■■■■■■■■　　　　　　　　　　";                               
}         

bool cl_GameManger::CheckingMap()	// 맵을 비교 및 재출력하는 함수                                   
{
	if(OutPrintScore() == false)
	{
		return true;
	}
	ReprintNextSave();	// 다음블록과 저장블록을 출력하는 함수
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
			if(cMap[i][j] != cTempMap[i][j] || PauseCheck == true)	// 기존에 저장된 맵이 바뀜맵과 다르면 재출력 
			{
				//cout <<"i:" << i <<"	" <<"j :" << j;
				RePrintMap(j, i);	// 배열의 값을 보내서 위치를 표시하는 방식임.. 
				cMap[i][j] = cTempMap[i][j];			// 원래맵으로 돌려놓는다. 
			}
		}
	}
	return false;
}

void cl_GameManger::RePrintMap(int Xpos, int Ypos)	// 맵을 다시 출력하는 함수
{
	// x좌표 : 3 ~ 22	Y좌표 : 1 ~ 20 	블록 시작 좌표 :  x(8), y(1)
	// NEXT 좌표 : x 24 ~ 30	y 2 ~ 5
	// SAVE 좌표 : x 24 ~ 30	y 9 ~ 12
	gotoxy(Xpos * 2 + 2, Ypos - 3);
	//cout << "y :" << Ypos;
	ColorBlockPrint(cTempMap[Ypos][Xpos]);
}

void cl_GameManger::ReprintNextSave()	// 다음블록과 저장블록을 출력하는 함수 
{
//	static bool First = false;
	int xPos, yPos;
	// NEXT 좌표 : x 24 ~ 30	y 2 ~ 5
	// SAVE 좌표 : x 24 ~ 30	y 9 ~ 12
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

void cl_GameManger::ChangeNextBlock()	// 다음블록을 정하는 함수
{
	srand((unsigned int)time(NULL));
	
	bBlockCheck = true;	// 다음블록이 호출되면 현재블록을 활성화한다 
	bBlockActive = false;	// 배정됫다는건 아직 맵에 블록이 소환이 되지않앗으니 세팅해준다. 
	
	if(bFirstStart == false)	// 처음 호출되면 다음블록을 초기화한다 
	{
		iNextBlock = rand() % 7 + 1;
		bFirstStart = true;
	}
	iTempNEXT = iNextBlock;	// 전블록에 초기화전 블록 입력 
	iThisBlock = iNextBlock;	// 현재블록에 초기화전 블록 입력 
	SetBlock(cThisBlock, iNextBlock, BT_0);
	eBlock_Turn = BT_0;
	
	int iDex1, iDex2, iTemp;
	for(int i = 0 ; i < 10; i++)
	{
		// iDex1,2 값에 45 이하의 랜덤값 부여
		iDex1 = rand() % 7;
		iDex2 = rand() % 7;
		
		// 서로 바꿔준다
		iTemp = iNumberBlock[iDex1];
		iNumberBlock[iDex1] = iNumberBlock[iDex2];
		iNumberBlock[iDex2] = iTemp;
	}
	iNextBlock = iNumberBlock[rand() % 7];	// 다음블록 초기화 
	SetBlock(cNEXT, iNextBlock, BT_0);
	return;
}

void cl_GameManger::SetBlock(char cBlock[5][5], int iBlock, Block_Turn iBlock_s)		// 블록 모양을 변수에 입력하는 함수 
{
	switch(iBlock)
	{
		case BS_SQUARE:
		//	iThisBlock = BS_SQUARE;
			INPUT_BLOCK(cBlock, Block_Square, iBlock_s);	// INPUT_BLOCK() 메크로 value.h 
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

void cl_GameManger::BlockRePosition()	// 현재블록 위치를 다시 나타내는 함수
{
	for(int i = 0; i < 24; i++)		// 블록 인식 맵은 블록이 내려올떄 기존맵에 있던 블록을 지운다. 
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
			if(cThisBlock[i][j] != BC_NONE) 	// 만약 빈칸이 아니면 대입 
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
			cout << "　";
			break;
		case '1':
			setcolor(11, 0);
			cout << "■";
			break;
		case '2':
			setcolor(12, 0);
			cout << "■";
			break;
		case '3':
			setcolor(9, 0);
			cout << "■";
			break;
		case '4':
			setcolor(2, 0);
			cout << "■";
			break;
		case '5':
			setcolor(13, 0);
			cout << "■";
			break;
		case '6':
			setcolor(14, 0);
			cout << "■";
			break;
		case '7':
			setcolor(10, 0);
			cout << "■";
			break;
		case '8':
			cout << "。";
			break;
	}
	setcolor(7, 0);
}

void cl_GameManger::RePrintStartLine(int Xpos)
{
	gotoxy(Xpos*2 + 2, 0);
	cout << "。";
	return;
}

bool cl_GameManger::OutPrintScore()	// 점수화면을 출력하는 함수
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

bool cl_GameManger::PrintBlock() 	// 블록을 그리는 함수 
{
	// x좌표 : 3 ~ 22	Y좌표 : 1 ~ 20 	블록 시작 좌표 :  x(8), y(1)
	// NEXT 좌표 : x 24 ~ 30	y 2 ~ 5
	// SAVE 좌표 : x 24 ~ 30	y 9 ~ 12
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
			if(cThisBlock[i][j] != BC_NONE) 	// 만약 빈칸이 아니면 대입 
			{
				if(!(cTempMap[iThisYpos + i][iThisXpos + j] == BC_NONE || cTempMap[iThisYpos + i][iThisXpos + j] == BC_MapCircle))	// 시작칸에 블록이 있으면 게임오버 
					return false;
				cTempMap[iThisYpos + i][iThisXpos + j] = cThisBlock[i][j];	
				cThisBlockMap[iThisYpos + i][iThisXpos + j] = cThisBlock[i][j];				
			}

		}
	}
	bBlockActive = true;
	return true;
}

 bool cl_GameManger::BlockDown()	// 블록이 내려가는 함수 
{
	static int iLate = 0;	// 블록이 내려오는 시간 
	if(iLate != iStageSpeed)
	{
		iLate++;
		return true;
	}
	else iLate = 0;	// 블록이 내려오는 시간 
	
	
	if(BlockCollisoinCheck())	// 블록이 충돌하면
	{
		for(int i = 0; i < 24; i++)		// 블록 인식 맵은 블록이 내려올떄 기존맵에 있던 블록을 지운다. 
		{
			for(int j = 0; j < 10; j++)
			{
				cEndMap[i][j] = cTempMap[i][j];
				cThisBlockMap[i][j] = BC_NONE;
			}
		}
		return false; 	
	}
	iThisYpos++;	// Y값을 증가시켜서 좌표를 한칸 내린다.
	
	for(int i = 0; i < 24; i++)		// 블록 인식 맵은 블록이 내려올떄 기존맵에 있던 블록을 지운다. 
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
			if(cThisBlock[i][j] != BC_NONE) 	// 만약 빈칸이 아니면 대입 
			{
				cTempMap[iThisYpos + i][iThisXpos + j] = cThisBlock[i][j];	
				cThisBlockMap[iThisYpos + i][iThisXpos + j] = cThisBlock[i][j];	
			}
		}
	}
	return true;
}

bool cl_GameManger::BlockCollisoinCheck()	// 블록 충돌 체크 블록이 충돌하면 true 반환 
{
	for(int i = 0; i < 4; i++) 
	{
		for(int j = 0; j < 4; j++)
		{
			if(!(cThisBlockMap[iThisYpos + i][iThisXpos + j] == BC_NONE || cThisBlockMap[iThisYpos + i][iThisXpos + j] == BC_MapCircle) && iThisYpos + i < 24)	
			{
				//cout << "i : " << i << " j : " << j;
				if(iThisYpos + i == 23 && iThisXpos + j < 10)	// 블록부분이 땅에닿으면 
				{
				//	cout << "bug" << iThisYpos + i ;
					return true; 
				}
				if(!(cEndMap[iThisYpos + i + 1][iThisXpos + j] == BC_NONE || cEndMap[iThisYpos + i + 1][iThisXpos + j] == BC_MapCircle) && iThisXpos + j < 10)	// 미리 쌓여있는 블록이 있으면 
				{
					//cout << iThisYpos + i + 1  << "  " << iThisXpos + j;
					return true;					
				}

			} 
		}
	}
	return false;
}

void cl_GameManger::KeyInput(unsigned char Key)	// 키를 입력받는 함수
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
			if(BlockDown() == false)	// 블록을 한칸 내리고 충돌하면
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

void cl_GameManger::BlockRotation()	// 블록 회전 
{
	Block_Turn eTurnTemp = eBlock_Turn;
	switch(eBlock_Turn)	// 방향전환 
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
				if(!(cEndMap[iThisYpos + i][iThisXpos + j] == BC_NONE || cEndMap[iThisYpos + i][iThisXpos + j] == BC_MapCircle))	// 만약 회전된 블록 이 들어갈 칸에
				{														// 다른블록이 있으면 회전취소 
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

void cl_GameManger::BlockSave()	// 블록을 세이브하는 키 함수
{
	if(Saving == true)return;	// 이미 저장된 블록이 있으면 리턴 
	// 세이브블록에 현재블록 대입 
	eBlock_Turn = BT_0;
	Block_RESET(cSaveBlock);
	
	iSaveBlock = iThisBlock;
	SetBlock(cSaveBlock, iThisBlock, BT_0);
	//BLOCK_SUB(cSaveBlock, cThisBlock);
	Saving = true;
	
	// cTempMap 에 cEndMap 값을 대입하면 맵재출력 함수에서 현재블록이 사라진다 
	MAP_SUB(cTempMap, cEndMap);
	MAP_RESET(cThisBlockMap);
	DownKey = true;	// 다운키를 활성화하면 Run함수에서 자동으로 블록이 맵에서 없어진것으로 판정한다. 
	return;
}

void cl_GameManger::BlockLoad()	// 블록을 불러오는 키 함수 
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
	MAP_SUB(cTempMap, cEndMap);	// 현재맵에있는 블록을 없엔다. 
	
	MAP_RESET(cThisBlockMap);
	
	PrintBlock();
	Saving = false;
}

void cl_GameManger::GamePause()	 // 게임을 정지시키는 함수
{
	setcolor(7, 0);
	gotoxy(7, 7);	cout << "■■■■■■■■■■■■■■■■■■■■■■■■";
	gotoxy(7, 8);	cout << "■                                            ■";
	gotoxy(7, 9);	cout << "■         G A M E          P A U S E         ■";
	gotoxy(7, 10);	cout << "■                                            ■";
	gotoxy(7, 11);	cout << "■              - Press AnyKey -              ■";
	gotoxy(7, 12);	cout << "■                                            ■";
	gotoxy(7, 13);	cout << "■■■■■■■■■■■■■■■■■■■■■■■■";
	getch();
	
	system("cls");
	PauseCheck = true;
	
	OutPrintMap();			// 맵재출력 
	CheckingMap();
	 
	
	PauseCheck = false;
}

void cl_GameManger::StageClear()	// 스테이지 클리어 
{
	if(iStage < 5)
	{
		setcolor(11, 0);
		gotoxy(7, 7);	cout << "■■■■■■■■■■■■■■■■■■■■■■■■";
		gotoxy(7, 8);	cout << "■                                            ■";
		gotoxy(7, 9);	cout << "■        S T A G E " << iStage << "         C L E A R       ■";
		gotoxy(7, 10);	cout << "■                                            ■";
		gotoxy(7, 11);	cout << "■              - Press AnyKey -              ■";
		gotoxy(7, 12);	cout << "■                                            ■";
		gotoxy(7, 13);	cout << "■■■■■■■■■■■■■■■■■■■■■■■■";
		getch();
	}
	else if(iStage == 5)
	{
		setcolor(11, 0);
		gotoxy(7, 7);	cout << "■■■■■■■■■■■■■■■■■■■■■■■■";
		gotoxy(7, 8);	cout << "■                                            ■";
		gotoxy(7, 9);	cout << "■      F I N A L  S T A G E  C L E A R       ■";
		gotoxy(7, 10);	cout << "■                                            ■";
		gotoxy(7, 11);	cout << "■              - Press AnyKey -              ■";
		gotoxy(7, 12);	cout << "■                                            ■";
		gotoxy(7, 13);	cout << "■■■■■■■■■■■■■■■■■■■■■■■■";
		getch();
	}
	
	if(iStage < 4)
	{
		setcolor(10, 0);
		gotoxy(7, 7);	cout << "■■■■■■■■■■■■■■■■■■■■■■■■";
		gotoxy(7, 8);	cout << "■                                            ■";
		gotoxy(7, 9);	cout << "■        S T A G E " << iStage + 1<< "         S R A R T       ■";
		gotoxy(7, 10);	cout << "■                                            ■";
		gotoxy(7, 11);	cout << "■              - Press AnyKey -              ■";
		gotoxy(7, 12);	cout << "■                                            ■";
		gotoxy(7, 13);	cout << "■■■■■■■■■■■■■■■■■■■■■■■■";
		getch();
	}
	else if(iStage == 4)
	{
		setcolor(10, 0);
		gotoxy(7, 7);	cout << "■■■■■■■■■■■■■■■■■■■■■■■■";
		gotoxy(7, 8);	cout << "■                                            ■";
		gotoxy(7, 9);	cout << "■      F I N A L  S T A G E  S T A R T       ■";
		gotoxy(7, 10);	cout << "■                                            ■";
		gotoxy(7, 11);	cout << "■              - Press AnyKey -              ■";
		gotoxy(7, 12);	cout << "■                                            ■";
		gotoxy(7, 13);	cout << "■■■■■■■■■■■■■■■■■■■■■■■■";
		getch();
	}
	setcolor(7, 0);	
}

void cl_GameManger::StageFail()	// 스테이지 패비
{
	setcolor(12, 0);
	gotoxy(7, 7);	cout << "■■■■■■■■■■■■■■■■■■■■■■■■";
	gotoxy(7, 8);	cout << "■                                            ■";
	gotoxy(7, 9);	cout << "■         G A M E           O V E R          ■";
	gotoxy(7, 10);	cout << "■                                            ■";
	gotoxy(7, 11);	cout << "■              - Press AnyKey -              ■";
	gotoxy(7, 12);	cout << "■                                            ■";
	gotoxy(7, 13);	cout << "■■■■■■■■■■■■■■■■■■■■■■■■";
	getch();
	setcolor(7, 0);
}

bool cl_GameManger::CheckingLine()	// 테트리스 라인을 체크하는 함수
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
					cout << "　　　 TETRIS!　　　";
				else
					cout << "　　　"<< Num << " COMBO!　　　";
				setcolor(7, 0);
				for(int t = 0; t < 10; t++)	// 라인 클리어 대면 해당 라인을 다 공백으로 만든다 
					cEndMap[i][t] = BC_NONE;
			}
		}
	}
	MAP_RESET(cEmpty);
	if(Num > 0) 	// 만약 라인이 하나이상 클리어 됫으면
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

void cl_GameManger::GetScore(int iNum)	// 스코어를 휙득하는 함수 
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

void cl_GameManger::StageDeficullty()	// 스테이지 난이도
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

bool cl_GameManger::CheckEnding()	// 게임 엔딩 함수
{
	if(iStage > 5)
	{
		system("mode con cols=141 lines=19") ;
		// YOU WIN
		gotoxy(4,2);	cout <<	"■■　　　　■■　　　■■　　　■■　　　　　■■　　　■■　　　　　■■　　　　　■■　■■■■■■　■■　　　　　　　■■　■■";
		gotoxy(4,3);	cout <<	"■■　　　　■■　　■■■■　　■■　　　　　■■　　　■■　　　　■■■■　　　　■■　■■■■■■　■■　　　　　　■■■　■■";
		gotoxy(4,4);	cout <<	"■■　　　　■■　■■　　■■　■■　　　　　■■　　　■■　　　　■■■■　　　　■■　　　■■　　　■■　　　　　■■■■　■■";
		gotoxy(4,5);	cout <<	"　■■　　■■　　■■　　■■　■■　　　　　■■　　　　■■　　■■　　■■　　■■　　　　■■　　　■■　　　　■■　■■　■■";
		gotoxy(4,6);	cout << "　　■■■■　　　■■　　■■　■■　　　　　■■　　　　■■　　■■　　■■　　■■　　　　■■　　　■■　　　■■　　■■　■■"; 
		gotoxy(4,7);	cout << "　　　■■　　　　■■　　■■　■■　　　　　■■　　　　■■　　■■　　■■　　■■　　　　■■　　　■■　　■■　　　■■　■■"; 
		gotoxy(4,8); 	cout << "　　　■■　　　　■■　　■■　■■　　　　　■■　　　　　■■■■　　　　■■■■　　　　　■■　　　■■　■■　　　　■■　■■";
		gotoxy(4,9); 	cout << "　　　■■　　　　■■　　■■　　■■　　　■■　　　　　　■■■■　　　　■■■■　　　　　■■　　　■■■■　　　　　■■　　　";
		gotoxy(4,10);	cout << "　　　■■　　　　　■■■■　　　　■■■■■　　　　　　　　■■　　　　　　■■　　　　■■■■■■　■■■　　　　　　■■　■■";
		gotoxy(4,11);	cout << "　　　■■　　　　　　■■　　　　　　■■■　　　　　　　　　■■　　　　　　■■　　　　■■■■■■　■■　　　　　　　■■　■■";
		gotoxy(4,13);	cout << "　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　MADE BY GarryMilk　　　　　　　　　";
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

bool cl_GameManger::RUN()	// 게임을 구동하는 함수 
{
	unsigned char Key = 0;
	StageDeficullty();
	Clean_Cussor();
	system("title TETRIS");
	//OutPrintIntro();
	OutPrintMap();
	ChangeNextBlock();	// 다음블록을 초기화한다, 처음선언시 처음블록 도 초기화됨 
	while(true)
	{
		if(bBlockCheck == false)	ChangeNextBlock();	// 현재 블록이 비활성화되면 다음블록을 입력한다.
		if(bBlockActive == false)	// 맵에 아직 현재블록이 출력되지 않앗으면 출력해준다. 
		{
			if(PrintBlock() == false) // 시작칸에 블록이 있으면 패배 
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
		if(CheckingMap() == true)	// 참값을 보내면 점수로인한 스테이지 클리어 
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
		else if(BlockDown() == false)	// 블록을 한칸 내리고 충돌하면 
		{
			bBlockCheck = false; 
			bBlockActive = false;
		}
		CheckingLine();
		Sleep(30);
	}
}
