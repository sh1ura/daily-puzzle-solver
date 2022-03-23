#define F_SIZE 7
#define FX F_SIZE
#define FY F_SIZE
#define POSE 8 // maximum cases of pose (mirror + rotation)

typedef struct {
  int p[F_SIZE][F_SIZE]; // pattern
  int x, y; // effective size of the pattern
  unsigned long long int bitmap; // bitmap of the pattern for acceleration
} Field;

#define BL 99

// select the puzzle to solve
//#include "original.c"
#include "8p.c"
//#include "9p.c"
//#include "10p.c"
//#include "11p.c"

int poseNum[PN]; // effective number of poses
Field field = {{{0}}}; // pattern of empty field

void initPuzzle(void) {
  int i;
  Field f;
  
  if(sizeof(f.bitmap) < 8) {
    printf("unsigned long long int is shorter than 8.\n");
    exit(-1);
  }
  
  for(i = 0; i < PN; i++) {
    poseNum[i] = 1;
  }
}  

Field simpleRot(Field f) { // just rotate the pattern CCW 90deg
  Field nf;
  int x, y;
  
  for(y = 0; y < F_SIZE; y++) {
    for(x = 0; x < F_SIZE; x++) {
      nf.p[y][x] = f.p[x][F_SIZE - y - 1];
    }
  }
  return nf;
}

Field transpose(Field f) { // mirror
  Field nf;
  int x, y;
  
  for(y = 0; y < F_SIZE; y++) {
    for(x = 0; x < F_SIZE; x++) {
      nf.p[y][x] = f.p[x][y];
    }
  }
  return nf;
}		       

Field shiftUp(Field f) { // delete empty line
  int x, y, i;
  int sum;
  
  for(i = 0; i < F_SIZE; i++) {
    sum = 0;
    for(x = 0; x < F_SIZE; x++) {
      sum += f.p[0][x];
    }
    if(sum == 0) {
      for(y = 1; y < F_SIZE; y++) {
	for(x = 0; x < F_SIZE; x++) {
	  f.p[y-1][x] = f.p[y][x];
	}
      }
      for(x = 0; x < F_SIZE; x++) {
	f.p[F_SIZE-1][x] = 0;
      }
    }
  }
  return f;
}

Field shiftXY(Field f) { // shift the pattern to upper-left
  f = shiftUp(f);
  f = transpose(f);
  f = shiftUp(f);
  f = transpose(f);
  return f;
}

Field shiftRot(Field f) { // rotate and shift to upper-left
  return shiftXY(simpleRot(f));
}

void showField(Field f) { // show the field to the display
  int x, y;

  for(x = 0; x < F_SIZE; x++) {
    printf("--");
  }
  printf("\n");

  for(y = 0; y < F_SIZE; y++) {
    for(x = 0; x < F_SIZE; x++) {
      if(f.p[y][x] < 0) {
	printf(" *");
      }
      else if(f.p[y][x] == 0) {
	printf(" .");
      }
      else {
	printf(" %c", 'A' + f.p[y][x] - 1);
      }
    }
    printf("\n");
  }

  for(x = 0; x < F_SIZE; x++) {
    printf("--");
  }
  printf("\n");

}

int isSame(Field a, Field b) { // compare two patterns
  int x, y;

  for(y = 0; y < F_SIZE; y++) {
    for(x = 0; x < F_SIZE; x++) {
      if(a.p[y][x] != b.p[y][x]) {
	return 0;
      }
    }
  }
  return 1;
}

// generate bitmap. LSB is top-left.
void genBitmap(Field *f) {
  int x, y;

  f->bitmap = 0;
  for(y = 0; y < F_SIZE; y++) {
    for(x = 0; x < F_SIZE; x++) {
      if(f->p[y][x]) {
	f->bitmap |= ((unsigned long long int)1) << (y * F_SIZE + x);
      }
    }
  }
}

void genPose(void) { // generate rotated and mirrored patterns of pieces
  int pn, pose, i, j;
  Field f;
  
  for(pn = 0; pn < PN; pn++) {
    // generating rotated pattern
    f = piece[pn][0];
    for(i = 0; i < 4; i++) {
      f = shiftRot(f);
      for(j = 0; j < poseNum[pn]; j++) {
	if(isSame(piece[pn][j], f)) {
	  break; // delete redundant pattern
	}
      }
      if(j == poseNum[pn]) {
	piece[pn][j] = f;
	poseNum[pn]++;
      }
    }
    // generating mirrored and rotated pattern
    f = transpose(piece[pn][0]);
    for(i = 0; i < 4; i++) {
      f = shiftRot(f);
      for(j = 0; j < poseNum[pn]; j++) {
	if(isSame(piece[pn][j], f)) {
	  break; // delete redundant pattern
	}
      }
      if(j == poseNum[pn]) {
	piece[pn][j] = f;
	poseNum[pn]++;
      }
    }
  }
  // calculate the effective pattern size
  for(pn = 0; pn < PN; pn++) {
    for(pose = 0; pose < poseNum[pn]; pose++) {
      int x, y;

      piece[pn][pose].x = 0;
      piece[pn][pose].y = 0;
      for(y = 0; y < F_SIZE; y++) {
	for(x = 0; x < F_SIZE; x++) {
	  if(piece[pn][pose].p[y][x]) {
	    if(piece[pn][pose].x <= x) {
	      piece[pn][pose].x = x + 1;
	    }
	    if(piece[pn][pose].y <= y) {
	      piece[pn][pose].y = y + 1;
	    }
	  }
	}
      }
    }
  }      
  for(pn = 0; pn < PN; pn++) {
    for(pose = 0; pose < poseNum[pn]; pose++) {
      genBitmap(&piece[pn][pose]);
    }
  }
}

// check if the pattern is placeable at (sx, sy)
int isPlaceable(Field *f, Field *p, int sx, int sy) {
  if((p->bitmap << (sy * F_SIZE + sx)) & f->bitmap) { // collision
    return 0;
  }
  return 1;
}

// place the pattern at (sx, sy)
void doPlace(Field *f, Field *p, int sx, int sy) {
  int x, y;

  for(y = 0; y < p->y; y++) {
    for(x = 0; x < p->x; x++) {
      if(p->p[y][x]) {
	f->p[y + sy][x + sx] = p->p[y][x];
      }
    }
  }
  f->bitmap |= (p->bitmap << (sy * F_SIZE + sx));
}

// convert map to field. if month/date == 0, do not place 1
Field convMap(Field map, int month, int date) {
  int x, y;
  Field f;

  for(y = 0; y < F_SIZE; y++) {
    for(x = 0; x < F_SIZE; x++) {
      if(map.p[y][x] == BL) {
	f.p[y][x] = -1;
      }
      else if(month && map.p[y][x] == -month) {
	f.p[y][x] = -1;
      }
      else if(date && map.p[y][x] == date) {
	f.p[y][x] = -1;
      }
      else {
	f.p[y][x] = 0;
      }
    }
  }
  genBitmap(&f);
  return f;
}
	
