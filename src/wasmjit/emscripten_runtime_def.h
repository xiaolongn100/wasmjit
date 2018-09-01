/* -*-mode:c; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */

/*
  Copyright (c) 2018 Rian Hunter

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

#define staticAlloc(_top , s)                           \
	(((_top) + (s) + 15) & ((uint32_t) -16))

#define alignMemory(size, factor) \
	(((size) % (factor)) ? ((size) - ((size) % (factor)) + (factor)) : (size))

#define TOTAL_STACK 5242880
#define STACK_ALIGN_V 16
#define GLOBAL_BASE 1024
#define STATIC_BASE (GLOBAL_BASE)
#define STATICTOP ((STATIC_BASE) + 5472 - 16)
#define tempDoublePtr_V (staticAlloc((STATICTOP), 16))
#define DYNAMICTOP_PTR_V (staticAlloc((tempDoublePtr_V), 4))
#define STACKTOP_V (alignMemory((DYNAMICTOP_PTR_V), (STACK_ALIGN_V)))
#define STACK_BASE_V (STACKTOP_V)
#define STACK_MAX_V ((STACK_BASE_V) + (TOTAL_STACK))


#define CURRENT_MODULE global

START_MODULE()

START_TABLE_DEFS()
END_TABLE_DEFS()

START_MEMORY_DEFS()
END_MEMORY_DEFS()

START_GLOBAL_DEFS()
DEFINE_WASM_F64_GLOBAL(NaN, NAN, 0)
DEFINE_WASM_F64_GLOBAL(Infinity, INFINITY, 0)
END_GLOBAL_DEFS()

START_FUNCTION_DEFS()
END_FUNCTION_DEFS()

END_MODULE()

#undef CURRENT_MODULE

#define CURRENT_MODULE env

START_MODULE()

START_TABLE_DEFS()
END_TABLE_DEFS()

START_MEMORY_DEFS()
DEFINE_WASM_MEMORY(memory, 256, 256)
END_MEMORY_DEFS()

START_GLOBAL_DEFS()
DEFINE_WASM_I32_GLOBAL(memoryBase, STATIC_BASE, 0)
DEFINE_WASM_I32_GLOBAL(tableBase, 0, 0)
DEFINE_WASM_I32_GLOBAL(DYNAMICTOP_PTR, DYNAMICTOP_PTR_V, 0)
DEFINE_WASM_I32_GLOBAL(tempDoublePtr, tempDoublePtr_V, 0)
DEFINE_WASM_I32_GLOBAL(ABORT, 0, 0)
DEFINE_WASM_I32_GLOBAL(STACKTOP, STACKTOP_V, 0)
DEFINE_WASM_I32_GLOBAL(STACK_MAX, STACK_MAX_V, 0)
END_GLOBAL_DEFS()

#define DEFINE_EMSCRIPTEN_FUNCTION(_name, ...) \
	DEFINE_WASM_FUNCTION(_name, &(wasmjit_emscripten_ ## _name), __VA_ARGS__)

START_FUNCTION_DEFS()
DEFINE_EMSCRIPTEN_FUNCTION(enlargeMemory, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(getTotalMemory, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(abortOnCannotGrowMemory, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(abortStackOverflow, VALTYPE_NULL, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(nullFunc_ii, VALTYPE_NULL, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(nullFunc_iiii, VALTYPE_NULL, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___lock, VALTYPE_NULL, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___setErrNo, VALTYPE_NULL, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall140, VALTYPE_I32, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall146, VALTYPE_I32, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall54, VALTYPE_I32, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___syscall6, VALTYPE_I32, VALTYPE_I32, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(___unlock, VALTYPE_NULL, VALTYPE_I32)
DEFINE_EMSCRIPTEN_FUNCTION(_emscripten_memcpy_big, VALTYPE_I32, VALTYPE_I32, VALTYPE_I32, VALTYPE_I32)
END_FUNCTION_DEFS()

END_MODULE()

#undef DEFINE_EMSCRIPTEN_FUNCTION

#undef CURRENT_MODULE

#undef DEFINE_WASM_F64_GLOBAL
#undef DEFINE_WASM_I32_GLOBAL
