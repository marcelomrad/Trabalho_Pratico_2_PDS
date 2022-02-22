#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
  int codigo;
  char nome[100];
  int quantidade;
  float preco;
  char estado[20];
}Mercadoria;

int OrdemAlfabetica(Mercadoria *mercadorias, int tamanho_estoque)//função de colocar em ordem alfabetica
{   
    //variaveis auxiliares para colocar em ordem alfabetica
    char Nome[100], Estado[20];
    int Codigo, Quantidade;
    float Preco;

    //algoritimo para colocar em ordem alfabetica e ordenar a struct 
    for (int i = 0; i < tamanho_estoque; i++ ) 
    {
      for (int j = i+1; j < tamanho_estoque; j++ ) 
      {
        if (strcmp(mercadorias[i].nome, mercadorias[j].nome) > 0 )
        {
            strcpy (Nome, mercadorias[i]. nome );
            strcpy (Estado, mercadorias[i].estado);
            Codigo = mercadorias[i].codigo;
            Quantidade = mercadorias[i].quantidade;
            Preco = mercadorias[i].preco;

            strcpy (mercadorias[i].nome, mercadorias[j].nome );
            strcpy (mercadorias[i].estado, mercadorias[j].estado );
            mercadorias[i].codigo = mercadorias[j].codigo;
            mercadorias[i].quantidade = mercadorias[j].quantidade;
            mercadorias[i].preco = mercadorias[j].preco;
            
            strcpy (mercadorias[j].nome, Nome);
            strcpy (mercadorias[j].estado, Estado);
            mercadorias[j].codigo = Codigo;
            mercadorias[j].quantidade = Quantidade;
            mercadorias[j].preco = Preco;
        }    
      }
    }
    return(EXIT_SUCCESS);
}

int GerarRelatorio(Mercadoria *mercadorias, char *parametro, int tamanho_estoque) //executar função 1
{
    //abrir e criar um arquivo novo para ser escrito o estoque em ordem alfabetica
    FILE * estoque;
    estoque = fopen(parametro,"w");

    //chamando função de ordem alfabetica
    OrdemAlfabetica(mercadorias, tamanho_estoque);

    //imprimir o estoque em ordem alfabetica
    for (int x = 0; x < tamanho_estoque; x++)
    {
        fprintf(estoque,"%d\n%s%d\n%.2f\n%s",mercadorias[x].codigo,mercadorias[x].nome,
              mercadorias[x].quantidade,mercadorias[x].preco,mercadorias[x].estado);
    } 

    fclose(estoque);
    return(EXIT_SUCCESS);
}

int PesquisarPorCodigo(Mercadoria *mercadorias, int parametro, int tamanho_estoque) // funçao 2
{
    for (int j = 0; j < tamanho_estoque; j++)
    {
        //comparar codigo fornecido com o banco de dados
        if(parametro == mercadorias[j].codigo)
        {
            printf("%d\n%s%d\n%.2f\n%s",mercadorias[j].codigo,mercadorias[j].nome,
            mercadorias[j].quantidade,mercadorias[j].preco,mercadorias[j].estado);  
        }
    }   
    return(EXIT_SUCCESS);
}

int MenorQuantidadeEstoque(Mercadoria *mercadorias, int tamanho_estoque) //função 3
{
    int aux_menor;
    //comparação inicial entre o primeiro e o segundo valor
    if (mercadorias[0].quantidade > mercadorias[1].quantidade)
      aux_menor = mercadorias[1].quantidade;
    else
      aux_menor = mercadorias[0].quantidade;
    //achar o produto com menor quantidade no estoque
    for (int b = 2; b < tamanho_estoque; b++)
    { 
      if (aux_menor > mercadorias[b].quantidade)
        aux_menor = mercadorias[b].quantidade;
    }
    //imprimir dados do produto com menor quantidade no estoque 
    for (int c = 0; c < tamanho_estoque; c++)
    {
      if (aux_menor == mercadorias[c].quantidade)
        printf("%d\n%s%d\n%.2f\n%s",mercadorias[c].codigo,mercadorias[c].nome,
        mercadorias[c].quantidade,mercadorias[c].preco,mercadorias[c].estado);
    }

    return(EXIT_SUCCESS);
}

