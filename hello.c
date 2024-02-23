#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

const int LINHAS = 10;
const int COLUNAS = 20;

// Print instructions
void instruçoes()
{
    printf("Leva a caixa \"O\" para a saida \"X\"\n");
    printf("O jogador é \"I\"\n");
    printf("Tenha cuidado com os inimigos \"P\"\n");
    printf("O jogo começa quando clicar-\n");
    printf("W-Cima\n");
    printf("A-Direita\n");
    printf("D-Esquerda\n");
    printf("S-Baixo\n\n");
}

// Print map
void printMapa(char **map, int linhas, int colunas, int pontos)
{
    printf("%d\n", pontos);
    for (int linha = 0; linha < linhas; linha++)
    {
        for (int coluna = 0; coluna < colunas; coluna++)
        {
            printf("%c", map[linha][coluna]);
        }
        printf("\n");
    }
    printf("\n");
    for (int linha = 0; linha < linhas; linha++)
    {
        free(map[linha]);
    }
}

// Cria mapa
char **map(int linhas, int colunas)
{
    char **texto = malloc(linhas * sizeof(char *));
    for (int linha = 0; linha < linhas; linha++)
    {
        texto[linha] = malloc(colunas * sizeof(char));
        for (int coluna = 0; coluna < colunas; coluna++)
        {
            if ((coluna == 0 || coluna == colunas - 1) && linha != 0)
            {
                texto[linha][coluna] = '|';
            }
            else if ((linha == 0 || linha == linhas - 1) && coluna != 0 && coluna != colunas - 1)
            {
                texto[linha][coluna] = '_';
            }
            else
            {
                texto[linha][coluna] = ' ';
            }
        }
    }
    return texto;
}

