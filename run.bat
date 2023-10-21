if not exist bin mkdir bin
make CC='C:\Users\Connor\Downloads\cc65\bin\cl65.exe'
if not exist .\bin\sorcery64.prg echo "No sorcery64.prg found"
if exist .\bin\sorcery64.prg x64sc .\bin\sorcery64.prg