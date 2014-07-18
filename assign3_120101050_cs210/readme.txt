i.This folder contains seven c files:
contain hashtable implementation:-
1.chaining_hashing.c:- using bucketing.
2.coalesced_hashing.c:- with collision resolution as coalesced hashing using M1 slots for hash-indexing and 
M-M1 slots for cellar M-size table
3. double_hashing.c:- with collision resolution as double hashing.
4. linearhash.c:- with collision resolution by linear probing.
5. quadratic_hash.c:- with collision resolution by quadratic probing.
6. simple_hashing.c:- without collision resolution.
and to generate input for each program:-
7.generate_input.c:- this generates input_gen.txt file.To vary input-contents modify generate_input.c file.
ii.
1.To compile a .c file type in terminal gcc -o executable_name filename.c
2. To run the executable type in terminal ./executable_name <input_gen.txt
3. Sample output files are also given for existing input_gen.txt file.

