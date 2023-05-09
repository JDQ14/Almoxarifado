#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;
int funcaoADMIN();
int usuarioNormal();
int main();
struct produto
{
	string nome;
	int codigo;
	int qtd_estoque;
	long long cod_fornecedor;
	int tipo_produto;
	double valor_produto;
};
struct data_venda{
	int dia, mes, ano;
};
struct venda {
	string codigo_produto;
	int quantidade;
	float valor_compra;
	data_venda data_venda;
};
void exibir_vetor(produto* pcadastro, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << pcadastro[i].nome << endl;
		cout << pcadastro[i].codigo << endl;
		cout << pcadastro[i].qtd_estoque << endl;
		cout << pcadastro[i].cod_fornecedor << endl;
		cout << pcadastro[i].tipo_produto << endl;
		cout << pcadastro[i].valor_produto << endl;
	}
}
int funcaoVenda() {
	string codigo_venda;
	ofstream fout;
	fout.open("venda.txt", ios_base::out | ios_base::app);
	if (!fout.is_open())
	{
		cout << "Nçao foi possível abrir o arquivo!\n";
		system("pause");
		exit(EXIT_FAILURE);
	}
	char escolha_compra_qtd;
	int cod_fornecedor;
	int tipo_produto;
	float preço_produto;
	string codigo_venda_arquivo;
	string qtd_venda;
	string estoque;
	double valor_total_compra;
	bool produto_encontrado = false;
	char continuar_compra;
	ifstream fin;
	venda venda;
	//bool escolha = false;

	fin.open("produtos.txt");

	cout << "      [FUNCAO VENDA INICIADA]\n\n\n";
	
		cout << "Digite o codigo de barras do produto: ";
		cin >> codigo_venda;

		fin >> codigo_venda_arquivo;
		while (fin.good())
		{
			if (codigo_venda == codigo_venda_arquivo)
			{
				produto_encontrado = true;
				cout << "Produto encontrado!\n\n";
				cout << "Quantidade: ";
				cin >> qtd_venda;
				fin >> estoque;
				if (qtd_venda <= estoque)
				{
					fin >> cod_fornecedor;
					fin >> tipo_produto;
					fin >> preço_produto;
					fin.close();
					int qtd_venda_int = stoi(qtd_venda);
					valor_total_compra = preço_produto * qtd_venda_int;

					venda.codigo_produto = codigo_venda;
					fout << venda.codigo_produto << " ";
					venda.quantidade = qtd_venda_int;
					fout << venda.quantidade << " ";
					venda.valor_compra = valor_total_compra;
					fout << venda.valor_compra << " ";
					cout << endl << "Valor total da compra: " << venda.valor_compra << endl;
					cout << "Data da compra:\n\n\n";
					cout << "Dia da compra: ";
					cin >> venda.data_venda.dia; cout << endl;
					fout << venda.data_venda.dia << "/";
					cout << "Mes da compra: ";
					cin >> venda.data_venda.mes;
					fout << venda.data_venda.mes << "/";
					cout << "Ano da compra: ";
					cin >> venda.data_venda.ano;
					fout << venda.data_venda.ano << "\n";
					fout.close();
					cout << "Deseja realizar outra compra?[S/N]\n";
					cout << ">> "; cin >> continuar_compra;
					if (continuar_compra == 'S' || continuar_compra == 's')
					{
						return funcaoVenda();
					}
					if (continuar_compra == 'N' || continuar_compra == 'n')
					{
						return usuarioNormal();
					}
					break;

				}
				else
				{
					cout << "Estoque insuficiente!\n";
					cout << "So temos " << estoque << " no estoque\n";
					cout << "Deseja comprar com essa nova quantidade?[S/N]\n";
					cin >> escolha_compra_qtd;
					if (escolha_compra_qtd == 'S' ||  escolha_compra_qtd == 's')
					{
						qtd_venda = estoque;
						fin >> cod_fornecedor;
						fin >> tipo_produto;
						fin >> preço_produto;
						fin.close();
						int qtd_venda_int = stoi(qtd_venda);
						valor_total_compra = preço_produto * qtd_venda_int;

						venda.codigo_produto = codigo_venda;
						fout << venda.codigo_produto << " ";
						venda.quantidade = qtd_venda_int;
						fout << venda.quantidade << " ";
						venda.valor_compra = valor_total_compra;
						fout << venda.valor_compra << " ";
						cout << endl << "Valor total da compra: " << venda.valor_compra << endl;
						cout << "Data da compra:\n\n\n";
						cout << "Dia da compra: ";
						cin >> venda.data_venda.dia; cout << endl;
						fout << venda.data_venda.dia << "/";
						cout << "Mes da compra: ";
						cin >> venda.data_venda.mes;
						fout << venda.data_venda.mes << "/";
						cout << "Ano da compra: ";
						cin >> venda.data_venda.ano;
						fout << venda.data_venda.ano << "\n";
						fout.close();
						cout << "Deseja realizar outra compra?[S/N]\n";
						cout << ">> "; cin >> continuar_compra;
						if (continuar_compra == 'S' || continuar_compra == 's')
						{
							return funcaoVenda();
						}
						if (continuar_compra == 'N' || continuar_compra == 'n')
						{
							return usuarioNormal();
						}
						break;

					}
					if (escolha_compra_qtd == 'N' ||  escolha_compra_qtd == 'n')
					{
						return funcaoVenda();
					}

				}
				break;
			}
			fin >> codigo_venda_arquivo;
		}
		if (produto_encontrado == false)
		{
			cout << "Produto não encontrado\n";
			return funcaoVenda();
		}
}

