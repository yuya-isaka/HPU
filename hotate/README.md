yuya-isaka
==============
The simple 32-bit RISC-V core.

# 現状

### アーキテクチャ
* 1命令に5クロック(フェッチ→デコード→実行→メモリ・アクセス→書き戻しの5段階にそれぞれ1クロック)
* パイプライン省略
* 命令セット：RV32I
* 特権命令や割り込み周りは省略
* 生成した16進数の命令列はSystemVerilogの$readmemhを利用して命令メモリに埋めこみ
	* ファイル名の指定（$readmemh） /home/isaka/...
* 関数の引数と戻り値が入るa0レジスタの値を10進数で7セグLEDに表示する回路
* 動作を見やすくするためにクロックを10万分周 → これ多分してない？？？

### testディレクトリ
* test/test.c...フィボナッチ数列の第10番目の項を再帰で求めるプログラムを実行
* test/start.S...何もせずmainを呼び出すように指定(普通にコンパイルしてしまうと未実装の命令を使った初期化ルーチンが走ってしまう)
* test/link.ld...命令を0番地から実行するように指定
* test/Makefile...hexファイル,dumpファイル生成自動化

### testディレクトリ（Makefileによって生成されるもの）
* test/test.hex...CPUが実行する命令列が16進数,4バイト並ぶ
* test/test.dump...test.elfを逆アセンブリした結果(再帰でフィボナッチ数を求めた後、`8c'を無限ループするプログラムになっていることが確認)

### Makefile流れ
```
// アセンブラ準備
$ riscv32-unknown-linux-gnu-gcc -march=rv32id -c -o start.o start.S

// コンパイル
$ riscv32-unknown-linux-gnu-gcc -march=rv32id -c -o test.o test.c

// リンク
$ riscv32-unknown-linux-gnu-ld test.o start.o -L/opt/riscv32/riscv32-unknown-linux-gnu/lib/ -T link.ld -static -o test.elf

// 逆アセンブル
$ riscv32-unknown-linux-gnu-objdump -d test.elf > test.dump

// バイナリ生成
$ riscv32-unknown-linux-gnu-objcopy -O binary test.elf test.bin

// hex生成
$ od -An -tx4 -w4 -v test.bin > test.hex
```

### Makefile使い方
```
$ make <テストしたいCファイル名>

例
$ make fib
→ fib.cがRISC-V用にコンパイルされる。

// 下記は必要に応じて、多分いらない。
// sudo chmod 777 test.hex
```

### ディレクトリ構成
* Linux側では，vivado_prjが用意されている．
* vivado関連はgithubにあげない．
* binとかhexファイルもあげない．