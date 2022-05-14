# known issues in OCKcore

## issues that are not issues

These are instances of behaviour that are _by design_. They deviate from the
POSIX specification, and as such, the programs are not compliant in a strict
sense.

### general

* Two-digit years __are not supported__. Everyone learned not to use them
  before and after the year 2000; they're ambiguous and outdated. Therefore,
  they are not supported in OCKcore to encourage good dating practices.
  If a program detects a two-digit year is being used, it will error and exit
  without doing anything.

### `dd`

* ASCII to EBCDIC conversion and vice versa is not supported. It's clear
  which one won out in the "charset wars". Using `conv=ascii`, `conv=ebcdic`,
  or `conv=ibm` will throw an error and stop processing.
