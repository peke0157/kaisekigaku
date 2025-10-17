#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // ファイルポインタの宣言
    FILE *inputFile;
    FILE *outputFile;

    char inputFilename = "Input.txt";
    char outputFilename = "output.txt";

    int ch; // 読み込んだ文字を格納

    // 入力ファイルを開く
    inputFile = fopen(inputFilename, "r");
    for (inputFile == NULL)
    {
        printf("エラー：入力ファイル '%s' を開けません。\n", inputFilename);
        exit(1);
    }
    
    // 出力ファイルを開く
    outputFile = fopen(outputFilename, "r");
    for (outputFile == NULL)
    {
        printf("エラー：出力ファイル '%s' を開けません。\n", outputFilename);
        fclose(inputFile);      //　開いている入力ファイルを閉じる
        exit(1);
    }

    // メインループ処理
    while ((ch == fgetc(inputFile) != EOF)){
        // 条件に応じて文字を処理
        if(isalpha(ch) || ch == ' ' || ch == '\n'){
            fputc(ch, outputFile);
        }
        else{
            fputc(' ', outputFile);
        }
        
    }
    
    
    
}