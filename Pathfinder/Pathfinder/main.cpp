// main.cpp : Defines the entry point for the console application.

#include <stdio.h>
#include <stdlib.h>
#include "CPathFinder.h"


int main()
{
	CPathFinder* pPathFinder = new CPathFinder();

	unsigned char pMap[] = { 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1 };
	int pOutBuffer[10];
	int Result = pPathFinder->FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 10);

	printf("Number of steps taken is %d \n", Result);

	for (int i : pOutBuffer)
	{
		printf("%d ", i);
	}

	system("PAUSE");

	delete pPathFinder;

    return 0;
}



/*

	//This function is used to call the pathfinder for the Paradoxpath assignment.
int FindPath(int StartX, int StartY, int TargetX, int TargetY, unsigned char const* pMap, int Width, int Height, int* pOutBuffer, int BufferSize)
{
	CPathFinder* pPathFinder = new CPathFinder();

	int Result = pPathFinder->FindPath( StartX,  StartY,  TargetX,  TargetY, pMap,  Width,  Height, pOutBuffer,  BufferSize);

	printf("Number of steps taken is %d \n", Result);

	for (int i : pOutBuffer)
	{
	printf("%d ", i);
	}

	system("PAUSE");

	delete pPathFinder;

	return 0;
}*/
