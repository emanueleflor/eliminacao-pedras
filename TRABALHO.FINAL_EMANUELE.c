/*Trabalho final - Jogo da eliminação das pedras
Aluna: Emanuele Anastácio Bernardo Flor da Rosa*/

#include <stdio.h>


void inic_tab(char m[8][8])
{
    // Inicialização do tabuleiro
    // Colocar as pedras nos lugares do tabuleiro original
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            m[i][j] = '*';          
        }
    }

    // Coloca espaços vazios ao centro do tabuleiro
    for (int i = 2; i < 6; i++)
    {
        for (int j = 2; j < 6; j++)
        {
            m[i][j] = '-';
        }
    }
}

void apr_tab(char m[8][8])
// Realiza a apresentação do tabuleiro inicalizado anteriormente

{
    printf("\n");
    printf("  ");
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < 8; i++)
    {
        printf("%d ", i + 1);
        for (int j = 0; j < 8; j++)
        {
            printf("%c ", m[i][j]);
        }
        printf("\n");
    }
}

void tab_atualizado(char m[8][8], int l1, int c1, int l2, int c2)
{
    // Atualização após cada jogada (movimentação das pedras)
    int j = c1;

    if (l1 < l2 && c1 < c2) // esquerda cima
    {
        for (int i = l1; i <= l2; i++)
        {
            m[i - 1][j - 1] = '-';
            j++;
            m[l2 - 1][c2 - 1] = '*';
        }
    }

    if (l1 > l2 && c1 < c2) // esquerda baixo
    {
        for (int i = l1; i >= l2; i--)
        { // l1 > l2 E c1 < c2
            m[i - 1][j - 1] = '-';
            j++;
            m[l2 - 1][c2 - 1] = '*';
        }
    }

    if (l1 > l2 && c1 > c2) // direita baixo
    {
        for (int i = l1; i >= l2; i--)
        { // l1 > l2 E c1 > c2
            m[i - 1][j - 1] = '-';
            j--;
            m[l2 - 1][c2 - 1] = '*';
        }
    }

    if (l1 < l2 && c1 > c2) // direita cima
    {
        for (int i = l1; i <= l2; i++)
        { // l1 < l2 E c1 > c2
            m[i - 1][j - 1] = '-';
            j--;
            m[l2 - 1][c2 - 1] = '*';
        }
    }
}

void apr_tab_atualizado(char m[8][8])
{
    // Apresentação do tabuleiro atualizado com as movimentações da jogada anterior

    printf("\n");
    printf("  ");
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < 8; i++)
    {
        printf("%d ", i + 1);
        for (int j = 0; j < 8; j++)
        {
            printf("%c ", m[i][j]);
        }
        printf("\n");
    }
}

void info_jogada(int l1, int c1, int l2, int c2, int p, int *t, int *r)
{
    // Apresenta as informações da jogada (quantas pedras foram retiradas no salto, 
    // quantas pedras foram retiradas ao total e quantas ainda restam)

    int j = c1 - 1;

    if (l1 < l2 && c1 < c2) // esquerda cima
    {
        for (int i = l1; i < l2 - 1; i++)
        {
            p++;         // Incrementa o numero de pedras
            j++;         // Incrementa o contador
        }
        *t = *t + p;     // Cálculo para o total de pedras retiradas
        *r = 48 - *t;    // Cálculo para o número de pedras restantes
    }

    if (l1 > l2 && c1 < c2) // esquerda baixo
    {
        for (int i = l1 - 1; i > l2; i--)
        { // l1 > l2 E c1 < c2
            p++;
            j++;
        }
        *t = *t + p;
        *r = 48 - *t;
    }

    if (l1 > l2 && c1 > c2) // direita baixo
    {
        for (int i = l1 - 1; i > l2; i--)
        { // l1 > l2 E c1 > c2
            p++;
            j--;
        }
        *t = *t + p;
        *r = 48 - *t;
    }

    if (l1 < l2 && c1 > c2) // direita cima
    {
        for (int i = l1; i < l2 - 1; i++)
        { // l1 < l2 E c1 > c2

            p++;
            j--;
        }
        *t = *t + p;
        *r = 48 - *t;
    }

    printf("\nSalto de (%d, %d) para (%d, %d) com %d pedra(s) eliminada(s) neste salto.", l1, c1, l2, c2, p);
    printf(" %d pedras eliminadas; restam %d pedras no tabuleiro.\n", *t, *r);
}

