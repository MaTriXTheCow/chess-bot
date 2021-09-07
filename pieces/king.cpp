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

  void GetLegalMoves(Coordinates* legalMoves, bool *succeeded) {
    if(HasCacheForTurn(boardG -> GetTurn())) {
      GetLegalMovesCache(legalMoves, succeeded);
      return;
    }

    Coordinates currentRow = GetSquare() -> GetPosition();

    Coordinates all[8];

    all[0] = currentRow.MakeNewCoordinatesAdd(1,-1); // Up left
    all[1] = currentRow.MakeNewCoordinatesAdd(1,0); // Up
    all[2] = currentRow.MakeNewCoordinatesAdd(1,1); // Right up

    all[3] = currentRow.MakeNewCoordinatesAdd(0,-1); // Left
    all[4] = currentRow.MakeNewCoordinatesAdd(0, 1); // Right

    all[5] = currentRow.MakeNewCoordinatesAdd(-1,-1); // Down left
    all[6] = currentRow.MakeNewCoordinatesAdd(-1, 0); // Down
    all[7] = currentRow.MakeNewCoordinatesAdd(-1, 1); // Down right

    std::cout << "Got here" << "\n";

    for(int i = 0; i < 8; i++) {
      succeeded[i] = false;

      std::cout << "Knight: " << i << " " << all[i].x << " " << all[i].y << "\n";

      if(!(all[i].IsInBounds(0,0,8,8))) continue;

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

    std::cout << "Got to before caching" << "\n";



    SetLegalMovesCache(legalMoves, succeeded, boardG -> GetTurn());
  }
};
