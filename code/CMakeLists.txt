SET( LIBRARY_VERSION "0.1.0" )

SET( traglast_inc
)

SET( traglast_src
	Band.cpp
	Band.h
	BandOp.cpp
	BandOp.h
	CalcOption.cpp
	CalcOption.h
	Calculate.cpp
	Calculate.h
	ChildView.cpp
	ChildView.h
	DebugLogStream.cpp
	DebugLogStream.h
	Delmat.cpp
	Delmat.h
	Eigenschaften.cpp
	Eigenschaften.h
	Einzeleinwirkung.cpp
	Einzeleinwirkung.h
	Element.cpp
	ElementStack.h
	ElementWork.cpp
	ElementWork.h
	element_berechnen.cpp
	element_berechnen.h
	EnviromentServer.cpp
	EnviromentServer.h
	fem2d.h
	GUITextUtils.cpp
	GUITextUtils.h
	ILogStream.h
	images
	Inzidenz.cpp
	inzidenz.h
	IOperation.h
	ISolveStep.h
	IUpdate.cpp
	Koord.cpp
	Koord.h
	KoordWork.cpp
	KoordWork.h
	Lager.cpp
	Last.cpp
	Last.h
	LinAlg.cpp
	LinALg.h
	LocalizationObserver.cpp
	LocalizationObserver.h
	LocalizationObserverSubject.h
	LocalizationServer.cpp
	LocalizationServer.h
	Logger.cpp
	Logger.h
	MainFrm.cpp
	MainFrm.h
	Material.cpp
	MaterialWork.cpp
	MaterialWork.h
	MyMathDef.cpp
	mymathdef.h
	Node.h
	NodeStack.cpp
	NodeStack.h
	Observer.cpp
	Observer.h
	ObserverSubject.cpp
	ObserverSubject.h
	OSUtils.cpp
	OSUtils.h
	PlastCalcCtrl.cpp
	PlastCalcCtrl.h
	Plot.cpp
	resource.h
	StdAfx.cpp
	StdAfx.h
	Streckeneinwirkung.cpp
	Streckeneinwirkung.h
	Structure.cpp
	Structure.h
	SystemStiffnessBuilder.cpp
	SystemStiffnessBuilder.h
	Tragwerk.cpp
	TragwerkInfo.cpp
	TragwerkInfo.h
	TScale.h
	types.h
	vector.h
	Vektor.cpp
	Win_Traglast.cpp
	Win_Traglast.h
	Win_Traglast.rc
	wtErrorHandler.h
	wtlErrorHandler.cpp
)

ADD_LIBRARY( traglast SHARED
	${traglast_src}
)

target_link_libraries ( traglast )

