# Functions, Parameters, and File I/O in C

## Functions and Parameters

A function is a named, reusable block of instructions — write the steps once, run ("call") them as many times as needed.

```c
#include <stdio.h>

int add(int a, int b) {
    int sum = a + b;
    return sum;
}

int main(void) {
    int result = add(3, 5);
    printf("%d\n", result);   // prints 8
    return 0;
}
```

- `int add(int a, int b)` — the function signature.
  - `add` — the function's name.
  - `int` (before the name) — the type of value the function returns.
  - `(int a, int b)` — the **parameters**: blanks that only exist inside this function.
- `{ ... }` — the function body.
- `return sum;` — hands the value back to the caller and immediately exits the function.
- `add(3, 5)` in `main` is the **call**. `3` and `5` here are the **arguments** — the actual values plugged into the parameter blanks.

**Parameter vs argument:** parameter = the blank in the definition (`a`, `b`). Argument = what you plug in at the call site (`3`, `5`).

**Why functions:** write logic once instead of duplicating it; a well-named function documents itself; you can test one function in isolation.

**No return value → `void`:**
```c
void printGreeting(void) {
    printf("Hello!\n");
}
```

**Pass by value (the gotcha that matters for labs):** C copies arguments into parameters. Changing a parameter inside a function does NOT change the original variable in the caller.

```c
void tryToChange(int x) {
    x = 100;
}

int main(void) {
    int num = 5;
    tryToChange(num);
    printf("%d\n", num);   // still 5, not 100
}
```

To let a function actually modify a variable in the caller (e.g. Lab 0.2's "swap" problem), pass a **pointer** (the variable's address) instead of the value itself.

## File I/O

A file is data saved on disk that survives after the program ends (unlike a variable, which lives in RAM and disappears when the program exits). File I/O = reading from / writing to files.

**Notebook analogy:** open the drawer and take the notebook out (open the file) → read or write pages → put it back (close the file). You can't use a file you haven't opened.

### Opening — `fopen`

```c
FILE *fp = fopen("data.txt", "r");
```

- Returns a `FILE *` — a "ticket" representing the open file connection. Shown to every function that reads/writes it.
- Mode string:
  - `"r"` — read only, file must exist.
  - `"w"` — write only; **creates the file, or erases it if it already exists.**
  - `"a"` — append; write, adds to the end instead of erasing.
  - `"r+"` / `"w+"` — read and write.
  - Add `b` (e.g. `"rb"`) for binary mode.

**Always check for failure.** `fopen` returns `NULL` if it can't open the file (missing, no permission, etc.) instead of crashing outright — but using a `NULL` pointer afterward *will* crash the program. So:

```c
if (fp == NULL) {
    printf("Could not open file\n");
    return 1;
}
```

### Reading

- **`fgetc(fp)`** — one character at a time. Returns `int`, not `char`, because it needs the extra value `EOF` ("end of file") to signal "nothing left."
- **`fgets(buffer, size, fp)`** — one line at a time, capped at `size-1` chars so it can't overflow the buffer (the safe alternative to `gets`, which has no size limit and is banned in modern C).
- **`fscanf(fp, format, ...)`** — structured/numeric data, like `scanf` but from a file. Stops at whitespace, so it's bad for free text with spaces.

Rule of thumb: unknown/free text → `fgets`. Structured/numeric data → `fscanf`. Byte-by-byte → `fgetc`.

#### `fgetc(fp)` — parameter by parameter

Full signature: `int fgetc(FILE *stream);`

| Parameter | Meaning |
|---|---|
| `stream` (named `fp` in our code) | The `FILE *` ticket from `fopen` — tells `fgetc` *which* open file to pull the next character from. `fgetc` has no idea about "the file" in general, only about whichever `FILE *` you hand it. |

Only one parameter, but two things to notice about what it returns: it's `int`, and each call moves an internal "current position" forward by one character, so the *next* call to `fgetc(fp)` continues from where the last one left off — the `FILE *` itself is tracking your position in the file for you.

```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("greeting.txt", "r");
    if (fp == NULL) {
        printf("Could not open file\n");
        return 1;
    }

    int ch;
    int charCount = 0;
    int vowelCount = 0;

    while ((ch = fgetc(fp)) != EOF) {
        charCount++;
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            vowelCount++;
        }
    }

    printf("Total characters: %d\n", charCount);
    printf("Lowercase vowels: %d\n", vowelCount);

    fclose(fp);
    return 0;
}
```
Run against `greeting.txt` (`"Hello, file!\nLine two.\nAppended line.\n"`), output:
```
Total characters: 38
Lowercase vowels: 11
```
This is the shape you'd reuse for Lab 0.3's line/word-counting problem — reading char-by-char lets you inspect and react to every single character, which `fgets`/`fscanf` don't give you as directly.

#### `fgets(buffer, size, fp)` — parameter by parameter

Full signature: `char *fgets(char *str, int n, FILE *stream);`

| Parameter | Meaning |
|---|---|
| `str` (`buffer`/`line` in our code) | A `char` array you already declared — `fgets` writes the line it reads *into* this array. You provide the storage; `fgets` fills it. |
| `n` (`size`) | The array's **capacity**, not the line length. `fgets` reads at most `n-1` real characters, then always appends a `'\0'` (null terminator) after them — this is exactly what makes overflow impossible, unlike `gets`, which has no size limit at all. |
| `stream` (`fp`) | Same as before — which open file to read from. |

In practice `n` is almost always written as `sizeof(line)`, which asks the compiler "how many bytes did I actually declare this array with?" instead of hardcoding a number that could drift out of sync with the array's real size.

