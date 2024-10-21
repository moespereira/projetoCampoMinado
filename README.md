Projeto Campo Minado
Para obtemção de nota da TP1 do curdo de Engenharia de Software da UFAM

Matéria AED

A entrada do jogo é composta com uma letra para identificar a dificuldade (tamanho) do jogo.
Estas letras podem ser:
F para fácil
M para médio
D pra difícil
S para sair

O básico______________________________________________________________________________________________________________________________________________________________________________________________

Há tratamentos na entrada do teclado caso tenha erro na digitação, neste caso você digita novamente, ou mudança da tipografia da letra caso sejam inseridas as letras corretas mas minísculas.

O jogo é iniciado com uma matriz de tamanho NxN a se selecionada pela dificuldade escolhida.

A tela mostra a matriz NxN com a marcação de X sinalizando as coordenadas não jogadas ou fechadas.

O usuário irá entrar com 2 números inteiros para iniciar a sua jogada.

Também há tratamento nessas entradas. Caso o usuário entre dois números não inteiros ou com números fora do tamanho da matriz NxN

A cada rodada, o usuário irá entrar com um par ordenado (x, y) e o programa irá calcular as seguintes situações:

Caso a entrada seja válida e o par ordenado (x, y) tenha informação de que não tem mina na escolha, o programa irá imprimir uma mova matriz com o número 0 impresso no par escolhido.
Em adição, o programa irá imprimir todos os pares (x, y) próximos do par escolhodo que contenham a mesma informação.
O programa irá parar de imprimir quando chegar na borda da matriz ou quando encontrar uma flag de mina na vizinhança.
Esta flag funciona como parede que circula a mina.

Caso a coordenada seja uma flag de mina, o programa só irá mostrar a coordenada selecionada

caso a coordenada seja uma mina, o programa irá encerrar mostrando toda a matriz junto com a mensagem "Game Over"

Caso o usuário consiga completar todas as coordenadas sem selecionar uma mina, o prigrama irá mostrar a mensagem "Parabéns, você é fera" junto com a matriz completa, onde as minas são sinalizadas com X.

O programa se encerra após a partida.
___________________________________________________________________________________________________________________________________________________________________________________________________

O código contém uma Struct chamada Coordenada, nela estão três variáveis para ajudar a identificar uma jogada.

A variável temMina, que identifica que naquela posição tem uma Mina
A variável abertura, que identifica que aquela posição já foi jogada ou aberta
A Variável vizinho, que identifica a quantidade de minas próximas àquela posição

