#include <iostream>
#include <string>
#include <fstream>
#include "abb.hpp"
#define TAM 256

using namespace std;

template <typename T>
void inputToList (LUE <T> &lista, string phrase, int vetor[]) {
    for (int i = 0; i < phrase.length(); i++)
        if (phrase[i]!= '\0') vetor[int(phrase[i])]++;    // Incrementa 1 na tabela hash criada com a chave sendo o numero da tabela ASCII do char(letra)

    for (int i = 0; i < TAM; i++)
    {
        if (vetor[i] != 0)              // Se for diferente de 0, significa que tem uma frequencia e a letra esta na frase
        {
            No <T> *aux = new No <T>; // Crio novo no
            aux->info = char(i);     // Armazeno a letra
            aux->freq = vetor[i];   // e a frequencia da letra
            cout << "\tLetra: " << aux->info << "  ||  Frequencia: " << aux->freq << endl;
            inserirLUE(lista, aux);  // Alteramos a biblioteca concedida pelo professor para inserir por ondem de frequencia ao inves de info
            // tornando a insercao ordenada.
        }
    }
}

//imprimir tabela hash

void imprimir_tabela (int tabela[])
{
    for (int i=0; i < TAM; i++) // loop pelo vetor e mostra apenas as chaves que possuem frequencia
    {
        if (tabela[i] > 0)
            cout << "\t" << i << " = " << tabela[i] << " = " << char(i) << endl;
    }
}

template <typename T>
void comprimirBits (LUE <T> &lista)
{
    while (!(lista.comeco->elo == NULL || lista.comeco == NULL))
    {
        NoL <T> *auxOne = lista.comeco;                // usado para deletar o primeiro elemento da lista
        NoL <T> *auxTwo = lista.comeco->elo;          // usado para deletar o segundo elemento da lista
        No <T> *auxEsq = lista.comeco->infoL;        // usado para pegar 1 no da lista
        No <T> *auxDir = lista.comeco->elo->infoL;  // usado para pegar o no seguinte

        if (lista.comeco->elo->elo!=NULL) lista.comeco = lista.comeco->elo->elo; // se a lista tiver 3 elementos ou mais
        else lista.comeco = NULL;     // caso tiver apenas 2 elementos na lista para o loop

        delete auxOne;                 // deleta o primeiro elemento da lista
        delete auxTwo;                 // deleta o segundo, pois ambos viraram um no

        No <T> *auxThree = new No <T>;     // cria o no(raiz) que sera armazenado os 2 elementos da lista
        auxThree->freq = auxEsq->freq + auxDir->freq;     // soma as frequencias
        auxThree->info = '\0';                           // sem info apenas frequencia
        auxThree->esq = auxEsq;                         // 1 elemento da lista vira esquerda
        auxThree->dir = auxDir;                        // 2 elemento da lista vira o da direita (maior)

        inserirLUE(lista, auxThree);          //insere a raiz na lista de elementos
        cout << "\tProcesso de evolucao da lista abaixo, juntar 2 elementos menores e criar um novo No" << endl;
        mostrarLUE(lista);          // mostra o passa passo do elemento
        cout << endl;
    }
}

template <typename T>
bool caminholetra (No <T> *aux, char &letra, string &resultado)  //funcao para obter o caminho da raiz a letra
{
    if (aux == NULL) return false;                            // condicao de parada em no nulo
    if (noFolha(aux) && aux->info == letra) return true;  // se achar a letra return true

    if(caminholetra(aux->esq, letra, resultado))   // se o no esq retornar true soma 0 na string
    {
        resultado = "0" + resultado; return true;
    }
    if(caminholetra(aux->dir, letra, resultado))  // se o no dir retornar true soma 1 na string
    {
        resultado= "1" + resultado; return true;
    }
    return false;
}

template <typename T>
void resultadoFinal (No <T> *aux, string &frase, string &resultado) //recebe frase, e chama a funcao de caminhar letra a letra
{
    int i = 0;
    while(i < frase.length())
    {
        string caminho;
        if(frase[i]!= '\0') caminholetra(aux, frase[i], caminho);
        resultado += caminho;
        i++;
    }
}

template <typename T>
void descompressao (No <T> *raiz, string codigo, string &resultado)
{
    No <T> *aux = raiz;                                             //criacao de um auxiliar para ajudar a navegar
    for (int i=0; i < codigo.length(); i++)                        // loop for do tamanho da frase
    {
        if (codigo[i] == '1')                                   // se for 1 navega para direita
        {
            aux = aux->dir;
            if (noFolha(aux))                              //se chegar em um no folha salva o char e reseta raiz
            {
                resultado += aux->info;
                aux = raiz;
            }
        }
        if (codigo[i] == '0')                               // se for 0 navega para esquerda
        {
            aux = aux->esq;
            if (noFolha(aux))                           //se chegar em um no folha salva o char e reseta raiz
            {
                resultado += aux->info;
                aux = raiz;
            }
        }
    }
}

int main()
{
    LUE <char> lista;
    inicializarLUE(lista);

    char opcao;
    string frase;
    do {
        bool flag = false;
        while (!flag)
        {
            cout << "\tDeseja abrir um arquivo txt ou inserir sua frase?\n\n";
            cout << "\t(a) -> Arquivo" << endl;
            cout << "\t(b) -> Frase" << endl;
            cout << "\t(c) -> Sair\n" << endl;
            cout << "\tEscolha: ";
            cin >> opcao;

            system("cls");

            if (opcao == 'c' || opcao == 'C') break;

            else if (opcao == 'b' || opcao == 'B') {
                cin.ignore();
                cout << "\tInsira sua frase: ";
                getline(cin, frase);
                flag = true;
            }
            else if (opcao == 'a' || opcao == 'A') {
                string name;
                cout << "\tDigite o nome do arquivo a ser lido: ";
                cin >> name;
                ifstream arquivo;
                arquivo.open(name + ".txt");
                if(arquivo.is_open())
                {
                    //while (!arquivo.eof())    // Loop inconstante, deixamos documentado caso queira testar
                        getline(arquivo, frase);
                    arquivo.close();
                    flag = true;
                } else
                {
                    system("cls");
                    cout << "\tNao foi possivel abrir o arquivo.\n" << endl;
                    system("pause"); system("cls");
                }
            } else {
                system("cls");
                cout << "\tOpcao invalida. Tente novamente.\n" << endl;
                system("pause"); system("cls");
            }
        }

        if (opcao == 'c' || opcao == 'C') break;

        cout << endl;

        int vetorFreq[TAM] = {};
        cout << endl;

        inputToList(lista, frase, vetorFreq);
        cout << endl;

        cout << "\tTabela hash dos caracteres abaixo:" << endl << endl;
        imprimir_tabela(vetorFreq);

        cout << endl;
        comprimirBits(lista);
        cout << endl << "\tArvore abaixo:" << endl;

        mostrar_arvore(lista.comeco->infoL, contar(lista.comeco->infoL));
        cout << endl;

        string resultado = "";
        resultadoFinal(lista.comeco->infoL, frase, resultado);

        cout << "\n\tCompressao:\t" << resultado << endl;

        string descompress = "";
        descompressao(lista.comeco->infoL, resultado, descompress);
        cout << "\tDescompressao:\t" << descompress << endl;

        cout << endl;
        liberarLUE(lista);

        system("pause");
        system("cls");
    } while (opcao != 'c' || opcao != 'C');

    return 0;
}
