#include<iostream>

using namespace std;

struct Node {
	int data;
	struct Node* LChild;
	struct Node* RChild;
};

//创建节点
struct Node* createNode(int insertData) {
	struct Node* pNew = (struct Node*)malloc(sizeof(struct Node));

	while (nullptr == pNew)
	{
		pNew = (struct Node*)malloc(sizeof(struct Node));
	}

	pNew->data = insertData;
	pNew->LChild = nullptr;
	pNew->RChild = nullptr;
	return pNew;
}

//插入节点（按照有序二叉树的方式插入）
void insertNode(struct Node*& root, int insertData) {
	if (nullptr == root) {
		root = createNode(insertData);
		return;
	}
	else if (insertData < root->data) {
		insertNode(root->LChild, insertData);
		return;
	}
	else if (insertData > root->data) {
		insertNode(root->RChild, insertData);
		return;
	}
}

//先序遍历
void preorder(struct Node* root) {
	if (nullptr == root) {
		return;
	}
	//根
	cout << root->data << " ";
	//左
	preorder(root->LChild);
	//右
	preorder(root->RChild);
}

//中序遍历
void inorder(struct Node* root) {
	if (nullptr == root) {
		return;
	}
	//左
	inorder(root->LChild);
	//根
	cout << root->data << " ";
	//右
	inorder(root->RChild);
}

//后序遍历
void postorder(struct Node* root) {
	if (nullptr == root) {
		return;
	}
	//左
	postorder(root->LChild);
	//右
	postorder(root->RChild);
	//根
	cout << root->data << " ";
}

//删除（不包括重复的）
void deleteNode(struct Node*& root, int delData) {
	if (nullptr == root)return;

	//待删节点是根节点
	if (delData == root->data) {
		//如果没有右孩子，左孩子成为新的根节点
		if (nullptr == root->RChild) {
			struct Node* pDel = root;
			root = root->LChild;
			free(pDel);
			pDel = nullptr;
			return;
		}
		else {
			//若有右孩子，右孩子成为新的根节点，左孩子成为新的根节点的最左孩子

			//如果有左孩子的话
			if (nullptr != root->LChild) {
				struct Node* pTemp = root->RChild;
				while (pTemp->LChild)
				{
					pTemp = pTemp->LChild;
				}
				//左孩子成为新的根节点的最左孩子
				pTemp->LChild = root->LChild;
			}

			//右孩子成为新的根节点
			struct Node* pDel = root;
			root = root->RChild;
			free(pDel);
			pDel = nullptr;
			return;
		}
	}

	//删除非根节点
	if (delData < root->data) {
		deleteNode(root->LChild, delData);
	}
	else {
		deleteNode(root->RChild, delData);
	}
}

//查找节点
struct Node* findNode(struct Node* root, int destData) {
	if (nullptr == root)return nullptr;
	while (root) {
		if (destData == root->data)return root;
		if (destData < root->data) {
			root = root->LChild;
		}
		else {
			root = root->RChild;
		}
	}

	return nullptr;
}

//修改节点
void modifyNode(struct Node*& root, int oldData,int newData) {
	if (nullptr == root)return;
	deleteNode(root, oldData);
	insertNode(root, newData);
}

int main() {
	//创建一棵树
	struct Node* tree = nullptr;
	//准备要插入的数据
	int arr[] = { 7,1,9,8,6,5,2,44,38,96,57,66,83 };
	//遍历插入
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		insertNode(tree, arr[i]);
	}

	/*cout << "先序遍历：";
	preorder(tree);
	cout << endl;

	cout << "中序遍历：";
	inorder(tree);
	cout << endl;

	cout << "后序遍历：";
	postorder(tree);
	cout << endl;*/

	cout << "先序遍历：";
	preorder(tree);
	cout << endl;
	int n;
	while (true)
	{
		cout << "请输入要删除的数据：";
		cin >> n;
		deleteNode(tree, n);
		cout << "先序遍历：";
		preorder(tree);
		cout << endl;
	}

	return 0;
}
