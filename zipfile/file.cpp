#include"main.h"
#include<fstream>
#include<math.h>

//��ȡԭ�ļ����õ��ַ�Ȩֵ
void ReadFileChar(const string FileName, int ch_times[CHAR_RANGE])
{
	ifstream fin;
	fin.open(FileName, ios::in | ios::binary);
	if (!fin.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		exit(-1);
	}
	unsigned char ch;//ÿ�ζ�����ַ�
	while (!fin.eof()) {//ѭ������
		ch = fin.get();
		ch_times[ch]++;//��Ӧ�ַ����ִ���+1
	}
	ch_times[CHAR_RANGE - 1]--;//ȡ���������һ��EOF
	fin.close();//�ر��ļ�
}

//����ԭ�ļ����õ��µĶ����Ʊ����ַ���
void GetNewContent(string& NewContent, const string FileName, string NewCode[CHAR_RANGE])
{
	ifstream fin;
	fin.open(FileName, ios::in | ios::binary);
	if (!fin.is_open()) {
		cout << "�ļ���ʧ��" << endl;
	}
	unsigned char ch;//ÿ�ζ�����ַ�
	while (!fin.eof()) {//ѭ������
		ch = fin.get();
		NewContent += NewCode[ch];
	}
	fin.close();//�ر��ļ�
}

//д��ѹ���ļ�
void WriteZipFile(const string FileName, string& NewContent)
{
	ofstream fout;
	fout.open(FileName, ios::out| ios::binary|ios::app);
	if (!fout.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		exit(-1);
	}
    //
	unsigned char pad0 = (8 - NewContent.length() % 8) % 8;//����0��λ��
	fout.put(pad0);//д�����λ��

	//д��ʣ������
	char ch = 0;//������д����ֽ�
	int cnt = 0;//������
	for (int i = 0; i < NewContent.length(); i++) {//��λд��
		cnt++;//����ǰ��λ��
		if (NewContent[i] == '0') {
			ch = ch << 1;//����1λ
		}
		else if (NewContent[i] == '1') {
			ch = ch << 1;//����1λ
			ch = ch | 1;//��ch���һλΪ1
		}
		if (cnt == 8) {//��8λ��д��
			fout.put(ch);
			ch = 0;//����
			cnt = 0;
		}
	}
	//���ʣ��λ��
	if (pad0 != 0) {//ch�ĺ�pad0λ����Ҫд���
		ch = (ch << pad0);
		fout.put(ch);
	}

	fout.close();//�ر��ļ�
}

//��int��д���ļ�
void WriteInt(ofstream &fout, int wi)
{
	for (int i = 0; i < 4; i++) {
		char ch = 0;//��д����ַ�
		for (int j = 0; j < 8; j++) {
			ch = ch << 1;
			if (wi & 0x80000000) //�����λΪ1
				ch = ch | 1;	
			wi = wi << 1;
		}
		fout.put(ch);
	}
}

//д��ԭ�ļ��ַ�Ȩֵ
void WriteChTimes(const string FileName, int ch_times[CHAR_RANGE])
{
	ofstream fout(FileName, ios::out|ios::binary);
	if (!fout.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		exit(-1);
	}
	for (int i = 0; i < CHAR_RANGE - 1; i++) {
		if (ch_times[i] != 0) {
			fout.put(i);
			WriteInt(fout, ch_times[i]);
		}
	}
	//д�����CHAR_RANGE��ch_times��Ϊ������־
	fout.put(unsigned char(CHAR_RANGE - 1));
	WriteInt(fout, ch_times[CHAR_RANGE - 1]);
	fout.close();//�ر��ļ�
}

//�õ��ļ���С
int GetFilesize(const string FileName)
{
	int filzesize = 0;
	ifstream fin;
	fin.open(FileName, ios::in | ios::binary);
	if (!fin.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		exit(-1);
	}
	while (!fin.eof()) {//ѭ������
		fin.get();
		filzesize++;
	}
	filzesize--;
	fin.close();//�ر��ļ�
	return filzesize;
}


//���ļ��ж���int
int ReadInt(ifstream& fin)
{
	int ri = 0;
	char ch_int[4];//�ĸ�char��Ϊһ��int
	fin.read(ch_int, 4);//��ȡ4���ֽ�
	for (int i = 0; i < 4; i++) {
		unsigned int t = unsigned char(ch_int[i]);
		ri = ri | (t << ((3 - i) * 8));
	}
	return ri;
}
//����ѹ���ļ��Ŀ�ͷ���õ��ַ�Ȩֵ
void ReadChTimes(ifstream& fin, int ch_times[CHAR_RANGE])
{
	unsigned char ch = 0;
	int cht = 0;
	while (ch != CHAR_RANGE - 1) {//��ȡ�����һλ����
		ch = fin.get();
		ch_times[ch] = ReadInt(fin);//��Ӧ�ַ���Ȩֵ
	}
}

//����ѹ������������
void GetZipContent(const string FileName, string& ZipContent, int ch_times[CHAR_RANGE])
{
	ifstream fin(FileName, ios::in | ios::binary);
	if (!fin.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		exit(-1);
	}
	//��ȡch_times
	ReadChTimes(fin, ch_times);
	//��ȡ���λ��
	unsigned char pad0 = fin.get();//����0��λ��

	//����ʣ������
	char ch = 0;//��������ֽ�
	int cnt = 0;//������
	while (!fin.eof()) {//ѭ������
		ch = fin.get();
		for (int i = 0; i < 8; i++) {//����8λ
			int t = (ch & 0x80); //�ж����λ
			if (t)  //1
				ZipContent += "1";
			else //0
				ZipContent += "0";
			ch = ch << 1;//����1λ
		}	
	}
	//����ʣ��λ��(һ��EOF��pad0)
	ZipContent = ZipContent.substr(0, ZipContent.length() - pad0 - 8);

	fin.close();//�ر��ļ�
}