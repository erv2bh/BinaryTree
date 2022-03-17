//BianryTree.c
#include "BinaryTree.h"
#include <stdio.h>
#include <memory.h>

#pragma warning (disable:4996)

void BinaryTree_Create(BinaryTree* binaryTree) {
	binaryTree->root = NULL;
	binaryTree->length = 0;
	binaryTree->balance = 0;
}

BinaryNode* Insert(BinaryTree* binaryTree, void* key, size_t size, int(*compare)(void*, void*)) {
	BinaryNode* index;
	BinaryNode* it;
	BinaryNode* parent = NULL;

	index = (BinaryNode*)malloc(sizeof(BinaryNode)*size);
	memcpy(index + 1, key, size);
	index->left = NULL;
	index->right = NULL;
	it = binaryTree->root;
	while (it != NULL) {
		parent = it;
		if (compare(it + 1, key) > 0) {
			it = it->left;
		}
		else {
			it = it->right;
		}
	}
	if (parent != NULL) {
		if (compare(parent + 1, key) > 0) {
			parent->left = index;
		}
		else {
			parent->right = index;
		}
		if (compare(binaryTree->root + 1, key) > 0) {
			binaryTree->balance--;
		}
		else {
			binaryTree->balance++;
		}
	}
	else {
		binaryTree->root = index;
	}
	binaryTree->length++;
	return index;
}

void BinaryTree_Destroy(BinaryTree* binaryTree) {
	Node_Destroy(binaryTree->root);
}

void Node_Destroy(BinaryNode* node) {
	if (node != NULL) {
		Node_Destroy(node->left);
		Node_Destroy(node->right);
		if (node != NULL) {
			free(node);
			node = NULL;
		}
	}
}

void BinaryTree_GetAt(BinaryTree* binaryTree, BinaryNode* index, void* key, size_t size) {
	memcpy(key, index + 1, size);
}

BinaryNode* BinaryTree_Delete(BinaryTree* binaryTree, void* key, size_t size, int(*compare)(void*, void*)) {
	BinaryNode* index;
	BinaryNode* indexParent = NULL;
	BinaryNode* it = NULL;
	BinaryNode* itParent = NULL;
	void* balance;
	balance = malloc(size);
	memcpy(balance, binaryTree->root + 1, size);
	index = binaryTree->root;
	while (index != NULL && compare(index + 1, key) != 0) {
		indexParent = index;
		if (compare(index + 1, key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	itParent = index;
	it = index->right;
	while (it != NULL && it->left != NULL) {
		itParent = it;
		it = it->left;
	}
	if (it == NULL) {
		it = index->left;
	}
	while (it != NULL && compare(it + 1, key) < 0) {
		itParent = it;
		it = it->right;
	}
	if (index == itParent && compare(it + 1, key) > 0) {
		it->left = index->left;
	}
	if (index!=itParent&&compare(it+1,key)>0){
		it->left = index->left;
	}
	
	if (index != itParent && it != NULL) {
		if (compare(it + 1, key) < 0) {
			itParent->right = it->left;
			it->left = index->left;
		}
		else {
			itParent->left = it->right;
			it->right = index->right;
		}
	}
	if (index != binaryTree->root) {
		if (indexParent->right != index) {
			indexParent->left = it;
		}
		else {
			indexParent->right = it;
		}
	}
	else {
		binaryTree->root = it;
	}
	if (index != NULL) {
		free(index);
		index = NULL;
	}
	if (compare(balance, key) != 0) {
		if (compare(balance, key) > 0) {
			binaryTree->balance++;
		}
		else {
			binaryTree->balance--;
		}
	}
	binaryTree->length--;
	if (balance != NULL) {
		free(balance);
		balance = NULL;
	}
	return index;
}

BinaryNode* Search(BinaryTree* binaryTree, void* key, size_t size, int(*compare)(void*, void*)) {
	BinaryNode* index;
	index = binaryTree->root;
	while (index != NULL && compare(index + 1, key) != 0) {
		if (compare(index + 1, key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	return index;
}
	

void MakeKeys(BinaryTree* binaryTree, void* (*keys), Long* count, size_t size) {
	Long index = 0;
	*count = 0;
	*keys = calloc(binaryTree->length, size);
	Node_MakeKeys(binaryTree->root, *keys, count, &index, size);
}

void Node_MakeKeys(BinaryNode* node, void(*keys), Long* count, Long* index, size_t size) {
	if (node != NULL) {
		Node_MakeKeys(node->left, keys, count, index, size);
		memcpy(((char*)keys) + ((*index) * size), node + 1, size);
		(*count)++;
		(*index)++;
		Node_MakeKeys(node->right, keys, count, index, size);
	}
}

void MakeBalance(BinaryTree* binaryTree, size_t size) {
	void(*keys);
	Long count;
	MakeKeys(binaryTree, &keys, &count, size);
	DeleteAllItems(binaryTree);
	MakeTree(binaryTree, keys, count, size);
	if (keys != NULL) {
		free(keys);
		keys = NULL;
	}
}

void DeleteAllItems(BinaryTree* binaryTree) {
	Node_DeleteAllItems(binaryTree->root);
	binaryTree->root = NULL;
	binaryTree->length = 0;
	binaryTree->balance = 0;
}

void Node_DeleteAllItems(BinaryNode* node) {
	if (node != NULL) {
		Node_DeleteAllItems(node->left);
		Node_DeleteAllItems(node->right);
		if (node != NULL) {
			free(node);
			node = NULL;
		}
	}
}

void MakeTree(BinaryTree* binaryTree, void(*keys), Long count, size_t size) {
	Long remainder;
	binaryTree->root = Node_MakeTree(keys, 0, count - 1, size);
	binaryTree->length = count;
	remainder = count % 2;
	if (remainder != 0) {
		binaryTree->balance = 1;
	}
	else {
		binaryTree->balance = 0;
	}
}

BinaryNode* Node_MakeTree(void(*keys), Long low, Long high, size_t size) {
	BinaryNode* node=NULL;
	Long middle;
	if (low <= high) {
		middle = (low + high) / 2;
		node = (BinaryNode*)malloc(sizeof(BinaryNode) * size);
		memcpy(node + 1, ((char*)keys) + (middle * size), size);
		node->left = Node_MakeTree(keys, low, middle - 1, size);
		node->right = Node_MakeTree(keys, middle + 1, high, size);
	}
	else {
		if (node != NULL) {
			free(node);
			node = NULL;
		}
	}
	return node;
}
