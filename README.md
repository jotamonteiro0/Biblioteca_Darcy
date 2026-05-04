# Sistema Bibliotecário Simples — Biblioteca Darcy

Sistema de gerenciamento de biblioteca desenvolvido em linguagem C, com persistência de dados em arquivos `.txt`. Projeto acadêmico da disciplina de Algoritmos e Programação.

---

## Funcionalidades

- Cadastro e listagem de usuários
- Cadastro e listagem de exemplares
- Empréstimo de exemplares (com controle de estoque)
- Devolução com cálculo automático de multa por atraso

---

## Regras de Negócio

- Prazo máximo de empréstimo: **7 dias**
- Multa por atraso: **R$ 1,00 por dia excedente**
- O sistema calcula o atraso automaticamente com base nas datas informadas

---

## Como compilar e executar

### Pré-requisitos

- GCC instalado
- Linux (testado no Arch Linux)

### Compilar

```bash
gcc trabalho_hilson.c -o biblioteca
```

### Executar

```bash
./biblioteca
```

---

## Arquivos gerados

| Arquivo | Conteúdo |
|---|---|
| `Usuarios.txt` | Dados dos usuários cadastrados |
| `Exemplares.txt` | Dados dos exemplares e estoque |

---

## Estrutura do Menu

```
+------------------------------+
|     BIBLIOTECA DARCY         |
+------------------------------+
| 1  - Cadastrar Usuario       |
| 2  - Listar Usuarios         |
| 3  - Cadastrar Exemplar      |
| 4  - Listar Exemplares       |
| 5  - Emprestimo              |
| 6  - Devolucao               |
| 7  - Sair                    |
+------------------------------+
```

---

## Observações

- O sistema utiliza `system("clear")` para limpar o terminal — compatível com Linux
- As datas devem ser inseridas no formato `DD/MM/AAAA`
- Os arquivos de dados são criados automaticamente na primeira execução

---

## Autor

João Monteiro  
Curso de Engenharia de Software — 1° Período
