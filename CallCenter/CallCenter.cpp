// CallCenter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include "ConnectionServer.h"
#include "SystemKernel.h"


CSystemKernel *CSK;

int main(int argc, char* argv[])
{
	FLOG << time << "[**] START service" << endl;

	CSK = new CSystemKernel(true);
	
	Sleep(500);
	CSK->Resume();

	for (;/*!kbhit()*/;) Sleep(10000);

	FLOG << time << "[**] END service" << endl;

	return 0;
}
