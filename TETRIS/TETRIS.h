#pragma once

#include "value.h"

void gotoxy(int x,int y);
void Clean_Cussor();	// 커서를 지우는 함수 
void setcolor(int color, int bgcolor);

const char Block_Square[4][4][5] =
{ {{'1','1','0','0'},{'1','1','0','0'},{'0','0','0','0'},{'0','0','0','0'}}, {{'1','1','0','0'},{'1','1','0','0'},{'0','0','0','0'},{'0','0','0','0'}}, 
{{'1','1','0','0'},{'1','1','0','0'},{'0','0','0','0'},{'0','0','0','0'}}, {{'1','1','0','0'},{'1','1','0','0'},{'0','0','0','0'},{'0','0','0','0'}} };
const char Block_Stick[4][4][5] =
{ {{'2','0','0','0'},{'2','0','0','0'},{'2','0','0','0'},{'2','0','0','0'}}, {{'2','2','2','2'},{'0','0','0','0'},{'0','0','0','0'},{'0','0','0','0'}}, 
{{'2','0','0','0'},{'2','0','0','0'},{'2','0','0','0'},{'2','0','0','0'}}, {{'2','2','2','2'},{'0','0','0','0'},{'0','0','0','0'},{'0','0','0','0'}} };      
const char Block_Zigzag_L[4][4][5] =
{ {{'0','3','3','0'},{'3','3','0','0'},{'0','0','0','0'},{'0','0','0','0'}}, {{'3','0','0','0'},{'3','3','0','0'},{'0','3','0','0'},{'0','0','0','0'}}, 
{{'0','3','3','0'},{'3','3','0','0'},{'0','0','0','0'},{'0','0','0','0'}}, {{'3','0','0','0'},{'3','3','0','0'},{'0','3','0','0'},{'0','0','0','0'}} };      
const char Block_Zigzag_R[4][4][5] =
{ {{'4','4','0','0'},{'0','4','4','0'},{'0','0','0','0'},{'0','0','0','0'}}, {{'0','4','0','0'},{'4','4','0','0'},{'4','0','0','0'},{'0','0','0','0'}}, 
{{'4','4','0','0'},{'0','4','4','0'},{'0','0','0','0'},{'0','0','0','0'}}, {{'0','4','0','0'},{'4','4','0','0'},{'4','0','0','0'},{'0','0','0','0'}} };      
const char Block_Point[4][4][5] =
{ {{'0','5','0','0'},{'5','5','5','0'},{'0','0','0','0'},{'0','0','0','0'}}, {{'0','5','0','0'},{'5','5','0','0'},{'0','5','0','0'},{'0','0','0','0'}}, 
{{'5','5','5','0'},{'0','5','0','0'},{'0','0','0','0'},{'0','0','0','0'}}, {{'5','0','0','0'},{'5','5','0','0'},{'5','0','0','0'},{'0','0','0','0'}} };      
const char Block_Lblock_L[4][4][5] =
{ {{'0','0','6','0'},{'6','6','6','0'},{'0','0','0','0'},{'0','0','0','0'}}, {{'6','6','0','0'},{'0','6','0','0'},{'0','6','0','0'},{'0','0','0','0'}}, 
{{'6','6','6','0'},{'6','0','0','0'},{'0','0','0','0'},{'0','0','0','0'}}, {{'6','0','0','0'},{'6','0','0','0'},{'6','6','0','0'},{'0','0','0','0'}} };   
const char Block_Lblock_R[4][4][5] =
{ {{'7','0','0','0'},{'7','7','7','0'},{'0','0','0','0'},{'0','0','0','0'}}, {{'0','7','0','0'},{'0','7','0','0'},{'7','7','0','0'},{'0','0','0','0'}}, 
{{'7','7','7','0'},{'0','0','7','0'},{'0','0','0','0'},{'0','0','0','0'}}, {{'7','7','0','0'},{'7','0','0','0'},{'7','0','0','0'},{'0','0','0','0'}} };      	      
            
enum Block_Shape
{          
	BS_NONE = 0,
	BS_SQUARE,
	BS_STICK,
	BS_ZIGZAG_L,
	BS_ZIGZAG_R,
	BS_POINT,
	BS_LBLOCK_L,
	BS_LBLOCK_R
};

enum Block_Color
{
	BC_NONE = '0',
	BC_SQUARE = '1',
	BC_STICK = '2',
	BC_ZIGZAG_L = '3',
	BC_ZIGZAG_R = '4',
	BC_POINT = '5',
	BC_LBLOCK_L = '6',
	BC_LBLOCK_R = '7',
	BC_MapCircle = '8'
};

class cl_GameManger
{
	public:
		cl_GameManger();
		~cl_GameManger()
		{
			
		}
	private:
		enum WordColor { WS_T1 = 0, WS_E, WS_T2, WS_R, WS_I, WS_S};
		enum Block_Input { BI_THIS, BI_NEXT, BI_SAVE };
		enum Block_Turn { BT_0 = 0, BT_90, BT_180, BT_270 };	// 블록 회전율
		
	private:
		//void ReadBlock();	// 블록 변수들의 값을 대입하는 함수 
	
