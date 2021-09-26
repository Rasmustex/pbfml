# Examples
This directory contains example bfml files. Below is listed what each file does:
## test.bfml
test.bfml marks up the 2 first letters as blue, bold, and font size 31, while the first letter is underlined. The rest of the letters are "normal".
## rainbowhello.bfml
This program shows the text "Hello, world!" in rainbow colours. This is achieved by incrementing each cell in such a way, that the colour bits for each character is correct. The deeper architecture behind this is discussed in the wiki.
![image](https://user-images.githubusercontent.com/71628935/134813010-56f72705-3dd9-4cdb-8fa0-b3a8704a2a7c.png)
Note the plain text on the first line. It is read as part of the BF program, but treated as a comment. Thus, it is not included in the output.
