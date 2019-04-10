#!/usr/local/bin/math -script
s = ToExpression[Import["!tee","Text"]];
ss = Map[ExportString[#,"ExpressionJSON"]&,s];
sss = Map[StringReplace[{" "->"","\t"->"","\n"->""}][#]&,ss];
out = StringReplace[{"{"->"","}"->"",", "->"\n"}][ToString[sss]];
Print[out]
