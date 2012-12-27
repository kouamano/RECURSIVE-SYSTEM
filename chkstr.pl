#!/usr/local/bin/perl
# Copyright (C)1995-2000 ASH multimedia lab. (http://ash.jp/)
#
# 文字コード判定処理
#

sub chk1st {
    my ($buf, $len) = @_;

# 文字種判定処理
#   buf: チェックデータ格納バッファ
#   len: チェックデータサイズ
# 返却値
#    0: ASCII
#    1: JIS
#    2: SJIS
#    3: EUC
#    4: Unknown(EUC/SJIS)
#   -1: Binary

    my $esc = 0; # 最終バイトの状態
    my $rtn = 0; # 返却値
    my ($c, $i);

    for ($i = 0; $i < $len; $i++) {
        $c = ord(substr($buf, $i, 1));

        if ($esc == 0) { # ESC以外
            if (($c >= 0x20) && ($c <= 0x7E)) {
                # ASCII
            } elsif (($c <= 0x06) || ($c == 0x7f) || ($c == 0xff)) {
                $rtn = -1; # Binary
                last;
            } elsif ($c == 0x1B) {
                $esc = 1; # ESC (1B)
                $rtn = 4; # Not ASCII
                next;
            } elsif (($c >= 0x07) && ($c <= 0x0d)) {
                # ctrl
            } elsif (($c >= 0x0e) && ($c <= 0x1F)) {
                $rtn = -1; # Binary
                last;
            } elsif ((($c >= 0x80) && ($c <= 0x8D))
                    || (($c >= 0x90) && ($c <= 0xA0))) {
                $rtn = 2; # SJIS
                last;
            } elsif ($c == 0xFE) {
                $rtn = 3; # EUC
                last;
            } else {
                $rtn = 4; # Not ASCII
            }

        } elsif ($esc == 1) { # ESC (1B)
            if ($c == 0x24) {
                $esc = 2; # ESC (1B 24)
            } elsif ($c == 0x28) {
                $esc = 3; # ESC (1B 28)
            } else {
                $esc = 0;
            }

        } elsif ($esc == 2) { # ESC (1B 24)
            $esc = 0;
            if (($c == 0x40) || ($c == 0x42)) {
                $rtn = 1; # JIS
                last;
            }

        } else { # ESC (1B 28)
            $esc = 0;
            if (($c == 0x42) || ($c == 0x49) || ($c == 0x4A)) {
                $rtn = 1; # JIS
                last;
            }
        }
    }

    if ($dbg) {printf("chk1st(buf, %d) rtn = %d\n", $len, $rtn);}

    return($rtn);
}


sub chkasc {
    my ($buf, $len) = @_;

# ASCIIコード判定処理
#   $buf: チェックデータ格納バッファ
#   $len: チェックデータサイズ
# 返却値
#    0: OK
#   -1: NG

    my $rtn; # 返却値
    my ($c, $i);

    $rtn = 0;

    for ($i = 0; $i < $len; $i++) {
        $c = ord(substr($buf, $i, 1));

        if (($c >= 0x07) && ($c <= 0x0d)) {
            # ctrl
        } elsif (($c >= 0x20) && ($c <= 0x7E)) {
            # ASCII
        } else {
            $rtn = -1;
            last;
        }
    }

    if ($dbg) {printf("chkasc(buf, %d) rtn = %d\n", $len, $rtn);}

    return($rtn);
}


