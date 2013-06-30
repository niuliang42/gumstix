//--------------------------------------------------------------------------------------------------
//	Declare variables	
//   AD    																					
//--------------------------------------------------------------------------------------------------
//Return values of functions 
long	Ret, Ret2;
//Device name
char	DeviceName[256] = "AIO000";
//ID
short	m_Id;
//Error code string
char	ErrorString[256];
//Range
short	AiRange;
//Number of the used channels
short	m_AiChannels=4;
//Converted data
#define	DATA_MAX	16000
#define TIMES 100
float	AiData[DATA_MAX];
//The current number of samplings
long	AiSamplingCount;
//The current status
long	AiStatus;
//The number of samplings to be retrieved
long	AiSamplingTimes = TIMES;
float sum;
//----------------------   AD    	
AioInit (DeviceName, &m_Id);//caio init
AioResetDevice(m_Id);
AiRange = 0;/////////////////////////////////////////////////
AioSetAiRangeAll (m_Id, AiRange);
//Set the number of channels : 1 channel
m_AiChannels = 4;
AioSetAiChannels(m_Id, m_AiChannels);
//Set the memory type : FIFO
AioSetAiMemoryType(m_Id, 0);
//Set the clock type : Internal
AioSetAiClockType(m_Id, 0);
//Set the sampling clock : 1000 usec
AioSetAiSamplingClock(m_Id, 1000);
//Set the start condition : Software
AioSetAiStartTrigger(m_Id, 0);
//Set the stop condition : Converting has completed for the specified times
AioSetAiStopTrigger(m_Id, 0);
//Set the number of samplings : AiSamplingTimes
AioSetAiStopTimes(m_Id, AiSamplingTimes);

//RMS   

long Ret, AiStatus, AiSamplingCount;
Ret = AioResetAiMemory(m_Id);
Ret = AioStartAi(m_Id);
do
{
	AioGetAiStatus(m_Id, &AiStatus);
	AioGetAiSamplingCount(m_Id, &AiSamplingCount);
	//progressBarLeft.Value = AiSamplingCount * 10;
	//labelStatus.Text = AiSamplingCount.ToString();

} while ((AiStatus & AIS_BUSY)== AIS_BUSY);

// AiSamplingCount = AiSamplingTimes;
Ret = AioGetAiSamplingDataEx(m_Id,&AiSamplingCount, &AiData[0]);
//progressBarLeft.Value = AiSamplingCount * 10;
for (int j = 0; j < m_AiChannels; j++)//    RMS     
{
	rms[j] = 0.0f;
}
for (int i = 0; i < AiSamplingCount; i++)
{
	for (int j = 0; j < m_AiChannels; j++)
	{
		rms[j] += AiData[i * m_AiChannels + j] * AiData[i * m_AiChannels + j];
	}
}
for (int j = 0; j < m_AiChannels; j++)
{
	rms[j] = rms[j] / AiSamplingCount;
	rms[j] = (float)sqrt(rms[j]);
}
printf("rms[0] %f  rms[3] %f\n",rms[0],rms[3]);
//MessageBox(NULL,"Start!","Hint",MB_OK);

if(rms[1]>constRMS1)
{
	g_RotateX5-=5.0f;
	if(g_RotateX5<=-60) 
	  g_RotateX5=-60;
}
else
{
	g_RotateX5+=5.0f;
	if(g_RotateX5>=0) 
	  g_RotateX5=0;
}
