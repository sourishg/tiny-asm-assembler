# Tiny ASM Assembler

This can handle the following operations on byte-sized registers: `mov`, `cmp`, `jmp`, `jc`, `jl`, `int`, `add`. Additionally `mov` works on word-sized registers too. Please note that the forward jump functionality isn't implemented yet.

# Compiling and Running

Compile using:
```bash
$ git clone https://github.com/sourishg/tiny-asm-assembler
$ cd tiny-asm-assembler/
$ gcc assembler.c
```

Run:
```bash
$ ./a.out
```

Sample input:
```bash
mov ah 2
mov dl 65
mov bl 70
L:
int 33
add dl 1
cmp dl bl
jl L
mov ah 76
int 33
end
```

Sample output:
```bash
.model small
.code
db 180
db 2
db 178
db 65
db 179
db 70
db 205
db 33
db 128
db 194
db 1
db 58
db 211
db 124
db -9
db 180
db 76
db 205
db 33
end
```

Paste the output on an ASM file and compile it using `masm`. The actual output will be `ABCDE`.

# License

MIT
