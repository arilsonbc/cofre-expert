$ErrorActionPreference='Stop'
$exe=Join-Path $PSScriptRoot '../bin/cofre-expert.exe'
$senha='VM-9x!R2k#L7p@Q5'
$cases=@(@{Name='correta';Value=$senha;Code=0},@{Name='vazia';Value='';Code=1},@{Name='curta';Value='abc';Code=1},@{Name='longa';Value=('A'*300);Code=1})
for($i=0;$i -lt $senha.Length;$i++) {
 $chars=$senha.ToCharArray()
 $chars[$i]=[char]([int]$chars[$i] -bxor 1)
 $cases+=@{Name="mutacao-$i";Value=(-join $chars);Code=1}
}
foreach($case in $cases) {
 $output=("$($case.Value)`n`n" | & $exe) -join "`n"
 $code=$LASTEXITCODE
 $expected=if($case.Code -eq 0){'ACESSO LIBERADO!'}else{'ACESSO NEGADO!'}
 if($code -ne $case.Code -or !$output.Contains($expected)){throw "Falhou: $($case.Name)"}
 Write-Host "OK: $($case.Name)"
}
Write-Host "Total: $($cases.Count) testes passaram."
