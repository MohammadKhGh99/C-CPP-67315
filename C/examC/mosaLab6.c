//#include <stdlib.h>
//#include <stdio.h>
//// typedef of pointer to function that returns nothing (void) and gets a single void* argument.
//// the name of the typedef is FreeFunc
//// A function of this type can be called on node->data to free it
//typedef void(* FreeFunc) (void*);
//
//// typedef of pointer to function that returns an int and gets 2 void* arguments.
//// the name of the typedef is CompareFunc
//// A function of this type can be called with node1->data,node2->data to compare between them,
//// returning a negative int if the first argument is smaller than the second, a positive int
//// if the first argument is larger than the second and 0 if they are equal.
//typedef int(*CompareFunc) (void*, void*);
//// generic Node struct definition - nodes of a BST
//typedef struct Node{
//	struct Node* parent;
//	struct Node* left;
//	struct Node* right;
//	void* data;
//} Node;
//
//// generic BST struct definition
//typedef struct BST{
//	Node* root;
//	FreeFunc freeFunc;
//	CompareFunc compareFunc;
//} BST;
//// this function creates a new node with the given data
//Node* newNode(void* data){
//	Node* node = (Node*)calloc(1,sizeof(Node));
//	if (!node){
//		return NULL;
//	}
//	node->data=data;
//	return node;
//}
//// this function creates a new BST with the given functions
//BST* newBST(FreeFunc freeFunc,CompareFunc compareFunc){
//	BST* tree = (BST*)malloc(sizeof(BST));
//	if (!tree){
//		return NULL;
//	}
//	tree->root = NULL;
//	tree->freeFunc = freeFunc;
//	tree->compareFunc = compareFunc;
//	return tree;
//}
//
//int addToBST(BST* tree,Node* node); // add a node to the tree. If it is there, or pointer invalid - return 0. else,
//// add the node and return 1
//Node* findInBST(BST* tree, void* data); // find a node in the tree. return the node if found, NULL if error or not found
//void freeBST(BST** ppTree); // free the tree, nodes and data within the nodes
//Node * findHelper(Node * root, void * data , CompareFunc compareFunc);
//int addHelper(BST** tree,Node* root, Node *node, Node* parent, CompareFunc compareFunc, int d);
//void freeHelper(Node * root, FreeFunc freeFunc);
//void freeBST(BST ** ppTree)
//{
//	freeHelper((*ppTree)->root,(*ppTree)->freeFunc);
//}
//void freeHelper(Node* root, FreeFunc freeFunc)
//{
//	if(root == NULL)
//	{
//		return;
//	}
//	freeHelper(root->left, freeFunc);
//	freeHelper(root->right, freeFunc);
//	freeFunc(root->data);
//	free(root);
//}
//Node * findHelper(Node* root , void * data, CompareFunc compareFunc)
//{
//	if(root == NULL)
//	{
//		return NULL;
//	}
//	if(compareFunc(root->data, data) == 0)
//	{
//		return root;
//	}
//	else if (compareFunc(root->data, data)>0)
//	{
//		return findHelper(root->left, data, compareFunc);
//	}
//	else
//	{
//		return findHelper(root->right, data, compareFunc);
//	}
//}
//Node * findInBST(BST* tree, void*data)
//{
//	if(data == NULL)
//	{
//		return NULL;
//	}
//	return findHelper(tree->root, data, tree->compareFunc);
//}
//
//int addToBST(BST* tree, Node *node)
//{
//	if(node == NULL)
//	{
//		return 0;
//	}
//	return addHelper(&tree,tree->root, node, tree->root, tree->compareFunc,0);
//}
//
//int addHelper(BST** tree,Node* root, Node *node,Node* parent, CompareFunc compareFunc, int d)
//{
//	if((*tree)->root == NULL)
//	{
//		(*tree)->root=(Node*)malloc(sizeof(struct Node));
//		if ((*tree)->root==NULL)
//		{
//			return 0;
//		}
//		(*tree)->root->data = node->data;
//		return 1;
//	}
//	if (root==NULL)
//	{
//		root=(Node*)malloc(sizeof(struct Node));
//		if (root==NULL)
//		{
//			return 0;
//		}
//		root->data = node->data;
//		root->parent=parent;
//		if (d)
//		{
//			parent->right=root;
//		}
//		else
//		{
//			parent->left=root;
//		}
//		return 1;
//	}
//	if(compareFunc(root->data,node->data) > 0)
//	{
//		return addHelper(tree,root->left, node, root, compareFunc,0);
//	}
//	else if(compareFunc(root->data, node->data) < 0)
//	{
//		return addHelper(tree,root->right, node, root, compareFunc,1);
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//
//
//
//
//int compareInts(void* a, void* b){
//	int *intA=(int*)a,*intB=(int*)b;
//	return (*intA)-(*intB);
//}
//void simpleFree(void* a){
//	free(a);
//}
//
//int main()
//{
//	BST *tree = newBST(simpleFree, compareInts);
//	int *a, *b, *c, *d;
//	a = (int *) malloc(sizeof(int));
//	b = (int *) malloc(sizeof(int));
//	c = (int *) malloc(sizeof(int));
//	d = (int *) malloc(sizeof(int));
//	*a = (*b = (*c = (*d = 1) + 1) + 1) + 1;
//	printf("%d\n", addToBST(tree, newNode(b)));
//	printf("%d\n", addToBST(tree, newNode(c)));
//	printf("%d\n", addToBST(tree, newNode(a)));
//	printf("%d\n", addToBST(tree, newNode(d)));
//	printf("%d\n", addToBST(tree, newNode(b)));
//	printf("%d\n", findInBST(tree, d) != NULL);
//	freeBST(&tree);
//	free(tree);
//}
//
//
//
//
//
//
//
//
//
//
//
