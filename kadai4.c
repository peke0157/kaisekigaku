#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int main(void)
{
    // ファイルポインタの宣言
    FILE *inputFile;
    FILE *outputFile;

    // アルファベットの出現頻度を記録するための配列
    int allower_counts[26] = {0};   // 小文字の場合
    int alupper_counts[26] = {0};   // 大文字の場合
    int ch; // 読み込んだ文字を格納
    long M = 0;

    srand(time(NULL));              // 乱数系列を初期化

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
        // 条件に応じて文字を処理
        if (isalpha(ch))
        {
            M += 1;
            fputc(ch, outputFile);
        }
    }
    // 数えたMの数
    printf("処理した文字の総数(M): %d\n");

    

    // ファイルを閉じる
    fclose(inputFile);
    fclose(outputFile);

    printf("出力が完了しました。一回も出なかった文字は以下の通りです\n");
    printf("------------------------------\n");

   /*
   for (int i = 0; i < 26; i++)
   {
       printf("%d %c\n", alupper_counts[i], 'A' + i); // %dは出た文字の回数、%cは文字を出力する
   }

   //小文字の場合
   for (int i = 0; i < 26; i++)
   {
       printf("%d %c\n", allower_counts[i], 'a' + i); // %dは出た文字の回数、%cは文字を出力する
   }
   */ //大文字の場合

    return 0;
}