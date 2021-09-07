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

  void GetLegalMoves(Coordinates* legalMoves, bool *succeeded) {
    if(HasCacheForTurn(boardG -> GetTurn())) {
      GetLegalMovesCache(legalMoves, succeeded);
      return;
    }

    Coordinates currentRow = GetSquare() -> GetPosition();

    Coordinates all[8];

    all[0] = currentRow.MakeNewCoordinatesAdd(-1,2); // Up left
    all[1] = currentRow.MakeNewCoordinatesAdd(1,2); // Up right

    all[2] = currentRow.MakeNewCoordinatesAdd(2,1); // Right up
    all[3] = currentRow.MakeNewCoordinatesAdd(2,-1); // Right down

    all[4] = currentRow.MakeNewCoordinatesAdd(1,-2); // Down right
    all[5] = currentRow.MakeNewCoordinatesAdd(-1,-2); // Down left

    all[6] = currentRow.MakeNewCoordinatesAdd(-2,-1); // left down
    all[7] = currentRow.MakeNewCoordinatesAdd(-2,1); // Left right

    for(int i = 0; i < 8; i++) {
      if(!all[i].IsInBounds(0,0,8,8)) continue;

      Square* sq = boardG -> GetSquareFromCoordBoard(all[i]);

      if(!sq -> HasPiece()) {
        legalMoves[i] = all[i];
        succeeded[i] = true;

        continue;
      }

      if(sq -> GetPiece() -> GetColor() != GetColor()){
        legalMoves[i] = all[i];
        succeeded[i] = true;

        continue;
      }
    }

    SetLegalMovesCache(legalMoves, succeeded, boardG -> GetTurn());
  }
};
