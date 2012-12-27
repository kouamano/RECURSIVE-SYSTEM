#!/usr/local/bin/perl
# Copyright (C)1995-2000 ASH multimedia lab. (http://ash.jp/)
#
# 文字コードチェックコマンド
#

require "chkstr.pl";

$prog_name = '';
$dbg = 0;

&main(); # メイン処理

# 使用方法の表示
sub usage() {
    printf("Usage: %s [option] files\n", $prog_name);
    printf("  options: オプション\n");
    printf("    -a: ASCIIコードとしてチェック\n");
    printf("    -j: JISコードとしてチェック\n");
    printf("    -s: ShiftJISコードとしてチェック\n");
    printf("    -e: EUCコードとしてチェック\n");
    printf("    -d: 機種依存文字チェック\n");
    printf("  files: チェックファイル名\n");
    exit(-1);
}

# メイン処理
sub main {
    local $file_open;
    my ($mode, $code, $rtn);
    my ($file, $fp, @opt_data);

    # デフォルトパラメータの設定
    $prog_name = $0;
    $mode = 0; # 機種依存チェックモード
    $code = 3; # EUC

    # オプションの解析
    while ($#ARGV >= 0) {
        if ($ARGV[0] eq "-x") { # デバッグ情報表示
            $dbg = 1;
        } elsif ($ARGV[0] eq '-a') { # ascii code
            $code = 0;
        } elsif ($ARGV[0] eq '-j') { # jis code
            $code = 1;
        } elsif ($ARGV[0] eq '-s') { # sjis code
            $code = 2;
        } elsif ($ARGV[0] eq '-e') { # euc code
            $code = 3;
        } elsif ($ARGV[0] eq '-d') { # depend check mode
            $mode = 1;
        } elsif ($ARGV[0] eq '-x') { # debug mode
            $code = 3;
        } elsif ($ARGV[0] =~ /^-/) { # 使用方法の表示
            &usage();
        } else {
            last;
        }
        shift(@ARGV);
    }
    @opt_data = @ARGV;

    # 入力ファイルのオープン
    if (@opt_data) {
        foreach $file (@opt_data) {
            if (-d $file) {next;}

            printf ("%s:", $file);
            $file_open = "<$file";
            if (!open(FILE_IN, $file_open)) {
                printf("File open error.\n");
                next;
            }
            printf ("\n");
            &_chkcode($mode, $code, FILE_IN);
            close(FILE_IN);
        }

    } else { # 指定なしの場合、標準入力
        &_chkcode($mode, $code, STDIN);
    }
}

sub _chkcode {
    my ($mode, $code, $fp) = @_;
    my ($buf, $rtn, $len, $line);

    for ($line = 1; $buf = <$fp>; $line++) {
        chomp($buf);
        $len = length($buf);

        if ($code == 0) {
            $rtn = chkasc($buf, $len);
        } elsif ($code == 1) {
            $rtn = chkjis($buf, $len);
        } elsif ($code == 2) {
            $rtn = chksjis($buf, $len);
        } else {
            $rtn = chkeuc($buf, $len);
        }

        if ($rtn < 0) {
            printf("%08d: 不正文字 exists. (%d)\n", $line, $rtn);
            printf("%s\n", $buf);
        } elsif ($mode == 1) { # 機種依存チェック
            if ($rtn & 8) {
                printf("%08d: 機種依存文字 exists. (%d)\n", $line, $rtn);
                printf("%s\n", $buf);
            } elsif ($rtn & 4) {
                printf("%08d: NEC拡張外字 exists. (%d)\n", $line, $rtn);
                printf("%s\n", $buf);
            }
        }
    }
}
