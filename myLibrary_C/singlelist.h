
#define maxLinked 5

struct TYPELINKED {

	char name[30];// xâu
	int base[maxLinked]; // mảng các số nguyên, tối đa 5 phần tử 

};
typedef struct TYPELINKED typeLinked;

//
struct linkedList { // một linked
	typeLinked data;
	struct linkedList *next;
};
typedef struct linkedList *linked;
//

linked newLinked () {//tao node trắng
	
	linked temp = NULL;
	temp = ( linked ) malloc ( sizeof ( linked )*100 );
	
	temp->next = NULL;
	
	return temp;
}
//
linked newLinkedWithData ( typeLinked data ) {// tạo node với data
	
	linked p = newLinked();

	p->data = data;

	return p;
}

void addTail ( linked head, typeLinked data ) {
	
	linked p = newLinkedWithData ( data );

	if ( head->next == NULL ) {
		head->next = p;
	} else {
		linked q = head->next;

		while ( q->next != NULL ) {
			q = q->next;
		}

		q->next = p;
	}
}
//

void addHead ( linked head, typeLinked data ) {// thêm vào đầu

	linked p = newLinkedWithData ( data );

	if ( head->next == NULL ) {
		head->next = p;
	} else {
		p->next = head->next;
		head->next = p;
	}
}
//

void del ( linked head, int id ) {// xóa node theo id ( base[0] )
	
	if ( head->next->data.base[0] == id ) {//	xóa đầu
	
		linked p = head->next;
		head->next = head->next->next;
	
		free(p);
	
	} else {//	xóa giữa
		
		linked q;
		
		for ( q = head->next; q->next != NULL; q = q->next ){
			
			if ( q->next->data.base[0] == id ) {
				linked p = q->next;
				q->next = q->next->next;
				free(p);
				break;
			}
		}

		if ( q->data.base[0] == id ) {
			free(q);
		}
	}
}

int lengthLinked ( linked h ) {
	int s = 0;
	for ( linked p = h; p != NULL; p = p->next ) {
		s++;
	}
	return s-1;
}

void clearLinked ( linked head ) {
	while ( head->next != NULL ) {
		del ( head, head->next->data.base[0] );
	}
}