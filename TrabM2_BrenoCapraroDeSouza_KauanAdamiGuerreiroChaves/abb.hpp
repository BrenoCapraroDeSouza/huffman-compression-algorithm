#include <iostream>

using namespace std;

template <typename T>
struct No {
    T info;
    int freq = 0;
    string code = "";
    No <T> *esq = NULL, *dir = NULL;
};

template <typename T>
struct NoL {
    No <T> *infoL = NULL;
    NoL <T> *elo = NULL;
};

template <typename T>
struct LUE {
    NoL <T> *comeco = NULL;
    NoL <T> *fim = NULL;
};

template <typename T>
bool inserir (No <T> *&raiz, T valor, int bitEsqDir = 0) {
    if (raiz == NULL) {
        raiz = new No <T>;
        raiz->info = valor;
        raiz->bitEsqDir = bitEsqDir;
        return true;
    }
    if (raiz->info == valor) return false;
    if (valor < raiz->info)
        return inserir(raiz->esq, valor);
    else
        return inserir(raiz->dir, valor, 1);
}

template <typename T>
T buscar_maior (No <T> *raiz) {
    if (raiz->dir != NULL)
        return buscar_maior(raiz->dir);
    else
        return raiz->info;
}

template <typename T>
bool retirar (No <T> *&raiz, T valor) {
    if (raiz == NULL) return false;
    if (raiz->info == valor) {
        No <T> *aux = raiz;
        if (raiz->esq == NULL && raiz->dir == NULL) { // Caso A
            raiz = NULL;
            delete aux;
            return true;
        }
        if (raiz->esq == NULL && raiz->dir != NULL) { // Caso B - parte I
            raiz = raiz->dir;
            delete aux;
            return true;
        }
        if (raiz->esq != NULL && raiz->dir == NULL) { // Caso B - parte II
            raiz = raiz->esq;
            delete aux;
            return true;
        }
        // caso C
        T info_aux = buscar_maior(raiz->esq);
        raiz->info = info_aux;
        return retirar(raiz->esq, info_aux);
    }
    if (valor < raiz->info)
        return retirar(raiz->esq, valor);
    else
        return retirar(raiz->dir, valor);
}

template <typename T>
void prefixado (No <T> *raiz) {
    if (raiz == NULL) return;
    cout << raiz->info << " ";
    prefixado(raiz->esq);
    prefixado(raiz->dir);
}

template <typename T>
void infixado (No <T> *raiz) {
    if (raiz == NULL) return;
    infixado(raiz->esq);
    cout << raiz->info << " ";
    infixado(raiz->dir);
}

template <typename T>
void posfixado (No <T> *raiz) {
    if (raiz == NULL) return;
    posfixado(raiz->esq);
    posfixado(raiz->dir);
    cout << raiz->info << " ";
}

template <typename T>
void liberar (No <T> *raiz) {
    if (raiz == NULL) return;
    liberar(raiz->esq);
    liberar(raiz->dir);
    delete raiz;
}

template <typename T>
bool pesquisar (No <T> *raiz, T valor) {
    if (raiz == NULL) return false;
    if (raiz->info == valor) return true;
    if (valor < raiz->info)
        return pesquisar(raiz->esq, valor);
    else
        return pesquisar(raiz->dir, valor);
}

template <typename T>
int contar (No <T> *raiz) {
    if (raiz == NULL) return 0;
    return 1 + contar(raiz->esq) + contar(raiz->dir);
}

template <typename T>
int altura (No <T> *raiz) {
    if (raiz == NULL) return 0;
    int altE = altura(raiz->esq);
    int altD = altura(raiz->dir);
    return (altE > altD) ? altE + 1 : altD + 1;
}

