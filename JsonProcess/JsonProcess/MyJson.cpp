#include <iostream>
#include "json.h"
#include <Windows.h>
#include <fstream>
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
	Json::Reader reader;
	Json::Value root;
	string strTxt = GetTxt("C:\\Users\\Administrator\\Desktop\\tmp.txt");  //��txt�ı���ȡ���ַ���
	if (strTxt != "")  //�ļ���ȡ�ɹ�
	{
		if (reader.parse(strTxt, root))
		{
			string format_name = root["format"]["format_name"].asString();  //�ļ����� mp3
			string duration = root["format"]["duration"].asString();  //�ļ����� 186s
			string size = root["format"]["size"].asString();   //�ļ���С 2919028byte
			string bit_rate = root["format"]["bit_rate"].asString();   //�ļ������� 128000
		}
	}
	remove("C:\\Users\\Administrator\\Desktop\\tmp1.txt");//ɾ���ļ�
	return 0;
}