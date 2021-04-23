

typedef struct BST {
    int data;
    struct BST* left;
    struct BST* right;
} *bst;
//
int LeftOf ( int value, bst root ) {
    return value < root->data;
}
int RightOf ( int value, bst root ) {
    return value > root->data;
}
int LeftMostValue ( bst root ) {

    while ( root->left != NULL )
        root = root->left;
    return root->data;
}
void outF ( bst root, FILE *p ) {
    if ( root != NULL ) {

        outF(root->left,p);
        fprintf( p,"%d\n", root->data );
        outF(root->right,p);
    }
}
//___________________________________________
void clearBST ( bst root ) {
    if ( root == NULL )
        return;
 
    clearBST( root->left );
    clearBST( root->right );
    free( root );
}
bst insertBST ( bst root, int value ) {
    if ( root == NULL ) {

        root = (bst)malloc( sizeof( bst ) );
        root->left = NULL;
        root->right = NULL;
        root->data = value;
        return root;
    }

    if ( LeftOf( value, root ) )
        root->left = insertBST( root->left, value );
    else if ( RightOf( value, root ) )
        root->right = insertBST( root->right, value );
    return root;
}
bst DelBST ( bst root, int value ) {
    if ( root == NULL )
        return root;
    if ( LeftOf( value, root ) )
        root->left = DelBST( root->left, value );
    else if ( RightOf( value, root ) )
        root->right = DelBST( root->right, value );
    else {
        // root->data == value, delete this bst
        if ( root->left == NULL ) {
            bst newRoot = root->right;
            free( root );
            return newRoot;
        }
        if ( root->right == NULL ) {
            bst newRoot = root->left;
            free( root );
            return newRoot;
        }

        root->data = LeftMostValue( root->right );
        root->right = DelBST( root->right, root->data );
    }
    return root;
}
void PreOrder ( bst root ){
    if(root != NULL) {

        printf("%d ", root->data);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}
void InOrder ( bst root ) {
    if(root != NULL) {

        InOrder(root->left);
        printf("%d ", root->data);
        InOrder(root->right);
    }
}
void PostOrder ( bst root ) {
    if(root != NULL) {

        PostOrder(root->left);
        PostOrder(root->right);
        printf("%d ", root->data);
    }
}
int size ( bst root ) {
    if ( root == NULL ) 
        return 0;
    return 1 + size( root->left ) + size( root->right );
}
int height ( bst root ) {
    
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
void outFile ( bst root, char *name ) {
    FILE *f = fopen (name,"w+");
    outF(root,f);
    fclose(f);
}
//____________________________________________