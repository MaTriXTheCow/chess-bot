struct Coordinates {
  int x;
  int y;

  bool IsInBounds(int upperX, int upperY) {
    return (x < upperX && y < upperY);
  }

  bool operator==(Coordinates a) {
    return a.x == x && a.y == y;
  }

};
