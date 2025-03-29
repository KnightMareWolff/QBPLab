# QBPLab
Um tópico bastante ativo atualmente na comunidade acadêmica é a realização
de Buscas de Músicas por Similaridade.
Em cada tipo de busca há diferentes tipos de entrada destes dados, bem como o
processamento de similaridade necessário também.
Algoritmos e métodos de busca por similaridade vem sendo pesquisados e
desenvolvidos devido a grande quantidade de características envolvida em cada tipo
de Query.
Portanto a grande maioria de pesquisas envolvendo buscas de musicas por
similaridade vem sendo nomeada com o prefixo “Query-by” onde o complemento do
nome identifica geralmente a entrada de dados sendo realizada na Query.
# Query By Playing
O objetivo principal de uma busca QBP é a busca por similaridade a partir de
um trecho musical que está sendo tocado pelo usuário (Playing).
Apesar de parecer um conceito muito parecido com os outros tipos de busca,
principalmente por QBE, na realidade tecnicamente a mesma difere significativamente
das outras desde a forma como as notas musicais são coletadas, até mesmo
como a quantidade, tamanho dos trechos de comparação e utilização do algoritmo de
similaridade são realizados.
Devido ao fato destas buscas serem realizadas por músicos utilizando instrumentos
musicais, para que as mesmas façam sentido ao usuário, a adoção de similaridade
levando-se em conta regras melódicas ganham relevância durante a performance
musical.
Portanto, a realização das buscas e sua consecutiva avaliação, bem como a
escolha de métodos de similaridade, devem-se levar em conta que tanto a comparação
de similaridade, como o espaço de busca utilizado, devem possibilitar o acesso a
dados e características relacionadas a notas musicais, seu encadeamento, escalas
tonais e diversas outras informações que não são utilizadas por outros tipos de
consultas Query-By.
O Grande desafio para um pesquisador de buscas Query By Playing é conseguir
dar ao usuário a sensação de que o computador está realmente entendendo a musica
que esta sendo executada, já que em sua maioria, os usuários serão músicos treinados
nesta linguagem musical.
# A automatização do Protocolo Experimental
Durante a realização da minha pesquisa de mestrado, houve a necessidade de automatização 
do protocolo experimental.O código fonte desta ferramenta chamada de QBPLab (Query By 
Playing Laboratory) está neste repositório, separadas por uma versão Release(Já empácotada
para execução), e o codigo fonte para compilação).
Dentre as diversas funcionalidades desenvolvidas neste software as funcionalidades
principais para a execução do protocolo experimental são a execução automatizada
via scripts e os relatórios de processamento que calculam as métricas de
avaliação.
Todas as funcionalidades desenvolvidas no QBPLab, foram expostas para
automatização através de scripts Lua http://www.lua.org.
