# Biblioteca Darcy

Sistema de gerenciamento de biblioteca desenvolvido em linguagem C, utilizando manipulação de arquivos `.txt` para armazenamento de dados.

O projeto simula operações básicas de uma biblioteca, incluindo:

- Login de usuários
- Controle de perfis
- Cadastro de usuários
- Cadastro de exemplares
- Listagem de registros
- Empréstimo de livros
- Devolução com cálculo de multa

---

# Funcionalidades

## Sistema de Login

O sistema possui autenticação com dois níveis de acesso:

### Gerente

Possui acesso completo ao sistema.

#### Permissões:
- Cadastrar usuários
- Listar usuários
- Cadastrar exemplares
- Listar exemplares
- Realizar empréstimos
- Realizar devoluções

### Usuário

Possui acesso limitado.

#### Permissões:
- Listar exemplares
- Realizar empréstimos

---

# Contas Padrão

## Gerente

```txt
Login: admin01
Senha: 0000
```

## Usuário

```txt
Login: user01
Senha: 0000
```

---

# Estruturas Utilizadas

O sistema utiliza `structs` para representar os dados.

## Conta

```c
typedef struct {
    char login[32];
    char senha[32];
    Perfil perfil;
} Conta;
```

## Usuário

```c
typedef struct {
    int  id;
    char nome[100];
    char dataNasc[15];
} Usuario;
```

## Exemplar

```c
typedef struct {
    int  id;
    char nome[100];
    char autor[100];
    char dataPublicacao[15];
    int  quantidade;
} Exemplar;
```

---

# Armazenamento de Dados

Os dados são persistidos em arquivos texto.

| Arquivo | Função |
|---|---|
| `Usuarios.txt` | Armazena usuários cadastrados |
| `Exemplares.txt` | Armazena exemplares cadastrados |
| `temp.txt` | Arquivo temporário utilizado em atualizações |

---

# Funcionamento do Empréstimo

Ao realizar um empréstimo:

1. O sistema busca o exemplar pelo ID
2. Verifica disponibilidade
3. Reduz a quantidade em estoque
4. Atualiza o arquivo automaticamente

Caso a quantidade seja `0`, o empréstimo é bloqueado.

---

# Funcionamento da Devolução

Na devolução:

O usuário informa:
- Data de retirada
- Data de devolução

O sistema calcula:
- Dias utilizados
- Dias de atraso
- Valor da multa

## Regra da multa

- Até 7 dias → sem multa
- Após 7 dias → R$ 1,00 por dia de atraso

---

# Segurança

O sistema utiliza ocultação de senha no terminal através da biblioteca:

```c
termios.h
```

Assim, a senha digitada não aparece na tela.

---

# Compilação

## Linux

### Compilar

```bash
gcc Biblioteca_Darcy.c -o biblioteca
```

### Executar

```bash
./biblioteca
```

---

# Tecnologias Utilizadas

- Linguagem C
- Manipulação de arquivos
- Structs
- Enum
- Terminal Linux
- Biblioteca `termios`

---

# Objetivo do Projeto

O projeto foi desenvolvido com finalidade acadêmica para praticar:

- Programação estruturada
- Manipulação de arquivos
- Organização modular
- Controle de acesso
- Estruturas de dados em C
- Lógica de sistemas CRUD

---

# Autor

João Guilherme Monteiro