int critica_origem(char m[8][8], int l1, int c1)
{

    if (l1 > 8 || c1 > 8)
    { // Se a linha ou a coluna infromadas forem maiores que 8
        printf("\nCasa de origem inexistente!\n");
        return 0;
    }

    if (m[l1 - 1][c1 - 1] == '-')
    { // Se a linha e coluna de origem estiver vazia
        printf("\nEssa casa de origem está vazia!\n");
        return 0;
    }

    return 1;
}

int critica_destino(char m[8][8], int l2, int c2)
{

    if (m[l2 - 1][c2 - 1] == '*')
    { // Se a linha e coluna de destino estiver ocupada
        printf("\nEstá casa de destino já está ocupada!\n");
        return 0;
    }

    if (l2 > 8 || c2 > 8)
    { // Se a linha ou a coluna infromadas forem maiores que 8
        printf("\nCasa de destino inexistente!\n");
        return 0;
    }

    return 1;
}

int critica_casa_vazia(char m[8][8], int l1, int c1, int l2, int c2)
{
    // Se as casas entre a casa de origem e de destino estão vazias 

    int j;

    if (l1 < l2 && c1 < c2) // esquerda cima
    {
        j = c1;

        for (int i = l1; i < l2 - 1; i++)
        {
            if (m[i][j] == '-')
            {
                return 0;
            }
            j++;
        }
    }

    if (l1 > l2 && c1 < c2) // esquerda baixo
    {
        j = c1;

        for (int i = l1-2; i > l2 - 1; i--)
        { // l1 > l2 E c1 < c2
            if (m[i][j] == '-')
            {
                return 0;
            }
            j++;
        }
    }

    if (l1 > l2 && c1 > c2) // direita baixo
    {
        j = c1 - 1;

        for (int i = l1 - 1; i > l2 - 1; i--)
        { // l1 > l2 E c1 > c2
            if (m[i][j] == '-')
            {
                return 0;
            }
            j--;
        }
    }

    if (l1 < l2 && c1 > c2) // direita cima
    {
        j = c1 - 1;

        for (int i = l1; i < l2 - 1; i++)
        { // l1 < l2 E c1 > c2
            j--;
            if (m[i][j] == '-')
            {
                return 0;
            }
        }
    }

    return 1;
}

int critica_diagonal(int l1, int c1, int l2, int c2)
{
    // Se a casa de destino está na mesma diagonal da casa de origem
    int j;

    if (l1 > l2 && c1 < c2) // esquerda baixo
    {
        j = c1 - 1;
        for (int i = l1 - 1; i < 0; i--)
        {
            if (i == l2 - 1 && j == c2 - 1)
            {
                return 1;
            }

            else
            {
                return 0;
            }
            j++;
        }
    }

    if (l1 > l2 && c1 > c2) // direita baixo
    {
        printf("direita baixo");
        j = c1 - 1;
        for (int i = l1 - 1; i >= 0; i--)
        {
            if (i == l2 - 1 && j == c2 - 1)
            {
                printf("i %d j %d\n", i, j);
                return 1;
            }
            j--;
        }
        return 0;
    }

    /*if(l1 < l2 && c1 < c2){ //esquerda cima
        printf("esquerda cima");
        j = c1;
        for (int i = l1; l1 < 7; i++){
            if (i == l2 - 1 && j == c2 - 1)
            {
                return 1;
            }

            else
            {
                return 0;
            }
            j++;
        }
    }*/

    return 1;
}

