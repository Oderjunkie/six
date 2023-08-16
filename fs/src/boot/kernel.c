typedef unsigned long long int size_t;
enum {
  VMEMWIDTH = 80,
  VMEMHEIGHT = 25,
  VMEMCHARSIZE = 2,
  VMEMC = VMEMWIDTH * VMEMHEIGHT * VMEMCHARSIZE
};
static const unsigned char *VMEM = (unsigned char *) 0xB8000;
static unsigned char *VMEMP = (unsigned char *) 0xB8000;
extern unsigned char in(unsigned short int);
extern void out(unsigned short int, unsigned char);

void *memset(void *ptr, int fill, size_t len) {
  while (len --> 0) ((char *) ptr)[len] = fill;
  return ptr;
}

void kernel_main() {
  memset(VMEM, 0, VMEMC);
}

