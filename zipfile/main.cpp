#include"main.h"
#include<string.h>

void myzip(const string OriFileName, const string ZipFileName);
void myunzip(const string ZipFileName, const string OriFileName);

int main(int argc, char* argv[])
{
	if (argc != 4) {
		cout << "ָ���������" << endl;
		return -1;
	}
	if (strcmp(argv[3],"zip") == 0) {
		myzip(argv[1], argv[2]); //ѹ���ļ�
	}
	else if (strcmp(argv[3], "unzip") == 0) {
		myunzip(argv[1], argv[2]); //ѹ���ļ�
	}
	else{
		cout << "ָ���������" << endl;
		return -1;
	}
	return 0;
}

void myzip(const string OriFileName, const string ZipFileName)
{
	int ch_times[CHAR_RANGE] = { 0 };//��ͬ�ֽ����ͣ��ַ�����Ӧ�ĳ��ִ���

	ReadFileChar(OriFileName, ch_times);

	Node* HuffmanTree = GetHmTree(ch_times);//�����ַ�Ȩֵ������������
	string NewCode[CHAR_RANGE];//ÿ���ַ���Ӧ���±��뷽ʽ���ö����Ƶ��ַ�����ʾ
	GetNewCode(NewCode, HuffmanTree);
	cout << "����ѹ���ļ�......" << endl;

	WriteChTimes(ZipFileName, ch_times);//д��ԭ�ļ��ַ�Ȩֵ

	string NewContent = "";//Ҫд���ļ��������ݣ��������ַ���
	GetNewContent(NewContent, OriFileName, NewCode);//�õ�д�������
	WriteZipFile(ZipFileName, NewContent);

	DeleteTree(HuffmanTree);//�ͷŹ��������ռ�
	cout << "ѹ���ļ���ɣ�" << endl;

	int orifilesize = GetFilesize(OriFileName);//ԭ�ļ���С
	int zipfilesize = GetFilesize(ZipFileName);//���ɵ�ѹ���ļ���С
	//���ѹ����
	cout << "ԭ�ļ���СΪ" << orifilesize << "�ֽ�" << endl;
	cout << "���ɵ�ѹ���ļ���СΪ" << zipfilesize << "�ֽ�" << endl;
	cout << "ѹ����Ϊ" << (double(zipfilesize) / double(orifilesize)) * 100 << "%" << endl;
}

void myunzip(const string ZipFileName, const string OriFileName)
{
	int ch_times[CHAR_RANGE] = { 0 };//��ͬ�ֽ����ͣ��ַ�����Ӧ�ĳ��ִ���

	cout << "���ڽ�ѹ���ļ�......" << endl;

	string ZipContent = "";//ѹ���ļ��Ķ������ַ���
	GetZipContent(ZipFileName, ZipContent, ch_times);//��ȡѹ���ļ����������

	Node* HuffmanTree = GetHmTree(ch_times);//�����ַ�Ȩֵ������������
	WriteOriFile(OriFileName, ZipContent, HuffmanTree);

	DeleteTree(HuffmanTree);//�ͷŹ��������ռ�
	cout << "��ѹ���ļ���ɣ�" << endl;
}