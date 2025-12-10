#include <bits/stdc++.h>

using namespace std;

#define KEYLANE 11
vector<vector<char>> keymap(3, vector<char>(KEYLANE));

int RIGHTEST_LEFTY = 5; // 左手か右手かの判別に使う 左手の中で一番右の位置


struct keydata {
    int x;
    int y;
    char keyname;
};



int ZXCV() { // エラーなら -1 を返す 正常終了は 0
    // すでに埋まっていないかチェック 埋まっていたら -1 
    for(int i=0; i<4; i++) {
        if(keymap[2][i] != ' ') return -1;
    }

    keymap[2][0] = 'Z';
    keymap[2][1] = 'X';
    keymap[2][2] = 'C';
    keymap[2][3] = 'V';
    return 0;
}

void disp_keymap() {
    for(int i=0; i<keymap.size(); i++) {
        if(i==1) cout << ' ';  // row staggered
        if(i==2) cout << "  "; // row staggered
        for(int j=0; j<KEYLANE; j++) {
            cout << keymap[i][j];

            if (j != KEYLANE) cout << "  "; // 最後でなければ区切る
        }
        cout << endl;
    }
    cout << endl;
}

// キーマップ初期化
void init_keymap() {
    for(int i=0; i<keymap.size(); i++) {
        vector<char> keylane = keymap[i];
        for(int j=0; j<keylane.size(); j++) {
            keymap[i][j] = ' ';
        }
    }
}

// 初期にすでに決まっているもの
void startup() {
    init_keymap();
    if (ZXCV()) cout << "zxcv filled" << endl;
}

// キーをセットする　埋まっていれば false を返す
bool set_key(keydata kd) {
    // if filled
    if (keymap[kd.x][kd.y] != ' ') {
        return false;
    }
    keymap[kd.x][kd.y] = kd.keyname;
    return true;
}
bool set_keys(vector<keydata> kds) { // キーの塊をセットする　埋まっていれば false
    for(int i=0; i<kds.size(); i++) {
        // 最初に埋まってないかだけチェック　埋まってたらすぐ false を返す
        int x = kds[i].x;
        int y = kds[i].y;
        if (keymap[x][y] != ' ') return false;
    }

    for(int i=0; i<kds.size(); i++) {
        int x = kds[i].x;
        int y = kds[i].y;
        keymap[x][y] = kds[i].keyname;
    }
    return true;
}


int main() {
    startup();

    // HJKL T字
    for(int i=1; i<3; i++) {
        for(int j=1; j<KEYLANE-3; j++) { // 小指を使いたくない
            // 手が分割するなど使いにくいのだけ排除
            if (j>=2 && j<=6) {
                continue;
            }

            startup();

            // hjkl
            keydata kh = { x:i, y:j, keyname:'H' };
            keydata kj = { x:i, y:j+1, keyname:'J' };
            keydata kl = { x:i, y:j+2, keyname:'L' };
            keydata kk = { x:i-1, y:j+1, keyname:'K' };
            set_keys({kh, kj, kl, kk});

            disp_keymap();
        }
    }

    return 0;
}


