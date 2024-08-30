#include"main.h"
#include<string.h>

void myzip(const string OriFileName, const string ZipFileName);
void myunzip(const string ZipFileName, const string OriFileName);

int main(int argc, char* argv[])
{
	if (argc != 4) {
		cout << "指令参数有误" << endl;
		return -1;
	}
	if (strcmp(argv[3],"zip") == 0) {
		myzip(argv[1], argv[2]); //压缩文件
	}
	else if (strcmp(argv[3], "unzip") == 0) {
		myunzip(argv[1], argv[2]); //压缩文件
	}
	else{
		cout << "指令参数有误" << endl;
		return -1;
	}
	return 0;
}

void myzip(const string OriFileName, const string ZipFileName)
{
	int ch_times[CHAR_RANGE] = { 0 };//不同字节类型（字符）对应的出现次数

	ReadFileChar(OriFileName, ch_times);

	Node* HuffmanTree = GetHmTree(ch_times);//根据字符权值创建哈夫曼树
	string NewCode[CHAR_RANGE];//每个字符对应的新编码方式，用二进制的字符串表示
	GetNewCode(NewCode, HuffmanTree);
	cout << "正在压缩文件......" << endl;

	WriteChTimes(ZipFileName, ch_times);//写入原文件字符权值

	string NewContent = "";//要写入文件的新内容，二进制字符串
	GetNewContent(NewContent, OriFileName, NewCode);//得到写入的内容
	WriteZipFile(ZipFileName, NewContent);

	DeleteTree(HuffmanTree);//释放哈夫曼树空间
	cout << "压缩文件完成！" << endl;

	int orifilesize = GetFilesize(OriFileName);//原文件大小
	int zipfilesize = GetFilesize(ZipFileName);//生成的压缩文件大小
	//输出压缩率
	cout << "原文件大小为" << orifilesize << "字节" << endl;
	cout << "生成的压缩文件大小为" << zipfilesize << "字节" << endl;
	cout << "压缩率为" << (double(zipfilesize) / double(orifilesize)) * 100 << "%" << endl;
}

void myunzip(const string ZipFileName, const string OriFileName)
{
	int ch_times[CHAR_RANGE] = { 0 };//不同字节类型（字符）对应的出现次数

	cout << "正在解压缩文件......" << endl;

	string ZipContent = "";//压缩文件的二进制字符串
	GetZipContent(ZipFileName, ZipContent, ch_times);//读取压缩文件的相关内容

	Node* HuffmanTree = GetHmTree(ch_times);//根据字符权值创建哈夫曼树
	WriteOriFile(OriFileName, ZipContent, HuffmanTree);

	DeleteTree(HuffmanTree);//释放哈夫曼树空间
	cout << "解压缩文件完成！" << endl;
}