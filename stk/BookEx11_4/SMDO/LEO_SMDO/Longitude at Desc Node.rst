stk.v.9.0
WrittenBy    STK_v9.0.0

BEGIN ReportStyle

BEGIN ClassId
	Class		Satellite
END ClassId

BEGIN Header
	StyleType		0
	Date		Yes
	Name		Yes
	DescShort		No
	DescLong		No
	YLog10		No
	Y2Log10		No
	VerticalGridLines		No
	HorizontalGridLines		No
	AnnotationType		Spaced
	NumAnnotations		3
	NumAngularAnnotations		5
	AnnotationRotation		1
	BackgroundColor		#ffffff
	ViewableDuration		3600.000000
	RealTimeMode		No
	DayLinesStatus		1
	LegendStatus		1

BEGIN PostProcessor
	Destination	0
	Use	0
	Destination	1
	Use	0
	Destination	2
	Use	0
	Destination	3
	Use	0
END PostProcessor
	NumSections		1
END Header

BEGIN Section
	Name		Section 1
	ClassName		Satellite
	NameInTitle		No
	ExpandMethod		0
	PropMask		4610
	ShowIntervals		No
	NumIntervals		0
	NumLines		1

BEGIN Line
	Name		Line 1
	NumElements		2

BEGIN Element
	Name		Time
	IsIndepVar		Yes
	IndepVarName		Time
	Title		Time
	NameInTitle		No
	Service		AstrogatorPassData
	Type		Geodetic
	Element		Time
	SumAllowedMask		23
	SummaryOnly		No
	DataType		0
	UnitType		2
	LineStyle		0
	LineWidth		0
	LineColor		#000000
	PointStyle		0
	PointSize		0
	PointColor		#000000
	FillPattern		0
	FillColor		#000000
	PropMask		0
	UseScenUnits		Yes
END Element

BEGIN Element
	Name		Astrogator Pass Data-Geodetic-Longitude
	IsIndepVar		No
	IndepVarName		Time
	Title		Longitude
	NameInTitle		Yes
	Service		AstrogatorPassData
	Type		Geodetic
	Element		Longitude
	SumAllowedMask		23
	SummaryOnly		No
	DataType		0
	UnitType		3
	LineStyle		0
	LineWidth		0
	LineColor		#000000
	PointStyle		0
	PointSize		0
	PointColor		#000000
	FillPattern		0
	FillColor		#000000
	PropMask		0
	UseScenUnits		No
BEGIN Units
		DistanceUnit		Meters
		TimeUnit		Seconds
		DateFormat		EpochSeconds
		AngleUnit		Degrees
		MassUnit		Kilograms
		PowerUnit		Watts
		FrequencyUnit		Hertz
		SmallDistanceUnit		Meters
		LatitudeUnit		Radians
		LongitudeUnit		Radians
		DurationUnit		Seconds
		Temperature		Kelvin
		SmallTimeUnit		Seconds
		RatioUnit		Units
		RcsUnit		SquareMeters
		DopplerVelocityUnit		MetersperSecond
		SARTimeResProdUnit		Meter-Second
		ForceUnit		Newtons
		PressureUnit		Pascals
		SpecificImpulseUnit		Seconds
		PRFUnit		Hertz
		BandwidthUnit		Hertz
		SmallVelocityUnit		MetersperSecond
		Percent		UnitValue
		MissionModelerDistanceUnit		Meters
		MissionModelerTimeUnit		Seconds
		MissionModelerAltitudeUnit		Meters
		MissionModelerFuelQuantityUnit		Kilograms
		MissionModelerRunwayLengthUnit		Meters
		MissionModelerBearingAngleUnit		Radians
		MissionModelerAngleOfAttackUnit		Radians
		MissionModelerAttitudeAngleUnit		Radians
		MissionModelerGUnit		StandardSeaLevelG
		SolidAngle		Steradians
		MissionModelerTSFCUnit		TSFCKgSecN
		MissionModelerPSFCUnit		PSFCKgSecW
		MissionModelerForceUnit		Newtons
		MissionModelerPowerUnit		FlightWatt
		SpectralBandwidthUnit		Hertz
		BitsUnit		Bits
		MagneticFieldUnit		Tesla
END Units
END Element
END Line
END Section
END ReportStyle

