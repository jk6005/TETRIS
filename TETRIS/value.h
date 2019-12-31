#pragma once

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <ctime> 
#include <cstdlib>

using namespace std;

#define MAP_Y	24
#define MAP_X	11

#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),  (mode)))==NULL

// 블록[5][5] 변수에 해당 블록 값을 넣어주는 매크로
// (블록[5][5], 블록모양, 회전타입) 
#define	INPUT_BLOCK(BlockType, Block, Block_s)	for(int i = 0; i < 4; i++)\
													for(int j = 0; j < 4; j++)\
														BlockType[i][j] = Block[Block_s][i][j]; 
					
					/*
//	메모장에 저장된 블록 모양을 불러오는 매크로 
#define	READBLOCK(Block)	for(int j = 0; j < 4; j++)\
								{\
									for(int k = 0; k < 4; k++)\
									{\
										for(int p = 0; p < 5; p++)\
										{\
											fread(&Block, sizeof(char), 1, pFile);\
											if(Block == '\n')\
												Block = EOF;\
										}\
									}\
								}*/
								
// Block_I[5][5] 블록에  Block_s[5][5] 블록을 대입하는 매크로 
#define BLOCK_SUB(Block_I, Block_s)	for(int i = 0; i < 5; i++)\
										for(int j = 0; j < 5; j++)\
											Block_I[i][j] = Block_s[i][j];
											
// Block_I 맵에 Block_S 맵을 대입하는 매크로 
#define MAP_SUB(Block_I, Block_s)	for(int i = 0; i < 24; i++)\
										for(int j = 0; j < 10; j++)\
											Block_I[i][j] = Block_s[i][j];
			
// 	맵을 초기화하는 매크로								
#define MAP_RESET(Block)	for(int i = 0; i < 24; i++)\
								for(int j = 0; j < 10; j++){\
									if(i == 3) Block[i][j] = '8';\
										Block[i][j] = '0';}
									
// 블록을 초기화하는 매크로
#define Block_RESET(Block) 	for(int i = 0; i < 4; i++)\
								for(int j = 0; j < 4; j++)\
									Block[i][j] = '0';
