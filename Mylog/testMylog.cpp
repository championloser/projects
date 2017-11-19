/**********************************************************
  > Filename     : testMylog.cpp
  > Author       : Jeysin<jeysin@qq.com>
  > Create time  : 2017-10-22 16:07:10
  > Last modified: 2017-10-22 16:07:10
 **********************************************************/
#include"Mylog.h"
#include<iostream>
using namespace std;
int main()
{
	for(int i=0; i<10000; i++)
	{
	LogEmerg("This is an emerg message");
	LogFatal("This is a Fatal message");
	LogAlert("This is a Alert message");
	LogCrit("This is a Crit message");
	LogError("This is an error message");
	LogWarn("This is a warn message");
	LogNotice("This is a notice message");
	LogInfo("This is a info message");
	LogDebug("This is a debug message");
	}
	return 0;
}
