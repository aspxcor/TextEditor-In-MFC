#include "stdafx.h"
#include<iostream>
#include <iosfwd>
#include <afxdlgs.h>
#include <commdlg.h>
#include <fstream>
#include <string>
#include "MyStack.h"
using namespace std;
class TextEditor
{
public:
	TextEditor(MyString s) {
		this->strcurrent = s;
	}
	TextEditor() {
		previous = initStack();
		now = initStack();
	}
	void ShowMainMune();//主菜单
	void ShowEditorMune();//编辑菜单
	void Run();//运行函数
	void Exit();//退出
	void Open();//打开文件
	void Save(char* path);//输出文件
	void FileSave();//保存
	void Clear();//清屏
	void Review();//重新输出当前的字符串
	void OutputCharCount();//统计字符
	void Input(string a, string b);//文本编辑器输入函数
	void Search();//文本查找
	void Replace();//文本替换
	void Delete();//文本删除
	void Insert();//文本插入
	void  Copy(char*& temp);//文本复制
	void  Cut(char*& temp);//文本剪切
	void Paste(char* temp);//文本粘贴
private:
	MyString strcurrent;//当前的字符串
	linkStack* previous;//修改前的
	linkStack* now; //修改后的
	MyString filepath;//文件保存位置
};
//输入插入位置->保存原先的字符串->插入->显示->保存插入后的字符串
void TextEditor::Paste(char* temp) {
	int index;
	if (strlen(temp) != 0)
	{
		cout << "粘贴内容：" << temp << endl;
		cout << "请输入你要粘贴的位置（用查找功能找到粘贴位置）" << endl;
		cin >> index;
		previous = push(previous, strcurrent.data());
		strcurrent.insert(temp, index);
		Review();
		now = push(now, strcurrent.data());
	}
	else
	{
		cout << "当前没有可粘贴内容" << endl;
	}
}
//输入开始位置和截取长度->截取字符串->显示截取内容->保存截取内容
void  TextEditor::Copy(char*& temp) {
	int start = 0;//复制粘贴的开始位置
	int length = 0;//复制粘贴的长度
	MyString copy;//复制,粘贴的内容
	cout << "你要从哪个位置开始复制?长度是多少?(英文每个字母长度为1，中文每个字长度为2)" << endl;
	cin >> start >> length;
	length = (length / 2);
	length = length * 2;
	copy = strcurrent.substring(start + 1, length);
	if (copy.strlength() != 0)
	{
		cout << "复制成功" << endl;
		cout << "内容为：" << copy.data() << endl;
		cout << "长度为：" << copy.strlength() << endl;
		temp = new char[strlen(copy.data())];
		for (int i = 0; i < strlen(copy.data()); i++)
		{
			temp[i] = copy.data()[i];
		}
		temp[strlen(copy.data())] = '\0';
	}
	else {
		cout << "复制失败" << endl;
		temp = "";
	}
}
//输入开始剪切位置和剪切长度->截取字符串->保存原先的字符串->替换字符串->保存替换后的字符串->显示替换后的内容->显示截取内容->保存截取内容
void  TextEditor::Cut(char*& temp) {
	int start = 0;//复制粘贴的开始位置
	int length = 0;//复制粘贴的长度
	MyString copy;//复制,粘贴的内容
	cout << "你要从哪个位置开始剪切?长度是多少?(英文每个字母长度为1，中文每个字长度为2)" << endl;
	cin >> start >> length;
	length = (length / 2);
	length = length * 2;
	copy = strcurrent.substring(start + 1, length);
	MyString s = strcurrent.data();
	MyString d = strcurrent.data();
	if (copy.strlength() != 0)
	{
		previous = push(previous, strcurrent.data());
		strcurrent.replace(d, s, copy.data(), "", false);
		strcurrent.setchar(d.data());
		Review();
		cout << "剪切内容为：" << copy.data() << endl;
		temp = new char[strlen(copy.data())];
		for (int i = 0; i < strlen(copy.data()); i++)
		{
			temp[i] = copy.data()[i];
		}
		temp[strlen(copy.data())] = '\0';
		now = push(now, strcurrent.data());
	}
	else {
		cout << "剪切失败" << endl;
		temp = "";
	}
}
//输入插入位置->保存原先的字符串->插入->显示->保存插入后的字符串
void TextEditor::Insert() {
	int index = 0;//插入位置
	previous = push(previous, strcurrent.data());
	char* buffer = new char[strcurrent.strlength() + 1];
	cout << "请输入要插入的内容" << endl;
	cin >> buffer;
	cout << "请输入插入位置" << endl;
	cin >> index;
	strcurrent.insert(buffer, index - 1);
	Clear();
	Review();
	now = push(now, strcurrent.data());
	delete(buffer);
}
//保存原来的字符串->替换->保存
void TextEditor::Delete() {
	int deleteflag, replaceflag;
	previous = push(previous, strcurrent.data());
	MyString s = strcurrent.data();//被替换后的返回的内容
	MyString d = strcurrent.data();//被替换的内容
	char* buffer = new char[strcurrent.strlength() + 1];
	cout << "请输入要删除的内容" << endl;
	cin >> buffer;
	cout << "是否全文删除这个内容 1.是 0.否" << endl;
	cin >> replaceflag;
	strcurrent.replace(d, s, buffer, "", replaceflag);
	strcurrent.setchar(d.data());
	Clear();
	Review();
	now = push(now, strcurrent.data());
	delete(buffer);
}
//同上，删除就是把替换内容写为"",替换允许用户输入
void TextEditor::Replace() {
	previous = push(previous, strcurrent.data());
	MyString s = strcurrent.data();
	MyString d = strcurrent.data();
	int replaceflag;
	char* buffer = new char[strcurrent.strlength() + 1];
	char* p = new char[strcurrent.strlength() + 1];
	cout << "请输入要替换的内容" << endl;
	cin >> buffer;
	cout << "请输入新内容" << endl;
	cin >> p;
	cout << "是否全文替换 1.是 0.否" << endl;
	cin >> replaceflag;
	strcurrent.replace(d, s, buffer, p, replaceflag);
	strcurrent.setchar(d.data());
	Clear();
	Review();
	now = push(now, strcurrent.data());
	delete(p);
	delete(buffer);
}
//temp是原文的复制，因为考虑到要不断的截取字符串（全文查找），所有不对原文修改。
void TextEditor::Search() {
	int search;
	int searchlength = 0;
	MyString temp = strcurrent;
	char* buffer = new char[strcurrent.strlength() + 1];
	cout << "请输入要查找的内容" << endl;
	cin >> buffer;
	buffer[strcurrent.strlength()] = '\0';
	cout << "是否全文查找 1.是 0.否" << endl;
	cin >> search;
	if (search == 1) {
		while (temp.indexof(buffer)) {
			int start = temp.indexof(buffer);
			searchlength = searchlength + start;
			cout << "查找位置是：" << searchlength << endl;
			temp = temp.substring(start, temp.strlength() - start);

		}
	}
	else {
		cout << "查找位置是：" << strcurrent.indexof(buffer) << endl;
	}

	delete(buffer);
}
void TextEditor::FileSave() {
	char* buffer = new char[100];//保存路径
	if (strcurrent.strlength() != 0)
	{
		cout << "请输入保存路径" << endl;
		cin >> buffer;
		//filepath.setchar(buffer);
		Save(buffer);
	}
	else {
		cout << "当前没有文本" << endl;
	}
}
void TextEditor::Input(string a, string b) {
	char* buffer;//要查找，替换，删除的缓冲
	cout << "请输入文本,换行以'#'结束" << endl;
	a.clear();
	while (1) {
		getline(cin, b);
		if (b[0] != '#') {

			a = a + b + '\n';

		}
		else {
			break;
		}
	}
	buffer = new char[a.length() + 1];
	for (int i = 0; i < a.length(); i++) {
		buffer[i] = a.data()[i];
	}
	buffer[a.length() + 1] = '\0';
	strcurrent = buffer;
}
void TextEditor::OutputCharCount() {
	cout << "大写字母数：" << strcurrent.CharCount().bchar << endl;
	cout << "小写字母数：" << strcurrent.CharCount().schar << endl;
	cout << "空格数：" << strcurrent.CharCount().space << endl;
	cout << "字符总数：" << strcurrent.CharCount().length << endl;
	cout << "数字总数：" << strcurrent.CharCount().number << endl;
}
void TextEditor::Clear() {
	system("cls");
}
void TextEditor::Review() {
	cout << "*----------------------编辑内容-----------------------*" << endl;
	cout << strcurrent.data() << endl;
	cout << "*----------------------操作选项-----------------------*" << endl;
	ShowEditorMune();
	cout << "*--------------------请输出操作编号-------------------*" << endl;
}
void TextEditor::ShowMainMune() {
	cout << "*----------------------顺心文本编辑器-----------------------*" << endl;
	cout << "*------------------------1.打开文件-------------------------*" << endl;
	cout << "*------------------------2.新建文件-------------------------*" << endl;
	cout << "*------------------------3.保存文件-------------------------*" << endl;
	cout << "*------------------------4.编辑-----------------------------*" << endl;
	cout << "*------------------------5.退出-----------------------------*" << endl;
	cout << "*------------------------请输出操作编号---------------------*" << endl;
}
void TextEditor::ShowEditorMune() {
	cout << "6.查找" << endl;
	cout << "7.替换" << endl;
	cout << "8.删除" << endl;
	cout << "9.插入" << endl;
	cout << "10.撤销" << endl;
	cout << "11.重做" << endl;
	cout << "12.字符统计" << endl;
	cout << "13.复制" << endl;
	cout << "14.剪切" << endl;
	cout << "15.粘贴" << endl;
	cout << "16.返回上一层" << endl;
}
void TextEditor::Exit() {
	cout << "感谢使用" << endl;

	exit(-1);
}
void TextEditor::Run() {
	ShowMainMune();
	int command;//指令
	//MyString temp;//查找操作是的临时缓冲，不直接在当前字符操作，避免出错
	string a = "";//用户输入的全部字符串
	string b = "";//用户输入的每一行字符串
	char* temp;
	while (1)
	{
		cin >> command;
		cin.ignore(2, '\n');
		switch (toupper(command))
		{
		case 1:
			Open();
			Clear();
			Review();
			break;
		case 2:
			Input(a, b);
			Clear();
			Review();
			break;
		case 3:
			FileSave();
			break;
		case 4:
			ShowEditorMune();

			break;
		case 5:
			Exit();
		case 6:
			Search();
			cout << "*------------------------请输出操作编号---------------------*" << endl;
			break;
		case 7:
			Replace();
			break;
		case 8:
			Delete();
			cout << "*------------------------请输出操作编号---------------------*" << endl;
			break;
		case 9:
			Insert();

			break;
		case 10:
			if (previous != NULL)
			{
				now = push(now, strcurrent.data());
				strcurrent = previous->data;
				Clear();
				Review();
				previous = pop(previous);

			}
			else {
				cout << "你当前没进行任何操作" << endl;
			}

			break;
		case 11:
			if (now != NULL)
			{
				previous = push(previous, strcurrent.data());
				strcurrent = now->data;
				Clear();
				Review();
				now = pop(now);

			}
			else {
				cout << "你当前没进行任何操作" << endl;
			}

			break;
		case 12:
			Clear();
			Review();
			OutputCharCount();

			break;
		case 13:

			Copy(temp);
			cout << "*------------------------请输出操作编号---------------------*" << endl;
			break;
		case 14:

			Cut(temp);
			cout << "*------------------------请输出操作编号---------------------*" << endl;
			break;
		case 15:
			Paste(temp);
			cout << "*------------------------请输出操作编号---------------------*" << endl;
			break;
		case 16:
			ShowMainMune();
			break;
		default:
			cout << "\n***Illegal command***\n";
			ShowMainMune();

		}

	}
}
void TextEditor::Save(char* buffer) {
	int i;
	ofstream outfile(buffer);
	if (!outfile) {
		cerr << "输出错误，不存在指定文件" << endl;
		exit(1);
	}
	for (i = 0; i < strcurrent.strlength() - 1; i++)
	{
		outfile << strcurrent.data()[i];
	}
	cout << "输出成功" << endl;
	outfile.close();
}
void TextEditor::Open() {
	OPENFILENAME ofn;
	TCHAR szPath[MAX_PATH];
	ZeroMemory(szPath, sizeof(szPath));
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	TCHAR szBuffer[1024] = { 0 };
	ofn.lpstrFilter = TEXT("应用程序\0*.*\0*.*\0\0");
	ofn.lpstrFile = szBuffer;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_DONTADDTORECENT | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NONETWORKBUTTON | OFN_PATHMUSTEXIST;
	if (GetOpenFileName(&ofn) == TRUE) {

		int iLength = WideCharToMultiByte(CP_ACP, 0, szBuffer, -1, NULL, 0, NULL, NULL); ;//CString,TCHAR汉字算一个字符，因此不用普通计算长度 
		char* _char = new char[iLength + 1];
		WideCharToMultiByte(CP_ACP, 0, szBuffer, -1, _char, iLength, NULL, NULL);

		filepath = _char;
		ifstream f(filepath.data(), ios::in | ios::binary);
		int length;
		f.seekg(0, ios::end);
		length = f.tellg();
		f.seekg(0, ios::beg);
		char* buffer = new char[length + 1];
		f.read(buffer, length);
		buffer[length] = '\0';
		this->strcurrent.setchar(buffer);
		delete(buffer);


	}
}