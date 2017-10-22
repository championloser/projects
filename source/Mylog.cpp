/**********************************************************
  > Filename     : Mylog.cpp
  > Author       : Jeysin<jeysin@qq.com>
  > Create time  : 2017-10-20 00:18:00
  > Last modified: 2017-10-21 14:32:17
 **********************************************************/
#include<iostream>
#include<log4cpp/OstreamAppender.hh>
#include<log4cpp/FileAppender.hh>
#include<log4cpp/Category.hh>
#include<log4cpp/PatternLayout.hh>
#include<log4cpp/Priority.hh>
#include<string.h>
#include<stdio.h>
#define FILENAME "mylog.log"
#define PRIORITY Priority::DEBUG
#define LogEmerg(msg) Mylog::getInstance()->emerg(msg,__func__,__LINE__);
#define LogFatal(msg) Mylog::getInstance()->fatal(msg,__func__,__LINE__);
#define LogAlert(msg) Mylog::getInstance()->alert(msg,__func__,__LINE__);
#define LogCrit(msg) Mylog::getInstance()->crit(msg,__func__,__LINE__);
#define LogError(msg) Mylog::getInstance()->error(msg,__func__,__LINE__);
#define LogWarn(msg) Mylog::getInstance()->warn(msg,__func__,__LINE__);
#define LogNotice(msg) Mylog::getInstance()->notice(msg,__func__,__LINE__);
#define LogInfo(msg) Mylog::getInstance()->info(msg,__func__,__LINE__);
#define LogDebug(msg) Mylog::getInstance()->debug(msg,__func__,__LINE__);
using namespace std;
using namespace log4cpp;
class Mylog
{
public:
	static Mylog *getInstance(const char *filename=FILENAME);
	void emerg(const char *msg,const char *funcname=NULL,int linenum=0);
	void fatal(const char *msg,const char *funcname=NULL,int linenum=0);
	void alert(const char *msg,const char *funcname=NULL,int linenum=0);
	void crit(const char *msg,const char *funcname=NULL,int linenum=0);
	void error(const char *msg,const char *funcname=NULL,int linenum=0);
	void warn(const char *msg,const char *funcname=NULL,int linenum=0);
	void notice(const char *msg,const char *funcname=NULL,int linenum=0);
	void info(const char *msg,const char *funcname=NULL,int linenum=0);
	void debug(const char *msg,const char *funcname,int linenum);
	void printInfo(int num,const char *msg,const char *funcname=NULL,int linenum=0);
private:
	Mylog(const char *filename);
	static Mylog *_pMylog;
	Category &_root;
	class Recycle
	{
	public:
		~Recycle()
		{
			delete _pMylog;
			_pMylog=NULL;
			Category::shutdown();
		}
	};
	static Recycle rec;
};
Mylog * Mylog::_pMylog=NULL;
Mylog::Recycle Mylog::rec;
Mylog * Mylog::getInstance(const char *filename)
{
	if(NULL==_pMylog)_pMylog=new Mylog(filename);
	return _pMylog;
}
Mylog::Mylog(const char *filename)
: _root(Category::getRoot())
{
	OstreamAppender *osAppender=new OstreamAppender("osAppender",&cout);
	FileAppender *fAppender=new FileAppender("fAppender",filename);
	PatternLayout *pLayout1=new PatternLayout();
	pLayout1->setConversionPattern("%d: [%p]: %m%n");
	osAppender->setLayout(pLayout1);
	PatternLayout *pLayout2=new PatternLayout();
	pLayout2->setConversionPattern("%d: [%p]: %m%n");
	fAppender->setLayout(pLayout2);
	_root.addAppender(osAppender);
	_root.addAppender(fAppender);
	_root.setPriority(PRIORITY);
}
void Mylog::emerg(const char *msg,const char *funcname,int linenum)
{
	printInfo(1,msg,funcname,linenum);
}
void Mylog::fatal(const char *msg,const char *funcname,int linenum)
{
	printInfo(2,msg,funcname,linenum);
}
void Mylog::alert(const char *msg,const char *funcname,int linenum)
{
	printInfo(3,msg,funcname,linenum);
}
void Mylog::crit(const char *msg,const char *funcname,int linenum)
{
	printInfo(4,msg,funcname,linenum);
}
void Mylog::error(const char *msg,const char *funcname,int linenum)
{
	printInfo(5,msg,funcname,linenum);
}
void Mylog::warn(const char *msg,const char *funcname,int linenum)
{
	printInfo(6,msg,funcname,linenum);
}
void Mylog::notice(const char *msg,const char *funcname,int linenum)
{
	printInfo(7,msg,funcname,linenum);
}
void Mylog::info(const char *msg,const char *funcname,int linenum)
{
	printInfo(8,msg,funcname,linenum);
}
void Mylog::debug(const char *msg,const char *funcname,int linenum)
{
	printInfo(9,msg,funcname,linenum);
}
void Mylog::printInfo(int num,const char *msg,const char *funcname,int linenum)
{
	char *buf=new char[strlen(msg)+50]();
	if(NULL==funcname)
	{
		sprintf(buf,"%s",msg);
	}
	if(NULL!=funcname && 0==linenum)
	{
		sprintf(buf,"%s:%s: %s",__FILE__,funcname,msg);
	}
	if(NULL!=funcname && 0!=linenum)
	{
		sprintf(buf,"%s:%s:%d: %s",__FILE__,funcname,linenum,msg);
	}
	switch(num)
	{
		case 1:_root.emerg(buf);break;
		case 2:_root.fatal(buf);break;
		case 3:_root.alert(buf);break;
		case 4:_root.crit(buf);break;
		case 5:_root.error(buf);break;
		case 6:_root.warn(buf);break;
		case 7:_root.notice(buf);break;
		case 8:_root.info(buf);break;
		case 9:_root.debug(buf);break;
		default:break;
	}
	delete [] buf;
}
int main()
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
	return 0;
}
