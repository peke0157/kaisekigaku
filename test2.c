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

    // 乱数系列を初期化
    srand(time(NULL));

    // 入力ファイルを開く(読み込みモードで)
    inputFile = fopen("Input.txt", "r");
    if (inputFile == NULL)
    {
        printf("エラー：入力ファイルを開けません。\n");
        exit(1);
    }

    // 出力ファイルを開く(書き込みモードで)
    outputFile = fopen("Output4_test.txt", "w");
    if (outputFile == NULL)
    {
        printf("エラー：出力ファイルを開けません。\n");
        fclose(inputFile); // 　開いている入力ファイルを閉じる
        exit(1);
    }

    // (a) テキストファイルの全文字数 M を数える
    while ((ch = fgetc(inputFile)) != EOF)
    {
        M += 1;
    }

    // 数えたMの数
    printf("処理した文字の総数(M): %ld\n", M);

    // Mが0（ファイルが空）だった場合、何もせず終了
    if (M == 0)
    {
        printf("入力ファイルが空です。\n");
        fclose(inputFile);
        fclose(outputFile);
        return 0;
    }

    // (b)~(d) の処理（ランダムな文字列生成）

    // fseek/fgetc を正しく動作させるため、
    // EOFに達したストリームの状態をリセットし、ファイルポインタを先頭に戻す
    rewind(inputFile);

    // (d) 100回繰り返す
    for (int i = 0; i < 100; i++)
    {
        // (b) M以下の任意の数 k を得る
        k = rand() % M;

        // (c) ファイル中の k 番目の文字を調べる
        fseek(inputFile, k, SEEK_SET); // ファイルポインタを k バイト目に移動
        ch = fgetc(inputFile);         // 1文字読み込む

        // ファイルに書き出す
        fputc(ch, outputFile);
    }

    // ファイルを閉じる
    fclose(inputFile);
    fclose(outputFile);

    printf("Output4.txt にランダムな文字列を出力しました。\n");

    return 0;
}