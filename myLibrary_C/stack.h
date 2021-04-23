
#define maxStack 1

struct TYPESTACK {
	int base[maxStack];
	char name[30];
};
typedef struct TYPESTACK typeStack;
//

struct STACK {
	typeStack data;
	struct STACK *next;// cấp trên 
};
typedef struct STACK *stack;
//

stack newStack () {//tao node trắng
	
	stack temp = NULL;
	temp = ( stack ) malloc ( sizeof ( stack )*100 );
	
	temp->next = NULL;
	
	return temp;
}

stack newStackWithData ( typeStack data ) {// tạo node với data
	
	stack p = newStack();

	p->data = data;

	return p;
}

void push ( stack head, typeStack data ) {// chính là thêm vào đầu của liên kết đơn 

	stack p = newStackWithData ( data );

	if ( head->next == NULL ) {
		head->next = p;
	} else {
		p->next = head->next;
		head->next = p;
	}
}

void pop ( stack head ) {
	if ( head->next != NULL ) {
		stack p = head->next;
		head->next = head->next->next;
		free(p);
	}
}

typeStack top ( stack head ) {
	return head->next->data;
}

int lengthStack ( stack h ) {
	int s = 0;
	for ( stack p = h; p != NULL; p = p->next ) {
		s++;
	}
	return s-1;
}

void clearStack ( stack head ) {
	while ( head->next != NULL ) {
		pop ( head );
	}
}
