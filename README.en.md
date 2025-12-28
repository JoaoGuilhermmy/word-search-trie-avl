# 🔤 Word Search Game

<div align="center">

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Data Structures](https://img.shields.io/badge/Data_Structures-AVL%20%7C%20Trie-orange?style=for-the-badge)
![Game](https://img.shields.io/badge/Type-Word%20Search%20Game-green?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

**Intelligent word search game with automatic search using Trie and AVL**

[🇧🇷 Versão em Português](README.md) | [📖 About](#-about-the-project) | [🚀 Installation](#-installation) | [💡 Features](#-features)

---

</div>

## 📋 About the Project

The **Word Search Game** is an application developed in C that combines entertainment with advanced data structure demonstration. The system:

- **Trie**: Stores dictionary of valid words for O(k) search
- **AVL**: Keeps found words alphabetically sorted with automatic balancing
- **Search Algorithm**: Scans board in 8 directions (horizontal, vertical, diagonals)

### 🎯 Objectives

- Demonstrate **AVL Tree with automatic balancing**
- Implement **Trie for efficient validation**
- Create **multidirectional search algorithm**
- Apply **modular programming** with separation of responsibilities
- Develop **interactive terminal game**

### ✨ Key Features

- 🌳 **AVL Tree** - Found words always balanced
- 🔍 **Trie** - Instant word validation
- 🧭 **8-Direction Search** - Horizontal, vertical and diagonals
- ↔️ **Reverse Search** - Detects words in both directions
- 🎮 **Interactive Interface** - Complete menu with options
- 📊 **Coordinates** - Shows start and end of each word

---

## 🏗️ Architecture

### Directory Structure

```
word-search/
├── avl.c                   # AVL implementation
├── avl.h                   # AVL interface
├── trie.c                  # Trie implementation
├── trie.h                  # Trie interface
├── jogo.c                  # Game logic
├── jogo.h                  # Game interface
├── main.c                  # Interface and menu
├── makefile                # Build script
├── tabuleiro.txt           # 10x10 board
└── palavras.txt            # Word dictionary
```

### 📊 Data Structures

#### 1. **AVL Tree** (Found Words)

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

**Usage**: Stores found words alphabetically sorted with coordinates.

**Advantages**:
- ✅ Automatic balancing
- ✅ O(log n) search
- ✅ O(log n) insertion
- ✅ In-order alphabetical traversal

#### 2. **Trie** (Dictionary)

```c
#define TAMANHO_ALFABETO 26

typedef struct NoTrie {
    struct NoTrie *filhos[TAMANHO_ALFABETO];
    int fim_palavra;
} NoTrie;
```

**Usage**: Validates if a word exists in the dictionary.

**Advantages**:
- ✅ O(k) search where k = word length
- ✅ Shared prefixes save memory
- ✅ Ideal for autocomplete and validation

#### 3. **Board**

```c
typedef struct {
    char **matriz;
    int tamanho;
} Tabuleiro;
```

**Usage**: Represents the game grid.

### 🔄 Program Flow

```
┌─────────────────────┐
│   tabuleiro.txt     │
│   10 10             │
│   O V W Q O...      │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────────────┐
│   Load Board                │
│   - Parse dimensions        │
│   - Create 2D matrix        │
│   - Convert to lowercase    │
└──────────┬──────────────────┘
           │
           ▼
┌─────────────────────┐
│   palavras.txt      │
│   jupiter           │
│   saturn            │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────────────┐
│   Load Dictionary           │
│   - Insert each word        │
│   - Build Trie              │
└──────────┬──────────────────┘
           │
           ▼
┌─────────────────────────────┐
│   Search Words              │
│   For each direction:       │
│   1. Generate substrings    │
│   2. Validate in Trie       │
│   3. If valid, insert AVL   │
└──────────┬──────────────────┘
           │
           ▼
┌─────────────────────────────┐
│   AVL (Found Words)         │
│                              │
│      europa                  │
│      /     \                 │
│  calisto  ganimedes          │
└─────────────────────────────┘
```

---

## 💡 Features

### 🔍 Search Directions

#### 1. **Horizontal** (→ and ←)

```c
NoAVL *buscar_horizontal(Tabuleiro *tab, NoTrie *trie, NoAVL *avl) {
    for (int i = 0; i < tab->tamanho; i++) {
        for (int j = 0; j < tab->tamanho; j++) {
            for (int tam = 2; j + tam <= tab->tamanho; tam++) {
                // Generate word from left to right
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

#### 2. **Vertical** (↓ and ↑)

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
                // ... validate and insert
            }
        }
    }
    return avl;
}
```

#### 3. **Main Diagonal** (↘ and ↖)

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
                // ... validate and insert
            }
        }
    }
    return avl;
}
```

#### 4. **Secondary Diagonal** (↙ and ↗)

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
                // ... validate and insert
            }
        }
    }
    return avl;
}
```

