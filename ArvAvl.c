#include "ArvAVL.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


struct arvno {  //Stuct ArvNo contém a informação, um ponteiro para o nó da esquerda e outro para o da direita, a altura das subárvores da esquerda e da direita 
    int info;
    ArvNo* esq;
    ArvNo* dir;
    int AltEsq;
    int AltDir;
};

struct arv{ //Struct que representa a árvore, contém o ponteiro para a raiz
    ArvNo* raiz;
};

Arv* avl_cria (void ){  //Função que cria a árvore

    Arv* a = (Arv*) malloc(sizeof (Arv));

    a-> raiz = NULL;

    return a;

}

static void imprime (ArvNo* r){  //Função que imprime as informações da árvore inteira

    if (r != NULL) {

        imprime(r-> esq);
        int x, y;
        if(r->dir==NULL) x=-1;
        else x=(r->dir)->info;
        if(r->esq==NULL) y=-1;
        else y=(r->esq)->info;
        printf("No: %d Direita:%d Esquerda:%d Altura direita:%d Altura esquerda:%d\n",r->info, x, y, r->AltDir, r->AltEsq);

        imprime(r-> dir);

    }

}

void avl_imprime (Arv* a){
    
    return imprime(a->raiz);

}

static ArvNo* busca (ArvNo* r, int v){  //Busca um elemento na árvore

    if (r == NULL) return NULL;

    else if (r-> info > v) return busca (r->esq , v);

    else if (r-> info < v) return busca (r->dir, v);

    else return r;

}

ArvNo* avl_busca (Arv* a, int v){

    return busca(a->raiz ,v);

}

ArvNo* rot_esq(ArvNo* r){  //Função que realiza a rotação esquerda
    ArvNo* p= r;
    ArvNo* Pdir= r->dir;

    p->dir=Pdir->esq;
    Pdir->esq=p;
    
    return Pdir;
}

ArvNo* rot_dir(ArvNo* r){  //Função que realiza a rotação direita
    ArvNo* p= r;
    ArvNo* Pesq= r->esq;

    p->esq=Pesq->dir;
    Pesq->dir=p;

    return Pesq;
}

ArvNo* rot_esqesq(ArvNo* r){  //Função que realiza a rotação esquerda dupla
    ArvNo* p= r;
    ArvNo* Pdir= r->dir;
    ArvNo* Pesqdir= Pdir->esq;
    p->dir = Pesqdir->esq;
    Pdir->esq = Pesqdir->dir;
    Pesqdir->dir= Pdir;
    Pesqdir->esq= p;

    return Pesqdir;
}

ArvNo* rot_dirdir(ArvNo* r){  //Função que realiza a rotação direita dupla
    ArvNo* p= r;
    ArvNo* Pesq= r->esq;
    ArvNo* Pdiresq= Pesq->dir;
    p->esq = Pdiresq->dir;
    Pesq->dir = Pdiresq->esq;
    Pdiresq->esq= Pesq;
    Pdiresq->dir= p;

    return Pdiresq;
}

int max (int a, int b) {  //Função que calcula o maior entre dois inteiros
        if (a>b) return a;
        return b;
}

int tamanhoSubArv (ArvNo* r) {  //Função que calcula o tamanho da subárvore de um  nó
    int k=0;  //Variável que armazena o tamanho
    if (r==NULL) return 0;
    k+=max(tamanhoSubArv(r->esq), tamanhoSubArv(r->dir))+1;
    return k;
}

static void Redefinir (ArvNo* r){  //Função que redefine os valores de AltDir e AltEsq em caso de mudanças para certo nó
    if (r != NULL) {
        Redefinir(r-> esq);  //Percorre sua subárvore da esquerda
        Redefinir(r-> dir);  //Percorre sua subárvore da direita
        r->AltEsq=tamanhoSubArv(r->esq);
        r->AltDir=tamanhoSubArv(r->dir);
    }
}

