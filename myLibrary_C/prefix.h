#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NODE_TOTAL 128 // so tu phu hop toi da
#define MAX_LINE 2000

struct Node{
	struct Node *c[MAX_NODE_TOTAL];
	int freq;
	char k;
	int line[MAX_LINE];
	struct Node *pr;
};

typedef struct Node *node;

node newNode(){	// tao node moi
	node temp;
	temp = (node)malloc(sizeof(node)*2000);
	for(int i = 0; i < MAX_NODE_TOTAL; i++){
		temp->c[i] = NULL;
		temp->freq = 0;
		// temp->k = ' ';
	}

	temp->pr = NULL;
	return temp;
}

int checkWord(char *str) {	
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] < '!' || str[i] > 'z') {
			return 0;
		}
	}
	if (strlen(str) == 0) {
		return 0;
	}
	return 1;
}

void insert_trie(node head, char *str, int line){
	node p = head;
	
	if (checkWord(str) == 1) {
		// int c = getchar();
		// printf("%s %ld:\t", str, strlen(str));
		
		for(int i = 0; i < strlen(str); i++){
			if( p->c[ str[i] - '!'] == NULL ){
				node temp = newNode();
				temp->k = str[i];
				temp->pr = p;
				p->c[ str[i] - '!'] = temp;
			}
			p = p->c[ str[i] - '!'];
			// printf("%d\t", str[i] - '!');
		}

		p->line[p->freq] = line;
		p->freq++; // ki tu cuoi 
		// // puts(str);
	} 
}

void clear_trie(node head) {
	if (head == NULL) {
		return;
	}
	for (int i = 0; i < MAX_NODE_TOTAL; i++) {
		clear_trie(head->c[i]);
	}
	free(head);
}

void traverse(node head) {
	if (head == NULL) {
		return;
	}
	for (int i = 0; i < MAX_NODE_TOTAL; i++) {
		traverse(head->c[i]);
	}
	if (head->pr != NULL) {
		printf("%c\n", head->pr->k);
	}
	// printf("%c %d", head->k, head->freq);
}

int isExist ( node head, char *str ) {
	node p = head;
	
	for( int i = 0; i < strlen(str); i++ ) {	
		p = p->c[ str[i] - '!'];

		if ( p == NULL ) {
			return 0;
		}
	}
	if (p->freq == 0) {
		return 0;
	}
	return 1;
}

int check_end(node p) {
	for (int i = 0; i < MAX_NODE_TOTAL; i++) {
		if (p->c[i] != NULL) {
			return i;
		}
	}
	return -1;
}
// ham dao nguoc chuoi (ko qua 50 ky tu)
void str_cvs(char *str) {
	char temp[50];
	int j = 0;
	for (int i = strlen(str)-1; i >= 0 ; i--) {
		temp[j++] = str[i];
	}
	temp[j] = '\0';
	strcpy(str, temp);
}
void printWord(node cur) {
	node p = cur;
	char str[50] = "";
	int i = 0;
	while (p != NULL) {
		// printf("%c", p->k);
		str[i++] = p->k;
		p = p->pr;
	}
	// printf("%s %ld\n", str, strlen(str));
	str_cvs(str);
	printf("%s %d, ", str, cur->freq);
	int curNum = -1;
	for (int i = 0; i < cur->freq; i++) {
		if (cur->line[i] != curNum) {
			printf("%d", cur->line[i]);
			curNum = cur->line[i];

			if (i < cur->freq - 1) {
				printf(", ");
			}
		}
	}
	printf("\n");
	
}

void printTree(node head) {
	if (head == NULL) {
		return;
	}
	if (head->freq != 0) {
		printWord(head);
		// printf("%c\t", head->k);
	}
	for (int i = 0; i < MAX_NODE_TOTAL; i++) {
		printTree(head->c[i]);
	}
}

void fprintWord(FILE *f, node cur) {
	node p = cur;
	char str[50] = "";
	int i = 0;
	while (p != NULL) {
		// printf("%c", p->k);
		str[i++] = p->k;
		p = p->pr;
	}
	// printf("%s %ld\n", str, strlen(str));
	str_cvs(str);
	fprintf(f, "%s %d, ", str, cur->freq);
	int curNum = -1;
	for (int i = 0; i < cur->freq; i++) {
		if (cur->line[i] != curNum) {
			fprintf(f, "%d", cur->line[i]);
			curNum = cur->line[i];

			if (i < cur->freq - 1) {
				fprintf(f, ", ");
			}
		}
	}
	fprintf(f, "\n");
	
}

void fprintTree(FILE *f, node head) {
	if (head == NULL) {
		return;
	}
	if (head->freq != 0) {
		fprintWord(f, head);
		// printf("%c\t", head->k);
	}
	for (int i = 0; i < MAX_NODE_TOTAL; i++) {
		fprintTree(f, head->c[i]);
	}
}

