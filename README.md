# tq
## compile
cd RECURSIVE-SYSTEM
compile_all.sh
## 再帰処理
再帰ラッパーと処理関数を完全に分離している。
再帰ラッパーが若干複雑である。
## 構造管理
Cons-cellを用いているのでメモリー消費が大きい。
テーブル管理を試す。
## エラートラップ
いくつかの場合でエラートラップできていない。
=> issue
## 実装予定機能
### Cons-cell -> 項テーブル管理
### ネットワーク(分散)対応
- サーバー・クライアント
- デーモン化
### 辞書対応
- 項書き換え <= 文字列置換処理
- パス追加 <= 文字列置換処理を試す、難しければ木構造編集

#チェッカー
./DimensionDefinitionLanguage/README
##compile
cd DimensionDefinitionLanguage
compile_checker.n007.sh
## 言語
### t系
- t
- et
- eet
### s系
- s
- es
- ees

# convert test
```
cd RECURSIVE-SYSTEM
bash conv-check.script
./tq.o in=test.ddf -FT out=test.ddl data=test.csv
  => X$XList($X$List($$X$Property[2]@(Length,Weight)),$X$List($$X$Unit[2]@(mm,kg)),$X$List[4]($$X$Real[2]@(1,2,322,4,5,68,7,81)))
$X$List($X$List($#1[],$#2[],$#3[]))
cd DimensionDefinitionLanguage
bash conv-test.script
bash conv_e-test.script
bash conv_ee-test.script
bash check-example.script

tq.oの仕様変更により以下要調整
bash cat-example.script | ./tq.o -FT -Pin in=/dev/stdin > tmp
bash cat-example.script | ./tq.o -FT -Pin in=/dev/stdin | ./tq.o -FT in=/dev/stdin > tmp2
diff tmp tmp2
./tq.o in=single-test.t it=single -FT

```
## performance
### time: 80 sec.; mem in use:640Byte @ N007
### time: 55 sec.; mem in use:612Byte @ G005
time ./tq.o in=lllarge-test.t

### time: 1m 24sec.; mem in use:560Byte @ N007
time ./tq.o in=lllarge-test.t Sp=0,1

### time: 1m43sec.; mem in use:560Byte @ N007
time ./tq.o in=lllarge-test.t -FS > /dev/null

### time: 14 sec.; mem in use:520Byte @ N007
time ./tq.o in=llarge-test.t

### time: 20 sec. ; mem in use:570Byte @ N007
time ./tq.o in=llarge-test.t -FT > /dev/null

### time: 20 sec. ; mem in use:570Byte @ N007
time ./tq.o in=llarge-test.t -FN > /dev/null

### time: 75 sec. ; mem: 89G. @ N007 ; 13M nodes
time ./tq.o in=llarge-single-test.t -FT it=single > /dev/null
### 参考 jq 80 sec. ; mem: 17G @ N007 ; 11M nodes
time cat llarge-single-test.t.j | jq . > tmp.json
### 参考 mathematica 20 sec. ; mem: 4G @ N007
js=Import["llarge-test-single.t.j","JSON"];


# Federation
cd DimensionDefinitionLanguage
# test file : toSheet
{.tgt , .ddf , .dsz , .ddl} =cat=> .frl =tqR2D=> .frl.dry =tqD2F=> .frl.dry.fed =tqR2D=> .frl.dry.fed.com
## create FRL
./tq target=toSheet
## FRL => DRY 
./tqR2D.pl toSheet.frl > toSheet.frl.dry # => toSheet.frl.dry.fed.com
## DRY => FED
./tqD2F.pl toSheet.frl.dry # => toSheet.frl.dry.fed
## FED => EXEC
=> toSheet.frl.dry.fed.com
## EXEC
./toSheet.frl.dry.fed.com

## file transition
```
|file| +exec+
|tgt|  +cat+
|dsz|  +   + 
|ddf|  +   + 
|ddl|  +   + 
       +   +  |frl|  +tqR2D+ 
                     +     +                         |com|  +com+
                     +     +  |dry|  +tqD2F+                +   +
                                     +     +  |fed|         +   +
```
