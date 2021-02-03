#pragma once


// CMoeQApp:
// See MoeQ.cpp for the implementation of this class
//

class CMoeQApp : public CWinApp
{
public:
	CMoeQApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMoeQApp theApp;
