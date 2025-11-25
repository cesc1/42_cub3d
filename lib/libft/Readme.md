# Libft


- [1 About](#1-about)
- [2 Documentation](#2-documentation)
  - [2.1 libc functions](#21-libc-functions)
    - [ft_isalpha](#ft_isalpha)
    - [ft_isdigit](#ft_isdigit)
    - [ft_isalnum](#ft_isalnum)
    - [ft_isascii](#ft_isascii)
    - [ft_isprint](#ft_isprint)
    - [ft_strlen](#ft_strlen)
    - [ft_memset](#ft_memset)
    - [ft_bzero](#ft_bzero)
    - [ft_memcpy](#ft_memcpy)
    - [ft_memmove](#ft_memmove)
    - [ft_strlcpy](#ft_strlcpy)
    - [ft_strlcat](#ft_strlcat)
    - [ft_toupper](#ft_toupper)
    - [ft_tolower](#ft_tolower)
    - [ft_strchr](#ft_strchr)
    - [ft_strrchr](#ft_strrchr)
    - [ft_strncmp](#ft_strncmp)
    - [ft_memchr](#ft_memchr)
    - [ft_memcmp](#ft_memcmp)
    - [ft_strnstr](#ft_strnstr)
    - [ft_atoi](#ft_atoi)
    - [ft_calloc](#ft_calloc)
    - [ft_strdup](#ft_strdup)
  - [2.2 Additional functions](#22-additional-functions)
    - [ft_substr](#ft_substr)
    - [ft_strjoin](#ft_strjoin)
    - [ft_strtrim](#ft_strtrim)
    - [ft_split](#ft_split)
    - [ft_itoa](#ft_itoa)
    - [ft_strmapi](#ft_strmapi)
    - [ft_striteri](#ft_striteri)
    - [ft_putchar_fd](#ft_putchar_fd)
    - [ft_putstr_fd](#ft_putstr_fd)
    - [ft_putendl_fd](#ft_putendl_fd)
    - [ft_putnbr_fd](#ft_putnbr_fd)
    - [ft_printf](#ft_printf)
    - [get_next_line](#get_next_line)
  - [2.3 List functions](#23-list-functions)
    - [ft_lstnew](#ft_lstnew)
    - [ft_lstadd_front](#ft_lstadd_front)
    - [ft_lstsize](#ft_lstsize)
    - [ft_lstlast](#ft_lstlast)
    - [ft_lstadd_back](#ft_lstadd_back)
    - [ft_lstdelone](#ft_lstdelone)
    - [ft_lstclear](#ft_lstclear)
    - [ft_lstiter](#ft_lstiter)
    - [ft_lstmap](#ft_lstmap)

# 1 About

This is my 42 libft library. Here I’ll create **C** utility functions to
use in future projects.

# 2 Documentation

## 2.1 libc functions

### ft_isalpha

`int ft_isalpha(int c)`

- **Description:** Checks if a character is alphabetic (upper or lower)
- **Arguments:**
  - `c (int)`: An unsigned char to check
- **Return:** None zero if true (1024), zero if false
- **Requires:** None

### ft_isdigit

`int ft_isdigit(int c)`

- **Description:** Checks if a character is a digit (0 to 9)
- **Arguments:**
  - `c (int)`: An unsigned char to check
- **Return:** None zero if true (2048), zero if false
- **Requires:** None

### ft_isalnum

`int ft_isalnum(int c)`

- **Description:** Checks if a character is a digit or alphabetic (upper
  or lower)
- **Arguments:**
  - `c (int)`: An unsigned char to check
- **Return:** None zero if true (8), zero if false
- **Requires:** `libft::(ft_isalpha, ft_isdigit)`

### ft_isascii

`int ft_isascii(int c)`

- **Description:** Checks if a character is a 7-bit unsigned char ASCII
  character set (0 to 127)
- **Arguments:**
  - `c (int)`: An unsigned char to check
- **Return:** None zero if true (1), zero if false
- **Requires:** None

### ft_isprint

`int ft_isprint(int c)`

- **Description:** Checks if a character is printable (32 to 126)
- **Arguments:**
  - `c (int)`: An unsigned char to check
- **Return:** None zero if true (16384), zero if false
- **Requires:** None

### ft_strlen

`size_t ft_strlen(const char *s)`

- **Description:** Calculate the length of a string, excluding ‘\0’
- **Arguments:**
  - `s (const char *)`: String to calculate the length
- **Return:** (`size_t`). Length of the string
- **Requires:** None (`const stddef::size_t`)

### ft_memset

`void *ft_memset(void *s, int c, size_t n)`

- **Description:** Fills the first `n` bytes of the pointer `s` with the
  constant byte `c`. The `n` bytes of the memory need to be accessible
- **Arguments:**
  - `s (void *)`: Pointer to memory
  - `c (int)`: Constant byte
  - `n (size_t)`: Number of bytes to fill
- **Return:** (`Void`) Original pointer `s` filled
- **Requires:** None (`const stddef::size_t`)

### ft_bzero

`void ft_bzero(void *s, size_t n)`

- **Description:** Fills the first `n` bytes of the pointer `s` with the
  character ‘\0’
- **Arguments:**
  - `s (void *)`: Pointer to memory
  - `n (size_t)`: Number of bytes to fill
- **Return:** (`Void`). It will modify s
- **Requires:** `libft::ft_memset` (`const stddef::size_t`)

### ft_memcpy

`void *ft_memcpy(void *dest, const void *src, size_t n)`

- **Description:** Copies `n` bytes from the pointer `src` to the
  pointer `dest`. **Can** fail if memory `src` and `dest` overlap.
- **Arguments:**
  - `dest (void *)`: Pointer to memory destination
  - `src (void *)`: Pointer to memory source bytes
  - `n (size_t)`: Number of bytes to copy
- **Return:** (`Void`) It will modify `dest`
- **Requires:** None (`const stddef::size_t`)

### ft_memmove

`void *ft_memmove(void *dest, const void *src, size_t n)`

- **Description:** Copies `n` bytes from the pointer `src` to the
  pointer `dest`. **Can’t** fail if memory `src` and `dest` overlap.
- **Arguments:**
  - `dest (void *)`: Pointer to memory destination
  - `src (void *)`: Pointer to memory source bytes
  - `n (size_t)`: Number of bytes to copy
- **Return:** (`Void`) It will modify `dest`
- **Requires:** None (`const stddef::size_t`)

### ft_strlcpy

`size_t ft_strlcpy(char *dst, const char *src, size_t size)`

- **Description:** Copies `size - 1` bytes from the string `src` to the
  string `dst`, and `NULL` terminate (‘\0’) the result. User needs to
  allocate at least `size` bytes of memory in `dst`
- **Arguments:**
  - `dest (void *)`: Character string destination
  - `src (void *)`: Character string source
  - `size (size_t)`: Number of characters to copy from `src + 1`
- **Return:** (`size_t`) Length of `src`. It will modify `dest`
- **Requires:** None (`const stddef::size_t`)

### ft_strlcat

`size_t ft_strlcat(char *dst, const char *src, size_t size)`

- **Description:** Appends `size - strlen(dst) - 1` bytes from the
  string `src` at the end of the string `dst`, and `NULL` terminate the
  result. User needs to allocate at least `size` bytes of memory in
  `dst`
- **Arguments:**
  - `dest (void *)`: Character string destination
  - `src (void *)`: Character string source
  - `size (size_t)`: Number of characters to copy from `src + 1`
- **Return:** (`size_t`) Length of `src + dst`. If size is too short,
  returns `size + dst`
- **Requires:** `libft::ft_strlcpy` (`const libft::size_t`)

### ft_toupper

`int ft_toupper(int c)`

- **Description:** If `c` is lowercase, it returns the uppercase match.
  Else returns `c`
- **Arguments:**
  - `c (int)`: Character
- **Return:** (`int`) Character transformed if necessary
- **Requires:** None

### ft_tolower

`int ft_tolower(int c)`

- **Description:** If `c` is uppercase, it returns the lowercase match.
  Else returns `c`
- **Arguments:**
  - `c (int)`: Character
- **Return:** (`int`) Character transformed if necessary
- **Requires:** None

### ft_strchr

`char *ft_strchr(const char *s, int c)`

- **Description:** Search the first occurrence of the character `c` in
  the string `s`. The null byte is considered part of the string
- **Arguments:**
  - `s (const char *)`: String to search
  - `c (int)`: Character to find
- **Return:** (`char *`) Pointer to the match character, or `NULL` if
  not found
- **Requires:** None

### ft_strrchr

`char *ft_strrchr(const char *s, int c)`

- **Description:** Search the last occurrence of the character `c` in
  the string `s`. The null byte is considered part of the string
- **Arguments:**
  - `s (const char *)`: String to search
  - `c (int)`: Character to find
- **Return:** (`char *`) Pointer to the matching character, or `NULL` if
  not found
- **Requires:** None

### ft_strncmp

`int ft_strncmp(const char *s1, const char *s2, size_t n)`

- **Description:** Compares the first `n` characters from `s1` and `s2`
  strings
- **Arguments:**
  - `s1 (const char *)`: String 1
  - `s2 (const char *)`: String 2
  - `n (size_t)`: Number of characters to compare
- **Return:** (`int`) 0 means a match, else a difference, can be
  positive or negative
- **Requires:** None (`const stddef::size_t`)

### ft_memchr

`void *ft_memchr(const void *s, int c, size_t n)`

- **Description:** Scans the initial `n` bytes of the pointer `s`,
  looking for the byte `c`
- **Arguments:**
  - `s (const char *)`: Pointer to search
  - `c (int)`: Byte to find
  - `n (size_t)`: Number of bytes to scan
- **Return:** (`void *`) Pointer to the matching byte, or `NULL` if not
  found
- **Requires:** None (`const stddef::size_t`)

### ft_memcmp

`int ft_memcmp(const void *s1, const void *s2, size_t n)`

- **Description:** Compares the first `n` bytes between `s1` and `s2`
  (interpreted as unsigned char)
- **Arguments:**
  - `s1 (const char *)`: Pointer 1
  - `s2 (const char *)`: Pointer 2
  - `n (size_t)`: Number of bytes to compare
- **Return:** (`int`) 0 means a match, else a difference, can be
  positive or negative
- **Requires:** None (`const stddef::size_t`)

### ft_strnstr

`char *ft_strnstr(const char *big, const char *little, size_t len)`

- **Description:** Scans the first `len` characters of string `big` for
  the string `little`
- **Arguments:**
  - `big (const char *)`: String to search to
  - `little (const char *)`: String to find
  - `len (size_t)`: Number of characters to search
- **Return:** (`char *`) If match, a pointer to the first occurrence is
  returned. If not, `NULL`. If little is an empty string, returns `big`
- **Requires:** None (`const stddef::size_t`)

### ft_atoi

`int ft_atoi(const char *nptr)`

- **Description:** Converts the initial part of the string `nptr` to an
  int. It ignores the spaces at the start an accepts one sign (+ or -)
- **Arguments:**
  - `nptr (const char *)`: Initial string
- **Return:** `(int)` Converted value or 0 on error
- **Requires:** None

### ft_calloc

`void *ft_calloc(size_t nmemb, size_t size)`

- **Description:** Allocates memory for an array of `nmemb` of `size`
  bytes, and set the memory to 0 (‘\0’). It will detect multiplication
  overflows, returning `NULL`
- **Arguments:**
  - `nmemb (size_t)`: Number of elements to allocate
  - `size (size_t)`: Number of bytes per element
- **Return:** `(void *)` Pointer to the allocated memory, or `NULL` if
  error or `size`/`nmemb` are 0
- **Requires:** `stdlib::malloc`, `libft::ft_bzero`
  (`const libft::size_t`, `limits::ULLONG_MAX`, `limits::NULL`)

### ft_strdup

`char *ft_strdup(const char *s)`

- **Description:** Duplicates `s`
- **Arguments:**
  - `s (const char *)`: String to duplicate
- **Return:** `(char *)` New allocated string. `NULL` if fails.
- **Requires:** `stdlib::malloc`, `libft::ft_strlen`
  (`const libft::size_t`)

## 2.2 Additional functions

### ft_substr

`char *ft_substr(char const *s, unsigned int start, size_t len)`

- **Description:** Calculates a string from string `s`, starting from
  the idx `start` and max length `len`
- **Arguments:**
  - `s (char const *)`: Starting string
  - `start (unsigned int)`: Starting index
  - `len (size_t)`: Max substring length
- **Return:** (`char *`) New allocated substring, NULL if memory
  allocation fails
- **Requires:** `stdlib::malloc`, `libft::(ft_strlen, ft_strlcpy)`
  (`const libft::size_t`)

### ft_strjoin

`char *ft_strjoin(char const *s1, char const *s2)`

- **Description:** Paste together strings `s1` and `s2`, creating a new
  string
- **Arguments:**
  - `s1 (char const *) s1`: First string
  - `s2 (char const *) s2`: Second string
- **Return:** (`char *`) New allocated string, NULL if memory allocation
  fails
- **Requires:** `stdlib::malloc`,
  `libft::(ft_strlen, ft_strlcpy, ft_strlcat)` (`const libft::size_t`)

### ft_strtrim

`char *ft_strtrim(char const *s1, char const *set)`

- **Description:** Trim `s1`, deleting characters from start and end of
  `s1` if they match any character from `set`, until finding a non `set`
  character
- **Arguments:**
  - `s1 (char const *)`: String to scan
  - `set (char const *)`: Set of trimable characters
- **Return:** (`char *`) New allocated string, NULL if memory allocation
  fails
- **Requires:** `stdlib::malloc`,
  `libft::(ft_strchr, ft_strlen, ft_strlcpy)` (`const libft::size_t`)

### ft_split

`char **ft_split(char const *s, char c)`

- **Description:** Creates an array of strings, splitting the string `s`
  in substrings using the character `c` as separator. The array ends
  with a `NULL` pointer
- **Arguments:**
  - `s (char const *)`: String to split
  - `c (char)`: Delimiter character
- **Return:** (`char **`) Allocated array of strings, `NULL` if any
  allocation fails
- **Requires:** `stdlib::(malloc, free)`, `libft::ft_substr`
  (`const libft::size_t`)

### ft_itoa

`char *ft_itoa(int n)`

- **Description:** Create a string from an int
- **Arguments:**
  - `n (int)`: Number to transform
- **Return:** (`char *`) Allocated string, `NULL` if allocation fails
- **Requires:** `stdlib::malloc`

### ft_strmapi

`char *ft_strmapi(char const *s, char (*f)(unsigned int, char))`

- **Description:** Apply a function that process every char of a string
  `s`, transforming it (`s` doesn’t change) and returning a new string
- **Arguments:**
  - `s (char const *)`: String to transform
  - `char (*f) (unsigned int, char)`: Function to apply. The first
    argument of `f` needs to be an idx of the string, and the second the
    character of the string. Returns a character
- **Return:** (`char *`) Allocated string, NULL if memory allocation
  fails
- **Requires:** `stdlib::malloc`

### ft_striteri

`void ft_striteri(char *s, void (*f)(unsigned int, char*))`

- **Description:** Apply a function that process every char of a string
  `s`, transforming it (`s` does change)
- **Arguments:**
  - `s (char *)`: String to transform
  - `void (*f) (unsigned int, char *)`: Function to apply. The first
    argument of `f` needs to be an idx of the string, and the second a
    pointer to a character, that the function will modify
- **Return:** (`void`) String `s` will be modified
- **Requires:** None

### ft_putchar_fd

`int ft_putchar_fd(char c, int fd)`

- **Description:** Send `c` to a file descriptor (1 == shell)
- **Arguments:**
  - `c (char)`: Character to send/print
  - `fd (int)`: File descriptor to write
- **Return:** (`int`) It returns 1 if the operation was successful, 0
  otherwise
- **Requires:** `unistd::write`

### ft_putstr_fd

`int ft_putstr_fd(char *s, int fd)`

- **Description:** Send string `s` to a file descriptor (1 == shell)
- **Arguments:**
  - `s (char *)`: String to send/print
  - `fd (int)`: File descriptor to write
- **Return:** (`int`) It returns 1 if the operation was successful, 0
  otherwise
- **Requires:** `libft::ft_putchar_fd` (`unistd::write`)

### ft_putendl_fd

`int ft_putendl_fd(char *s, int fd)`

- **Description:** Send string `s` and `'\n'` to a file descriptor (1 ==
  shell)
- **Arguments:**
  - `s (char *)`: String to send/print
  - `fd (int)`: File descriptor to write
- **Return:** (`int`) It returns 1 if the operation was successful, 0
  otherwise
- **Requires:** `libft::ft_putendl_fd` (`unistd::write`)

### ft_putnbr_fd

`int ft_putnbr_fd(int n, int fd)`

- **Description:** Send the number `n` to a file descriptor (1 == shell)
- **Arguments:**
  - `n (int)`: Number to send
  - `fd (int)`: File descriptor to write
- **Return:** (`int`) It returns 1 if the operation was successful, 0
  otherwise
- **Requires:** `libft::ft_putchar_fd` (`unistd::write`)

### ft_printf

`int ft_printf(char const *str, ...)`

- **Description:** Prints an output in console, according to a format
  (%iducspxX%). Can use flags (width, space, .0-+#). More info in
  [ft_print repo](https://github.com/cesc1/42_ft_printf)
- **Arguments:**
  - `str (char const *)`: String to print
  - `...`: Extra arguments, if using formatting
- **Return:** (`int`): Number of characters printed. -1 if fails
- **Requires:**
  - `stdlib::(malloc, free)`
  - `stdarg(va_start, va_arg, va_copy, va_end)`
  - `libft::(ft_strchr, ft_strlen, ft_strlcpy, ft_putchar_fd, ft_putstr_fd, ft_isdigit, ft_atoi, ft_itoa, ft_substr, ft_strdup)`

### get_next_line

`char *get_next_line(int fd)`

- **Description:** Reads a line from a file descriptor, returning this
  line as a malloc alloated string. The user needs to keep reading the
  file until the end, and needs to handle the memory of the return value
  (free when necessary).
- **Arguments:**
  - `fd (int)`: File descriptor to read. It needs to be opened to read.
- **Return:** `(char *)`: String allocated with malloc.
- **Requires:**
  - `stdlib::(malloc, free, NULL, size_t)`
  - `unistd::read`
  - `sys/types::(ssize_t)`

## 2.3 List functions

Check type `t_list` in [libft.h](libft.h)

### ft_lstnew

`t_list *ft_lstnew(void *content)`

- **Description:** Allocates the first node of the list, initializing
  the content and the next pointer is `NULL`
- **Arguments:**
  - `content (void *)`: The content of the node
- **Return:** A pointer to the new list (node)
- **Requires:** `stdlib::malloc`, `libft::t_list` (`const libft::NULL`)

### ft_lstadd_front

`void ft_lstadd_front(t_list **lst, t_list *new)`

- **Description:** Add the node `new` at the start of `lst`
- **Arguments:**
  - `lst (t_list **)`: Double pointer to the first node of the list
  - `new (t_list *)`: Pointer to a node to add at the start of `lst`
- **Return:** (`void`)
- **Requires:** `libft::t_list`

### ft_lstsize

`int ft_lstsize(t_list *lst)`

- **Description:** Count the number of nodes of a list
- **Arguments:**
  - \``lst (t_list *)`: Pointer to the start of the list
- **Return:** (`int`) Number of nodes of the list
- **Requires:** `libft::t_list`

### ft_lstlast

`t_list *ft_lstlast(t_list *lst)`

- **Description:** Returns the last node of a list
- **Arguments:**
  - `lst (t_list *)`: The first node of the list
- **Return:** (`t_list *`) Last node of the list
- **Requires:** `libft::t_list`

### ft_lstadd_back

`void ft_lstadd_back(t_list **lst, t_list *new)`

- **Description:** Add the node `new` at the end of `lst`
- **Arguments:**
  - `lst (t_list **)`: Double pointer to the first node of the list
  - `new (t_list *)`: Pointer to a node to add at the end of `lst`
- **Return:** (`void`)
- **Requires:** `libft::t_list`

### ft_lstdelone

`void ft_lstdelone(t_list *lst, void (*del)(void *))`

- **Description:** Deletes a node from a list, freeing the memory
  allocated using the function `del` (contents) and `stdlib::free`
- **Arguments:**
  - `lst (t_list *)`: Pointer to the first node of the list
  - `void (*del)(void *)`: Function to delete the contents of the
    pointer
- **Return:** (`void`)
- **Requires:** `stdlib::free`, `libft::t_list`

### ft_lstclear

`void ft_lstclear(t_list **lst, void (*del)(void *))`

- **Description:** Deletes the given node `lst` and the next ones,
  freeing the memory allocated using the function `del` (contents) and
  `stdlib::free`
- **Arguments:**
  - `lst (t_list **)`: Double pointer to the start of the list
  - `void (*del)(void *)`: Function to delete the contents of the
    pointer
- **Return:** (`void`)
- **Requires:** `stdlib::free`, `libft::t_list`

### ft_lstiter

`void ft_lstiter(t_list *lst, void (*f)(void *))`

- **Description:** Apply the function `f` through the contents of every
  node of `lst`
- **Arguments:**
  - `lst (t_list *)`: List to iterate
  - `void (*f)(void *)`: Function to apply to the contents of the nodes
- **Return:** (`void`)
- **Requires:** `libft::t_list`

### ft_lstmap

`t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))`

- **Description:** Apply the function `f` through the contents of every
  node of `lst`, allocating a new list
- **Arguments:**
  - `lst (t_list *)`: List to iterate
  - `void *(*f)(void *)`: Function to apply to the contents of the nodes
  - `void (*del)(void *)`: Function to apply if something fails, to
    delete the list that we’re constructing
- **Return:** (`t_list *`): List with the applied transformation. NULL
  if fails
- **Requires:**
  `libft::(t_list, ft_lstnew, ft_lstclear, ft_lstadd_back)`
  (`stdlib::(malloc, free)`)
