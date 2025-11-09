#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TO_GENERATE 100000000
int main(void)
{
    // ファイルポインタの宣言
    FILE *inputFile;
    FILE *outputFile;

    int ch, next_ch, ch1, next_ch1; // 読み込んだ文字を格納
    long M = 0;
    int k, k_prime, k1, k1_prime; // 乱数を生成する変数
    int A;      // 保存用(二次元)
    int a1, a2; // 保存用(三次元)

    srand(time(NULL)); // 乱数系列を初期化

    // 入力ファイルを開く(読み込みモードで)
    inputFile = fopen("Input.txt", "r");
    if (inputFile == NULL)
    {
        printf("エラー：入力ファイルを開けません。\n");
        exit(1);
    }

    // 出力ファイルを開く(書き込みモードで)
    outputFile = fopen("Output5.txt", "w");
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
    rewind(inputFile);
    if (M == 0){
        printf("入力ファイルが空です");
        fclose(inputFile);
        fclose(outputFile);
        return 0;
    } 
    // 2次元のとき
        k = rand() % (M -1);                                 // M以下の任意の数kを得る
        fseek(inputFile, k, SEEK_SET);                  // ファイルの中のk番目の数を調べる
        ch = fgetc(inputFile);                          // k番目の1文字を読み込む
        A = fgetc(inputFile);
        fputc(ch, outputFile);
        fputc(A, outputFile);

    // すでに二文字出力しているので繰り返す範囲を-2する
    for (int i = 0; i < (NUM_TO_GENERATE - 2); i++){
        int found = 0;      // Aに続く文字が見つかったかのフラグ

        k_prime = rand() % M;

        fseek(inputFile, k_prime, SEEK_SET);

        while((ch = fgetc(inputFile)) != EOF){
            // Aが見つかった時
            if(ch == A){
                next_ch = fgetc(inputFile);
                if(next_ch != EOF){

                    fputc(next_ch, outputFile);
                    A = next_ch;
                    found = 1;
                    break;           
                }
            }
        }

    }
    
    // 3次元の時
    for (int i = 0; i < M; i++)
    {
        k1 = rand() % M;                                 // M以下の任意の数kを得る
        fseek(inputFile, k, SEEK_SET);                  // ファイルの中のk番目の数を調べる
        ch = fgetc(inputFile);                          // k番目の1文字を読み込む
        A = ch1;
        fputc(ch, outputFile);
    }

    // 数えたMの数
    printf("全体の文字数: %ld\n", M);
    printf("ランダムな文字列を出力しました\n");

    return 0;
}