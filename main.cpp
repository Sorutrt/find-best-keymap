#include <bits/stdc++.h>

using namespace std;

#define KEYLANE 11
#define RIGHTEST_LEFTY 5

vector<vector<char>> keymap(3, vector<char>(KEYLANE));

// 左手か右手かの判別に使う 左手の中で一番右の位置


struct keydata {
    int r; // row
    int c; // column
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
    cout << "---------------------------" << endl;
}


// キーをセットする　埋まっていれば false を返す
bool set_key(keydata kd) {
    // if filled
    if (keymap[kd.r][kd.c] != ' ') {
        return false;
    }
    keymap[kd.r][kd.c] = kd.keyname;
    return true;
}
bool set_keys(vector<keydata> kds) { // キーの塊をセットする　埋まっていれば false
    for(int i=0; i<kds.size(); i++) {
        // 最初に埋まってないかだけチェック　埋まってたらすぐ false を返す
        int r = kds[i].r;
        int c = kds[i].c;
        if (keymap[r][c] != ' ') return false;
    }
    for(int i=0; i<kds.size(); i++) {
        int r = kds[i].r;
        int c = kds[i].c;
        keymap[r][c] = kds[i].keyname;
    }
    return true;
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
    set_key({r:1, c:5, keyname:'A'});
}

int main() {
    vector<vector<keydata>> hjkl_Patterns = {
        {   // パターン1: T字
            {r:1, c:1, keyname:'H'},
            {r:1, c:2, keyname:'J'},
            {r:1, c:3, keyname:'L'},
            {r:0, c:2, keyname:'K'}
        }, { // パターン2: 逆T字
            {r:0, c:2, keyname:'H'},
            {r:0, c:3, keyname:'K'},
            {r:0, c:4, keyname:'L'},
            {r:1, c:3, keyname:'J'}
        }, { // パターン3: 逆T字右寄り
            {r:0, c:2, keyname:'H'},
            {r:0, c:3, keyname:'K'},
            {r:0, c:4, keyname:'L'},
            {r:1, c:4, keyname:'J'}
        }
    };

    for(int hjklp=0; hjklp<hjkl_Patterns.size(); hjklp++) {
        startup();
        if(!set_keys(hjkl_Patterns[hjklp])) continue;

        // iueo
        set_key({r:0, c:7, keyname:'I'});
        set_key({r:1, c:6, keyname:'U'});
        set_key({r:1, c:7, keyname:'O'});
        set_key({r:1, c:8, keyname:'E'});

        disp_keymap();
    }

    return 0;
}


