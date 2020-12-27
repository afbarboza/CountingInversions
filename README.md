### Counting Inversions - The Problem
Consider an array of unordered integers as below

![Input](./input.gif?raw=true)

An inversion in the given array A happens when some element bigger than the other comes first. Formally, is defined as:

![Inversion](./inv.gif?raw=true)
 
 The task is compute all the inversions in the array, which means to compute the number of times that some value `A[i]` comes first than `A[j]`, with `A[i] > A[j]`.
 
 ### The Naive Solution - Don't go brute force
 
 One could intuitively think in the following solution:
 
 ```
 inversions = 0
 for i = 0 to i < A.length {
    for j = i + 1 to j < A.length {
      if (A[i] > A[j]) {
          inversions = inversions + 1
      }
    }
 }
 ```
 
 Altough this solution is correct, it is not performatic at all - it is easy to see that the running time of this naive approach takes `O(n²)`, with n being the size of the input array.
 Any serious software developer should ask himself: can we do better? As a matter of fact, yes we can!
 
 ### Divide it and then conquer it
 
[Merge Sort](https://rosettacode.org/wiki/Sorting_algorithms/Merge_sort) is a famous algorithm that uses the divide-and-conquer approach to sort any given array in `O(n logn)` time. This algorithm splits (divide) the array into smaller pieces,
recursively sort the smaller pieces and then merge it back (conquer), returing the final sorted array. Since Merge Sort is a comparison sort based algorithm, we can make some changes to use it in our initial problem of counting inversions.

### The Merge Sort Algorithm
Let's remember of how Merge Sort is implemented in pseudocode. Some implementation details were left out just to grasp the general idea of how it works:

```
function merge(array, start, middle, end) {
  for (i = start; leftPointer <= middle && rightPointer <= end; i++) {
    if (array[leftPointer] <= array[rightPointer]) {
        tmpArray = array[leftPointer]
        leftPointer++
    } else {
        tmpArray = array[rightPointer]
        rightPointer++;
    }
  }
}

function mergeSort(array, start, end) {
  middle = (start + 2) / 2;
  if (star >= end) {
    return; // we reached the base case of our recursion. so we can go back
  }
  /* divide the array */
  mergeSort(array, start, middle) // sort the left half of the array
  mergeSort(array, middle + 1, end) // sort the right half of the array
  
  /* conquer it - merge the two sorted halves into one single sorted array */
  merge(array, start, middle, end)
}

```

### The a-ha moment (Eureka!)

The `merge` routine described above has to compare the elements and copy from  the original array in two different situations. The first is when the `array[leftPointer]` is smaller than the element `array[rightPointer]`. This is not a inversion because the elements in the left half comes first.
Nevertheless, each time the `else` clause is executed it means we found some element smaller ahead of some other element bigger, which is a inversion. So, in the follwing snippet of the pseudocode:
```
  tmpArray = array[rightPointer]
  rightPointer++;
```

we are placing the element in its rightful position. The number of inversions is simply the number of elements in the left half which has not yet been considered to merge.
