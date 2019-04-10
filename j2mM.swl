#!/usr/local/bin/math -script
s = Import["!tee","Text"];
ss = StringSplit[s,"\n"];
sss = Map[ImportString[#,"ExpressionJSON"]&,ss];
ssss = Map[StringReplace[{" "->""}][ToString[#]]&,sss];
out = StringReplace[{"{"->"{\n","}"->"\n}",", "->",\n"}][ToString[ssss]];
Print[out]
