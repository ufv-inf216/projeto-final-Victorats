# BomberDepartment
Trabalho Final na disciplina INF 216  Projeto e Implementação de Jogos Digitais 2023/2.
Jogo parecido com Bomberman com tematizado com o Departamento de Informatica da Universidade Federal de Viçosa, implementado usando a biblioteca Simple DirectMedia Layer (SDL). 

Objetivo:
BomberDepartment é um Bomberman tematizado, o objetivo do jogo é o jogador destruir as caixas e pegar os buffs para conseguir eliminar o inimigo

Na versão atual do jogo, ainda não alteramos as sprites pois as que estão atualmente foram utilizadas no inicio do projeto. 

Mecanicas Basicas:
O jogo já pode ser jogado de dois jogadores. O jogador 1 se movimenta com as teclas (W,S,A,D) e planta a bomba no G o jogador 2 se movimenta nas setas e planta a bomba no L. A mecanica da explosão está quase totalmente funcional, só está com um pequeno problema de colisão na hora de ser construída, o que faz com que o resultado não seja igual o esperado. A mecânica da explosão matar os jogadores e querbar as caixas também já está funcional. Das mecânicas básicas o que está faltando mesmo é as caixas explodirem. A colisão entre os jogadores já está implementada, a colisão dos jogadores com a bomba também.

Condições de vitória e de derrota:

Um jogador ganha se conseguir fazer com que a explosão colida com o outro jogador.
Um jogador perde se entrar em contato com o rastro da explosão.

Considerações importantes: 
A explosão ainda está sendo desenvolvida apesar de estar quase funcional.
As caixas(quase sempre) explodem por causa dos bugs na explosão e os powers-ups ainda não foram implementados.
A colisão ainda será ajustada.
