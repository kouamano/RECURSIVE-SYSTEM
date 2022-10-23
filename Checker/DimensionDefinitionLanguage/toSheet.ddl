$ER$DRY($X$FileType,$X$DDF,$X$Target)
$X$Application	->	$X$Mathematica
$X$Set($xlsx,$X$Import($X$Target))
$X$Set($sheet,$X$toPartitionSheet($X$DDF)($X$FileType)($xlsx))
$X$Export($`export.sheet,$X$FullForm($sheet),$`String)
