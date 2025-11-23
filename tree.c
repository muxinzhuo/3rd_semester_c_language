// DCDCB ACCBD CCABC
//6.1
int Isomorphic( Tree T1, Tree T2 ) {
    if ( !T1 && !T2 )
        return 1;
    if ( (!T1 && T2) || (T1 && !T2) )
        return 0;
    if ( T1->Element != T2->Element )
        return 0;
    if ( !T1->Left && !T2->Left )
        return Isomorphic( T1->Right, T2->Right );
    if ( (T1->Left && T2->Left) && (T1->Left->Element == T2->Left->Element) )
        return Isomorphic( T1->Left, T2->Left ) && Isomorphic( T1->Right, T2->Right );
    return Isomorphic( T1->Left, T2->Right ) && Isomorphic( T1->Right, T2->Left );
}

//6.2
Tree BuildTree(int inorder[], int postorder[], int N)
{
    if (!N)
    {
        return NULL;
    }

    Tree T = (Tree)malloc(sizeof(struct TreeNode));
    T->Element = postorder[N - 1];
    T->Left = T->Right = NULL;

    int i;
    for (i = 0; i < N; i++)
    {
        if (inorder[i] == T->Element)
        {
            break;
        }
    }

    int LeftSize = i;
    int RightSize = N - LeftSize - 1;

    T->Left = BuildTree(inorder, postorder, LeftSize);
    T->Right = BuildTree(inorder + LeftSize + 1, postorder + LeftSize, RightSize);

    return T;
}

//6.3
#include <stdlib.h>

typedef struct TreeNode *Tree;
struct TreeNode {
    int Element;
    Tree Left;
    Tree Right;
};

Tree Insert(Tree T, int val) {
    if (!T) {
        T = (Tree)malloc(sizeof(struct TreeNode));
        T->Element = val;
        T->Left = T->Right = NULL;
    } else {
        if (val > T->Element) 
            T->Left = Insert(T->Left, val);
        else 
            T->Right = Insert(T->Right, val);
    }
    return T;
}

void GetPostOrder(Tree T, int A[], int *index) {
    if (!T) return;
    GetPostOrder(T->Left, A, index);
    GetPostOrder(T->Right, A, index);
    A[(*index)++] = T->Element;
}

int IsCBST( int A[], int N ) {
    Tree root = NULL;
    int i;
    for (i = 0; i < N; i++) {
        root = Insert(root, A[i]);
    }

    int isComplete = 1;
    int flag = 0;
    
    Tree *queue = (Tree *)malloc(sizeof(Tree) * (N + 1));
    int front = 0, rear = 0;
    
    if (root) queue[rear++] = root;
    
    while (front < rear) {
        Tree current = queue[front++];
        
        if (current->Left) {
            if (flag) isComplete = 0;
            queue[rear++] = current->Left;
        } else {
            flag = 1;
        }
        
        if (current->Right) {
            if (flag) isComplete = 0;
            queue[rear++] = current->Right;
        } else {
            flag = 1;
        }
        
        if (!isComplete) break;
    }
    free(queue);
    
    int idx = 0;
    GetPostOrder(root, A, &idx);
    
    return isComplete;
}