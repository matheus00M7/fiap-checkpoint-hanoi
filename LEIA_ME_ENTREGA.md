# Checkpoint Final - Hanoi Engine

## Grupo e entrega

Arthur Maziviero Faria - RM 573928
Jun Uehara - RM 570537
Felipe de Souza Gallo - RM 569680
Roberson Reguero Luiz Junior - RM 573031
Tommaso Conceissao Nagliatti - RM 572147
Matheus Martins Lacerda - RM 570843 (representante)

A composição de seis integrantes segue o grupo do Challenge informado. A entrega deve ser feita exclusivamente pelo representante Matheus Martins Lacerda. O nome completo de Tommaso foi atualizado conforme informado pelo grupo.

## Compilar e executar no Windows

1. Extraia a pasta completa do ZIP.
2. Tenha GCC no PATH e Python 3 instalado.
3. Abra um terminal dentro de Checkpoint_Hanoi e execute `build.bat`.
4. Execute `python bridge/bridge.py` e mantenha o terminal aberto.
5. Abra http://localhost:8080 no navegador.
6. Selecione de 3 a 8 discos e clique em Inicializar. Use Origem, Destino e Mover disco. Consulte o histórico com Atualizar.
7. Para encerrar o servidor, pressione Ctrl+C no terminal.

O executável Windows compilado está incluído em bin/hanoi_engine.exe. O código-fonte e os comandos de compilação também estão incluídos para recompilar no computador da entrega.

## Linux e macOS

Execute `make` dentro da pasta do projeto e depois `python3 bridge/bridge.py`. Abra http://localhost:8080. O executável Windows não é usado nesses sistemas.

## Organização

- src/hanoi.c: implementação das 12 funções e identificação dos integrantes.
- src/hanoi.h: structs e protótipos originais.
- src/main.c: protocolo original entre o processo C e a ponte.
- bridge/bridge.py: servidor HTTP original.
- frontend/: interface original HTML, CSS e JavaScript.
- docs/TEMPLATE_BIG_O.md: análise preenchida e resposta à questão do ponteiro para o último movimento.
- docs/TESTES_OBRIGATORIOS.md: resultados e reprodução dos testes.
- docs/evidencias/: capturas reais do navegador e registros de testes.
- tests/: testes das estruturas e da integração HTTP.

## Compatibilidade com os arquivos fornecidos

O guia PDF descreve uma versão com servidor HTTP em C, rotas separadas e visualização de endereços. O ZIP recebido fornece uma versão com bridge em Python e a rota POST /api/command, que transmite comandos INIT, MOVE, STATE, HISTORY e RESET ao executável C. Esta entrega preserva essa versão do ZIP; somente src/hanoi.c foi modificado entre os arquivos originais. Os demais arquivos adicionados documentam e testam a implementação.

As torres são listas simplesmente encadeadas usadas como pilhas. O histórico é outra lista encadeada. A regra real do jogo fica no C. O botão Ver demonstração é uma animação previamente fornecida pelo professor e não é utilizado como evidência do motor.

## Limites do contrato fornecido

reiniciarJogo retorna void e o main.c original sempre imprime sucesso após chamá-la. Se faltar memória durante a reconstrução, a implementação libera a lista parcial, mantém os ponteiros vazios e informa o erro em stderr. Propagar esse erro pela API exigiria modificar o contrato ou o protocolo original. As falhas de memória de moverDisco retornam -1 e preservam o estado.
