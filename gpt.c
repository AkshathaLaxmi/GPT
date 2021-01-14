#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
        char key[1025];
        struct node* left;
        struct node* right;
};
typedef struct node node_t;

struct tree {
        node_t* root;
};
typedef struct tree tree_t;

void init_tree(tree_t *ptr_tree) {
        ptr_tree -> root = NULL;
}

node_t *find_node(node_t *node, char parent[1025]) {
        if(node == NULL)
                return node;
        if(strcmp(node->key, parent) == 0)
                return node;
        if(find_node(node->left, parent) != NULL)
                return find_node(node->left, parent);
        if(find_node(node->right, parent) != NULL)
                return find_node(node->right, parent);
        return NULL;
}

void add_node(tree_t *ptr_tree, char parent[1025], char key[1025]) {
        node_t* temp = (node_t*)malloc(sizeof(node_t));
        node_t* parent_node;
        // cannot insert another root node if a root node already exists
        if(ptr_tree->root!=NULL && strcmp(key, " ")==0)
                return;
        // key for a root node
        else if(ptr_tree->root==NULL && strcmp(key, " ")==0)
                strcpy(temp->key, parent);
        // key for a non-root node.
        else
                strcpy(temp->key, key);
        temp->left = NULL; temp->right = NULL; 

        // inserting root node.
        if(ptr_tree->root==NULL)
                ptr_tree->root = temp;
        // inserting non-root node
        else {
                // finding the position to insert the new node.
                parent_node = find_node(ptr_tree->root, parent);
                if(parent_node->left == NULL)
                        parent_node->left = temp;
                else {
                        parent_node = parent_node->left;
                        while(parent_node->right)
                                parent_node = parent_node->right;
                        parent_node->right = temp;
                }
        }
}

//Leaf node is one that does not have any children in the GPT.
int isLeafNode(node_t *node) {
        return node->left == NULL;
}

// node does not have any more siblings if right node is NULL.
int hasNoSibling(node_t *node) {
        return node->right == NULL;
}

// function to print required number of tabs so that generated C file is somewhat readable.
void print_tabs(int n) {
        for(int i = 0; i<n; i++) 
        printf("\t");
}

// function to close switch and while loop
void close_switch_while(int level) {
        print_tabs(level+3);
        printf("}\n");
        print_tabs(level+3);
        printf("scanf(\"%%d\", &n);\n");
        print_tabs(level+2);
        printf("}\n");
}

// function to open a while loop and switch
void open_while_switch(int level) {
        print_tabs(level+3);
        printf("scanf(\"%%d\", &n);\n");
        print_tabs(level+3);
        printf("while(n) {\n");
        print_tabs(level+4);
        printf("switch(n) {\n");
}

// recursively print cases
void print_switch_case_rec(node_t* node, int sibling, int level, int l_or_r) {
        //the order required for traversal of binary tree is preorder.
        // leaf node is identified by left as null.
        // node does not have sibling if right is null.

        if(node == NULL) 
        	return;
	if(!isLeafNode(node)) {
                
                if(l_or_r)
                        sibling = 1;
                        
                print_tabs(level+3);
                printf("case %d: printf(\"%s\\n\");\n", sibling, node->key);
                open_while_switch(level);
        }
        else {
                if(l_or_r)
                        sibling = 1;
                print_tabs(level+3);
                printf("case %d: printf(\"%s\\n\");\n", sibling, node->key);
                print_tabs(level+4);
                printf("break;\n");
        }

        print_switch_case_rec(node->left, sibling, level+1, 1);

        if(hasNoSibling(node)) {
                close_switch_while(level);
                
                if(level>1){
                        print_tabs(level+2);
                        printf("break;\n");
                }
        }

        print_switch_case_rec(node->right, sibling+1, level, 0);       
}

void print_switch_case(const tree_t* ptr_tree) {
        int level = 0;
        print_tabs(level+2);
        printf("while(n) {\n");
        print_tabs(level+3);
        printf("switch(n) {\n");
	print_switch_case_rec(ptr_tree -> root->left, 1, level+1, 1);        
}

// recursively free nodes
void free_nodes(node_t* node) {

        if(node==NULL) return;

        free_nodes(node->left);
        free_nodes(node->right);

        free(node);

}

void free_tree(tree_t* ptr_tree) {
        free_nodes(ptr_tree->root);
        free(ptr_tree);
}

void preamble() {
        printf("#include <stdio.h>\n");
        printf("#include <stdlib.h>\n");
        printf("#include <string.h>\n");
        printf("\n");
}

void prolog() {
        printf("int main() {\n");
}

void epilog() {
        printf("\treturn 0;\n");
        printf("}\n");
}

int main() {
        char item[1025]; //changed here

        preamble();
        
        prolog();

        tree_t ptr_tree;
        init_tree(&ptr_tree);
        add_node(&ptr_tree, "root", " ");

        char parent[1025][1025]; //changed here
        strcpy(parent[0], "root");

        while(fgets(item, 1025, stdin) != NULL) { //changed here
                item[strlen(item)-1] = '\0';
                int k = 0;
                while (k<strlen(item) && item[k]=='\t') {
                        k++;
                }
                char temp[1025]; //changed here
                int l;
                for(l = 0; l<(strlen(item)-k); l++) {
                        temp[l] = item[l+k];
                }
                temp[l] = '\0';
                if (k==0) {
                        strcpy(parent[1], item);
                        add_node(&ptr_tree, parent[0], item);
                }
                else {
                        strcpy(parent[k+1], temp);
                        add_node(&ptr_tree, parent[k], temp);
                }
        }

        printf("\tint n;\n");
        printf("\tscanf(\"%%d\", &n);\n");
        print_switch_case(&ptr_tree);
        epilog();

        //free_tree(&ptr_tree);

        return 0;
}
