#pragma once

#include "value.h"

void gotoxy(int x,int y);
void Clean_Cussor();	// Ŀ���� ����� �Լ� 
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
		enum Block_Turn { BT_0 = 0, BT_90, BT_180, BT_270 };	// ��� ȸ����
		
	private:
		//void ReadBlock();	// ��� �������� ���� �����ϴ� �Լ� 
	
	private:	// �ʰ� ���õ� ������ 
		// �� 
		char cMap[MAP_Y][MAP_X];		// �� ���¸� �����ϴ� ���� 				cTempMap �� ���ʿ� : cTempMap �� ���Ե� 
		char cTempMap[MAP_Y][MAP_X];	// ����Ǵ� �ʻ��¸� �����ϴ� ���� 		������ ��ġ�� ���̱������� EndMap ��ϵ����� 
		char cEndMap[MAP_Y][MAP_X];	// ����� ���� ���¸� �����ϴ� ���� 	cEndMap ���� ������ ��ġ�� �Ⱥ��� 
		char cEmpty[MAP_Y][MAP_X];	// ���ĭ�� ����ִ� �� 
		char cThisBlockMap[MAP_Y][MAP_X];	// �������� ��ġ�� �Է��ϴ� ���� 
		
		// ������� 
		char cNEXT[5][5];		// ������� ����� �����ϴ� ���� 
		int iNumberBlock[7];
		int iTempNEXT;	// ������� ���� �ӽ÷� �����ϴ� ���� 
		int iNextBlock;			// ��������� �����ϴ� ���� 
		
		// ������ 
		char cThisBlock[5][5];	// ������ ����� �����ϴ� ���� 
		int iThisBlock;			// �������� �����ϴ� ��� 
		Block_Turn eBlock_Turn;	// ����� ������ �����ϴ� ���� 
		
		// ������
		bool Saving; // ����� �����޴��� Ȯ���ϴ� �Լ� 
		char cSaveBlock[5][5];	// ������ ����� �����ϴ� ����
		char iTempSave;
		int iSaveBlock;	// ���̺��� ������ �����ϴ� ����
		
		// �������� ���̵�
		int iStageSpeed; 
		
	private: 
	
		// ȸ����� üũ 
		char cRotationBlock[5][5];
	private:
		int iStage;	// ����������� �����ϴ� ���� 
		int iScore;	// ���������� �����ϴ� ���� 
		int iScoreTemp;
		bool bBlockCheck;	// �ʵ��� ����� Ȱ��ȭ�̴��� Ȯ���ϴ� ����
		bool bBlockActive;	// ����� ��ȯ�̴��� üũ�ϴ� ���� 
		
		int iThisXpos;	// �������� ��ǥ�� �����ϴ� ����	-�� +�� 
		int iThisYpos; 	//									+�Ʒ� 
		int iTempXpos;
		int iTempYpos;
		
	private:
		void SetPosFirst(int Ypos = 0);	// �����ǥ�� ������������ �ű�� �Լ� 
	
	private:
		void ResetMap();		// ���� �ʱ�ȭ�ϴ� �Լ�  
		
	public:
		void SetIntroColor(int Word, int Color);	// ��Ʈ�� ���ڸ� ����ϴ� �Լ�
		void OutPrintIntro();	// ��Ʈ�θ� ����ϴ� �Լ� 
	
	private:
		void OutPrintMap();	// ���� ���� ����ϴ� �Լ�
		bool CheckingMap();	// ���� �� �� ������ϴ� �Լ� 
		void RePrintMap(int Xpos, int Ypos);	// ���� �ٽ� ����ϴ� �Լ� 
		void ReprintNextSave();	// ������ϰ� �������� ����ϴ� �Լ� 
		void ColorBlockPrint(char Color);	// ����� ������ �־� �׷��ִ� �Լ� 
		void RePrintStartLine(int Xpos);	// ó�����۶����� �ٽñ׸��� �Լ� 
		bool OutPrintScore();	// ����ȭ���� ����ϴ� �Լ� 
	
	private:
		bool bFirstStart;
		bool First;
	
	private:
		void ChangeNextBlock();	// ����� ����������� �ٲٰ� ���ο� ��������� �����ϴ� �Լ� 
		void SetBlock(char cBlock[5][5], int iBlock, Block_Turn iBlock_s);		// ��� ����� ������ �Է��ϴ� �Լ� 
		void BlockRePosition();	// ������ ��ġ�� �ٽ� ��Ÿ���� �Լ�
		
	private:
		bool PrintBlock();	// ����� �׸��� �Լ�
		bool BlockDown();	// ����� �������� �Լ�
		bool BlockCollisoinCheck();	// ��� �浹 üũ  
		
	private:
		void KeyInput(unsigned char Key);	// Ű�� �Է¹޴� �Լ� 
		void BlockRotation();	// ��� ȸ�� 
		void BlockLeft();
		void BlockRight();
		void BlockSave();	// ����� ���̺��ϴ� Ű �Լ� 
		void BlockLoad();	// ����� �ҷ����� Ű �Լ� �� 
		void GamePause();	 // ������ ������Ű�� �Լ�
		void StageClear();	// �������� Ŭ���� 
		void StageFail();	// �������� �к� 

	private:
		bool DownKey;	// True �̸� Run �Լ����� ����� �������ɷ� �Ǵ��Ѵ�. 
		bool PauseCheck;	// �������¸� Ȯ���ϴ� ���� 
				
	private:
		bool CheckingLine();	// ��Ʈ���� ������ üũ�ϴ� �Լ� 
		void RePrintEndMap(const int Xpos, const int Ypos);
		void GetScore(int iNum);	// ���ھ �׵��ϴ� �Լ� 
		void StageDeficullty();	// �������� ���̵�
		
	public:
		void RESET();
		bool CheckEnding();	// ���� ���� �Լ� 
	
	public:
		bool RUN();	// ������ �����ϴ� �Լ�  
		
	private:	// �����
		void OutPrintBlock();
};