produto* cadastrar_produtos(produto* pcadastro, int tam_pcadastro)
{

	for (int i = 0; i < tam_pcadastro; i++)
	{
		cin.ignore();
		//Solicitando informações do(s) produto(s)
		system("cls");
		cout << "Cadastro do " << i + 1 << "º produto\n\n";
		cout << "Digite o nome do produto: ";
		getline(cin, pcadastro[i].nome);
		cout << "Digite o código do produto: ";
		cin >> pcadastro[i].codigo;
		cout << "Digite a quantidade em estoque: ";
		cin >> pcadastro[i].qtd_estoque;
		cout << "Digite o código do fornecedor: ";
		cin >> pcadastro[i].cod_fornecedor;
		cout << "Digite o valor do produto: ";
		cin >> pcadastro[i].valor_produto;
		system("cls");
		cout << "Digite em que tipo o produto se enquadra\n\n";   // utilizar enum
		cout << "[1] para produtos de limpeza/higiene pessoal\n";
		cout << "[2] para produtos alimentícios básicos\n";
		cout << "[3] para frutas\n";
		cout << "[4] para doces\n";
		cout << "[5] para produtos da padaria\n";
		cout << "[6] para outros\n";
		cout << ">";
		cin >> pcadastro[i].tipo_produto;
		system("cls");
	}
	return(pcadastro);
}
produto* deletar_produto(produto* pcadastro, string produto_del, int n)
{
	bool produto_encontrado = false;
	for (int i = 0; i < n; i++)
	{
		if (produto_del == pcadastro[i].nome)
		{
			produto_encontrado = true;
			cout << pcadastro[i].nome << endl;
			cout << "Excluindo produto...\n";
			pcadastro[i].nome = "NULL";
			pcadastro[i].codigo = 0;
			pcadastro[i].qtd_estoque = 0;
			pcadastro[i].cod_fornecedor = 0;
			pcadastro[i].tipo_produto = 0;
			pcadastro[i].valor_produto = 0;
			cout << pcadastro[i].nome << endl;
			cout << pcadastro[i].codigo << endl;
			cout << pcadastro[i].qtd_estoque << endl;
			cout << pcadastro[i].cod_fornecedor << endl;
			cout << pcadastro[i].tipo_produto << endl;
			cout << pcadastro[i].valor_produto << endl;
			cout << "Produto excluido com sucesso!\n";
			system("pause");
			system("cls");
		}
	}
	if (!produto_encontrado)
	{
		cout << "Produto não encontrado.\n";
		system("pause");
		system("cls");

	}
	return(pcadastro);
}
int deletar_produto_tam(produto* pcadastro, string produto_del, int tam_pcadastro)
{
	bool produto_encontrado = false;
	for (int i = 0; i < tam_pcadastro; i++)
	{
		if (produto_del == pcadastro[i].nome)
		{
			return(tam_pcadastro - 1);
		}
	}
	if (!produto_encontrado)
	{
		return tam_pcadastro;

	}
}
produto* adicionar_produto(produto* pcadastro, int num_produtos, int novos_produtos)
{
	int j{};
	int tam = num_produtos + novos_produtos;

	cout << "Iniciando cadastro de novos produtos...\n\n\n";

	for (j = num_produtos; j < tam; j++)
	{
		cin.ignore();
		//Solicitando informações do(s) produto(s)
		cout << "Cadastro do " << j + 1 << "º produto\n\n";
		cout << "Digite o nome do produto: ";
		getline(cin, pcadastro[j].nome); cout << endl;
		cout << "Digite o código do produto: ";
		cin >> pcadastro[j].codigo;
		cout << "Digite a quantidade em estoque: ";
		cin >> pcadastro[j].qtd_estoque;
		cout << "Digite o código do fornecedor: ";
		cin >> pcadastro[j].cod_fornecedor;
		cout << "Digite o valor do produto: ";
		cin >> pcadastro[j].valor_produto;
		system("cls");
		cout << "Digite em que tipo o produto se enquadra\n\n";
		cout << "[1] para produtos de limpeza/higiene pessoal\n";
		cout << "[2] para produtos alimentícios básicos\n";
		cout << "[3] para frutas\n";
		cout << "[4] para doces\n";
		cout << "[5] para produtos da padaria\n";
		cout << "[6] para outros\n";
		cout << ">";
		cin >> pcadastro[j].tipo_produto;
	}
	return(pcadastro);
}

