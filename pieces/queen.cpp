class Queen : public Piece {
private:
  Pixel** queenImage;

public:
  using Piece::Piece;

  Queen(bool clr, Square* s) {
    SetColor(clr);
    SetSquare(s);
    SetValue(9);
    SetType(QUEEN);
  };
};
