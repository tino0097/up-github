#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct Product{
	char code[11];
	char name[255];
	float price;
	int quantity;
	char dateProduct[255];
	char placeProduct[255];	
};

Product CreateProduct(){
	Product created;
	created.price = 0;
	printf("---------------------------------\n");
	printf("Insert product(s)\n");
	fflush(stdin);
	printf("Code:");
	gets(created.code);
	printf("Name:");
	gets(created.name);
	do{
		printf("Price:");
		scanf("%f", &created.price);
		fflush(stdin);
		if(created.price <= 0){
			printf("Insert invalid price! Try again\n");
		}
	}
	while(created.price <= 0);
	do{
		printf("Quantity:");
		scanf("%d", &created.quantity);
		fflush(stdin);
		if(created.quantity < 0){
			printf("Insert invalid quantity! Try again\n");
		}
	}
	while(created.price <= 0);

	printf("Date product:");
	gets(created.dateProduct);
	printf("Place product:");
	gets(created.placeProduct);
	return created;
}

void ShowProduct(Product *array, int n = 1){
	printf("Danh sach san pham\n");
	for(int i = 0; i < n; i++){
		printf("--------------------------------------------------------\n");
		printf("Code: %s | ", (array + i)->code);
		printf("Name: %s | ", (array + i)->name);
		printf("Price: %3.2f | ", (array + i)->price);
		printf("Quantity: %d | ", (array + i)->quantity);
		printf("Date product: %s | ", (array + i)->dateProduct);
		printf("Place product: %s | \n", (array + i)->placeProduct);
	}	
}

void InsertMoreProduct(Product *&array, int n){
	for(int i = 0; i < n; i++){
		*(array + i) = CreateProduct();
	}	
}

void InsertOneProduct(Product *&array, int &n, Product PhanTuThem){
	realloc(array, (n + 1) * sizeof(Product *));
	*(array + n) = PhanTuThem;
}

Product * FindProductCode(Product *array, int n, char search[]){
	for(int i = 0; i < n; i++){
		if((array + i)->code == search){
			printf("da vao day");
			return (array + i);
		}
	}
	return NULL;
}

int main(){
	int n;
	do{
		printf("\nNhap so luong san pham: ");
		scanf("%d", &n);
		if(n < 0){
			printf("\nError!!!.");
		}
	}
	while(n <= 0);
	
	Product *listProduct;
	listProduct = (Product *)malloc(n * sizeof(Product));
	if(n == 1){
		*listProduct = CreateProduct();
		ShowProduct(listProduct);
	}
	else {
		InsertMoreProduct(listProduct, n);
		ShowProduct(listProduct, n);
	}
	
	if(FindProductCode(listProduct, n, "1") == NULL){
		printf("ko");
	}
	else{
		printf("San pham can tim: \n%p", FindProductCode(listProduct, n, "1"));
	}
	
	free(listProduct);
	return 0;
}