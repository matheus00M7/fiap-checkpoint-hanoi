/*
 * Arthur Maziviero Faria - RM 573928
 * Jun Uehara - RM 570537
 * Felipe de Souza Gallo - RM 569680
 * Roberson Reguero Luiz Junior - RM 573031
 * Tommaso Conceissao Nagliatti - RM 572147
 * Matheus Martins Lacerda - RM 570843 (representante)
 */
/* Testes das listas, regras e alocacoes do motor. */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static int falharEm = -1;
static int ativos = 0;
static void *alocarTeste(size_t tamanho) {
    void *p;
    if (falharEm == 0) return NULL;
    if (falharEm > 0) falharEm--;
    p = malloc(tamanho);
    if (p != NULL) ativos++;
    return p;
}
static void liberarTeste(void *p) {
    if (p != NULL) ativos--;
    free(p);
}
#define malloc alocarTeste
#define free liberarTeste
#include "../src/hanoi.c"
#undef malloc
#undef free

static void conferirTorre(No *topo, int primeiro, int ultimo) {
    int disco;
    for (disco = primeiro; disco <= ultimo; disco++) {
        assert(topo != NULL && topo->disco == disco);
        topo = topo->proximo;
    }
    assert(topo == NULL);
}
static void resolver(int n, Torre *origem, Torre *auxiliar, Torre *destino,
                     Movimento **historico) {
    if (n == 0) return;
    resolver(n - 1, origem, destino, auxiliar, historico);
    assert(moverDisco(origem, destino, historico) == 1);
    resolver(n - 1, auxiliar, origem, destino, historico);
}
int main(void) {
    Torre a = {'A', NULL}, b = {'B', NULL}, c = {'C', NULL};
    Movimento *historico = NULL, *m;
    No *salvo, *destinoSalvo;
    int i, n;
    const char origens[] = "AACABBA";
    const char destinos[] = "CBBCACC";
    const int discos[] = {1, 2, 1, 3, 1, 2, 1};

    assert(pop(&a.topo) == -1 && peek(a.topo) == -1 && torreVazia(a.topo));
    assert(push(&a.topo, 2) && push(&a.topo, 1));
    salvo = a.topo;
    assert(peek(a.topo) == 1 && a.topo == salvo);
    assert(pop(&a.topo) == 1 && pop(&a.topo) == 2);
    assert(ativos == 0);

    assert(inicializarJogo(&a, &b, &c, 3));
    conferirTorre(a.topo, 1, 3);
    assert(b.topo == NULL && c.topo == NULL);
    salvo = a.topo;
    assert(!inicializarJogo(&a, &b, &c, 2) && a.topo == salvo);
    assert(moverDisco(&b, &c, &historico) == 0);
    assert(moverDisco(&a, &a, &historico) == 0);
    assert(moverDisco(NULL, &c, &historico) == 0);
    assert(moverDisco(&a, &c, NULL) == 0);
    assert(a.topo == salvo && historico == NULL);

    for (i = 0; i < 7; i++) {
        Torre *o = origens[i] == 'A' ? &a : origens[i] == 'B' ? &b : &c;
        Torre *d = destinos[i] == 'A' ? &a : destinos[i] == 'B' ? &b : &c;
        assert(moverDisco(o, d, &historico) == 1);
        assert(contarMovimentos(historico) == i + 1);
        if (i == 0) {
            salvo = a.topo;
            destinoSalvo = c.topo;
            m = historico;
            assert(moverDisco(&a, &c, &historico) == 0);
            assert(a.topo == salvo && c.topo == destinoSalvo && historico == m);
        }
    }
    m = historico;
    for (i = 0; i < 7; i++) {
        assert(m && m->disco == discos[i] && m->origem == origens[i] &&
               m->destino == destinos[i]);
        m = m->proximo;
    }
    assert(m == NULL && verificarVitoria(&c, 3));
    conferirTorre(c.topo, 1, 3);
    c.topo->disco = 2;
    assert(!verificarVitoria(&c, 3));
    c.topo->disco = 1;
    assert(push(&c.topo, 1));
    assert(!verificarVitoria(&c, 3));
    pop(&c.topo);

    reiniciarJogo(&a, &b, &c, &historico, 8);
    conferirTorre(a.topo, 1, 8);
    assert(b.topo == NULL && c.topo == NULL && historico == NULL && ativos == 8);
    for (i = 0; i < 2; i++) {
        salvo = a.topo;
        falharEm = i;
        assert(moverDisco(&a, &c, &historico) == -1);
        assert(a.topo == salvo && c.topo == NULL && historico == NULL && ativos == 8);
        falharEm = -1;
    }
    assert(moverDisco(&a, &c, &historico) == 1);
    for (i = 0; i < 2; i++) {
        salvo = a.topo;
        destinoSalvo = b.topo;
        m = historico;
        falharEm = i;
        assert(moverDisco(&a, &b, &historico) == -1);
        assert(a.topo == salvo && b.topo == destinoSalvo && historico == m);
        assert(contarMovimentos(historico) == 1 && ativos == 9);
        falharEm = -1;
    }
    for (i = 0; i < 8; i++) {
        salvo = a.topo;
        falharEm = i;
        assert(!inicializarJogo(&a, &b, &c, 8));
        assert(a.topo == salvo && ativos == 9);
        falharEm = -1;
    }
    for (n = 3; n <= 8; n++) {
        reiniciarJogo(&a, &b, &c, &historico, n);
        resolver(n, &a, &b, &c, &historico);
        assert(verificarVitoria(&c, n));
        assert(a.topo == NULL && b.topo == NULL);
        assert(contarMovimentos(historico) == (1 << n) - 1);
    }
    for (i = 0; i < 100; i++) {
        reiniciarJogo(&a, &b, &c, &historico, 3);
        assert(ativos == 3 && historico == NULL);
    }
    liberarTorre(&a.topo);
    liberarTorre(&b.topo);
    liberarTorre(&c.topo);
    liberarHistorico(&historico);
    liberarTorre(&a.topo);
    liberarHistorico(&historico);
    assert(ativos == 0 && a.topo == NULL && historico == NULL);
    puts("PASSOU: pilhas, regras, historico, reset, vitoria de 3 a 8 discos e falhas de memoria.");
    puts("Alocacoes pendentes: 0.");
    return 0;
}
