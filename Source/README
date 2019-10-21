# Huffman Tree Compression/Decompression
Developed by Jordan Kam and Kent Huang
Spring 2019 for CMPT 225

* Developed using c++ objected oriented programming, utilizing the Huffman tree algorithm to compress and decompress files

* Characters are read from a file and placed into leaf nodes based on its frequency of appearance. A Huffman tree is generated once all leaf nodeshave been created and linked. Encoding can be done by parsing through the Huffman tree recursively and generating a Huffman code (a binarycode) for each character

* Compression is performed by rewriting the strings from the original file but in its binary Huffman code, effectively saving space. The originalcharacters and frequencies are also written to the file for future decompression/decoding

* Decompression is performed by first decoding the characters. The Huffman tree is reconstructed by reading the list of characters and associatedfrequencies written previously from the compression step. Once reconstructed the Huffman tree is parsed and Huffman codes are generated again. The compressed file can now be read by parsing the Huffman tree and writing the associated character.

## Running the Code

This is the Huffman Tree compression/decompression algorithm. It was last tested and working on Linux, using g++ 
compiler and the included makefile.
Use the testdriver file to run the code.
In linux command terminal you can type:

```
"./huff -c filename.txt outputfilename" for compression

or 

"./huff -d filename.huff outputfilename.txt" for decompression
```
