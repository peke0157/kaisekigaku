#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    // ファイルポインタの宣言
    FILE *inputFile;
    FILE *outputFile;

    int ch, ch_1; // 読み込んだ文字を格納
    long M = 0;
    int k, k_1; // 乱数を生成する変数
    int A;      // 保存用

    srand(time(NULL)); // 乱数系列を初期化

    // 入力ファイルを開く(読み込みモードで)
    inputFile = fopen("Input.txt", "r");
    if (inputFile == NULL)
    {
        printf("エラー：入力ファイルを開けません。\n");
        exit(1);
    }

    // 出力ファイルを開く(書き込みモードで)
    outputFile = fopen("Output4.txt", "w");
    if (outputFile == NULL)
    {
        printf("エラー：出力ファイルを開けません。\n");
        fclose(inputFile); // 　開いている入力ファイルを閉じる
        exit(1);
    }

    // メインループ処理
    while ((ch = fgetc(inputFile)) != EOF)
    {
        M += 1;
    }
    if (M == 0){
        printf("入力ファイルが空です");
        fclose(inputFile);
        fclose(outputFile);
        return 0;
    } 
    rewind(inputFile);
    for (int i = 0; i < M; i++)
    {
        k = rand() % M;                                 // M以下の任意の数kを得る
        fseek(inputFile, k, SEEK_SET);                  // ファイルの中のk番目の数を調べる
        ch = fgetc(inputFile);                          // k番目の1文字を読み込む
        ch_1 = fgetc(inputFile + 1);                       // k+1番目の1文字を読み込む
        A = ch_1;
        fputc(ch, outputFile);
    }
    for (int i = 0; i < M; i++)
    {
        k_1 = rand() % M;                                 // M以下の任意の数kを得る
        fseek(inputFile, k, SEEK_SET);                  // ファイルの中のk番目の数を調べる
        ch = fgetc(inputFile);                          // k番目の1文字を読み込む
        ch_1 = fgetc(inputFile + 1);                       // k+1番目の1文字を読み込む
        A = ch_1;
        fputc(ch, outputFile);
    }

    // 数えたMの数
    printf("全体の文字数: %ld\n", M);
    printf("ランダムな文字列を出力しました\n");

    return 0;
}