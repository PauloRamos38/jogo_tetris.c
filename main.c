// Nível Novato - Fila Circular de Peças de Tetris 
// Nível Aventureiro - Fila e Pilha de Peças de Tetris
//N´vel Mestre - Fila e Pilha com Troca de Peças
//Autor: Paulo Ramos
//Data: 20/09/2024  
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ========================================
// DEFINIÇÕES
// ========================================

#define TAM_FILA 5
#define TAM_PILHA 3

// ========================================
// STRUCT DA PEÇA
// ========================================

typedef struct {
    char nome; // Tipo da peça
    int id;    // Identificador único
} Peca;

// ========================================
// STRUCT DA PILHA
// ========================================

typedef struct {

    Peca itens[TAM_PILHA];
    int topo;

} Pilha;

// ========================================
// STRUCT DA FILA CIRCULAR
// ========================================

typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// ========================================
// VARIÁVEL GLOBAL PARA IDs
// ========================================

int proximoID = 0;

// ========================================
// FUNÇÃO: gerarPeca
// Gera automaticamente uma nova peça
// ========================================

Peca gerarPeca() {

    char tipos[] = {'I', 'O', 'T', 'L'};
    
    Peca novaPeca;

    novaPeca.nome = tipos[rand() % 4];
    novaPeca.id = proximoID++;

    return novaPeca;
}

// ========================================
// FUNÇÃO: inicializarFila
// Inicializa os dados da fila
// ========================================

void inicializarFila(Fila *fila) {

    fila->inicio = 0;
    fila->fim = 0;
    fila->quantidade = 0;
}
// ========================================
// FUNÇÃO: inicializarPilha
// ========================================

void inicializarPilha(Pilha *pilha) {

    pilha->topo = -1;
}

// ========================================
// FUNÇÃO: filaCheia
// Verifica se a fila está cheia
// ========================================

int filaCheia(Fila *fila) {

    return fila->quantidade == TAM_FILA;
}
// ========================================
// FUNÇÃO: pilhaCheia
// ========================================

int pilhaCheia(Pilha *pilha) {

    return pilha->topo == TAM_PILHA - 1;
}
// ========================================
// FUNÇÃO: filaVazia
// Verifica se a fila está vazia
// ========================================

int filaVazia(Fila *fila) {

    return fila->quantidade == 0;
}
// ========================================
// FUNÇÃO: pilhaVazia
// ========================================

int pilhaVazia(Pilha *pilha) {

    return pilha->topo == -1;
}
// ========================================
// FUNÇÃO: push
// Insere peça na pilha
// ========================================

void push(Pilha *pilha, Peca peca) {

    if (pilhaCheia(pilha)) {

        printf("\nPilha cheia!\n");
        return;
    }

    pilha->topo++;

    pilha->itens[pilha->topo] = peca;
}
// ========================================
// FUNÇÃO: pop
// Remove peça do topo da pilha
// ========================================

Peca pop(Pilha *pilha) {

    Peca removida = pilha->itens[pilha->topo];

    pilha->topo--;

    return removida;
}
// ========================================
// FUNÇÃO: mostrarPilha
// ========================================

void mostrarPilha(Pilha *pilha) {

    printf("\nPilha de Reserva (Topo -> Base): ");

    if (pilhaVazia(pilha)) {

        printf("Vazia");
    }

    for (int i = pilha->topo; i >= 0; i--) {

        printf("[%c %d] ",
               pilha->itens[i].nome,
               pilha->itens[i].id);
    }

    printf("\n");
}
// ========================================
// FUNÇÃO: enqueue
// Insere peça no final da fila
// ========================================

void enqueue(Fila *fila, Peca peca) {

    if (filaCheia(fila)) {

        printf("\nFila cheia! Nao e possivel inserir.\n");
        return;
    }

    fila->itens[fila->fim] = peca;

    fila->fim = (fila->fim + 1) % TAM_FILA;

    fila->quantidade++;
}

// ========================================
// FUNÇÃO: dequeue
// Remove peça da frente da fila
// ========================================

Peca dequeue(Fila *fila) {

    Peca removida = fila->itens[fila->inicio];

    fila->inicio = (fila->inicio + 1) % TAM_FILA;

    fila->quantidade--;

    return removida;
}

// ========================================
// FUNÇÃO: exibirFila
// Mostra o estado atual da fila
// ========================================

