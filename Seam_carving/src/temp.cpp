 int ***rgb_ = new int**[H_];
    for (int i = 0; i < H_; i++) {
        rgb_[i] = new int*[W_];
        for (int j = 0; j < W_; j++) {
            rgb_[i][j] = new int[C_];
        }
    }
    for (int i = 0; i < H_; i++) {
        for (int j = 0; j < W_; j++) {
            for (int k = 0; k < C_; k++) {
                rgb_[i][j][k] = 0;
            }
        }
    }
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            for (int k = 0; k < C; k++) {
                rgb_[i][j][k] = rgb[i][j][k];
            }
        }
    }
    for (int i = 0; i < H_; i++) {
        for (int j = 0; j < W_; j++) {
            for (int k = 0; k < C_; k++) {
                cout << rgb_[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    for (int i = 0; i < H_; i++) {
        for (int j = 0; j < W_; j++) {
            delete[] rgb_[i][j];
        }
        delete[] rgb_[i];
    }
    delete[] rgb_;