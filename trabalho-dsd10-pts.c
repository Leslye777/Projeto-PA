#include <dir.h>
#include <time.h>
#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>

double PCFreq = 0.0;
__int64 CounterStart = 0;
 
void StartCounter(){
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        printf("QueryPerformanceFrequency Failed.\n");
    PCFreq = (double)(li.QuadPart) / 1000.0;
    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
 
double GetCounter(){
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return (double)(li.QuadPart - CounterStart) / PCFreq;
}

void menuAlgoritmos(){
	printf("\n-----SELECIONE O ALGORTIMO DESEJADO-----\n");
	printf("\n1-Selecion Sort");
	printf("\n2-Inserction Sort");
	printf("\n3-Shell Sort");
	printf("\n4-Merge Sort");
	printf("\n5-Heap Sort");
	printf("\n6-Quick Sort");
}

void MenuEntradas(){
	printf("\n-----DIGITE O TAMANHO DA ENTRADA DE DADOS-----\n");
	printf("\n 1- 10\n");
	printf("\n 2- 1000\n");
	printf("\n 3- 10000\n");
	printf("\n 4- 100000\n");
	printf("\n 5- 1000000\n");
}

int Selection_sort(int *vet,int n){
	int i,j;
	int indice;
	int aux;
	for(i=0;i<n-1;i++){
		indice=i;

		for(j=i+1;j<n;j++){
			if(vet[j]<vet[indice]){
				indice=j;
			}
		}
		aux=vet[i];
		vet[i]=vet[indice];
		vet[indice]=aux;
	}
}

int Inserction_sort(int *vet, int n){
	int i,j;
	
	for(i=1;i<n;i++){
		j=i-1;
		int x=vet[i];
		
		while(x<vet[j]&&j>=0){
			vet[j+1]=vet[j];
			vet[j]=x;
			j--;
		}
	}
}

	
void Shell_sort(int *vet, int n) {
    int i , j , value;
    int gap = 1;
    while(gap < n) {
        gap = 3*gap+1;
    }
    while ( gap > 1) {
        gap /= 3;
        for(i = gap; i < n; i++) {
            value = vet[i];
            j = i;
            while (j >= gap && value < vet[j - gap]) {
                vet[j] = vet [j - gap];
                j = j - gap;
            }
            vet [j] = value;
        }
    }
}

	
void Inversa(int *vet, int n) {
    int i , j , value;
    int gap = 1;
    while(gap < n) {
        gap = 3*gap+1;
    }
    while ( gap > 1) {
        gap /= 3;
        for(i = gap; i < n; i++) {
            value = vet[i];
            j = i;
            while (j >= gap && value > vet[j - gap]) {
                vet[j] = vet [j - gap];
                j = j - gap;
            }
            vet [j] = value;
        }
    }
    
}

void merge(int vetor[], int comeco, int meio, int fim) {
    int com1 = comeco, com2 = meio+1, comAux = 0, tam = fim-comeco+1;
    int *vetAux;
    vetAux = (int*)malloc(tam * sizeof(int));
    while(com1 <= meio && com2 <= fim){
        if(vetor[com1] < vetor[com2]) {
            vetAux[comAux] = vetor[com1];
            com1++;
        } else {
            vetAux[comAux] = vetor[com2];
            com2++;
        }
        comAux++;
    }
    while(com1 <= meio){  //Caso ainda haja elementos na primeira metade
        vetAux[comAux] = vetor[com1];
        comAux++;
        com1++;
    }
    while(com2 <= fim) {   //Caso ainda haja elementos na segunda metade
        vetAux[comAux] = vetor[com2];
        comAux++;
        com2++;
	}
    for(comAux = comeco; comAux <= fim; comAux++){    //Move os elementos de volta para o vetor original
        vetor[comAux] = vetAux[comAux-comeco];
    }
    free(vetAux); 
}

void mergeSort(int vetor[], int comeco, int fim){
    if (comeco < fim) {
        int meio = (fim+comeco)/2;
        mergeSort(vetor, comeco, meio);
        mergeSort(vetor, meio+1, fim);
        merge(vetor, comeco, meio, fim);
    }
}


void peneira(int *vet, int raiz, int fundo);

void heapsort(int *vet, int n){
	int i, tmp;

	for (i = (n / 2); i >= 0; i--) {
		peneira(vet, i, n - 1);
	}

	for (i = n-1; i >= 1; i--) {
		tmp = vet[0];
		vet[0] = vet[i];
		vet[i] = tmp;
		peneira(vet, 0, i-1);
	}
}

void peneira(int *vet, int raiz, int fundo) {
	int pronto, filhoMax, tmp;

	pronto = 0;
	while ((raiz*2 <= fundo) && (!pronto)) {
		if (raiz*2 == fundo) {
			filhoMax = raiz * 2;
		}
		else if (vet[raiz * 2] > vet[raiz * 2 + 1]) {
			filhoMax = raiz * 2;
		}
		else {
			filhoMax = raiz * 2 + 1;
		}

	if (vet[raiz] < vet[filhoMax]){
		tmp = vet[raiz];
		vet[raiz] = vet[filhoMax];
		vet[filhoMax] = tmp;
		raiz = filhoMax;
    }
	else {
      pronto = 1;
	}
  }
}

void quicksort(int *values, int began, int end){
	int i, j, pivo, aux;
	i = began;
	j = end-1;
	pivo = values[(began + end) / 2];
	while(i <= j){
		while(values[i] < pivo && i < end){
			i++;
		}
		while(values[j] > pivo && j > began){
			j--;
		}
		if(i <= j){
			aux = values[i];
			values[i] = values[j];
			values[j] = aux;
			i++;
			j--;
		}
	}
	if(j > began){
		quicksort(values, began, j+1);
	}
	if(i < end){
		quicksort(values, i, end);
	}
}

int main(){
	int i=0;
	FILE *pont_arq;
	int n;
	int *elementos;
	int *vet;
	int k;
	int opcaoAlgoritmos,opcaoEntradas;
	
	
	do{	
		double tempoEmMilissegundo = 0.0000000;
		menuAlgoritmos();
		printf("\n");
		scanf("%d",&opcaoAlgoritmos);
		fflush(stdin);
		switch(opcaoAlgoritmos){
			case 1:
				MenuEntradas();
				scanf("%d",&opcaoEntradas);		
				fflush(stdin);
				switch(opcaoEntradas){
					case 1:
						i=0;
						n=10;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada10.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
		                StartCounter();
						Selection_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
						StartCounter();
						Selection_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
	
						Inversa(vet, n);
						StartCounter();
						Selection_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
						free(elementos);
						free(vet);
						fclose(pont_arq);
					break;				
					case 2:
						n=1000;
						i=0;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada1000.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
		                StartCounter();
						Selection_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    StartCounter();
						Selection_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    Inversa(vet, n);
						StartCounter();
						Selection_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;
					case 3:
						n=10000;
						i=0;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada10000.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
		                StartCounter();
						Selection_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    StartCounter();
						Selection_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    Inversa(vet, n);
						StartCounter();
						Selection_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
									    
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;
					case 4:
						n=100000;
						i=0;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada1e+05.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
		                StartCounter();
						Selection_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    StartCounter();
						Selection_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    Inversa(vet, n);
						StartCounter();
						Selection_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
						
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;
					case 5:
						n=1000000;
						i=0;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada1e+06.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
						
						StartCounter();
						Selection_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
						StartCounter();
						Selection_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
						Inversa(vet, n);
						StartCounter();
						Selection_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
						
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;
					}
					break;
			case 2:
				MenuEntradas();
				scanf("%d",&opcaoEntradas);		
				fflush(stdin);
				switch(opcaoEntradas){
					case 1:
						i=0;
						n=10;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada10.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
		                StartCounter();
						Inserction_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
						StartCounter();
						Inserction_sort(vet, n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
						
						Inversa(vet, n);
						StartCounter();
						Inserction_sort(vet, n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
						free(elementos);
						free(vet);
						fclose(pont_arq);
					break;				
					case 2:
						n=1000;
						i=0;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada1000.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
		                StartCounter();
						Inserction_sort(vet, n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    StartCounter();
						Inserction_sort(vet, n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    Inversa(vet, n);
						StartCounter();
						Inserction_sort(vet, n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;
					case 3:
						n=10000;
						i=0;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada10000.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
						
		                StartCounter();
						Inserction_sort(vet, n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    StartCounter();
						Inserction_sort(vet, n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    Inversa(vet, n);
						StartCounter();
						Inserction_sort(vet, n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
									    
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;
					case 4:
						n=100000;
						i=0;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada1e+05.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
		                StartCounter();
						Inserction_sort(vet, n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    StartCounter();
						Inserction_sort(vet, n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    Inversa(vet, n);
						StartCounter();
						Inserction_sort(vet, n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
						
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;
					case 5:
						n=1000000;
						i=0;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada1e+06.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
		
						StartCounter();
						Inserction_sort(vet, n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
						StartCounter();
						Inserction_sort(vet, n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
						Inversa(vet, n);
						StartCounter();
						Inserction_sort(vet, n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
						
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;
					}
					break;
			case 3:
				MenuEntradas();
				scanf("%d",&opcaoEntradas);		
				fflush(stdin);
				switch(opcaoEntradas){
					case 1:
						i=0;
						n=10;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada10.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
						
		                StartCounter();
						Shell_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
						StartCounter();
						Shell_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
						
						Inversa(vet, n);
						StartCounter();
						Shell_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
						free(elementos);
						free(vet);
						fclose(pont_arq);
					break;				
					case 2:
						n=1000;
						i=0;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada1000.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
						
		                StartCounter();
						Shell_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    StartCounter();
						Shell_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    Inversa(vet, n);
						StartCounter();
						Shell_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;
					case 3:
						n=10000;
						i=0;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada10000.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
						
		                StartCounter();
						Shell_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    StartCounter();
						Shell_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    Inversa(vet, n);
						StartCounter();
						Shell_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
									    
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;
					case 4:
						n=100000;
						i=0;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada1e+05.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
						
		                StartCounter();
						Shell_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    StartCounter();
						Shell_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    Inversa(vet, n);
						StartCounter();
						Shell_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
						
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;
					case 5:
						n=1000000;
						i=0;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada1e+06.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
						
						StartCounter();
						Shell_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
						StartCounter();
						Shell_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
						Inversa(vet, n);
						StartCounter();
						Shell_sort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
						
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;
					}
					break;
			case 4:
				MenuEntradas();
				scanf("%d",&opcaoEntradas);		
				fflush(stdin);
				switch(opcaoEntradas){
					case 1:
						i=0;
						n=10;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada10.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
						
		                StartCounter();
						mergeSort(vet,0,n-1);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
						StartCounter();
						mergeSort(vet,0,n-1);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
						
						Inversa(vet, n);
						StartCounter();
						mergeSort(vet,0,n-1);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
						free(elementos);
						free(vet);
						fclose(pont_arq);
					break;				
					case 2:
						n=1000;
						i=0;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada1000.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
						
		                StartCounter();
						mergeSort(vet,0,n-1);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    StartCounter();
						mergeSort(vet,0,n-1);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    Inversa(vet, n);
						StartCounter();
						mergeSort(vet,0,n-1);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;
					case 3:
						n=10000;
						i=0;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada10000.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
						
		                StartCounter();
						mergeSort(vet,0,n-1);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    StartCounter();
						mergeSort(vet,0,n-1);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    Inversa(vet, n);
						StartCounter();
						mergeSort(vet,0,n-1);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
									    
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;
					case 4:
						n=100000;
						i=0;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada1e+05.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
						
		                StartCounter();
						mergeSort(vet,0,n-1);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    StartCounter();
						mergeSort(vet,0,n-1);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    Inversa(vet, n);
						StartCounter();
						mergeSort(vet,0,n-1);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
						
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;
					case 5:
						n=1000000;
						i=0;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada1e+06.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
						
						StartCounter();
						mergeSort(vet,0,n-1);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
						StartCounter();
						mergeSort(vet,0,n-1);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
						Inversa(vet, n);
						StartCounter();
						mergeSort(vet,0,n-1);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
						
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;
					}
					break;
			case 5:
				MenuEntradas();
				scanf("%d",&opcaoEntradas);		
				fflush(stdin);
				switch(opcaoEntradas){
					case 1:
						i=0;
						n=10;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada10.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
						
		                StartCounter();
						heapsort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
						StartCounter();
						heapsort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
						
						Inversa(vet, n);
						StartCounter();
						heapsort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;				
					case 2:
						n=1000;
						i=0;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada1000.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
						
		                StartCounter();
						heapsort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    StartCounter();
						heapsort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    Inversa(vet, n);
						StartCounter();
						heapsort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;
					case 3:
						n=10000;
						i=0;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada10000.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
						
		                StartCounter();
						heapsort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    StartCounter();
						heapsort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    Inversa(vet, n);
						StartCounter();
						heapsort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
									    
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;
					case 4:
						n=100000;
						i=0;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada1e+05.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
		                
						StartCounter();
						heapsort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    StartCounter();
						heapsort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
					    Inversa(vet, n);
						StartCounter();
						heapsort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
						
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;
					case 5:
						n=1000000;
						i=0;
						elementos=(int *)malloc(n*sizeof (int));
						vet=(int *)malloc(n*sizeof (int));
						pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada1e+06.txt","r");
						do{
							fscanf(pont_arq, "%d", &elementos[i] );
							printf("%d\n" ,elementos[i]);
							k=elementos[i];
							vet[i]=k;
							i++;
						}while(i!=n);
						
						StartCounter();
						heapsort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ALEATORIA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
						StartCounter();
						heapsort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDENADA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
					    
						Inversa(vet, n);
						StartCounter();
						heapsort(vet,n);
						tempoEmMilissegundo = GetCounter();
						printf("\nALGORITMO ENTRADA ORDEM INVERSA");
					    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
						
						free(elementos);
						free(vet);
						fclose(pont_arq);
						break;
					}
				break;
				case 6:
						MenuEntradas();
						scanf("%d",&opcaoEntradas);		
						fflush(stdin);
					switch(opcaoEntradas){
						case 1:
							i=0;
							n=10;
							elementos=(int *)malloc(n*sizeof (int));
							vet=(int *)malloc(n*sizeof (int));
							pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada10.txt","r");
							do{
								fscanf(pont_arq, "%d", &elementos[i] );
								printf("%d\n" ,elementos[i]);
								k=elementos[i];
								vet[i]=k;
								i++;
							}while(i!=n);
							
			                StartCounter();
							quicksort(vet, 0, n);
							tempoEmMilissegundo = GetCounter();
							printf("\nALGORITMO ENTRADA ALEATORIA");
						    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
						    
							StartCounter();
							quicksort(vet, 0, n);
							tempoEmMilissegundo = GetCounter();
							printf("\nALGORITMO ENTRADA ORDENADA");
						    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
							
							Inversa(vet, n);
							StartCounter();
							quicksort(vet, 0, n);
							tempoEmMilissegundo = GetCounter();
							printf("\nALGORITMO ENTRADA ORDEM INVERSA");
						    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
							free(elementos);
							free(vet);
							fclose(pont_arq);
							break;				
						case 2:
							n=1000;
							i=0;
							elementos=(int *)malloc(n*sizeof (int));
							vet=(int *)malloc(n*sizeof (int));
							pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada1000.txt","r");
							do{
								fscanf(pont_arq, "%d", &elementos[i] );
								printf("%d\n" ,elementos[i]);
								k=elementos[i];
								vet[i]=k;
								i++;
							}while(i!=n);
							
			                StartCounter();
							quicksort(vet, 0, n);
							tempoEmMilissegundo = GetCounter();
							printf("\nALGORITMO ENTRADA ALEATORIA");
						    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
						    
						    StartCounter();
							quicksort(vet, 0, n);
							tempoEmMilissegundo = GetCounter();
							printf("\nALGORITMO ENTRADA ORDENADA");
						    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
						    
						    Inversa(vet, n);
							StartCounter();
							quicksort(vet, 0, n);
							tempoEmMilissegundo = GetCounter();
							printf("\nALGORITMO ENTRADA ORDEM INVERSA");
						    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
							free(elementos);
							free(vet);
							fclose(pont_arq);
							break;
						case 3:
							n=10000;
							i=0;
							elementos=(int *)malloc(n*sizeof (int));
							vet=(int *)malloc(n*sizeof (int));
							pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada10000.txt","r");
							do{
								fscanf(pont_arq, "%d", &elementos[i] );
								printf("%d\n" ,elementos[i]);
								k=elementos[i];
								vet[i]=k;
								i++;
							}while(i!=n);
							
			                StartCounter();
							quicksort(vet, 0, n);
							tempoEmMilissegundo = GetCounter();
							printf("\nALGORITMO ENTRADA ALEATORIA");
						    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
						    
						    StartCounter();
							quicksort(vet, 0, n);
							tempoEmMilissegundo = GetCounter();
							printf("\nALGORITMO ENTRADA ORDENADA");
						    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
						    
						    Inversa(vet, n);
							StartCounter();
							quicksort(vet, 0, n);
							tempoEmMilissegundo = GetCounter();
							printf("\nALGORITMO ENTRADA ORDEM INVERSA");
						    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
										    
							free(elementos);
							free(vet);
							fclose(pont_arq);
							break;
						case 4:
							n=100000;
							i=0;
							elementos=(int *)malloc(n*sizeof (int));
							vet=(int *)malloc(n*sizeof (int));
							pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada1e+05.txt","r");
							do{
								fscanf(pont_arq, "%d", &elementos[i] );
								printf("%d\n" ,elementos[i]);
								k=elementos[i];
								vet[i]=k;
								i++;
							}while(i!=n);
			                StartCounter();
							quicksort(vet, 0, n);
							tempoEmMilissegundo = GetCounter();
							printf("\nALGORITMO ENTRADA ALEATORIA");
						    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
						    
						    StartCounter();
							quicksort(vet, 0, n);
							tempoEmMilissegundo = GetCounter();
							printf("\nALGORITMO ENTRADA ORDENADA");
						    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
						    
						    Inversa(vet, n);
							StartCounter();
							quicksort(vet, 0, n);
							tempoEmMilissegundo = GetCounter();
							printf("\nALGORITMO ENTRADA ORDEM INVERSA");
						    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
							
							free(elementos);
							free(vet);
							fclose(pont_arq);
							break;
						case 5:
							n=1000000;
							i=0;
							elementos=(int *)malloc(n*sizeof (int));
							vet=(int *)malloc(n*sizeof (int));
							pont_arq = fopen("C:\\Users\\Ana Clara\\Downloads\\aulapratica1 (1)\\aula_pratica_1\\entradas\\entrada1e+06.txt","r");
							do{
								fscanf(pont_arq, "%d", &elementos[i] );
								printf("%d\n" ,elementos[i]);
								k=elementos[i];
								vet[i]=k;
								i++;
							}while(i!=n);
			
							StartCounter();
							quicksort(vet, 0, n);
							tempoEmMilissegundo = GetCounter();
							printf("\nALGORITMO ENTRADA ALEATORIA");
						    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
						    
							StartCounter();
							quicksort(vet, 0, n);
							tempoEmMilissegundo = GetCounter();
							printf("\nALGORITMO ENTRADA ORDENADA");
						    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);
						    
							Inversa(vet, n);
							StartCounter();
							quicksort(vet, 0, n);
							tempoEmMilissegundo = GetCounter();
							printf("\nALGORITMO ENTRADA ORDEM INVERSA");
						    printf("\n Tempo = %.7lf milissegundos\n", tempoEmMilissegundo);			    
							
							free(elementos);
							free(vet);
							fclose(pont_arq);
							break;
						}
					break;
				}
				system("pause");
				system("cls");
 			}while(opcaoAlgoritmos!=0);
	
	return 0;
}