### ⚖️ AVL Balancing

#### Rotations

```c
// Right Rotation
NoAVL *rotacao_direita(NoAVL *y) {
    NoAVL *x = y->esquerdo;
    NoAVL *T2 = x->direito;
    
    x->direito = y;
    y->esquerdo = T2;
    
    atualizar_altura(y);
    atualizar_altura(x);
    
    return x;
}

// Left Rotation
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

#### Balance Factor

```c
int fator_balanceamento(NoAVL *no) {
    return no ? altura(no->esquerdo) - altura(no->direito) : 0;
}

// If BF > 1: Unbalanced to the left
// If BF < -1: Unbalanced to the right
// If -1 ≤ BF ≤ 1: Balanced
```

---

## 🚀 Installation

### Prerequisites

- **C99+ Compiler**: GCC, Clang or MSVC
- **Make** (optional)
- **Operating System**: Windows, Linux or macOS

### Compilation

#### Using Makefile (Recommended)

```bash
# Clone the repository
git clone https://github.com/JoaoGuilhermmy/word-search-c.git
cd word-search-c

# Compile
make

# Run
./caca-palavras          # Linux/macOS
caca-palavras.exe        # Windows
```

#### Manual Compilation

```bash
# Linux/macOS
gcc -std=c99 -Wall -Wextra -o caca-palavras main.c jogo.c avl.c trie.c

# Windows with MinGW
gcc -std=c99 -Wall -Wextra -o caca-palavras.exe main.c jogo.c avl.c trie.c
```

---

## 💻 How to Use

### Board Format (tabuleiro.txt)

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

**Structure**:
- First line: dimensions (rows columns)
- Other lines: letter matrix

### Words Format (palavras.txt)

```
ganimedes
calisto
io
metis
europa
himalia
```

**Structure**: One word per line

### Usage Example

```
===============================================
          WORD SEARCH GAME
===============================================
1 - Search words automatically
2 - Display found words
3 - Remove word
4 - Display board
5 - Exit
===============================================
Choose an option: 4

=== Board 10x10 ===
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

Choose an option: 1

Searching words on board...
Search completed!

Choose an option: 2

=== Found Words ===
agape           [(9,2) -> (9,6)]
calisto         [(1,7) -> (7,1)]
elara           [(6,4) -> (6,8)]
europa          [(4,7) -> (0,7)]
ganimedes       [(0,9) -> (8,9)]
himalia         [(1,0) -> (7,0)]
io              [(2,0) -> (3,1)]
sinope          [(6,2) -> (1,7)]

Choose an option: 3

Enter word to remove: io
Word 'io' removed successfully!

Choose an option: 5

Ending game...
```

---

## 🔧 Technical Details

### Trie Insertion

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

### Trie Search

```c
int buscar_trie(NoTrie *raiz, const char *palavra) {
    NoTrie *atual = raiz;
    
    for (int i = 0; palavra[i] != '\0'; i++) {
        char c = tolower(palavra[i]);
        int indice = c - 'a';
        
        if (!atual->filhos[indice]) {
            return 0;  // Word doesn't exist
        }
        
        atual = atual->filhos[indice];
    }
    
    return atual && atual->fim_palavra;
}
```

### AVL Insertion with Balancing

```c
NoAVL *inserir_avl(NoAVL *raiz, const char *palavra, Coordenadas coord) {
    // 1. Normal BST insertion
    if (!raiz) {
        return criar_no_avl(palavra, coord);
    }
    
    int cmp = strcmp(palavra, raiz->palavra);
    
    if (cmp < 0) {
        raiz->esquerdo = inserir_avl(raiz->esquerdo, palavra, coord);
    } else if (cmp > 0) {
        raiz->direito = inserir_avl(raiz->direito, palavra, coord);
    } else {
        return raiz;  // Word already exists
    }
    
    // 2. Update height
    atualizar_altura(raiz);
    
    // 3. Calculate balance factor
    int fb = fator_balanceamento(raiz);
    
    // 4. Apply rotations if necessary
    // Left-Left Case
    if (fb > 1 && strcmp(palavra, raiz->esquerdo->palavra) < 0) {
        return rotacao_direita(raiz);
    }
    
    // Right-Right Case
    if (fb < -1 && strcmp(palavra, raiz->direito->palavra) > 0) {
        return rotacao_esquerda(raiz);
    }
    
    // Left-Right Case
    if (fb > 1 && strcmp(palavra, raiz->esquerdo->palavra) > 0) {
        raiz->esquerdo = rotacao_esquerda(raiz->esquerdo);
        return rotacao_direita(raiz);
    }
    
    // Right-Left Case
    if (fb < -1 && strcmp(palavra, raiz->direito->palavra) < 0) {
        raiz->direito = rotacao_direita(raiz->direito);
        return rotacao_esquerda(raiz);
    }
    
    return raiz;
}
```

---

## 📊 Computational Complexity

| Operation | Complexity | Structure | Justification |
|-----------|------------|-----------|---------------|
| Insert word (dictionary) | O(k) | Trie | k = word length |
| Search word (validate) | O(k) | Trie | Traverse k nodes |
| Insert word (found) | O(log n) | AVL | Balanced tree |
| Search word (found) | O(log n) | AVL | Balanced tree |
| Remove word (found) | O(log n) | AVL | With rebalancing |
| Display in order | O(n) | AVL | In-order traversal |
| **Complete search** | **O(s² × d × k)** | - | s=size, d=directions, k=validation |

### Search Analysis

```
Board: 10x10
Directions: 8 (4 main × 2 directions)
Maximum word length: 10

