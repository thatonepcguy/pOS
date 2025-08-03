> This document is part of raspix and is licensed under the GNU General Public License v3.0 and later
> See the LICENSE file for details.

# raspix v0.1.0-alpha Syscall Documentation - Unfinished

## Syscall 0x000:

```c
int sys_open(const char *path_name, uint32_t flags, uint32_t mode)
```

### Description:

Opens the file specified by path_name

### Parameters:

`const char *path_name` -- Path to the file to open

`uint32_t flags` -- Flags to control how the file is opened

`uint32_t mode` -- File mode bits if a new file is created

### Return Value:

Returns a non-negative file descriptor on success, or a negative error code on failure

### Errors:

`E_INVALID_FLAG`

`E_NO_FILE`

`E_PERMISSION`

### Notes:

File descriptors are unique per process

Returns the first available fd starting from 0


## Syscall 0x001:

```c
int sys_close(int fd)
```

### Description:

Closes the file specified by the file descriptor (fd)

### Parameters:

`int fd` -- The file descriptor of the file to close

### Return Value:

Returns a 0 on success, or a negative error code on failure

### Errors:

`E_INVALID_FD`

### Notes:

File descriptors are unique per process

Makes the specified fd no longer valid



## Syscall 0x002:

```c
ssize_t sys_read(int fd, void *buf, size_t count)
```

### Description:

Reads `count` number of bytes from a file specified by `fd` and copies them into a buffer starting at `buf`

### Parameters:

`int fd` -- The file descriptor of the file to read from

`void *buf` -- A pointer to the start of the buffer

`size_t count` -- Specifies the number of bytes to read

### Return Value:

Returns a number greater than 0 specifing the number of bytes read on a success or returns a negative error code on failure

### Errors:

`E_INVALID_FD`

`E_EOF`

### Notes:

File descriptors are unique per process

If the end of the file is encountered before the read is finished, the function returns the number of bytes read up to that point, or an error if there are no more bytes to read



## Syscall 0x003:

```c
ssize_t sys_write(int fd, void *buf, size_t count)
```

### Description:

Writes `count` number of bytes to a file specified by `fd` copying them from a buffer starting at `buf`

### Parameters:

`int fd` -- The file descriptor of the file to write to

`void *buf` -- A pointer to the start of the buffer

`size_t count` -- Specifies the number of bytes to write

### Return Value:

Returns a number greater than 0 specifing the number of written on a success or returns a negative error code on failure

### Errors:

`E_INVALID_FD`

### Notes:

File descriptors are unique per process

If the end of the file is encountered before the write is finished,the function will extend the file the neccesary amount of bytes neccesary to write all of `buf`