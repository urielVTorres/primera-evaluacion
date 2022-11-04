#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Declaración de variables globales para guardar los tiempos de procesamiento.
double t1, t2, t3;

//Definición de estructura para usar como almaacenamiento dinámico
typedef struct vector{
    int *value;
    int length;
    int size;
} vector;

//Prototipos de funciones
void bubbleSort(int a[], int n);
void selectionSort(int a[], int n);
void insertionSort(int a[], int n);
void printArray(int a[], int n);
vector newVector();
void push_back(vector *p, int v);

//definición de las funciones

//Constructor del vector
vector newVector(){
    vector v;
    v.value = (int*)malloc(sizeof(int));
    v.length = 0;
    v.size = 1;
    
    return v;
}

//Añadir un valor al vector
void push_back(vector *p, int v){
    if(p->length >= p->size){
        p->size*=2;
        p->value = realloc(p->value, p->size * sizeof(int));
    }
    p->value[p->length] = v;
    p->length++;
}

//Imprimir un arreglo
void printArray(int a[], int n){
	int i;
	for(i=0;i < n; i++)
		printf("%d\t", a[i]);
	printf("\n\n");
	
}

//Algorítmo de ordenamiento por inserción
void insertionSort(int a[], int n){
    clock_t start = clock();
	int i, j, k;
	for(i=0; i < n-1; i++){
		for(j=i+1; j < n; j++){
			if(a[i]>a[j]){
				int aux = a[j];
				for(k=j; k>i; k--){
					a[k]= a[k-1];
				}
				a[i]=aux;
			}
		}
	}
    clock_t end = clock();
    double duracion = ((double) (end - start)/CLOCKS_PER_SEC);
    t3 = duracion;
    printf("Ordenamiento por Insertion Sort:\n");
    printArray(a,n);
}

//Algorítmo de ordenamiento burbuja
void bubbleSort(int a[], int n){
    clock_t start = clock();
    int eliminar = 2;
    while(n != eliminar+1){
    	int i = 0;
        for(i = 0; i <= n - eliminar; i++){
            if(a[i] > a[i+1]){
                int aux = a[i];
                a[i]=a[i+1];
                a[i+1]=aux;
            }
        }
        eliminar++;
    }
    clock_t end = clock();
    double duracion = ((double) (end - start)/CLOCKS_PER_SEC);
    t1 = duracion;
    printf("Ordenamiento por Bubble Sort:\n");
    printArray(a,n);
}

//Algorítmo de ordenamiento por selección
void selectionSort(int a[], int n){
    clock_t t = clock();
	int i,j;
	int aux2=0;
	for(i=0; i<n; i++){
		int aux = a[i];
		for(j=i+1; j<n;j++){
			if(aux > a[j]){
				aux=a[j];
				aux2=j;
			}else aux2=i;
		a[aux2]=a[i];
		a[i]=aux;
		}
	}
    t = clock() - t;
    double duracion = ((double) (t)/CLOCKS_PER_SEC);
    t2 = duracion;
    printf("Ordenamiento por Selection Sort:\n");
    printArray(a,n);
}



int main(){
    //Declaración de variables en donde se guardarán los datos.
    vector edades_1 = newVector();
    vector edades_2 = newVector();
    vector edades_3 = newVector();

    //Abrir el archivo setdatosedades.txt
    FILE *f;
    f = fopen("setdatosedades.txt", "r");
    
    //Leer las edades del archivo y guradarlas en los 3 arreglos.
    int edad;

    while(fscanf(f, "%i", &edad)==1){
        push_back(&edades_1, edad);
        push_back(&edades_2, edad);
        push_back(&edades_3, edad);
    }
    
    //Cerrar el archivo
    fclose(f);

    //Ejectar las funciones de ordenamientos.
    bubbleSort(edades_1.value, edades_1.length);
    selectionSort(edades_2.value, edades_2.length);
    insertionSort(edades_3.value, edades_3.length);


    //Resumen del tiempo de procesamiento
    printf("\n\nTiempo de procesamiento Ordenamiento por Bubble Sort: %f segundos\n", t1);

    printf("Tiempo de procesamiento Ordenamiento por Selection Sort: %f segundos\n", t2);

    printf("Tiempo de procesamiento Ordenamiento por Insertion Sort: %f segundos\n", t3);

    //Salir del programa
    printf("\n\tPresione la tecla 'Enter' para cerrar.");
    getchar();

    return 0;
}