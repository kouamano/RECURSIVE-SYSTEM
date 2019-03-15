# tq.o, tconv
## 再帰処理の末端処理
現在、再帰ラッパーと処理関数を完全に分離している。
このため、末端のleaf-nodeにカッコのclose回数を計上している。   
 -> Add_Bclose_To_Next()   
この結果、いくつかの処理が、却って複雑化する。   
一方で、再帰関数と処理関数の統合を考える。
この場合は、それぞれの機能ごとの再帰関数を書くことになる。
いずれを選択するか、コードの複雑化およびパフォーマンスを吟味すべし。
### 上記にともまう副作用
特定レベルでのsuffix処理を困難にしている。
### 上記を回避したコード
ExFunction_Recursive_Ser_MultiPrint()関数を作成済みである。
問題はないはずだがテスト段階に留めてある。
## 構造管理
Cons-cellを用いているのでメモリー消費が大きい。
テーブル管理を試す。
現在cqをテストコード中
- cq.c
- C-structure.h
- C-functions.h
- C-functions_imex.h
ただし、T系のコードも必要となっている。
## エラートラップ
いくつかの場合でエラートラップできていない。
=> issue
## 実装予定機能
### ネットワーク(分散)対応
