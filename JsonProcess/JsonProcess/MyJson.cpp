#include <iostream>
#include "json.h"
#include <Windows.h>
#include <fstream>
#include "shellapi.h"
#include <stdlib.h>
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
	/*char buf[256];
	ifstream ifs("C:\\Users\\yangk\\Desktop\\IsBat.bat");
	while (!ifs.eof())
	{
		ifs.getline(buf,256,'\n');
		cout << buf << endl;
	}
	ifs.close();
	system("pause");
	return 0;*/

	//写bat文件,bat文件放到C:\\Users\\IsBat12.bat,执行bat生成的文件信息txt文件的路径。
	ofstream ofs;
	ofs.open("C:\\Users\\yangk\\Desktop\\IsBat12.bat", ios::trunc);
	string targetFile = "C:\\Users\\yangk\\Desktop\\test.avi ";
	string str = "C:\\Users\\yangk\\Desktop\\ffmpeg0901\\ffmpeg\\ffmpeg-20170820-8754ccd-win64-shared\\bin\\ffprobe.exe  >E:\\tmp.txt -v quiet -print_format json -show_format -show_streams " + targetFile;
	if (ofs)
	{
		for (int i = 0; i <= str.length() - 1; i++)
		{
			ofs << str[i];
		}
	}
	ofs.close();
	//执行.bat文件，传入文件路径即可;生成文件信息的txt文件。
	HINSTANCE hd = ShellExecuteA(NULL, "open", "C:\\Users\\yangk\\Desktop\\IsBat12.bat", NULL, NULL, SW_SHOW);
	long hdInt = (long)hd;
	cout << hdInt << endl;


	//ShellExecuteA(NULL, "open", "c://WINDOWS//system32//cmd.exe", "/c md c://zzz", "", SW_SHOW);
	//string command = " -v quiet -print_format json -show_format -show_streams C:\\Users\\yangk\\Desktop\\test.avi >E:\\tmp.txt";
	//ShellExecuteA(NULL, "open", "ffprobe.exe", command.c_str(), NULL, SW_SHOW);
	//WinExec("ffprobe.exe -v quiet -print_format json -show_format -show_streams C:\\Users\\yangk\\Desktop\\test.avi >E:\\tmp.txt", SW_SHOW);
	//system("ffprobe.exe -v quiet -print_format json -show_format -show_streams C:\\Users\\yangk\\Desktop\\test.avi >C:\\Users\\公用\\tmp.txt");

	remove("C:\\Users\\Administrator\\Desktop\\tmp1.txt");//删除文件

	string strTxt = GetTxt("E:\\tmp.txt");  //把txt文本读取到字符串
	if (strTxt != "")  //文件读取成功
	{
		Json::Reader reader;
		Json::Value root;
		if (reader.parse(strTxt, root))
		{
			string format_name = root["format"]["format_name"].asString();  //文件类型 mp3
			string duration = root["format"]["duration"].asString();  //文件长度 186s
			string size = root["format"]["size"].asString();   //文件大小 2919028byte
			string bit_rate = root["format"]["bit_rate"].asString();   //文件比特率 128000
		}
	}
	system("pause");
	return 0;
}