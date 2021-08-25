class Knight : public Piece {
private:
  Pixel** knightImage;

public:
  using Piece::Piece;

  Knight(bool clr, Square* s) {
    SetColor(clr);
    SetSquare(s);
    SetValue(3);
    SetType(KNIGHT);

  };
};
