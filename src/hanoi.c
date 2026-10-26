/*
 * Arthur Maziviero Faria - RM 573928
 * Jun Uehara - RM 570537
 * Felipe de Souza Gallo - RM 569680
 * Roberson Reguero Luiz Junior - RM 573031
 * Tommaso Conceissao Nagliatti - RM 572147
 * Matheus Martins Lacerda - RM 570843 (representante)
 */
#include <stdio.h>
#include <stdlib.h>
#include "hanoi.h"

int push(No **topo, int disco) {
    No *novo;
    if (topo == NULL) return 0;
    novo = malloc(sizeof(No));
    if (novo == NULL) return 0;
    novo->disco = disco;
    novo->proximo = *topo;
    *topo = novo;
    return 1;
}

int pop(No **topo) {
    No *removido;
    int disco;
    if (topo == NULL || *topo == NULL) return -1;
    removido = *topo;
    disco = removido->disco;
    *topo = removido->proximo;
    free(removido);
    return disco;
}

int peek(No *topo) {
    return topo == NULL ? -1 : topo->disco;
}

int torreVazia(No *topo) {
    return topo == NULL;
}

int registrarMovimento(Movimento **historico, char origem, char destino, int disco) {
    Movimento *novo, *atual;
    if (historico == NULL) return 0;
    novo = malloc(sizeof(Movimento));
    if (novo == NULL) return 0;
    novo->disco = disco;
    novo->origem = origem;
    novo->destino = destino;
    novo->proximo = NULL;
    if (*historico == NULL) {
        *historico = novo;
    } else {
        atual = *historico;
        while (atual->proximo != NULL) atual = atual->proximo;
        atual->proximo = novo;
    }
    return 1;
}

int contarMovimentos(Movimento *historico) {
    int quantidade = 0;
    while (historico != NULL) {
        quantidade++;
        historico = historico->proximo;
    }
    return quantidade;
}

int moverDisco(Torre *origem, Torre *destino, Movimento **historico) {
    int disco;
    if (origem == NULL || destino == NULL || historico == NULL || origem == destino)
        return 0;
    if (torreVazia(origem->topo)) return 0;
    disco = peek(origem->topo);
    if (!torreVazia(destino->topo) && disco >= peek(destino->topo)) return 0;

    /* Primeiro aloca no destino: se malloc falhar, a origem continua intacta. */
    if (!push(&destino->topo, disco)) return -1;
    if (!registrarMovimento(historico, origem->nome, destino->nome, disco)) {
        pop(&destino->topo);
        return -1;
    }
    /* A origem so e removida depois que as duas alocacoes deram certo. */
    pop(&origem->topo);
    return 1;
}

int verificarVitoria(Torre *destino, int quantidadeDiscos) {
    No *atual;
    int esperado;
    if (destino == NULL || quantidadeDiscos < 3 || quantidadeDiscos > 8) return 0;
    atual = destino->topo;
    for (esperado = 1; esperado <= quantidadeDiscos; esperado++) {
        if (atual == NULL || atual->disco != esperado) return 0;
        atual = atual->proximo;
    }
    return atual == NULL;
}

void liberarTorre(No **topo) {
    if (topo == NULL) return;
    while (*topo != NULL) pop(topo);
}

void liberarHistorico(Movimento **historico) {
    Movimento *removido;
    if (historico == NULL) return;
    while (*historico != NULL) {
        removido = *historico;
        *historico = removido->proximo;
        free(removido);
    }
}

int inicializarJogo(Torre *a, Torre *b, Torre *c, int quantidadeDiscos) {
    No *novoTopo = NULL;
    int disco;
    if (a == NULL || b == NULL || c == NULL || a == b || a == c || b == c ||
        quantidadeDiscos < 3 || quantidadeDiscos > 8) return 0;
    for (disco = quantidadeDiscos; disco >= 1; disco--) {
        if (!push(&novoTopo, disco)) {
            liberarTorre(&novoTopo);
            return 0;
        }
    }
    liberarTorre(&a->topo);
    liberarTorre(&b->topo);
    liberarTorre(&c->topo);
    a->nome = 'A';
    b->nome = 'B';
    c->nome = 'C';
    a->topo = novoTopo;
    return 1;
}

void reiniciarJogo(Torre *a, Torre *b, Torre *c, Movimento **historico,
                   int quantidadeDiscos) {
    if (a == NULL || b == NULL || c == NULL || historico == NULL ||
        a == b || a == c || b == c || quantidadeDiscos < 3 || quantidadeDiscos > 8)
        return;
    liberarTorre(&a->topo);
    liberarTorre(&b->topo);
    liberarTorre(&c->topo);
    liberarHistorico(historico);
    if (!inicializarJogo(a, b, c, quantidadeDiscos))
        fprintf(stderr, "Falha de memoria ao inicializar o jogo.\n");
}
