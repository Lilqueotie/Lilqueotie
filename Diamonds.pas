program Diamonds;
uses SwinGame;

procedure FillDiamond(clr: Color; x, y: Single; width, height: Integer);
var
	midX, rightX, midY, bottomY: Single;
begin
	midX := x + width / 2;
	rightX := x + width;
	midY := y + height / 2;
	bottomY := y + height;
	
	FillTriangle(clr, x, midY, midX, y, rightX, midY);
	FillTriangle(clr, x, midY, midX, bottomY, rightX, midY);
end;

procedure DrawDiamond(clr: Color; x, y: Single; width, height: Integer);
var
	midX, rightX, midY, bottomY: Single;
begin
	midX := x + width / 2;
	rightX := x + width;
	midY := y + height / 2;
	bottomY := y + height;

	DrawLine(clr, x, midY, midX, y);
	DrawLine(clr, midX, y, rightX, midY);
	DrawLine(clr, rightX, midY, midX, bottomY);
	DrawLine(clr, midX, bottomY, x, midY);
end;

procedure Main();
begin
	OpenGraphicsWindow('Diamonds', 400, 400);
	LoadDefaultColors();

	ClearScreen(ColorWhite);
	
	FillDiamond(ColorRed, 0, 0, 100, 100);
	FillDiamond(ColorGreen, 350, 350, 50, 50);
	FillDiamond(ColorBlue, 300, 0, 100, 50);
	FillDiamond(ColorTeal, 250, 100, 75, 75);
	FillDiamond(ColorOrange, 250, 300, 50, 25);

	DrawDiamond(ColorRed, 200, 50, 100, 50);
	DrawDiamond(ColorGreen, 150, 350, 25, 25);
	DrawDiamond(ColorBlue, 150, 200, 150, 50);
	DrawDiamond(ColorTeal, 375, 50, 15, 15);
	DrawDiamond(ColorOrange, 75, 75, 50, 50);

	RefreshScreen();
	Delay(5000);
end;

begin
	Main();
end.