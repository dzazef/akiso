# akiso
Skrypty i programy na Architekturę Komputerów i Systemów Operacyjnych.

## Lista 2.
### Zad 6.
Program wyświetlający napisy w różnych kolorach przy użyciu sekwencji Esc.
### Zad 7.
Program zamieniający wszystkie nazwy plików w danym katalogu na małe litery.

## Lista 3.
### Zad 1.
Skrypt pokazujący prędkość przesyłania danych za pomoca wykresu, czas działania systemu, stan baterii oraz obciążenie systemu.
### Zad 2.
Skrypt pokazujący informacje o wszystkich procesach.
### Zad 3.
Skrypt wyświetlający obraz za pomoca ASCII art oraz cytat.
### Zad 4.
Program monitorujący zmiany na stronie.
Podczas uruchamiania program przyjmuje jako pierwszy parametr adres strony, a jak drugi czas odświeżania.

## Lista 4.
### Zad 1.
Uruchamianie powłoki Bash z prawami roota.
### Zad 2.
Programy sprawdzające działania polecenia kill oraz sygnałów.
### Zad 3.
Prosta wersja powłoki **lsh**.

## Lista 5.
### Zad 1.
Własna implementacja funkcji **printf** oraz **scanf**.
Aby skompilować program przy użyciu gcc należy mieć zainstalowaną bibliotekę gcc-multilib.  
Kompilacja przy użyciu polecenia
```
gcc -m32 -fno-stack-protector zad1.c
```
### Zad 2.
Wielowątkowa wersja mnożenia macierzy boolowskich.  
Kompilacja przy użyciu polecenia  
```
gcc -pthread zad2.c
```
Podczas uruchamiania program przyjmuje jako pierwszy parametr bok macierzy, a jako drugi liczbę wątków.  
### Zad 3.
Prosty komunikator internetowy (serwer) napisany przu użyciu wywołania **select** oraz socketów.    
Podczas uruchamiania program przyjmuje jako pierwszy parametr nazwę hosta, jako drugi port.  
Z serwerem można się połączyć np. za pomocą programu telnet.  
Po uruchomieniu widzimy listę dostępnych użytkowników, ustawiamy swój nick i możemy pisać do innych użytkowników za pomocą komendy
```
<username> <message>
```
### Zad 4.
Program mnożący dwukrotnie dwie macierze o dowolnym rozmiarze n, 
w tradycyjny sposób oraz robiąc wcześniej transpozycję macierzy.
Podczas uruchamiania program przyjmuje jako parametr bok macierzy.

## Lista 6.
### Zad 1.
Program zamieniający liczbę 8-bitową na system szesnastkowy w assemblerze dla 6502.
### Zad 2.
Program wyświetlający liczby pierwsze w zakresie od 1 do 1000.
Kompilacja przy użyciu polecenia:
```
nasm -f elf32 zad2.asm -o zad2.o
gcc -m32 zad2.o -o zad2
```
### Zad 3.
Prosty kalkulator w assemblerze x86.
Kompilacja przy użyciu polecenia:
```
nasm -f elf32 zad3.asm -o zad3.o
gcc -m32 zad3.o -o zad3
```
### Zad 4.
Program liczący silnię w assemblerze x86 przy użyciu komend SSE2.
```
nasm -f elf32 zad4.asm -o zad4.o
gcc -m32 zad4.o -o zad4
```
### Zad 8.
#### 1.
Program liczący sinus hiperboliczny w assemblerze x86.
```
nasm -f elf32 zad8_1.asm -o zad8_1.o
gcc -m32 zad8_1.o -o zad8_1
```
#### 2.
Program liczący area sinus hiperboliczny w assemblerze x86.
```
nasm -f elf32 zad8_2.asm -o zad8_2.o
gcc -m32 zad8_2.o -o zad8_2
```

## Lista 7.
### Zad 1.
Program dokonujący konwersji liczby zmiennoprzecinkowej zapisanej w postaci dziesiętnej do postaci binarnej z podaną dokładnością.
### Zad 6.
Program w języku C, który asembluje program napisany dla prostego procesora MARIE, wykorzystujący tylko adresy bezpośrednie.
