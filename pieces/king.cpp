class King : public Piece {
private:
  bool canCastle;
  bool isChecked;
  Pixel** kingImage;

public:
  using Piece::Piece;

  King(bool clr, Square* s) {
    SetColor(clr);
    SetSquare(s);
    SetValue(100000000);
    SetType(KING);

    canCastle = false;
    isChecked = false;
  };
};
