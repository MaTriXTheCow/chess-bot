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

  Coordinates* GetLegalMoves() {
    Coordinates currentRow = GetSquare() -> GetPosition();

    Coordinates legalMoves[14];

    bool directions[4] = {false};
    int step = 0;

    while(!(directions[0] && directions[1] && directions[2] && directions[3])) {
      for(int i = 0; i < 4; i++) {
        if(directions[i]) continue;

        Coordinates checkPos = currentRow.MakeNewCoordinatesAdd((i%2) * (2-i), ((i+1)%2) * (i-1));

        if(!checkPos.IsInBounds(0,0,8,8)) {
          directions[i] = true;
          continue;
        }

        Square* checkSq = boardG -> GetSquare(checkPos.x, checkPos.y);

        if(!checkSq -> HasPiece()) {
          legalMoves[step + i] = checkPos;
          continue;
        }

        if(checkSq -> HasPiece()) {
          Piece* p = checkSq -> GetPiece();

          if((p -> GetColor()) == GetColor()) {
            directions[i] = true;
          } else {
            legalMoves[step+i] = checkPos;
            directions[i] = true;
          }
        }
      }

      step++;
    }

    return legalMoves;
  }
};
