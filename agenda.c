#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    char telefone[13]; 
} Contato;

// declaração de funções
int menu();
int consultar();
int adicionar();
int excluir();


Contato dados_salvos;
int opcao;

int menu() {
    printf("Escolha uma opcao:\n");
    printf("1. Consultar Contato\n");
    printf("2. Adicionar Contato\n");
    printf("3. Excluir Contato\n");
    printf("4. Sair\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            consultar();
            break;
        case 2:
            adicionar();
            break;
        case 3:
            excluir();
            break;
        case 4:
            printf("SAINDO\n");
            break;
        default:
            printf("Opcao Invalida\n");
            break;
    }
    return opcao;
}

// função consultar
int consultar() {
    char ctt_consulta[50];
    int ctt_salvo = 0;
    FILE *principal_arq;

    printf("Digite um contato para pesquisar: ");
    scanf("%s", ctt_consulta);

    if ((principal_arq = fopen("contatos.bin", "rb")) == NULL) {  // rb= leitura binaria
        printf("Contato não Existe!\n");
        return 1;
    }
    while (fread(&dados_salvos, sizeof(Contato), 1, principal_arq) == 1) {
        if (strcmp(dados_salvos.nome, ctt_consulta) == 0) {
            printf("Nome: %s \nTelefone: %s\n\n", dados_salvos.nome, dados_salvos.telefone);
            ctt_salvo = 1;
            break;
        }
    }
    if (ctt_salvo == 0) {
        printf("Contato não encontrado\n");
    }

    fclose(principal_arq);
    return 0;
}

// função adicionar contato
int adicionar() {
    FILE *principal_arq;
    principal_arq = fopen("contatos.bin", "ab"); //ab = Abre o arquivo para escrita no final do arquivo. Se o arquivo não existir, será criado.
    if (principal_arq == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }

    printf("Nome do Contato: ");
    scanf("%s", dados_salvos.nome);
    fflush(stdin); 

    printf("Telefone do Contato: ");
    scanf("%s", dados_salvos.telefone);
    fflush(stdin);

    fwrite(&dados_salvos, sizeof(Contato), 1, principal_arq);
    fclose(principal_arq);

    return 0;
}

// função excluir contato
int excluir() {
    char ctt_consulta[50];
    int ctt_localiza = 0;
    FILE *principal_arq, *temp_arq;

    printf("Qual contato deseja remover?: ");
    scanf("%s", ctt_consulta);

    if ((principal_arq = fopen("contatos.bin", "rb")) == NULL) {  // rb= abrir o arquivo para leitura no modo binário
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }
    temp_arq = fopen("temp.bin", "wb");
    if (temp_arq == NULL) {
        printf("Erro ao criar arquivo binario!\n");
        fclose(principal_arq);
        return 1;
    }

    while (fread(&dados_salvos, sizeof(Contato), 1, principal_arq)) {
        if (strcmp(dados_salvos.nome, ctt_consulta) == 0) {
            printf("Nome: %s \nTelefone: %s\n", dados_salvos.nome, dados_salvos.telefone);
            ctt_localiza = 1;
            int opc = 0;
            printf("Tem certeza que deseja excluir esse contato?\n 1. Sim\n 2. Nao\n");
            scanf("%d", &opc);
            if (opc == 1) {
                printf("Contato excluido\n");
            } else {
                printf("\nOpcao cancelada.\n");
                fwrite(&dados_salvos, sizeof(Contato), 1, temp_arq);
            }
        } else {
            fwrite(&dados_salvos, sizeof(Contato), 1, temp_arq);
        }
    }
    if (!ctt_localiza) {
        printf("Esse contato não existe.\n");
    }

    fclose(principal_arq);
    fclose(temp_arq);
    remove("contatos.bin");
    rename("temp.bin", "contatos.bin");

    return 0;
}

int main() {    //funçaõ principal para exibir menu
    while (menu() != 4) { 
    return 0;
}
