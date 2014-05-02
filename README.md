B4M1勉強会2014 - High Performance Programming
====

概要
----
Fx10やMICを最大限利用した行列演算を作成し、競ってください。

内容
----
このテストプログラムをリンクし、測定を行います。
その際に、Fx10とMIC向けの設定項目が存在ので注意してください。(コンパイラやエンディアンが異なるため)

最も簡単な使い方
----
* 適当なx86やamd64のマシン(自分のラップトップなど)でg++によりビルドする場合
  1. srcの中にある、mymulmat.cppを変更する
  2. このREADME.mdがあるディレクトリに移動して、`make`コマンドを実行
  3. 生成されるmain.binを実行する
  4. 問題セットを変更したい場合は、data/list-intel.txtを変更する。

* FX10向けにビルドする場合
  1. Makefileを開き、PLATFORMの項目をFX10に変更する
  2. data/list.txtのシンボリックリンクを、data/list-fx10.txtに張り替える。
     dataディレクトリにcdした後、`ln -fs list-fx10.txt list.txt`を実行すればできる。
  3. srcの中にある、mymulmat.cppを変更する
  4. このREADME.mdがあるディレクトリに移動して、`make`コマンドを実行
  5. run.bashの中のrscgrp, node, elapseなどを適切に設定し、`pjsub run.bash`を実行
  6. `pjstat`コマンドでタスクが終わるのを確認する
  7. run.bash.oXXXXXXのようなファイルに結果が書き込まれているのを確認する
  8. 問題セットを変更したい場合は、data/list-fx10.txtを変更する。

* MIC向けにビルドする場合
  1. Makefileを開き、PLATFORMの項目をXEONPHIに変更する
  2. srcの中にある、mymulmat.cppを変更する
  3. このREADME.mdがあるディレクトリに移動して、`make`コマンドを実行
  4. 出来上がったmain.bin、及びdataディレクトリをmicに転送し、実行する。
  5. 問題セットを変更したい場合は、data/list-intel.txtを変更する。


また、main.binを始めとする副生成物を削除したい場合は、
```
make clean
```
を実行してください。

自分のリポジトリとの結合
----
別にリポジトリを自分で作ってしまって、mymulmat.(cpp|h)をシンボリックリンクに置き換えてしまうのが手軽でよいと思います。

テスト
----
適当なデータセットでプログラムを走らせ、WRONGが0であればそのデータセットにおいてテストが通っていると言えます。

測定
----
正式な競技内容に関しては検討中です。
詳細が決まるのをお待ちください。

結果の参照
----
測定結果をうまく表示するためのシステムを用意しようと考えています。
実装をお待ちください。

作者
----
Makoto Shimazu <shimazu@eidos.ic.i.u-tokyo.ac.jp>
