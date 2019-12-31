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

// ���[5][5] ������ �ش� ��� ���� �־��ִ� ��ũ��
// (���[5][5], ��ϸ��, ȸ��Ÿ��) 
#define	INPUT_BLOCK(BlockType, Block, Block_s)	for(int i = 0; i < 4; i++)\
													for(int j = 0; j < 4; j++)\
														BlockType[i][j] = Block[Block_s][i][j]; 
					
					/*
//	�޸��忡 ����� ��� ����� �ҷ����� ��ũ�� 
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
								
// Block_I[5][5] ��Ͽ�  Block_s[5][5] ����� �����ϴ� ��ũ�� 
#define BLOCK_SUB(Block_I, Block_s)	for(int i = 0; i < 5; i++)\
										for(int j = 0; j < 5; j++)\
											Block_I[i][j] = Block_s[i][j];
											
// Block_I �ʿ� Block_S ���� �����ϴ� ��ũ�� 
#define MAP_SUB(Block_I, Block_s)	for(int i = 0; i < 24; i++)\
										for(int j = 0; j < 10; j++)\
											Block_I[i][j] = Block_s[i][j];
			
// 	���� �ʱ�ȭ�ϴ� ��ũ��								
#define MAP_RESET(Block)	for(int i = 0; i < 24; i++)\
								for(int j = 0; j < 10; j++){\
									if(i == 3) Block[i][j] = '8';\
										Block[i][j] = '0';}
									
// ����� �ʱ�ȭ�ϴ� ��ũ��
#define Block_RESET(Block) 	for(int i = 0; i < 4; i++)\
								for(int j = 0; j < 4; j++)\
									Block[i][j] = '0';
