#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
//#include "Heap.h"
//#include "StackQueue.h"
#include <string.h>

void my_InsertSort(int* a, int n);
void InsertSort(int* a, int n);
void ShellSort(int* a, int n);

void SelectSort(int* a, int n);

void BubbleSort(int* a, int n);

void QSort(int* a, int begin, int end);

void _MergeSort(int* a, int begin, int end, int* tmp);
void MergeSort(int* a, int n);
void MergeSortNonR(int* a, int n);

void CountSort(int* a, int n);

