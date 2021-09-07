class Piece;

class Square {
private:
  int row;
  int column;

  int color;
  int defaultColor;
  int toggleColor;

  Piece* piece;

  bool hasPiece;
  bool isClicked;

  bool isHighlighted;

public:
  Square(int r, int c) {
    row = r;
    column = c;

    hasPiece = false;
    isClicked = false;

    defaultColor = (r%2 == c%2) ? blackSq : whiteSq;
    toggleColor = (defaultColor == whiteSq) ? 0xf9f788 : 0xb7cb44;

    color = defaultColor;
  }

  Piece* GetPiece() {
    return piece;
  }

  int GetColor() {
    return color;
  }

  Coordinates GetPosition() {
    return Coordinates{column, row};
  }

  void SetPiece(Piece* p) {
    hasPiece = true;
    piece = p;
  }

  void ToggleColor() {
    color = (color == defaultColor) ? toggleColor : defaultColor;
  }

  bool IsClicked() {
    return isClicked;
  }

  bool ToggleClicked();

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
