# Faustic Inferno's C++ implementation

## Machine state

The state of the machine is determined by the running state, the contents of CPU
registers, and the size and contents of available memory. Other information that
might be maintained by the environment is not considered part of the machine
state.

### Memory

The memory consists of two separate equally-sized parts, one for code and one
for data. The CPU sees memory as something internal, but its allocation is
decided by the environment, which can change memory size while the CPU is not
running. As long as there is enough memory available, the environment can change
memory size by specifying a number of bits between 12 and 64; the resulting
memory size is `pow(2, nbits)` for code memory and the same for data memory.

Memory addresses can be expressed with two bytes if `nbits <= 16`, four bytes
if `nbits > 16 && nbits <= 32`, or eight bytes if `nbits > 32`.

Integer values that take more than one byte are stored into memory following
big-endian conventions (most significant byte at the lowest address).

### CPU registers

The CPU has six 64-bit registers: one program counter, one pointer mask, two
general purpose registers (R0 and R1) and two stack control registers (S0 and
S1).

```
    |----------------|        |----------------|
    |       PC       |        |       PM       |
    |----------------|        |----------------|

    |----------------|        |----------------|
    |       R0       |        |       R1       |
    |----------------|        |----------------|

    |----------------|        |----------------|
    |       S0       |        |       S1       |
    |----------------|        |----------------|

```

`PC`: address of the instruction that will be executed next.

`PM`: mask that will be applied to values that express memory addresses. It will
always have the form `0xffff'ffff'ffff'ffff >> (64 - nbits)`.

`R0`: primary general purpose register.

`R1`: secondary general purpose register.

`S0`: stack pointer register.

`S1`: stack base register.


### Running state

The CPU may be in one of two states: running or paused. While it is running,
instructions are fetched and executed in order one at a time. While it is
paused, the contents of memory and registers are preserved, and the environment
may see them and change them.
