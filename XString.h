#include "stdafx.h"
#include <iostream>
#include "CharInfo.h"
using namespace std;
class MyString {
private:
	char* ch;
	int length;

public:
	MyString() {
		this->length = 0;
	}
	MyString(char* c) {
		length = strlen(c);
		ch = new char[length + 1];
		for (int i = 0; i < length; i++)
		{
			this->ch[i] = c[i];
		}
		ch[length] = '\0';
	}
	~MyString() {
		delete(ch);

	}
	int strlength();//串的长度
	int strcompare(MyString s, char* t);//串的比较 若s>t返回相差字符个数，若s=t返回0,若s<t返回-1
	int clearstring();//清空串.0代表失败，1代表成功
	int concat(MyString& n, char* t);//n为返回的新字符串
	char* data();	//返回当前对象的字符串内容
	int indexof(char* t);//返回子串所在位置,-1代表失败，
	char* substring(int start, int length);//start从0开始，length指代截取字符串长度
	void  replace(MyString& n, MyString& s, char* c, char* flag, bool search);//n代表新字符串，s代表原来字符串，c替换字符串，flag替换标志，search代表是否全文替换。
	CharInfo CharCount();//返回字符串统计信息的结构体
	void setchar(char* c);//将ch数组赋值
	void insert(char* c, int index);//c指插入内容，index代表插入位置
	char* operator+(char* c);//运算符‘+’重载---使用方法Mystring s=s+"12321";
	void  operator=(char* c);//运算符‘=’重载

};
int MyString::strlength() {
	return this->length;
}
void MyString::setchar(char* c) {
	this->length = strlen(c);
	this->ch = new char[length + 1];
	for (int i = 0; i < length; i++)
	{
		this->ch[i] = c[i];
	}
	ch[length] = '\0';
}
//从index+1（当前位的后一位）的位置（index从0开始计算）开始截取，分成2半，复制前半部->加入插入内容->复制后半部
void MyString::insert(char* c, int index) {
	int nLength = strlen(c) + this->length;
	char* k = new char[nLength + 1];

	if (index >= 0)
	{
		char* a = this->substring(0, index + 1);

		char* b = this->substring(index + 1, this->length - index + 1);
		cout << a << " " << b << endl;
		for (int i = 0; i < (int)strlen(a); i++)
		{
			k[i] = a[i];
		}

		for (int i = 0; i < (int)strlen(c); i++)
		{
			k[i + strlen(a)] = c[i];
		}

		for (int i = 0; i < (int)strlen(b); i++)
		{
			k[strlen(a) + strlen(c) + i] = b[i];
		}
		k[nLength] = '\0';


		this->ch = k;
	}
	else {
		cout << "找不到插入位置" << endl;
	}

}
int MyString::strcompare(MyString s, char* t) {
	for (int i = 0; i < s.length && strlen(t); i++) {
		if (s.ch[i] != t[i])
		{
			return s.ch[i] - t[i];
		}
		else
		{
			return s.length - strlen(t);
		}
	}
	return 0;
}
int MyString::clearstring() {
	if (this->ch)
	{
		delete(this->ch);
		this->ch = NULL;
		this->length = 0;
		return 1;
	}
	else {
		return 0;
	}

}
int MyString::concat(MyString& n, char* t) {
	if (clearstring())
	{
		if (n.ch = new char[this->length + strlen(t) + 1])
		{
			for (int i = 0; i < this->length; i++) {
				n.ch[i] = this->ch[i];
			}
			for (int i = 0; i < strlen(t); i++) {
				n.ch[i + this->length - 1] = t[i];
			}
			n.ch[this->length + strlen(t)] = '\0';
			n.length = this->length + strlen(t);
			return 1;
		}
		else {
			cout << "分配内存失败" << endl;
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
char* MyString::data() {
	return this->ch;
}
//回溯法查找
int MyString::indexof(char* t) {
	int i = 0, j = 0;
	int slen = strlen(this->ch);
	int plen = strlen(t);

	while (j < plen && i < slen) {
		if (this->ch[i] == t[j]) {
			i++;
			j++;

		}
		else {
			i = i - j + 1;
			j = 0;

		}
	}

	if (j == plen)
	{
		return i - plen + 1;
	}
	else
	{
		return 0;
	}
}
//截取
char* MyString::substring(int start, int length) {
	if (char* c = new char[length + 1]) {

		for (int i = 0; i < length; i++)
		{
			c[i] = this->ch[start + i];
		}
		c[length] = '\0';
		return c;
	}
	else {
		return NULL;
	}

}
//替换
void MyString::replace(MyString& n, MyString& s, char* pSrc, char* pDst, bool search)
{
	char* pi, * po, * p;
	int nSrcLen, nDstLen, nLen;

	// 指向输入字符串的游动指针.   
	pi = s.ch;
	// 指向输出字符串的游动指针.   
	po = n.ch;
	// 计算被替换串和替换串的长度.   
	nSrcLen = strlen(pSrc);
	nDstLen = strlen(pDst);

	// 查找pi指向字符串中第一次出现替换串的位置,并返回指针(找不到则返回null).   
	p = strstr(pi, pSrc);
	if (p)
	{
		// 找到.   
		while (p)
		{
			// 计算被替换串前边字符串的长度.   
			nLen = (int)(p - pi);
			// 复制到输出字符串.   
			memcpy(po, pi, nLen);
			memcpy(po + nLen, pDst, nDstLen);
			// 跳过被替换串.   
			pi = p + nSrcLen;
			// 调整指向输出串的指针位置.   
			po = po + nLen + nDstLen;
			// 继续查找.
			if (search) {
				p = strstr(pi, pSrc);
			}
			else {
				break;
			}

		}
		// 复制剩余字符串.   
		strcpy(po, pi);
	}
	else
	{
		// 没有找到则原样复制.   
		strcpy(po, pi);
	}
}
CharInfo MyString::CharCount() {

	CharInfo charinfo;
	charinfo.length = 0;
	charinfo.number = 0;
	charinfo.schar = 0;
	charinfo.bchar = 0;
	charinfo.space = 0;
	for (int i = 0;; i++)
	{
		charinfo.length = i;
		if (this->ch[i] >= 65 && this->ch[i] <= 90)   //判断是否为小写
		{
			charinfo.bchar += 1;
			continue;
		}
		if (this->ch[i] >= 97 && this->ch[i] <= 122)     //判断是否为大写
		{
			charinfo.schar += 1;
			continue;
		}
		if (this->ch[i] == 32)     //判断是否为空格
		{
			charinfo.space += 1;
			continue;
		}
		if (this->ch[i] >= '0' && this->ch[i] <= '9')   //判断是否为数字
		{
			charinfo.number += 1;
			continue;
		}
		if (this->ch[i] == '\0') break;      //判断字符串是否结束

	}
	charinfo.length = this->length;
	return charinfo;
}
char* MyString::operator+(char* c) {
	char* nch = new char[strlen(this->ch) + strlen(c) + 1];
	for (int i = 0; i < this->length; i++)
	{
		nch[i] = this->ch[i];
	}
	for (int i = 0; i < strlen(c); i++)
	{
		nch[i + strlen(this->ch)] = c[i];
	}
	nch[strlen(this->ch) + strlen(c) + 1] = '\0';
	return nch;
}
void  MyString::operator =(char* c) {
	this->length = strlen(c);
	this->ch = new char[length + 1];
	for (int i = 0; i < length; i++)
	{
		this->ch[i] = c[i];
	}
	ch[length] = '\0';

}