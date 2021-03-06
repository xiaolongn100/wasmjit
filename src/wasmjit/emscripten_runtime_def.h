/* -*-mode:c; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */

/*
  Copyright (c) 2018 Rian Hunter et. al, see AUTHORS file.

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
 */

#define DEFINE_WASM_I32_GLOBAL(_name, _init, _mut)          \
	DEFINE_WASM_GLOBAL(_name, _init, VALTYPE_I32, i32, _mut)
#define DEFINE_WASM_F64_GLOBAL(_name, _init, _mut)             \
	DEFINE_WASM_GLOBAL(_name, _init, VALTYPE_F64, f64, _mut)

#define CURRENT_MODULE global

START_MODULE()

START_TABLE_DEFS()
END_TABLE_DEFS()

START_MEMORY_DEFS()
END_MEMORY_DEFS()

#define NAN_BITS 0x7ff8000000000000
#define INFINITY_BITS 0x7ff0000000000000

START_GLOBAL_DEFS()
DEFINE_WASM_F64_GLOBAL(NaN, NAN_BITS, 0)
DEFINE_WASM_F64_GLOBAL(Infinity, INFINITY_BITS, 0)
END_GLOBAL_DEFS()

START_FUNCTION_DEFS()
END_FUNCTION_DEFS()

END_MODULE()

#undef CURRENT_MODULE

#define CURRENT_MODULE env

START_MODULE()

START_TABLE_DEFS()
DEFINE_EXTERNAL_WASM_TABLE(table)
END_TABLE_DEFS()

START_MEMORY_DEFS()
DEFINE_WASM_MEMORY(memory, 256, 256)
END_MEMORY_DEFS()

START_GLOBAL_DEFS()
DEFINE_EXTERNAL_WASM_GLOBAL(__memory_base)
DEFINE_EXTERNAL_WASM_GLOBAL(__table_base)
DEFINE_EXTERNAL_WASM_GLOBAL(memoryBase)
DEFINE_EXTERNAL_WASM_GLOBAL(tempDoublePtr)
DEFINE_EXTERNAL_WASM_GLOBAL(DYNAMICTOP_PTR)
DEFINE_EXTERNAL_WASM_GLOBAL(STACKTOP)
DEFINE_EXTERNAL_WASM_GLOBAL(STACK_MAX)
DEFINE_WASM_I32_GLOBAL(tableBase, 0, 0)
DEFINE_WASM_I32_GLOBAL(ABORT, 0, 0)
END_GLOBAL_DEFS()

#define DEFINE_EMSCRIPTEN_FUNCTION(_name, _output, _n, ...)		\
	DEFINE_WASM_FUNCTION(_name, &(wasmjit_emscripten_ ## _name), _output, _n, ##__VA_ARGS__)

START_FUNCTION_DEFS()
DEFINE_EMSCRIPTEN_FUNCTION(enlargeMemory, VALTYPE_I32, 0)
DEFINE_EMSCRIPTEN_FUNCTION(getTotalMemory, VALTYPE_I32, 0)
DEFINE_EMSCRIPTEN_FUNCTION(abortOnCannotGrowMemory, VALTYPE_I32, 0)
DEFINE_EMSCRIPTEN_FUNCTION(abortStackOverflow, VALTYPE_NULL, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(nullFunc_ii, VALTYPE_NULL, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(nullFunc_iii, VALTYPE_NULL, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(nullFunc_iiii, VALTYPE_NULL, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(nullFunc_iiiii, VALTYPE_NULL, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(nullFunc_iiiiii, VALTYPE_NULL, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(nullFunc_vi, VALTYPE_NULL, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(nullFunc_vii, VALTYPE_NULL, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(nullFunc_viii, VALTYPE_NULL, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(nullFunc_viiii, VALTYPE_NULL, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___lock, VALTYPE_NULL, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___setErrNo, VALTYPE_NULL, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall3, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall42, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall140, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall146, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall4, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall54, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall6, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___unlock, VALTYPE_NULL, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_emscripten_memcpy_big, VALTYPE_I32, 3, VALTYPE_I32, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(abort, VALTYPE_NULL, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___buildEnvironment, VALTYPE_NULL, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall10, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall102, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall221, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall12, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall122, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall142, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall145, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall15, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall168, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall180, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall181, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall191, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall340, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall192, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall194, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall195, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall196, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall197, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall199, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall200, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall202, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall20, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall201, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall212, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall220, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall5, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall268, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall272, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall295, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall300, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall334, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall38, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall39, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall60, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall63, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall64, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall66, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall75, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall85, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall91, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall97, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_abort, VALTYPE_NULL, 0)
DEFINE_EMSCRIPTEN_FUNCTION(_endgrent, VALTYPE_NULL, 0)
DEFINE_EMSCRIPTEN_FUNCTION(_execve, VALTYPE_I32, 3, VALTYPE_I32, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_clock_gettime, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_exit, VALTYPE_NULL, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_fork, VALTYPE_I32, 0)
DEFINE_EMSCRIPTEN_FUNCTION(_getaddrinfo, VALTYPE_I32, 4, VALTYPE_I32, VALTYPE_I32, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_gai_strerror, VALTYPE_I32, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_getenv, VALTYPE_I32, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_getgrent, VALTYPE_I32, 0)
DEFINE_EMSCRIPTEN_FUNCTION(_getgrnam, VALTYPE_I32, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_getpagesize, VALTYPE_I32, 0)
DEFINE_EMSCRIPTEN_FUNCTION(_getpwnam, VALTYPE_I32, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_gettimeofday, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_gmtime_r, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_time, VALTYPE_I32, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_kill, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_llvm_stackrestore, VALTYPE_NULL, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_llvm_stacksave, VALTYPE_I32, 0)
DEFINE_EMSCRIPTEN_FUNCTION(_localtime_r, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_localtime, VALTYPE_I32, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_mktime, VALTYPE_I32, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_raise, VALTYPE_I32, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_sched_yield, VALTYPE_I32, 0)
DEFINE_EMSCRIPTEN_FUNCTION(_sem_init, VALTYPE_I32, 3, VALTYPE_I32, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_sem_post, VALTYPE_I32, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_sem_wait, VALTYPE_I32, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_setgrent, VALTYPE_NULL, 0)
DEFINE_EMSCRIPTEN_FUNCTION(_setgroups, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_setitimer, VALTYPE_I32, 3, VALTYPE_I32, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_sigaction, VALTYPE_I32, 3, VALTYPE_I32, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall29, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_sigaddset, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_sigemptyset, VALTYPE_I32, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_sigprocmask, VALTYPE_I32, 3, VALTYPE_I32, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_sigsuspend, VALTYPE_I32, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_strftime, VALTYPE_I32, 4, VALTYPE_I32, VALTYPE_I32, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_sysconf, VALTYPE_I32, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_usleep, VALTYPE_I32, 1, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_utimes, VALTYPE_I32, 2, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_waitpid, VALTYPE_I32, 3, VALTYPE_I32, VALTYPE_I32, VALTYPE_I32)
END_FUNCTION_DEFS()

DEFINE_WASM_START_FUNCTION(wasmjit_emscripten_start_func)

END_MODULE()

#undef DEFINE_EMSCRIPTEN_FUNCTION

#undef CURRENT_MODULE

#undef DEFINE_WASM_F64_GLOBAL
#undef DEFINE_WASM_I32_GLOBAL
