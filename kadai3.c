#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_UNIGUE_BIGRAMS 5000
// 2組と出現頻度を保存する構造体
typedef struct 
{
    char bigram[3];     // ex) 'he' + '0\' で3バイト
    int count;
}BigramFreq;
BigramFreq list[MAX_UNIGUE_BIGRAMS];
int unique_bigram_count = 0;

// 3組と出現頻度を保存する構造体
typedef struct{
    char ngram[4];      // 'the' + '\0' で4バイト
    int count;
}Ngram;
Ngram list[MAX_UNIGUE_BIGRAMS];
int unique_ngram_count = 0;

int main(void)
{
   


    // ファイルポインタの宣言
    FILE *inputFile;
    FILE *outputFile;
    
    // アルファベットの出現頻度を記録するための配列
    int nijigen_counts[26] = {0};   // 小文字の場合
    int sanjigen_counts[26] = {0};   // 大文字の場合
    int ch, prev_ch = EOF; // 読み込んだ文字を格納

    // 入力ファイルを開く(読み込みモードで)
    inputFile = fopen("Input.txt", "r");
    if (inputFile == NULL)
    {
        printf("エラー：入力ファイルを開けません。\n");
        exit(1);
    }

    // 出力ファイルを開く(書き込みモードで)
    outputFile = fopen("Output2.txt", "w");
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
        if (isalpha(ch))
        {
            if (isupper(ch))                            // 大文字の時
            {
                int index_A = ch - 'A';
                nijigen_counts[index_A]++;
            }
            else if (islower(ch))                      // 小文字の時
            {
                int index_a = ch - 'a';
                sanjigen_counts[index_a]++;
            }

            fputc(ch, outputFile);
        }
        // 条件に応じて文字を処理(三文字)
        else if (isalpha(ch))
        {
            if (isupper(ch))                            // 大文字の時
            {
                int index_A = ch - 'A';
                nijigen_counts[index_A]++;
            }
            else if (islower(ch))                      // 小文字の時
            {
                int index_a = ch - 'a';
                sanjigen_counts[index_a]++;
            }

            fputc(ch, outputFile);
        }
        else if (ch == ' ' || ch == '\n')
        {
            fputc(ch, outputFile);
        }
        else
        {
            fputc(' ', outputFile);
        }
    }

    // ファイルを閉じる
    fclose(inputFile);
    fclose(outputFile);

    printf("出力が完了しました。一回も出なかった文字は以下の通りです\n");
    printf("------------------------------\n");

    //大文字の場合
    for (int i = 0; i < 26; i++)
    {
        printf("%d %c\n", nijigen_counts[i], 'A' + i); // %dは出た文字の回数、%cは文字を出力する
    }

    //小文字の場合
    for (int i = 0; i < 26; i++)
    {
        printf("%d %c\n", sanjigen_counts[i], 'a' + i); // %dは出た文字の回数、%cは文字を出力する
    }

    return 0;
}