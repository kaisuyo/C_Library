

void swap(int *x, int *y){
	int temp = *x;
	*x = *y;
	*y = temp;
}

void max_heap (int s[], int n, int a) { // mảng s, n phần tử, phần tử thứ a

	int best = a; // chỉ số của thằng nhất trong 3 thằng s[a], s[2a], s[2a+1];
	int left = 2*a + 1; // chỉ số thằng con trái
	int right = 2*a + 2; // chỉ số thằng con phải

	if( left < n && s[left] > s[best] ) {// nếu tồn tại thằng con trái và nó hơn cha
		best = left;// trao chức nhất cho thằng con trái
	}

	if( right < n && s[right] > s[best] ) {// nếu tồn tại thằng con phải và nó hơn thằng nhất
		best = right;// nó bây giờ được phong là thằng nhất
	}

	// mới chỉ là phong chức chứ chưa chính thức nhận chức

	if( a != best ){// nếu thằng lớn nhất ko phải thằng s[a] 

		swap( &s[a], &s[best] );// chính thức nhận chức nhất (đổi chỗ)

		max_heap( s, n, best );// bị giáng chức thì kiểm tra nó với các con tiếp theo (đệ quy);
	}
																									
void heapSort (int s[], int n) {// sắp xếp từ bé đến lớn

	for(int i = n/2 - 1; i >= 0; i--){
		max_heap( s, n, i );
	}

	for(int i = n - 1; i > 0; i--){
		swap( &s[0], &s[i]);// đổi chỗ xong thì tìm ra phần tử lớn nhất và chuyển nó về cuối dãy

		max_heap( s, i, 0 );// gọi max_heap với mẳng s, i phần tử, phần tử thứ 0 (sau khi gọi thì s[0] chính là thằng lớn nhất dãy còn lại)
	}

}

void out(int s[], int n){
	for(int i = 0; i < n; i++){
		printf("%d ",s[i]);
	}
}

void bubbleSort(int s[], int n){// sap xep noi bot
	for(int i = 0; i < n-1; i++){
		for(int j = i+1; j < n; j++){
			if(s[i] >= s[j]){
				int tg = s[i];
				s[i] = s[j];
				s[j] = tg;
			}
		}
	}
}


int searchMin(int s[],int start, int n){// tim phan tu min trong mang bat dau tu phan tu start den cuoi
	int o = start;
	for(int i = start; i < n; i++){
		if(s[o] > s[i]){
			o = i;
		}
	}
	return o; // return thu tu cua min trong [start,n]
}

void selectionSort(int s[], int n){// sap xep lua chon
	for(int i = 0; i < n; i++){
		int t = searchMin(s, i, n);
		int temp = s[i];
		s[i] = s[t];
		s[t] = temp;
	}
}


int divide_Q(int s[], int low, int heigh){
	int i = low, j = heigh - 1;
	int pivot = s[heigh];
	
	while(1){
		while(i <= j && s[i] < pivot){// tang i den khi s[i] < s[pivot]
			i++;
		}
		while(i <= j && s[j] > pivot){// tang j den khi s[j] > s[pivot]
			j--;
		}
		
		if(i >= j) break; // thoat khoi vong lap khi i >= j
		
		int temp = s[i]; // khi i khong tang, j khong giam duoc nua thi s[i] va a[j] doi cho cho nhau
		s[i] = s[j];	
		s[j] = temp;
		
		i++;// sau khi doi xong thi tiep tuc tang i, giam j
		j--;
		
	}
	
	int temp = s[i]; // dua pivot ve dung vi tri
	s[i] = s[heigh];
	s[heigh] = temp;
	
	return i; // tra ve vi tri dung
}

void quickSort(int s[], int low, int heigh){
	if( low < heigh){
		
		int pv = divide_Q(s, low, heigh);
		
		quickSort(s, low, pv-1);// de quy sap xep trai
		quickSort(s, pv+1, heigh);// de quy sap xep phai
	}
}

void divide_Mg(int s[], int l, int m, int r){
	int i, j, k;
	int n1 = m - l + 1;
	int n2 =  r - m;

	int L[n1], R[n2];// tao 2 mang con

	for (i = 0; i < n1; i++)// truyen du lieu
		L[i] = s[l + i];
	for (j = 0; j < n2; j++)
		R[j] = s[m + 1 + j];

	i = 0;// cac chi so ban dau cua L, R, mang dich
	j = 0;
	k = l;
	while (i < n1 && j < n2){// them phan tu nho hon vao s
		if (L[i] <= R[j]){
			s[k] = L[i];
			i++;
		}else{
			s[k] = R[j];
		j++;
		}
		
		k++;
	}
	
	// them phan tu vao s neu 2 mang con chua het
	while (i < n1){
		s[k] = L[i];
		i++;
		k++;
	}
	
	while (j < n2){
		s[k] = R[j];
		j++;
		k++;
    }
}

void mergeSort(int s[], int l, int r){
	if(l < r){
		int m = (r+l)/2;
	
		mergeSort(s, l, m);
		mergeSort(s, m+1, r);
		
		divide_Mg(s, l, m, r);
	}
}
