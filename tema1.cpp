# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# define Nmax1 10
# define Nmax2 300
# define Nmax3 10000
typedef struct lista{
	int info;
	lista *urm;
}lista;

typedef struct arbore{
	int info;
	arbore *st;
	arbore *dr;
}arbore;
void afisare(int *v , int lungime){
	for(int i = 0 ; i < lungime ; i++)
		printf("%d ",v[i]);
	printf("\n");
}
void citire1(int *v , int lungime){
	for(int i = 0 ; i < lungime ; i++)
		v[i] = i;
}
void citire2(int *v , int lungime){
	srand(time(0));
	for(int i = 0 ; i < lungime ; i++)
		v[i] = rand()%100+1;
}
void citire3(int *v , int lungime){
	for(int i = 0 ; i < lungime ; i++)
		v[i] = lungime - i;
}

long Strand(int *v , int lungime){
	int sublist[lungime] , sortat[lungime] , aux[lungime] , last , i , j , k , indiceaux , indicesortat = -1  ;
	long contor = 0;
	//cat timp lungimea vectorului care trebuie sortat este mai mare decat 0 il vom sorta
	while( lungime > 0 ){
		//punem in sublista primul element din v apoi il stergem din v si scadem cu 1 unitate lungimea vectorului
		last = 0;
		sublist[last] = v[0];
		contor += 4;
		for( i = 0 ; i < lungime - 1; i++){
			v[i] = v[i+1];
			contor += 4;
		}
		lungime--;
		contor++;
		//Introducem elementele mai mari decat ultimul element introdus in sublist in vectorul sublist si apoi le stergem din v si micsoram lungimea
		for(i = 0 ; i < lungime ; i++){
			contor += 3;
			if( sublist[last] <= v[i] ){
				last++;
				sublist[last] = v[i];
				contor += 4;
				for(j = i ; j < lungime - 1 ; j++){
					v[j] = v[j+1];
					contor += 3;
				}
				lungime--;
				i--;
				contor += 2;
			}
		}
		indiceaux = 0;
		j = 0 ;//j ma ajuta sa parcurg vectorul sortat
		k = 0 ;//k ma ajuta sa parcurg vectorul sublist
		contor += 3;
		while( (indicesortat >= j) && (last >= k) ){
			contor += 3;
			if(sublist[k] < sortat[j]){
				aux[indiceaux++] = sublist[k++];
				contor += 5;
			}
			else {
				aux[indiceaux++] = sortat[j++];
				contor += 5;
			}
		}
		while( j <= indicesortat ){//in caz ca vectorul sortat are mai multe elemente decat sublist
				aux[indiceaux++] = sortat[j++];
				contor += 6;
		}
		while( k <= last ){//in caz ca vectorul sublist are mai multe elemente decat sortat
				aux[indiceaux++] = sublist[k++];
				contor += 6;
		}
		indicesortat = indiceaux - 1;
		contor++;
		for( j = 0 ; j <= indicesortat ; j++){
			sortat[j] = aux[j];
			contor += 3;
		}
	}
	for ( i = 0 ; i <= indicesortat ; i++){
		v[i] = sortat[i];
		contor += 3;
	}
	return contor;
}

long CocktailSort( int *v , int lungime ){
	int i , aux;
	long contor = 0;
	bool sortat ;
	do{
		sortat = true;
		contor ++;
		for( i = 0 ; i < lungime - 1 ; i++ ){
			if( v[i] > v[i+1] ){
				aux = v[i];
				v[i] = v[i+1];
				v[i+1] = aux;
				sortat = false;
				contor += 14;
			}
			contor++;
		}
		if( sortat == true )break;
		contor++;
		for(i = lungime - 2 ; i >= 0 ; i--){
			if( v[i] > v[i+1] ){
				aux = v[i];
				v[i] = v[i+1];
				v[i+1] = aux;
				sortat = false;
				contor += 14;
			}
			contor ++;
		}
		contor++;
	}while(sortat == false);
	return contor;
}

