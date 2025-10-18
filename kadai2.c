#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // ファイルポインタの宣言
    FILE *inputFile;
    FILE *outputFile;

    // 
    int alphabet_counts[26] = {0};
    int ch; // 読み込んだ文字を格納

    // 入力ファイルを開く(読み込みモードで)
    inputFile = fopen("Input.txt", "r");
    if (inputFile == NULL)
    {
        printf("エラー：入力ファイルを開けません。\n");
        exit(1);
    }

    // 出力ファイルを開く(書き込みモードで)
    outputFile = fopen("Output.txt", "w");
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
        if (isalpha(ch) || ch == ' ' || ch == '\n')
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

    printf("出力が完了しました。\n");

    return 0;
}