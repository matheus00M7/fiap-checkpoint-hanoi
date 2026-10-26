# Análise de complexidade Big-O

Considere n discos no jogo, m movimentos já registrados e k nós presentes nas três torres antes de uma inicialização. A análise considera malloc/free com custo constante e apresenta o pior caso; o intervalo de 3 a 8 discos não substitui a análise em função de n.

| Função | Tempo | Espaço auxiliar | Justificativa |
| --- | --- | --- | --- |
| push | O(1) | O(1) | Aloca um nó e atualiza o topo, sem percorrer a lista. |
| pop | O(1) | O(1) | Salva o disco, avança o topo e libera o antigo primeiro nó. |
| peek | O(1) | O(1) | Consulta apenas o primeiro nó. |
| torreVazia | O(1) | O(1) | Compara o topo com NULL. |
| registrarMovimento | O(m) | O(1) | Percorre a lista até o último movimento e insere um nó. |
| contarMovimentos | O(m) | O(1) | Visita todos os movimentos para contar. |
| moverDisco | O(m + 1) | O(1) | Valida os topos em O(1), executa push/pop em O(1) e registra em O(m). Uma tentativa inválida termina em O(1). |
| verificarVitoria | O(n) | O(1) | Confere cada valor de 1 até n e exige o fim da lista. |
| liberarTorre | O(n) | O(1) | Remove e libera cada nó da torre. |
| liberarHistorico | O(m) | O(1) | Salva o próximo endereço e libera cada movimento. |
| inicializarJogo | O(k + n) | O(n) | Monta uma lista temporária com n nós e libera as torres antigas com k nós. Com torres vazias, O(n). |
| reiniciarJogo | O(k + m + n) | O(n) | Libera torres e histórico e recria os n discos; para reiniciar com a mesma quantidade, O(n + m). |

Os nós criados por push e registrarMovimento pertencem ao armazenamento das listas. A coluna de espaço indica o custo adicional de uma chamada; a inicialização mantém temporariamente n novos nós antes de substituir o estado anterior. As três torres juntas ocupam O(n), pois cada disco aparece em uma única torre. O histórico ocupa O(m), portanto o estado completo ocupa O(n + m).

## Como inserir no histórico em O(1)?

Seria necessário manter, além do ponteiro para o primeiro movimento, um ponteiro para o último movimento. Na primeira inserção, ambos apontariam para o novo nó. Nas seguintes, ultimo->proximo receberia o novo nó, e ultimo passaria a apontar para ele. Ao liberar o histórico, ambos deveriam voltar a NULL.

Isso evita percorrer a lista a cada inserção. A implementação entregue mantém o percurso em O(m), conforme a versão simples ensinada e o contrato fornecido, que recebe somente o endereço do primeiro movimento.

## Custo de uma partida

A quantidade mínima de movimentos para resolver n discos é 2^n - 1: para mover o maior disco, é preciso mover os n - 1 menores, mover o maior e mover os n - 1 novamente. Assim, T(n) = 2T(n - 1) + 1, com T(1) = 1.

Como cada registro percorre o histórico, uma partida com M movimentos custa O(M²) no motor: os percursos somam 0 + 1 + ... + (M - 1). Para uma solução mínima, isso corresponde a O(4^n). Com um ponteiro para o último movimento, o registro total seria O(M), ou O(2^n) na solução mínima. Essa melhoria não elimina os percursos de contagem e serialização realizados pela integração fornecida.

## Ordem das operações e memória

Todos os movimentos são validados antes de qualquer alteração. O destino recebe push antes do pop da origem, para que uma falha de malloc não perca o disco. Se a alocação do histórico falhar, o nó recém-criado no destino é removido. Só após as duas alocações terem sucesso o nó antigo da origem é liberado. Assim, uma falha mantém o estado anterior e um sucesso utiliza as operações de pilha exigidas.


## Integrantes

Arthur Maziviero Faria - RM 573928
Jun Uehara - RM 570537
Felipe de Souza Gallo - RM 569680
Roberson Reguero Luiz Junior - RM 573031
Tommaso Conceissao Nagliatti - RM 572147
Matheus Martins Lacerda - RM 570843 (representante)
