#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "puzzlelib.c"

#define DEBUG 0
#define FIND_ALL_SOLUTION 0

// recursive search of placing pieces
int placeCheck(Field *f, int pn) {
  int x, y, pose, result = 0;

  if(pn == PN) {
    showField(*f);
    return 1;
  }
  for(pose = 0; pose < poseNum[pn]; pose++) {
    for(y = 0; y <= FY - piece[pn][pose].y; y++) {
      for(x = 0; x <= FX - piece[pn][pose].x; x++) {
	if(isPlaceable(f, &piece[pn][pose], x, y)) {
	  Field nf = *f;
	  doPlace(&nf, &piece[pn][pose], x, y);
	  result += placeCheck(&nf, pn + 1);
#if !FIND_ALL_SOLUTION
	  if(result) {
	    return 1;
	  }
#endif
	}
      }
    }
  }
  return result;
}

int main(int argc, char *argv[]) {
  int pn, i, month, date;
  Field field;

  initPuzzle();
  genPose(); // generate mirrored and rotated patterns of pieces

  if(argc == 3) {
    month = atoi(argv[1]);
    date = atoi(argv[2]);
    field = convMap(map, month, date);
    showField(field);
    i = placeCheck(&field, 0); // search
    printf("success no = %d\n", i);
  }
  else {
    int min_i = INT_MAX;
    for(month = 1; month <= 12; month++) {
      for(date = 1; date <= 31; date++) {
	field = convMap(map, month, date);
	printf("%d/%d\n", month, date);
	i = placeCheck(&field, 0); // search
	if(min_i > i) {
	  min_i = i;
	}
      }
    }
    printf("# of minimum solution is %d\n", min_i);
  }
  
  return 0;
}
