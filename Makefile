all: run measuretime measureerror GenerateData.exe GenerateUnbalanceData.exe
run: DimensionOneNormal.cpp DimensionOneSqrt.cpp DimensionOneLog.cpp DimensionOneLinear.cpp DimensionOneForUnbalance.cpp ToolForDimensionOne.cpp DimensionOneMain.cpp
	g++ -o run DimensionOneNormal.cpp DimensionOneSqrt.cpp DimensionOneLog.cpp DimensionOneLinear.cpp DimensionOneForUnbalance.cpp ToolForDimensionOne.cpp DimensionOneMain.cpp
measuretime: DimensionOneNormal.cpp DimensionOneSqrt.cpp DimensionOneLog.cpp DimensionOneLinear.cpp DimensionOneForUnbalance.cpp ToolForDimensionOne.cpp DimensionOneTime.cpp
	g++ -o measuretime DimensionOneNormal.cpp DimensionOneSqrt.cpp DimensionOneLog.cpp DimensionOneLinear.cpp DimensionOneForUnbalance.cpp ToolForDimensionOne.cpp DimensionOneTime.cpp
measureerror: DimensionOneNormal.cpp DimensionOneSqrt.cpp DimensionOneLog.cpp DimensionOneLinear.cpp DimensionOneForUnbalance.cpp ToolForDimensionOne.cpp DimensionOneCompare.cpp
	g++ -o measureerror DimensionOneNormal.cpp DimensionOneSqrt.cpp DimensionOneLog.cpp DimensionOneLinear.cpp DimensionOneForUnbalance.cpp ToolForDimensionOne.cpp DimensionOneCompare.cpp
measuretimeforplot: DimensionOneNormal.cpp DimensionOneSqrt.cpp DimensionOneLog.cpp DimensionOneLinear.cpp DimensionOneForUnbalance.cpp ToolForDimensionOne.cpp DimensionOneTime.cpp
	g++ -D PLOT -o measuretimeforplot DimensionOneNormal.cpp DimensionOneSqrt.cpp DimensionOneLog.cpp DimensionOneLinear.cpp DimensionOneForUnbalance.cpp ToolForDimensionOne.cpp DimensionOneTime.cpp
GenerateData.exe: GenerateData.cs
	mcs GenerateData.cs
GenerateUnbalanceData.exe: GenerateUnbalanceData.cs
	mcs GenerateUnbalanceData.cs
clean:
	rm run measuretime measureerror measuretimeforplot GenerateData.exe result.dat duration.png
