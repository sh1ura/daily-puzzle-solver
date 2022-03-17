#include <stdio.h>

#include "puzzlelib.c"

#define DEBUG 1

#define MONTH 12
#define DATE 31
int check[MONTH][DATE] = {0};

void checkResult(Field *f) {
  int x, y;
  int cnt = 0;
  int month = -1, date = -1;
  
  for(y = 0; y < FY; y++) {
    for(x = 0; x < FX; x++) {
      if(f->p[y][x] == 0) {
	if(map.p[y][x] > 0) {
	  date = map.p[y][x];
	}
	else {
	  month = -map.p[y][x];
	}
      }
    }
  }
  if(month < 0 || date < 0) {
    return;
  } 
  check[month - 1][date - 1]++;
}

// recursive search of placing pieces
int placeCheck(Field *f, int pn) {
  int x, y, pose, result = 0;

  if(pn == PN) {
    checkResult(f);
    return 1;
  }
  for(pose = 0; pose < poseNum[pn]; pose++) {
    for(y = 0; y <= FY - piece[pn][pose].y; y++) {
      for(x = 0; x <= FX - piece[pn][pose].x; x++) {
#if DEBUG
      if(pn == 0) {
	printf("processing pose=%d y=%d x=%d\n", pose, y, x);
      }
#endif
	if(isPlaceable(f, &piece[pn][pose], x, y)) {
	  Field nf = *f;
	  doPlace(&nf, &piece[pn][pose], x, y);
	  result += placeCheck(&nf, pn + 1);
	}
      }
    }
  }
  return result;
}

int main(void) {
  int pn, i;
  Field f;

  genPose(); // generate mirrored and rotated patterns of pieces

  f = convMap(map, 0, 0); // do not place 1 anywhere
  showField(f);
  
  placeCheck(&f, 0); // search

  int month, date, minSol, sum = 0;
  minSol = check[0][0];
  for(month = 0; month < MONTH; month++) {
    for(date = 0; date < DATE; date++) {
      printf("%d/%d = %d\n", month + 1, date + 1, check[month][date]);
      sum += check[month][date];
      if(check[month][date] < minSol) {
	minSol = check[month][date]; // find the minimum soluction case
      }
    }
  }
  printf("# of total solution is %d\n", sum);
  printf("# of minimum solution is %d\n", minSol);
    
  return 0;
}