long RadixSort(int *v , int lungime , int nrMaxCifre){
 	int m = 10 , n = 1 , i , aux , indice;
	long contor = 0;
	lista *lst[10];
	while( m <= nrMaxCifre ){
		contor++;
		for(i = 0 ; i < 10 ; i++){
			lst[i] = NULL;
			contor += 2;
		}
		for( i = 0 ; i < lungime; i++ ){
			aux = ( v[i] % m ) / n;
			contor += 4;
			if(lst[aux] == NULL){
				lst[aux] = new lista;
				lst[aux]->info = v[i];
				lst[aux]->urm = NULL;
				contor += 9;
			}
			else{
				lista *auxx= new lista;//am luat un nou pinter cu care ma deplasez pentru a nu pierde inceputul listei
				auxx = lst[aux];
				contor += 3;
				while (auxx->urm != NULL){ 
					auxx = auxx -> urm;
					contor ++;
				}
				lista *c = new lista;//am luat un nou pointer cu care adaug in lista
				c->info = v[i];
				c->urm = NULL;
				auxx-> urm = c;
				contor += 5;
			}
		}
		indice = 0;
		contor++;
		for( i = 0 ; i < 10 ; i++ ){
			contor ++;
			if(lst[i] != NULL){
				contor += 2;
				while(lst[i] != NULL){
					v[indice++] = lst[i]->info ;
					lst[i]=lst[i]->urm;
					contor += 8;
				}
			}
		}
		n = m;
		m = m * 10;
		contor += 2;
	}
return contor;
}

void adaugareArbore(arbore *& arb , int x ,long &contor){
	if(arb == NULL){
		arb = new arbore;
		arb->st = NULL;
		arb->dr = NULL;
		arb->info = x;
		contor += 4;
	}
	else if(arb->info <= x){
		contor++;
		adaugareArbore(arb->dr , x , contor);//daca x este mai mic decat informatia din nodul curent incercam sa-l punem pe x in subarborele stang al nodului curent
	}
		else{ 
			adaugareArbore(arb->st , x , contor);//daca x este mai mare decat informatia din nodul curent incercam sa-l punem pe x in subarborele drept al nodului curent
			contor++;
		}
}

void SuprascrieV(arbore *arb , int *v , int &indice , long &contor){
	//parcurgem subarborele stang pana la ultimul nod
	if(arb->st != NULL){ 
		contor++;
		SuprascrieV(arb->st , v , indice , contor);
	}
	indice++;
	v[indice] = arb->info;//punem in v elementele
	contor += 3;
	if(arb->dr != NULL){
		contor++;
		SuprascrieV(arb->dr , v , indice , contor);// parcurgem subarborele drept pana la ultimul nod
	}
}

long BinaryTrees(int *v , int lungime){
	int i ;
	arbore *arb;
	arb = NULL;
	long contor = 0 , contor2 = 0 , contor3 = 0;
	for(i = 0 ; i < lungime ; i++){
		contor ++;
		adaugareArbore(arb,v[i],contor2);//adaugam in arbore elemente din vector
		contor += contor2;
	}
	i = -1;//pentru a putea creea vectorul avem nevoie de o variabila pe care o vom trimite prin referinta functiei SuprascriereV,aceasta variabila este indexul vectorului
	contor ++;
	SuprascrieV(arb , v , i ,contor3);//Suprascriem vectorul v punand in el elementele din arbore astfel incat vectorul sa fie sortat
	contor += contor3;
	return contor ;
}

void verificareH2(int heap[],int parinte,int lungime , long &contor){
	int copil1 = parinte*2+1;
	int copil2 = parinte*2+2;
	int max , indmax , aux;
	contor += 6;
	//verificam cati copii are parintele
	//parintele are 2 copii
	if(copil1 <= lungime && copil2 <= lungime){
		contor += 3;
		//cautam maximul dintre cei 2 copii si il retinem in max si indicele il retinem in indmax
		if(heap[copil1] >= heap[copil2]){
			max = heap[copil1];
			indmax = copil1;
			contor += 6;
		}
			else {
				max = heap[copil2];
				indmax = copil2;
				contor += 6;
			}
	//daca parintele este mai mic decat max interschimbam cele 2 valori si repetam verifacareH2 pentru heap[] si indmax
		if(heap[parinte] < max){
			aux = max;
			heap[indmax] = heap[parinte];
			heap[parinte] = max;
			contor += 8;
			verificareH2(heap,indmax,lungime,contor);
		}
	}
	//parintele are 1 copil.Daca parintele are 1 copil inseamna ca acel copil este ultimul element din vector.
	else if (copil1 <= lungime && copil2 > lungime){
		contor += 3;
		if (heap[parinte] < heap[copil1]){
			aux = heap[copil1];
			heap[copil1] = heap[parinte];
			heap[parinte] = aux;
			contor += 10;
		}
	}
}

