# Notes
* So it turns out it is not possible to invade a lot of memory with just plain integer array because of stack size limitation. So gotta use `malloc`.

* If one doesn't touch the memory after allocating with `malloc`, the os doesn't actually seem to allocate the memory.

* There is some kind of limitation how much memory a process can consume. The process `Segmentation fault` after `2048M` even though there is more free memory left.

### Tip
`htop` is much easier and convenient than `free` or `top` to keep track of memory.
