#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ★追加: 生成したいおおよその文字数を定義
#define NUM_TO_GENERATE 1000

int main(void)
{
    // ファイルポインタの宣言
    FILE *inputFile;
    FILE *outputFile;

    // ★修正: ch や A は EOF (-1) を扱えるよう int 型に変更
    int ch;
    long M = 0;
    int k, k_prime; // 乱数用のインデックス
    int A;          // 探す文字 (k+1番目の文字)
    int next_ch;    // Aの次に見つかった文字

    srand(time(NULL)); // 乱数系列を初期化

    // 入力ファイルを開く(読み込みモードで)
    inputFile = fopen("Input.txt", "r");
    if (inputFile == NULL)
    {
        printf("エラー：入力ファイルを開けません。\n");
        exit(1);
    }

    // ★修正: 出力ファイル名を課題に合わせる (例: Output_problem5.txt)
    outputFile = fopen("Output_problem5.txt", "w");
    if (outputFile == NULL)
    {
        printf("エラー：出力ファイルを開けません。\n");
        fclose(inputFile); // 開いている入力ファイルを閉じる
        exit(1);
    }

    // --- ステップa: テキストファイルの全文字数 M を数える ---
    while ((ch = fgetc(inputFile)) != EOF)
    {
        M += 1;
    }

    // ★修正: 2文字（ペア）未満のファイルは処理できない
    if (M < 2)
    {
        printf("入力ファイルが小さすぎます (2文字未満)。\n");
        fclose(inputFile);
        fclose(outputFile);
        return 0;
    }
    printf("全体の文字数: %ld\n", M);

    // ファイルポインタを最初に戻す
    rewind(inputFile);

    // --- ステップb: M以下の任意の数kを得る ---
    // (M-1)までの乱数を生成し、k番目とk+1番目を読めるようにする
    // (rand() % (M - 1) は 0 から M-2 までの値を生成)
    k = rand() % (M - 1);

    // --- ステップc: k番目とk+1番目の文字を出力し、k+1番目をAとする ---
    fseek(inputFile, k, SEEK_SET); // k番目の位置へ移動

    ch = fgetc(inputFile); // k番目の文字
    A = fgetc(inputFile);  // k+1番目の文字

    if (ch == EOF || A == EOF)
    {
        // 基本的に M < 2 で弾かれるはずだが念のため
        printf("エラー: ファイルの読み込みに失敗しました。\n");
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    fputc(ch, outputFile); // k番目を出力
    fputc(A, outputFile);  // k+1番目を出力

    // --- ステップd, e, f: 繰り返し処理 ---
    // 既に2文字出力したので、(NUM_TO_GENERATE - 2) 回繰り返す
    for (int i = 0; i < (NUM_TO_GENERATE - 2); i++)
    {
        int found = 0; // Aに続く文字が見つかったかのフラグ

        // --- ステップd: 乱数により M 以下の任意数 k' を得る ---
        k_prime = rand() % M; // 0 から M-1 の乱数

        // --- ステップe: k'番目の文字より後で最初に出現する A を探す ---
        // (ここでは k'番目「から」探し始め、ファイル末尾まで探す)
        fseek(inputFile, k_prime, SEEK_SET);

        while ((ch = fgetc(inputFile)) != EOF)
        {
            if (ch == A)
            {
                // --- ステップf: 見つかったらその次の文字を次のAとして出力 ---
                next_ch = fgetc(inputFile);
                if (next_ch != EOF)
                {
                    fputc(next_ch, outputFile);
                    A = next_ch; // Aを更新
                    found = 1;
                    break; // このiのループでの探索は終わり
                }
                else
                {
                    // Aがファイルの最後だった。ループから抜ける
                    break;
                }
            }
        }

        // k'から末尾までで見つからなかった場合、ファイルの先頭からk'までを探す (ラップアラウンド)
        if (!found)
        {
            rewind(inputFile);
            long current_pos = 0;
            // k_prime の位置「まで」探す
            while (current_pos < k_prime && (ch = fgetc(inputFile)) != EOF)
            {
                current_pos = ftell(inputFile); // 読んだ「後」の位置
                if (ch == A)
                {
                    next_ch = fgetc(inputFile);
                    if (next_ch != EOF)
                    {
                        fputc(next_ch, outputFile);
                        A = next_ch;
                        found = 1;
                        break;
                    }
                    // else: Aがファイルの最後だった
                }
            }
        }

        // もしAに続く文字が（EOF以外で）本当に見つからなかった場合
        if (!found)
        {
            // (例: 'A' がファイルの末尾にしか存在しない)
            // 処理が止まってしまうので、ランダムなペアでリセットする
            k = rand() % (M - 1);
            fseek(inputFile, k, SEEK_SET);
            ch = fgetc(inputFile);
            A = fgetc(inputFile);
            if (A == EOF)
            {
                break; // ファイルが小さすぎる場合
            }
            fputc(A, outputFile); // 1文字だけ追加
        }

    } // for ループ (i) の終わり

    printf("ランダムな文字列を出力しました (Output_problem5.txt)\n");

    // ファイルを閉じる
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}