	private:	// 맵과 관련된 변수들 
		// 맵 
		char cMap[MAP_Y][MAP_X];		// 맵 상태를 저장하는 변수 				cTempMap 과 비교필요 : cTempMap 이 대입됨 
		char cTempMap[MAP_Y][MAP_X];	// 변경되는 맵상태를 저장하는 변수 		현재블록 위치가 보이긴하지만 EndMap 블록도보임 
		char cEndMap[MAP_Y][MAP_X];	// 블록이 쌓인 상태를 저장하는 변수 	cEndMap 에는 현재블록 위치가 안보임 
		char cEmpty[MAP_Y][MAP_X];	// 모든칸이 비어있는 맵 
		char cThisBlockMap[MAP_Y][MAP_X];	// 현재블록의 위치만 입력하는 변수 
		
		// 다음블록 
		char cNEXT[5][5];		// 다음블록 출력을 저장하는 변수 
		int iNumberBlock[7];
		int iTempNEXT;	// 다음블록 값을 임시로 저장하는 변수 
		int iNextBlock;			// 다음블록을 저장하는 변수 
		
		// 현재블록 
		char cThisBlock[5][5];	// 현재블록 모양을 저장하는 변수 
		int iThisBlock;			// 현재블록을 저장하는 블록 
		Block_Turn eBlock_Turn;	// 블록의 각도를 저장하는 변수 
		
		// 저장블록
		bool Saving; // 블록을 저장햇는지 확인하는 함수 
		char cSaveBlock[5][5];	// 저장블록 모양을 저장하는 변수
		char iTempSave;
		int iSaveBlock;	// 세이브블록 종류를 저장하는 변수
		
		// 스테이지 난이도
		int iStageSpeed; 
		
	private: 
	
		// 회전블록 체크 
		char cRotationBlock[5][5];
	private:
		int iStage;	// 몇스테이지인지 저장하는 변수 
		int iScore;	// 현재점수를 저장하는 변수 
		int iScoreTemp;
		bool bBlockCheck;	// 필드의 블록이 활성화됫는지 확인하는 변수
		bool bBlockActive;	// 블록이 소환됫는지 체크하는 변수 
		
		int iThisXpos;	// 현재블록의 좌표를 저장하는 변수	-좌 +우 
		int iThisYpos; 	//									+아래 
		int iTempXpos;
		int iTempYpos;
		
	private:
		void SetPosFirst(int Ypos = 0);	// 블록좌표를 시작지점으로 옮기는 함수 
	
	private:
		void ResetMap();		// 맵을 초기화하는 함수  
		
	public:
		void SetIntroColor(int Word, int Color);	// 인트로 글자를 출력하는 함수
		void OutPrintIntro();	// 인트로를 출력하는 함수 
	
	private:
		void OutPrintMap();	// 맵을 맵을 출력하는 함수
		bool CheckingMap();	// 맵을 비교 및 재출력하는 함수 
		void RePrintMap(int Xpos, int Ypos);	// 맵을 다시 출력하는 함수 
		void ReprintNextSave();	// 다음블록과 저장블록을 출력하는 함수 
		void ColorBlockPrint(char Color);	// 블록을 색깔을 넣어 그려주는 함수 
		void RePrintStartLine(int Xpos);	// 처음시작라인을 다시그리는 함수 
		bool OutPrintScore();	// 점수화면을 출력하는 함수 
	
	private:
		bool bFirstStart;
		bool First;
	
	private:
		void ChangeNextBlock();	// 블록을 다음블록으로 바꾸고 새로운 다음블록을 배정하는 함수 
		void SetBlock(char cBlock[5][5], int iBlock, Block_Turn iBlock_s);		// 블록 모양을 변수에 입력하는 함수 
		void BlockRePosition();	// 현재블록 위치를 다시 나타내는 함수
		
	private:
		bool PrintBlock();	// 블록을 그리는 함수
		bool BlockDown();	// 블록이 내려가는 함수
		bool BlockCollisoinCheck();	// 블록 충돌 체크  
		
	private:
		void KeyInput(unsigned char Key);	// 키를 입력받는 함수 
		void BlockRotation();	// 블록 회전 
		void BlockLeft();
		void BlockRight();
		void BlockSave();	// 블록을 세이브하는 키 함수 
		void BlockLoad();	// 블록을 불러오는 키 함수 도 
		void GamePause();	 // 게임을 정지시키는 함수
		void StageClear();	// 스테이지 클리어 
		void StageFail();	// 스테이지 패비 

	private:
		bool DownKey;	// True 이면 Run 함수에서 블록이 없어진걸로 판단한다. 
		bool PauseCheck;	// 정지상태를 확인하는 변수 
				
	private:
		bool CheckingLine();	// 테트리스 라인을 체크하는 함수 
		void RePrintEndMap(const int Xpos, const int Ypos);
		void GetScore(int iNum);	// 스코어를 휙득하는 함수 
		void StageDeficullty();	// 스테이지 난이도
		
	public:
		void RESET();
		bool CheckEnding();	// 게임 엔딩 함수 
	
	public:
		bool RUN();	// 게임을 구동하는 함수  
		
	private:	// 디버그
		void OutPrintBlock();
};
