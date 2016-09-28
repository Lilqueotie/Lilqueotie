program HelloUser;
uses TerminalUserInput;

procedure Main();
var
	name: String;
	age: Integer;
	year: Integer;
	yearborn: Integer;
begin
	name := ReadString('Please enter your name: ');
	age := ReadInteger('How old are you this year? :');
	year := ReadInteger('What year is it? :');
	yearborn := year - age;
	WriteLn('Hello,', name);
	WriteLn('you were born in ', yearborn)
end;

begin
	Main();
end.