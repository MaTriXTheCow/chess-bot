struct Coordinates {
  int x;
  int y;

  bool IsInBounds(int lowerX, int lowerY, int upperX, int upperY) {
    return (x < upperX && y < upperY) && (x >= lowerX && x >= lowerY);
  }

  bool operator==(Coordinates a) {
    return a.x == x && a.y == y;
  }

  Coordinates MakeNewCoordinatesAdd(int xa, int ya) {
    return Coordinates{x+xa,y+ya};
  }
};
