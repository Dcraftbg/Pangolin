# Pangolin

Pangolin is a Unix like microkernel written in C, primarily developed by [@Dcraftbg](https://github.com/Dcraftbg) and [@UnmappedStack](https://github.com/UnmappedStack).

## Usage

### Requirements

You'll need to make sure that your system has the following programs:

- Bash
- Make
- Coreutils & binutils
- GCC
- Git (even if you downloaded the repository through the GitHub website!)
- Qemu
- NASM assembler

Most of these should already be installed on almost all Linux distros.

You can install everything quickly with this line with Arch linux (or any other distro which uses Pacman):

```bash
sudo pacman -Sy git qemu-full nasm
```

I haven't used Debian lately or any other distros using apt, so I'm not sure about what that would require. Please feel free to open an issue if you have a list of packages to add with apt.

### Build & run

To build and run, simply run:

```bash
./build.sh
```
Which will automatically run the makefile and build the whole system, as well as run it in Qemu. It uses KVM, meaning that it may not run on a non-Linux environment without modification to the build script.

If you get an error message saying that permission to run `build.sh` is denied, try running `chmod +x build.sh` and run it again.

## License & contribution

Pangolin is mostly under the Mozilla Public License 2.0. See the [LICENSE](LICENSE) file in this repository for more information.

However, some parts of Pangolin are under the MIT license:
 - [Parts of the paging implementation](kernel/src/mem/page.c)
 - [The Plist allocator](kernel/src/mem/plist.c)

Additionally, Pangolin is open to contributions! The general guide to submitting a contribution is:

 - Open an issue explaining the problem and the solution that you want to implement.
 - Ask for permission to get assigned to it.
 - Once you've gotten permission, open a pull request which solves it.

The general code style is the following:

 - **Commit names** should be in the format: `[topic] message`, where `topic` is the general part of the project changed and `message` is a very short message describing the change. If there are multiple areas of the project changed, split them with `|`, like so: `[topic1|topic2] message`.
 - **Indentation** should be 4 *spaces*.
 - **Scopes** should be on the same line as the statement that references them. For example, this is preferred:
    ```C
    if (some_condition) {
        // do stuff
    }
    ```
    rather than this:
    ```C
    if (some_condition)
    {
        // do stuff
    }
    ```
 - **Casing** should be `snake_case` for variable names, typedefs and functions, `PascalCase` for structs and enums, and `CAPITAL` for non-function and non-type macros.
 - **Stars** are flexible, but preferred on the right side - so `char *msg = "hi";` should be used instead of `char* msg = "hi";`.
 - **Comments** should be used minimally within functions, but preferably before complex functions to explain the general concept of what it does. Comments within functions should generally not be needed if it's clear and well-written code with descriptive variable names.
