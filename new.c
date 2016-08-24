
/***********************************************
 * 	   Software para academias - beta 0.0.1    *
 * Desenvolvedores: Tiado David & Luis Eduardo *
 * ********************************************/

#include <stdio.h>
#include <stdlib.h>

// variaveis globais
unsigned char cpf[15], telefone[15], nome[50];
char refazer_cadastro, refazer_cadastro2, procurar_cadastro;
int menu, menu_case;
// Escolher qual cadastro modificar
void cadastro();
// Iniciar programa
void start();
// modificar cadastro dentro de cadastro()
void modifica();
// teste no banco de dados
/*void banco();

//Testes com o banco de dados
void banco(){
	
	MYSQL conexao;//variavel de conexão
	int ret;//variavel de retorno para o a insersão
	
	mysql_init(&conexao); //conectando-se ao banco

 	if(mysql_real_connect(&conexao,"127.0.0.1", "root", "181997", "cadastro", 0, NULL, 0))
	{
		printf("Conexão com sucesso!!!!!!\n");
		ret = mysql_query(&conexao, "INSERT INTO alunos(cpf, nome, telefone) VALUES(%s, %s, %s);"); 
	}
	if(ret)
	{
		printf("Não inseriu!\n");
		printf("Erro%d: %s\n", mysql_errno(&conexao), mysql_error(&conexao));
		
	}
	else
	{
		printf("Inseriu%d\n", mysql_affected_rows(&conexao));
		printf("Conectou!!!!\n");
	}
	mysql_close(&conexao);
}

*/
void modifica (char *vari) {
	printf("Informe o novo : ");
	scanf(" %[^\n]s", vari);
	printf("---------------------------------------\n");
	printf("Nome: %s\nCPF: %s\nTelefone: %s\n", nome, cpf, telefone);
	start();
}

void cadastro() {
	printf("\n[A] Todos os dados\n[N] - Nome\n[T] - Telefone\n[C] - CPF\n");
	printf("O que deseja modificar?\n");
	// tem q fazer pra deixar padrão o tamanho das letras
	scanf("%s", &refazer_cadastro2);
	switch (refazer_cadastro2) 
	{
		// Nome
		case 'n':
			modifica(nome);
			start();
			break;
		// Telefone
		case 't':
			// Modiciar telefone, void modifca()
			modifica(telefone);
			start();
			break;
		// CPF
		case 'c':
			// Modiciar cpf, void modifca()
			modifica(cpf);
			start();
			break;
		// todos - all
		case 'a':
			// Nome
			printf("Informe o nome a ser cadastrado: ");
			scanf(" %[^\n]s", nome);
			// CPF
			printf("Informe o CPF a ser cadastrado: ");  
			scanf("%s", cpf);
			// Fone
			printf("Informe o Telefone a ser cadastrado: "); 
			scanf("%s", telefone);
			// return
			printf("---------------------------------------\n");
			printf("Nome: %s\nCPF: %s\nTelefone: %s\n", nome, cpf, telefone);
			start();
			break;
		// Padrão
		default:
		printf("Valor Informado não válido!\n");
		printf("---------------------------------------\n");
		printf("Nome: %s\nCPF: %s\nTelefone: %s\n", nome, cpf, telefone);
		printf("---------------------------------------\n");
		cadastro();
	}
}

void start()
{
	// Menu
	printf("---------------------------------------\n");
	printf("\n[1]  -  Novo Cadastro\n");
	printf("[2]  -  Consultar Cadastros\n");
	printf("[3]  -  Financeiro\n\n");
	printf("[0]  -  Sair\n\n");
	printf("---------------------------------------\n");
	printf("Digite uma opção: ");	

	scanf("%i", &menu_case); 
	switch(menu_case) 
	{
		// Terminar Sessão
		case 0:
			printf("\nTem certeza que deseja sair? \n");
			printf("[1] - Voltar | [0] - Sair ");
			scanf("%i", &menu_case);

			if(menu_case == 1) {
				start();
			}	

			else {
				break;
			}

		// Cadastro
		case 1:
			// Username
			printf("Informe o Nome: ");
			scanf("%s[^\n]", nome);
			
			// CPF
			printf("Informe o CPF: ");  
			scanf("%s", cpf);
			
			// Fone
			printf("Informe o Telefone: "); 
			scanf("%s", telefone);

			// Criando....
			//printf("Horario [M] | [T] | [N] | [G]\n");

			printf("---------------------------------------\n");
			printf("Nome: %s\nCPF: %s\nTelefone: %s\n", nome, cpf, telefone);
			printf("---------------------------------------\n");
			printf("Os dados informados estão corretos? [S/N]: ");
			scanf("%s", &refazer_cadastro);
			// Em teste....
			if (refazer_cadastro == 's' || refazer_cadastro == 'S')
			{
				printf("\n\nCadastro realizado com sucesso!!\n\n");
				//voltar ao inicio
				start();
				/*
				try:
					enviar pra db;
					printf("Enviado com sucesso");
				execpt ERRO:
					printf("Erro ao enviar");
					// tem q fazer uma treta dessa!
				*/
			}
			else
			{
				//refazer cadastro: void cadastro()
				cadastro();
			}

			break;

		// Consultar cadastro
		case 2:
			printf("Procura por: \n[1] Telefone | [2] CPF \n");
			scanf("%s", &procurar_cadastro);
			if (procurar_cadastro == '1') {
				printf("Procurar por telefone\n");
				//db
			}
			else if (procurar_cadastro == '2')
			{
				printf("Procurar por CPF\n");
				//db
			}

			else {
				printf("---------------------------------------\n");
				printf("--> [ERRO!] Opção inválida! <--\n");
				start();
				break;
			}
			break;
		
		// Financeiro
		case 3:
			printf("Financeiro\n");
			
			/* Menu
			verificar pagamentos proximos = 1
			verificar pagamento expecifico = 2
			*/

			// if = 1
			/* calculo (data de cadastro + 25 dias)
			 *	retornar todos os cadastro que faltam 5 dias para o pagamento.
			 */
			//if = 2
			/*
			 * Veriricar por CPF ou por Telefone.
			 */
			break;
		default:
			printf("\n\n---------------------------------------\n");
			printf("[ERRO!] Opção inválida!\n");
			start();
	}
}


int main() {
	start();
 	return 0;
}
