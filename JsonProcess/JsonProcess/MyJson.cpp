#include <iostream>
#include "json.h"
#include <Windows.h>
#include <fstream>
#include "shellapi.h"
#include <stdlib.h>
using namespace std;

/*�ַ���ȥ�ո�*/
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
/*��ȡtxt�ļ����ַ�����*/
string GetTxt(const string fileName)
{
	string str1 = "";   //���ı����ݶ�ȡ���ַ�����
	ifstream ifs;       //����������
	ifs.open(fileName,ios::in);
	if (!ifs) //���ļ�ʧ��
	{
		return str1;
	}
	char buf[256];
	while (!ifs.eof())		//�ж��ļ��Ƿ񵽴��β
	{
		ifs.getline(buf, 256, '\n');
		{
			string str(buf);	//cout << buf << endl; //��ӡ��ǰ��ȡ����
			str1 = str1.append(str);	//str = str + "\n";    //����ȡ���ַ����ӻ��з�
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

	//дbat�ļ�,bat�ļ��ŵ�C:\\Users\\IsBat12.bat,ִ��bat���ɵ��ļ���Ϣtxt�ļ���·����
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
	//ִ��.bat�ļ��������ļ�·������;�����ļ���Ϣ��txt�ļ���
	HINSTANCE hd = ShellExecuteA(NULL, "open", "C:\\Users\\yangk\\Desktop\\IsBat12.bat", NULL, NULL, SW_SHOW);
	long hdInt = (long)hd;
	cout << hdInt << endl;


	//ShellExecuteA(NULL, "open", "c://WINDOWS//system32//cmd.exe", "/c md c://zzz", "", SW_SHOW);
	//string command = " -v quiet -print_format json -show_format -show_streams C:\\Users\\yangk\\Desktop\\test.avi >E:\\tmp.txt";
	//ShellExecuteA(NULL, "open", "ffprobe.exe", command.c_str(), NULL, SW_SHOW);
	//WinExec("ffprobe.exe -v quiet -print_format json -show_format -show_streams C:\\Users\\yangk\\Desktop\\test.avi >E:\\tmp.txt", SW_SHOW);
	//system("ffprobe.exe -v quiet -print_format json -show_format -show_streams C:\\Users\\yangk\\Desktop\\test.avi >C:\\Users\\����\\tmp.txt");

	remove("C:\\Users\\Administrator\\Desktop\\tmp1.txt");//ɾ���ļ�

	string strTxt = GetTxt("E:\\tmp.txt");  //��txt�ı���ȡ���ַ���
	if (strTxt != "")  //�ļ���ȡ�ɹ�
	{
		Json::Reader reader;
		Json::Value root;
		if (reader.parse(strTxt, root))
		{
			string format_name = root["format"]["format_name"].asString();  //�ļ����� mp3
			string duration = root["format"]["duration"].asString();  //�ļ����� 186s
			string size = root["format"]["size"].asString();   //�ļ���С 2919028byte
			string bit_rate = root["format"]["bit_rate"].asString();   //�ļ������� 128000
		}
	}
	system("pause");
	return 0;
}