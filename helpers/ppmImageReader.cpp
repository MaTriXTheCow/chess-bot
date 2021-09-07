class PPMImageReader {
private:
  std::map<std::string,Pixel**> cache;

public:
  PPMImageReader() {

  }

  Pixel** ReadImage(std::string path) {
    if(cache.count(path) != 0) {
      return cache[path];
    }

    int w = 80;
    int h = 80;

    Pixel** imageMap = new Pixel*[h];

    for(int i = 0; i < h; i++) {
      imageMap[i] = new Pixel[w];

      for(int j = 0; j < w; j++) {
        imageMap[i][j] = Pixel{0,0,0};
      }
    }

    FILE *fp;
    errno_t err = fopen_s(&fp, path.c_str(), "rb");
    if (err != 0) return imageMap;

    int row = 0;
    int col = 0;

    int nByte = 0;

    int c;
    do {
      c = getc(fp);
      //std::putchar(c);

      nByte++;
    } while (nByte < 13); // Thirteen bytes of info

    while(true) {
      int r = getc(fp);
      int g = getc(fp);
      int b = getc(fp);

      //std::cout << row << " " << col << " " << "rbg:" << r << " " << g << " " << b << "\n";

      imageMap[row][col].r = r;
      imageMap[row][col].g = g;
      imageMap[row][col].b = b;

      col++;

      if(col == 80) {
        row++;
        col %= 80;
      }

      if(row == 80) {
        break;
      }
    }

    fclose(fp);

    if(cache.count(path) == 0) {
      cache[path] = imageMap;
    }

	  return imageMap;
  }

};

PPMImageReader* reader;