```c
char line[256];
while (fgets(line, sizeof(line), fp) != NULL) {
    printf("%s", line);
}
```
(Output already shown above under "Reading it back" — `Hello, file!` / `Line two.` / etc., one call per line.)

#### `fscanf(fp, format, ...)` — parameter by parameter

Full signature: `int fscanf(FILE *stream, const char *format, ...);`

| Parameter | Meaning |
|---|---|
| `stream` (`fp`) | Which open file to read from. |
| `format` (`"%d %d"` in our example) | A template describing what pattern of values to expect next in the file — `%d` means "expect a whole number here," and the literal space between the two `%d`s means "skip any whitespace between them" (spaces, tabs, newlines all count). |
| `...` (the rest — `&a, &b`) | One pointer *per* `%` placeholder in the format string, in the same order. They must be addresses (`&a`, not `a`) because `fscanf` needs to reach back into your variables and write the values it read — the same pass-by-value problem from Part 1: without `&`, `fscanf` would only get a copy and your real variable would stay untouched. |

```c
FILE *fp = fopen("numbers.txt", "w");
fprintf(fp, "10 20\n30 40\n");
fclose(fp);

fp = fopen("numbers.txt", "r");
int a, b;
while (fscanf(fp, "%d %d", &a, &b) == 2) {
    printf("Read pair: %d + %d = %d\n", a, b, a + b);
}
fclose(fp);
```
Output:
```
Read pair: 10 + 20 = 30
Read pair: 30 + 40 = 70
```
`fscanf`'s return value — the `int` it hands back — is how many `%` placeholders it actually managed to fill in on that call. That's why the loop checks `== 2`: it stops the moment a read doesn't produce a full pair (including at genuine end-of-file), rather than trusting a generic "did it work" check.

### Writing

```c
fprintf(out, "id=%d name=%s\n", id, name);   // formatted, like printf
fputs("plain text\n", out);                    // raw string, no formatting
fputc('x', out);                               // one character
```

### Closing — `fclose(fp)`

Not optional. Writes are buffered (held in memory) before actually hitting disk; `fclose` flushes that buffer. Skipping it risks losing writes, and leaked open handles can exhaust the OS's per-process file limit.

### Worked examples, each compiled and run for real (`gcc -Wall -Wextra -Werror`)

**1. Writing a file**
```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("greeting.txt", "w");
    if (fp == NULL) {
        printf("Could not open file\n");
        return 1;
    }
    fprintf(fp, "Hello, file!\n");
    fprintf(fp, "Line two.\n");
    fclose(fp);
    printf("Wrote to greeting.txt\n");
    return 0;
}
```
Program output:
```
Wrote to greeting.txt
```
Contents of `greeting.txt` afterward (checked with `cat greeting.txt`):
```
Hello, file!
Line two.
```

**2. Reading it back**
```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("greeting.txt", "r");
    if (fp == NULL) {
        printf("Could not open file\n");
        return 1;
    }
    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    fclose(fp);
    return 0;
}
```
Output:
```
Hello, file!
Line two.
```

**3. Appending (mode `"a"` — adds to the end, does not erase)**
```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("greeting.txt", "a");
    if (fp == NULL) {
        printf("Could not open file\n");
        return 1;
    }
    fprintf(fp, "Appended line.\n");
    fclose(fp);
    printf("Appended to greeting.txt\n");
    return 0;
}
```
Output:
```
Appended to greeting.txt
```
`greeting.txt` now contains (the first two lines survived — `"a"` did not erase them, unlike `"w"` would have):
```
Hello, file!
Line two.
Appended line.
```
Running the read-back program (#2) again now prints all three lines.

**4. Opening a file that doesn't exist — the `NULL` check firing for real**
```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("doesnotexist.txt", "r");
    if (fp == NULL) {
        printf("Could not open doesnotexist.txt\n");
        return 1;
    }
    fclose(fp);
    return 0;
}
```
Output:
```
Could not open doesnotexist.txt
```
Exit code: `1` (nonzero — signals failure to the shell/caller). This is the `fopen` failure path from earlier, not hypothetical — `doesnotexist.txt` genuinely isn't there, and the program detects it and exits cleanly instead of crashing.

**5. Structured reading with `fscanf`**
```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("numbers.txt", "w");
    fprintf(fp, "10 20\n30 40\n");
    fclose(fp);

    fp = fopen("numbers.txt", "r");
    if (fp == NULL) {
        printf("Could not open file\n");
        return 1;
    }
    int a, b;
    while (fscanf(fp, "%d %d", &a, &b) == 2) {
        printf("Read pair: %d + %d = %d\n", a, b, a + b);
    }
    fclose(fp);
    return 0;
}
```
Output:
```
Read pair: 10 + 20 = 30
Read pair: 30 + 40 = 70
```
Note the loop condition: `fscanf` returns how many values it successfully matched. Checking `== 2` (not just "did it succeed at all") is what makes the loop stop cleanly at end of file instead of looping forever on a failed read — a common bug when people check `fscanf(...) != EOF` instead.

**Control flow (general shape across all five):** open → check for `NULL` → do the read/write work → close.
**Complexity:** O(n) in file size, O(1) extra memory (just the line/variable buffer — the whole file is never loaded into memory at once with `fgets`/`fscanf`).
**Interview follow-ups:** why `fgets` over `gets`? (buffer-overflow safety). Why does `fgetc` return `int`? (needs `EOF` outside `char`'s range). `fscanf`/`fprintf` vs `fread`/`fwrite`? (text-mode/formatted vs raw binary bytes — `fread`/`fwrite` for structs, images, non-text data). Why check `fscanf`'s return count instead of comparing to `EOF`? (a malformed line that matches 0 or 1 fields isn't necessarily end-of-file, and looping on it forever is a classic infinite-loop bug).