int ListarProdutosEstados(Mercadoria *mercadorias, char *parametro, int tamanho_estoque) //função 4
{
    //chamando função de ordem alfabetica
    OrdemAlfabetica(mercadorias, tamanho_estoque);

    //comparar o estado fornecido com o banco de dados e imprimir os produtos do referente estado
    for (int y = 0; y < tamanho_estoque; y++)
    {
        mercadorias[y].estado[strlen(mercadorias[y].estado)-1] = '\0';
        if (strcmp(parametro, mercadorias[y].estado) == 0)
        printf("%d\n%s%d\n%.2f\n%s\n",mercadorias[y].codigo,mercadorias[y].nome,
        mercadorias[y].quantidade,mercadorias[y].preco,mercadorias[y].estado);
    }

    return(EXIT_SUCCESS);
}

int MenorQuantidadeEstoqueEstado(Mercadoria *mercadorias, char *parametro, int tamanho_estoque) //função 5
{
    int aux_quantidade = 99999;
    for (int r = 0; r < tamanho_estoque; r++)
    {
        /* comparar o estado fornecido com o banco de dados e achar o produto 
        com menor quantidade do estado fornecido */
        mercadorias[r].estado[strlen(mercadorias[r].estado)-1] = '\0';
        if (strcmp(parametro, mercadorias[r].estado) == 0)
        {
            if (mercadorias[r].quantidade < aux_quantidade)
            aux_quantidade = mercadorias[r].quantidade; 
         }
    }
        //imprirmir o produto com menor quantidade do estado fornecido 
    for (int p = 0; p < tamanho_estoque; p++)
    {
        if (mercadorias[p].quantidade == aux_quantidade)
            printf("%d\n%s%d\n%.2f\n%s",mercadorias[p].codigo,mercadorias[p].nome,
            mercadorias[p].quantidade,mercadorias[p].preco,mercadorias[p].estado);
    }

    return(EXIT_SUCCESS);
}

int SomarQuantidade(Mercadoria *mercadorias, int tamanho_estoque) // função 6
{
    int soma_quantidade = 0;
    //somar a quantidade de produtos do estoque e imprimir a soma
    for (int l = 0; l < tamanho_estoque; l++)
    {
        soma_quantidade += mercadorias[l].quantidade;
    }
    printf("%d\n", soma_quantidade);

    return(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{   
    //evitando possiveis erros nos parametros informados
    if (argc < 2)
    {
        printf("Erro. Favor informar o nome do arquivo");
        return EXIT_FAILURE;
    }
    if (argc > 4)
    {
        printf("Quantidade de argumentos invalidos");
        return EXIT_FAILURE;
    }
    //abrir o arquivo
    FILE * arquivo;
    arquivo = fopen(argv[1], "r");

    //evitando possiveis erros de abertura de arquivo
    if (arquivo == NULL)
    {
        printf("Arquivo não encontrado");
        return 0;
    }
    
    //ler quantidade de produtos
    char tamanho_aux[100];
    int  tamanho_estoque;
    fgets(tamanho_aux, 100, arquivo);
    sscanf(tamanho_aux, "%d", &tamanho_estoque);
    
    //ler lista completa 
    Mercadoria mercadorias[5000];
    char temporaria[1000];

    for (int i = 0; i < tamanho_estoque; i++)
    {
        fgets(temporaria, 100, arquivo);
        mercadorias[i].codigo = atoi(temporaria);
    
        fgets(mercadorias[i].nome, 100, arquivo);

        fgets(temporaria, 100, arquivo);
        mercadorias[i].quantidade = atoi(temporaria);

        fgets(temporaria, 100, arquivo);
        mercadorias[i].preco = atof(temporaria);

        fgets(mercadorias[i].estado, 5, arquivo);
    }

    //Executar função 1
    if (atoi(argv[2]) == 1)
    {
        GerarRelatorio(mercadorias, argv[3], tamanho_estoque);
    }

    //Executar funçao 2
    if (atoi(argv[2]) == 2)
    {
        PesquisarPorCodigo(mercadorias, atoi(argv[3]), tamanho_estoque);
    }

    //Executar função 3
    if (atoi(argv[2]) == 3)
    {
        MenorQuantidadeEstoque(mercadorias, tamanho_estoque); 
    }

    //Executar função 4
    if (atoi(argv[2]) == 4)
    {
        ListarProdutosEstados(mercadorias, argv[3], tamanho_estoque);
    }

    //Executar função 5
    if (atoi(argv[2]) == 5)
    {
        MenorQuantidadeEstoqueEstado(mercadorias, argv[3], tamanho_estoque);
    }

    //Executar função 6
    if (atoi(argv[2]) == 6)
    {
        SomarQuantidade(mercadorias, tamanho_estoque); 
    }

    fclose(arquivo);
    return (EXIT_SUCCESS);
}