ArvNo* arv_Balancear(ArvNo* r, Arv* a){  //Função que balanceia um nó, caso necessário
  
    ArvNo* NoBal=r;  //NoBal é o onde será armazenado o nó após ser balanceado
    if((r->AltEsq)-(r->AltDir)>=2){  //Se a altura da esquerda for maior que a altura da direita por dois, realiza ou rotação direita ou dupla direita
       
        ArvNo* resq= r->esq;
        if((resq->AltDir)-(resq->AltEsq)>=1){  //Caso pese a sad mais que a sae da esquerda, realiza-se rotação dupla direita
           
            NoBal=rot_dirdir(r);
        }
        else NoBal=rot_dir(r);  //Se não, faz-se rotação direita
    }
    else if((r->AltDir)-(r->AltEsq)>=2){  //Se a altura da direita for maior que a altura da esquerda por dois, realiza ou rotação esquerda ou dupla esquerda
       
        ArvNo* rdir= r->dir;
        if((rdir->AltEsq)-(rdir->AltDir)>=1){  //Caso pese a sae mais que a sad da direita, realiza-se rotação dupla esquerda
       
            NoBal=rot_esqesq(r);
        }
        else NoBal=rot_esq(r);   //Se não, faz-se rotação esquerda
    }
    
    Redefinir(NoBal); //Redefine-se o novo nó balanceado
    
    return NoBal;

}

static ArvNo* insere (ArvNo* r, int v, Arv* a){  //Função que insere novo nó
    
    if (r == NULL) {
        
        r = (ArvNo*) malloc(sizeof (ArvNo ));
        r-> info = v;
        r-> esq = r-> dir = NULL;
        r->AltDir=0;
        r->AltEsq=0;
    }
    else if (v < r-> info){
       
        r-> esq = insere(r->esq ,v, a);
    }
    else{
        
        r-> dir = insere(r->dir,v , a);
    }    
  
    Redefinir(r); //Após a inserção, redefine-se a subárvore percorrida de forma recursiva
    
    r=arv_Balancear(r, a);  //Balanceia-se cada nó, caso necessário

    return r;
}

void avl_insere (Arv* a, int v){

    a-> raiz = insere(a->raiz ,v, a);
}

static ArvNo* retira (ArvNo* r, int v, Arv* a){  //Retira um nó da árvore

    if (r == NULL) return NULL;  //Se não encontra o nó, retorna nulo

    else if (r-> info > v){ 
        
        r-> esq = retira(r->esq , v, a);  //Se a informação do nó é maior que a informação desejada, percorre sae
    }
    else if (r-> info < v){ 
        
        r-> dir = retira(r->dir, v, a);  //Se for menor, percorre a sad
    }
    
    //Após encontrar o nó, existem 4 casos de remoção

    if (r-> esq == NULL && r-> dir == NULL) {  //Caso 1
        

        
        free (r);
        
        r = NULL;
        
    }
    else if (r-> esq == NULL) {  //Caso 2
        
        ArvNo* t = r;
        
        r = r-> dir;

        free (t);

    }

    else if (r-> dir == NULL) {  //Caso 3
        
        ArvNo* t = r;
        
        r = r-> esq;

        free (t);
        
    }

    else if(r->info==v && r->dir!=NULL && r->esq!=NULL){  //Caso 4
        
        ArvNo* f = r-> esq;

        while (f-> dir != NULL) {

            f = f-> dir;

        }

        r-> info = f-> info; // troca as informações
        
        f-> info = v;

        r-> esq = retira(r->esq ,v, a);
        
        Redefinir(r);  //Redefine após a remoção
        
        r=arv_Balancear(r, a);  //Balanceia após a remoção
        

    }
    else{  //Caso o nó avaliado não contenha o valor procurado para a remoção, realiza a redefinição e o balanceamento nesse nó
     
        Redefinir(r);
        
        r=arv_Balancear(r, a);
        
    }

    return r;

}

void avl_retira (Arv* a, int v){

    a-> raiz = retira(a->raiz ,v, a);

}

