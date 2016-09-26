/*
Rewrite our binary search algo to only use one test inside the loop. P. 58.
*/

#include <stdio.h>

/*Original*/
// int binsearch(int *sorted, int len, int target) {
//   int low, high, mid;
//
//   low = 0;
//   high = len - 1;
//
//   while (low <= high) {
//     mid = (low + high) / 2;
//
//     if (target > sorted[mid]) {
//       low = mid + 1;
//     } else if (target < sorted[mid]) {
//       high = mid - 1;
//     } else {
//       return mid;
//     }
//   }
//
//   return -1;
// }
//

/*Edited*/
int binsearch(int *sorted, int len, int target) {
  int low, high, mid;

  low = 0;
  high = len - 1;

  while (low < high) {
    mid = (low + high) / 2;

    if (target <= sorted[mid]) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }
  return target == sorted[high] ? high : -1;
}
