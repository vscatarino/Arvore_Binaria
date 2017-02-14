#include<stdio.h>
#include<stdlib.h>

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

/*int ehVazia(Folha* f){
	if(f == NULL)
		return 1;
}*/

int busca(Folha* f, int num){
	if(f == NULL){
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
	if(f == NULL){
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
	Folha* arvore;
	arvore = insere(arvore, 7);
	arvore = insere(arvore, 6);
	arvore = insere(arvore, 9);
	arvore = insere(arvore, 3);
	arvore = insere(arvore, 4);
	arvore = insere(arvore, 10);
	imprime(arvore);
	printf("\n\n");
	arvore = retira(arvore, 6);
	arvore = insere(arvore, 1);
	arvore = insere(arvore, 5);
	imprime(arvore);
	destruir(arvore);
	if(busca(arvore, 10)){
		printf("ACHEI! \n");
	}

	return 0;
}