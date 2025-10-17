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
    
}