void exibirFila(Fila *fila) {

    printf("\nFila de Pecas: ");

    int indice = fila->inicio;

    for (int i = 0; i < fila->quantidade; i++) {

        printf("[%c %d] ",
               fila->itens[indice].nome,
               fila->itens[indice].id);

        indice = (indice + 1) % TAM_FILA;
    }

    printf("\n");
}

// ========================================
// FUNÇÃO: trocarTopo
// Troca a frente da fila com o topo da pilha
// ========================================

void trocarTopo(Fila *fila, Pilha *pilha) {

    if (filaVazia(fila)) {

        printf("\nFila vazia!\n");
        return;
    }

    if (pilhaVazia(pilha)) {

        printf("\nPilha vazia!\n");
        return;
    }

    Peca temp;

    temp = fila->itens[fila->inicio];

    fila->itens[fila->inicio] =
        pilha->itens[pilha->topo];

    pilha->itens[pilha->topo] = temp;

    printf("\nTroca realizada com sucesso!\n");
}
// ========================================
// FUNÇÃO: trocarTres
// Troca os 3 primeiros da fila com a pilha
// ========================================

void trocarTres(Fila *fila, Pilha *pilha) {

    if (fila->quantidade < 3) {

        printf("\nFila nao possui 3 pecas!\n");
        return;
    }

    if (pilha->topo < 2) {

        printf("\nPilha nao possui 3 pecas!\n");
        return;
    }

    for (int i = 0; i < 3; i++) {

        int indiceFila =
            (fila->inicio + i) % TAM_FILA;

        Peca temp =
            fila->itens[indiceFila];

        fila->itens[indiceFila] =
            pilha->itens[pilha->topo - i];

        pilha->itens[pilha->topo - i] =
            temp;
    }

    printf("\nTroca dos 3 elementos realizada!\n");
}

// ========================================
// FUNÇÃO PRINCIPAL
// ========================================

int main() {

    srand((unsigned)time(NULL));

    Fila fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // ====================================
    // Preenchimento inicial da fila
    // ====================================

    for (int i = 0; i < TAM_FILA; i++) {

        enqueue(&fila, gerarPeca());
    }
    for (int i = 0; i < TAM_PILHA; i++) {

    push(&pilha, gerarPeca());
    }

    int opcao;

    do {

        printf("\n=================================\n");
        printf("       TETRIS STACK\n");
        printf("=================================\n");

        exibirFila(&fila);
        mostrarPilha(&pilha);

        printf("\n=== Estado Atual ===\n");

        printf("\nOpcoes:\n");

        printf("1 - Jogar peca da frente da fila\n");
        printf("2 - Enviar peca da fila para reserva (pilha)\n");
        printf("3 - Usar peca da reserva (pilha)\n");
        printf("4 - Trocar peca da frente da fila com o topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com as 3 pecas da pilha\n");
        printf("0 - Sair\n");

        printf("\nOpcao: ");
        scanf("%d", &opcao);

        switch(opcao) {

    case 1: {

        if (filaVazia(&fila)) {

            printf("\nFila vazia!\n");

        } else {

            Peca removida = dequeue(&fila);

            printf("\nPeca jogada: [%c %d]\n",
                   removida.nome,
                   removida.id);

            enqueue(&fila, gerarPeca());
        }

        break;
    }

    case 2: {

        if (filaVazia(&fila)) {

            printf("\nFila vazia!\n");

        } else if (pilhaCheia(&pilha)) {

            printf("\nPilha cheia!\n");

        } else {

            Peca reservada = dequeue(&fila);

            push(&pilha, reservada);

            printf("\nPeca reservada: [%c %d]\n",
                   reservada.nome,
                   reservada.id);

            enqueue(&fila, gerarPeca());
        }

        break;
    }

    case 3: {

        if (pilhaVazia(&pilha)) {

            printf("\nPilha vazia!\n");

        } else {

            Peca usada = pop(&pilha);

            printf("\nPeca usada da reserva: [%c %d]\n",
                   usada.nome,
                   usada.id);
        }

        break;
    }

    case 4: {

        trocarTopo(&fila, &pilha);

        break;
    }

    case 5: {

        trocarTres(&fila, &pilha);

        break;
    }

    case 0:

        printf("\nEncerrando programa...\n");
        break;

    default:

        printf("\nOpcao invalida!\n");
}

    } while(opcao != 0);

    return 0;
}