# pbfml
## About 
Pbfml is a command line program that converts BFML documents to HTML.

### What is BFML?
BFML is a markup language based on BrainFuck with 36-bit unsigned cells.

It uses the resulting tape from a brainfuck program on the first line of the file, and applies different markup options to the plain text character that the cell corresponds to, depending on the value of the cell. These options include things like colour, font size and boldness. An example of a BFML program could be:

```
-[+256>.-] This should make all characters blue; This first line is a BF program and this text is a comment
Hello, world!
```
This document will result in this when converted to HTML:

![image](https://user-images.githubusercontent.com/71628935/134909103-85afd925-7c03-4445-aa27-d7a13f4410b3.png)

To understand more about how BFML works, [have a look at the wiki.](https://github.com/Rasmustex/pbfml/wiki/BFML)

## Usage
```sh
Usage: pbfml <filename> [OPTIONS]...\n

pbfml is a BFML to HTML transpiler.
It takes a BFML file as input, and outputs the converted file.
Running pbfml <filename> results in an output file called out.html.

Options:
  -h            show help
  -o <filename> output the resulting html file to <filename>
```

## Building/installing pbfml
Currently, pbfml is only tested on linux, but will probably work fine on MacOS.

There currently aren't any distributed binaries of pbfml, but you can build it from this github repo quite easily. For instructions on how to do so, see [building pbfml.](https://github.com/Rasmustex/pbfml/blob/main/BUILD.md)
