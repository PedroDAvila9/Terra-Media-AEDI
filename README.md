# SUPER SENHORES DOS ANÉIS
![Imagem Interessante](https://preview.redd.it/lord-of-the-rings-mario-super-moria-v0-y9ievx9rei2c1.jpg?width=640&crop=smart&auto=webp&s=e8344e3b7638a9670c219c6ea1c8ccb915f496b2)

## 📜 **Descrição do Projeto**
Implementação de um sistema em C que simula a jornada de Frodo para destruir o Anel, utilizando estruturas de dados para gerenciar diferentes aspectos da aventura.

## 🏗️ Estruturas de Dados Utilizadas
**1. Árvore Binária**

Finalidade: 
- Representar o mapa hierárquico da Terra Média

Justificativa:

- Organização natural dos locais (Vila dos Hobbits como raiz)

- Navegação eficiente (esquerda/direita para movimentação)

- Busca rápida de locais conectados

**2. Fila**

Finalidade: 
- Gerenciar o sistema de batalha por turnos

Justificativa:

- Ordem FIFO para enfrentar inimigos

- Simula a chegada de novos oponentes

- Implementação justa de turnos

**3. Pilha**

Finalidade: 
- Rastrear caminho percorrido

Justificativa:

- LIFO para voltar aos locais anteriores, apenas desempilhando o último item empilhado

- Histórico de navegação simples

- Mecânica de "desfazer movimento"

## 🎮 Funcionalidades Implementadas

- **Sistema de Jornada**: Mapa com 6 locais interconectados

- **Sistema de movimentação (esquerda/direita/voltar)**

- **Diferentes desafios em cada local (inimigos diferentes)**

- **Sistema de Batalha**: Inimigos com atributos variados

- **4 ações possíveis no combate** (atacar, defender, usar item, fugir)

- **Dano calculado baseado em atributos**

- **Sistema de Itens**

- **3 tipos de itens colecionáveis** com efeitos especiais (cura, aumento de força/resistência)

- **Inventário organizado como árvore binária**
  
## 🛠️ Como Compilar e Executar
**Pré-requisitos**: Compilador GCC (ou equivalente) e Make instalado.

1. Abra o terminal na pasta do projeto.
2. Para compilar todo o código, digite:
    ```bash
    make
    ```
3. Para executar o programa:
    ```bash
    make run
    ```
4. Para limpar os arquivos objeto (.o) e o executável:
    ```bash
    make clean
    ```
5. Caso deseje executar manualmente após o make, basta rodar ./terra_media diretamente no terminal.

## 💡 Lógica de Implementação

**Árvore para o mapa**: 
- Escolhida por representar naturalmente hierarquias


**Fila para batalhas**: 
- Garante justiça nos turnos de combate

**Pilha para caminho**: 
- Solução ideal para rastrear histórico

## 🎯 Desafios Resolvidos

Uso das estruturas de dados diferentes pros propósitos variados do jogo

Gerenciamento de estado do jogo

Integração das estruturas de dados

Uso de TADs para que tenhamos organização entre especificação e implementação

## **🎯 Objetivo do Jogo**

Guiar Frodo até Mordor para destruir o Anel, coletando itens e sobrevivendo às batalhas.

### Como Jogar

1. **Menu Principal**  
   - **[1]** Explorar local atual  
     - Possibilidade de encontrar itens e inimigos.  
   - **[2]** Mover para a esquerda (←)  
   - **[3]** Mover para a direita (→)  
   - **[4]** Voltar ao local anterior (usa a pilha de histórico)  
   - **[5]** Status de Frodo (exibe vida, força, resistência, inventário)  
   - **[6]** Inventário (listar e usar itens)  
   - **[0]** Sair do jogo  

2. **Combate**  
   - Iniciado ao explorar um local com inimigos.  
   - **Ações**: Atacar, Defender, Usar item ou Fugir.  

3. **Itens**  
   - Ao explorar, pode-se encontrar itens (cura, força, resistência).  
   - Armazenados em uma árvore binária de inventário, ordenados por nome.  

4. **Condição de Vitória**  
   - Estar em Mordor com o Anel, escolher destruir o Anel.  

5. **Condição de Derrota**  
   - Se Frodo chegar a 0 de vida em combate.

## 👥 Autores

Pedro Victor Valle Gonçalves

Pedro D'Ávila
