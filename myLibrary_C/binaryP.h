
#define max 1

struct BST_TYPE {
    int base[max];// base[0] là tần số xuất hiện
    char name[30];
};
typedef struct BST_TYPE typeTree ;
//
struct BST_P{
    typeTree data;
    struct BST_P *left;
    struct BST_P *right;
};
typedef struct BST_P* bst_p;
void outFBST_p ( bst_p root, FILE *p ) {// left - prev - right
    if ( root != NULL ) {

        outFBST_p(root->left,p);
        fprintf(p,"%s\t%d\n", root->data.name, root->data.base[0]);
        outFBST_p(root->right,p);
    }
}
typeTree LeftMostdata(bst_p root ){
    bst_p p = root;
    while ( p->left != NULL )
        p = p->left;
    return p->data;
}
//________________________________________________________________
//________________________________________________________________
bst_p insertBST_p(bst_p root, typeTree data ) {
    if ( root == NULL ) {
        
        root = (bst_p)malloc(sizeof(bst_p)*100);
        
        root->left = NULL;
        root->right = NULL;
        
        // for ( int i = 0; i < max; i++ ){
        //     root->data.base[i] = 0;
        // }

        // strcpy(root->data.name, data.name);
        root->data = data;
        return root;
    }
    // nếu root đã tồn tại
    if ( strcmp(root->data.name, data.name) > 0){
        root->left = insertBST_p(root->left, data);
    } else {
        if ( strcmp(root->data.name, data.name) < 0){
            root->right = insertBST_p(root->right, data);
        } else { // ___________________________________

            return root;
        }
    }
    return root;
}
bst_p searchBST_pName ( bst_p root, char *str ) {// tìm kiếm theo tên
    if ( root == NULL )
        return NULL;
    if( strcmp ( root->data.name, str ) == 0 ) {
        return root;
    } else {

        if ( strcmp(root->data.name, str ) > 0 ) {
            return searchBST_pName( root->left, str );
        }

        else{
            return searchBST_pName( root->right, str );
        }
    }
}
bst_p SearchBST_pData( bst_p root, int x ) {// tìm kiếm theo giá trị

    if ( root == NULL )
        return NULL;
    if ( root->data.base[0] == x ) {
        return root;
    } else {
        SearchBST_pData( root->left, x );
        SearchBST_pData( root->right, x );
    }
}
bst_p DelBST_p ( bst_p root, char *name ){
    
    if ( root == NULL )
        return root;
    
    if ( strcmp ( root->data.name, name ) > 0 )
        root->left = DelBST_p( root->left, name );

    else if ( strcmp ( root->data.name, name ) < 0 )
        root->right = DelBST_p( root->right, name );

    else {
        
        if ( root->left == NULL ) {
            bst_p newRoot = root->right;
            free( root );
            return newRoot;
        }

        if ( root->right == NULL ) {

            bst_p newRoot = root->left;
            free( root );
            return newRoot;
        }
        root->data = LeftMostdata( root->right );
        root->right = DelBST_p( root->right, root->data.name );
    }
    return root;
}
void InOrder_p ( bst_p root ) {// left - prev - right
    if ( root != NULL ) {

        InOrder_p(root->left);
        printf("%s %d\n", root->data.name, root->data.base[0]);
        InOrder_p(root->right);
    }
}
void PreOrder_p ( bst_p root ) {// prev - left - right
    if ( root != NULL ) {
        printf("%s %d\n", root->data.name, root->data.base[0]);
        PreOrder_p(root->left);
        PreOrder_p(root->right);
    }
}
void PostOrder_p ( bst_p root ) {// left - right - prev
    if ( root != NULL ){

        PostOrder_p(root->left);
        PostOrder_p(root->right);
        printf("%s %d\n", root->data.name, root->data.base[0]);
    }
}
int size_p ( bst_p root ) {
    if ( root == NULL ) 
        return 0;
    return 1 + size_p( root->left ) + size_p( root->right );
}
int height_p ( bst_p root ) {
    
    if ( root == NULL ){
        return 0;
    }

    int a = height_p( root->left );
    int b = height_p( root->right );

    if(a > b){
        return a+1;
    }

    return b+1;
}
void outFile_p (bst_p root, char *name ) {
    FILE *f = fopen (name,"w+");
    outFBST_p(root,f);
    fclose(f);
}
void clearBST_p ( bst_p root ){
    if ( root == NULL )
        return;
 
    clearBST_p( root->left );
    clearBST_p( root->right );
    free( root );
}
//___________________________________________________________________