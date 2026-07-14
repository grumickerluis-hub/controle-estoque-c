#include <stdio.h>
#include <string.h>

void listar_produtos(char nomes[50][50], int qtde[50], double precos[50], int totalProdutos) {
	printf("----------Lista de Produtos----------\n");

	if(totalProdutos == 0) {
		printf("Nenhum produto cadastrado!\n");
	} else {
		for(int i = 0; i < totalProdutos; i++) {
			printf("%d - %s | Quantidade: %d | Preço: R$ %.2lf\n", i + 1, nomes[i], qtde[i], precos[i]);
		}
	}
}
int cadastrar_produto(char nomes[50][50], int qtde[50], double precos[50], int totalProdutos) {
	if (totalProdutos >= 50) {
		printf("Limite de produtos atingido!\n");
		return totalProdutos;
	}
	printf("Nome do produto: ");
	while(getchar() != '\n');
	fgets(nomes[totalProdutos], 50, stdin);
	nomes[totalProdutos][strcspn(nomes[totalProdutos], "\n")] = '\0';

	printf("Quantidade: ");
	scanf("%d", &qtde[totalProdutos]);

	printf("Preço: ");
	scanf("%lf", &precos[totalProdutos]);

	totalProdutos++;

	printf("Produto cadastrado com sucesso!\n");

	return totalProdutos;
}
void registrar_venda(char nomes[50][50], int qtde[50], double precos[50], int totalProdutos, int historico[50][12]) {
	int produto, vendas;

	printf("Registrar vendas\n");

	if(totalProdutos == 0) {
		printf("Nenhum produto cadastrado!\n");
	} else {
		listar_produtos(nomes, qtde, precos, totalProdutos);

		printf("Escolha o produto: \n");
		scanf("%d", &produto);
		produto--;

		printf("Quantidade vendida: \n");
		scanf("%d", &vendas);

		if(produto < 0 || produto >= totalProdutos) {
			printf("Produto inválido!\n");
		} else if(vendas > qtde[produto]) {
			printf("Estoque insuficiente!\n");
		} else {
			qtde[produto] -= vendas;
			historico[produto][0] += vendas;
			printf("Venda registrada com sucesso!\n");
			printf("Valor Total: R$ %.2lf\n", vendas * precos[produto]);
		}
	}
}
void relatorio(char nomes[50][50], int qtde[50], double precos[50], int totalProdutos, int historico[50][12]) {

	printf("Relatório\n");

	double valortotal = 0;
	int maior = 0, menor = 0;

	if(totalProdutos == 0) {
		printf("Nenhum produto cadastrado!\n");
	} else {

		printf("Total de produtos cadastrados: %d\n", totalProdutos);

		for(int i = 0; i < totalProdutos; i++) {

			valortotal += qtde[i] * precos[i];

			if(qtde[i] > qtde[maior]) {
				maior = i;
			}

			if(qtde[i] < qtde[menor]) {
				menor = i;
			}
		}
		printf("\nHistórico de vendas:\n");

		for(int i = 0; i < totalProdutos; i++) {
			printf("%s - %d unidades vendidas\n", nomes[i], historico[i][0]);
		}

		printf("Valor total do estoque: R$ %.2lf\n", valortotal);
		printf("Maior estoque: %s - %d unidades\n", nomes[maior], qtde[maior]);
		printf("Menor estoque: %s - %d unidades\n", nomes[menor], qtde[menor]);
	}
}
int main () {

	int opcao;
	int totalProdutos = 0;

	char nomes[50][50];
	int qtde[50];
	double precos[50];
	int historico[50][12] = {0};

	do {
		printf("\n---------Sistema de Estoque---------\n");
		printf("1 - Cadastrar Produto\n");
		printf("2 - Listar Produtos\n");
		printf("3 - Registrar Vendas\n");
		printf("4 - Relatório\n");
		printf("0 - Sair\n");
		printf("Escolha uma opção: ");
		scanf("%d", &opcao);

		switch(opcao) {
		case 1:
			totalProdutos = cadastrar_produto(nomes, qtde, precos, totalProdutos);
			break;
		case 2:
			listar_produtos(nomes, qtde, precos, totalProdutos);
			break;
		case 3:
			registrar_venda(nomes, qtde, precos, totalProdutos, historico);
			break;
		case 4:
			relatorio(nomes, qtde, precos, totalProdutos, historico);
			break;
		case 0:
			printf("Saindo...\n");
			break;
		default:
			printf("Opção Inválida!\n");
		}
	} while(opcao != 0);


	return 0;
}