#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct elemento{
  char nome[100];
}t_elemento;

typedef struct no{
  struct no * esquerda;
  t_elemento dado;
  struct no * direita;
}t_no;

typedef t_no * t_arvore;


t_no * criar(){

  t_no * no = (t_no*) malloc(sizeof(t_no));

  if(no){
    no->esquerda = no->direita = NULL;
  }

  return no;
}

int comparar(t_elemento dado1, t_elemento dado2){
  return strcmp(dado1.nome, dado2.nome);
}

int inserir(t_arvore * arvore, t_elemento dado, int alert){

  int resultado;
  int falso = 0;


  if(*arvore == NULL){
    *arvore = criar();
    if(*arvore == NULL){
      system("clear");
      printf("\n\t\tERRO!! NÃO FOI POSSÍVEL INSERIR NA ÁRVORE.\n");
      sleep(1);
      return 0;
    }
    (*arvore)->dado = dado;
    printf("\t\t-- RAIZ DA ÁRVORE.\n");
    sleep(1);
    return 1;
  }

  if(comparar((*arvore)->dado, dado) < 0){
    resultado = inserir(&((*arvore)->direita), dado, falso);

    if(resultado){
      printf("\t\t-- ELEMENTO INSERIDO A DIREITA.\n");
      sleep(1);
    }
  }else{
    if (comparar((*arvore)->dado, dado) > 0){
      resultado = inserir(&((*arvore)->esquerda), dado, falso);

      if(resultado){
        printf("\t\t-- ELEMENTO INSERIDO A ESQUERDA.\n");
        sleep(1);
      }
    }else{
      resultado = 0;
      system("clear");
      printf("\n\t\tERRO!! ESSE ELEMENTO JÁ EXISTE, NÃO FOI POSSÍVEL INSERIR NA ÁRVORE,\n");
      sleep(1);
    }
  }

  if (resultado && alert) {
    system("clear");
    printf("\n\t\t\tINSERIDO COM SUCESSO!!\n");
    sleep(1);
  }

  return resultado;
}


t_elemento criarElemento(){
  t_elemento dado;
  char nome[100];

  printf("\nINFORME UM NOME: ");
  scanf("%s", nome);

  strcpy(dado.nome, nome);

  return dado;
}

t_no * buscaSetPai(t_arvore arvore, t_elemento dado, t_no ** pai){

  if(arvore == NULL){
    *pai = NULL;
    return NULL;
  }

  if(comparar(arvore->dado, dado) == 0){
    return arvore;
  }

  if(comparar(arvore->dado, dado) > 0){
    *pai = arvore;
    return buscaSetPai(arvore->esquerda, dado, pai);
  }else{
    *pai = arvore;
    return buscaSetPai(arvore->direita, dado, pai);
  }
}


t_no * buscar(t_arvore * arvore, t_elemento dado) {

  system("clear");
  printf("\n\t\t\tBUSCANDO...\n");
  sleep(1);

  if((*arvore) == NULL){

    system("clear");
    printf("\n\t\tESSE ELEMENTO NÃO EXISTE NA ÁRVORE!!\n");
    sleep(1);
    return NULL;
  }

  if(comparar((*arvore)->dado, dado) == 0){
    system("clear");
    printf("\n\t\tO ELEMENTO '%s' FOI ENCONTRADO NA ÁRVORE!!\n", dado.nome);
    sleep(1);
    return *arvore;
  }

  if(comparar((*arvore)->dado, dado) < 0){
    return buscar(&((*arvore)->direita), dado);
  }else{
    return buscar(&((*arvore)->esquerda), dado);
  }
}

int remover(t_arvore * arvore, t_elemento dado){

  t_no * no,
       * pai,
       * substitutoNo,
       * paiSucessor,
       * sucessor;

  no = *arvore;
  pai = NULL;
  no = buscaSetPai(*arvore, dado, &pai);

  system("clear");
  printf("\n\t\t\tREMOVENDO...\n");
  sleep(1);

  if(no == NULL){
    system("clear");
    printf("\n\t\tNÃO FOI POSSÍVEL REMOVER\n");
    sleep(1);
    return 0;
  }

  if(no->esquerda == NULL){
    substitutoNo = no->direita;
  }else{
    if(no->direita == NULL){
      substitutoNo = no->esquerda;
    }else{
      paiSucessor = no;
      substitutoNo = no->direita;
      sucessor = substitutoNo->esquerda;

      while (sucessor != NULL) {
        paiSucessor = substitutoNo;
        substitutoNo = sucessor;
        sucessor = substitutoNo->esquerda;
      }

      if(paiSucessor != no){
        paiSucessor->esquerda = substitutoNo->direita;
        substitutoNo->direita = no->direita;
      }

      substitutoNo->esquerda = no->esquerda;
    }
  }

  if(pai == NULL){
    *arvore = substitutoNo;
  }else{
    if(no == pai->esquerda){
      pai->esquerda = substitutoNo;
    }else{
      pai->direita = substitutoNo;
    }
  }

  system("clear");
  printf("\n\t\t\tREMOVIDO COM SUCESSO!!\n");
  sleep(1);

  free(no);
  return 1;
}

