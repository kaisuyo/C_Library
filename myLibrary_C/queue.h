
#include<string.h>
#define maxQueue 5

struct TYPEQUEUE {
	int base[maxQueue];
	char name[30];
};
typedef struct TYPEQUEUE typeQueue;

struct QUEUE {
	struct QUEUE *next;
	struct QUEUE *prev;
	typeQueue data;
};
typedef struct QUEUE *queue;

queue newQueue () {

	queue temp = NULL;
	temp = (queue)malloc(sizeof(queue)*100);

	temp->prev = NULL;
	temp->next = NULL;

	return temp;
}

queue newQueueWithData ( typeQueue data ) {
	
	queue p = newQueue();

	p->data = data;
	return p;
}


void enQueue ( queue head, typeQueue data ) {
	
	queue p = newQueueWithData( data );
	
	if ( head->next == NULL ) {
		head->next = p;
		head->prev = p;

	} else {
		p->prev = head->prev;
		head->prev->next = p;

		head->prev = p;

	}
}

void deQueue ( queue head ) {
	
	queue p = head->next;
	
	if ( p != NULL && p->next != NULL ) {
	
		head->next = head->next->next;
		head->next->prev = NULL;

	} else {
			head->next = NULL;
			head->prev = NULL;
			printf("\nclear.!!!\n");
	}
	
	free(p);
}

int lengthQueue ( queue head ) {
	int n = 0;
	queue p = head->next;

	while ( p != NULL ) {
		n++;
		p = p->next;
	}

	return n;	
}


typeQueue front ( queue head ) {
	return head->next->data;
}

void clear ( queue head ) {
	queue p = head->next;
	if ( p != NULL ) {
		deQueue( head );
		clear(head);
	}
}
