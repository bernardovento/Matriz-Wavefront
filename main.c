#include <stdio.h>
#include <stdlib.h>

#define TAM_LINHAS 20
#define TAM_COLUNAS 20

#define LIMITE_MAIOR 999

// Fun��o para preencher a matriz com valores iniciais (LIMITE_MAIOR)
void preencherMatriz(int matriz[][TAM_COLUNAS]);
// Fun��o para imprimir a matriz
void printarMatriz(int matriz[][TAM_COLUNAS]);
// Fun��o para calcular as dist�ncias na matriz
void mapearDistancia(int matriz[][TAM_COLUNAS]);
// Fun��o para encontrar a menor dist�ncia a partir de uma posi��o
int menorPonto(int posX, int posY, int matriz[][TAM_COLUNAS]);
// Fun��o para colocar paredes na matriz
void criarParedes(int matriz[][TAM_COLUNAS]);

int main()
{
    int matriz[TAM_LINHAS][TAM_COLUNAS];
    preencherMatriz(matriz);
    printf("Matriz Inicial:\n");
    matriz[0][0] = 1; // Define o ponto de partida
    printarMatriz(matriz);
    criarParedes(matriz); // Define as paredes
    mapearDistancia(matriz); // Calcula as dist�ncias a partir do ponto de partida
    printf("\nMatriz Apos Calculo das Distancias:\n");
    printarMatriz(matriz); // Imprime a matriz atualizada com as dist�ncias
    return 0;
}

void preencherMatriz(int matriz[][TAM_COLUNAS])
{
    // Loop para preencher a matriz com valores LIMITE_MAIOR
    for (int x = 0; x < TAM_LINHAS; x++)
    {
        for (int y = 0; y < TAM_COLUNAS; y++)
        {
            matriz[x][y] = LIMITE_MAIOR;
        }
    }
}

void printarMatriz(int matriz[][TAM_COLUNAS])
{
    // Loop para imprimir a matriz formatada
    for (int x = 0; x < TAM_LINHAS; x++)
    {
        printf("(");
        for (int y = 0; y < TAM_COLUNAS; y++)
        {
            printf(" %.3i", matriz[x][y]); // Imprime cada valor da matriz
            if (y != TAM_COLUNAS - 1)
                printf(",");
        }
        printf(")\n");
    }
}

void mapearDistancia(int matriz[][TAM_COLUNAS])
{
    int novo;
    int contador = 0;

    while (1)
    {
        int mudou = 0;

        for (int i = 0; i < TAM_LINHAS; i++)
        {
            for (int j = 0; j < TAM_COLUNAS; j++)
            {
                if (matriz[i][j] >= 1)
                {
                    novo = 1 + menorPonto(i, j, matriz); // Calcula a nova dist�ncia
                    if (novo < matriz[i][j])
                    {
                        matriz[i][j] = novo; // Atualiza a matriz se uma dist�ncia menor for encontrada
                        if (!mudou)
                        {
                            mudou = 1;
                        }
                    }
                }
            }
        }

        if (!mudou)
        {
            contador++;
        }
        if (contador > 400)
        {
            break; // Sai do loop se n�o houver mais mudan�as ou ap�s um limite de itera��es
        }
    }
}

int menorPonto(int posX, int posY, int matriz[][TAM_COLUNAS])
{
    int pontos[8];

    // Inicializa o array de pontos com valores LIMITE_MAIOR
    for (int i = 0; i < 8; i++)
    {
        pontos[i] = LIMITE_MAIOR;
    }

    // Calcula as dist�ncias a partir de posi��es vizinhas na matriz
    if (posX > 0)
    {
        pontos[0] = matriz[posX - 1][posY];
        if (posY < TAM_COLUNAS - 1)
        {
            pontos[1] = matriz[posX - 1][posY + 1];
        }
    }

    if (posY < TAM_COLUNAS - 1)
    {
        pontos[2] = matriz[posX][posY + 1];
    }

    if (posX < TAM_LINHAS - 1)
    {
        if (posY < TAM_COLUNAS - 1)
        {
            pontos[3] = matriz[posX + 1][posY + 1];
        }
        pontos[4] = matriz[posX + 1][posY];
        if (posY > 0)
        {
            pontos[5] = matriz[posX + 1][posY - 1];
        }
    }

    if (posY > 0)
    {
        pontos[6] = matriz[posX][posY - 1];
        if (posX > 0)
        {
            pontos[7] = matriz[posX - 1][posY - 1];
        }
    }

    int menor = LIMITE_MAIOR + 1;
    for (int i = 0; i < 8; i++)
    {
        if (pontos[i] < menor && pontos[i] >= 1)
        {
            menor = pontos[i]; // Encontra a menor dist�ncia entre as posi��es vizinhas
        }
    }
    return menor;
}

void criarParedes(int matriz[][TAM_COLUNAS])
{
    int parede = TAM_COLUNAS/3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < TAM_LINHAS - 1; j++)
        {
            matriz[j][(i+1)*parede] = 0;
        }
    }
}