void cadastrar_produtos_arq(produto* pcadastro, int tam_pcadastro)
{
	ofstream fout;
	fout.open("produtos.txt", ios_base::out | ios_base::app);
	for (int i = 0; i < tam_pcadastro; i++)
	{

		if (pcadastro->codigo != 0)
		{
			fout << pcadastro[i].nome << " ";
			fout << pcadastro[i].codigo << " ";
			fout << pcadastro[i].qtd_estoque << " ";
			fout << pcadastro[i].cod_fornecedor << " ";
			fout << pcadastro[i].tipo_produto << " ";
			fout << pcadastro[i].valor_produto << " " << endl;
		}
	}

}

produto* organizador_pcadastro(produto* pcadastro, int n)
{
	produto* pcadastro_copia = new produto[n];
	for (int i = 0; i < n; i++)
	{
		pcadastro_copia[i].nome = pcadastro[i].nome;
		pcadastro_copia[i].codigo = pcadastro[i].codigo;
		pcadastro_copia[i].qtd_estoque = pcadastro[i].qtd_estoque;
		pcadastro_copia[i].cod_fornecedor = pcadastro[i].cod_fornecedor;
		pcadastro_copia[i].tipo_produto = pcadastro[i].tipo_produto;
		pcadastro_copia[i].valor_produto = pcadastro[i].valor_produto;
	}
	for (int i = 0; i < n - 1; i++)
	{
		for (int i = 0; i < n - 1; i++)
		{
			if (pcadastro[i].codigo == 0)
			{
				pcadastro[i].nome = pcadastro_copia[i + 1].nome;
				pcadastro[i].codigo = pcadastro_copia[i + 1].codigo;
				pcadastro[i].qtd_estoque = pcadastro_copia[i + 1].qtd_estoque;
				pcadastro[i].cod_fornecedor = pcadastro_copia[i + 1].cod_fornecedor;
				pcadastro[i].tipo_produto = pcadastro_copia[i + 1].tipo_produto;
				pcadastro[i].valor_produto = pcadastro_copia[i + 1].valor_produto;
			}
		}
	}
	delete[] pcadastro_copia;
	return(pcadastro);
}

