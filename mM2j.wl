#!/usr/bin/wolframscript -function
Function[Quiet[   StringReplace[{"{"->"","}"->"",", "->"\n"}][ToString[Map[StringReplace[{" "->"","\t"->"","\n"->""}][ExportString[#,"ExpressionJSON"]]&,Get[#1]]]]]   ]