For each cell (100 cells):
  For each direction (8 directions):
    For each length (2 to 10):
      Generate substring: O(k)
      Validate in Trie: O(k)
      If valid, insert AVL: O(log n)

Total ≈ 100 × 8 × 9 × k × (k + log n)
      ≈ 7200 × k × (k + log n)

With k ≈ 5 and n ≈ 20:
      ≈ 7200 × 5 × (5 + 4)
      ≈ 324,000 operations

Time: < 50ms on modern hardware
```

---

## 🎓 Data Structures Concepts

### AVL Tree

**Definition**: Self-balancing BST where |height(left) - height(right)| ≤ 1.

**Advantages**:
- ✅ Guarantees O(log n) in worst case
- ✅ Automatic balancing
- ✅ Ideal for many searches

**Disadvantages**:
- ❌ More complex than BST
- ❌ Balancing overhead

### Trie

**Definition**: Prefix tree where each node represents a character.

**Advantages**:
- ✅ O(k) search independent of n
- ✅ Shared prefixes
- ✅ Ideal for dictionaries

**Disadvantages**:
- ❌ Memory usage (26 pointers/node)
- ❌ Overhead for short words

---

## 🐛 Troubleshooting

### Problem: Words not found

**Possible Causes**:
1. Word not in dictionary
2. Typo in board
3. Word too short (< 2 letters)

**Solution**:
```bash
# Check palavras.txt
cat palavras.txt

# Check tabuleiro.txt
cat tabuleiro.txt
```

### Problem: Memory leak

**Check**:
```bash
valgrind --leak-check=full ./caca-palavras
```

**Solution**: Make sure to call `liberar_avl()` and `liberar_trie()` before exiting.

### Problem: Segmentation fault

**Common Cause**: Matrix bounds access.

**Solution**:
```c
// Always check bounds
if (i + tam <= tab->tamanho && j + tam <= tab->tamanho) {
    // Safe to access matriz[i+k][j+k]
}
```

---

## 📈 Possible Improvements

### Short Term
- [ ] Add scoring per word
- [ ] Timer for challenges
- [ ] Difficulty levels
- [ ] Random board generator

### Medium Term
- [ ] GUI with SDL2
- [ ] Multiplayer mode
- [ ] Different themes (cities, animals, etc.)
- [ ] Performance statistics

### Long Term
- [ ] Web version with WebAssembly
- [ ] Mobile app
- [ ] Online tournaments
- [ ] AI for word suggestions

---

## 📄 License

This project is under the MIT license. See the [LICENSE](LICENSE) file for more details.

---

## 👨‍💻 Author

**João Guilhermmy**

- 🔗 GitHub: [https://github.com/JoaoGuilhermmy](https://github.com/JoaoGuilhermmy)
- 💼 LinkedIn: [www.linkedin.com/in/joão-guilhermmy-93661b29b](https://www.linkedin.com/in/joão-guilhermmy-93661b29b)
- 📧 Email: joaoguilhermmy2@gmail.com

---

## 🙏 Acknowledgments

- C community for educational resources
- Word game developers for inspiration
- Professors and mentors

---

<div align="center">

### ⭐ If this project was useful, consider giving it a star!

**Developed with ❤️ and lots of ☕**

### 💡 Educational project demonstrating AVL and Trie in C

</div>
