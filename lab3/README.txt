Laboratório de Classificação e Pesquisa de Dados.
Alunos: Sofia Popsin e Arthur Baumgardt
Cartões: 313563, 315913
Arquivos:
- 1.py: código referente ao problema 1 do laboratório(radixsort), gera arquivos texto
- lsb.py: módulo que contém radixsort usando LSB
- msb.py: módulo que contém radixsort usando MSB
- frankestein_clean_ordenado.txt: arquivo contendo o ebook ordenado lexicograficamente
- frankestein_clean_stats.txt: arquivo contendo a contagem de palavras do ebook
- war_and_peace_clean_ordenado.txt: arquivo contendo o ebook ordenado lexicograficamente
- war_and_peace_clean_stats.txt: arquivo contendo a contagem de palavras do ebook

Resposta à pergunta do LAB 3:
- Tentamos implementar o algoritmo usando MSB, pois nesse laboratório estamos lidando com strings de tamanhos diferentes, logo podemos desconsiderar strings pequenas
  quando ordenamos strings maiores, por exemplo: "ar" é maior, na ordem lexicográfica, que "árvore", "arbório" e "arsênico", logo podemos desconsiderar "ar" do ordenamento das
  palavras que contém prefixo "ar-", economizando tempo. Além de que, usando LSB precisamos ter um tamanho fixo de string ou começar a ordenar a partir de um tamanho máximo,
  percorrendo a lista de strings em todas as iterações para ordenar as de tamanho válido.
- Como nossa implementação de MSB demorou muito para completar, não conseguimos testá-la por completo com os arquivos dados, mas nos testes que fizemos parece funcionar. Logo, tivemos
  que buscar uma outra implementação para usar com os arquivos, e encontramos uma LSB que funciona bem.
