# 9. I/0 and HDD/SSD

Memory and I/O buses/interconnect, PCI/USB/SATA, micro-controller, I/O device, programmed I/O, interrupt-based I/O, DMA, I/O instructions (isolated I/O), memory-mapped I/O, I/O stack, block device, storage stack, block addresses, sector, HDD, platter, surface, spindle, RPM, track, cylinder, disk arm, disk head, seek time, rotational delay, SSD, SLC/MLC/TLC, NAND flash, flash translation layer, trim, write amplification, wear levelling, RAID 0/1/5, iops, sequential/random read/write

## 9.1 Input / Output

![proto-system-arch](assets/proto-system-arch.png)

^ Why do we need this hierarchy?

> Because of physics (for high-performance) and cost.

![modern-system-arch](assets/modern-system-arch.png)

**DMI**: Direct Media Interface
**eSATA**: External SATA (Serial ATA) (ATA: AT Attachment)

---

![canonical-device](assets/canonical-device.png)

^ The first is the **hardware interface** that it provides.
^ Second is the **internals**, that is implement-specific (containing firmware
etc)

```c
While (STATUS == BUSY)
; // wait until device is not busy
Write data to DATA register
Write command to COMMAND register
(starts the device and executes the command)
While (STATUS == BUSY)
; // wait until device is done with your request
```

^ Typical how the OS communicates with the device.

When the main CPU is involved in the data movement, it is called **programmed I/O**.

^ This implementation (polling) is not efficient, because the CPU is waiting for the device

> Instead, we can use **interrupts**, which lets the calling process to sleep.

That is, we go from this:

![polling](assets/polling.png)

To this:

![interrupt](assets/interrupt.png)

**However**:

> If a device is fast, it may be best to _poll_; if it is slow, _interrupts_, which allows for overlaps

And if the device is both fast and slow, it may be best to use a **hybrid** approach where

> Poll for a little, if it's not finished, then sleep and wait for an interrupt.

---

![slow-cpu](assets/slow-cpu.png)

^ When the CPU is moving data to and from Memory, it's quite slow

Instead we can use **DMA** (Direct Memory Access), where the device can directly access the memory

With DMA:

![dma](assets/dma.png)

It works as follows:

1. The CPU tells the DMA engine where data lives in memory, how much data to move, and which device to send it to.
2. When the DMA is complete, the DMA controller raises an interrupt and the OS knows the transfer is complete.

---

How to communicate with the device?

1. The oldest way is to use **I/O instructions** (isolated I/O) (in/out instructions)

   - use `in` and `out` instructions with an address space based on ports (similar to TCP/UDP ports)

2. **Memory-mapped I/O**:
   - use physical addresses (those not used by RAM) and map those to registers on I/O-devices, then we can reuse instructions like `mov`

---

How to fit every device into the OS (each with its own interface)

We used the good-old technique called **abstraction**:

- We create a **device driver** for each device

![device-driver](assets/device-driver.png)

## 9.2 Storage

#### Addressing

The (HDD) drive consist of a large number of _n_ **sectors** (512 bytes blocks) that are numbered from 0 to _n-1_.

This is the **address space** of the drive.

### 9.2.1 HDD

![hdd](assets/hdd.png)
A HDD consists of:

- platter with surface grouped in a spindle
- rotation measured in RPM
- a circle on a surface is a track, the set of all tracks above each other is a cylinder
- a disk arm accesses a sector with its disk head
- each platter have two surfaces, there are many platters and each platter have
  a disk arm for top and bottom surface
- e.g. eight platters with two surfaces means 16 disk arms (they all move to-
  gether, not independently)

#### HDD Access Times

- **Seek time**: time to move the disk arm to the right track
- **Rotational delay**: time to wait for the sector to rotate under the head
- **Accessing Sectors**: time to read/write the sector

Total time = $T_{I/O} = T_{seek} + T_{rotational} + T_{transfer}$

![track2](assets/track2.png)

#### Calculations

Compute $T_{rotation}$ for a 7200 RPM:

$T_{rotation} = \frac{1 minute}{7200 rot} \cdot \frac{60 seconds}{1 minute} \cdot \frac{1000 ms}{1 seconds} = \frac{8.33 ms}{rot}$

