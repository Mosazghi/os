# 6. Memory Management

TLB, hit/miss, hit rate, temporal/spatial locality, TLB entry, ASID, multi-level page table, PTBR, PDBR, CR3, inverted page table, swap, page fault, minor/major page fault, optimal/fifo/random/LRU/clock page replacement, demand-paging vs pre-paging/pre-fetching, thrashing, working set, hugepages

To major issues with `Paging` are:

1. It is too slow, every memory access (also called a memory reference) leads to an
   extra memory access since the page table is stored in RAM; **Solved with TLB
   (translation lookaside buffer)**:
   - A part of the MMU
   - an _address-translation cache_ that stores the most recent translations
   - Such that the MMU can look up the translation in the TLB, instead of the page table (faster)
2. The page table is to big (takes up too much space in RAM), let’s solve this with
   one of
   - Multi-level page table (most used)
   - Inverted page table

### 6.1.1 TLB (Translation Lookaside Buffer)

Example:

```c
int i, sum = 0;
  for (i = 0; i < 10; i++) {
  sum += a[i];
}
```

![tlb-array](assets/tlb-array.png)

_Elements that reside besides each other will get faster access times, because of the TLB-lookup._

Thus, our **TLB hit-rate** is 70% (7 out of 10 hits).

To take advantage of hardware caches, we need to exploit _locality_ (in instructions and references).

- **Temporal locality**: If you access a memory location, you are likely to access it again soon.
- **Spatial locality**: If you access a memory location, you are likely to access nearby memory locations soon.

TLBs rely on both temporal and spatial locality to achieve high hit rates.

### Who needs to handle TLB misses?

In old days, the hardware would handle it:

1. It needs to know _where_ the page table (via **page table register**) is stored in memory, and their _exact format_.
2. "Walk" the page table to find the correct entry and extract, and update TLB.

Modern CPUs use a **Hardware-managed TLB**:

1. The hardware raises an exception when a TLB miss occurs.
2. -> interrupt handler in the OS kernel is invoked to handle the miss.
3. the code will look up the correct entry in the page table and update the TLB.
4. and return

Advantages of this approach:

- The OS can decide how to handle TLB misses -- **flexibility**.
- The hardware doesn't do much -- **simplicity**.

### 6.1.2 TLB contents

Typical entry:

VPN | PPN | Other bits

- Other bits:
  - Valid bit: Is this entry valid traslation?
  - Protection bits: Can we read/write/execute this page?
  - etc.

When problem arises with TLB: **HOW TO MANAGE TLB CONTENTS ON A CONTEXT SWITCH?**

- Simply solution is to _flush_ the TLB on a context switch (setting all valid
  bits to 0 thus clearing out the TLB).

But flushing could introduce a performance penalty, so we have a better solution:

**ASID (Address Space Identifier)**

![asid](assets/asid.png)

## 6.2 Smaller Page Tables

Trying to tackle huge memory usage.

_Bigger pages_ lead to internal fragmentation, _smaller pages_ lead to more page table entries.
