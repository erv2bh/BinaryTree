//Main.c
#include"BinaryTree.h"
#include <stdio.h>
#include <stdlib.h>

void Print(BinaryTree* binaryTree);
void Node_Print(BinaryNode* node);
int CompareKeys(void* one, void* other);
int main(int argc, char* argv[]) {
	BinaryTree binaryTree;
	BinaryNode* index;
	Long key;
	Long ret;
	Long(*keys);
	Long i = 0;
	Long count;

	BinaryTree_Create(&binaryTree);

	key = 100;
	index = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);

	BinaryTree_GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\n", ret);



	key = 50;
	index = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);

	BinaryTree_GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	key = 180;
	index = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);

	BinaryTree_GetAt(&binaryTree, index, &ret, sizeof(Long));

	printf("%d\n", ret);

	key = 80;
	index = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);

	BinaryTree_GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	key = 150;
	index = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);

	BinaryTree_GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\n", ret);


	Print(&binaryTree);
	printf("전위수식\n");

	key = 200;
	index = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	BinaryTree_GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	key = 70;
	index = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	BinaryTree_GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	key = 130;
	index = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	BinaryTree_GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	key = 30;
	index = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	BinaryTree_GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	key = 40;
	index = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	BinaryTree_GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	key = 160;
	index = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	BinaryTree_GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\n", ret);



	key = 80;
	index = Search(&binaryTree, &key, sizeof(Long), CompareKeys);
	BinaryTree_GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	key = 150;
	index = Search(&binaryTree, &key, sizeof(Long), CompareKeys);
	BinaryTree_GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	Print(&binaryTree);
	printf("전위수식\n");


	key = 180;
	index = BinaryTree_Delete(&binaryTree, &key, sizeof(Long), CompareKeys);
	if (index == NULL) {
		printf("지워졌습니다\n");
	}

	Print(&binaryTree);
	printf("전위수식\n");

	key = 50;
	index = BinaryTree_Delete(&binaryTree, &key, sizeof(Long), CompareKeys);
	if (index == NULL) {
		printf("지워졌습니다\n");
	}

	Print(&binaryTree);
	printf("전위수식\n");

	key = 100;
	index = BinaryTree_Delete(&binaryTree, &key, sizeof(Long), CompareKeys);
	if (index == NULL) {
		printf("지워졌습니다\n\n");
	}
	
	Print(&binaryTree);
	printf("전위수식\n");

	key = 100;
	index = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	BinaryTree_GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	Print(&binaryTree);
	printf("전위수식\n");

	key = 50;
	index = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	BinaryTree_GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	Print(&binaryTree);
	printf("전위수식\n");

	key = 180;
	index = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	BinaryTree_GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	Print(&binaryTree);
	printf("전위수식\n");


	MakeBalance(&binaryTree,sizeof(Long));
	printf("밸런스 조정 완료\n");

	Print(&binaryTree);
	printf("밸런스 조정후 출력\n");

	BinaryTree_Destroy(&binaryTree);

	return 0;
}
int CompareKeys(void* one, void* other) {
	int ret;
	if (*((Long*)(one)) > *((Long*)(other))) {
		ret = 1;
	}
	else if (*((Long*)(one)) == *((Long*)(other))) {
		ret = 0;
	}
	else if (*((Long*)(one)) < *((Long*)(other))) {
		ret = -1;
	}
	return ret;
}

void Print(BinaryTree* binaryTree) {

	if (binaryTree->root != NULL) {
		Node_Print(binaryTree->root);
	}
}

void Node_Print(BinaryNode* node) {
	if (node != NULL) {
		printf("%d\  ", *((Long*)(node + 1)));
		Node_Print(node->left);
		Node_Print(node->right);
	}
}