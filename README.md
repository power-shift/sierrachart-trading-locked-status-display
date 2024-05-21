# Trading Locked Status Study for Sierra Chart

This extension for Sierra Chart displays a customizable text label on the chart, which can be used to indicate when trading is locked. The text display, position, style, and background can be easily configured the study's settings.

## Installation

1. Download the `TradingLockedStatus.cpp` file.
2. Place the .cpp file in the Sierra Chart/ACS_Source folder.
3. Compile the file in Sierra Chart by opening Analysis >> Build Custom Studies DLL >> Remote Build.
	
	Full instructions can be found [here](https://www.sierrachart.com/index.php?page=doc/HowToBuildAnAdvancedCustomStudyFromSourceCode.html).

4. Restart Sierra Chart to load the new DLL and add it to your chart from Analysis >> Studies >> Add Custom Study.

## Configuration

After installation, add the "Trading Locked Status" study to your chart:

- **Horizontal Position From Left (1-150):** Sets the horizontal position of the text from the left side of the chart. Default is 130.
- **Vertical Position From Bottom (1-100):** Sets the vertical position of the text from the bottom of the chart. Default is 97.
- **Display in Fill Space:** Option to control whether the text should be displayed in the fill space.
- **Use Bold Font:** Option to use a bold font for the text.
- **Locked Text:** The text to display when trading is locked. Default is "TRADING LOCKED".
- **Transparent Background:** Option to set the background of the text as transparent.

## Usage

The text will automatically display on the chart containing this study and based on the trading lock status from Trade >> Trading Locked.


## License

This extension is provided as-is without warranty. The user assumes all risks associated with its use in trading environments.