$ER$DRY($X$FileType,$X$DDF,$X$Target)
$X$Application	->	$X$Mathematica
$Set($xlsx,$Import($X$Target))
$Set($sheet,$toPartitionSheet($X$DDF)($X$FileType)($xlsx))
$Export($`export.sheet,$FullForm($sheet),$`String)
