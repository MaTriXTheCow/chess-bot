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

    isClicked = false;

    color = (r%2 == c%2) ? blackSq : whiteSq;
  }

  Piece* GetPiece() {
    return piece;
    
  }

  int GetColor() {
    return color;
  }

  Coordinates GetPosition() {
    return Coordinates{row, column};
  }

  void SetPiece(Piece* p) {
    hasPiece = true;
    piece = p;
  }

  bool IsClicked() {
    return isClicked;
  }

  bool ToggleClicked() {
    std::cout << numberToLettter[column] << row+1 << "\n";
    if(IsClicked()) {
      isClicked = false;
      return true;
    }


    if(HasPiece()) isClicked = true;

    return HasPiece();
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
