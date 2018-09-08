#include <stdlib.h>
#include <assert.h>
#include "bitree.h"


void bitree_init(BiTree* tree,int(*compare)(const BiTreeNode*,const BiTreeNode*))
{
	assert(compare != NULL && tree != NULL);

	tree->size = 0;
	tree->root = NULL;
	tree->compare = compare;
}

void bitree_destory(BiTree* tree)
{
	
}

BiTreeNode* bitree_find(BiTree* tree,BiTreeNode* node)
{
	if(bitree_root(tree) == NULL || node == NULL)
		return NULL;

	BiTreeNode* next_node = tree->root;
	while(1){
		int retval = tree->compare(next_node,node);
		if(retval == 0)
			return next_node; 
		else if(retval > 0)
			next_node = bitree_left(next_node);
		else 
			next_node = bitree_right(next_node);

		if(next_node == NULL)
			break;
	}	
	return NULL;
}

int bitree_insert(BiTree* tree,BiTreeNode* node)
{
	assert(tree->compare != NULL);

	BiTreeNode* next_node = NULL;

	if(tree->root == NULL){
		tree->root = node;
		tree->size = 1;
		return 0;
	}
	
	next_node = bitree_root(tree);	
	while(1)
	{
		if(tree->compare(next_node,node) <= 0){
			if(bitree_right(next_node) == NULL){
				bitree_right(next_node) = node;
				break;
			}
			next_node = bitree_right(next_node);
		}else{
			if(bitree_left(next_node) == NULL){
				bitree_left(next_node) = node;
				break;
			}
			next_node = bitree_left(next_node);
		}
	}	
	tree->size++;
	return 0;
}

static BiTreeNode* bitree_get_leftmost(BiTreeNode* node)
{
	BiTreeNode* next_node = node;

	if(next_node == NULL)
		return next_node;

	while(next_node->left != NULL)
		next_node = next_node->left;
	return next_node;
}

int bitree_remove(BiTree* tree,BiTreeNode* node)
{
	BiTreeNode *parent_node = bitree_get_parent(tree,node);

	// root node

	if(node->right == NULL && node->left == NULL){
		if(parent_node == NULL){
			bitree_root(tree) = NULL;	
		}else{
			if(bitree_is_child_right(parent_node,node))
				parent_node->right = NULL;
			else 
				parent_node->left = NULL;
		}
	}else if(node->right == NULL && node->left != NULL){
		if(parent_node == NULL){
			bitree_root(tree) = node->left;	
		}else{
			if(bitree_is_child_right(parent_node,node))
				parent_node->right = node->left;
			else 
				parent_node->left = node->left;
		}
	}else if(node->right != NULL && node->left == NULL){
		if(parent_node == NULL){
			bitree_root(tree) = node->right;	
		}else{
			if(bitree_is_child_right(parent_node,node))
				parent_node->right = node->right;
			else 
				parent_node->left = node->right;
		}
	}else{
			BiTreeNode* left_most_node = bitree_get_leftmost(node->right);
			left_most_node->left = node->left;

			if(parent_node == NULL){
				bitree_root(tree) = bitree_root(tree)->right;
			}else{
				if(bitree_is_child_right(parent_node,node))
					parent_node->right = node->right;
				else
					parent_node->left = node->right;
			}
	}
	tree->size--;	
}


BiTreeNode* bitree_get_parent(BiTree* tree,BiTreeNode* node)
{
	assert(tree != NULL && node != NULL);

	if(bitree_root(tree) == NULL || node == NULL)
		return NULL;

	BiTreeNode* next_node = tree->root;
	BiTreeNode* pre_node = NULL;
	while(1){
		int retval = tree->compare(next_node,node);
		if(retval == 0)
			return pre_node; 
		else if(retval > 0){
			pre_node = next_node;
			next_node = bitree_left(next_node);
		}else{ 
			pre_node = next_node;
			next_node = bitree_right(next_node);
		}

		if(next_node == NULL)
			break;
	}	
	return pre_node;
}

int bitree_merge(BiTree* merge,BiTree *left,BiTree* right,const void *data)
{
	return 0;
}

