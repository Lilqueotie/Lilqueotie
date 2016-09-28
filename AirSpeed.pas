program AirSpeed;
uses TerminalUserInput;

function AirSpeedVelocity(frequency, amplitude : Double): Double;
	const STROUHAL_NUM = 0.33;
begin
	result := ((frequency * (amplitude/100))/ STROUHAL_NUM);
end;

procedure main();
begin
	WriteLn('African Swallow: ', AirSpeedVelocity(15,21):8:4, ' metres / sec');
	WriteLn('European Swallow: ', AirSpeedVelocity(14,22):8:4, ' metres / sec');
end;

begin
	main()
end.
//WriteLn('African Swallow: ', AirSpeedVelocity(15,21):8:4, ' metres / sec'