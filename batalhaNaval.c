#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define TAMANHO_SKILL 5
#define EFEITO_SKILL 5

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

/**
 * @brief Posiciona um navio no tabuleiro após validar os limites e a sobreposição.
 * 
 * @param tabuleiro A matriz do jogo.
 * @param linha A linha inicial do navio (0-9).
 * @param coluna A coluna inicial do navio (0-9).
 * @param tamanho O número de células que o navio ocupa.
 * @param orientacao 'H' (Horizontal), 'V' (Vertical), 'D' (Diagonal Principal), 'S' (Diagonal Secundária).
 * @return int Retorna 1 em caso de sucesso, 0 em caso de falha.
 */
int posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, char orientacao) {
    // 1. Validação de limites do tabuleiro
    if ((orientacao == 'H' && (coluna + tamanho > TAMANHO_TABULEIRO)) ||
        (orientacao == 'V' && (linha + tamanho > TAMANHO_TABULEIRO)) ||
        (orientacao == 'D' && (linha + tamanho > TAMANHO_TABULEIRO || coluna + tamanho > TAMANHO_TABULEIRO)) ||
        (orientacao == 'S' && (linha + tamanho > TAMANHO_TABULEIRO || coluna - tamanho < -1))) {
        return 0; // Falha: Fora dos limites
    }

    // 2. Validação de sobreposição
    for (int i = 0; i < tamanho; i++) {
        if ((orientacao == 'H' && tabuleiro[linha][coluna + i] != AGUA) ||
            (orientacao == 'V' && tabuleiro[linha + i][coluna] != AGUA) ||
            (orientacao == 'D' && tabuleiro[linha + i][coluna + i] != AGUA) ||
            (orientacao == 'S' && tabuleiro[linha + i][coluna - i] != AGUA)) {
            return 0; // Falha: Sobreposição detectada
        }
    }

    // 3. Posicionamento do navio
    for (int i = 0; i < tamanho; i++) {
        if (orientacao == 'H') tabuleiro[linha][coluna + i] = NAVIO;
        else if (orientacao == 'V') tabuleiro[linha + i][coluna] = NAVIO;
        else if (orientacao == 'D') tabuleiro[linha + i][coluna + i] = NAVIO;
        else if (orientacao == 'S') tabuleiro[linha + i][coluna - i] = NAVIO;
    }
    return 1; // Sucesso
}

/**
 * @brief Exibe o tabuleiro do jogo no console com um título.
 * 
 * @param tabuleiro A matriz do jogo a ser exibida.
 * @param titulo O título a ser exibido acima do tabuleiro.
 */
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], const char* titulo) {
    printf("\n%s\n\n", titulo);

    // Imprime o cabeçalho das colunas (A - J)
    printf("   "); // Espaço para os números das linhas
    for (char c = 'A'; c < 'A' + TAMANHO_TABULEIRO; c++) {
        printf("%c ", c);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Imprime o número da linha (1 - 10)
        printf("%2d ", i + 1);

        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief Sobrepõe uma matriz de habilidade no tabuleiro principal.
 * 
 * @param tabuleiro O tabuleiro principal do jogo.
 * @param habilidade A matriz 5x5 que define o padrão da habilidade.
 * @param origem_linha A linha de origem (canto superior esquerdo) para aplicar a habilidade.
 * @param origem_coluna A coluna de origem para aplicar a habilidade.
 */
void aplicar_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_SKILL][TAMANHO_SKILL], int origem_linha, int origem_coluna) {
    for (int i = 0; i < TAMANHO_SKILL; i++) {
        for (int j = 0; j < TAMANHO_SKILL; j++) {
            if (habilidade[i][j] == 1) {
                int linha_alvo = origem_linha + i;
                int coluna_alvo = origem_coluna + j;
                if (linha_alvo >= 0 && linha_alvo < TAMANHO_TABULEIRO && coluna_alvo >= 0 && coluna_alvo < TAMANHO_TABULEIRO) {
                    tabuleiro[linha_alvo][coluna_alvo] = EFEITO_SKILL;
                }
            }
        }
    }
}

