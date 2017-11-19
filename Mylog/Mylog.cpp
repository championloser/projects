/**********************************************************
  > Filename     : Mylog.cpp
  > Author       : Jeysin<jeysin@qq.com>
  > Create time  : 2017-10-20 00:18:00
  > Last modified: 2017-10-22 16:06:50
 **********************************************************/
#include"Mylog.h"
#include<iostream>

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
	OstreamAppender *osAppender=new OstreamAppender("osAppender",&std::cout);
#if ISROLLINGFILE
	RollingFileAppender *fAppender=new RollingFileAppender("fAppender", filename, 
								ROLLINGFILESIZE, ROLLINGFILENUM);
#else
	FileAppender *fAppender=new FileAppender("fAppender",filename);
#endif
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