void exibir_produtos_arq()
{
	system("cls");
	cout << "Produtos cadastrados:\n\n\n\n";
	ifstream fin;
	fin.open("produtos.txt");
	if (!fin.is_open())
	{
		cout << "Não foi possível abrir o arwuivo\n";
		system("pause");
		exit(EXIT_FAILURE);
	}
	string nome_produto_arq;
	int cod_produto_arq;
	long quant_estoque_arq;
	long cod_fornecedor_arq;
	short tipo_produto_arq;
	double preço_produto_arq;
	int num_produto_arq = 1;
	fin >> nome_produto_arq;
	while (fin.good())
	{
		cout << num_produto_arq << " º PRODUTO:\n\n";
		cout << "Nome do produto: " << nome_produto_arq << endl;
		fin >> cod_produto_arq;
		cout << "Código do produto: " << cod_produto_arq << endl;
		fin >> quant_estoque_arq;
		cout << "Quantiidade em estoque : " << quant_estoque_arq << endl;
		fin >> cod_fornecedor_arq;
		cout << "Código do fornecedor: " << cod_fornecedor_arq << endl;
		fin >> tipo_produto_arq;
		cout << "Tipo do produto : " << tipo_produto_arq << endl;
		fin >> preço_produto_arq;
		cout << "Preço: " << preço_produto_arq << endl;
		fin >> nome_produto_arq;
		num_produto_arq++;
		cout << "\n\n\n";
	}
}
int main() {

	int loginEscolha;
	system("cls");
	cout << "Bem vindo ao Almoxarifado!\n\n\n";
	cout << "[1] Entrar como usuario\n\n[2] Entrar como Admin\n\n[3] Sair\n\n>>";
	cin >> loginEscolha;
	switch (loginEscolha) {
	case 1:
		usuarioNormal();
		break;
	case 2:
		funcaoADMIN();
	case 3:
		system("cls");
		cout << "Vendeu foi nada! ALEGRIA\n";
		system("pause");
		return 0;
	default:
		system("cls");
		cout << "Opcao invalida, tente novamente!\n\n";
		system("pause");
		return main();
	}
	return 0;
}

