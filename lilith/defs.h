#ifndef __LILITH_DEFS_H__
#define __LILITH_DEFS_H__

// alloc.c //////////////////////////////////////////////////////////////////////////////////////////////////////////

#define STBM_MUTEX_HANDLE int *
#define STBM_MUTEX_ACQUIRE spin_lock
#define STBM_MUTEX_RELEASE spin_unlock
#define STBM_UINT32 uint32_t
#define STBM_UINTPTR uintptr_t
#define STBM_POINTER_SIZE 64
#define STBM_ASSERT(x) { if(!(x)) _exit(1); }
#define STBM_MEMSET memset
#define STBM_MEMCPY memcpy
#include "stb_malloc.h"

extern stbm_heap *data_heap;
extern stbm_heap *code_heap;
void heaps_init(void);

// utils.c //////////////////////////////////////////////////////////////////////////////////////////////////////////
extern struct hash_t paths_table;

uint64_t read_uint64(void *mem, off_t off);
void *malloc_executable_aligned(size_t size, int64_t alignment, int64_t misalignment);
char *strclone(char *s);
void writestr(int fd, char *s);
bool extension_is(char *s, char *ext);
void signal_handler(int sig, siginfo_t *info, void *ucontext);
char *fileconcat(char *p1, char *p2, bool for_templeos);

// hash.c //////////////////////////////////////////////////////////////////////////////////////////////////////////
struct hash_t {
	struct hash_entry_t *h;
	int sz;
};

struct hash_entry_t {
	char *key;
	struct hash_entry_t *next;
	struct export_t *val;
};

void hash_init(struct hash_t *h, int sz);
struct export_t *hash_get(struct hash_t *h, char *key);
void hash_put(struct hash_t *h, char *key, struct export_t *val);
struct hash_entry_t *hash_find_closest_entry_before(struct hash_t *h, uint64_t v);
int hashfn(char *key);

// load.c //////////////////////////////////////////////////////////////////////////////////////////////////////////
extern struct hash_t symbols;

struct export_t {
	uint32_t type;
	uint64_t val;
	uint64_t module_base;
};

struct templeos_thread {
	struct CCPU *Gs;
	struct CTask *Fs;
};

struct templeos_thread_info {
	pthread_t thread_id;
	
	struct templeos_thread t;
	
	void (*fp)(uint8_t *);
	uint8_t *data;
	uint64_t stk_size;
	
	bool window_initialized;
	bool window_failed;
	Window win;
	XImage *image;
	XShmSegmentInfo shminfo;
	bool image_used_by_server;
	struct CDC *dc;
	uint32_t *text_base;
	
	struct templeos_thread_info *next;
};

void load_pass1(uint8_t *patch_table, uint8_t *module_base);
void load_one_import(uint8_t **patch_table, uint8_t *module_base, int64_t ld_flags);
struct export_t *symbols_put(char *key, uint32_t type, uint64_t val, void *module_base);
void load_kernel(void);

void kernel_patch_instruction(char *name, off_t off, uint8_t original, uint8_t replacement);
void trampoline_kernel_patch(struct templeos_thread *t, char *name, void dest(void));
void kernel_patch_var32(char *name, uint32_t val);
void kernel_patch_var64(char *name, uint64_t val);
void kernel_patch_var64_off(char *name, int off, uint64_t val);
uint64_t *kernel_var64_ptr(char *name);

// task.c //////////////////////////////////////////////////////////////////////////////////////////////////////////

void init_templeos(struct templeos_thread *t, void *stk_base_estimate);
void enter_templeos(struct templeos_thread *t);
void exit_templeos(struct templeos_thread *t);

void *find_entry_point(struct templeos_thread *t, char *name);
uint64_t call_templeos(struct templeos_thread *t, char *name);
uint64_t call_templeos2(struct templeos_thread *t, char *name, uint64_t arg1, uint64_t arg2);
void call_templeos3(struct templeos_thread *t, char *name, uint64_t arg1, uint64_t arg2, uint64_t arg3);
uint64_t call_templeos4(struct templeos_thread *t, char *name, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4);
uint64_t call_templeos6(struct templeos_thread *t, char *name, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5, uint64_t arg6);

void *malloc_for_templeos(uint64_t size, stbm_heap *heap, bool zero);
void free_for_templeos(void *p);
void register_templeos_memory(void *p, size_t sz, bool is_mmapped);
struct templeos_mem_entry_t *get_templeos_memory(uint64_t p);
bool is_templeos_memory(uint64_t p);

extern pthread_mutex_t thread_create_destruct_mutex;
extern struct templeos_thread_info *first_templeos_task;

void *templeos_task_start(void *arg);

// templeos_hash_table.c //////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "templeos_defs.h"

struct thiter {
	struct CHashTable *h;
	int i;
	bool first;
	struct CHash *he;
};

struct thiter thiter_new(struct CTask *task);
void thiter_next(struct thiter *it);
bool thiter_valid(struct thiter *it);

bool is_hash_type(struct CHash *he, uint64_t type);

void print_templeos_hash_table(FILE *out, struct CTask *task);

int print_stack_trace(FILE *out, struct CTask *task, uint64_t rip, uint64_t rbp, uint64_t rsp);

void *templeos_var64_ptr(struct CTask *task, char *name);

// static.c //////////////////////////////////////////////////////////////////////////////////////////////////////////

struct builtin_file {
	char *name;
	uint64_t size;
	uint8_t *body;
};
extern uint8_t kernel_bin_c[];
extern struct builtin_file builtin_files[];

// syscall_tramp.c //////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup_syscall_trampolines(void);

// x11.c //////////////////////////////////////////////////////////////////////////////////////////////////////////

extern char *x11_display;
extern bool x11_enabled;

void x11_start(struct templeos_thread sys_winmgr_thread);

#endif