#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "ctype.h"

struct Product{
	char code[11];
	char name[255];
	float price;
	int quantity;
	char dateProduct[11];
	char placeProduct[255];	
};

// declare
Product CreateProduct();
void ShowProduct(Product *, int);
void InitListProduct(Product *&, int);
void AddElement(Product *&, int, Product);
void DeleteElement(Product *&, int &, int);
Product * FindProductCode(Product *, int, char*);
Product * FindProductName(Product *, int, char*);
Product * FindProductPrice(Product *, int, float, int&);
int EditProductByCode(Product *&, int, char*);
int DeleteProductByCode(Product *&, int &, char*);
int DeleteProductByPrice(Product *&, int &, float);
void InsertChar(char *, int, int, char *);
float InsertNum(char *, int, int);
void SaveFileData(Product *, int, char*);
void ReadFileData(Product *&, int, char*);

// detail
Product CreateProduct(){
	Product created;
	
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

void ShowProduct(Product *array, int n){
	printf("List Product\n");
	for(int i = 0; i < n; i++){
		printf("--------------------------------------------------------\n");
		printf("Code: %s | ", (array + i)->code);
		printf("Name: %s | ", (array + i)->name);
		printf("Price: %3.2f | ", (array + i)->price);
		printf("Quantity: %d | ", (array + i)->quantity);
		printf("Date product: %s | ", (array + i)->dateProduct);
		printf("Place product: %s\n", (array + i)->placeProduct);
	}	
}

void InitListProduct(Product *&array, int n){
	for(int i = 0; i < n; i++){
		*(array + i) = CreateProduct();
	}	
}

void AddElement(Product *&Array, int count, Product element){
	realloc(Array, count * sizeof(Product *));
	*(Array + count - 1) = element;
}

void DeleteElement(Product *&Array, int &n, int position){
	for(int i = 0; (Array + position + i) != (Array + n - 1); i++){
		*(Array + position + i) = *(Array + position + i + 1);
	}
	n--; 
	//realloc(Array, n * sizeof(Product *)); // CHUA FIX DUOC
}

Product * FindProductCode(Product *array, int n, char *search){
	for(int i = 0; i <= n/2; i++){	
		if(strcmp((array + i)->code, search) == 0){
			return (array + i);
		}
		else if(strcmp((array + n - 1 - i)->code, search) == 0){
			return (array + n - 1 - i);
		}
	}
	return NULL;
}

Product * FindProductName(Product *array, int n, char *search){
	for(int i = 0; i <= n/2; i++){
		if(strcmp((array + i)->name, search) == 0){
			return (array + i);
		}
		else if(strcmp((array + n - 1 - i)->name, search) == 0){
			return (array + n - 1 - i);
		}
	}
	return NULL;
}

Product * FindProductPrice(Product *array, int n, float search, int &numProduct){
	int count = 0;
	Product * tmpArray;
	tmpArray = (Product *)malloc(1 * sizeof(Product));
	for(int i = 0; i < n; i++){
		if ((array + i)->price == search){
			count++;
			AddElement(tmpArray, count, *(array + i));
		}
	}
	numProduct = count;
	if(count <= 0){
		free(tmpArray);
		return NULL;
	}
	else{
		return tmpArray;
	}
}

int EditProductByCode(Product *&array, int n, char* code){
	Product * tmpPointer = FindProductCode(array, n, code);
	if(tmpPointer == NULL){
		return 0;
	}
	else{
		*tmpPointer = CreateProduct();
		return 1;
	}
}

int DeleteProductByCode(Product *&array, int &n, char* code){
	Product * tmpPointer = FindProductCode(array, n, code);
	if(tmpPointer == NULL){
		return 0;
	}
	else{
		for(int i = 0; (tmpPointer + i) != (tmpPointer + n - 1); i++){
			*(tmpPointer + i) = *(tmpPointer + i + 1);
		}
		n--; 
		//realloc(array, n * sizeof(Product *)); // CHUA FIX DUOC
		return 1;
	}
}

int DeleteProductByPrice(Product *&array, int &n, float search){
	int count = 0;
	for(int i = 0; i < n; ){
		if ((array + i)->price == search){
			printf("i = %d - n = %d\n", i, n);
			count++;
			DeleteElement(array, n, i);
			i=0;
		}
		else i++;
	}
	return count;
}
	
void InsertChar(char *str, int x, int y, char *e_str){
	int tmp = 0;
	for (int i = x; i < y; i++){
		e_str[tmp] = str[i];
		tmp++;
	};
	e_str[tmp] = '\0';
}

float InsertNum(char *str, int x, int y){
	int p_dot = 0;
	float num = 0, div = 1;
	for (int i = x; i < y; i++){
		if (str[i] == '.'){
			p_dot = i;
			break;
		}
	}

	if (p_dot == 0) p_dot = y;

	for (int i = x; i < p_dot; i++){
		num = num*10 + (str[i] - 48);
	}
	for (int i = p_dot + 1; i < y; i++){
		num = num*10 + (str[i] - 48);
		div = div * 10;
	}
	num = num /div;

	return num;
}

void SaveFileData(Product *array, int n, char *fileName){
	FILE *file;
	file = fopen(fileName, "w");
	if(!file){
		printf("\nFile not found: %s", fileName);
		return;
	}
	// get system time
	time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    fprintf(file, "%s", asctime(timeinfo));
    
    // write data into file
	for(int i = 0; i < n; i++){
		fprintf(file, "Code:%s|", (array + i)->code);
		fprintf(file, "Name:%s|", (array + i)->name);
		fprintf(file, "Price:%3.2f|", (array + i)->price);
		fprintf(file, "Quantity%d|", (array + i)->quantity);
		fprintf(file, "Date:%s|", (array + i)->dateProduct);
		fprintf(file, "Place:%s\n", (array + i)->placeProduct);
	}
	fclose(file);
}

void ReadFileData(Product *&array, int n, char *fileName){
	int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    int count = 0;
	char * str;
	
	FILE *file;
	file = fopen(fileName, "r");
	if(!file){
		printf("\nFile not found: %s", fileName);
		return;
	}
    while (!feof(file)){
       	if(count == 0){
       		str = fgets(buffer, BUFFER_SIZE, file);
           	printf("Time: %s", str);
		}
 		else{
	 		str = fgets(buffer, BUFFER_SIZE, file);
	        for (int i = 0; i < strlen(str); i++){
				if (isalpha(str[i]) || (str[i] == ':') || (str[i] == '|')){
					str[i] = ' ';
				} 
			}
		
			int n = strlen(str);
			str[n] = ' ';
		
			for(int i = 0, j, count_data = 1; i < n;){		
				if (str[i] != ' ') {
					j = i;
					while (str[i] != ' '){
						i++;
					};
					switch (count_data){
						case 1: // insert code
							InsertChar(str, j, i, (array + count - 1)->code);
							break;
						case 2: // insert name
							InsertChar(str, j, i, (array + count - 1)->name);
							break;
						case 3: // insert price
							(array + count - 1)->price = InsertNum(str, j, i);
							break;
						case 4: // insert quantity
							(array + count - 1)->quantity = (int)InsertNum(str, j, i);
							break;
						case 5: // insert date product
							InsertChar(str, j, i, (array + count - 1)->dateProduct);
							break;
						case 6: // insert place product
							InsertChar(str, j, i, (array + count - 1)->placeProduct);
							break;
					}
					count_data++;
				}
				else i++;
			}
		}
		count++;
		if(n >= count) n = count;
	}	    
}

int main(){
	printf("..:: PRODUCT MANAGER ::..");
	int n;
	int numProduct = 0;
	do{
		printf("\nInsert product quantity: ");
		scanf("%d", &n);
		if(n < 0){
			printf("\nError!!!.");
		}
	}
	while(n <= 0);
	
	Product *listProduct;
	listProduct = (Product *)malloc(n * sizeof(Product));
	
	InitListProduct(listProduct, n);
	ShowProduct(listProduct, n);
	
	// Test Delete
	//DeleteProductByCode(listProduct, n, "2");
	//DeleteProductByPrice(listProduct, n, 1);
	//ShowProduct(listProduct, n);
	
	//SaveFileData(listProduct, n, "data.txt");
	//ReadFileData(listProduct, n, "data.txt");
	
	// Test Search
	Product *result = FindProductPrice(listProduct, n, 1, numProduct);
	
	if(numProduct <= 0){
		printf("\nNo product found");
	}
	else{
		printf("\nProduct found: %d\n", numProduct);
		ShowProduct(result, numProduct);
	}
	
	// giai phong o nho
	free(result);
	free(listProduct);
	return 0;
}
