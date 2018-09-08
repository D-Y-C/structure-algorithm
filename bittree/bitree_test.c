#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bitree.h"

typedef struct BitreeTest_t
{
	BiTreeNode bitree_node;
	int data;
}BitreeTest;

int bitree_compare(const BiTreeNode* node1,const BiTreeNode* node2)
{
	BitreeTest* test1 = container_of(node1,struct BitreeTest_t,bitree_node);
	BitreeTest* test2 = container_of(node2,struct BitreeTest_t,bitree_node);
	
	if(test1->data > test2->data)
		return 1;
	else if(test1->data == test2->data)
		return 0;
	else 
		return -1;
}

void dfs_show_node(BiTreeNode *node,int spaces)
{
	int loop ;

	if(node == NULL)
		return ;

	dfs_show_node(node->right,spaces + 4);
	
	for(loop = 1; loop <= spaces; loop++){
		printf(" ");
	}
	struct BitreeTest_t* test = container_of(node,struct BitreeTest_t,bitree_node);

	printf("%d\n",test->data);	
	
	dfs_show_node(node->left,spaces+4);
	
	node = NULL;


}

void show_tree(BiTree *tree)
{
	dfs_show_node(tree->root,0);	
	printf("\ntree size : %d\n",tree->size);
}


int main()
{	
	BiTree tree;
	BitreeTest node_table[50];
	int node_cnt = 0;
	memset((void*)node_table,0,sizeof(node_table));

	printf("Wlecome to Bit Tree test\n");

	node_table[node_cnt++].data = 20;
	node_table[node_cnt++].data = 10;
	node_table[node_cnt++].data = 50;
	node_table[node_cnt++].data = 25;
	node_table[node_cnt++].data = 65;
	node_table[node_cnt++].data = 2;
	node_table[node_cnt++].data = 43;
	
	bitree_init(&tree,bitree_compare);	

	printf("<-- Insert Bit Tree test -->\n");

	int i = 0 ;
	for(i = 0 ; i < node_cnt ; i++)
		bitree_insert(&tree,&node_table[i].bitree_node);

	show_tree(&tree);
	printf("---------------------\n");

	printf("<-- find bit tree test -->\n");

	for(i = 0 ; i < node_cnt; i++){
		BiTreeNode* node = bitree_find(&tree,&node_table[i].bitree_node);
		if(node != NULL)
			printf("find data %d ok\n",node_table[i].data);
		else
			printf("find data %d faild\n",node_table[i].data);	
	}

	printf("---------------------\n");

	printf("<-- get parent bit tree node test -->\n");

	for(i = 0 ; i < node_cnt; i++){
		BiTreeNode* node = bitree_get_parent(&tree,&node_table[i].bitree_node);
		if(node != NULL){
			BitreeTest* parent_node = container_of(node,struct BitreeTest_t,bitree_node);	
			printf("find parent %d-%d ok\n",parent_node->data,node_table[i].data);
		}
		else
			printf("this is root node, %d \n",node_table[i].data);	
	}
	printf("---------------------\n");
	
	printf("<-- remove bit tree node test -->\n");
	show_tree(&tree);	
	printf("\n\n");
	
	bitree_remove(&tree,&node_table[0].bitree_node);

	bitree_remove(&tree,&node_table[3].bitree_node);


	show_tree(&tree);
	printf("---------------------\n");
/*
	for(i = 10; i < 20; i++){
		bitree_ins_right(&tree,&node_table[i].bitree_node);
	}

	show_tree(&tree);
	*/
	return 0;
}
