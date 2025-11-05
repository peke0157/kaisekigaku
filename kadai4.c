#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    // ファイルポインタの宣言
    FILE *inputFile;
    FILE *outputFile;

    int ch; // 読み込んだ文字を格納
    long M = 0;
    int k; // 乱数を生成する変数

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
    for (int i = 0; i < 100; i++)
    {
        k = rand() % M;
        fseek(inputFile, k, SEEK_SET);
        ch = fgetc(inputFile);
        fputc(ch, outputFile);
    }

    // 数えたMの数
    printf("全体の文字数: %ld\n", M);
    printf("ランダムな文字列を出力しました\n");

    return 0;
}