Given transfer rate of 100 MB/s, calculate how long it takes to transfer 512 KB block in ms:

$\frac{ms}{1 request} = \frac{512 KB}{1 request} \cdot \frac{1 MB}{1024 KB} \cdot \frac{1 s}{100MB} \cdot \frac{1000ms}{1 second} = \frac{5ms}{request}$

![calc](assets/calc.png)
![RIO](assets/RIO.png)

---

### 9.2.2 SSD

![ssd](assets/ssd.png)

> **Solid State Drive**
>
> - No moving parts
> - Faster than HDD
> - More expensive
> - Limited write cycles

#### 9.2.2.1. Storing bits

- **SLC (Single Level Cell)**: 1 bit per transistor
- **MLC (Multi Level Cell)**: 2 bits per transistor
- **TLC (Triple Level Cell)**: 3 bits per transistor

---

**Three low-level mechanisms**

- **Read**: read a page
- **Erase**: (before writing) erase a block
- **Program**: write a sector

![states](assets/states.png)

---

![perf](assets/perf.png)

**Major issues with SSDs**

- **Wear out**: limited number of write cycles
- **Disturbance**: when writing to a cell, the surrounding cells may be disturbed

---

![logical-diagram](assets/logical-diagram.png)

- **FTL**: Flash Translation Layer (maps logical addresses to physical addresses)
  - should be fast and reliable

For even better performance, we can use **parallelism** of the flash chips.

Another performance goal is to reduce **write amplification** (the amount of data written to the flash memory is more than the amount of data written by the host)

**wear leveling**: spread out the writes over the entire disk to reduce wear out (done so by the _FTL_)

**direct mapped FTL**: is bad in terms of performance and reliability.

## Summary

## Review Questions and Problems

1. What is the difference between memory-mapped I/O and isolated I/O?

   - Memory-mapped I/O uses the same address space as the memory, while isolated I/O uses a separate address space.

   - Memory-mapped uses the same instructions as memory, while isolated I/O uses special I/O instructions.

2. (KEY PROBLEM) On a hard drive, how many bytes are in a sector?
   How long would you estimate it takes to fetch a 4KB block at a
   random location on the disk if the disk has 2MB per track, is
   15000rpm and has an average seek time of 3ms?

   - 512 bytes or 4KB

   - ![2](assets/2.png)

3. What is the benefit of organizing disks in a RAID? How are the disks organized at RAID level 1? How are the disks organized at RAID level 5?

   - Share data across multiple disks for performance and reliability.

   - RAID 1: Mirrored
     ![2024-10-21-19-16-15](assets/2024-10-21-19-16-15.png)
   - RAID 5: Striped with parity
     ![raid5](assets/raid5.png)

4. (KEY PROBLEM) Explain the difference between HDD and SSD in terms of reading, writing/overwriting and deleting files. What is the point of the TRIM command?

Reading, writing and erasing are the same (sector on HDD, and pages on SSD), the big one
the difference is overwritten since SSDs must erase the contents of the cells before they can
has been written to, and deletion can only take place on entire blocks. Since HDD and SSD do not
understand what can be deleted before the operating system tries to overwrite something takes overwriting
long on the SSD, this should be solved with the TRIM command, which is a way to
The OS will notify the SSD that data may be deleted.

- **TRIM**: Siden HDD og SSD ikke skjønner hva som kan slettes før OSet forsøker overskrive noe tar overskriving lang til p˚a SSD, dette skal løses med TRIM kommandoen som er en m˚ate for OSet ˚a gi SSD’n beskjed om at data kan slettes.

5. Why is it beneficial that data is stored continuously (in sequence) on a HDD? Does this also apply to a SSD? Justify your answer.

   - Because the disk arm can move to the next sector without having to wait for the disk to rotate. This does not apply to SSDs because there is no moving parts.

6. (KEY PROBLEM) Run the command `iostat` on your linux. What is TPS? What is the difference between running just iostat and
   iostat 1 ?

- TPS: Transactions per second (IOPS)
- `iostat` shows the average since boot, `iostat 1` shows the average for the last second.

<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>
<script type="text/x-mathjax-config">
    MathJax.Hub.Config({ tex2jax: {inlineMath: [['$', '$']]}, messageStyle: "none" });
</script>
