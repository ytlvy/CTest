/*
 * @Author: Y.t
 * @Date: 2021-06-22 10:50:59
 * @LastEditors: Y.t
 * @LastEditTime: 2021-06-22 10:53:20
 * @Description: 
 */

#include <stdio.h>
#include <cstdio>
#include <cstdlib>

class MyString
{
public :
	MyString(const char *str = NULL);//重载构造函数
	MyString(const MyString &s);//重载拷贝构造函数
	~MyString();//重载析构函数
	MyString & operator = (const MyString & s);// 赋值函数(赋值的重载）
private :
	char *mdata;//用于保存字符串
};
MyString::MyString(const char*str)//构造函数
{
	if (str ==NULL)//判断是否为空
	{
		mdata = new char[1];
		*mdata = '\0';

	}
	else
	{
		const int length = strlen(str);
		mdata = new char[length + 1];
		strcpy(mdata, str);
	}
}
MyString::MyString(const MyString &s)//拷贝构造函数
{
	int length = strlen(s.mdata);
	if (length == 0)//判断是否为空
	{
		mdata = new  char[1];
		*mdata = '\0';
	}
	else
	{
		mdata = new char[length + 1];
		strcpy(mdata, s.mdata);
	}
}
MyString::~MyString()
{
	delete[] mdata;
}
MyString &MyString:: operator=(const MyString &s)
{
	if (this ==& s)//检查是否是自赋值
	{
		return *this;
		
	}
	delete[] mdata;//释放空间。
	int length = strlen(s.mdata);
	mdata = new char[length + 1];
	strcpy(mdata,s.mdata);
	return *this;
	
	
}