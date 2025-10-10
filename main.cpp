#include <bits/stdc++.h>

using namespace std;

vector<vector<char>> keymap(3, vector<char>(11));

int RIGHTEST_LEFTTY = 5; // 左手か右手かの判別に使う 左手の中で一番右の位置


int ZXCV() { // エラーなら -1 を返す 正常終了は 0
    int result = 0;
    // すでに埋まっていないかチェック 埋まっていたら -1 
    for(int i=0; i<4; i++) {
        if(keymap[2][i] != ' ') result = -1;
    }

    keymap[2][0] = 'Z';
    keymap[2][1] = 'X';
    keymap[2][2] = 'C';
    keymap[2][3] = 'V';

    return result;
}

void disp_keymap() {
    for(int i=0; i<keymap.size(); i++) {
        vector<char> keylane = keymap[i];
        for(int j=0; j<keylane.size(); j++) {
            cout << keylane[j];

            if (j != keylane.size()) cout << " | "; // 最後でなければ区切る
        }
        cout << endl;
    }
}

int main() {
    // キーマップ初期化
    for(int i=0; i<keymap.size(); i++) {
        vector<char> keylane = keymap[i];
        for(int j=0; j<keylane.size(); j++) {
            keymap[i][j] = ' ';
        }
    }

    int zxcvR = ZXCV();
    if (zxcvR == -1) cout << "zxcv error" << endl;

    

    disp_keymap();

    return 0;
}


