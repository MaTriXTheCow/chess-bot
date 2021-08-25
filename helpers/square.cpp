class Piece;

class Square {
private:
  int row;
  int column;

  int color;

  Piece* piece;

  bool hasPiece;
  bool isClicked;

public:
  Square(int r, int c) {
    row = r;
    column = c;

    hasPiece = false;

    color = (r%2 == c%2) ? whiteSq : blackSq;
  }

  Piece* GetPiece() {
    return piece;
  }

  int GetColor() {
    return color;
  }

  void SetPiece(Piece* p) {
    hasPiece = true;
    piece = p;
  }

  void SetClicked() {
    if(HasPiece()) isClicked = true;
  }

  bool HasPiece() {
    return hasPiece;
  }

  int GetTopLeftX(int x) {
    return x - column*80;
  }

  int GetTopLeftY(int y) {
    return y - row*80;
  }

  Coordinates GetRelative(Coordinates pos) {
    pos.x -= column*80;
    pos.y -= row * 80;

    return pos;
  }


};
