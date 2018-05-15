#!/usr/local/bin/perl
#print @ARGV;
&RunPCA(@ARGV);
sub RunPCA{
        my ($matcol,$matrow,$matref,$descref) = @_;
        my $retstr = "$matcol $matrow\n";

        my @matarray = @{ $matref };
        my @descarray = @{ $descref };

        my $pcacmd = "echo \"@matarray\" \| " .
          "$conf->{bin}->{pca} $matrow $matcol $querydata{$conf->{frm}->{pca}}";
        open(PCA,"$pcacmd |") || return;

        my $rowcount = 0;
        while(<PCA>){
                $retstr .= $descarray[$rowcount] . ' ' . $_;
                $rowcount++;
        }
        close(PCA) || return; 
        
        return $retstr;
}

