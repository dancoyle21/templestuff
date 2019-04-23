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

void signal_handler(int sig, siginfo_t *info, void *ucontext_void) {
	struct templeos_thread t;
	exit_templeos(&t);
	struct ucontext_t *ucontext = (struct ucontext_t *)ucontext_void;
	
	uint64_t rip = ucontext->uc_mcontext.gregs[REG_RIP];
	uint64_t rbp = ucontext->uc_mcontext.gregs[REG_RBP];
	int count = 0;
	
	fprintf(stderr, "Received signal %d at 0x%lx\n", sig, rip);
	
	while ((count < 20) && (rbp != 0)) {
		//TODO: figure out what rip belongs to
		fprintf(stderr, "\trip=0x%lx rbp=0x%lx\n", rip, rbp);
		
		if (!is_templeos_memory(rip)) {
			break;
		}
		
		struct hash_entry_t *e = hash_find_closest_entry_before(&symbols, rip);
		if (e != NULL) {
			uint64_t ghidra_off = 0;
			
			if (e->val->module_base != 0) {
				ghidra_off = rip - e->val->module_base + 0x10000020;
			}
			
			fprintf(stderr, "\t\tat %s (0x%lx+0x%lx) ghidra=0x%lx\n", e->key, e->val->val, rip - e->val->val, ghidra_off);
		}
		
		rip = *((uint64_t *)(rbp+8));
		rbp = *((uint64_t *)rbp);
		++count;
	}
	
	//TODO: stacktrace
	
	fflush(stderr);
	_exit(EXIT_FAILURE);
}