#include<stdlib.h>
struct Node {   
    int data; // giá trị
    struct Node *left;  
    struct Node *right;  
    int depth;  // chiều sâu
};  

typedef struct Node *node;

int max(int a, int b){
    return (a > b)? a : b;
}  
  
int depth(node n) {

    if (n == NULL) 
        return 0; 
    return n->depth;
}  

node newNode(int data) {
    
    node temp;
    temp = (node)malloc(sizeof(node)*100); 
    
    temp->data = data;  
    temp->left = NULL;  
    temp->right = NULL;  
    temp->depth = 1;
    return temp;  
}  

node rightRotate(node y) {// xoay phải

    node x = y->left;  
    node T2 = x->right;  

    x->right = y;  
    y->left = T2;  
 
    y->depth = max( depth(y->left), depth(y->right) ) + 1;  
    x->depth = max( depth(x->left), depth(x->right) ) + 1;  
    
    return x;  
}  
  
node leftRotate(node x) {

    node y = x->right;  
    node T2 = y->left;  

    y->left = x;  
    x->right = T2;  

    x->depth = max( depth(x->left), depth(x->right) ) + 1;  
    y->depth = max( depth(y->left), depth(y->right) ) + 1;  
  
    return y;  
}

int getBalance(node N) {

    if (N == NULL)  
        return 0;  
    return depth(N->left) - depth(N->right);  
}    

node insert(node head, int data)  {  

    if (head == NULL)  
        return newNode(data);  
  
    if (data < head->data)  
        head->left = insert(head->left, data);  
    else if (data > head->data)  
        head->right = insert(head->right, data);  
    else
        return head;
  
    head->depth = 1 + max(depth(head->left),  depth(head->right));  
  
    int balance = getBalance(head);        //get balance factor
  

    if (balance > 1 && data < head->left->data)  
        return rightRotate(head);  
  
    // Right Right Case  
    if (balance < -1 && data > head->right->data)  
        return leftRotate(head);  
  // Left Right Case  
    if (balance > 1 && data > head->left->data)  
    {  
        head->left = leftRotate(head->left);  
        return rightRotate(head);  
    }  
  
    // Right Left Case  
    if (balance < -1 && data < head->right->data)  
    {  
        head->right = rightRotate(head->right);  
        return leftRotate(head);  
    }  
    return head;  
}  
  
// find the node with minimum value 
node minValueNode(node head)  
{  
    node current = head;  
  
    // find the leftmost leaf */
    while (current->left != NULL)  
        current = current->left;  
  
    return current;  
}  
// delete a node from AVL tree with the given data  
node del(node head, int data)  
{  
    if (head == NULL)  
        return head;  
  
    //perform BST delete 
    if ( data < head->data )  
        head->left = del(head->left, data);  
  
    else if( data > head->data )  
        head->right = del(head->right, data);  
  
else
    {  
        // node with only one child or no child  
        if( (head->left == NULL) || 
            (head->right == NULL) )  
        {  
            node temp = head->left ?  head->left : head->right; 
  
            if (temp == NULL)  
            {  
                temp = head;  
                head = NULL;  
            }
            else // One child case  
            head = temp;   
            free(temp);  
        }  
   else
        {  
            node temp = minValueNode(head->right);  
  
            head->data = temp->data;  
  
            // Delete the inorder successor  
            head->right = del(head->right, temp->data);  
        }  
    }  
  
    if (head == NULL)  
    return head;  
  
    // update depth  
    head->depth = 1 + max(depth(head->left),  
                           depth(head->right));  
  
    // get balance factor 
    int balance = getBalance(head);  
  
    //rotate the tree if unbalanced
  
    // Left Left Case  
    if (balance > 1 &&  
        getBalance(head->left) >= 0)  
        return rightRotate(head);  
  
    // Left Right Case  
    if (balance > 1 &&  getBalance(head->left) < 0)  {  
        head->left = leftRotate(head->left);  
        return rightRotate(head);  
    }  
    // Right Right Case  
    if (balance < -1 &&  getBalance(head->right) <= 0)  
        return leftRotate(head);  
  
    // Right Left Case  
    if (balance < -1 && getBalance(head->right) > 0)   {  
        head->right = rightRotate(head->right);  
        return leftRotate(head);  
    }  
    return head;  
}  
// prints inOrder traversal of the AVL tree
void InOrder(node head) {  
    if(head != NULL) {  
        InOrder(head->left);
        printf("%d ",head->data);  
        InOrder(head->right);  
    }  
}

void PreOrder ( node root ) {// prev - left - right
    if ( root != NULL ) {
        printf("%d ", root->data);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

void PostOrder ( node root ) {// left - right - prev
    if ( root != NULL ){

        PostOrder(root->left);
        PostOrder(root->right);
        printf("%d ", root->data);
    }
}

int size ( node root ) {
    if ( root == NULL ) 
        return 0;
    return 1 + size( root->left ) + size( root->right );
}

int height ( node root ) {
    
    if ( root == NULL ){
        return 0;
    }

    int a = height( root->left );
    int b = height( root->right );

    if(a > b){
        return a+1;
    }

    return b+1;
}

void clear ( node root ){
    if ( root == NULL )
        return;
 
    clear( root->left );
    clear( root->right );
    free( root );
}
