#include <iostream>

using namespace std;

template <typename T>
struct NoL {
    T info;
    NoL <T> *elo = NULL;
};

template <typename T>
struct LUE {
    NoL <T> *comeco = NULL;
    NoL <T> *fim = NULL;
};

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
void mostrarLUE (LUE <T> lista) {
    NoL <T> *aux = lista.comeco;

    while (aux != NULL) {
        cout << aux->info << " ";
        aux = aux->elo;
    }
    if (lista.comeco == NULL)  cout << "<Vazio>";
}

//
// Insere o valor na lista dada respeitando a ordem crescente
//
template <typename T>
bool inserirLUE (LUE <T> &lista, T valor) {
    NoL <T> *novo;

    // Criar o novo no
    novo = new NoL <T>;
    if (novo == NULL)  return false;
    novo->info = valor;
    novo->elo = NULL;

    // Lista vazia
    if (lista.comeco == NULL) {
        lista.comeco = novo;
        lista.fim = novo;
        return true;
    }

    // Inser��o no comeco
    if (valor < lista.comeco->info) {
        novo->elo = lista.comeco;
        lista.comeco = novo;
        return true;
    }

    // Inser��o no final
    if (valor > lista.fim->info) {
        lista.fim->elo = novo;
        lista.fim = novo;
        return true;
    }

    // Inserir no meio
    NoL <T> *aux = lista.comeco;
    while (aux->info < valor && aux->elo->info < valor)
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
    novo->info = valor;
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
        if (aux->info == valor) return aux;
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

    while (aux != NULL && aux->info != valor) {
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

