#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct folha{
	int num;
	struct folha* esq;
	struct folha* dir;
};
/*A estrutura folha guarda uma informação e está linkada com 
duas folhas filhas*/

typedef struct folha Folha;

Folha* inicializa(){
	return NULL;
}

int ehVazia(Folha* f){
	return f == NULL ;
		
}

int busca(Folha* f, int num){
	if(ehVazia(f)){
		return 0;
	}else if(f->num == num){
		return 1;
	}else{
		int direcao = f->num < num;

		if(direcao){
			return busca(f->dir, num); 
			//printf("%d direita de %d \n", num, f->num);
		}else{
			return busca(f->esq, num);
			//printf("%d esquerda de %d \n", num, f->num);
		}
	}

}


Folha* cria(int num){
	Folha* f= (Folha*)malloc(sizeof(Folha));

	f->num = num;
	f->esq = inicializa();
	f->dir = inicializa();
	
	return f;
}

Folha* insere(Folha* f, int num){
	if(ehVazia(f)){
		f = cria(num);
		//printf("Raiz :%d\n", num);
	}else if(f->num == num){
		return f;
	}else{
		int direcao = f->num < num;

		if(direcao){
			f->dir = insere(f->dir, num); 
			//printf("%d direita de %d \n", num, f->num);
		}else{
			f->esq = insere(f->esq, num);
			//printf("%d esquerda de %d \n", num, f->num);
		}
	}
	return f;
}

Folha* retira(Folha* f, int num){

	if(f != NULL){
		int direcao;

		if(f->num == num){

			if(f->esq != NULL && f->dir != NULL){
				Folha* succ = f->dir;
				while(succ->esq != NULL)
					succ = succ->esq;

				num = succ->num;
				f->num = num;

			}else{
				//Folha* salva = f;

				if(f->esq == NULL){
					f = f->dir;
				}else{
					f = f->esq;
				}
				//free(salva);
				return f;
			}
		}
		if(f->num <= num){
			f->dir = retira(f->dir, num);
		}else{
			f->esq = retira(f->esq, num);
		}
	}

	return f;
}

void destruir(Folha* f){
	if(f != NULL){
		destruir(f->dir);
		destruir(f->esq);
		free(f);
	}
}

void imprime(Folha* f){
	if(f != NULL){
		printf("%d \n", f->num);
		imprime(f->dir);
		imprime(f->esq);		
	}
}

int main(){
	
 	int aux;
   	Folha* arvore;
   	srand(time(NULL));
   	for(int i =0; i< 15; i++){
   		aux = rand()%30;
   		printf("número escolhido: %d \n", aux);
   		arvore = insere(arvore, aux);
   } 
	printf("xxxxxxxxxxxx\n");
	printf("Arvore:\n");
   	imprime(arvore);
   	printf("xxxxxxxxxxxx\n");
	aux = rand()%10;
	printf("\nProcurar por: %d \n", aux);
	if(busca(arvore, aux)){
		printf("ACHEI!\n");
	}else{
		printf("O número não existe na árvore! \n");	
	}

	return 0;
}