#include <iostream>
#include "json.h"
#include <Windows.h>
#include <fstream>
using namespace std;
/*字符串去空格*/
void trim(string &s)
{
	int index = 0;
	if (!s.empty())
	{
		while ((index = s.find(' ', index)) != string::npos)
		{
			s.erase(index, 1);
		}
	}
}
/*读取txt文件到字符串中*/
string GetTxt(const string fileName)
{
	string str1 = "";   //将文本内容读取到字符串中
	ifstream ifs;       //构造输入流
	ifs.open(fileName,ios::in);
	if (!ifs) //打开文件失败
	{
		return str1;
	}
	char buf[256];
	while (!ifs.eof())		//判断文件是否到达结尾
	{
		ifs.getline(buf, 256, '\n');
		{
			string str(buf);	//cout << buf << endl; //打印当前读取数据
			str1 = str1.append(str);	//str = str + "\n";    //给读取的字符串加换行符
		}
	}
	ifs.close();
	trim(str1);
	return str1;
}

int main()
{
	Json::Reader reader;
	Json::Value root;
	string strTxt = GetTxt("C:\\Users\\Administrator\\Desktop\\tmp.txt");  //把txt文本读取到字符串
	if (strTxt != "")  //文件读取成功
	{
		if (reader.parse(strTxt, root))
		{
			string format_name = root["format"]["format_name"].asString();  //文件类型 mp3
			string duration = root["format"]["duration"].asString();  //文件长度 186s
			string size = root["format"]["size"].asString();   //文件大小 2919028byte
			string bit_rate = root["format"]["bit_rate"].asString();   //文件比特率 128000
		}
	}
	remove("C:\\Users\\Administrator\\Desktop\\tmp1.txt");//删除文件
	return 0;
}