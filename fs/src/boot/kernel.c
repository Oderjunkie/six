typedef unsigned long long int size_t;
enum {
  VMEMWIDTH = 80,
  VMEMHEIGHT = 25,
  VMEMCHARSIZE = 2,
  VMEMC = VMEMWIDTH * VMEMHEIGHT * VMEMCHARSIZE,
};
static unsigned char *const VMEM = (unsigned char *) 0xB8000;
static unsigned int VMEMI = 0;
extern unsigned char inb(unsigned short int);
extern unsigned short int inw(unsigned short int);
extern void outb(unsigned short int, unsigned char);

void *memset(void *ptr, int fill, size_t len) {
  while (len --> 0) ((char *) ptr)[len] = fill;
  return ptr;
}

void putc(const char c) {
  if (c == '\n') {
    VMEMI += VMEMWIDTH - (VMEMI % VMEMWIDTH);
  } else {
    VMEM[VMEMI * 2] = c;
    VMEM[VMEMI * 2 + 1] = 0x0F;
    ++VMEMI;
  }
}

void puts(const char str[]) {
  const char *ptr;

  for (ptr = str; *ptr; ++ptr)
    putc(*ptr);
}

void putx(unsigned char x) {
  static const char hex[] = "0123456789abcdef";
  putc(hex[x >> 4]);
  putc(hex[x & 0x0F]);
}

void kernel_main() {
  unsigned char buffer[512] = { 0 };
  unsigned char *bufp = buffer;
  outb(0x1f2, 0x01);
  outb(0x1f3, 0x01);
  outb(0x1f4, 0x00);
  outb(0x1f5, 0x00);
  outb(0x1f6, 0xa0);
  outb(0x1f7, 0x20);
  while (!(inb(0x1f7) & 0x08))
    ;
  for (int i = 0; i < 0x100; ++i) {
    unsigned short int byte;
    byte = inw(0x1f0);
    *bufp++ = byte & 0xFF;
    *bufp++ = byte >> 8;
  }
  bufp = buffer + 0x100;
  for (int j = 0; j < 16; ++j) {
    for (int i = 0; i < 16; ++i) {
      putx(*bufp++);
      putc(' ');
      if (i % 8 == 7) putc(' ');
    }
    putc('\n');
  }
}

