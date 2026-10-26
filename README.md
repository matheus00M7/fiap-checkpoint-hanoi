# Checkpoint Final - Hanoi Engine em C

Torre de Hanoi com backend em C, integrada ao frontend HTML, CSS e JavaScript fornecido pelo professor. As 12 funções de `src/hanoi.c` estão implementadas: as torres são pilhas sobre listas simplesmente encadeadas, com `malloc()` e `free()`, e o histórico é uma lista encadeada em ordem cronológica.

## Integrantes e representante

| Integrante | RM |
| --- | --- |
| Arthur Maziviero Faria | 573928 |
| Jun Uehara | 570537 |
| Felipe de Souza Gallo | 569680 |
| Roberson Reguero Luiz Junior | 573031 |
| Tommaso Conceissao Nagliatti | 572147 |
| Matheus Martins Lacerda | 570843 |

**Representante da entrega: Matheus Martins Lacerda — RM 570843.**

A composição de seis integrantes segue o grupo do Challenge informado. A entrega deve ser realizada exclusivamente pelo representante.

## Compilar e executar no Windows

Requisitos: GCC disponível no PATH e Python 3 instalado.

1. Baixe ou clone o repositório e abra um terminal na pasta raiz do projeto.
2. Execute `build.bat` para compilar o motor.
3. Execute `python bridge/bridge.py` e mantenha o terminal aberto.
4. Acesse [http://localhost:8080](http://localhost:8080).
5. Selecione de 3 a 8 discos e clique em **Inicializar**. Escolha **Origem** e **Destino** e use **Mover disco**. Consulte o histórico com **Atualizar**.
6. Para encerrar o servidor, pressione `Ctrl+C` no terminal.

O executável Windows está incluído em `bin/hanoi_engine.exe`. O código-fonte e os comandos de compilação permitem recompilar o programa no computador da entrega.

## Compilar e executar no Linux/macOS

Requisitos: compilador C, `make` e Python 3.

Na pasta raiz do projeto, execute:

```sh
make
python3 bridge/bridge.py
```

Acesse [http://localhost:8080](http://localhost:8080).

## Organização do projeto

- [src/hanoi.c](src/hanoi.c): implementação das 12 funções e identificação do grupo.
- [src/hanoi.h](src/hanoi.h): estruturas e protótipos originais.
- [src/main.c](src/main.c): protocolo entre o processo C e a ponte Python.
- [bridge/bridge.py](bridge/bridge.py): servidor HTTP fornecido.
- [frontend/](frontend/): interface HTML, CSS e JavaScript fornecida.
- [docs/TEMPLATE_BIG_O.md](docs/TEMPLATE_BIG_O.md): análise Big-O preenchida e resposta sobre o ponteiro para o último movimento.
- [docs/TESTES_OBRIGATORIOS.md](docs/TESTES_OBRIGATORIOS.md): resultados e instruções para reproduzir os testes.
- [docs/evidencias/](docs/evidencias/): capturas da aplicação e registros dos testes.
- [tests/](tests/): testes das estruturas e da integração HTTP.

## Integração com os arquivos fornecidos

O guia PDF descreve uma versão com servidor HTTP em C, rotas separadas e visualização de endereços. O ZIP fornecido utiliza uma ponte em Python e a rota `POST /api/command`, que transmite os comandos `INIT`, `MOVE`, `STATE`, `HISTORY` e `RESET` ao executável C. Este projeto utiliza a arquitetura do ZIP, mantendo o frontend, a ponte e o contrato de `hanoi.h` fornecidos.

A regra do jogo e o estado das torres ficam no C. O botão **Ver demonstração** é uma animação previamente fornecida pelo professor e não é utilizado como evidência do motor.

O executável escreve uma linha de resposta por comando respondido em `stdout`. Mensagens de depuração devem usar `stderr`, para preservar o protocolo.

## Limitação no tratamento de falta de memória

Na implementação desta versão, `reiniciarJogo()` retorna `void`. Se faltar memória durante a reconstrução, a lista parcial é liberada, as torres ficam vazias e o erro é informado em `stderr`; o `main.c` fornecido ainda pode responder como se o jogo tivesse sido inicializado. As falhas de memória em `moverDisco()` retornam `-1` e preservam o estado anterior.
