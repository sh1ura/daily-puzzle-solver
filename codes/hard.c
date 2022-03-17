#define FX 7
#define FY 7

typedef struct {
  int p[FY][FX]; // pattern
  int x, y; // effective size of the pattern
} Field;

#define BL 99
Field map = {
  {
    { 1,  2, -1,  0,  3,  4, -2 },
    { 5,  0,  6,  7,  0, -3,  8 },
    { 0,  9, -4, 10, 11, 12, 13 },
    {-5, 14,  0, -6, 15, 16, 17 },
    {18, 19, -7, 20, 21, 22, 23 },
    {24, -8, 25, -9, 26, 27,-10 },
    {28, 29,-11, 30,-12,  0, 31 }
  }
};


Field field = { // pattern of empty field
  {
    { 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0}
  }
};

#define PN 8 // number of pieces
#define POSE 8 // maximum cases of pose (mirror + rotation)

Field piece[PN][POSE] = { // pattern of pieces  
  {{{{1, 1, 1},
     {1, 1, 1},
     {1, 0, 0}}}},

  {{{{2, 2, 2},
     {0, 2, 2},
     {0, 0, 2}}}},

  {{{{3, 3, 3, 3},
     {0, 3, 0, 0},
     {0, 3, 0, 0}}}},

  {{{{4, 4, 4, 0},
     {0, 4, 4, 4}}}},

  {{{{5, 5, 5, 5},
     {5, 5, 0, 0}}}},

  {{{{6, 6, 6},
     {6, 6, 0},
     {0, 6, 0}}}},

  {{{{0, 7, 7, 7},
     {7, 7}}}},
  
  {{{{8, 8, 8, 8},
     {8, 0, 0, 0}}}},
};

int poseNum[PN] = {1, 1, 1, 1, 1, 1, 1, 1}; // effective number of poses

