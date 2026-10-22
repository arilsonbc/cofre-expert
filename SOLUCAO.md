# Solução — spoilers

Senha: `VM-9x!R2k#L7p@Q5` (16 caracteres ASCII, respeitando maiúsculas e símbolos).

A VM decodifica pares opcode/argumento com XOR 0xa7/0x5c. LOAD (0x31) lê um caractere e aplica XOR com um byte do estado; ADD (0x52) soma módulo 256; ROL (0x73) rotaciona 8 bits; CHECK (0x94) acumula divergências com o argumento XOR 0xd3; MIX (0xb5) atualiza o estado por (estado XOR acumulador)*1103515245+12345, módulo 2^32; END (0xe6) testa divergências e estado final. O índice de leitura percorre (i*7)%16. Decodifique os pares e reverta ROL, ADD e XOR em cada rodada. Como o resultado esperado do acumulador está no CHECK, é possível calcular o próximo estado e resolver sequencialmente.

Para o patch, localize o ponto que escolhe sucesso/falha após a validação, confirme com entradas diferentes e altere uma cópia. Não há offsets fixos neste guia: dependem da compilação. Um patch na mensagem isolada pode exibir sucesso sem alterar o código de saída; uma solução completa deve também retornar código 0.

O teste automatizado usa a senha correta, uma mutação em cada posição, entrada vazia, curta e longa. Ele não demonstra que você concluiu a análise manual no Ghidra ou x64dbg.
