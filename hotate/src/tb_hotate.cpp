#include <iostream>
#include <verilated.h>
#include "Vtop.h"
// #include <verilated_vcd_c.h> // VCD出力用のインクルードファイル
#include <verilated_fst_c.h> // FST出力用のインクルードファイルを追加

// 初期化
int time_counter = 0;
// 下のように書いてる人もいた。これが一つのメイン時間になる
// unsigned int main_time = 0;     // Current simulation time

int main(int argc, char **argv)
{

	// おまじない
	Verilated::commandArgs(argc, argv);

	// counter_4bitモジュールをインスタンス化
	Vtop *dut = new Vtop();

	// VCD波形ダンプ
	// // 波形ダンプを有効化し、波形ファイル名をsmx.vcdとしてファイルディスクリプタをオープン
	// // -- ここから
	// // Trace DUMP ON
	// Verilated::traceEverOn(true);
	// VerilatedVcdC *tfp = new VerilatedVcdC;

	// dut->trace(tfp, 100); // Trace 100 levels of hierarchy
	// tfp->open("simx.vcd");
	// // -- ここまで
	// // → これだけでは波形は生成されず、dut->eval()毎に波形ダンプ用の関数を呼び出す必要がある。

	// FST波形ダンプ
	// -- ここから
	// Trace DUMP ON
	Verilated::traceEverOn(true);
	VerilatedFstC *tfp = new VerilatedFstC;

	dut->trace(tfp, 100); // Trace 100 levels of hierarchy
	tfp->open("hotate.fst");
	// -- ここまで

	// 初期化（フォーマット）
	// dut->clk = 0;
	// dut->rst = 1;

	// // 100単位時間ほどリセット状態を保持
	// // 状態を安定させるため？
	// while (time_counter < 100)
	// {
	// 	// 回路を実行（DUTを評価）
	// 	dut->eval();
	// 	tfp->dump(time_counter); // 波形ダンプ用の記述を追加

	// 	time_counter++;
	// }

	// // リセットをリリースし、シミュレーション開始
	// // カウンターが動き出す
	// dut->rst = 0;

	// クロックサイクルの記録
	int cycle = 0;
	// 500単位時間動作させる
	// 現在time_counter==100なので残り400
	// 回路が終了していない限り、評価する（終了している場合もあるから一応）
	while (time_counter < 10000000 && !Verilated::gotFinish())
	{
		// 5単位時間に１回 clkをトグル（スイッチ）
		// ここは単位時間重視！
		// if ((time_counter % 5) == 0)
		// {
		// 	// トグル
		// 	dut->clk = !dut->clk; // Toggle clock
		// }
		// // クロックサイクルを数える
		// if ((time_counter % 10) == 0)
		// {
		// 	// Cycle Count
		// 	cycle++;
		// }
		dut->clk = !dut->clk; // Toggle clock
		cycle++;

		// 5サイクルに１回 en信号を有効化
		// 50単位時間に１回有効
		// → 400/50 = 8
		// ここはサイクル重視！
		// if (cycle % 5 == 0)
		// {
		// 	// 有効化
		// 	dut->en = 1; // Assert En
		// }
		// else
		// {
		// 	// 無効化
		// 	dut->en = 0; // Deassert En
		// }

		// 毎単位時間にDUTを評価（回路を動かす）
		dut->eval();
		tfp->dump(time_counter); // 波形ダンプ用の記述を追加

		// printf("Led Value = %d\n", dut->led);
		// printf("Seg Value = %d\n", dut->seg);
		time_counter++;
	}

	// 所定時間シミュレーションを実行すると終了し、最後に結果dut->cntを出力する
	// std::cout << "Final Counter Value = " << dut->cnt << '\n';
	// printf("Final Led Value = %d\n", dut->led);
	printf("Final Led Value = %d\n", dut->led);
	// printf("Final Seg Value = %d\n", dut->seg);

	// インスタンスした回路を終了させる
	dut->final();
	tfp->close(); // 波形ファイルも閉じる
}

// テンプレート
// // 必要なファイルのインクルード
// #include <iostream>
// #include <verilated.h>
// #include "Vcounter_4bit.h"

// int main(int argc, char **argv) {
//     // Verilatorのコマンド解析
//     // DUTモジュールのインスタンス化
//     // DUTモジュールのインタフェースの初期化

//     // while文 {
//     //     クロックを1サイクルずつ進めていく記述
//     //     DUTを評価（回路を実行する）記述
//     //     DUTインタフェースを評価する処理
//     // }

//     // 終了
// }