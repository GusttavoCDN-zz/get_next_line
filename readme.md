<h1 align="center"><strong>GET NEXT LINE - @42SP</strong></h1>

<p align="center">Esse projeto é sobre desenvolver uma função que lê um fd linha por linha.</p>

<p align="center"><a href="https://www.42sp.org.br/" target="_blank"><img src="https://img.shields.io/static/v1?label=&message=SP&color=000&style=for-the-badge&logo=42"></a></p>
<p align="center"><img src="https://user-images.githubusercontent.com/81205527/149212588-45d60d10-2e78-46c5-bf0c-0dc247464ad5.png"> </p>
 <p align="center">Nota: <strong>125/100</strong> ✔️ </p>

<h2 align="center"><strong>Oque é a GNL?</strong></h2>

> Esse é o segundo projeto do curriculo da [42SP](https://www.42sp.org.br/). Consiste em criar uma função que seja capaz de ler de um fd uma linha por vez até o fim.

### **Oque é um file descriptor?**

De forma resumida um fd é uma forma do sistema mapear um arquivo para um ponteiro de memória. Um fd é representado como um inteiro dentro do programa, sendo 3 padrões que são frequentemente usados sendo:

- 0: stdin
- 1: stdout
- 2: stderr

Qualquer arquivo aberto pelo programa pode ser mapeado para um fd. No Linux a quantidade maxima de fds que podem ser abertos por uma programa é de 1024.

### **Manuseando um fd**

A GNL é uma função auxiliar, ela lê uma linha de um fd e retorna a linha lida a cada vez que é chamada. Para ser usada é necessario primeiro que um fd seja aberto e para isso existem funções auxiliares como a **open** e **fopen**.

Após o manuseio do arquivo ele precisa ser fechado com funções como a **close** e **fclose**.


### **Como a GNL funciona?**

A função GNL utiliza a função read para ler um arquivo a quantidade setada pelo **BUFFER_SIZE**, o retorno da read é a quantidade de caracteres lidos.

Com esse retorno em mãos a função GNL verifica se existe um **'\n'** nele (assim que é definido uma linha). Caso tenha sido lido mais bytes do que o necessario para compor uma linha a GNL trata esse retorno separando a linha lida e a parte restante em um buffer estatico para que seja utilizado na proxima chamada da função.

### **Como utilizar**

Baixe o repositorio e execute o seguinte comando no diretorio:

```
$ make
```

Sera gerado um arquivo chamado **get_next_line.a**. Agora você pode utilizar as funções em seus programas compilando da seguinte forma.

```
$ gcc -Wall -Wextra -Werror get_next_line.a main.c - nomeDoPrograma
```

Para limpar os arquivo objetos gerados ao compilar a biblioteca só utiliar o comando

```
$ make clean
```
