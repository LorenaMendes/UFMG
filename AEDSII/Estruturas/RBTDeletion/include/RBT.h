#ifndef _RedBlack_H
#define _RedBlack_H
 
typedef int ElementType;
#define NegInfinity ~0U
 
typedef enum ColorType {
    Red, Black
} ColorType;
 
typedef struct RedBlackNode *RedBlackTree;
 
struct RedBlackNode {
    ElementType Element;
    RedBlackTree Left;
    RedBlackTree Right;
    ColorType Color;
};

/*
 * Free every node in the tree.
 * @param T: the tree that will be freed.
 */
RedBlackTree MakeEmpty(RedBlackTree T);

/*
 * Create a new tree, and returns a pointer to it.
 * @return a pointer to the newly created tree.
 */
RedBlackTree Initialize(void);

/*
 * Inserts a new element into the tree.
 * @param X: the element that will be inserted.
 * @param T: the tree that shall receive this new element.
 * @return a pointer to the new tree that contains X.
 */
RedBlackTree Insert(ElementType X, RedBlackTree T);

/*
 * See if the tree contains a given element.
 * @param X: the element that we are searching for.
 * @param T: the tree that is being searched.
 * @return 1 if X is in T, and 0 otherwise.
 */
int Contains(ElementType X, RedBlackTree T);
 
/*
 * Traverses the tree in central order.
 * @param T: the tree that will be traversed.
 * @param visitor: the function that shall be invoked for every element in
 * the tree.
 */
void Central_RBT_Header(RedBlackTree T, void (*visitor)(RedBlackTree));

/*
 * This function tells if a node is the leaf node used as a sentinel in the
 * Red-Black Tree.
 * @param T: the node that we are querying.
 * @return true if T is the null node.
 */
int isNullNode(RedBlackTree T);
 
#endif
