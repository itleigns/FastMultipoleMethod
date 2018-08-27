all: run measuretime measureerror
run: DimensionOneNormal.cpp DimensionOneSqrt.cpp DimensionOneLog.cpp DimensionOneLinear.cpp ToolForDimensionOne.cpp DimensionOneMain.cpp
	g++ -o run DimensionOneNormal.cpp DimensionOneSqrt.cpp DimensionOneLog.cpp DimensionOneLinear.cpp ToolForDimensionOne.cpp DimensionOneMain.cpp
measuretime: DimensionOneNormal.cpp DimensionOneSqrt.cpp DimensionOneLog.cpp DimensionOneLinear.cpp ToolForDimensionOne.cpp DimensionOneTime.cpp
	g++ -o measuretime DimensionOneNormal.cpp DimensionOneSqrt.cpp DimensionOneLog.cpp DimensionOneLinear.cpp ToolForDimensionOne.cpp DimensionOneTime.cpp
measureerror: DimensionOneNormal.cpp DimensionOneSqrt.cpp DimensionOneLog.cpp DimensionOneLinear.cpp ToolForDimensionOne.cpp DimensionOneCompare.cpp
	g++ -o measureerror DimensionOneNormal.cpp DimensionOneSqrt.cpp DimensionOneLog.cpp DimensionOneLinear.cpp ToolForDimensionOne.cpp DimensionOneCompare.cpp
clean:
	rm run measuretime measureerror