int esvaziarArvore(t_arvore * arvore){

  system("clear");
  printf("\n\t\t\tESVAZIANDO...\n");
  sleep(1);

  if(*arvore == NULL){
    printf("A ÁRVORE JÁ ESTÁ VAZIA\n");
    return 0;
  }

  esvaziarArvore(&((*arvore)->esquerda));
  esvaziarArvore(&((*arvore)->direita));

  free(*arvore);
  *arvore = NULL;

  return 1;
}

void salvarInOrdem(t_arvore arvore, FILE * arquivo){

  if(arvore != NULL){
    fseek(arquivo, 0, SEEK_END);
    fprintf(arquivo, "%s - ", arvore->dado.nome);
    salvarInOrdem(arvore->esquerda, arquivo);
    salvarInOrdem(arvore->direita, arquivo);
  }

}

int salvarArquivo(t_arvore * arvore){

  FILE * arquivo;

  arquivo = fopen("ArvoreBinariaPesquisa.csv", "w+");

  if(arquivo == 0){
    printf("ERRO AO ABRIR O ARQUIVO");
    return 0;
  }

  salvarInOrdem(*arvore, arquivo);
  fclose(arquivo);

  return 1;
}

void lerInOrdem(FILE * arquivo, t_arvore * arvore){
  t_elemento dado;
  char load[1000] = { };
  int falso = 0;

  while (!feof(arquivo)) {
    fscanf(arquivo, "%s - ", dado.nome);
    system("clear");
    strcat(load, ".");
    printf("\n\tCARREGANDO A ÁRVORE, AGUARDE... %s\n\n", load);
    inserir(&(*arvore), dado, falso);
  }
  sleep(1);
}

//**  INTERFACE  **//

void menu(char * opcao){

  system("clear");
  printf("\n**--------------------------------------------------**\n\n");
  printf(" ALUNO: DANILLO RODRIGUES DE ALMEIDA\n");
  printf(" MATRICULA: 1610014885\n");
  printf(" DISCIPLINA: ESTRUTURA DE DADOS I\n");
  printf(" PROFESSOR: WALACE BONFIM\n\n\n\n");


  printf("**-------- EDITOR DE ÁRVORE BINÁRIA DE PESQUISA --------**\n\n\n");

  printf("ESCOLHA UMA DAS OPÇÕES: \n\n");
  printf("| 1 | - INSERIR NA ÁRVORE\n");
  printf("| 2 | - REMOVER APENAS UM NÓ\n");
  printf("| 3 | - PESQUISAR\n");
  printf("| 4 | - ESVAZIAR A ÁRVORE\n");
  printf("| 5 | - EXIBIR A ÁRVORE\n");
  printf("| 0 | - SAIR\n\n");

  scanf(" %c", opcao);
  setbuf(stdin, NULL);
}


void menuExibirArvore(char * opcao){

  system("clear");
  printf("**-------- EXIBIR A ÁRVORE --------**\n\n\n");

  printf("ESCOLHA UMA DAS OPÇÕES: ");
  printf(" | 1 | - EXIBIR EM PRÉ-ORDEM\n");
  printf(" | 2 | - EXIBIR EM IN-ORDEM\n");
  printf(" | 3 | - EXIBIR EM PÓS-ORDEM\n");
  printf(" | 4 | - EXIBIR ÁRVORE GRAFICAMENTE\n");
  printf(" | 0 | - VOLTAR PARA O MENU PRINCIPAL\n\n");

  scanf("%c", opcao);
  setbuf(stdin, NULL);
}

void PreOrdem(t_arvore * arvore){

  if((*arvore) != NULL){
    printf("%s - ", (*arvore)->dado.nome);
    PreOrdem(&((*arvore)->esquerda));
    PreOrdem(&((*arvore)->direita));
  }
}

