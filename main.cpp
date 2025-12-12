#include <bits/stdc++.h>

using namespace std;

#define KEYLANE 11
// 左手か右手かの判別に使う 左手の中で一番右の位置
#define RIGHTEST_LEFTY 5

vector<vector<char>> keymap(3, vector<char>(KEYLANE));


struct keydata {
    int r; // row
    int c; // column
    char keyname;
};

// 左手の押しやすさ
const int LEFT_TYPABILITY[3*5][2] = {
    {1,3},
    {1,2},
    {1,4},
    {1,1},
    {1,0},
    {0,1},
    {0,2},
    {0,3},
    {0,4},
    {2,2},
    {2,3},
    {2,4},
    {0,0},
    {2,0},
    {2,1}
};

// 頻度順 without hjkl      15-4-4=7
const char consonants[] = {
    'N',
    'T',
    'S',
    'R',
    'M',
    'D',
    'G',
    // 'W',
    'B',
    'P',
};

vector<vector<keydata>> hjkl_Patterns = {
    {
        {r:0, c:1, keyname:'H'},
        {r:0, c:2, keyname:'K'},
        {r:0, c:3, keyname:'J'},
        {r:0, c:4, keyname:'L'}

    },{   // パターン: T字
        {r:1, c:1, keyname:'H'},
        {r:1, c:2, keyname:'J'},
        {r:1, c:3, keyname:'L'},
        {r:0, c:2, keyname:'K'}
    }, {
        // パターン: T字
        {r:1, c:2, keyname:'H'},
        {r:1, c:3, keyname:'J'},
        {r:1, c:4, keyname:'L'},
        {r:0, c:3, keyname:'K'}
    },{ // パターン2: 逆T字
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

void disp_keymap() {
    cout << endl;
    for(int i=0; i<keymap.size(); i++) {
        if(i==1) cout << ' ';  // row staggered
        if(i==2) cout << "  "; // row staggered
        for(int j=0; j<KEYLANE; j++) {
            char c = keymap[i][j];
            bool isHJKL = false;
            bool isHOME = false; // ホームポジションのポチ
            if (c=='H' || c=='J' || c=='K' || c=='L') isHJKL = true;
            if (i==1 && (j==3 || j==6)) isHOME = true;
            
            if (isHJKL && isHOME) cout << "\033[4;31m";
            else if(isHJKL) cout << "\033[31m";
            else if(isHOME) cout << "\033[4m";
            cout << keymap[i][j];
            if(isHJKL || isHOME) cout << "\033[m";
            
            if (j != KEYLANE) cout << "  "; // 最後でなければ区切る
        }
        cout << endl;
    }
    cout << "---------------------------" << endl;
}

// アルファベットがキーマップに存在するか
bool is_exsist(char c) {
    bool exs = false;
    // すでに置かれてないかチェック
    for(int i=0; i<3 && !exs; i++) {
        for(int j=0; j<KEYLANE && !exs; j++) {
            if(keymap[i][j] == c) exs = true;
        }
    }
    return exs;
}

// キーをセットする　埋まっていれば -1 を返す すでにそのアルファベットが存在すれば 0
int set_key(keydata kd) {
    // if filled
    if (keymap[kd.r][kd.c] != ' ') {
        return -1;
    }
    // すでに置かれてないかチェック
    for(int i=0; i<3; i++) {
        for(int j=0; j<KEYLANE; j++) {
            if(keymap[i][j] == kd.keyname) return 0;
        }
    }
    keymap[kd.r][kd.c] = kd.keyname;
    return 1;
}
bool set_keys(vector<keydata> kds) { // キーの塊をセットする　できてれば 1, 埋まっていれば -1
    // 最初に埋まってないかだけチェック　埋まってたらすぐ false を返す
    for(int i=0; i<kds.size(); i++) {
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

// キーマップ初期化（空白埋め）
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
    set_key({r:2, c:0, keyname:'Z'});
    set_key({r:2, c:1, keyname:'X'});
    set_key({r:2, c:5, keyname:'C'});
    set_key({r:2, c:6, keyname:'V'});

    // aiueo
    set_key({r:1, c:5, keyname:'A'});
    set_key({r:1, c:6, keyname:'U'});
    set_key({r:1, c:7, keyname:'I'});
    set_key({r:0, c:7, keyname:'O'});
    set_key({r:1, c:8, keyname:'E'});

    set_key({r:0, c:5, keyname:'Q'});
    set_key({r:0, c:6, keyname:'F'});
    set_key({r:0, c:8, keyname:'Y'});
    set_key({r:0, c:9, keyname:'W'});
}

int main() {
    for(int hjklp=0; hjklp<hjkl_Patterns.size(); hjklp++) {
        cout << endl;

        startup();
        if(!set_keys(hjkl_Patterns[hjklp])) continue;

        // 押しやすさで左手を考える
        int conscnt = 0;
        for(int i=0; i<15; i++) {
            int row = LEFT_TYPABILITY[i][0];
            int col = LEFT_TYPABILITY[i][1];
            int r = set_key({r: row, c: col, keyname: consonants[conscnt]});
            if(r==1 || r==0) {
                conscnt++;
            }
        }   
        
        disp_keymap();
        
        // 残りのアルファベット表示
        cout << "残りアルファベット全体: ";
        for(int c='A'; c<='Z'; c++) {
            if(!is_exsist(c)) cout << (char) c;
        }
        cout << endl;

    }
    return 0;
}
