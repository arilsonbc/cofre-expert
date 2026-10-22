# Cofre expert — nível 4

Crackme educativo em C para Windows x64, Ghidra e x64dbg. Você tem autorização para analisar, depurar, modificar e distribuir suas soluções deste projeto (licença MIT).

Maquina virtual de bytecode com acumulador, estado encadeado e instrucoes codificadas.

A classificação é relativa à série Cofre Fácil: expert é o mais complexo desta série didática, sem pretensão de reproduzir proteções comerciais.

## Comece pelo executável

Baixe o ZIP em **Releases**, extraia e execute `bin/cofre-expert.exe`. Não precisa instalar compilador ou dependências extras. O ZIP do desafio contém apenas o EXE e este guia. Evite abrir `src/`, `tests/` e `SOLUCAO.md` antes de tentar: contêm spoilers.

## Objetivos verificáveis

1. Descobrir uma senha aceita e abrir o EXE original fora do depurador.
2. Explicar a transformação dos dados e confirmar a interpretação do Ghidra no assembly e em execução no x64dbg.
3. Em uma cópia, modificar a decisão de acesso e salvar o patch no arquivo.
4. Executar a cópia modificada fora do depurador com duas senhas erradas diferentes e obter sucesso.

Use **x64dbg**, pois o executável é de 64 bits. Guarde o original e compare seu SHA-256 com o arquivo publicado. Endereços absolutos podem variar; anote também o módulo e o deslocamento relativo. Alterar registradores durante uma sessão não equivale a salvar um patch no EXE.

## Dicas graduais

<details><summary>Dica 1</summary>

Comece pelas strings de sucesso e falha e siga suas referências cruzadas. A senha não aparece como uma string legível no executável.
</details>

<details><summary>Dica 2</summary>

Identifique o despachante da VM, mapeie os opcodes e registre acumulador e estado a cada instrucao.
</details>

<details><summary>Dica 3</summary>

Cada instrução ocupa dois bytes. O opcode é decodificado com XOR 0xa7 e o argumento com XOR 0x5c. Há seis operações.
</details>

## Compilar e testar

Com Zig 0.13.0 no Windows, execute na pasta do projeto:

```powershell
.\build.ps1 -Zig 'C:\caminho\zig.exe'
.\tests\test.ps1
```

Flags: `-O2 -s`. O executável não contém símbolos de depuração. A compilação otimizada pode fundir funções e reorganizar condições; o pseudocódigo não é o fonte original.

Programa local de console: não usa rede, não guarda arquivos e não acessa dados pessoais. A dificuldade está no algoritmo; não há anti-debug, temporizadores ou verificações do computador. Não use este cofre fictício para proteger dados reais.
