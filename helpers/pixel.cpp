struct Pixel {
    int r;
    int g;
    int b;
};

bool IsTransparent(int r, int g, int b) {
  return (r >= 100 && r <= 255 && g <= 30 && b >= 100 && b <= 255);
};
