typedef int SortType;

/**********************************************************/
/********************** Bubble Sort ***********************/
/**********************************************************/
void bubbleSort(SortType *begin, SortType *end, int (*cmp)(SortType *a, SortType *b)) {
  SortType temp;
  int flag = 1;
  for (SortType *i = begin; i != end - 1; i++) {
    for (SortType *j = begin; j != end - 1 - (i - begin); j++) {
      if (!cmp(j, j + 1)) {
        temp = *j;
        *j = *(j + 1);
        *(j + 1) = temp;
        flag = 0;
      }
    }
    if (flag) break;
    flag = 1;
  }
}
/**********************************************************/


/**********************************************************/
/********************** Quick Sort ************************/
/**********************************************************/
SortType* partitionFunc(SortType *begin, SortType *end, int (*cmp)(SortType *a, SortType *b)) {
  SortType *l = begin, *r = end - 1;
  SortType temp = *begin;
  while (l < r) {
    while(l < r && cmp(&temp, r)) r--;
    if (l < r) {
      *l = *r;
      l++;
    }
    while(l < r && cmp(l, &temp)) l++;
    if (l < r) {
      *r = *l;
      r--;
    }
  }
  *l = temp;
  return l;
}

void quickSort(SortType *begin, SortType *end, int (*cmp)(SortType *a, SortType *b)) {
  if (begin < end) {
    SortType *index = partitionFunc(begin, end, cmp);
    quickSort(begin, index, cmp);
    quickSort(index + 1, end, cmp);
  }
}
/**********************************************************/