int funcaoADMIN()
{
	system("cls");
	string usuarioADMIN, senhaADMIN;
	ifstream fin;
	fin.open("admin.txt");
	string usuarioADMIN_arq, senhaADMIN_arq;
	bool admin_encontrado = false;
	cout << "      [LOGIN ADMIN]\n\n";
	cout << "Usuario: ";
	cin >> usuarioADMIN;
	cout << "Senha: ";
	cin >> senhaADMIN;
	fin >> usuarioADMIN_arq;
	while (fin.good())
	{
		fin >> senhaADMIN_arq;
		if (usuarioADMIN == usuarioADMIN_arq && senhaADMIN == senhaADMIN_arq) 
		{
			system("cls");
			cout << "Bem vindo ao sistema de [ADMIN]!\n\n\n";
			admin_encontrado = true;

		}
		fin >> usuarioADMIN_arq;
	}
	if(admin_encontrado == false) 
	{
		system("cls");
		cout << "Usuario ou senha incorretos, tente novamente!\n\n\n";
		system("pause");
		return main();
	}
	setlocale(LC_ALL, "Portuguese");
	int escolha_sistema, escolha;
	cout << "Digite 1 para entrar no sistema de cadastro de produtos" << endl;
	cout << "Digite 2 para entrar no sistema de vendas" << endl;
	cout << "Digite 3 para sair do sistema de ADMIN" << endl;
	cout << ">> "; cin >> escolha_sistema;

	if (escolha_sistema == 1)
	{
		exibir_produtos_arq();
		cout << "Deseja cadastrar novos produtos?[S/N]" << endl;
		char escolha_cadastrar_produtos;
		cout << ">> "; cin >> escolha_cadastrar_produtos;
		if (escolha_cadastrar_produtos == 'S' || escolha_cadastrar_produtos == 's')
		{
			system("cls");
			int num_produtos;
			int tam_pcadastro;
			string produto_del;
			cout << "Digite quantos produtos você deseja cadastrar: ";
			cin >> tam_pcadastro;
			int n = tam_pcadastro * 5;
			system("cls");
			produto* pcadastro = new produto[n]{};
			pcadastro = cadastrar_produtos(pcadastro, tam_pcadastro);
			cout << "\n\n";
			do
			{
				exibir_vetor(pcadastro, tam_pcadastro);
				cout << "[1] DELETAR estoque e cadastrar produtos novamente." << endl;
				cout << "[2] para deletar um produto." << endl;
				cout << "[3] para deletar um produto do arquivo." << endl;
				cout << "[4] para adicionar produtos." << endl;
				cout << "[5] para finalizar o programa de cadastro de produtos" << endl;
				cout << "Digite ao lado a sua escolha: ";
				cin >> escolha; cout << "\n\n\n";
				system("cls");
				cin.ignore();
				switch (escolha)
				{
				case 1:
					exibir_vetor(pcadastro, tam_pcadastro);
					cout << "Digite quantos produtos você deseja cadastrar: ";
					cin >> tam_pcadastro;
					system("cls");
					pcadastro = cadastrar_produtos(pcadastro, tam_pcadastro);
					cout << "\n\n";
					break;
				case 2:
					exibir_vetor(pcadastro, tam_pcadastro);
					cout << "Qual o nome do produto que você quer deletar(por favor digite tal como você escreveu quando o cadastrou): ";
					getline(cin, produto_del);
					tam_pcadastro = deletar_produto_tam(pcadastro, produto_del, tam_pcadastro);
					pcadastro = deletar_produto(pcadastro, produto_del, n); // o problema está aqui. Problema identificado: variavel n como parametro ;;; RESOLVIDO!!!
					pcadastro = organizador_pcadastro(pcadastro, n);
					cout << "\n\n";
					break;
				case 3:

				case 4:
					cout << "Por favor, digite a quantidade de produtos que você já tem cadastrado: ";
					cin >> num_produtos;
					int novos_produtos;
					cout << "Quantos produtos novos você quer adicionar?\n>>";
					cin >> novos_produtos;
					tam_pcadastro = num_produtos + novos_produtos;
					pcadastro = adicionar_produto(pcadastro, num_produtos, novos_produtos);
					cout << "\n\n";
					break;
				case 5:
					cout << "Fim do programa de cadastro de produtos.";
					cadastrar_produtos_arq(pcadastro, tam_pcadastro);
					delete[] pcadastro;
					cout << "\n\n";
					return main();

				default:
					cout << "Escolha Inválida.";
					cout << "\n\n";
				}

			} while (escolha != 5);
		}
		else if (escolha_cadastrar_produtos == 'N' || escolha_cadastrar_produtos == 'n')
		{
			system("cls");
			return (funcaoADMIN());
		}
	}
	if (escolha_sistema == 2)
	{
		system("cls");
		cout << "Bem vindo ao sistema!\n\n\n";
		cout << "[1] Operacao de vendas\n[2] Relatorio de vendas\n[3] Sair\n";
		cin >> escolha;
		switch (escolha) {
		case 1:
			system("cls");
			cout << "Acessando sistema de vendas...";
			system("pause");
			system("cls");
			funcaoVenda();
			break;
			//funcaoVenda();
		case 2:
			system("cls");
			cout << "Ainda nao implementado!\n";
			system("pause");
			return main();
			break;
		case 3:
			system("cls");
			return main();
			break;
		default:
			system("cls");
			cout << "Opcao invalida, tente novamente!\n";
			return main();
			break;
		}
		system("pause");
	}
	if (escolha_sistema == 3)
	{
		cout << "Saindo do sistema de ADMIN..." << endl;
		system("pause");
		return (main());
	}

}
int usuarioNormal() {
	system("cls");
	ifstream fin;
	fin.open("usuarionormal.txt");
	if (!fin.is_open())
	{
		cout << "Não foi possível abrir o arquivo\n";
		system("pause");
		exit(EXIT_FAILURE);
	}
	string usuario_arq, senha_arq;
	string usuario, senha;
	int tenteDNV, escolhausuario;
	bool usuario_encontrado = false;
	cout << "      [LOGIN USUARIO]\n\n";
	cout << "Usuario: ";
	cin >> usuario;
	cout << "Senha: ";
	cin >> senha;
	fin >> usuario_arq;
	while(fin.good())
	{ 
		fin >> senha_arq;
	if (usuario == usuario_arq && senha == senha_arq)
	{
		system("cls");
		cout << "Bem vindo ao sistema!\n\n\n";
		usuario_encontrado = true;
		cout << "[1] Operacao de vendas\n[2] Relatorio de vendas\n[3] Sair\n";
		cin >> escolhausuario;
		switch (escolhausuario) {
		case 1:
			system("cls");
			cout << "Acessando o sistema de vendas...\n";
			system("pause");
			system("cls");
			funcaoVenda();
			break;
			//funcaoVenda();
		case 2:
			system("cls");
			cout << "Ainda nao implementado!\n";
			system("pause");
			return main();
			break;
		case 3:
			system("cls");
			return main();
			break;
		default:
			system("cls");
			cout << "Opcao invalida, tente novamente!\n";
			return main();
			break;
		}
		system("pause");

	}
	fin >> usuario_arq;
	}
	if (usuario_encontrado == false)
	{
		system("cls");
			cout << "\nUsuario ou senha incorretos\n\nInsira qualquer numero para tentar novamente ou [1] para voltar ao inicio\n";
			cin >> tenteDNV;
			switch (tenteDNV) {
			case 1:
				system("cls");
					return main();
					break;
			default:
				return usuarioNormal();
			}
	}
}
