;uruchom używając:
;nasm -f elf32 zad2.asm -o zad2.o
;gcc -m32 zad2.o -o zad2


section .data
  int: db "%d", 10, 0
  
section .text
  global main
  extern printf

main:
  mov ebx,1
  
start:					;pętla od 2 do 1000
  cmp ebx,1000
  je end				;jeśli 1000 zakończ program
  inc ebx
    
  prime:				;sprawdzenie czy liczba pierwsza
    mov ecx,1			;dzielnik

    check:
      inc ecx			;zwiększ dzielnik
      mov eax,ebx		;dzielna
      cmp ecx,ebx		;jeśli dzielna i dzielnik sa takie same znaczy że liczba jest pierwsza
      je printint		;wypisz liczbę
      mov edx,0			;wyzeruj edx
      div ecx			;edx <- eax MOD ecx
      cmp edx,0
      je start			;jeśli edx 0 liczba nie jest pierwsza
      call check      	

printint:
  push ebx
  push dword int
  call printf
  call start
  
end:
  mov eax, 1
  int 0x80
