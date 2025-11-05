#include <stdio.h>
#include <stdlib.h> // exit, qsort のため
#include <string.h> // strcmp, strcpy のため
#include <ctype.h>  // isalpha, tolower のため

// --- 定義 ---
// それぞれ何種類のN-gramを記録するか (必要に応じて増やす)
#define MAX_UNIQUE_BIGRAMS 10000
#define MAX_UNIQUE_TRIGRAMS 20000 
#define TOP_N 30 // 上位何件を表示するか

// --- 構造体定義 ---

// 二ッ組 ("he" など) のための構造体
typedef struct {
    char bigram[3]; // 2文字 + 終端文字'\0'
    int count;
} BigramFreq;

// 三ッ組 ("the" など) のための構造体
typedef struct {
    char trigram[4]; // 3文字 + 終端文字'\0'
    int count;
} TrigramFreq;

// --- グローバル変数 (構造体の配列とカウンタ) ---
BigramFreq bigram_list[MAX_UNIQUE_BIGRAMS];
int unique_bigram_count = 0;

TrigramFreq trigram_list[MAX_UNIQUE_TRIGRAMS];
int unique_trigram_count = 0;


// --- 関数プロトタイプ ---
void update_bigram_count(const char* bigram);
void update_trigram_count(const char* trigram);
int compare_bigram(const void *a, const void *b);
int compare_trigram(const void *a, const void *b);


/**
 * @brief メイン関数
 */
int main(void) {
    FILE *inputFile;
    // ch     = 現在の文字
    // prev_ch = 1つ前の文字
    // prev_prev_ch = 2つ前の文字
    int ch, prev_ch = EOF, prev_prev_ch = EOF;

    // --- 1. ファイルを開く ---
    inputFile = fopen("Input.txt", "r");
    if (inputFile == NULL) {
        fprintf(stderr, "エラー: Input.txt を開けません。\n");
        exit(1);
    }

    // --- 2. ファイルを1文字ずつ読み込み、N-gramを生成・カウント ---
    while ((ch = fgetc(inputFile)) != EOF) {
        
        // --- 二ッ組の処理 ---
        // (1つ前の文字 と 現在の文字 が両方アルファベットか？)
        if (isalpha(prev_ch) && isalpha(ch)) {
            char current_bigram[3];
            current_bigram[0] = tolower(prev_ch); // 小文字に統一
            current_bigram[1] = tolower(ch);
            current_bigram[2] = '\0';
            update_bigram_count(current_bigram);
        }

        // --- 三ッ組の処理 ---
        // (2つ前、1つ前、現在 の3文字が全てアルファベットか？)
        if (isalpha(prev_prev_ch) && isalpha(prev_ch) && isalpha(ch)) {
            char current_trigram[4];
            current_trigram[0] = tolower(prev_prev_ch);
            current_trigram[1] = tolower(prev_ch);
            current_trigram[2] = tolower(ch);
            current_trigram[3] = '\0';
            update_trigram_count(current_trigram);
        }

        // --- 最後に文字をスライドさせる ---
        prev_prev_ch = prev_ch;
        prev_ch = ch;
    }

    // --- 3. ファイルを閉じる ---
    fclose(inputFile);

    // --- 4. qsortで頻度順にソートする ---
    printf("ソートを実行中...\n");
    // 二ッ組リストをソート
    qsort(bigram_list, unique_bigram_count, sizeof(BigramFreq), compare_bigram);
    // 三ッ組リストをソート
    qsort(trigram_list, unique_trigram_count, sizeof(TrigramFreq), compare_trigram);

    // --- 5. 結果を表示する ---
    
    // 二ッ組の表示
    printf("\n--- 二ッ組 (Bigram) の出現頻度 TOP %d ---\n", TOP_N);
    int limit_bigram = (unique_bigram_count > TOP_N) ? TOP_N : unique_bigram_count;
    for (int i = 0; i < limit_bigram; i++) {
        printf("%8d 回: %s\n", bigram_list[i].count, bigram_list[i].bigram);
    }

    // 三ッ組の表示
    printf("\n--- 三ッ組 (Trigram) の出現頻度 TOP %d ---\n", TOP_N);
    int limit_trigram = (unique_trigram_count > TOP_N) ? TOP_N : unique_trigram_count;
    for (int i = 0; i < limit_trigram; i++) {
        printf("%8d 回: %s\n", trigram_list[i].count, trigram_list[i].trigram);
    }
    
    printf("\n処理が完了しました。\n");
    
    return 0;
}


/**
 * @brief 二ッ組リストの出現回数を更新する
 */
void update_bigram_count(const char* bigram) {
    // 1. 既にリストに存在するか探す
    for (int i = 0; i < unique_bigram_count; i++) {
        if (strcmp(bigram_list[i].bigram, bigram) == 0) {
            bigram_list[i].count++; // 見つかったらカウントアップ
            return; // 処理終了
        }
    }

    // 2. 見つからなかったら、新しくリストに追加する (配列の空きがあれば)
    if (unique_bigram_count < MAX_UNIQUE_BIGRAMS) {
        strcpy(bigram_list[unique_bigram_count].bigram, bigram);
        bigram_list[unique_bigram_count].count = 1;
        unique_bigram_count++;
    }
    // 配列が一杯の場合は警告を出すこともできるが、ここでは無視する
}


/**
 * @brief 三ッ組リストの出現回数を更新する
 */
void update_trigram_count(const char* trigram) {
    // 1. 既にリストに存在するか探す
    for (int i = 0; i < unique_trigram_count; i++) {
        if (strcmp(trigram_list[i].trigram, trigram) == 0) {
            trigram_list[i].count++; // 見つかったらカウントアップ
            return; // 処理終了
        }
    }

    // 2. 見つからなかったら、新しくリストに追加する (配列の空きがあれば)
    if (unique_trigram_count < MAX_UNIQUE_TRIGRAMS) {
        strcpy(trigram_list[unique_trigram_count].trigram, trigram);
        trigram_list[unique_trigram_count].count = 1;
        unique_trigram_count++;
    }
}


/**
 * @brief qsort用: 二ッ組をcountの降順（多い順）で比較する
 */
int compare_bigram(const void *a, const void *b) {
    BigramFreq *freq_a = (BigramFreq *)a;
    BigramFreq *freq_b = (BigramFreq *)b;
    // b - a で降順ソート
    return freq_b->count - freq_a->count;
}


/**
 * @brief qsort用: 三ッ組をcountの降順（多い順）で比較する
 */
int compare_trigram(const void *a, const void *b) {
    TrigramFreq *freq_a = (TrigramFreq *)a;
    TrigramFreq *freq_b = (TrigramFreq *)b;
    // b - a で降順ソート
    return freq_b->count - freq_a->count;
}
