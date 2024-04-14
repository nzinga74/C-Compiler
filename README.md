Projeto de Compilador de C em C++
Este repositório contém o código-fonte de um compilador de C desenvolvido em C++. O projeto foi realizado como parte de um trabalho acadêmico na disciplina de Compiladores, ministrada pelo Dr. André Filemon na nossa instituição ISPTEC.

Fases do Compilador
Um compilador passa por várias fases durante o processo de tradução do código-fonte para o código objeto. As principais fases incluem:

Análise Léxica (Scanner): Esta fase envolve a leitura do código-fonte caractere por caractere para identificar tokens como palavras-chave, identificadores, números e operadores.

Análise Sintática (Parser): Nesta fase, os tokens identificados na etapa anterior são estruturados de acordo com as regras gramaticais da linguagem para formar uma árvore sintática.

Análise Semântica: Aqui, a árvore sintática é analisada para verificar se as construções da linguagem têm significado válido e consistente.

Geração de Código: Na última fase, o compilador gera o código objeto (por exemplo, em linguagem de máquina) com base na árvore sintática analisada.

Ferramentas Utilizadas
Durante o desenvolvimento deste compilador, utilizamos o JFLAP para a construção de autômatos finitos que serviram como guia na implementação do analisador léxico. Isso nos ajudou a entender e implementar eficientemente o reconhecimento dos tokens necessários para a fase de análise léxica.

Contexto Acadêmico
Este projeto foi uma excelente oportunidade para aplicar os conceitos teóricos aprendidos em sala de aula na prática. Agradecemos ao Dr. André Filemon por orientar e propor este desafio, que nos proporcionou uma compreensão mais profunda do funcionamento interno dos compiladores e das técnicas de análise de linguagens formais.
