# *** THIS IS NOT A LONG TERM SOLUTION ***

LCFLAGS ?= -Isrc -g -Wall -Wextra -Werror

all: wasmjit

WASMJIT_PREQS = src/wasmjit/main.o src/wasmjit/vector.o src/wasmjit/ast.o src/wasmjit/parse.o src/wasmjit/ast_dump.o src/wasmjit/compile.o src/wasmjit/runtime.o src/wasmjit/util.o src/wasmjit/elf_relocatable.o src/wasmjit/dynamic_emscripten_runtime.o src/wasmjit/posix_sys.o src/wasmjit/instantiate.o src/wasmjit/emscripten_runtime.o src/wasmjit/high_level.o src/wasmjit/dynamic_runtime.o src/wasmjit/sys.o src/wasmjit/high_level_posix.o

clean:
	rm -f wasmjit $(WASMJIT_PREQS) src/wasmjit/posix_sys_linux_kernel.o src/wasmjit/kwasmjit_linux.o src/wasmjit/x86_64_jmp.o

wasmjit: $(WASMJIT_PREQS)
	$(CC) -o $@ $(WASMJIT_PREQS) $(LCFLAGS) -pthread

.c.o:
	$(CC) -c -o $@ $< $(LCFLAGS)
