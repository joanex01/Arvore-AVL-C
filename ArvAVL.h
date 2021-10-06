#ifndef ARVAVL_H
#define ARVAVL_H


typedef struct arvno ArvNo;
typedef struct arv Arv;
static void imprime (ArvNo* r);
void avl_imprime (Arv* a);
static ArvNo* busca (ArvNo* r, int v);
ArvNo* avl_busca (Arv* a, int v);
Arv* avl_cria (void );
static ArvNo* insere (ArvNo* r, int v, Arv*);
void avl_insere (Arv* a, int v);
static ArvNo* retira (ArvNo* r, int v, Arv* a);
void avl_retira (Arv* a, int v);
ArvNo* arv_Balancear(ArvNo* r, Arv* a);
ArvNo* rot_esq(ArvNo* r);
ArvNo* rot_dir(ArvNo* r);
ArvNo* rot_esqesq(ArvNo* r);
ArvNo* rot_dirdir(ArvNo* r);


#endif