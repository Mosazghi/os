#include <stdio.h>
#define VPN_MASK 0xFFFFFFFFFFFFF000
#define PTI_MASK 0x1FF

int main() {
  int x = 10;
  unsigned long addr = (long)&x;

  unsigned long VPN = (addr & VPN_MASK) >> 12;

  unsigned long offset = (addr & ~VPN_MASK);

  unsigned long PTI = (VPN & PTI_MASK);

  printf("x's location: %p\n", &x);
  printf("VPN: 0x%lx\n", VPN);
  printf("offset: 0x%lx\n", offset);
  printf("PTI: 0x%lx\n", PTI);
  return 0;
}

/*
 *  Ved 4_000_000 * 4 = 16_000_000 (16MB) ser jeg redusert i hastighet fordi den
 *  nærmerer seg L3 cache som er 18MB.
 *
 *  Ved 40_000_000 * 4 = 160_000_000 (160MB) ser jeg kraftig redusert hastighet
 *  fordi den er langt over L3 cache (som betry at den må fetche fra memory).
 *
 * */
