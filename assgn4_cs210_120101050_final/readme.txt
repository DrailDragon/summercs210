i.This folder contains following files:
1.graph_using_adlist.c: This file contains implementation of graph-traversal algorithms dfs and bfs using adjasency-list.
2.graph_using_matrix.c: This file contains implementation of graph-traversal algorithms dfs and bfs using 2-d array matrix.
3.auxiliary.h: this file contains the function-definitions for stack and queue operations needed for bfs and dfs.
4.bst.c: This is the source file for the program to make a binary tree from given sequence of integers.For this we have taken an struct with two integers left and right to denote left and right child respectively.We virtually make binary search tree of the input array without copying its contents.
5.bst_using_selfreference.c:This is the source file for the program to make a binary tree from given sequence of integers.For this we have taken self referntial struct and also copying the contents of the array to construct the tree.
6.bst_input.txt: this is sample input file for both bst.c and bst_using_selfreference.c
7.graph_input.txt: this is sample input file for both graph_using_adlist.c and graph_using_matrix.c
Also corresponding sample output files are there along with this readme.txt. 

ii.To compile files 1 and 2(for graph) type in terminal "gcc [-o executablename] graph_using_x.c auxiliary.h"
and to run type "./a.out(or ./executablename) <graph_input.txt"(ignore this if you want to give input manually) 
where x is either adlist or matrix.

iii.To compile files 4 and 5 type "gcc [-o executablename] filename.c".
and to run type "./a.out(or ./executablename) <bst_input.txt(ignore this if you want to give input manually)"
where filename is either bst or bst_using_selfreference.
