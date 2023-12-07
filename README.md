# sorcery64
Sorcery64 is somthing of a demake of [sorcery](https://github.com/ConnorMilligan/sorcery), a project for my advanced programming class at the University of Vermont with [Tim Harrold](https://github.com/timjhh).

## Building
Building should be pretty straight forward, the only requirement is the [cc65](https://github.com/cc65/cc65) compiler. This is tested working with cc65 2.19 on Gentoo linux.

Compiling can be done by creating a `bin/` directory, and calling `make` or using a run script which will also run the program into the [VICE emulator](https://vice-emu.sourceforge.io/).

## Notes
- Maps are stored as binary, with each bit representing a cell in each row. `map.c` is a little programs that can generate these maps. In a 20x20 map, the size is reduced down to 15% it's original size!
- Fat pointer for strings and linear allocators could have improved memory safety when it comes to formatted printing.
- Writing a map data structure would have worked well for the locale system.
- The `takeInput()` function really should have had it's code functionalized.

## Sources
- [Commodore 64 Programmer's Reference Guide](https://archive.org/details/c64-programmer-ref)
- [MOS 6581 SID Data Sheet](https://archive.org/details/mos-6581-sid-data-sheet)