sub chkjis {
    my ($buf, $len) = @_;

# JISコード判定処理
#   $buf: チェックデータ格納バッファ
#   $len: チェックデータサイズ
# 返却値
#   0000: ASCII
#   0001: JIS漢字
#   0010: JISカナ
#   0100: JIS漢字(NEC拡張外字)
#   1000: JIS漢字(機種依存)
#     -1: NG

    my $esc; # ESCの状態
    my $stat; # 最終バイトの状態
    my $kind; # 文字コードの状態
    my $rtn; # 返却値
    my ($c, $i);

    $rtn = 0; # ASCII
    $esc = 0;
    $stat = 0;
    $kind = 0;

    for ($i = 0; $i < $len; $i++) {
        $c = ord(substr($buf, $i, 1));

        if ($esc == 0) { # ESC以外
            if ($c == 0x1B) {
                $esc = 1; # ESC (1B)
                next;
            }

            if ($kind == 0) { # ASCII
                if (($c >= 0x07) && ($c <= 0x0d)) {
                    # ctrl
                } elsif (($c >= 0x20) && ($c <= 0x7E)) {
                    # ASCII
                } else {
                    $rtn = -1; # Not JIS
                    last;
                }
            } elsif ($kind == 1) { # JISカナ
                if (($c >= 0x21) && ($c <= 0x5F)) {
                    # JISカナ
                } else {
                    $rtn = -1; # Not JIS
                    last;
                }
            } else { # JIS漢字
                if ($stat == 0) { # 1バイト目
                    $stat = 1;
                    if (($c >= 0x21) && ($c <= 0x7E)) {
                        if (($c == 0x2D) || (($c >= 0x79) && ($c <= 0x7C))) {
                            $rtn = $rtn | 4; # JIS漢字(NEC拡張外字)
                        } elsif ((($c >= 0x29) && ($c <= 0x2F)) ||
                                   (($c >= 0x75) && ($c <= 0x7E))) {
                            $rtn = $rtn | 8; # JIS漢字(機種依存)
                        }
                    } else {
                        $rtn = -1; # Not JIS
                        last;
                    }
                } else { # 2バイト目
                    $stat = 0;
                    if (($c >= 0x21) && ($c <= 0x7E)) {
                        # JIS漢字
                    } else {
                        $rtn = -1; # Not JIS
                        last;
                    }
                }
            }

        } elsif ($esc == 1) { # ESC (1B)
            if ($c == 0x24) {
                $esc = 2; # ESC (1B 24)
            } elsif ($c == 0x28) {
                $esc = 3; # ESC (1B 28)
            } else {
                $rtn = -1; # Not JIS
                last;
            }

        } elsif ($esc == 2) { # ESC (1B 24)
            $esc = 0;
            if (($c == 0x40) || ($c == 0x42)) {
                $kind = 2; # JIS漢字
                $rtn = $rtn | 1; # JIS漢字
            } else {
                $rtn = -1; # Not JIS
                last;
            }

        } else { # ESC (1B 28)
            $esc = 0;
            if (($c == 0x42) || ($c == 0x4A)) {
                $kind = 0; # JISローマ字
            } elsif ($c == 0x49) {
                $kind = 1; # JISカナ
                $rtn = $rtn | 2; # JISカナ
            } else {
                $rtn = -1; # Not JIS
                last;
            }
        }
    }

    if ($dbg) {printf("chkjis(buf, %d) rtn = %02x\n", $len, $rtn);}

    return($rtn);
}


sub chksjis {
    my ($buf, $len) = @_;

# SJISコード判定処理
#   $buf: チェックデータ格納バッファ
#   $len: チェックデータサイズ
# 返却値
#   0000: ASCII
#   0001: JIS漢字
#   0010: JISカナ
#   0100: JIS漢字(NEC拡張外字)
#   1000: JIS漢字(機種依存)
#     -1: NG

    my $stat; # 最終バイトの状態
    my $rtn; # 返却値
    my ($c, $c1, $i);

    $rtn = 0; # ASCII
    $stat = 0;

    for ($i = 0; $i < $len; $i++) {
        $c = ord(substr($buf, $i, 1));

        if ($stat == 0) { # 文字の1バイト目
            if (($c >= 0x07) && ($c <= 0x0d)) {
                # ctrl
            } elsif (($c >= 0x20) && ($c <= 0x7E)) {
                # ASCII
            } elsif (($c >= 0xA1) && ($c <= 0xDF)) {
                $rtn = $rtn | 2; # JISカナ
            } elsif (($c >= 0x81) && ($c <= 0x9F)) {
                $stat = 1; # JIS漢字(81-9F)
                $c1 = $c;
                $rtn = $rtn | 1;
            } elsif (($c >= 0xE0) && ($c <= 0xEF)) {
                $stat = 2; # JIS漢字(E0-EF)
                $c1 = $c;
                $rtn = $rtn | 1;
            } else {
                $rtn = -1; # Not SJIS
                last;
            }

        } elsif ($stat == 1) { # JIS漢字(81-9F)の2バイト目
            if ((($c >= 0x40) && ($c <= 0x7E)) ||
                (($c >= 0x80) && ($c <= 0xFC))) {
                $stat = 0;
                if (($c1 == 0x87) && ($c < 0x9E)) {
                    $rtn = $rtn | 4; # JIS漢字(NEC拡張外字)
                } elsif (($c1 >= 0x85) && ($c1 <= 0x87)) {
                    $rtn = $rtn | 8; # JIS漢字(機種依存)
                } elsif (($c1 == 0x88) && ($c < 0x9E)) {
                    $rtn = $rtn | 8; # JIS漢字(機種依存)
                }
            } else {
                $rtn = -1; # Not SJIS
                last;
            }

        } else { # JIS漢字(E0-EF)の2バイト目
            if ((($c >= 0x40) && ($c <= 0x7E)) ||
                (($c >= 0x80) && ($c <= 0xFC))) {
                $stat = 0;
                if (($c1 >= 0xED) && ($c1 <= 0xEE)) {
                    $rtn = $rtn | 4; # JIS漢字(NEC拡張外字)
                } elsif (($c1 >= 0xEB) && ($c1 <= 0xEF)) {
                    $rtn = $rtn | 8; # JIS漢字(機種依存)
                }
            } else {
                $rtn = -1; # Not SJIS
                last;
            }
        }
    }

    if ($dbg) {printf("chksjis(buf, %d) rtn = %02x\n", $len, $rtn);}

    return($rtn);
}


