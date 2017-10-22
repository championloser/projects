#include<string.h>
#include<iostream>
using namespace std;
class String
{
public:
	String();
	String(const char *arr);
	~String();
	char *c_str();
	int length();
	int size();
	String & operator=(const char *arr);
	String & operator=(const String &rhs);
	String & operator+=(const String &rhs);
	String & operator+=(const char *arr);
	char & operator[](int idx);
	friend String operator+(const String &lhs, const String &rhs);
	friend bool operator==(const String &lhs, const String &rhs);
	friend bool operator!=(const String &lhs, const String &rhs);
	friend bool operator>(const String &lhs, const String &rhs);
	friend bool operator<(const String &lhs, const String &rhs);
	friend bool operator>=(const String &lhs, const String &rhs);
	friend bool operator<=(const String &lhs, const String &rhs);
	friend ostream & operator<<(ostream &out, const String &rhs);
	friend istream & operator>>(istream &in, String &rhs);
private:
	char *_arr;
	int _size;
};
String::String()
: _arr(NULL)
, _size(0)
{}
String::String(const char *arr)
: _arr(new char[strlen(arr)+1]())
, _size(strlen(arr))
{
	strcpy(_arr,arr);
}
String::~String()
{
	delete [] _arr;
	_arr=NULL;
}
char * String::c_str()
{
	return _arr;
}
int String::length()
{
	return _size;
}
int String::size()
{
	return _size;
}
String & String::operator=(const char *arr)
{
	delete [] _arr;
	_arr=new char[strlen(arr)+1]();
	strcpy(_arr,arr);
	_size=strlen(arr);
	return *this;
}
String & String::operator=(const String &rhs)
{
	delete [] _arr;
	_arr=new char[rhs._size+1]();
	strcpy(_arr,rhs._arr);
	_size=rhs._size;
	return *this;
}
String & String::operator+=(const String &rhs)
{
	char *newarr=new char[_size+rhs._size+1]();
	strcpy(newarr,_arr);	
	strcat(newarr,rhs._arr);
	delete [] _arr;
	_arr=newarr;
	_size=_size+rhs._size;
	return *this;
}
String & String::operator+=(const char *arr)
{
	char *newarr=new char[_size+strlen(arr)+1]();
	strcpy(newarr,_arr);
	strcat(newarr,arr);
	delete [] _arr;
	_arr=newarr;
	_size=_size+strlen(arr);
	return *this;
}
char & String::operator[](int idx)
{
	return _arr[idx];
}
String operator+(const String &lhs, const String &rhs)
{
	String str;
	str._arr=new char[lhs._size+rhs._size+1]();
	strcpy(str._arr,lhs._arr);
	strcat(str._arr,rhs._arr);
	str._size=lhs._size+rhs._size;
	return str;
}
bool operator==(const String &lhs, const String &rhs)
{
	if(lhs._arr==NULL && rhs._arr==NULL)return true;
	if(lhs._size!=rhs._size)return false;
	if(strcmp(lhs._arr,rhs._arr)==0)return true;
	else return false;
}
bool operator!=(const String &lhs, const String &rhs)
{
	if(lhs==rhs)return false;
	else return true;
}
bool operator>(const String &lhs, const String &rhs)
{
	if(lhs._arr==NULL && rhs._arr==NULL)return false;
	if(lhs._arr!=NULL && rhs._arr==NULL)return true;
	if(lhs._arr==NULL && rhs._arr!=NULL)return false;
	int ret=strcmp(lhs._arr,rhs._arr);
	if(ret>0)return true;
	else return false;
}
bool operator<(const String &lhs, const String &rhs)
{
	if(lhs._arr==NULL && rhs._arr==NULL)return false;
	if(lhs._arr!=NULL && rhs._arr==NULL)return false;
	if(lhs._arr==NULL && rhs._arr!=NULL)return true;
	int ret=strcmp(lhs._arr,rhs._arr);
	if(ret<0)return true;
	else return false;
}
bool operator>=(const String &lhs, const String &rhs)
{
	if(lhs._arr==NULL && rhs._arr==NULL)return true;
	if(lhs._arr!=NULL && rhs._arr==NULL)return true;
	if(lhs._arr==NULL && rhs._arr!=NULL)return false;
	int ret=strcmp(lhs._arr,rhs._arr);
	if(ret>=0)return true;
	else return false;
}
bool operator<=(const String &lhs, const String &rhs)
{
	if(lhs._arr==NULL && rhs._arr==NULL)return true;
	if(lhs._arr!=NULL && rhs._arr==NULL)return false;
	if(lhs._arr==NULL && rhs._arr!=NULL)return true;
	int ret=strcmp(lhs._arr,rhs._arr);
	if(ret<=0)return true;
	else return false;
}
ostream & operator<<(ostream &out, const String &rhs)
{
	out<<rhs._arr;
	return out;
}
istream & operator>>(istream &in, String &rhs)
{
	char buf[1024]={0};
	in>>buf;
	delete [] rhs._arr;
	rhs._arr=new char[strlen(buf)+1]();
	strcpy(rhs._arr,buf);
	return in;
}
int main()
{
	String str1("hello world");
	String str2="jiaxian";
	String str3;
	str3="jiang jiaxian";
	cout<<str3<<endl;
	cin>>str3;
	cout<<str3<<endl;
	return 0;
}
