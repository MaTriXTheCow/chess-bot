Piece* Piece::MakePieceFromChar(char pieceChar, bool colorPiece, Square* sq) {
  switch(pieceChar) {
    case 'P': {
      return new Pawn(colorPiece, sq);
    } break;

    case 'R': {
      return new Rook(colorPiece, sq);
    } break;

    case 'B': {
      return new Bishop(colorPiece, sq);
    } break;

    case 'N': {
      return new Knight(colorPiece, sq);
    } break;

    case 'K': {
      return new King(colorPiece, sq);
    } break;

    case 'Q': {
      return new Queen(colorPiece, sq);
    } break;
  }

  return NULL;
}

int Piece::GetMaxMovesLength(pieceType p) {
  if(p == PAWN) return 4;
  if(p == KNIGHT) return 8;
  if(p == KING) return 10;
  if(p == ROOK) return 14;
  if(p == BISHOP) return 14;
  if(p == QUEEN) return 28;

  return -1;
}

void Piece::ToggleHighlightLegal() {
  Coordinates* movesList = (Coordinates*) malloc(maxMoveLen * sizeof(Coordinates));
  bool* movesSucceeded = (bool*) malloc(maxMoveLen * sizeof(bool));

  for(int i = 0; i < maxMoveLen; i++) {
    movesSucceeded[i] = false;
  }

  GetLegalMoves(movesList, movesSucceeded);

  for(int i = 0; i < maxMoveLen; i++) {
    if(!movesSucceeded[i]) continue;

    std::cout << "Moves: " << "\n";
    std::cout << movesList[i].x << " " << movesList[i].y << "\n";

    boardG -> GetSquareFromCoordBoard(movesList[i]) -> ToggleColor();
  }

  free(movesList);
  free(movesSucceeded);
}