void InOrdem(t_arvore * arvore){

  if((*arvore) != NULL){
    InOrdem(&((*arvore)->esquerda));
    printf("%s - ", (*arvore)->dado.nome);
    InOrdem(&((*arvore)->direita));
  }
}

void PosOrdem(t_arvore * arvore){

  if((*arvore) != NULL){
    PosOrdem(&((*arvore)->esquerda));
    PosOrdem(&((*arvore)->direita));
    printf("%s - ", (*arvore)->dado.nome);
  }
}

void gotoxy(int x, int y) {
    printf("%c[%d;%df", 0x1B, y, x);
}

void ExibirGraficamente(t_arvore * arvore, int coluna, int linha, int desloc){

  if ((*arvore) == NULL) {
    return;
  }

  gotoxy(coluna, linha);

  printf("%s", (*arvore)->dado.nome);

  if((*arvore)->esquerda != NULL){
    ExibirGraficamente(&((*arvore)->esquerda), coluna - desloc, linha + 2, desloc / 2+1);
  }

  if((*arvore)->direita != NULL){
    ExibirGraficamente(&((*arvore)->direita), coluna + desloc, linha + 2, desloc / 2+1);
  }
}

void exibirArvore(t_arvore arvore){

int loop = 1;
char sair[1000];
char opcao;

do {

  opcao = ' ';
  menuExibirArvore(&opcao);

  switch (opcao) {
    case '0':
      loop = 0;
      break;

    case '1':
      do{
        system("clear");
        printf("PRÉ-ORDEM: ");
        printf("\n\n\t\t[ ");
        PreOrdem(&arvore);
        printf("]");

        printf("\n\n | 0 | - SAIR");
        scanf("%s", sair);
      }while(strcmp(sair, "0"));
      break;

    case '2':
      do{
        system("clear");
        printf("IN-ORDEM: ");
        printf("\n\n\t\t[ ");
        InOrdem(&arvore);
        printf("]");

        printf("\n\n | 0 | - SAIR");
        scanf("%s", sair);
      }while(strcmp(sair, "0"));
      break;

    case '3':
      do{
        system("clear");
        printf("PÓS-ORDEM: ");
        printf("\n\n\t\t[ ");
        PosOrdem(&arvore);
        printf("]");

        printf("\n\n | 0 | - SAIR");
        scanf("%s", sair);
      }while(strcmp(sair, "0"));
      break;

    case '4':
      do{
        system("clear");
        printf("GRAFICAMENTE: ");
        ExibirGraficamente(&arvore, 30, 5, 5);

        printf("\n\n | 0 | - SAIR");
        scanf("%s", sair);
      }while(strcmp(sair, "0"));
      break;

    default:
      system("clear");
      printf("\n\tOPÇÃO INVÁLIDA!! TENTE NOVAMENTE.\n");
      sleep(1);
      break;

  }
} while(loop);

}

//**  ARQUIVO  **//

int lerArquivo(t_arvore * arvore){

  FILE * arquivo;

  arquivo = fopen("ArvoreBinariaPesquisa.csv", "r");

  if(arquivo == 0){
    return 0;
  }

  lerInOrdem(arquivo, &(*arvore));
  fclose(arquivo);

  return 1;
}

int main() {

  t_arvore arvore = NULL;
  t_elemento dado;
  int loop = 1;
  char opcao;
  int truue = 1;
  int alert;

  lerArquivo(&arvore);

do {

  opcao = ' ';
  menu(&opcao);

  switch (opcao) {
    case '0':

      loop = 0;
      break;

    case '1':

      dado = criarElemento();
      inserir(&arvore, dado, truue);
      salvarArquivo(&arvore);
      break;

    case '2':

      dado = criarElemento();
      remover(&arvore, dado);
      salvarArquivo(&arvore);
      break;

    case '3':

      dado = criarElemento();
      buscar(&arvore, dado);
      break;

    case '4':

      alert = esvaziarArvore(&arvore);
      salvarArquivo(&arvore);
      if(alert){
        system("clear");
        printf("\n\t\t\tÁRVORE ESVAZIADA COM SUCESSO!!\n");
        sleep(1);
      }
      break;

    case '5':

      exibirArvore(arvore);
      break;

    default:
      system("clear");
      printf("\n\tOPÇÃO INVÁLIDA, ESCOLHA ALGUMA OPÇÃO VÁLIDA NO MENU.\n");
      sleep(1);
      break;

  }
} while(loop);
}
