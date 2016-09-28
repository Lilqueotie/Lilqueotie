program CircleArea;
procedure Main();
var
cirRadius, cirArea: Single;
 roundedValue: Integer;
begin
 cirRadius := ReadInteger('Enter a radius: ');
 cirArea := Pi() * Sqr(cirRadius);
 WriteLn('Circles area is ', cirArea:4:2);
 roundedValue := Round(cirArea);
 WriteLn('Which rounded off has a value of ', roundedValue);
end;
begin
 Main();
end.