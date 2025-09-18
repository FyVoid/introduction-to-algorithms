# Introduction to Algorithms Implementation

This is implementation of algorithms in book *Introduction to Algorithms* in c++23 and python. 

# Contents

## The Basics

### Notations

* $\Theta$
* O
* $\Omega$

### Recursion

* Substitution method
* Recursion-tree method
* Master theorem
    Let $a \ge 1$ and $b \gt 1$ be constants, let $f(n)$ be a function, and let $T(n)$ be defined on the nonnegative integers by the recurrence $T(n) = aT(n/b) + f(n)$;
    where we interpret $n/b$ to mean either $\left \lfloor n/b \right \rfloor$ or $\left \lceil n/b \right \rceil$. Then $T(n)$ has the follow-ing asymptotic bounds:
    1. If $f(n) = O(n^{log_b a-\epsilon})$ for some constant $\epsilon > 0$, then $T(n) = nlog_b a$.
    2. If $f(n) = \Theta(n^{log_b^{a}})$, then $T(n) = n^{log_b a} lg(n)$.
    3. If $f(n) = \Omega(n^{log_b a + \epsilon}) $ for some constant $\epsilon > 0$, and if $af(n/b) \le cf(n)$ for some constant $c \lt 1$ and all sufficiently large $n$, then $T(n) = \Theta(f(n))$.

## Sorting

### Insertion Sort & Bubble Sort

### Merge Sort

### Heap Sort and Priority Queue

### Quick Sort (and its random version!)

### Counting Sort

### Radix Sort (and how it's implemented parallelly)

### Bucket Sort

## Order Statistics

Select ith smallest/largest element

### Selection with random partiion

### BFPRT (Median of Medians)

## Data Structures

This project will NOT include implementations of data structures used in the book (since the cpp standard library already has all data structures we need).

### Linear List, Stack, Queue and Linked List

### Hash Table

Notice concepts like universal hashing, open addressing(probing) and perfect hash(FKS Scheme)

### Binary Search Tree

Notice predecessor and successor of the tree. Deleting a node from the tree is a bit sophiscated

### Red Black Tree

### Order Statistic Tree and Interval Tree