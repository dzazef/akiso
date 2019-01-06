section .data
  scan: db "%lf", 0
  print: db "%lf", 10, 0

section .bss
  inp resb 8
  
section .text
  global main
  extern printf
  extern scanf

main:
  push inp
  push scan
  call scanf
  
  finit					;moduł zmiennoprzecinkowy
  fld qword [inp]		;st(0) = x
  fldl2e				;st(1) = x | st(0) = log2(e)
  fyl2x					;st(0) = x*log2(e)
  f2xm1					;st(0) = 2^(x*log2(e))-1
  fld1					;st(1) = 2^(x*log2(e))-1 | st(0) = 1
  faddp					;st(0) = 2^(x*log2(e))
  fld1					;st(1) = 2^(x*log2(e)) | st(0) = 1
  fld1					;st(2) = 2^(x*log2(e)) | st(1) = 1 | st(0) = 1
  faddp					;st(1) = 2^(x*log2(e)) | st(0) = 2
  fdivp					;st(0) = 2^(x*log2(e))/2
  fld qword [inp]		;st(1) = 2^(x*log2(e))/2 | st(0) = x
  fchs					;st(1) = 2^(x*log2(e))/2 | st(0) = -x
  fldl2e				;st(2) = 2^(x*log2(e))/2 | st(1) = -x | st(0) = log2(e)
  fyl2x					;st(1) = 2^(x*log2(e))/2 | st(0) = -x*log2(e)
  f2xm1					;st(1) = 2^(x*log2(e))/2 | st(0) = 2^(-x*log2(e))-1
  fld1					;st(2) = 2^(x*log2(e))/2 | st(1) = 2^(-x*log2(e))-1 | st(0) = 1
  faddp					;st(1) = 2^(x*log2(e))/2 | st(0) = 2^(-x*log2(e))
  fld1					;st(2) = 2^(x*log2(e))/2 | st(1) = 2^(-x*log2(e)) | st(0) = 1
  fld1					;st(3) = 2^(x*log2(e))/2 | st(2) = 2^(-x*log2(e)) | st(1) = 1 | st(0) = 1
  faddp					;st(2) = 2^(x*log2(e))/2 | st(1) = 2^(-x*log2(e)) | st(0) = 2
  fdivp					;st(1) = 2^(x*log2(e))/2 | st(0) = 2^(-x*log2(e))/2
  fsubrp				;st(0) = 2^(x*log2(e))/2 - st(0) = 2^(-x*log2(e))/2
  
printresult:
  fstp qword [inp]
  push dword [inp+4]
  push dword [inp]
  push print
  call printf
  
end:
  mov eax, 1
  int 0x80