long HeapSort(int *v , int lungime){
	int heap[lungime] , i , aux , j , heap2[lungime];
	long contor = 0 , contor2 = 0 , contor3 = 0;
// in vectorul heap2 vom adauga elemente mereu la inceputul vectorului
	for(i = 0 ; i < lungime ; i++){
		for(j = i ; j > 0 ; j--){
			heap2[j] = heap2[j-1];
			contor += 4;
		}
		heap2[0] = v[i];
		contor += 3;
		verificareH2(heap2 , 0 , i , contor2);//verificam daca dupa ce adaugam elementul v[i] se respecta conditiile heapului
		contor += contor2;
	} 
	i = lungime - 1 ;
	contor += 2;
	while(i >= 0){
		v[i] = heap2[0];
		i--;
		heap2[0] = heap2[lungime - 1];
		lungime--;
		contor += 9;
		verificareH2(heap2 , 0 , lungime , contor3);
		contor += contor3;
	}
	return contor;
}
int main(){
	int i , *v1, *v2, *v3 , mod;
	long contor;
	v1 = (int*) malloc (Nmax1*sizeof(int));
	v2 = (int*) malloc (Nmax2*sizeof(int));
	v3 = (int*) malloc (Nmax3*sizeof(int));
	printf("Alegeti modul de lucru\n Introduceti 1 sau 2\n 	1:Modul de testare\n	2:Modul de analiza\n");
	scanf("%d",&mod);
	if ( mod != 1 && mod != 2 )return 0;
		else if ( mod == 1 ){
			printf("\n\nSortarea unor vectori cu elemnte generate aleator:\n");
			
			//Sortarea Strand
			citire2(v1,Nmax1);
			printf("Vectorul inainte de sortare:");
			afisare(v1,Nmax1);
			contor = Strand(v1,Nmax1);
			printf("Vectorul dupa sortarea Strand:");
			afisare(v1,Nmax1);
			printf("Numarul de operatii = %d", contor);
			printf("\n\n");
	
			//sortarea CocktailSort
			citire2(v1,Nmax1);
			printf("Vectorul inainte de sortare:");
			afisare(v1,Nmax1);
			printf("Vectorul dupa sortarea CocktailSort:");
			contor = CocktailSort(v1,Nmax1);
			afisare(v1,Nmax1);
			printf("Numarul de operatii = %d", contor);
			printf("\n\n");
	
			//Sortarea Radix Sort
			citire2(v1,Nmax1);
			printf("Vectorul inainte de sortare:");
			afisare(v1,Nmax1);
			printf("Vectorul dupa sortarea RadixSort:");
			contor = RadixSort(v1,Nmax1,100);
			afisare(v1,Nmax1);
			printf("Numarul de operatii = %d", contor);
			printf("\n\n");
	
			//Sortarea BinaryTrees
			citire2(v1,Nmax1);
			printf("Vectorul inainte de sortare:");
			afisare(v1,Nmax1);
			printf("Vectorul dupa sortarea BinaryTrees:");
			contor = BinaryTrees(v1,Nmax1);
			afisare(v1,Nmax1);
			printf("Numarul de operatii = %d", contor);
			printf("\n\n");
	
			//Sortarea HeapSort
			citire2(v1,Nmax1);
			printf("Vectorul inainte de sortare:");
			afisare(v1,Nmax1);
			printf("Vectorul dupa sortarea HeapSort:");
			contor = HeapSort(v1,Nmax1);
			afisare(v1,Nmax1);
			printf("Numarul de operatii = %d", contor);
			printf("\n\n");
			return 0;
		}
		else if (mod == 2){
			//Fiecare vector este sortat crescator cu elemente de la 0 la Nmax
			printf("Sortarea unor vectori gata sortati:\n");
			citire1(v1,Nmax1);
			citire1(v2,Nmax2);
			citire1(v3,Nmax3);
			//Strand pentru 10 elemente
			contor = Strand(v1,Nmax1);
			printf("Numarul de operatii pentru sortarea unui vector cu 10 elemennte cu  Strand = %d\n\n",contor);
			
			//Cocktail Sort pentru 10 elemente
			contor = CocktailSort(v1,Nmax1);
			printf("Numarul de operatii pentru sortarea unui vector cu 10 elemennte cu  CocktailSort = %d\n\n",contor);
			
			//RadixSort pentru 10 elemente
			contor = RadixSort(v1,Nmax1,100);
			printf("Numarul de operatii pentru sortarea unui vector cu 10 elemennte cu  RadixSort = %d\n\n",contor);
			
			//Binary Tree pentru 10 elemente
			contor = BinaryTrees(v1,Nmax1);
			printf("Numarul de operatii pentru sortarea unui vector cu 10 elemennte cu  BinaryTrees = %d\n\n",contor);
			
			//Heap Sort pentru 10 elemente
			contor = HeapSort(v1,Nmax1);
			printf("Numarul de operatii pentru sortarea unui vector cu 10 elemennte cu  HeapSort = %d\n\n",contor);
	
			//Strand pentru 300 elemente
			contor = Strand(v2,Nmax2);
			printf("Numarul de operatii pentru sortarea unui vector cu 300 elemennte cu  Strand = %d\n\n",contor);
			
			//Cocktail Sort pentru 300 elemente
			contor = CocktailSort(v2,Nmax2);
			printf("Numarul de operatii pentru sortarea unui vector cu 300 elemennte cu  CocktailSort = %d\n\n",contor);
			
			//RadixSort pentru 300 elemente
			contor = RadixSort(v2,Nmax2,100);
			printf("Numarul de operatii pentru sortarea unui vector cu 300 elemennte cu  RadixSort = %d\n\n",contor);
			
			//Binary Tree pentru 300 elemente
			contor = BinaryTrees(v2,Nmax2);
			printf("Numarul de operatii pentru sortarea unui vector  cu 300 elemennte cu  BinaryTrees = %d\n\n",contor);
			
			//Heap Sort pentru 300 elemente
			contor = HeapSort(v2,Nmax2);
			printf("Numarul de operatii pentru sortarea unui vector cu 300 elemennte cu  HeapSort = %d\n\n",contor);
			
			//Strand pentru 300 elemente
			contor = Strand(v2,Nmax2);
			printf("Numarul de operatii pentru sortarea unui vector cu 10000 elemennte cu  Strand = %d\n\n",contor);
			
			//Cocktail Sort pentru 10000 elemente
			contor = CocktailSort(v3,Nmax3);
			printf("Numarul de operatii pentru sortarea unui vector cu 10000 elemennte cu  CocktailSort = %d\n\n",contor);
			
			//RadixSort pentru 10000 elemente
			contor = RadixSort(v3,Nmax3,100);
			printf("Numarul de operatii pentru sortarea unui vector cu 10000 elemennte cu  RadixSort = %d\n\n",contor);
			
			//Binary Tree pentru 10000 elemente
			contor = BinaryTrees(v3,Nmax3);
			printf("Numarul de operatii pentru sortarea unui vector cu 10000 elemennte cu  BinaryTrees = %d\n\n",contor);
			
			//Heap Sort pentru 10000 elemente
			contor = HeapSort(v3,Nmax3);
			printf("Numarul de operatii pentru sortarea unui vector cu 10000 elemennte cu  HeapSort = %d\n\n",contor);
			
			
			printf("\n\nSortarea unor vectori cu elemente aleatorii:\n");
			citire2(v1,Nmax1);
			contor = Strand(v1,Nmax1);
			printf("Numarul de operatii pentru sortarea unui vector cu 10 elemennte cu  Strand = %d\n\n",contor);
			
			//Sortarea Cocktail sort pentru 10 elemente
			citire2(v1,Nmax1);
			contor = CocktailSort(v1,Nmax1);
			printf("Numarul de operatii pentru sortarea unui vector cu 10 elemennte cu  CocktailSort = %d\n\n",contor);
			
			//Sortarea RadixSort pentru 10 elemente 
			citire2(v1,Nmax1);
			contor = RadixSort(v1,Nmax1,100);
			printf("Numarul de operatii pentru sortarea unui vector cu 10 elemennte cu  RadixSort = %d\n\n",contor);
			
			//Sortarea BinaryTrees pentru 10 elemente
			citire2(v1,Nmax1);
			contor = BinaryTrees(v1,Nmax1);
			printf("Numarul de operatii pentru sortarea unui vector cu 10 elemennte cu  BinaryTrees = %d\n\n",contor);
			
			//Sortarea HeapSort pentru 10 elemente
			citire2(v1,Nmax1);
			contor = HeapSort(v1,Nmax1);
			printf("Numarul de operatii pentru sortarea unui vector cu 10 elemennte cu  HeapSort = %d\n\n",contor);
			
			//Sortarea Strand 300 elemente
			citire2(v2,Nmax2);
			contor = Strand(v2,Nmax2);
			printf("Numarul de operatii pentru sortarea unui vector cu 300 elemennte cu  Strand = %d\n\n",contor);
			
			//Sortarea Cocktail sort pentru 300 elemente
			citire2(v2,Nmax2);
			contor = CocktailSort(v2,Nmax2);
			printf("Numarul de operatii pentru sortarea unui vector cu 300 elemennte cu  CocktailSort = %d\n\n",contor);
			
			//Sortarea RadixSort pentru 300 elemente 
			citire2(v2,Nmax2);
			contor = RadixSort(v2,Nmax2,100);
			printf("Numarul de operatii pentru sortarea unui vector cu 300 elemennte cu  RadixSort = %d\n\n",contor);
			
			//Sortarea BinaryTrees pentru 300 elemente
			citire2(v2,Nmax2);
			contor = BinaryTrees(v2,Nmax2);
			printf("Numarul de operatii pentru sortarea unui vector cu 300 elemennte cu  BinaryTrees = %d\n\n",contor);
			
			//Sortarea HeapSort pentru 300 elemente
			citire2(v2,Nmax2);
			contor = HeapSort(v2,Nmax2);
			printf("Numarul de operatii pentru sortarea unui vector cu 300 elemennte cu  HeapSort = %d\n\n",contor);
			
			//Sortarea Strand 10000 elemente
			citire2(v3,Nmax3);
			contor = Strand(v3,Nmax3);
			printf("Numarul de operatii pentru sortarea unui vector cu 10000 elemennte cu  Strand = %d\n\n",contor);
			
			//Sortarea Cocktail sort pentru 10000 elemente
			citire2(v3,Nmax3);
			contor = CocktailSort(v3,Nmax3);
			printf("Numarul de operatii pentru sortarea unui vector cu 10000 elemennte cu  CocktailSort = %d\n\n",contor);
			
			//Sortarea RadixSort pentru 10000 elemente 
			citire2(v3,Nmax3);
			contor = RadixSort(v3,Nmax3,100);
			printf("Numarul de operatii pentru sortarea unui vector cu 10000 elemennte cu  RadixSort = %d\n\n",contor);
			
			//Sortarea BinaryTrees pentru 10000 elemente
			citire2(v3,Nmax3);
			contor = BinaryTrees(v3,Nmax3);
			printf("Numarul de operatii pentru sortarea unui vector cu 10000 elemennte cu  BinaryTrees = %d\n\n",contor);
			
			//Sortarea HeapSort pentru 10000 elemente
			citire2(v3,Nmax3);
			contor = HeapSort(v3,Nmax3);
			printf("Numarul de operatii pentru sortarea unui vector cu 10000 elemennte cu  HeapSort = %d\n\n",contor);
			
			
			
			
			//Fiecare vector este sortat descrescator cu elemente de la Nmax pana la 1
			//Sortarea Strand 10 elemente
			printf("\n\nSortarea unor vectori sortati descrescatori:\n");
			citire3(v1,Nmax1);
			contor = Strand(v1,Nmax1);
			printf("Numarul de operatii pentru sortarea unui vector cu 10 elemennte cu  Strand = %d\n\n",contor);
			
			//Sortarea Cocktail sort pentru 10 elemente
			citire3(v1,Nmax1);
			contor = CocktailSort(v1,Nmax1);
			printf("Numarul de operatii pentru sortarea unui vector cu 10 elemennte cu  CocktailSort = %d\n\n",contor);
			
			//Sortarea RadixSort pentru 10 elemente 
			citire3(v1,Nmax1);
			contor = RadixSort(v1,Nmax1,100);
			printf("Numarul de operatii pentru sortarea unui vector sortat 10 elemennte cu  RadixSort = %d\n\n",contor);
			
			//Sortarea BinaryTrees pentru 10 elemente
			citire3(v1,Nmax1);
			contor = BinaryTrees(v1,Nmax1);
			printf("Numarul de operatii pentru sortarea unui vector cu 10 elemennte cu  BinaryTrees = %d\n\n",contor);
			
			//Sortarea HeapSort pentru 10 elemente
			citire3(v1,Nmax1);
			contor = HeapSort(v1,Nmax1);
			printf("Numarul de operatii pentru sortarea unui vector cu 10 elemennte cu  HeapSort = %d\n\n",contor);
			
			//Sortarea Strand 300 elemente
			citire3(v2,Nmax2);
			contor = Strand(v2,Nmax2);
			printf("Numarul de operatii pentru sortarea unui vector cu 300 elemennte cu  Strand = %d\n\n",contor);
			
			//Sortarea Cocktail sort pentru 300 elemente
			citire3(v2,Nmax2);
			contor = CocktailSort(v2,Nmax2);
			printf("Numarul de operatii pentru sortarea unui vector cu 300 elemennte cu  CocktailSort = %d\n\n",contor);
			
			//Sortarea RadixSort pentru 300 elemente 
			citire3(v2,Nmax2);
			contor = RadixSort(v2,Nmax2,100);
			printf("Numarul de operatii pentru sortarea unui vector cu 300 elemennte cu  RadixSort = %d\n\n",contor);
			
			//Sortarea BinaryTrees pentru 300 elemente
			citire3(v2,Nmax2);
			contor = BinaryTrees(v2,Nmax2);
			printf("Numarul de operatii pentru sortarea unui vector cu 300 elemennte cu  BinaryTrees = %d\n\n",contor);
			
			//Sortarea HeapSort pentru 300 elemente
			citire3(v2,Nmax2);
			contor = HeapSort(v2,Nmax2);
			printf("Numarul de operatii pentru sortarea unui vector cu 300 elemennte cu  HeapSort = %d\n\n",contor);
			
			//Sortarea Strand 10000 elemente
			citire3(v3,Nmax3);
			contor = Strand(v3,Nmax3);
			printf("Numarul de operatii pentru sortarea unui vector  cu 10000 elemennte cu  Strand = %d\n\n",contor);
			
			//Sortarea Cocktail sort pentru 10000 elemente
			citire3(v3,Nmax3);
			contor = CocktailSort(v3,Nmax3);
			printf("Numarul de operatii pentru sortarea unui vector cu 10000 elemennte cu  CocktailSort = %d\n\n",contor);
			
			//Sortarea RadixSort pentru 10000 elemente 
			citire3(v3,Nmax3);
			contor = RadixSort(v3,Nmax3,100);
			printf("Numarul de operatii pentru sortarea unui vector  cu 10000 elemennte cu  RadixSort = %d\n\n",contor);
			
			//Sortarea BinaryTrees pentru 10000 elemente
			citire3(v3,Nmax3);
			contor = BinaryTrees(v3,Nmax3);
			printf("Numarul de operatii pentru sortarea unui vector cu 10000 elemennte cu  BinaryTrees = %d\n\n",contor);
			
			//Sortarea HeapSort pentru 10000 elemente
			citire3(v3,Nmax3);
			contor = HeapSort(v3,Nmax3);
			printf("Numarul de operatii pentru sortarea unui vector cu 10000 elemennte cu  HeapSort = %d\n\n",contor);
			return 0;
		}
}