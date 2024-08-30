#include"main.h"
//stl
#include<vector>
#include<queue>
#include<fstream>

//创建哈夫曼树结点
Node* CreateNode(int in_times, unsigned char in_ch = 0)
{
	Node* hnode = new(nothrow) Node(in_ch, in_times);
	if (hnode == NULL)
		return NULL;//动态内存申请失败
	else
		return hnode;//返回地址
}

//释放哈夫曼树空间
void DeleteTree(Node* tnode)
{
	//深度优先遍历
	if (tnode->lc != NULL)
		DeleteTree(tnode->lc);
	if (tnode->rc != NULL)
		DeleteTree(tnode->rc);
	delete tnode;
}

struct cmp {  //自定义比较方式
	bool operator()(Node*& a, Node*& b) {
		return a->times > b->times;
	}
};
//根据字符权值创建哈夫曼树
Node* GetHmTree(int ch_times[CHAR_RANGE])
{
	priority_queue<Node*, vector<Node*>, cmp> NodeHeap;//小顶堆，堆顶为权值最小的结点
	for (int i = 0; i < CHAR_RANGE; i++) {//遍历
		if (ch_times[i] != 0) {
			Node* tmp = CreateNode(ch_times[i], i);
			NodeHeap.push(tmp);//装入堆
		}
	}

	//持续构建，直到只剩下一个根节点
	while (NodeHeap.size() != 1) {
		//提取出头两个结点，权值最小
		Node* n1 = NodeHeap.top();
		NodeHeap.pop();
		Node* n2 = NodeHeap.top();
		NodeHeap.pop();
		//创建一个新结点，权值为其和
		Node* NewNode = CreateNode(n1->times + n2->times);
		//连接左右子树
		NewNode->lc = n1;
		NewNode->rc = n2;
		NodeHeap.push(NewNode);//装入堆
	}
	//返回根节点
	return NodeHeap.top();
}

//遍历二叉树
void GetFromTree(string& TmpCode, string NewCode[CHAR_RANGE], Node* tnode)
{
	//深度优先遍历
	if (tnode->lc != NULL) {
		TmpCode += "0";//左子树编码为0
		GetFromTree(TmpCode, NewCode, tnode->lc);
		TmpCode.pop_back();//除去最后一个字符
	}
	if (tnode->rc != NULL) {
		TmpCode += "1";//右子树编码为1
		GetFromTree(TmpCode, NewCode, tnode->rc);
		TmpCode.pop_back();//除去最后一个字符
	}
	if (tnode->lc == NULL && tnode->rc == NULL) {//叶子结点
		NewCode[tnode->ch] = TmpCode;//确定对应编码值
	}
}
//根据哈夫曼树，得到原文的新内容编码
void GetNewCode(string NewCode[CHAR_RANGE], Node* HmTree)
{
	string TmpCode = "";//临时编码
	GetFromTree(TmpCode, NewCode, HmTree);
}

//根据新编码和哈夫曼树，生成原内容
void WriteOriFile(const string FileName, string &ZipContent, Node* HuffmanTree)
{
	ofstream fout;
	fout.open(FileName, ios::out | ios::binary);
	if (!fout.is_open()) {
		cout << "文件打开失败" << endl;
		exit(-1);
	}

	Node* p = HuffmanTree;//遍历树的指针
	for (int i = 0; i < ZipContent.length(); i++) {
		if (ZipContent[i] == '0') 
			p = p->lc;
		else if (ZipContent[i] == '1') 
			p = p->rc;
		if (p->lc == NULL && p->rc == NULL) {//到了叶子结点
			fout.put(p->ch);//写入对应的字符
			p = HuffmanTree;//回到根节点
		}
	}

	fout.close();
}