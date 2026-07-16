*This project has been created as part of the 42 curriculum by garodri2.*

---

## Description

`get_next_line` is a C function that reads one line at a time from a given file descriptor. Each call picks up exactly where the last one left off, allowing a file (or stdin) to be consumed line by line without loading it fully into memory.

This implementation covers the mandatory part: a single file descriptor tracked with one static variable.

---

## Files

| File | Description |
|------|-------------|
| `get_next_line.c` | Core function + `check_new_line`, `read_fd`, `build_line`, `clean` |
| `get_next_line_utils.c` | `ft_strlen`, `ft_strjoin`, `ft_strncpy` |
| `get_next_line.h` | Header with prototypes, `BUFFER_SIZE` default, and includes |

---

## Instructions

### Compilation

`BUFFER_SIZE` controls how many bytes `read()` fetches per call. Set it at compile time:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

If `-D BUFFER_SIZE` is omitted, the header defaults to `42`.

### Usage example

```c
#include "get_next_line.h"
#include 
#include 

int main(void)
{
    int   fd;
    char  *line;

    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Prototype

```c
char *get_next_line(int fd);
```

Returns the next line including `\n`, or `NULL` on EOF or error. The caller must `free()` the returned string.

---

## Algorithm

### Overview

The function relies on a **persistent stash** — a heap-allocated string that survives between calls via a `static` variable. On each call, it reads from the fd only as much as needed to find a `\n`, returns the complete line, and saves whatever remains in the stash for the next call.

### Call flow
get_next_line(fd)
│
├─ read_fd(fd, stash)
│       └─ loop: read(fd, buffer, BUFFER_SIZE)
│              → strjoin stash + buffer
│              → stop when '\n' found in stash or EOF
│
├─ build_line(stash)
│       └─ copy stash[0..'\n'] into a new string → return as line
│
└─ clean(stash)
└─ copy stash[after '\n'..end] into a new string → new stash
free old stash
return NULL if nothing remains

### Function breakdown

**`check_new_line(stash)`** — scans the stash for `\n`. Used as the loop condition inside `read_fd` to stop reading as soon as a full line is available.

**`read_fd(fd, stash)`** — allocates a `BUFFER_SIZE + 1` buffer, reads in a loop, and appends each chunk to the stash via `ft_strjoin` (which always frees the old stash). Stops on EOF (`bytes == 0`), error (returns `NULL`, freeing both `buffer` and `stash`), or when `\n` is detected in the stash.

**`build_line(stash)`** — walks the stash until `\n` or `\0`, allocates exactly the right amount, copies that slice with `ft_strncpy`, and returns it. The `\n` is included in the returned string.

**`clean(stash)`** — advances past the `\n` in the stash. If nothing follows (or there's no `\n` at all), frees stash and returns `NULL`. Otherwise allocates a new string from the remainder, frees the original, and returns the trimmed stash.

**`ft_strjoin(s1, s2)`** — concatenates `s1` and `s2` into a new allocation, always freeing `s1`. If `s1` is `NULL`, it initialises an empty string before joining, so the very first call works without a pre-allocated stash.

**`ft_strncpy(dest, src, n)`** — copies up to `n` bytes from `src` into `dest`, padding the rest with `\0` if `src` is shorter than `n`.

### Design choices and trade-offs

- **`ft_strjoin` frees s1** — this avoids a separate `free(stash)` after every append and keeps `read_fd` clean, but it means the caller must never use `s1` after the call.
- **No `lseek`, no global variables** — as required by the subject.
- **`BUFFER_SIZE` agnostic** — because the stash accumulates partial reads, the function behaves correctly whether `BUFFER_SIZE` is `1`, `42`, or `10000000`. A very large buffer may over-read past the first `\n`, but that data is preserved in the stash and returned correctly on the next call.

---

## Resources

- [man 2 read](https://man7.org/linux/man-pages/man2/read.2.html) — behavior and return values of the `read()` syscall.
- [man 2 open](https://man7.org/linux/man-pages/man2/open.2.html) — opening file descriptors.
- [42 Subject: get_next_line](https://cdn.intra.42.fr/pdf/pdf/44/get_next_line.en.pdf) — official project subject.

**AI usage in this project:**

-  AI was used to explain C concepts.