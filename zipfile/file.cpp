#include"main.h"
#include<fstream>
#include<math.h>

//读取原文件，得到字符权值
void ReadFileChar(const string FileName, int ch_times[CHAR_RANGE])
{
	ifstream fin;
	fin.open(FileName, ios::in | ios::binary);
	if (!fin.is_open()) {
		cout << "文件打开失败" << endl;
		exit(-1);
	}
	unsigned char ch;//每次读入的字符
	while (!fin.eof()) {//循环读入
		ch = fin.get();
		ch_times[ch]++;//对应字符出现次数+1
	}
	ch_times[CHAR_RANGE - 1]--;//取消计算最后一个EOF
	fin.close();//关闭文件
}

//根据原文件，得到新的二进制编码字符串
void GetNewContent(string& NewContent, const string FileName, string NewCode[CHAR_RANGE])
{
	ifstream fin;
	fin.open(FileName, ios::in | ios::binary);
	if (!fin.is_open()) {
		cout << "文件打开失败" << endl;
	}
	unsigned char ch;//每次读入的字符
	while (!fin.eof()) {//循环读入
		ch = fin.get();
		NewContent += NewCode[ch];
	}
	fin.close();//关闭文件
}

//写入压缩文件
void WriteZipFile(const string FileName, string& NewContent)
{
	ofstream fout;
	fout.open(FileName, ios::out| ios::binary|ios::app);
	if (!fout.is_open()) {
		cout << "文件打开失败" << endl;
		exit(-1);
	}
    //
	unsigned char pad0 = (8 - NewContent.length() % 8) % 8;//填充的0的位数
	fout.put(pad0);//写入填充位数

	//写入剩余内容
	char ch = 0;//即将被写入的字节
	int cnt = 0;//计数器
	for (int i = 0; i < NewContent.length(); i++) {//逐位写入
		cnt++;//代表当前的位数
		if (NewContent[i] == '0') {
			ch = ch << 1;//右移1位
		}
		else if (NewContent[i] == '1') {
			ch = ch << 1;//右移1位
			ch = ch | 1;//令ch最后一位为1
		}
		if (cnt == 8) {//满8位，写入
			fout.put(ch);
			ch = 0;//更新
			cnt = 0;
		}
	}
	//填充剩余位数
	if (pad0 != 0) {//ch的后pad0位是需要写入的
		ch = (ch << pad0);
		fout.put(ch);
	}

	fout.close();//关闭文件
}

//把int型写入文件
void WriteInt(ofstream &fout, int wi)
{
	for (int i = 0; i < 4; i++) {
		char ch = 0;//待写入的字符
		for (int j = 0; j < 8; j++) {
			ch = ch << 1;
			if (wi & 0x80000000) //若最高位为1
				ch = ch | 1;	
			wi = wi << 1;
		}
		fout.put(ch);
	}
}

//写入原文件字符权值
void WriteChTimes(const string FileName, int ch_times[CHAR_RANGE])
{
	ofstream fout(FileName, ios::out|ios::binary);
	if (!fout.is_open()) {
		cout << "文件打开失败" << endl;
		exit(-1);
	}
	for (int i = 0; i < CHAR_RANGE - 1; i++) {
		if (ch_times[i] != 0) {
			fout.put(i);
			WriteInt(fout, ch_times[i]);
		}
	}
	//写入最后CHAR_RANGE的ch_times作为结束标志
	fout.put(unsigned char(CHAR_RANGE - 1));
	WriteInt(fout, ch_times[CHAR_RANGE - 1]);
	fout.close();//关闭文件
}

//得到文件大小
int GetFilesize(const string FileName)
{
	int filzesize = 0;
	ifstream fin;
	fin.open(FileName, ios::in | ios::binary);
	if (!fin.is_open()) {
		cout << "文件打开失败" << endl;
		exit(-1);
	}
	while (!fin.eof()) {//循环读入
		fin.get();
		filzesize++;
	}
	filzesize--;
	fin.close();//关闭文件
	return filzesize;
}


//从文件中读入int
int ReadInt(ifstream& fin)
{
	int ri = 0;
	char ch_int[4];//四个char视为一个int
	fin.read(ch_int, 4);//读取4个字节
	for (int i = 0; i < 4; i++) {
		unsigned int t = unsigned char(ch_int[i]);
		ri = ri | (t << ((3 - i) * 8));
	}
	return ri;
}
//根据压缩文件的开头，得到字符权值
void ReadChTimes(ifstream& fin, int ch_times[CHAR_RANGE])
{
	unsigned char ch = 0;
	int cht = 0;
	while (ch != CHAR_RANGE - 1) {//读取到最后一位结束
		ch = fin.get();
		ch_times[ch] = ReadInt(fin);//对应字符的权值
	}
}

//读入压缩二进制内容
void GetZipContent(const string FileName, string& ZipContent, int ch_times[CHAR_RANGE])
{
	ifstream fin(FileName, ios::in | ios::binary);
	if (!fin.is_open()) {
		cout << "文件打开失败" << endl;
		exit(-1);
	}
	//读取ch_times
	ReadChTimes(fin, ch_times);
	//读取填充位数
	unsigned char pad0 = fin.get();//填充的0的位数

	//读入剩余内容
	char ch = 0;//被读入的字节
	int cnt = 0;//计数器
	while (!fin.eof()) {//循环读入
		ch = fin.get();
		for (int i = 0; i < 8; i++) {//读入8位
			int t = (ch & 0x80); //判断最高位
			if (t)  //1
				ZipContent += "1";
			else //0
				ZipContent += "0";
			ch = ch << 1;//右移1位
		}	
	}
	//消除剩余位数(一个EOF和pad0)
	ZipContent = ZipContent.substr(0, ZipContent.length() - pad0 - 8);

	fin.close();//关闭文件
}