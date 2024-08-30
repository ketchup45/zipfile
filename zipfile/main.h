#pragma once
#include<iostream>
using namespace std;
#define CHAR_RANGE 256 //�ַ���Χ

//��������
struct Node {//�����������
	Node* lc;//ָ������
	Node* rc;//ָ���Һ���
	unsigned char ch;//����������ַ�
	int times;//�������ִ���

	Node(unsigned char in_ch = 0, int in_times = 0) {//��ʼ��
		lc = NULL;
		rc = NULL;
		times = in_times;
		ch = in_ch;
	}
};
void DeleteTree(Node* HuffmanTree);//�ͷŹ��������ռ�
Node* GetHmTree(int ch_times[CHAR_RANGE]);//�����ַ�Ȩֵ������������
void GetNewCode(string NewCode[CHAR_RANGE], Node* HmTree);//�õ��±����ʽ
//�����±���͹�������������ԭ����
void WriteOriFile(const string FileName, string& ZipContent, Node* HuffmanTree);

//�ļ�����
void ReadFileChar(const string FileName, int ch_times[CHAR_RANGE]);//��ȡ�ļ����ַ�
void GetNewContent(string& NewContent, const string FileName, string NewCode[CHAR_RANGE]);//����ԭ�ļ����õ��µĶ����Ʊ����ַ���
void WriteChTimes(const string FileName, int ch_times[CHAR_RANGE]);//д��ԭ�ļ��ַ�Ȩֵ
void WriteZipFile(const string FileName, string& NewContent);//д��ѹ���ļ�
int GetFilesize(const string FileName);//�õ��ļ���С

void ReadChTimes(ifstream& fin, int ch_times[CHAR_RANGE]);//����ѹ���ļ��Ŀ�ͷ���õ��ַ�Ȩֵ
void GetZipContent(const string FileName, string& ZipContent, int ch_times[CHAR_RANGE]);//����ѹ������������
//