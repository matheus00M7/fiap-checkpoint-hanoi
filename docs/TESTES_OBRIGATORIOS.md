# Testes obrigatórios e evidências

Validação realizada em 26/10/2026, Windows, GCC, padrão C11 e Python 3.

## Compilação

O motor e o teste das estruturas foram compilados com -Wall -Wextra -Wpedantic -Werror -std=c11. Não houve avisos nem erros.

## Resultados

| Caso obrigatório | Resultado observado | Evidência |
| --- | --- | --- |
| Inicialização com 3 discos | A = 1 -> 2 -> 3; B e C vazias; zero movimentos. | 01_inicializacao_3.png e teste_http.txt |
| Inicialização com 8 discos | A = 1 -> 2 -> ... -> 8; B e C vazias. | 05_reset_8_discos.png e teste_http.txt |
| Movimento válido A -> C | Disco 1 em C; A começa no disco 2; histórico com um nó. | 02_movimento_valido.png e teste_http.txt |
| Origem vazia | MOVE B C recusado; estado preservado. | teste_http.txt e teste_estruturas.txt |
| Maior sobre menor | Segundo MOVE A C recusado; estado e histórico preservados. | teste_http.txt e teste_estruturas.txt |
| Histórico com pelo menos 5 movimentos | Sete registros conferidos em ordem, com disco, origem e destino. | 04_historico_vitoria.png e teste_http.txt |
| Reset | Torres antigas e histórico liberados; oito discos recriados e histórico vazio. | 05_reset_8_discos.png e teste_estruturas.txt |
| Vitória com 3 discos | C = 1 -> 2 -> 3; MOVES=7 e WIN=1. | 03_vitoria_3_discos.png e teste_http.txt |

Os arquivos de evidência estão em docs/evidencias/. As capturas de vitória e histórico são vistas complementares da mesma partida no frontend original.

## Testes adicionais

- push, pop, peek e pilha vazia.
- Torres iguais, inexistentes e quantidade fora de 3 a 8 discos.
- Verificação de vitória rejeitando ordem incorreta e nó excedente.
- Solução de todos os tamanhos de 3 a 8, sempre usando moverDisco; contagem final igual a 2^n - 1.
- Cem reinícios seguidos.
- Falha simulada na alocação do disco de destino e do registro do histórico, inclusive com histórico já existente.
- Falha em cada alocação de uma inicialização com oito discos, com liberação da lista parcial.
- Contagem de alocações e liberações do motor durante os testes: zero alocações pendentes no encerramento. Este acompanhamento não substitui uma ferramenta de análise de memória como Valgrind.
- Requisições HTTP reais à ponte original: arquivos estáticos, ping, inicialização, movimentos, histórico e reset.

Os vetores nos testes armazenam apenas resultados esperados e sequências de comandos. As torres do motor utilizam exclusivamente nós encadeados.

## Reproduzir

Na raiz de Checkpoint_Hanoi, execute:

```text
gcc -Wall -Wextra -Wpedantic -Werror -std=c11 -O2 src/main.c src/hanoi.c -o bin/hanoi_engine.exe
gcc -Wall -Wextra -Wpedantic -Werror -std=c11 -O0 -g tests/test_hanoi.c -o bin/test_hanoi.exe
bin\test_hanoi.exe
python tests/test_integracao.py
```

No Linux/macOS, remova .exe dos nomes de saída, execute ./bin/test_hanoi e use python3. O teste HTTP inicia seu próprio servidor em uma porta local disponível e encerra o processo C ao terminar. Não requer o servidor da interface aberto.


## Integrantes

Arthur Maziviero Faria - RM 573928
Jun Uehara - RM 570537
Felipe de Souza Gallo - RM 569680
Roberson Reguero Luiz Junior - RM 573031
Tommaso Conceissao Nagliatti - RM 572147
Matheus Martins Lacerda - RM 570843 (representante)
