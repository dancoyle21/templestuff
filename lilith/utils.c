uint64_t read_uint64(void *mem, off_t off) {
	return *((uint64_t *)(((char *)mem) + off));
}

void *malloc_executable_aligned(size_t size, int64_t alignment, int64_t misalignment) {
	int64_t mask=alignment-1;
	uint8_t *ptr = mmap(NULL, size+mask+sizeof(int64_t)+misalignment, PROT_EXEC|PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS|MAP_32BIT, -1, 0);
	// note that MAP_32BIT is fundamental, this will break if the ptr3 can't be represented in 32bits, if linux ever stops honoring MAP_32BIT we're going to be fucked hard.
	uint8_t *res=(uint8_t *)((((uint64_t)(ptr+sizeof(int64_t)+mask))&~mask)+misalignment);
	//res(I64 *)[-1]=ptr-res; // wtf is this?
	register_templeos_memory(res, size);
	return res;
}

char *strclone(char *s) {
	char *r = malloc(strlen(s)+1);
	strcpy(r, s);
	return r;
}

bool extension_is(char *s, char *ext) {
	if (strlen(s) <= strlen(ext)) {
		return false;
	}
	
	char *p = s + strlen(s) - strlen(ext);
	return strcmp(p, ext) == 0;
}

void writestr(int fd, char *s) {
	char *p = s;
	int n = strlen(s);
	while (n > 0) {
		int r = write(fd, p, n);
		if (r == -1) {
			_exit(EXIT_FAILURE);
		}
		p += r;
		n -= r;
	}
}

#define STACKTRACE_PRINT_ARGS true

void signal_handler(int sig, siginfo_t *info, void *ucontext_void) {
	struct templeos_thread t;
	exit_templeos(&t);
	struct ucontext_t *ucontext = (struct ucontext_t *)ucontext_void;
	
	uint64_t rip = ucontext->uc_mcontext.gregs[REG_RIP];
	uint64_t rbp = ucontext->uc_mcontext.gregs[REG_RBP];
	
	fprintf(stderr, "Received signal %d at 0x%lx\n", sig, rip);
	print_stack_trace(stderr, rip, rbp);
	
	fprintf(stderr, "\nRegisters:\n");
	
	fprintf(stderr, "\tRAX %016llx\n", ucontext->uc_mcontext.gregs[REG_RAX]);
	fprintf(stderr, "\tRBX %016llx\n", ucontext->uc_mcontext.gregs[REG_RBX]);
	fprintf(stderr, "\tRCX %016llx\n", ucontext->uc_mcontext.gregs[REG_RCX]);
	fprintf(stderr, "\tRDX %016llx\n", ucontext->uc_mcontext.gregs[REG_RDX]);
	fprintf(stderr, "\tRSI %016llx\n", ucontext->uc_mcontext.gregs[REG_RSI]);
	fprintf(stderr, "\tRDI %016llx\n", ucontext->uc_mcontext.gregs[REG_RDI]);
	fprintf(stderr, "\tR8  %016llx\n", ucontext->uc_mcontext.gregs[REG_R8]);
	fprintf(stderr, "\tR9  %016llx\n", ucontext->uc_mcontext.gregs[REG_R9]);
	fprintf(stderr, "\tR10 %016llx\n", ucontext->uc_mcontext.gregs[REG_R10]);
	fprintf(stderr, "\tR11 %016llx\n", ucontext->uc_mcontext.gregs[REG_R11]);
	fprintf(stderr, "\tR12 %016llx\n", ucontext->uc_mcontext.gregs[REG_R12]);
	fprintf(stderr, "\tR13 %016llx\n", ucontext->uc_mcontext.gregs[REG_R13]);
	fprintf(stderr, "\tR14 %016llx\n", ucontext->uc_mcontext.gregs[REG_R14]);
	fprintf(stderr, "\tR15 %016llx\n", ucontext->uc_mcontext.gregs[REG_R15]);
	
	fprintf(stderr, "\nPrint system hash table:\n");
	
	print_hash_table(stderr, t.Fs);
	
	fflush(stderr);
	_exit(EXIT_FAILURE);
}

void print_stack_trace(FILE *out, uint64_t rip, uint64_t rbp) {
	int count = 0;
	
	while ((count < 20) && (rbp != 0)) {
		fprintf(out, "\trip=0x%lx rbp=0x%lx\n", rip, rbp);
		
		if (!is_templeos_memory(rip)) {
			break;
		}
		
		struct hash_entry_t *e = hash_find_closest_entry_before(&symbols, rip);
		if (e != NULL) {
			uint64_t ghidra_off = 0;
			
			if (e->val->module_base != 0) {
				ghidra_off = rip - e->val->module_base + 0x10000020;
			}
			
			fprintf(out, "\t\tat %s (0x%lx+0x%lx) ghidra=0x%lx\n", e->key, e->val->val, rip - e->val->val, ghidra_off);
		}
		
		rip = *((uint64_t *)(rbp+0x8));
		
		if (STACKTRACE_PRINT_ARGS) {
			fprintf(out, "\t\t\targs");
			for (int i = 1; i <= 3; i++) {
				fprintf(out, " %lx", *((uint64_t *)(rbp+0x8*(i+1))));
			}
			fprintf(out, "\n");
		}
		
		rbp = *((uint64_t *)rbp);
		++count;
	}
}

void print_stack_trace_here(void) {
	uint64_t rbp;
	asm("movq %%rbp, %0" : "=r"(rbp));
	
	uint64_t rip = *((uint64_t *)(rbp+0x8));
	
	struct templeos_thread t;
	bool itm = false;
	
	if (is_templeos_memory(rip)) {
		itm = true;
		exit_templeos(&t);
	}
	
	print_stack_trace(stderr, rip, rbp);
	
	if (itm) {
		enter_templeos(&t);
	}
}

struct hash_t paths_table;

uint64_t intern_path(char *p) {
	struct export_t *e = hash_get(&paths_table, p);
	if (e != NULL) {
		return e->val;
	}
	e = (struct export_t *)malloc(sizeof(struct export_t));
	char *k = strclone(p);
	e->type = 0;
	e->val = (uint64_t)(k);
	hash_put(&paths_table, k, e);
	return e->val;
}
