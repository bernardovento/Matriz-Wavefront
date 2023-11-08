#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Configurações do código:
// Tamanho da matriz:
#define TAM_LINHAS 20
#define TAM_COLUNAS 20
// Define onde vai ser o ponto de partida do Wave Front
#define POS_X_INICIAL 0
#define POS_Y_INICIAL 0
// Vai aparecer o processo de Wave Front? 0 para não e 1 para sim
#define PRINTAR_PROCESSO 0
// Vai existir paredes na matriz? 0 para não e 1 para sim
#define TER_PAREDES 0



#define LIMITE_MAIOR 999

// Função para preencher a matriz com valores iniciais (LIMITE_MAIOR)
void preencherMatriz(int matriz[][TAM_COLUNAS]);
// Função para imprimir a matriz
void printarMatriz(int matriz[][TAM_COLUNAS]);
// Função para calcular as distâncias na matriz
void mapearDistancia(int matriz[][TAM_COLUNAS]);
// Função para encontrar a menor distância a partir de uma posição
int menorPonto(int posX, int posY, int matriz[][TAM_COLUNAS]);
// Função para colocar paredes na matriz
void criarParedes(int matriz[][TAM_COLUNAS]);
// Função para printar o processo de wave front
void printarProcesso(int matriz[][TAM_COLUNAS]);


int main()
{
    int matriz[TAM_LINHAS][TAM_COLUNAS];
    preencherMatriz(matriz); // Preenche a matriz com o valor do LIMITE_MAIOR
    if(TER_PAREDES) // Checa se vai ou não ter paredes
        criarParedes(matriz); // Define as paredes
    matriz[POS_X_INICIAL][POS_Y_INICIAL] = 1; // Define o ponto de partida
    printf("Inicial: ");
    printarMatriz(matriz); // Imprime a matriz

    if(PRINTAR_PROCESSO)
        Sleep(2000);

    mapearDistancia(matriz); // Calcula as distâncias a partir do ponto de partida

    if(PRINTAR_PROCESSO)
        system("cls");

    printf("\nApos Calculo das Distancias:\n");
    printarMatriz(matriz); // Imprime a matriz atualizada com as distâncias
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
    printf("Matriz:\n");
    // Loop para imprimir a matriz formatada
    for (int x = 0; x < TAM_LINHAS; x++)
    {
        printf("(");
        for (int y = 0; y < TAM_COLUNAS; y++)
        {
            if(matriz[x][y] == LIMITE_MAIOR)
                printf(" |||");
            else if(matriz[x][y] > 0)
                printf(" %.3i", matriz[x][y]); // Imprime cada valor da matriz
            else
                printf(" ---");
            if (y != TAM_COLUNAS - 1)
                printf(",");
        }
        printf(")\n");
    }
}

void mapearDistancia(int matriz[][TAM_COLUNAS])
{
    int novo; // variavel auxiliar

    while (1) // while para verdadeiro, gerando um loop infinito a priori
    {
        int mudou = 0;
         // Loop para checar toda matriz
        for (int i = 0; i < TAM_LINHAS; i++)
        {
            for (int j = 0; j < TAM_COLUNAS; j++)
            {
                if (matriz[i][j] >= 1) // Checa se é uma parede
                {
                    novo = 1 + menorPonto(i, j, matriz); // Calcula a nova distância
                    if (novo < matriz[i][j])
                    {
                        matriz[i][j] = novo; // Atualiza a matriz se uma distância menor for encontrada
                        if(PRINTAR_PROCESSO)
                            printarProcesso(matriz);
                        if (!mudou)
                        {
                            mudou = 1; // Avisa que nesse loop ocorreram mudanças na matriz
                        }
                    }
                }
            }
        }

        if (!mudou)
        {
            break; // Para o while infinito
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

    // Calcula as distâncias a partir de posições vizinhas na matriz, não permitindo que ultrapasse os limites do array
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
    for (int i = 0; i < 8; i++) // Loop para buscar o menor vizinho do ponto de origem
    {
        if (pontos[i] < menor && pontos[i] >= 1)
        {
            menor = pontos[i];
        }
    }
    return menor; // Retorna o menor vizinho
}

void criarParedes(int matriz[][TAM_COLUNAS])
{
    int parede = TAM_COLUNAS/3;

    for (int j = 0; j < TAM_LINHAS - 1; j++) // Cria primeira parede
    {
        matriz[j][parede] = 0;
    }
    for (int j = 1; j < TAM_LINHAS; j++) // Cria segunda parede
    {
        matriz[j][2*parede] = 0;
    }
}

void printarProcesso(int matriz[][TAM_COLUNAS])
{
    system("cls");
    printarMatriz(matriz);
    Sleep(50);
}
