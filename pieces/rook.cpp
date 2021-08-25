class Rook : public Piece {
private:
  bool hasMoved;
  Pixel** rookImage;

public:
  using Piece::Piece;

  Rook(bool clr, Square* s) {
    SetColor(clr);
    SetSquare(s);
    SetValue(5);
    SetType(ROOK);

    hasMoved = false;
  };
};
