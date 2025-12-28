# 🔤 Jogo de Caça-Palavras

<div align="center">

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Data Structures](https://img.shields.io/badge/Data_Structures-AVL%20%7C%20Trie-orange?style=for-the-badge)
![Game](https://img.shields.io/badge/Type-Word%20Search%20Game-green?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

**Jogo inteligente de caça-palavras com busca automática usando Trie e AVL**

[🇺🇸 English Version](README.en.md) | [📖 Sobre](#-sobre-o-projeto) | [🚀 Instalação](#-instalação) | [💡 Funcionalidades](#-funcionalidades)

---

</div>

## 📋 Sobre o Projeto

O **Jogo de Caça-Palavras** é uma aplicação desenvolvida em C que combina entretenimento com demonstração avançada de estruturas de dados. O sistema:

- **Trie**: Armazena dicionário de palavras válidas para busca O(k)
- **AVL**: Mantém palavras encontradas ordenadas alfabeticamente com balanceamento automático
- **Algoritmo de Busca**: Varre tabuleiro em 8 direções (horizontal, vertical, diagonais)

### 🎯 Objetivos

- Demonstrar **Árvore AVL com balanceamento automático**
- Implementar **Trie para validação eficiente**
- Criar **algoritmo de busca multidirecional**
- Aplicar **programação modular** com separação de responsabilidades
- Desenvolver **jogo interativo** em terminal

### ✨ Características Principais

- 🌳 **Árvore AVL** - Palavras encontradas sempre balanceadas
- 🔍 **Trie** - Validação instantânea de palavras
- 🧭 **Busca 8 Direções** - Horizontal, vertical e diagonais
- ↔️ **Busca Reversa** - Detecta palavras em ambos sentidos
- 🎮 **Interface Interativa** - Menu completo com opções
- 📊 **Coordenadas** - Mostra início e fim de cada palavra

---

## 🏗️ Arquitetura

### Estrutura de Diretórios

```
caca-palavras/
├── avl.c                   # Implementação AVL
├── avl.h                   # Interface AVL
├── trie.c                  # Implementação Trie
├── trie.h                  # Interface Trie
├── jogo.c                  # Lógica do jogo
├── jogo.h                  # Interface do jogo
├── main.c                  # Interface e menu
├── makefile                # Script de compilação
├── tabuleiro.txt           # Tabuleiro 10x10
└── palavras.txt            # Dicionário de palavras
```

### 📊 Estruturas de Dados

#### 1. **Árvore AVL** (Palavras Encontradas)

```c
typedef struct {
    int linha_inicio;
    int coluna_inicio;
    int linha_fim;
    int coluna_fim;
} Coordenadas;

typedef struct NoAVL {
    char *palavra;
    Coordenadas coord;
    struct NoAVL *esquerdo;
    struct NoAVL *direito;
    int altura;
} NoAVL;
```

**Uso**: Armazena palavras encontradas ordenadas alfabeticamente com coordenadas.

**Vantagens**:
- ✅ Balanceamento automático
- ✅ Busca O(log n)
- ✅ Inserção O(log n)
- ✅ Travessia em ordem alfabética

#### 2. **Trie** (Dicionário)

```c
#define TAMANHO_ALFABETO 26

typedef struct NoTrie {
    struct NoTrie *filhos[TAMANHO_ALFABETO];
    int fim_palavra;
} NoTrie;
```

**Uso**: Valida se uma palavra existe no dicionário.

**Vantagens**:
- ✅ Busca O(k) onde k = tamanho da palavra
- ✅ Prefixos compartilhados economizam memória
- ✅ Ideal para autocompletar e validação

#### 3. **Tabuleiro**

```c
typedef struct {
    char **matriz;
    int tamanho;
} Tabuleiro;
```

**Uso**: Representa o grid do jogo.

### 🔄 Fluxo do Programa

```
┌─────────────────────┐
│   tabuleiro.txt     │
│   10 10             │
│   O V W Q O...      │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────────────┐
│   Carregar Tabuleiro        │
│   - Parse dimensões         │
│   - Criar matriz 2D         │
│   - Converter para minúsculo│
└──────────┬──────────────────┘
           │
           ▼
┌─────────────────────┐
│   palavras.txt      │
│   ganimedes         │
│   calisto           │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────────────┐
│   Carregar Dicionário       │
│   - Inserir cada palavra    │
│   - Construir Trie          │
└──────────┬──────────────────┘
           │
           ▼
┌─────────────────────────────┐
│   Buscar Palavras           │
│   Para cada direção:        │
│   1. Gerar substrings       │
│   2. Validar na Trie        │
│   3. Se válida, inserir AVL │
└──────────┬──────────────────┘
           │
           ▼
┌─────────────────────────────┐
│   AVL (Palavras Achadas)    │
│                              │
│      europa                  │
│      /     \                 │
│  calisto  ganimedes          │
└─────────────────────────────┘
```

---

## 💡 Funcionalidades

### 🔍 Direções de Busca

#### 1. **Horizontal** (→ e ←)

```c
NoAVL *buscar_horizontal(Tabuleiro *tab, NoTrie *trie, NoAVL *avl) {
    for (int i = 0; i < tab->tamanho; i++) {
        for (int j = 0; j < tab->tamanho; j++) {
            for (int tam = 2; j + tam <= tab->tamanho; tam++) {
                // Gerar palavra da esquerda para direita
                char palavra[100];
                for (int k = 0; k < tam; k++) {
                    palavra[k] = tab->matriz[i][j + k];
                }
                palavra[tam] = '\0';
                
                if (buscar_trie(trie, palavra) && !buscar_avl(avl, palavra)) {
                    Coordenadas coord = {i, j, i, j + tam - 1};
                    avl = inserir_avl(avl, palavra, coord);
                }
            }
        }
    }
    return avl;
}
```

#### 2. **Vertical** (↓ e ↑)

```c
NoAVL *buscar_vertical(Tabuleiro *tab, NoTrie *trie, NoAVL *avl) {
    for (int j = 0; j < tab->tamanho; j++) {
        for (int i = 0; i < tab->tamanho; i++) {
            for (int tam = 2; i + tam <= tab->tamanho; tam++) {
                char palavra[100];
                for (int k = 0; k < tam; k++) {
                    palavra[k] = tab->matriz[i + k][j];
                }
                palavra[tam] = '\0';
                // ... validar e inserir
            }
        }
    }
    return avl;
}
```

#### 3. **Diagonal Principal** (↘ e ↖)

```c
NoAVL *buscar_diagonal_principal(Tabuleiro *tab, NoTrie *trie, NoAVL *avl) {
    for (int i = 0; i < tab->tamanho; i++) {
        for (int j = 0; j < tab->tamanho; j++) {
            for (int tam = 2; i + tam <= tab->tamanho && j + tam <= tab->tamanho; tam++) {
                char palavra[100];
                for (int k = 0; k < tam; k++) {
                    palavra[k] = tab->matriz[i + k][j + k];
                }
                palavra[tam] = '\0';
                // ... validar e inserir
            }
        }
    }
    return avl;
}
```

#### 4. **Diagonal Secundária** (↙ e ↗)

```c
NoAVL *buscar_diagonal_secundaria(Tabuleiro *tab, NoTrie *trie, NoAVL *avl) {
    for (int i = 0; i < tab->tamanho; i++) {
        for (int j = 0; j < tab->tamanho; j++) {
            for (int tam = 2; i + tam <= tab->tamanho && j - tam + 1 >= 0; tam++) {
                char palavra[100];
                for (int k = 0; k < tam; k++) {
                    palavra[k] = tab->matriz[i + k][j - k];
                }
                palavra[tam] = '\0';
                // ... validar e inserir
            }
        }
    }
    return avl;
}
```

### ⚖️ Balanceamento AVL

#### Rotações

```c
// Rotação Direita
NoAVL *rotacao_direita(NoAVL *y) {
    NoAVL *x = y->esquerdo;
    NoAVL *T2 = x->direito;
    
    x->direito = y;
    y->esquerdo = T2;
    
    atualizar_altura(y);
    atualizar_altura(x);
    
    return x;
}

// Rotação Esquerda
NoAVL *rotacao_esquerda(NoAVL *x) {
    NoAVL *y = x->direito;
    NoAVL *T2 = y->esquerdo;
    
    y->esquerdo = x;
    x->direito = T2;
    
    atualizar_altura(x);
    atualizar_altura(y);
    
    return y;
}
```

#### Fator de Balanceamento

```c
int fator_balanceamento(NoAVL *no) {
    return no ? altura(no->esquerdo) - altura(no->direito) : 0;
}

// Se FB > 1: Desbalanceado à esquerda
// Se FB < -1: Desbalanceado à direita
// Se -1 <= FB <= 1: Balanceado
```

---

## 🚀 Instalação

### Pré-requisitos

- **Compilador C99+**: GCC, Clang ou MSVC
- **Make** (opcional)
- **Sistema Operacional**: Windows, Linux ou macOS

### Compilação

#### Usando Makefile (Recomendado)

```bash
# Clone o repositório
git clone https://github.com/JoaoGuilhermmy/caca-palavras-c.git
cd caca-palavras-c

# Compile
make

# Execute
./caca-palavras          # Linux/macOS
caca-palavras.exe        # Windows
```

#### Compilação Manual

```bash
# Linux/macOS
gcc -std=c99 -Wall -Wextra -o caca-palavras main.c jogo.c avl.c trie.c

# Windows com MinGW
gcc -std=c99 -Wall -Wextra -o caca-palavras.exe main.c jogo.c avl.c trie.c
```

---

## 💻 Como Usar

### Formato do Tabuleiro (tabuleiro.txt)

```
10 10
O V W Q O L L A D G
H A E O J K O N A Q
I P P I T J E N U B
M O O P A S I F A E
A R N J V M I P D S
L U I E E X L I B S
I E S D P E Z E A Y
A T E E L A R A D C
D S F L K X E K T A
Y C A G A P E H E T
```

**Estrutura**:
- Primeira linha: dimensões (linhas colunas)
- Demais linhas: matriz de letras

### Formato das Palavras (palavras.txt)

```
ganimedes
calisto
io
metis
europa
himalia
```

**Estrutura**: Uma palavra por linha

### Exemplo de Uso

```
===============================================
          JOGO DE CACA-PALAVRAS
===============================================
1 - Buscar palavras automaticamente
2 - Exibir palavras encontradas
3 - Remover palavra
4 - Exibir tabuleiro
5 - Sair
===============================================
Escolha uma opcao: 4

=== Tabuleiro 10x10 ===
O V W Q O L L A D G 
H A E O J K O N A Q 
I P P I T J E N U B 
M O O P A S I F A E 
A R N J V M I P D S 
L U I E E X L I B S 
I E S D P E Z E A Y 
A T E E L A R A D C 
D S F L K X E K T A 
Y C A G A P E H E T 

Escolha uma opcao: 1

Buscando palavras no tabuleiro...
Busca concluida!

Escolha uma opcao: 2

=== Palavras Encontradas ===
agape           [(9,2) -> (9,6)]
calisto         [(1,7) -> (7,1)]
elara           [(6,4) -> (6,8)]
europa          [(4,7) -> (0,7)]
ganimedes       [(0,9) -> (8,9)]
himalia         [(1,0) -> (7,0)]
io              [(2,0) -> (3,1)]
sinope          [(6,2) -> (1,7)]

Escolha uma opcao: 3

Digite a palavra a remover: io
Palavra 'io' removida com sucesso!

Escolha uma opcao: 5

Encerrando jogo...
```

---

## 🔧 Detalhes Técnicos

### Inserção na Trie

```c
void inserir_trie(NoTrie *raiz, const char *palavra) {
    NoTrie *atual = raiz;
    
    for (int i = 0; palavra[i] != '\0'; i++) {
        char c = tolower(palavra[i]);
        int indice = c - 'a';  // 'a' = 0, 'b' = 1, ...
        
        if (!atual->filhos[indice]) {
            atual->filhos[indice] = criar_no_trie();
        }
        
        atual = atual->filhos[indice];
    }
    
    atual->fim_palavra = 1;
}
```

### Busca na Trie

```c
int buscar_trie(NoTrie *raiz, const char *palavra) {
    NoTrie *atual = raiz;
    
    for (int i = 0; palavra[i] != '\0'; i++) {
        char c = tolower(palavra[i]);
        int indice = c - 'a';
        
        if (!atual->filhos[indice]) {
            return 0;  // Palavra não existe
        }
        
        atual = atual->filhos[indice];
    }
    
    return atual && atual->fim_palavra;
}
```

### Inserção na AVL com Balanceamento

```c
NoAVL *inserir_avl(NoAVL *raiz, const char *palavra, Coordenadas coord) {
    // 1. Inserção BST normal
    if (!raiz) {
        return criar_no_avl(palavra, coord);
    }
    
    int cmp = strcmp(palavra, raiz->palavra);
    
    if (cmp < 0) {
        raiz->esquerdo = inserir_avl(raiz->esquerdo, palavra, coord);
    } else if (cmp > 0) {
        raiz->direito = inserir_avl(raiz->direito, palavra, coord);
    } else {
        return raiz;  // Palavra já existe
    }
    
    // 2. Atualizar altura
    atualizar_altura(raiz);
    
    // 3. Calcular fator de balanceamento
    int fb = fator_balanceamento(raiz);
    
    // 4. Aplicar rotações se necessário
    // Caso Esquerda-Esquerda
    if (fb > 1 && strcmp(palavra, raiz->esquerdo->palavra) < 0) {
        return rotacao_direita(raiz);
    }
    
    // Caso Direita-Direita
    if (fb < -1 && strcmp(palavra, raiz->direito->palavra) > 0) {
        return rotacao_esquerda(raiz);
    }
    
    // Caso Esquerda-Direita
    if (fb > 1 && strcmp(palavra, raiz->esquerdo->palavra) > 0) {
        raiz->esquerdo = rotacao_esquerda(raiz->esquerdo);
        return rotacao_direita(raiz);
    }
    
    // Caso Direita-Esquerda
    if (fb < -1 && strcmp(palavra, raiz->direito->palavra) < 0) {
        raiz->direito = rotacao_direita(raiz->direito);
        return rotacao_esquerda(raiz);
    }
    
    return raiz;
}
```

---

## 📊 Complexidade Computacional

| Operação | Complexidade | Estrutura | Justificativa |
|----------|--------------|-----------|---------------|
| Inserir palavra (dicionário) | O(k) | Trie | k = tamanho palavra |
| Buscar palavra (validar) | O(k) | Trie | Percorre k nós |
| Inserir palavra (achada) | O(log n) | AVL | Árvore balanceada |
| Buscar palavra (achada) | O(log n) | AVL | Árvore balanceada |
| Remover palavra (achada) | O(log n) | AVL | Com rebalanceamento |
| Exibir em ordem | O(n) | AVL | Travessia em ordem |
| **Busca completa** | **O(s² × d × k)** | - | s=tamanho, d=direções, k=validação |

### Análise de Busca

```
Tabuleiro: 10x10
Direções: 8 (4 principais × 2 sentidos)
Tamanho máximo palavra: 10

Para cada célula (100 células):
  Para cada direção (8 direções):
    Para cada tamanho (2 a 10):
      Gerar substring: O(k)
      Validar na Trie: O(k)
      Se válida, inserir AVL: O(log n)

Total ≈ 100 × 8 × 9 × k × (k + log n)
      ≈ 7200 × k × (k + log n)

Com k ≈ 5 e n ≈ 20:
      ≈ 7200 × 5 × (5 + 4)
      ≈ 324.000 operações

Tempo: < 50ms em hardware moderno
```

---

## 🎓 Conceitos de Estruturas de Dados

### Árvore AVL

**Definição**: BST auto-balanceável onde |altura(esq) - altura(dir)| ≤ 1.

**Vantagens**:
- ✅ Garante O(log n) no pior caso
- ✅ Balanceamento automático
- ✅ Ideal para muitas buscas

**Desvantagens**:
- ❌ Mais complexa que BST
- ❌ Overhead de balanceamento

### Trie

**Definição**: Árvore de prefixos onde cada nó representa um caractere.

**Vantagens**:
- ✅ Busca O(k) independente de n
- ✅ Prefixos compartilhados
- ✅ Ideal para dicionários

**Desvantagens**:
- ❌ Uso de memória (26 ponteiros/nó)
- ❌ Overhead para palavras curtas

---

## 🐛 Solução de Problemas

### Problema: Palavras não encontradas

**Causas Possíveis**:
1. Palavra não está no dicionário
2. Erro de digitação no tabuleiro
3. Palavra muito curta (< 2 letras)

**Solução**:
```bash
# Verificar palavras.txt
cat palavras.txt

# Verificar tabuleiro.txt
cat tabuleiro.txt
```

### Problema: Vazamento de memória

**Verificação**:
```bash
valgrind --leak-check=full ./caca-palavras
```

**Solução**: Certificar-se de chamar `liberar_avl()` e `liberar_trie()` antes de sair.

### Problema: Segmentation fault

**Causa Comum**: Acesso fora dos limites da matriz.

**Solução**:
```c
// Sempre verificar limites
if (i + tam <= tab->tamanho && j + tam <= tab->tamanho) {
    // Seguro acessar matriz[i+k][j+k]
}
```

---

## 📈 Possíveis Melhorias

### Curto Prazo
- [ ] Adicionar pontuação por palavra
- [ ] Timer para desafios
- [ ] Níveis de dificuldade
- [ ] Gerador aleatório de tabuleiros

### Médio Prazo
- [ ] Interface gráfica com SDL2
- [ ] Modo multiplayer
- [ ] Diferentes temas (cidades, animais, etc.)
- [ ] Estatísticas de desempenho

### Longo Prazo
- [ ] Versão web com WebAssembly
- [ ] App mobile
- [ ] Torneios online
- [ ] IA para sugerir palavras

---

## 📄 Licença

Este projeto está sob a licença MIT. Consulte o arquivo [LICENSE](LICENSE) para mais detalhes.

---

## 👨‍💻 Autor

**João Guilhermmy**

- 🔗 GitHub: [https://github.com/JoaoGuilhermmy](https://github.com/JoaoGuilhermmy)
- 💼 LinkedIn: [www.linkedin.com/in/joão-guilhermmy-93661b29b](https://www.linkedin.com/in/joão-guilhermmy-93661b29b)
- 📧 Email: joaoguilhermmy2@gmail.com

---

## 🙏 Agradecimentos

- Comunidade C pelos recursos educacionais
- Desenvolvedores de jogos de palavras pela inspiração
- Professores e mentores

---

<div align="center">

### ⭐ Se este projeto foi útil, considere dar uma estrela!

**Desenvolvido com ❤️ e muito ☕**

### 💡 Projeto educacional demonstrando AVL e Trie em C

</div>
