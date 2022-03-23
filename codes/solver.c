#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "puzzlelib.c"

#define DEBUG 0
#define FIND_ALL_SOLUTIONS 0
#define SHOW_FIELD 1

typedef struct { // data structure for recursive search
  Field f; // current pattern of the field
  int used[PN]; // table of used pieces
} Sdata;

Sdata sd = {
  {{{0}}},
  {0}
};

// recursive search of placing pieces
int placeCheck(Sdata *sd, int pn) {
  int x, y, i, pose, result = 0;

#if DEBUG
  for(i = 0; i < PN; i++) {
    printf(" %d", sd->used[i]);
  }
  printf("\n");
  showField(sd->f);
#endif
  
  if(pn == PN) { // solution is found
#if SHOW_FIELD
    showField(sd->f);
#if FIND_ALL_SOLUTIONS
    printf("\n");
#endif
#endif
    return 1;
  }
  // find top-left empty cell
  for(y = 0; y < F_SIZE; y++) {
    for(x = 0; x < F_SIZE; x++) {
      if(sd->f.p[y][x] == 0) {
	goto OUT;
      }
    }
  }
 OUT:
  for(i = 0; i < PN; i++) {
    if(sd->used[i]) { // select unsed piece
      continue;
    }
    for(pose = 0; pose < poseNum[i]; pose++) {
      for(int py = 0; py < piece[i][pose].y; py++) {
	for(int px = 0; px < piece[i][pose].x; px++) {
	  int posx = x - px;
	  int posy = y - py;
	  if(posx < 0 || posy < 0 ||
	     posx + piece[i][pose].x > F_SIZE ||
	     posy + piece[i][pose].y > F_SIZE) {
	    continue; // piece is not in the field
	  }
	  if(piece[i][pose].p[py][px] <= 0) {
	    continue; // the piece must fill (y, x)
	  }
	  if(isPlaceable(&(sd->f), &piece[i][pose], posx, posy)) {
	    Sdata nsd = *sd;
	    nsd.used[i] = 1;
	    doPlace(&(nsd.f), &piece[i][pose], posx, posy);
	    result += placeCheck(&nsd, pn + 1);
#if !FIND_ALL_SOLUTIONS
	    if(result) {
	      return 1;
	    }
#endif
	  }
	}
      }
    }
  }
  return result;
}

int main(int argc, char *argv[]) {
  int pn, i, month, date;

  initPuzzle();
  genPose(); // generate mirrored and rotated patterns of pieces

  if(argc == 3) {
    month = atoi(argv[1]);
    date = atoi(argv[2]);
    sd.f = convMap(map, month, date);
    showField(sd.f);
    i = placeCheck(&sd, 0); // search
#if FIND_ALL_SOLUTIONS
    printf("Solution = %d\n", i);
#endif
  }
  else {
    int min_i = INT_MAX;
    for(month = 1; month <= 12; month++) {
      for(date = 1; date <= 31; date++) {
	sd.f = convMap(map, month, date);
	printf("%d/%d\n", month, date);
	i = placeCheck(&sd, 0); // search
#if FIND_ALL_SOLUTIONS
	printf("Solution = %d\n", i);
#endif
	if(min_i > i) {
	  min_i = i;
	}
      }
    }
    printf("# of minimum solution is %d\n", min_i);
  }
  
  return 0;
}
