# Message-Box-BOF
This reporsitory hosts the code for a Havoc C2 BOF that displays a message box.

This code was created as part of [100 Days of Red Team](https://www.100daysofredteam.com/p/lets-write-a-beacon-object-file-for-havoc-c2-part-1)

## Compiling the BOF

- C: x86_64-w64-mingw32-gcc -c message-box.c -o message-box.o -w

## Loading the BOF
- Method 1: inline-execute /tmp/message-box.o (assuming that message-box.o is stored in the /tmp directory)
- Method 2: Load the Python script using Script Manager: Scripts → Script Manager → Load Script, navigate to the path where the Python script is stored, selecte it and press Open.

## Using the BOF
- Method 1: inline-execute /tmp/message-box.o (assuming that message-box.o is stored in the /tmp directory)
- Method 2: Type message-box in the beacon interactive prompt.
