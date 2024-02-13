#include "sierrachart.h"

SCDLLName("TradingLockedText") 

SCSFExport scsf_Trading_Locked_Text(SCStudyInterfaceRef sc)
{
	SCSubgraphRef TextDisplay = sc.Subgraph[0];

	SCInputRef HorizontalPosition = sc.Input[0];
	SCInputRef VerticalPosition = sc.Input[1];
	SCInputRef DisplayInFillSpace = sc.Input[2];
	SCInputRef BoldFont = sc.Input[3];
    SCInputRef LockedText = sc.Input[4];
    SCInputRef TransparentBG = sc.Input[5];

	if (sc.SetDefaults)
	{
		// Set the configuration and defaults

		sc.GraphName = "Trading Locked Text";
		sc.AutoLoop = 0;
        sc.FreeDLL = 0;
		sc.GraphRegion = 0;

		TextDisplay.Name = "Text";
		TextDisplay.LineWidth = 10;
		TextDisplay.DrawStyle = DRAWSTYLE_CUSTOM_TEXT;
		TextDisplay.PrimaryColor = RGB(255, 0, 0); // Red
		TextDisplay.SecondaryColor = RGB(255, 255, 255);
		TextDisplay.SecondaryColorUsed = true;

		HorizontalPosition.Name = "Horizontal Position From Left (1-150)";
		HorizontalPosition.SetInt(130);
		HorizontalPosition.SetIntLimits(1, 150);

		VerticalPosition.Name = "Vertical Position From Bottom (1-100)";
		VerticalPosition.SetInt(97);
		VerticalPosition.SetIntLimits(1, 100);

		DisplayInFillSpace.Name = "Display in Fill Space";
		DisplayInFillSpace.SetYesNo(false);

		BoldFont.Name = "Used Bold Font";
		BoldFont.SetYesNo(true);

        sc.TextInputName = "Locked Text";
        sc.TextInput = "TRADING LOCKED";
        
        TransparentBG.Name = "Transparent Background";
        TransparentBG.SetYesNo(false);

		return;
	}

	// Do data processing
	if (sc.HideStudy) return; // Do nothing if study is hidden

	int& r_TextDrawingLineNumber = sc.GetPersistentInt(1);
    int& r_LineNumberTextDrawingLineNumber = sc.GetPersistentInt(2);  // Use another persistent int for line number

	s_UseTool Tool;

	Tool.Clear();
	Tool.ChartNumber = sc.ChartNumber;
	Tool.DrawingType = DRAWING_TEXT;
	Tool.TransparentLabelBackground = TransparentBG.GetBoolean();

	if (r_TextDrawingLineNumber != 0)
		Tool.LineNumber = r_TextDrawingLineNumber;

	if (!DisplayInFillSpace.GetYesNo())
		Tool.BeginDateTime = HorizontalPosition.GetInt();
	else
		Tool.BeginDateTime = -3;

	Tool.Region = sc.GraphRegion;
	Tool.BeginValue = (float)VerticalPosition.GetInt();
	Tool.UseRelativeVerticalValues = true;
	Tool.Color = TextDisplay.PrimaryColor;
	Tool.FontBackColor = TextDisplay.SecondaryColor;
	Tool.MultiLineLabel = true;
    Tool.AddAsUserDrawnDrawing = 1;

	if (BoldFont.GetYesNo())
		Tool.FontBold = true;
	else
		Tool.FontBold = false;

	// If trading is locked, then display the text
	if (sc.TradingIsLocked == 1)
	{
        Tool.Text = sc.TextInput.GetChars();
		Tool.FontSize = TextDisplay.LineWidth;
		Tool.AddMethod = UTAM_ADD_OR_ADJUST;
		Tool.ReverseTextColor = false;

		sc.UseTool(Tool);
		r_TextDrawingLineNumber = Tool.LineNumber;
	}
	else if (sc.TradingIsLocked == 0)
	{
        // If the text was previously drawn, delete it.
        if (r_TextDrawingLineNumber != 0)
        {
            sc.DeleteUserDrawnACSDrawing(sc.ChartNumber, r_TextDrawingLineNumber);   
            r_TextDrawingLineNumber = 0;  // Reset to indicate the drawing is no longer on the chart.
        }
        
    }
}