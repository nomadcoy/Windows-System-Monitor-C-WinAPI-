# Windows System Monitor (C + WinAPI)

Monitor de sistema em tempo real desenvolvido em **C**, utilizando **WinAPI** para coletar métricas do Windows.

## Funcionalidades

- Uso de CPU (%)
- Número de núcleos
- Memória total e disponível (RAM)
- Percentual de uso de memória
- Atualização a cada 1 segundo

---

## Requisitos

- Windows 10 ou 11
- MSYS2 instalado: https://www.msys2.org/
- Ambiente **MSYS2 UCRT64**

---

## Como rodar (MSYS2 UCRT64)

Abra o terminal **MSYS2 UCRT64** e execute:

```bash
# Instalar o compilador (caso ainda não tenha)
pacman -S mingw-w64-ucrt-x86_64-gcc

# Ir até a pasta do projeto
cd /c/caminho/para/o/projeto
# Exemplo:
# cd /c/Users/Admin/Downloads

# Compilar
gcc monitor.c -o monitor.exe

# Executar
./monitor.exe

## Conceitos Utilizados

GetSystemTimes() → cálculo de uso de CPU
GlobalMemoryStatusEx() → monitoramento de RAM
GetSystemInfo() → número de núcleos
Programação em C com WinAPI
