# libvrb-win

Partial port of the [original](https://linux.die.net/man/3/vrb) virtual ring buffer library.

## General information

Not all of the original type and functions are declared, however the ones that are try to ensure intercompatibility.

Offered as is, and probably needs a bit of testing.

## Getting started

The repository contains the necessary Eclipse CDT Project files for building the library with MinGW.

## Credits

The Windows implementation of a memory-mapped ring buffer has been discussed in the following threads:
 - https://stackoverflow.com/questions/1016888/windows-ring-buffer-without-copying
 - https://stackoverflow.com/questions/39984710/virtual-memory-ring-buffer-on-windows
 - https://blogs.msdn.microsoft.com/oldnewthing/20031007-00/
 - https://gist.github.com/rygorous/3158316

## License

This library is licensed under the [GNU Lesser General Public License v3.0](https://www.gnu.org/licenses/lgpl-3.0.en.html). For more information, please read the LICENSE file.
