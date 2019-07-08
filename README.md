# tq
## 使用例
- Wolfram Languageに変換   
./tq.o in=test_prd.1.ddf out=test_prd.5.ddl data=test2.csv -FT -Pprod  -C  | ./tq.o in=/dev/stdin -Pin -FW
## TODO
- コードマージ    
  坂本さんのコードに最新版をマージ
  1. T-functionsをアップデート <= tq_base
  2. マージチェック
  3. fix
  4. tqコード比較・アップデート <= tq_base
- その他: issue : https://github.com/kouamano/RECURSIVE-SYSTEM/issues

## compile
```
cd DimensionDefinitionLanguage/
./compile_checker.sh
```

```
cd ../
compile-all.sh
```

## 実装予定機能
### Cons-cell -> 項テーブル管理
### ネットワーク(分散)対応
- MPI対応
- サーバー化
  - クライアントプログラム
### 辞書対応
- 項書き換え可能ルール検索
  - 直接的な項置き換え
  - similarなネットワークの置き替え

# チェッカー
./DimensionDefinitionLanguage/README
## compile
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
# README.exam も読むこと
## escape test
./tq.o in=test_escape.1.t -FT -Pin
./tq.o in=test_escape.2.t -FT -Pin
./tq.o in=test_escape.3.t -FT -Pin
./tq.o in=test_escape.4.t -FT -Pin

## single line
```
cd RECURSIVE-SYSTEM
- conv
bash conv-check.script
- head
while read line; do echo $line | ./tq.o in=/dev/stdin -FT -Pin ; done < test_head.t
- self-bind
echo '#1$1(#2$2(#3$3,$#1),$#3($#1,$#2))' | ./tq.o in=/dev/stdin -FT -Pin
 => #1$1(#2$2(#3$3,$#1@#1$1),$#3@#3$3($#1@#1$1,$#2@#2$2))
echo '#1$1(#2$2($#3,$#1[2]),#3$3($#1,$#2))' | ./tq.o in=/dev/stdin -FT -Pin data=test.csv
 => #1$1(#2$2($#3@#3$3,$#1[2]@#1$1@(Length,Weight)),#3$3($#1@#1$1,$#2@#2$2))
- data-bind
./tq.o in=test.ddf -FT out=test.ddl data=test.csv -Pin -Pout
  => $X$List($X$List($$X$Property[2]@(Length,Weight)),$X$List($$X$Unit[2]@(mm,kg)),$X$List[4]($$X$Real[2]@(1,2,322,4,5,68,7,81)))
$X$List($X$List($#1[],$#2[],$#3[]))
./tq.o in=test.ddf -Fst out=test.ddl data=test.csv -Pin -Pout
 OutのRefアドレスが取れているか確認する：
 => :Adr=36763216::SN=0::H=$X$List::D=(null)::nval=0::vstr=(null)::Pa=-1::Ref=0::LVs=0::Cj=0::LT=::Lb=-1::Cs=0::NCs=1::NC=3:
:Adr=36765440::SN=1::H=$X$List::D=(null)::nval=0::vstr=(null)::Pa=0::Ref=0::LVs=1::Cj=0::LT=::Lb=-1::Cs=0::NCs=1::NC=1:
:Adr=36766624::SN=2::H=#1$$X$Property[2]::D=[2::nval=2::vstr=Length,Weight::Pa=1::Ref=0::LVs=2::Cj=0::LT=h::Lb=1::Cs=2::NCs=1::NC=0:
:Adr=36767840::SN=3::H=$X$List::D=(null)::nval=0::vstr=(null)::Pa=0::Ref=0::LVs=1::Cj=1::LT=::Lb=-1::Cs=0::NCs=2::NC=1:
:Adr=36768992::SN=4::H=#2$$X$Unit[2]::D=[2::nval=2::vstr=mm,kg::Pa=3::Ref=0::LVs=2::Cj=0::LT=h::Lb=2::Cs=2::NCs=1::NC=0:
:Adr=36770208::SN=5::H=$X$List[4]::D=(null)::nval=0::vstr=(null)::Pa=0::Ref=0::LVs=1::Cj=1::LT=::Lb=-1::Cs=0::NCs=3::NC=1:
:Adr=36771360::SN=6::H=#3$$X$Real[2]::D=[4[2::nval=8::vstr=1,2,322,4,5,68,7,81::Pa=5::Ref=0::LVs=2::Cj=0::LT=h::Lb=3::Cs=2::NCs=1::NC=0:

:Adr=36773264::SN=0::H=$X$List::D=(null)::nval=0::vstr=(null)::Pa=-1::Ref=0::LVs=0::Cj=0::LT=::Lb=-1::Cs=0::NCs=1::NC=1:
:Adr=36773376::SN=1::H=$X$List::D=(null)::nval=0::vstr=(null)::Pa=0::Ref=0::LVs=1::Cj=0::LT=::Lb=-1::Cs=0::NCs=1::NC=3:
:Adr=36775760::SN=2::H=$#1[]::D=(null)::nval=0::vstr=(null)::Pa=1::Ref=36766624::LVs=2::Cj=0::LT=::Lb=-1::Cs=0::NCs=1::NC=0:
:Adr=36776912::SN=3::H=$#2[]::D=(null)::nval=0::vstr=(null)::Pa=1::Ref=36768992::LVs=2::Cj=1::LT=::Lb=-1::Cs=0::NCs=2::NC=0:
:Adr=36778064::SN=4::H=$#3[]::D=(null)::nval=0::vstr=(null)::Pa=1::Ref=36771360::LVs=2::Cj=1::LT=::Lb=-1::Cs=0::NCs=3::NC=0:

```

## multi line
```
./tq.o in=test-single.multi.t -Pin -FT 
```

## large tree performance: 42 sec; 22G mem @ N007
```
cd DimensionDefinitionLanguage
time ./tq.o in=lllarge-single-test.t buff=30
124653854 Nodes were operated.

real    0m41.609s
user    0m29.708s
sys     0m11.886s
```

### another test print json form: 1m14sec; 28G mem @ N007
```
time ./tq.o in=lllarge-single-test.t buff=30 -FJ -Pin > lllarge-single-test.json
124653854 Nodes were operated.

real    1m14.024s
user    0m56.709s
sys     0m17.296s
```

### compare to jq 36G
```
time cat lllarge-single-test.json | jq . > /dev/null
real    2m33.725s
user    2m13.524s
sys     0m21.406s

```


### large tree performance (2) ; 1m18sec; 41G mem @ N007
time ./tq.o in=lllarge-single-test_double.t buff=30
249307706 Nodes were operated.

### large tree performance (3) ; 1m47sec; 41G mem @ N007
time ./tq.o in=lllarge-single-test_double.t buff=30 -FT -Pin > /dev/null

### large tree performance (4) ; 2m33sec; 56G mem @ N007
time ./tq.o in=lllarge-single-test_double.t buff=30 -Pin -FJ > lllarge-single-test_double.json

### large tree performance (4) vs jq ; 4m43sec; 72G mem @ N007
time cat lllarge-single-test_double.json | jq . > /dev/null

### large-large tree performance (1): 2m37sec; 83G mem @ N007
time tq.o in=lllarge-single-test_dd.t buff=30
498615410 Nodes were operated.

## format conv
```
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
time ./tq.o in=lllarge-test.t

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
- test file : toSheet
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
