#include "CHexViewer.h"

SmitED::CHexViewer::CHexViewer()
	:pData(nullptr)
	, uiDataSize(0)
{
	memEdit = new MemoryEditor();
}

void SmitED::CHexViewer::update()
{
	begin();
	if (uiDataSize !=0)
		memEdit->DrawContents(pData, uiDataSize);
	end();
}

void SmitED::CHexViewer::SetData(std::string _sName, uint8_t* _pData, uint32_t _uiSize)
{
	sSelectedFilename = _sName;
	pData = _pData;
	uiDataSize = _uiSize;

	WindowName(sSelectedFilename);

	OnDataSet();
}