sub chkeuc {
    my ($buf, $len, $stat) = @_;

# EUCコード判定処理
#   $buf:  チェックデータ格納バッファ
#   $len:  チェックデータサイズ
#   $stat: 最終バイトの状態
#     0: 文字の最後
#     1: JISカナの1バイト目
#     2: JIS漢字の1バイト目
# 返却値
#   0000: ASCII
#   0001: JIS漢字
#   0010: JISカナ
#   0100: JIS漢字(NEC拡張外字)
#   1000: JIS漢字(機種依存)
#     -1: NG

    my $rtn; # 返却値
    my ($c, $i);

    $rtn = 0; # ASCII
    $stat = 0;

    for ($i = 0; $i < $len; $i++) {
        $c = ord(substr($buf, $i, 1));

        if ($stat == 0) { # 文字の1バイト目
            if (($c >= 0x07) && ($c <= 0x0d)) {
                # ctrl
            } elsif (($c >= 0x20) && ($c <= 0x7E)) {
                # ASCII
            } elsif ($c == 0x8E) {
                $stat = 1; # JISカナ
                $rtn = $rtn | 2; # JISカナ
            } elsif (($c >= 0xA1) && ($c <= 0xFE)) {
                $stat = 2; # JIS漢字
                $rtn = $rtn | 1; # JIS漢字
                if (($c == 0xAD) || (($c >= 0xF9) && ($c <= 0xFC))) {
                    $rtn = $rtn | 4; # JIS漢字(NEC拡張外字)
                } elsif ((($c >= 0xA9) && ($c <= 0xAF)) ||
                           (($c >= 0xF5) && ($c <= 0xFE))) {
                    $rtn = $rtn | 8; # JIS漢字(機種依存)
                }
            } else {
                $rtn = -1;
                last;
            }

        } elsif ($stat == 1) { # JISカナの2バイト目
            if (($c >= 0xA1) && ($c <= 0xFE)) {
                $stat = 0;
            } else {
                $rtn = -1;
                last;
            }

        } else { # JIS漢字の2バイト目
            if (($c >= 0xA1) && ($c <= 0xFE)) {
                $stat = 0;
            } else {
                $rtn = -1;
                last;
            }
        }
    }

    if ($dbg) {printf("chkeuc(buf, %d) rtn = %02x\n", $len, $rtn);}

    return($rtn);
}


sub getcode {
    my ($buf, $len) = @_;

# 文字コード判定処理
#   $buf: チェックデータ格納バッファ
#   $len: チェックデータサイズ
# 返却値
#    0: ASCII
#    1: JIS
#    2: SJIS
#    3: EUC
#    4: Unknown (SJIS/EUC)
#   -1: Binary

    my $rtn; # 返却値
    my ($rtn_sjis, $rtn_euc);
    my $c;

    $rtn = chk1st($buf, $len);
    if ($rtn != 4) {goto end;}

    $rtn_sjis = chksjis($buf, $len);
    $rtn_euc  = chkeuc($buf, $len);

    if ($rtn_sjis >= 0) {
        if ($rtn_euc >= 0) {
            $rtn = 4; # Unknown (SJIS/EUC)
            if (!($rtn_sjis & 1)) { # 漢字なしの場合
                $rtn = 3; # EUC
            }
        } else {
            $rtn = 2; # SJIS
        }
    } else {
        if ($rtn_euc >= 0) {
            $rtn = 3; # EUC
        } else {
            $rtn = -1; # Binary
        }
    }
end:

    if ($dbg) {printf("getcode(buf, %d) rtn = %d\n", $len, $rtn);}

    return($rtn);
} 

1;