void entrada(char m[8][8], int *l1, int *c1, int *l2, int *c2)
{
    // Declaração de variáveis locais
    int OK_para_critica_origem;
    int OK_para_critica_Destino;
    int OK_para_critica_casa_vazia;
    int OK_para_critica_diagonal;

    do
    {   // Loop para repetir a entrada de dados se as críticas de dados encontrarem erros

        printf("\nDigite a linha e coluna de origem (0 para finalizar/desistir): ");
        scanf("%d", l1);
        scanf(" %d", c1);

        printf("\nDigite a linha e coluna de destino (0 para finalizar/desistir): ");
        scanf("%d", l2);
        scanf(" %d", c2);

        OK_para_critica_origem = critica_origem(m, *l1, *c1);

        OK_para_critica_Destino = critica_destino(m, *l2, *c2);

        OK_para_critica_casa_vazia = critica_casa_vazia(m, *l1, *c1, *l2, *c2);
        if (OK_para_critica_casa_vazia == 0) // Se der erro 
        {
            printf("\nEsse salto não é permitido!\n");
            printf("Existem casas vazias no intervalo!\n");
        }

        OK_para_critica_diagonal = critica_diagonal(*l1, *c1, *l2, *c2);
        if (OK_para_critica_diagonal == 0) // Se der erro
        {
            printf("\nEsse salto não é permitido!\n");
            printf("Diagonal inválida!\n");
        }

    } while (OK_para_critica_Destino == 0 || OK_para_critica_origem == 0 || OK_para_critica_casa_vazia == 0 || OK_para_critica_diagonal == 0);
}

void nivel_dificuldade(int t, int s)
{
    // Ver quantas pedras o jogador cocnseguiu remover e apresentar o grau de dificuldade atingido
    printf("\nCom o total de %d pedras eliminadas e %d saltos realizados, o nível de dificuldade atingido foi: ", t, s);

    if (t <= 29)
    {
        printf("\nExtremamente fácil\n");
    }
    else if (t <= 39)
    {
        printf("\nFácil\n");
    }
    else if (t <= 44)
    {
        printf("\nDifícil\n");
    }
    else
    {
        printf("\nExtremamente difícil\n");
    };
}

int main()
{
    printf("\nJogo da Eliminacao das Pedras\n");
    
    printf("\n----------------------------Niveis de Dificuldade---------------------------------------\n");
    printf("Extremamente facil: eliminar até 29 pedras\n");
    printf("Facil: eliminar de 30 a 39 pedras\n");
    printf("Dificil: eliminar de 40 a 44 pedras\n");
    printf("Extremamente dificil: eliminar de 45 a 47 pedras\n");
    printf("---------------------------------------------------------------------------------------\n");

    printf("\n-------------------------------------Regras----------------------------------------------\n");
    printf("> Um salto consiste sempre em deslocar uma pedra qualquer para uma casa que esteja vazia\n");
    printf("> A casa de destino da pedra no salto deve estar na diagonal da sua casa de origem\n");
    printf("> Para atingir a casa vazia, a pedra não pode passar por outras casas vazias\n");
    printf("----------------------------------------------------------------------------------------\n");


    // Declaração de variáveis
    char tab[8][8];                     // Tabuleiro (Representação)
    int lin_o, col_o, lin_d, col_d;     // Dados da jogada
    int num_pedras;                     // Numero de pedras eliminadas na jogada
    int num_rest;                       // Numero restante de pedras
    int num_total;                      // Numero total de pedras eliminadas
    int num_salto;                      // Numero total de saltos realizados
    char opc;                           // Opção de jogar novamente

    do
    {
        // Iniciaização das variáveis
        num_pedras = 0;
        num_rest = 0;
        num_total = 0;
        num_salto = 0;
        opc = 'n';

        // Inicialização do tabuleiro
        inic_tab(tab);

        // Apresentar o tabuleiro
        apr_tab(tab);

        do
        {
            // Solicitar a casa de origem e de destino (jogada) 
            entrada(tab, &lin_o, &col_o, &lin_d, &col_d);

            // Apresentar tabuleiro atualizado
            tab_atualizado(tab, lin_o, col_o, lin_d, col_d);
            apr_tab_atualizado(tab);

            // Mostrar informações
            if (lin_o != 0 && col_o != 0 && lin_d != 0 && col_d != 0) // Se o jogaror não tiver finalizado o jogo
            {
                // Apresenta informações sobre o salto
                info_jogada(lin_o, col_o, lin_d, col_d, num_pedras, &num_total, &num_rest);
                num_salto++;    // Incrementa o numero de saltos
            }

        } while (lin_o != 0 && col_o != 0 && lin_d != 0 && col_d != 0);

        // Mostrar o nivel de dificuldade e número de saltos
        nivel_dificuldade(num_total, num_salto);

        // Perguntar se quer repetir o jogo
        printf("\nDeseja jogar novamente? (S/N)\n");
        scanf(" %c", &opc);

    } while (opc == 'S' || opc == 's');

    if (opc == 'N' || opc == 'n')
    {
        printf("\nParabéns!\n");
    }
}
