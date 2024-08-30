#include"main.h"
//stl
#include<vector>
#include<queue>
#include<fstream>

//���������������
Node* CreateNode(int in_times, unsigned char in_ch = 0)
{
	Node* hnode = new(nothrow) Node(in_ch, in_times);
	if (hnode == NULL)
		return NULL;//��̬�ڴ�����ʧ��
	else
		return hnode;//���ص�ַ
}

//�ͷŹ��������ռ�
void DeleteTree(Node* tnode)
{
	//������ȱ���
	if (tnode->lc != NULL)
		DeleteTree(tnode->lc);
	if (tnode->rc != NULL)
		DeleteTree(tnode->rc);
	delete tnode;
}

struct cmp {  //�Զ���ȽϷ�ʽ
	bool operator()(Node*& a, Node*& b) {
		return a->times > b->times;
	}
};
//�����ַ�Ȩֵ������������
Node* GetHmTree(int ch_times[CHAR_RANGE])
{
	priority_queue<Node*, vector<Node*>, cmp> NodeHeap;//С���ѣ��Ѷ�ΪȨֵ��С�Ľ��
	for (int i = 0; i < CHAR_RANGE; i++) {//����
		if (ch_times[i] != 0) {
			Node* tmp = CreateNode(ch_times[i], i);
			NodeHeap.push(tmp);//װ���
		}
	}

	//����������ֱ��ֻʣ��һ�����ڵ�
	while (NodeHeap.size() != 1) {
		//��ȡ��ͷ������㣬Ȩֵ��С
		Node* n1 = NodeHeap.top();
		NodeHeap.pop();
		Node* n2 = NodeHeap.top();
		NodeHeap.pop();
		//����һ���½�㣬ȨֵΪ���
		Node* NewNode = CreateNode(n1->times + n2->times);
		//������������
		NewNode->lc = n1;
		NewNode->rc = n2;
		NodeHeap.push(NewNode);//װ���
	}
	//���ظ��ڵ�
	return NodeHeap.top();
}

//����������
void GetFromTree(string& TmpCode, string NewCode[CHAR_RANGE], Node* tnode)
{
	//������ȱ���
	if (tnode->lc != NULL) {
		TmpCode += "0";//����������Ϊ0
		GetFromTree(TmpCode, NewCode, tnode->lc);
		TmpCode.pop_back();//��ȥ���һ���ַ�
	}
	if (tnode->rc != NULL) {
		TmpCode += "1";//����������Ϊ1
		GetFromTree(TmpCode, NewCode, tnode->rc);
		TmpCode.pop_back();//��ȥ���һ���ַ�
	}
	if (tnode->lc == NULL && tnode->rc == NULL) {//Ҷ�ӽ��
		NewCode[tnode->ch] = TmpCode;//ȷ����Ӧ����ֵ
	}
}
//���ݹ����������õ�ԭ�ĵ������ݱ���
void GetNewCode(string NewCode[CHAR_RANGE], Node* HmTree)
{
	string TmpCode = "";//��ʱ����
	GetFromTree(TmpCode, NewCode, HmTree);
}

//�����±���͹�������������ԭ����
void WriteOriFile(const string FileName, string &ZipContent, Node* HuffmanTree)
{
	ofstream fout;
	fout.open(FileName, ios::out | ios::binary);
	if (!fout.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		exit(-1);
	}

	Node* p = HuffmanTree;//��������ָ��
	for (int i = 0; i < ZipContent.length(); i++) {
		if (ZipContent[i] == '0') 
			p = p->lc;
		else if (ZipContent[i] == '1') 
			p = p->rc;
		if (p->lc == NULL && p->rc == NULL) {//����Ҷ�ӽ��
			fout.put(p->ch);//д���Ӧ���ַ�
			p = HuffmanTree;//�ص����ڵ�
		}
	}

	fout.close();
}