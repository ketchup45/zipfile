#pragma once
#include<iostream>
using namespace std;
#define CHAR_RANGE 256 //字符范围

//哈夫曼树
struct Node {//哈夫曼树结点
	Node* lc;//指向左孩子
	Node* rc;//指向右孩子
	unsigned char ch;//本结点代表的字符
	int times;//本结点出现次数

	Node(unsigned char in_ch = 0, int in_times = 0) {//初始化
		lc = NULL;
		rc = NULL;
		times = in_times;
		ch = in_ch;
	}
};
void DeleteTree(Node* HuffmanTree);//释放哈夫曼树空间
Node* GetHmTree(int ch_times[CHAR_RANGE]);//根据字符权值创建哈夫曼树
void GetNewCode(string NewCode[CHAR_RANGE], Node* HmTree);//得到新编码格式
//根据新编码和哈夫曼树，生成原内容
void WriteOriFile(const string FileName, string& ZipContent, Node* HuffmanTree);

//文件操作
void ReadFileChar(const string FileName, int ch_times[CHAR_RANGE]);//读取文件的字符
void GetNewContent(string& NewContent, const string FileName, string NewCode[CHAR_RANGE]);//根据原文件，得到新的二进制编码字符串
void WriteChTimes(const string FileName, int ch_times[CHAR_RANGE]);//写入原文件字符权值
void WriteZipFile(const string FileName, string& NewContent);//写入压缩文件
int GetFilesize(const string FileName);//得到文件大小

void ReadChTimes(ifstream& fin, int ch_times[CHAR_RANGE]);//根据压缩文件的开头，得到字符权值
void GetZipContent(const string FileName, string& ZipContent, int ch_times[CHAR_RANGE]);//读入压缩二进制内容
//