int main() {
    // Nível Novato - Posicionamento dos Navios

    // Criação e inicialização do tabuleiro 10x10 com 0 (água)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int i, j;

    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // Posicionamento dos navios usando a função de validação
    // Coordenadas são baseadas em índice 0 (linha 3 = índice 2, coluna D = índice 3)
    posicionar_navio(tabuleiro, 2, 3, TAMANHO_NAVIO, 'H'); // Horizontal
    posicionar_navio(tabuleiro, 5, 7, TAMANHO_NAVIO, 'V'); // Vertical
    posicionar_navio(tabuleiro, 0, 0, TAMANHO_NAVIO, 'D'); // Diagonal Principal
    posicionar_navio(tabuleiro, 0, 9, TAMANHO_NAVIO, 'S'); // Diagonal Secundária

    exibir_tabuleiro(tabuleiro, "Tabuleiro Inicial do Jogo:");

    // Nível Mestre - Habilidade 'Cone'
    printf("\n--- Nivel Mestre: Habilidade em Area ---\n");

    // 1. Criação da matriz da habilidade 'Cone' 5x5
    int habilidade_cone[TAMANHO_SKILL][TAMANHO_SKILL];
    for (i = 0; i < TAMANHO_SKILL; i++) {
        for (j = 0; j < TAMANHO_SKILL; j++) {
            // Condicionais para desenhar a forma do cone (apontando para baixo)
            if ((i == 2) || (i == 1 && j >= 1 && j <= 3) || (i == 0 && j == 2)) {
                habilidade_cone[i][j] = 1; // Posição afetada
            } else {
                habilidade_cone[i][j] = 0; // Posição não afetada
            }
        }
    }

    int origem_linha_cone = 4;
    int origem_coluna_cone = 2; // Corresponde à coluna 'C'
    printf("Aplicando habilidade 'Cone' com origem na posicao %d-%c.\n", origem_linha_cone + 1, 'A' + origem_coluna_cone);
    aplicar_habilidade(tabuleiro, habilidade_cone, origem_linha_cone, origem_coluna_cone);
    exibir_tabuleiro(tabuleiro, "Tabuleiro com habilidade 'Cone' aplicada:");

    // Implementação da habilidade 'Cruz'
    int habilidade_cruz[TAMANHO_SKILL][TAMANHO_SKILL];
    int centro_skill = TAMANHO_SKILL / 2; // O centro de uma matriz 5x5 é o índice 2

    for (i = 0; i < TAMANHO_SKILL; i++) {
        for (j = 0; j < TAMANHO_SKILL; j++) {
            // A condição para uma cruz é que a célula esteja na linha central OU na coluna central
            if (i == centro_skill || j == centro_skill) {
                habilidade_cruz[i][j] = 1;
            } else {
                habilidade_cruz[i][j] = 0;
            }
        }
    }

    int origem_linha_cruz = 0;
    int origem_coluna_cruz = 4; // Corresponde à coluna 'E'
    printf("\nAplicando habilidade 'Cruz' com origem na posicao %d-%c.\n", origem_linha_cruz + 1, 'A' + origem_coluna_cruz);
    aplicar_habilidade(tabuleiro, habilidade_cruz, origem_linha_cruz, origem_coluna_cruz);
    exibir_tabuleiro(tabuleiro, "Tabuleiro com habilidade 'Cruz' aplicada:");

    // Implementação da habilidade 'Octaedro'
    int habilidade_octaedro[TAMANHO_SKILL][TAMANHO_SKILL];

    for (i = 0; i < TAMANHO_SKILL; i++) {
        for (j = 0; j < TAMANHO_SKILL; j++) {
            // Condição explícita para a forma de octaedro/diamante
            if ((i == centro_skill && j == centro_skill) || // Ponto central
                (i == centro_skill - 1 && j == centro_skill) || // Ponto acima
                (i == centro_skill + 1 && j == centro_skill) || // Ponto abaixo
                (i == centro_skill && j == centro_skill - 1) || // Ponto à esquerda
                (i == centro_skill && j == centro_skill + 1)) { // Ponto à direita
                habilidade_octaedro[i][j] = 1;
            } else {
                habilidade_octaedro[i][j] = 0;
            }
        }
    }

    int origem_linha_octa = 6;
    int origem_coluna_octa = 5; // Corresponde à coluna 'F'
    printf("\nAplicando habilidade 'Octaedro' com origem na posicao %d-%c.\n", origem_linha_octa + 1, 'A' + origem_coluna_octa);
    aplicar_habilidade(tabuleiro, habilidade_octaedro, origem_linha_octa, origem_coluna_octa);
    exibir_tabuleiro(tabuleiro, "Tabuleiro com habilidade 'Octaedro' aplicada:");

    return 0;
}