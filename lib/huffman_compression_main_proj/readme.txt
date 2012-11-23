USAGE:
filename is argument one (argv[1])
output of the execution has been redirected to a file using redirection operator as 

mpirun -np 4 m in.txt > out.txt

in.txt is the input and the out , correspondingly the output


The program incorporates huffman encoding scheme. It is in the nature of huffman not to support text files of less varied ie., it does not do good for files with almost every characters around the same frequency. So , compression of file is a matter of input file selection . For the file v have attached in.txt the algorithm does compression.V have parallelised the code @ data level. yet there was  no appreciable speed up . The running time wer almost similar . V did also try incorporating arithmetic 
compression schemes but the float value corresponding to each string is exactly of the same length or even more than the string which made it less probable to be a choice of algorithm.

OPENMP :
 Frequency is calculated parallely
 Creation of Huffman tree nodes are done parallelly 
 And , binary to hex conversion of the file is done parallely taking into consideration the necessary Consistency conditions
 Speed up though not substatntial has been acheived
 
MPI:
 The input has been split and distributed to other processes and then frequency is calculated individually and the freq array is reduced using MPI_Reduce
 Similarly the bit array is split and sent to processees wer they are converted into hex and then recieved back in root and merged together to form the encoded array .
 
 system configuration :
 3GB RAM core 2 duo processor @ 1.83GHz.
 
 
 
  OPTIMISATIONS MADE :
1. input has been scanned directly from files instead of reading and parsing them.
2. use of register integers inside for loops
3. Integer and floating point declarations has been arranged to see if they cud fit into a block , thereby reducing cache-memory 	accesses. sadly it dint seem to be much of an advantage. (Hope the declarations ought to be substantial to feel the 		difference )
4. Memory reference to the array of strings has been reduced using temporary strings.
5. use of macros

TEAM MEMBERS :

Ravi Sankar R      - 20072189
Santhosh Kumar M L - 20072194
