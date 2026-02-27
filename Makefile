#include <stdio.h>

// Função para imprimir um número em formato binário
void imprime_binario(int numero)
{
  // Encontra o bit mais significativo
  int bits_significativos = 32;
  for (int i = 31; i > 0; i--)
  {
    if ((numero >> i) & 1)
    {
      break;
    }
    bits_significativos--;
  }

  // Garante que pelo menos 4 bits sejam mostrados
  if (bits_significativos < 4)
    bits_significativos = 4;
  // Ajusta para o próximo múltiplo de 4
  else if (bits_significativos % 4 != 0)
    bits_significativos = ((bits_significativos / 4) + 1) * 4;

  // Imprime os bits em grupos de 4
  for (int i = bits_significativos - 1; i >= 0; i--)
  {
    printf("%d", (numero >> i) & 1);
    if (i % 4 == 0 && i != 0)
      printf(" ");
  }
  printf("\n");
}

// Funções de manipulação de bits (Letra C)
int ativa_bit(int numero, int posicao)
{
  return numero | (1 << posicao);
}

int desativa_bit(int numero, int posicao)
{
  return numero & ~(1 << posicao);
}

int alterna_bit(int numero, int posicao)
{
  return numero ^ (1 << posicao);
}

// Função para contar o número de bits 1 em um inteiro (Letra D)
int conta_bits_1(int numero)
{
  int contador = 0;
  for (int i = 0; i < 32; i++)
  {
    if (numero & (1 << i))
    {
      contador++;
    }
  }
  return contador;
}

// Funções Letra E: Compactação e descompactação de números

// Função para compactar dois números de 4 bits em um único byte
unsigned char compactar(unsigned char a, unsigned char b)
{
  if (a > 15 || b > 15)
    return 0; // Verifica se os números são válidos (máximo 4 bits)
  return (a << 4) | b;
}

// Função para descompactar o byte em dois números de 4 bits
void descompactar(unsigned char compactado, unsigned char *a, unsigned char *b)
{
  *a = (compactado >> 4) & 0x0F; // Recupera os 4 bits mais significativos
  *b = compactado & 0x0F;        // Recupera os 4 bits menos significativos
}

int main()
{
  int x, n, a, b;

  // Letra A: Comparação de dois números em binário
  printf("\n=== Letra A: Comparação de dois números em binário ===\n");
  printf("Digite o primeiro número (a): ");
  scanf("%d", &a);
  printf("Digite o segundo número (b): ");
  scanf("%d", &b);

  printf("\nNúmeros em decimal:\n");
  printf("a = %d\n", a);
  printf("b = %d\n", b);

  printf("\nNúmeros em binário:\n");
  printf("a = ");
  imprime_binario(a);
  printf("b = ");
  imprime_binario(b);

  printf("\nOperações bit a bit:\n");

  printf("a & b = %d\n", a & b);
  printf("Binário: ");
  imprime_binario(a & b);

  printf("a | b = %d\n", a | b);
  printf("Binário: ");
  imprime_binario(a | b);

  printf("a ^ b = %d\n", a ^ b);
  printf("Binário: ");
  imprime_binario(a ^ b);

  printf("~a = %d\n", ~a);
  printf("Binário: ");
  imprime_binario(~a);

  // Letra B: Deslocamentos de bits
  printf("\n=== Letra B: Deslocamentos de bits ===\n");
  printf("Digite um número inteiro positivo (x): ");
  scanf("%d", &x);
  printf("Digite o valor do deslocamento (n): ");
  scanf("%d", &n);

  printf("\nNúmero original:\n");
  printf("x = %d (decimal)\n", x);
  printf("x = ");
  imprime_binario(x);

  printf("\nDeslocamento para a esquerda (x << %d):\n", n);
  printf("Decimal: %d\n", x << n);
  printf("Binário: ");
  imprime_binario(x << n);

  printf("\nDeslocamento para a direita (x >> %d):\n", n);
  printf("Decimal: %d\n", x >> n);
  printf("Binário: ");
  imprime_binario(x >> n);

  // Letra C: Manipulação de bits
  printf("\n=== Letra C: Manipulação de bits ===\n");
  printf("Digite um número inteiro: ");
  scanf("%d", &x);
  printf("Digite a posição do bit (0-31): ");
  scanf("%d", &n);

  printf("\nNúmero original: ");
  imprime_binario(x);

  int ativado = ativa_bit(x, n);
  printf("Após ativar bit %d: ", n);
  imprime_binario(ativado);

  int desativado = desativa_bit(x, n);
  printf("Após desativar bit %d: ", n);
  imprime_binario(desativado);

  int alternado = alterna_bit(x, n);
  printf("Após alternar bit %d: ", n);
  imprime_binario(alternado);

  // Letra D: Contagem de bits 1
  printf("\n=== Letra D: Contagem de bits 1 ===\n");
  printf("Digite um número inteiro positivo: ");
  scanf("%d", &x);
  printf("Número em binário: ");
  imprime_binario(x);
  printf("Quantidade de bits 1: %d\n", conta_bits_1(x));

  // Letra E: Compactação de números
  printf("\n=== Letra E: Compactação de números de 4 bits ===\n");
  unsigned char num1, num2, compactado;

  printf("Digite o primeiro número (0-15): ");
  scanf("%hhu", &num1);
  printf("Digite o segundo número (0-15): ");
  scanf("%hhu", &num2);

  compactado = compactar(num1, num2);
  printf("\nNúmeros compactados em binário: ");
  imprime_binario(compactado);

  unsigned char valor1, valor2;
  descompactar(compactado, &valor1, &valor2);
  printf("Números descompactados: %d e %d\n", valor1, valor2);

  printf("\nPrograma finalizado.\n");
  return 0;
}