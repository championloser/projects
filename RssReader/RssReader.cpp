#include"tinyxml2.h"
#include<sys/types.h>
#include<dirent.h>
#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<fstream>
using namespace tinyxml2;
using std::cout;
using std::endl;
using std::string;
using std::vector;
struct RssItem
{
	string title;
	string link;
	string description;
	string content;
};
class RssReader
{
public:
	void findParseDumpRss(const char *);
	void parseRss(const char *);
	void dump(const char *);
private:
	vector<RssItem> _rss;
};
void RssReader::findParseDumpRss(const char *path)
{
	std::regex reg("[A-Za-z0-9]+\\.xml");
	DIR *dir=opendir(path);
	struct dirent *p;
	while((p=readdir(dir))!=NULL)
	{
		if(regex_match(p->d_name, reg))
		{
			cout<<"parsing '"<<p->d_name<<"'..."<<endl;
			parseRss(p->d_name);
			cout<<"dumpping '"<<p->d_name<<"'..."<<endl;
			dump("pagelib.dat");
		}
	}
}
void RssReader::parseRss(const char * filename)
{
	std::regex reg("<.+?>");
	XMLDocument doc;	
	doc.LoadFile(filename);
	XMLElement *rss=doc.FirstChildElement("rss");
	XMLElement *channel=rss->FirstChildElement("channel");
	XMLElement *item=channel->FirstChildElement("item");
	RssItem tmp;
	while(item)
	{
		tmp.title=item->FirstChildElement("title")->GetText();
		tmp.link=item->FirstChildElement("link")->GetText();
		tmp.description=item->FirstChildElement("description")->GetText();
		const char *content=item->FirstChildElement("content:encoded")->GetText();
		if(NULL==content)tmp.content=tmp.description;
		else tmp.content=std::regex_replace(content, reg, "");
		_rss.push_back(tmp);
		item=item->NextSiblingElement("item");
	}
}
void RssReader::dump(const char *filename)
{
	std::ofstream ofs(filename, std::ios::app);
	static int num=1;
	for(vector<RssItem>::iterator it=_rss.begin(); it!=_rss.end(); ++it,++num)
	{
		ofs<<"<doc>\n"
		  <<"<docid>"<<num<<"</docid>\n"
		  <<"<title>"<<it->title<<"</title>\n"
		  <<"<link>"<<it->link<<"</link>\n"
		  <<"<description>"<<it->description<<"</description>\n"
		  <<"<content>"<<it->content<<"</content>\n"
		  <<"</doc>\n";
	}
	_rss.clear();
}
int main(int argc, char *argv[])
{
	if(argc!=2){cout<<"argc error!"<<endl;return 0;}
	RssReader rRead;
	rRead.findParseDumpRss(argv[1]);
	return 0;
}
