#!/usr/bin/wolframscript -function
Function[
  StringReplace[{"{"->"{\n","}"->"\n}",", "->",\n"}][ToString[Map[ Function[StringReplace[" "->""][ToString[ImportString[#,"ExpressionJSON"]]]],StringSplit[Import[#1,"Text"],"\n"] ]]]
]
