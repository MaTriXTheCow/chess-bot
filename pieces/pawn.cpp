class Pawn : public Piece {
private:
  bool isFirstMove;
  Pixel** pawnImage;

public:
  using Piece::Piece;

  Pawn(bool clr, Square* square) {
    SetColor(clr);
    SetSquare(square);
    SetValue(1);
    SetType(PAWN);

    isFirstMove = true;
  };

  Coordinates* GetLegalMoves() {

  }
};
