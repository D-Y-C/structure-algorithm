#ifndef BITREE_H
#define BITREE_H

#ifndef offsetof
#define offsetof(TYPE, MEMBER)    ((size_t) &((TYPE *)0)->MEMBER)
#endif

#ifndef container_of
#define container_of(ptr, type, member) ({ \
			const typeof( ((type *)0)->member ) *__mptr = (ptr);     \
			(type *)( (char *)__mptr - offsetof(type,member) ); })
#endif



typedef struct bitree_node_t
{
	void *data;
	struct bitree_node_t *left;
	struct bitree_node_t *right;
}BiTreeNode;


typedef struct BiTree_t
{
	int size;
	struct bitree_node_t *root ;
	int (*compare)(const struct bitree_node_t*,const struct bitree_node_t*) ;
}BiTree;

void bitree_init(BiTree* tree,int(*compare)(const BiTreeNode*,const BiTreeNode*));

BiTreeNode* bitree_find(BiTree* tree,BiTreeNode* node);
int bitree_insert(BiTree* tree,BiTreeNode* node);
int bitree_remove(BiTree* tree,BiTreeNode* node);

//int bitree_merge(BiTree* merge,BiTree *left,BiTree* right,const void *data);

BiTreeNode* bitree_get_parent(BiTree* tree,BiTreeNode* node);

#define bitree_size(tree)((tree)->size)
#define bitree_root(tree)((tree)->root)
#define bitree_is_eob(node)((node) == NULL)
#define bitree_is_leaf(node)((node)->left == NULL &&(node)->right == NULL)
#define bitree_data(node)((node)->data)
#define bitree_left(node)((node)->left)
#define bitree_right(node)((node)->right)

#define bitree_is_child_right(parent,child)((parent->right == child))

#endif
