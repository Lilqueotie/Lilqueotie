program PictureDrawing;
uses SwinGame, sgTypes;

begin
	OpenGraphicsWindow ('Drawing', 800, 600);
	
	ClearScreen(ColorLightBlue);
	FillEllipse(ColorGreen, 0, 450, 900, 300);
	FillEllipse(ColorForestGreen, -100, 400, 600, 250);
	
	FillEllipse(ColorSnow, 150, 100, 175, 100);
	FillEllipse(ColorSnow, 225, 100, 150, 125);
	
	FillEllipse(ColorSnow, 425, 150, 300, 150);
	FillEllipse(ColorSnow, 550, 150, 200, 125);

	FillRectangle(ColorRosyBrown, 200, 275, 75, 200);
	FillCircle(ColorForestGreen, 175, 200, 115);
	FillCircle(ColorForestGreen, 235, 190, 125);

	RefreshScreen(60);
	Delay(5000);
end.
