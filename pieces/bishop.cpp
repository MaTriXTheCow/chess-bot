class Bishop : public Piece {
private:
  Pixel** bishopImage;

public:
  using Piece::Piece;

  Bishop(bool clr, Square* s) {
    SetColor(clr);
    SetSquare(s);
    SetValue(3);
    SetType(BISHOP);

  };
};
