class InputReader {
  public:
	InputReader() {
	    in = stdin;
        cursor = 0;
        fread(buffer, 1, SIZE, in);
	}
    InputReader(const char *input_file) {
        in = fopen(input_file, "r");
        cursor = 0;
        fread(buffer, 1, SIZE, in);
    }
    template <typename T>
    InputReader& operator>>(T &nr) {
        while (!isdigit(buffer[cursor]))
            advance();
        nr = 0;
        while (isdigit(buffer[cursor])) {
            nr *= 10;
            nr += buffer[cursor] - '0';
            advance();
        }
        return (*this);
    }
  private:
    FILE *in;
    static const int SIZE = (1 << 17);
    char buffer[SIZE];
    int cursor;
    void advance() {
        ++ cursor;
        if (cursor == SIZE) {
            cursor = 0;
            fread(buffer, 1, SIZE, in);
        }
    }
};
 
class OutputWriter {
  public:
    OutputWriter() {
	    out = stdout;
        cursor = 0;
	}
    OutputWriter(const char *output_file) {
        out = fopen(output_file, "w");
        cursor = 0;
    }
    ~OutputWriter() { flush(); }
    OutputWriter& operator<<(int nr) {
        char digits[10];
        int cnt = 0;
        do {
            digits[cnt ++] = (nr % 10 + '0');
            nr /= 10;
        } while (nr);
        for (int i = cnt - 1; i >= 0; -- i)
            (*this) << digits[i];
        return (*this);
    }
    OutputWriter& operator<<(const char &ch) {
        if (cursor == SIZE)
            flush();
        buffer[cursor ++] = ch;
        return (*this);
    }
    void flush() {
        fwrite(buffer, 1, cursor, out);
        cursor = 0;
    }
  private:
    FILE *out;
    static const int SIZE = (1 << 17);
    char buffer[SIZE];
    int cursor;
};

