bool Square::ToggleClicked() {
  if(IsClicked()) {
    isClicked = false;

    ToggleColor();
    return true;
  }


  if(HasPiece() && ((boardG -> GetTurn() + 1)% 2 == (unsigned int)(GetPiece() -> GetColor()))) {
    ToggleColor();
    isClicked = true;

    return true;
  }

  return false;
}