int main(void)
{
    // Inicia o jogo
    bool proximoNivel = true;
    int pontos = 0;

    int x = 1;
    int y = 1;

    bool movement1 = false;
    int inimigoX1 = 18;
    int inimigoY1 = 1;

    bool movement2 = false;
    int inimigoX2 = 18;
    int inimigoY2 = 9;

    bool movement3 = false;
    int inimigoX3 = 1;
    int inimigoY3 = 9;

    bool movement4 = false;
    int inimigoX4 = 1;
    int inimigoY4 = 1;

    while (proximoNivel)
    {
        proximoNivel = false;

        // Coordenadas caixa
        srand(time(NULL));
        int caixaX = rand() % 15 + 2;
        int caixaY = rand() % 5 + 2;

        // Coordenadas da saida
        int saidaX;
        int saidaY;
        do
        {
            saidaX = rand() % 15 + 2;
            saidaY = rand() % 5 + 2;
        } while (saidaX == caixaX && saidaY == caixaY);

        // Cria o mapa e faz print
        char **mapa = map(LINHAS, COLUNAS);
        mapa[y][x] = 'I';
        mapa[caixaY][caixaX] = 'O';
        mapa[saidaY][saidaX] = 'X';
        if (pontos >= 2)
        {
            mapa[inimigoY1][inimigoX1] = 'P';
        }
        if (pontos >= 6)
        {
            mapa[inimigoY2][inimigoX2] = 'P';
        }
        if (pontos >= 10)
        {
            mapa[inimigoY3][inimigoX3] = 'P';
        }
        if(pontos>=14){
            mapa[inimigoY4][inimigoX4] = 'P';
        }
        printMapa(mapa, LINHAS, COLUNAS, pontos);
        if (pontos == 0)
        {
            instruçoes();
        }

        // Começa o jogo
        while (!proximoNivel)
        {
            // Lê o input do player e guarda a posiçao antiga
            int mX = x;
            int mY = y;
            int caixaMX = caixaX;
            int caixaMY = caixaY;
            char input;
            scanf(" %c", &input);
            if (input == 'w')
            {
                y--;
                if (y == caixaY && x == caixaX)
                {
                    caixaY--;
                }
            }
            else if (input == 's')
            {
                y++;
                if (y == caixaY && x == caixaX)
                {
                    caixaY++;
                }
            }
            else if (input == 'a')
            {
                x--;
                if (y == caixaY && x == caixaX)
                {
                    caixaX--;
                }
            }
            else if (input == 'd')
            {
                x++;
                if (y == caixaY && x == caixaX)
                {
                    caixaX++;
                }
            }

            // Verifica se o player e a caixa estao dentro do range do mapa
            if ((y >= LINHAS || x >= COLUNAS - 1 || y <= 0 || x <= 0) || (caixaY >= LINHAS || caixaX >= COLUNAS - 1 || caixaY <= 0 || caixaX <= 0))
            {
                caixaX = caixaMX;
                caixaY = caixaMY;
                x = mX;
                y = mY;
            }

            // Recria o mapa com a nova posiçao do player, caixas e inimigos
            mapa = map(LINHAS, COLUNAS);
            mapa[caixaY][caixaX] = 'O';
            mapa[saidaY][saidaX] = 'X';
            mapa[y][x] = 'I';
            // Spawma inimigos quando o player atinge um certo numero de pontos
            if (pontos >= 2)
            {
                movement1 = !movement1;
                if (movement1)
                {
                    if (inimigoY1 - y < 0)
                    {
                        inimigoY1++;
                    }
                    else if (inimigoY1 - y > 0)
                    {
                        inimigoY1--;
                    }
                    else if (inimigoX1 - x < 0)
                    {
                        inimigoX1++;
                    }
                    else
                    {
                        inimigoX1--;
                    }
                }
                if (inimigoX1 == x && inimigoY1 == y)
                {
                    printf("Game Over\n");
                    printf("Tiveste %d pontos\n", pontos);
                    return 0;
                }
                mapa[inimigoY1][inimigoX1] = 'P';
            }
            if (pontos >= 6)
            {
                movement2 = !movement2;
                if (movement2)
                {
                    if (inimigoX2 - x < 0)
                    {
                        inimigoX2++;
                    }
                    else if (inimigoX2 - x > 0)
                    {
                        inimigoX2--;
                    }
                    else if (inimigoY2 - y < 0)
                    {
                        inimigoY2++;
                    }
                    else
                    {
                        inimigoY2--;
                    }
                }
                if (inimigoX2 == x && inimigoY2 == y)
                {
                    printf("Game Over\n");
                    printf("Tiveste %d\n pontos", pontos);
                    return 0;
                }
                mapa[inimigoY2][inimigoX2] = 'P';
            }
            if (pontos >= 10)
            {
                movement3 = !movement3;
                if (movement3)
                {
                    if (inimigoY3 - y < 0)
                    {
                        inimigoY3++;
                    }
                    else if (inimigoY3 - y > 0)
                    {
                        inimigoY3--;
                    }
                    else if (inimigoX3 - x < 0)
                    {
                        inimigoX3++;
                    }
                    else
                    {
                        inimigoX3--;
                    }
                }
                if (inimigoX3 == x && inimigoY3 == y)
                {
                    printf("Game Over\n");
                    printf("Tiveste %d pontos\n", pontos);
                    return 0;
                }
                mapa[inimigoY3][inimigoX3] = 'P';
            }
            if (pontos >= 14)
            {
                movement4 = !movement4;
                if (movement4)
                {
                    if (inimigoX4 - x < 0)
                    {
                        inimigoX4++;
                    }
                    else if (inimigoX4 - x > 0)
                    {
                        inimigoX4--;
                    }
                    else if (inimigoY4 - y < 0)
                    {
                        inimigoY4++;
                    }
                    else
                    {
                        inimigoY4--;
                    }
                }
                if (inimigoX4 == x && inimigoY4 == y)
                {
                    printf("Game Over\n");
                    printf("Tiveste %d pontos\n", pontos);
                    return 0;
                }
                mapa[inimigoY4][inimigoX4] = 'P';
            }
            printMapa(mapa, LINHAS, COLUNAS, pontos);

            // Limpa o buffer de entrada
            int c;
            while ((c = getchar()) != '\n')
            {
                getchar();
            }

            // Verifica se a caixa entra na saida
            if (saidaX == caixaX && saidaY == caixaY)
            {
                pontos++;
                proximoNivel = true;
            }
        }
    }
}