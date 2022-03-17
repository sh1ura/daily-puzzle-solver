#define FX 7
#define FY 7

typedef struct {
  int p[FY][FX]; // pattern
  int x, y; // effective size of the pattern
} Field;

#define BL 99
Field map = {
  {
    { -1, -2, -3, -4, -5, -6, BL },
    { -7, -8, -9,-10,-11,-12, BL },
    {  1,  2,  3,  4,  5,  6,  7 },
    {  8,  9, 10, 11, 12, 13, 14 },
    { 15, 16, 17, 18, 19, 20, 21 },
    { 22, 23, 24, 25, 26, 27, 28 },
    { 29, 30, 31, BL, BL, BL, BL }
  }
};

Field field = { // pattern of empty field
  {
    { 0, 0, 0, 0, 0, 0, 1},
    { 0, 0, 0, 0, 0, 0, 1},
    { 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 1, 1, 1, 1}
  }
};

#define PN 8 // number of pieces
#define POSE 8 // maximum cases of pose (mirror + rotation)

Field piece[PN][POSE] = { // pattern of pieces
  {{{{1, 1, 1},
     {1, 1, 1}}}},
   
   {{{{0, 2, 2, 2},
      {2, 2, 0, 0}}}},

   {{{{3, 0, 0, 0},
      {3, 3, 3, 3}}}},

   {{{{4, 4, 4, 4},
      {0, 4, 0, 0}}}},

  {{{{5, 5, 5},
     {5, 0, 5}}}},

  {{{{6, 6, 6},
     {6, 0, 0},
     {6, 0, 0}}}},

   {{{{0, 7, 7},
      {0, 7, 0},
      {7, 7, 0}}}},

   {{{{8, 8, 8},
      {0, 8, 8}}}},
};

int poseNum[PN] = {1, 1, 1, 1, 1, 1, 1, 1}; // effective number of poses

