#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_UNIGUE_BIGRAMS 5000
#define MAX_UNIGUE_NRAMS 5000
#define TOP_N 15

// 2組と出現頻度を保存する構造体
typedef struct
{
    char bigram[3]; // ex) 'he' + '0\' で3バイト
    int count;
} BigramFreq;
BigramFreq bigram_list[MAX_UNIGUE_BIGRAMS];
int unique_bigram_count = 0;

// 3組と出現頻度を保存する構造体
typedef struct
{
    char ngram[4]; // 'the' + '\0' で4バイト
    int count;
} Ngram;
Ngram ngram_list[MAX_UNIGUE_NRAMS];
int unique_ngram_count = 0;

//---関数プロトタイプ---//
void update_bigram_count(const char *bigram);
void update_ngram_count(const char *ngram);
int compare_bigram(const void *a, const void *b);
int compare_ngram(const void *a, const void *b);

int main(void)
{

    // ファイルポインタの宣言
    FILE *inputFile;
    FILE *outputFile;

    // アルファベットの出現頻度を記録するための配列
    int nijigen_counts[26] = {0};  // 小文字の場合
    int sanjigen_counts[26] = {0}; // 大文字の場合
    int prev_ch, ch = EOF;         // 読み込んだ文字を格納       prev_chはEOFで初期化
    int prevv_ch = EOF;            // 三文字用の変数

    // 入力ファイルを開く(読み込みモードで)
    inputFile = fopen("Input.txt", "r");
    if (inputFile == NULL)
    {
        printf("エラー：入力ファイルを開けません。\n");
        exit(1);
    }

    // 出力ファイルを開く(書き込みモードで)
    outputFile = fopen("Output3.txt", "w");
    if (outputFile == NULL)
    {
        printf("エラー：出力ファイルを開けません。\n");
        fclose(inputFile); // 　開いている入力ファイルを閉じる
        exit(1);
    }

    // メインループ処理
    while ((ch = fgetc(inputFile)) != EOF)
    {
        // 条件に応じて文字を処理(二文字)
        if (isalpha(prev_ch) && isalpha(ch))
        {
            char current_bigram[3];
            current_bigram[0] = tolower(prev_ch); // 小文字で統一、prev_chに格納
            current_bigram[1] = tolower(ch);      // chに格納
            current_bigram[2] = '\0';
            update_bigram_count(current_bigram);
        }
        // 条件に応じて文字を処理(三文字)
        else if (isalpha(prevv_ch) && isalpha(prev_ch) && isalpha(ch))
        {
            char current_ngram[4];
            current_ngram[0] = tolower(prevv_ch);
            current_ngram[1] = tolower(prev_ch);
            current_ngram[2] = tolower(ch);
            current_ngram[3] = '\0';
            update_ngram_count(current_ngram);
        }
        prev_ch = ch;
        prevv_ch = prevv_ch;
    }

    // ファイルを閉じる
    fclose(inputFile);
    fclose(outputFile);

    printf("処理中です\n");
    printf("------------------------------\n");

    // 2文字の並べ替え
    qsort(bigram_list, unique_bigram_count, sizeof(BigramFreq), compare_bigram);
    // 3文字の並べ替え
    qsort(ngram_list, unique_ngram_count, sizeof(Ngram), compare_ngram);

    // 2文字の場合
    void update_bigram_count(const char *bigram)
    {
        for (int i = 0; i < unique_bigram_count; i++)
        {
            if (strcmp(bigram_list[i].bigram, bigram) == 0)
            {
                bigram_list[i].unique_bigram_count++;
                return;
            }
            if(unique_bigram_count < MAX_UNIGUE_BIGRAMS){
                strcmp(bigram_list[unique_bigram_count].bigram, current_bigram);
                list[unique_bigram_count].count = 1;
                unique_bigram_count++;
            }
        }
    }

    // 3文字の場合
    void update_ngram_count(const char *ngram)
    {
        for (int i = 0; i < unique_ngram_count; i++)
        {
            if (strcmp(ngram_list[i], ngram) == 0){
                ngram_list[i].unique_ngram_count++;
                return;
            }
            if(unique_ngram_count < MAX_UNIGUE_ngramS){
                strcmp(ngram_list[unique_ngram_count].ngram, current_ngram);
                list[unique_ngram_count].count = 1;
                unique_ngram_count++;
            }
        }
    }

    // 2文字をcountの降順で比較する
    int compare_bigram(const void *a, const void *b){
        BigramFreq *freq_a = (BigramFreq*) a;
        BigramFreq *freq_b = (BigramFreq*) b;
        // b - a で降順ソート
        return freq_b->count - freq_a- > count;
    }
    int compare_ngram(const void *a, const void *b){
        Ngram *freq_a = (Ngram*) a;
        Ngram *freq_b = (Ngram*) b;
        // b - a で降順ソート
        return freq_b->count - freq_a- > count;
    }
}