template <typename T>
void mostrar_arvore (No <T> *raiz, int tab) {
    cout << endl;
    for(int i = 0; i < tab; i++)  cout << " ";
    if (raiz == NULL) {
        cout << "*";
        return;
    }
    cout << raiz->info << "(" << raiz->freq << ")";
    mostrar_arvore(raiz->esq, tab + 3) ;
    mostrar_arvore(raiz->dir, tab + 3) ;
}
template <typename T>
bool noFolha(No <T> *no)
{
    return (no->esq == NULL && no->dir == NULL) ? true : false;
}
//
// Inicializa a lista dada por par�metro
//
template <typename T>
void inicializarLUE (LUE <T> &lista) {
    lista.comeco = NULL;
    lista.fim = NULL;
}

//
// Mostra todo o conte�do da lista na tela
//
template <typename T>
void mostrarLUE(LUE <T> lista){
    NoL <T> *aux = lista.comeco;

    while(aux != NULL){
        cout << aux->infoL->info << "(" << aux->infoL->freq << ")" << " ";
        aux = aux->elo;
    }
    if( lista.comeco == NULL ) cout << "<Vazio>";
}

//
// Insere o valor na lista dada respeitando a ordem crescente
//
template <typename T>
bool inserirLUE(LUE <T> &lista, No <T> *valor){
    NoL <T> *novo;

    // Criar o novo NoL
    novo = new NoL<T>;
    if (novo == NULL) return false;
    novo->infoL = valor;
    novo->elo = NULL;

    // Lista vazia
    if (lista.comeco  == NULL) {
        lista.comeco = novo;
        lista.fim = novo;
        return true;
    }

    // Inserção no comeco
    if (valor->freq <= lista.comeco->infoL->freq) {
        novo->elo = lista.comeco;
        lista.comeco = novo;
        return true;
    }

    // Inserção no final
    if (valor->freq >= lista.fim->infoL->freq) {
        lista.fim->elo = novo;
        lista.fim = novo;
        return true;
    }

    // Inserção no meio
    NoL <T> *aux = lista.comeco;
    while (aux->infoL->freq < valor->freq && aux->elo->infoL->freq <= valor->freq)
        aux = aux->elo;

    novo->elo = aux->elo;
    aux->elo = novo;
    return true;
}

//
// Insere o valor dado sempre no final da lista
//
template <typename T>
bool inserirFinalLUE(LUE <T> &lista, T valor){
    NoL <T> *novo;

    // Criar o novo no
    novo = new NoL <T>;
    if (novo == NULL)  return false;
    novo->infoL = valor;
    novo->elo = NULL;

    // Lista vazia
    if (lista.comeco == NULL) {
        lista.comeco = novo;
        lista.fim = novo;
        return true;
    }

    lista.fim->elo = novo;
    lista.fim = novo;
    return true;
}

//
// Pesquisar se o valor est� na lista
// retornar o endere�o do valor ou nulo se n�o estiver
//
template <typename T>
NoL <T> * pesquisarLUE(LUE <T> lista, T valor){
    NoL <T> *aux = lista.comeco;

    while (aux != NULL) {
        if (aux->infoL == valor) return aux;
        aux = aux->elo;
    }
    return NULL;
}

//
// Retirar o valor da lista
// retornar verdadeiro ou false se n�o achar
//
template <typename T>
bool retirarLUE(LUE <T> &lista, T valor) {
    NoL <T> *aux = lista.comeco, *anterior=NULL;

    while (aux != NULL && aux->infoL != valor) {
        anterior = aux;
        aux = aux->elo;
    }
    if (aux == NULL) return false;

    if (aux == lista.comeco) { // Casos 1 e 2
        lista.comeco = lista.comeco->elo;
        if (aux == lista.fim) lista.fim = NULL;
    } else { // Casos 3 e 4
        anterior->elo = aux->elo;
        if (aux == lista.fim) lista.fim = anterior;
    }
    delete aux;
    return true;
}

//
// Libera toda a mem�ria alocada para a lista fornecida
//
template <typename T>
void liberarLUE (LUE <T> &lista) {
    NoL <T> *aux = lista.comeco;
    NoL <T> *aux2;

    while (aux != NULL) {
        aux2 = aux->elo;
        delete aux;
        aux = aux2;
    }
}
