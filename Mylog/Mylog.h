/**********************************************************
  > Filename     : Mylog.h
  > Author       : Jeysin<jeysin@qq.com>
  > Create time  : 2017-10-22 16:07:00
  > Last modified: 2017-10-22 16:07:00
 **********************************************************/
#include<string.h>
#include<stdio.h>
#include<log4cpp/OstreamAppender.hh>
#include<log4cpp/FileAppender.hh>
#include<log4cpp/RollingFileAppender.hh>
#include<log4cpp/Category.hh>
#include<log4cpp/PatternLayout.hh>
#include<log4cpp/Priority.hh>
using namespace log4cpp;

#define FILENAME "../mylog.log"		//日志文件位置
#define PRIORITY Priority::DEBUG 	//日志级别
#define ISROLLINGFILE 1			//是否设置回滚文件，1设置，0不设置
#define ROLLINGFILESIZE 1024*1024	//设置回滚文件大小
#define ROLLINGFILENUM 5		//设置保留的回滚文件个数

#define LogEmerg(msg) Mylog::getInstance()->emerg(msg,__func__,__LINE__);
#define LogFatal(msg) Mylog::getInstance()->fatal(msg,__func__,__LINE__);
#define LogAlert(msg) Mylog::getInstance()->alert(msg,__func__,__LINE__);
#define LogCrit(msg) Mylog::getInstance()->crit(msg,__func__,__LINE__);
#define LogError(msg) Mylog::getInstance()->error(msg,__func__,__LINE__);
#define LogWarn(msg) Mylog::getInstance()->warn(msg,__func__,__LINE__);
#define LogNotice(msg) Mylog::getInstance()->notice(msg,__func__,__LINE__);
#define LogInfo(msg) Mylog::getInstance()->info(msg,__func__,__LINE__);
#define LogDebug(msg) Mylog::getInstance()->debug(msg,__func__,__LINE__);

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
