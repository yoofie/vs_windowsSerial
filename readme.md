# vs_windowsSerial: Visual Studio Windows Serial Example Project

This is a barebones Visual Studio C++ console application that uses the native Windows Serial API to print serial data to the console.

The purpose is to quickly copy this project, adjust serial parameters and print the serial data from your device to the Windows console.

From there, once you proven it works, you can integrate this C/C++ code to another project where you require serial.

## Motivation
I don't want to use .Net, C# or any other language. Just straight C/C++ please. I don't want to read your confusing tutorial. Just show me a bare bones basic project.

It was surprisingly hard to find a plain **simple** C/C++ example of reading serial data from Windows. Everything I could find on Google
was incomplete, simply didn't work or required too much reading and work to get running1. So here we are. Just the basics.

## How to use

1. Download this repo
2. Adjust settings in the source code to match your serial device. The settings are self-explantory.
3. Compile and build with Visual Studio (NOT Visual Studio Code, you need a toolchain for that!)

### Compatibilty

This little project was tested and working with Visual Studio 2019 on Windows 10 LTSC 2019.

### Notes

There are two buffers, one to hold the latest data from the Windows Serial buffer and one to old the old previous data. 
Without these two buffers, the console will spit out the same bytes over and over at very fast rate which you can't read fast enough as a human.
So the added code uses two buffers to compare new & old data and only prints **new** data if its different from what came before.
