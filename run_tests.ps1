# Compila e executa testes automatizados para jogo_tetris
Set-StrictMode -Version Latest
Push-Location -Path (Split-Path -Path $MyInvocation.MyCommand.Path -Parent)

# Garantir pastas
$testsDir = Join-Path -Path $PWD -ChildPath 'tests'
$outputsDir = Join-Path -Path $PWD -ChildPath 'outputs'
if (-Not (Test-Path $outputsDir)) { New-Item -ItemType Directory -Path $outputsDir | Out-Null }

# Finaliza processo pendente
Get-Process -Name outDebug -ErrorAction SilentlyContinue | Stop-Process -Force -ErrorAction SilentlyContinue

# Compilar
Write-Host "Compilando..."
& gcc -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference -g3 -O0 -c main.c -o .\build\Debug\main.o
& gcc -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference -g3 -O0 .\build\Debug\main.o -o .\build\Debug\outDebug.exe
if ($LASTEXITCODE -ne 0) { Write-Error "Compilação falhou."; Exit 1 }

# Executar cada teste
$tests = Get-ChildItem -Path $testsDir -Filter "*.txt" | Sort-Object Name
foreach ($t in $tests) {
    $outFile = Join-Path $outputsDir ($t.BaseName + ".out")
    Write-Host "Executando teste: $($t.Name) -> $outFile"
    $errFile = $outFile + '.err'
    Start-Process -FilePath ".\build\Debug\outDebug.exe" -RedirectStandardInput $t.FullName -RedirectStandardOutput $outFile -RedirectStandardError $errFile -NoNewWindow -Wait
}

Write-Host "Todos os testes executados. Saídas em: $outputsDir"
Pop-Location