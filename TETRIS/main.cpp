#include "value.h"
#include "TETRIS.h"

int main()
{
	cl_GameManger GM;
	NEXT:
	if(GM.RUN() == true)
	{
		system("cls");
		if(GM.CheckEnding() == false)
			return 1;
		GM.RESET();
		goto NEXT;
	}
	else
		return 0;
	
	return 0;
}
