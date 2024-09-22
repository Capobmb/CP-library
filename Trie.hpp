#include<bits/stdc++.h>

template<unsigned char_count = 26, int char_base = 'a'>
struct Trie {
    struct Node {
        Node* child[char_count];
        int char_n; // char_base_indexed
        int word_end_count;
        // 以下に任意の情報を追加

        // cというcharをもつ頂点を作成
        Node(int c) : char_n(c), word_end_count(0) {
            for(unsigned i=0; i<char_count; i++) child[i] = nullptr;
        }
    };
    Node* root = nullptr;

    Trie() { root = new Node(-1); }
    void insert(const std::string& s) {
        Node* now = root;
        for(int c : s) {
            c -= char_base;
            if(!now->child[c]) {
                now->child[c] = new Node(c);
            }
            now = now->child[c];
        }
        now->word_end_count++;
    }

    bool find(const std::string& s) const {
        Node* now = root;
        for(int c : s) {
            c -= char_base;
            if(!now->child[c]) return false;
            now = now->child[c];
        }
        return now->word_end_count > 0;
    }
};


// template<unsigned char_count = 26, int char_base = 'a'>
// struct Trie {
//     struct Node {
//         Node* child[char_count];
//         int char_n; // char_base_indexed
//         int word_end_count;
//         int least_child_char;
//         // 以下に任意の情報を追加

//         // cというcharをもつ頂点を作成
//         Node(int c) : char_n(c), word_end_count(0), least_child_char(char_count) {
//             for(unsigned i=0; i<char_count; i++) child[i] = nullptr;
//         }
//     };
//     Node* root = nullptr;

//     Trie() { root = new Node(-1); }
//     void insert(const std::string& s) {
//         Node* now = root;
//         for(int c : s) {
//             c -= char_base;
//             if(!now->child[c]) {
//                 now->child[c] = new Node(c);
//                 if(c < now->least_child_char) now->least_child_char = c;
//             }
//             now = now->child[c];
//         }
//         now->word_end_count++;
//     }

//     bool find(const std::string& s) const {
//         Node* now = root;
//         for(int c : s) {
//             c -= char_base;
//             if(!now->child[c]) return false;
//             now = now->child[c];
//         }
//         return now->word_end_count > 0;
//     }
// };

    /*
    std::string find_smallest(Node* now) const {
        std::string ret;
        ret.push_back(now->char_n + char_base);
        while(now->word_end_count == 0) {
            ret.push_back(now->least_child_char + char_base);
            now = now->child[now->least_child_char];
        }
        return ret;
    }
    // trieにinsertしたもの：
    // abc
    // ac
    // lower_bound(abcd) = ac
    // std::string がprefixである文字列を貪欲に検索
    // それが見つからなくなったら, find_smallestする
    // 再帰ならなんとかなるかも
    std::string lower_bound(const std::string& s) {
        return internal_lb(root, s);
        // Node* now = root;
        // std::string ret;

        // for(int c : s) {
        //     c -= char_base;
        //     if(now->child[c]) {
        //         ret.push_back(c + char_base);
        //         now = now->child[c];
        //     }
        //     else {
        //         for(int i=c+1; i<char_count; ++i) {
        //             if(now->child[i]) return ret + find_smallest(now->child[i]);
        //         }
        //         return std::string{};
        //     }
        // }
        // // まだここでも末端でない場合の処理が必要
        // return ret;
    }
    std::string internal_lb(Node* now, const std::string& s) {
        if(s.length() == 0) {
            // うわあああああああ
        }
        if(now->child[s.front()])
    }
    */