# SDL-Study
Códigos que desenvolvi estudando SDL

------

### Primeiro Programa

Desenvolva um programa em C++ com SDL que apresente uma tela  branca e que permita que o usuário mova um quadradro preto de 8x8 pixels por meio de teclas do teclado, deixando um rastro. As teclas a serem usadas são as seguintes:
   
- 8 e w/W - move para cima
- 2 e x/X - move para baixo
- 4 e a/A - move para esquerda
- 6 e d/D - move para direita
- 5 e s/S - limpa o desenho (pinta de branco a tela)
- ESC - encerra a aplicação.

------

### Segundo Programa

Escreva um programa em C++ com SDL para mostrar uma tela de cor preta e repetir a sequência de ações abaixo até que o usuário pressione ESC:
- deteminar aleatoriamente se desenhará uma linha ou uma circunferência;
- escolher aleatoriamente uma cor para os pontos a serem desenhados;
- para o caso da linha, escolher aleatoriamente duas posições (xi, yi) e (xf,yf) na tela e desenhar uma linha entre esses pontos utilizando o método analítico de desenho de linhas; para o caso da circunferência, escolher um ponto central (xc, yc) e um raio r e desenhar a circunferência usando o algoritmo de Bresenham para tal fim.
 
Para as ações do terceiro tópico, implente duas funções como sugeridas abaixo. Provavelmente será necessário incluir um parâmetro para informar a cor da linha. No entanto, essas funções devem usar exclusivamente o comando de desenhar pontos do SDL. Não é permitido o uso de comandos SDL para traçar linhas nem circunferências e elipses.
 
   void linhaDDA (SDL_Surface *s, int xi, int yi, int xf, int yf);
   void circBrasenham (SDL_Surface *s, int xc, int yc, int r);
