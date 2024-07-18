#ifndef __CPLAYER_H__
#define __CPLAYER_H__

#define TURN(x64) (DWORD)((uintptr_t)x64)
#define TmpLog(...)
class CPlayer
{
public:
	CPlayer();
	~CPlayer();
public:
	BOOL Open(LPCTSTR lpFileName);//���ļ�  
	BOOL Play(DWORD dwPos = 0);//����  
	BOOL Close();//�ر�  
	BOOL Stop();//ֹͣ  
	BOOL Pause();//��ͣ  
	BOOL Continue();//����  
	BOOL SetVolume(DWORD dSize);
	BOOL SetPos(DWORD dwPos);
	BOOL SetAudio(bool AudioOff);
	BOOL SetSpeed(DWORD Speed);
	DWORD GetLength();//��ȡ��������  
	BOOL GetError(LPTSTR pszText, UINT cchText);
	DWORD GetPos();
	void SetWindowHwnd(HWND hWnd);//���������ھ��  
private:
	MCI_OPEN_PARMS m_ciOpen;//���豸����  
	HWND m_hWnd;	//�����ھ��  
	DWORD m_dwFrom;	//������ʼ��
	MCIERROR m_dwError;
};



//#include "stdafx.h"
//#include "Player.h"
#include <digitalv.h>

#pragma comment(lib, "Winmm.lib")
#define _USER_MCI_COMMAND


CPlayer::CPlayer()
	: m_hWnd(nullptr)
	, m_dwFrom(0)
	, m_dwError(0)
{
	ZeroMemory(&m_ciOpen, sizeof(MCI_OPEN_PARMS));
}


CPlayer::~CPlayer()
{
	if (m_ciOpen.wDeviceID)///����д򿪵�MCI�豸�͹ر�  
		Close();
}

/// ���豸
BOOL CPlayer::Open(LPCTSTR lpFileName)
{
	TmpLog(__func__+(string)" "+lpFileName);
	TCHAR lpszShortPath[MAX_PATH] = { 0 };
	GetShortPathName(lpFileName, lpszShortPath, _countof(lpszShortPath));// ��ö�·��
#ifdef _USER_MCI_COMMAND
	if (m_ciOpen.wDeviceID)///����д򿪵�MCI�豸�͹ر�  
		Close();
	m_ciOpen.dwCallback = (DWORD) TURN(m_hWnd);
	TmpLog(__func__);
	m_ciOpen.lpstrDeviceType = NULL;
	m_ciOpen.lpstrElementName = lpszShortPath;///�����ļ�·��
	m_ciOpen.lpstrAlias = _T("MusicAlias");
	if (m_dwError = mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD) TURN(&m_ciOpen)))///���豸ʱ���豸��Ϊ0
	{
		TmpLog(__func__);
		return FALSE;
	}
	m_dwFrom = 0;
	return TRUE;
#else
	mciSendString(_T("Stop MusicAlias"), nullptr, 0, m_hWnd);
	TCHAR lpstrCommand[MAX_PATH * 2] = {};
	_stprintf_s(lpstrCommand, _T("Open %s Alias MusicAlias"), lpszShortPath);// MusicAlias ���豸����
	return !(m_dwError = mciSendString(lpstrCommand, nullptr, 0, m_hWnd));
#endif
}

/// ��������  
BOOL CPlayer::Play(DWORD dwPos)
{
	TmpLog(__func__);
	m_dwFrom = dwPos;
#ifdef _USER_MCI_COMMAND
	MCI_PLAY_PARMS mciplayparms;///���Ų����ṹ  	
	DWORD cdlen = GetLength();///�õ��ļ���С  
	mciplayparms.dwCallback = (DWORD) TURN(m_hWnd);
	mciplayparms.dwFrom = m_dwFrom;///������ʼλ��  
	mciplayparms.dwTo = cdlen;///������ֹλ��  
	if (m_ciOpen.wDeviceID != 0)///�ж��Ƿ���ļ�  
		return !(m_dwError = mciSendCommand(m_ciOpen.wDeviceID, MCI_PLAY, MCI_TO | MCI_FROM, (DWORD) TURN(&mciplayparms)));
	return FALSE;
#else
	return !(m_dwError = mciSendString(_T("Play MusicAlias"), nullptr, 0, m_hWnd));
#endif
}

/// ִ��MCI_CLOSE�������ر�MCI�豸  
BOOL CPlayer::Close()
{
	TmpLog(__func__);
#ifdef _USER_MCI_COMMAND
	if (m_ciOpen.wDeviceID)
		return !(m_dwError = mciSendCommand(m_ciOpen.wDeviceID, MCI_CLOSE, 0, 0));
	return FALSE;
#else
	return !(m_dwError = mciSendString(_T("Close MusicAlias"), nullptr, 0, m_hWnd));
#endif
}

/// ִ��MCI_STOP������ֹͣ��������  
BOOL CPlayer::Stop()
{
	TmpLog(__func__);
#ifdef _USER_MCI_COMMAND
	if (m_ciOpen.wDeviceID)
	{
		if (0 == mciSendCommand(m_ciOpen.wDeviceID, MCI_STOP, 0, 0))
			return !(m_dwError = mciSendCommand(m_ciOpen.wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, 0));///�Ѳ���λ���趨Ϊ�����ļ��Ŀ�ͷ����һ�β��Ų������ļ���ͷλ�ÿ�ʼ��  
	}
	m_dwFrom = 0;
	return FALSE;
#else
	return !(m_dwError = mciSendString(_T("Stop MusicAlias"), nullptr, 0, m_hWnd));
#endif
}

/// ִ��MCI_PAUSE��������ͣ�������� 
BOOL CPlayer::Pause()
{
	TmpLog(__func__);
#ifdef _USER_MCI_COMMAND
	if (m_ciOpen.wDeviceID)
	{
		DWORD dwsf = GetPos();
		m_dwFrom = MCI_MAKE_MSF(MCI_MSF_MINUTE(dwsf), MCI_MSF_SECOND(dwsf), MCI_MSF_FRAME(dwsf));
		return !(m_dwError = mciSendCommand(m_ciOpen.wDeviceID, MCI_PAUSE, 0, 0));
	}
	return FALSE;
#else
	return !(m_dwError = mciSendString(_T("Pause MusicAlias"), nullptr, 0, m_hWnd));
#endif
}

BOOL CPlayer::Continue()
{
	TmpLog(__func__);
#ifdef _USER_MCI_COMMAND
	MCI_PLAY_PARMS mciplayparms;///���Ų����ṹ  	
	DWORD cdlen = GetLength();///�õ��ļ���С  
	mciplayparms.dwCallback = (DWORD) TURN(m_hWnd);
	mciplayparms.dwTo = cdlen;///������ֹλ��  
	if (m_ciOpen.wDeviceID != 0)///�ж��Ƿ���ļ�  
		return !(m_dwError = mciSendCommand(m_ciOpen.wDeviceID, MCI_PLAY, MCI_TO, (DWORD) TURN(&mciplayparms)));
	return FALSE;
#else
	return !(m_dwError = mciSendString(_T("Play MusicAlias"), nullptr, 0, m_hWnd));
#endif
}

/// �õ��ļ���С  
DWORD CPlayer::GetLength()
{
	TmpLog(__func__);
#ifdef _USER_MCI_COMMAND
	MCI_STATUS_PARMS mcistatusparms;
	mcistatusparms.dwCallback = (DWORD) TURN(m_hWnd);
	mcistatusparms.dwItem = MCI_STATUS_LENGTH;
	mcistatusparms.dwReturn = 0;
	m_dwError = mciSendCommand(m_ciOpen.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD) TURN(&mcistatusparms));
	return mcistatusparms.dwReturn;/// ��λ�Ǻ��� mm
#else
	TCHAR sPosition[256];
	DWORD lLength;
	mciSendString(_T("Status MusicAlias length"), sPosition, 255, m_hWnd);
	lLength = _tcstol(sPosition, nullptr, 10);
	return lLength;/// ��λ�Ǻ��� mm
#endif
}

/// �õ��ļ�����λ��
DWORD CPlayer::GetPos()
{
	TmpLog(__func__);
#ifdef _USER_MCI_COMMAND
	MCI_STATUS_PARMS mcistatusparms;
	mcistatusparms.dwCallback = (DWORD) TURN(m_hWnd);
	mcistatusparms.dwItem = MCI_STATUS_POSITION;
	mcistatusparms.dwReturn = 0;
	m_dwError = mciSendCommand(m_ciOpen.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD) TURN(&mcistatusparms));
	return mcistatusparms.dwReturn;
#else
	TCHAR sPosition[256];
	DWORD lLength;
	mciSendString(_T("Status MusicAlias position"), sPosition, 255, m_hWnd);
	lLength = _tcstol(sPosition, nullptr, 10);
	return lLength;/// ��λ�Ǻ��� mm
#endif
}

void CPlayer::SetWindowHwnd(HWND hWnd)
{
	TmpLog(__func__);
	m_hWnd = hWnd;
}

/// �������� 0-100���ٷֱ�
BOOL CPlayer::SetVolume(DWORD dSize)
{
	TmpLog(__func__);
#ifdef _USER_MCI_COMMAND
	MCI_DGV_SETAUDIO_PARMS mciSetAudioPara;
	mciSetAudioPara.dwCallback = (DWORD) TURN(m_hWnd);
	mciSetAudioPara.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mciSetAudioPara.dwValue = dSize * 10; ///�˴�����������С (0--1000)
	return !(m_dwError = mciSendCommand(m_ciOpen.wDeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)TURN(&mciSetAudioPara)));
#else
	TCHAR lpstrCommand[32] = {};
	_stprintf_s(lpstrCommand, _T("setaudio MusicAlias volume to %ld"), dSize);
	return !(m_dwError = mciSendString(lpstrCommand, nullptr, 0, m_hWnd));
#endif
}

/// ���ý���
BOOL CPlayer::SetPos(DWORD dwPos)
{
	TmpLog(__func__);
	m_dwFrom = dwPos;
#ifdef _USER_MCI_COMMAND
	DWORD dwLength = GetLength();///�õ��ļ���С
	MCI_SEEK_PARMS Seek;
	Seek.dwCallback = (DWORD)TURN(m_hWnd);
	Seek.dwTo = dwPos;
	DWORD dwFlags = MCI_WAIT;
	if (dwPos > 0 && dwPos < dwLength)
		return !(m_dwError = mciSendCommand(m_ciOpen.wDeviceID, MCI_SEEK, MCI_WAIT | MCI_TO, (DWORD) TURN(&Seek)));
	else if (dwPos >= dwLength)
		return !(m_dwError = mciSendCommand(m_ciOpen.wDeviceID, MCI_SEEK, MCI_WAIT | MCI_SEEK_TO_END, 0));
	return !(m_dwError = mciSendCommand(m_ciOpen.wDeviceID, MCI_SEEK, MCI_WAIT | MCI_SEEK_TO_START, 0));
#else
	TCHAR lpstrCommand[32] = {};
	_stprintf_s(lpstrCommand, _T("seek MusicAlias to %ld"), dwPos);
	return !(m_dwError = mciSendString(lpstrCommand, nullptr, 0, m_hWnd));
#endif
}

/// ����TrueΪ������FALSEΪȡ������
BOOL CPlayer::SetAudio(bool AudioOff)
{
	TmpLog(__func__);
#ifdef _USER_MCI_COMMAND
	MCI_SET_PARMS setAudio;
	setAudio.dwCallback = (DWORD)TURN(m_hWnd);
	setAudio.dwTimeFormat = MCI_FORMAT_MILLISECONDS;
	setAudio.dwAudio = MCI_SET_AUDIO_ALL;
	DWORD dwFlags = MCI_SET_AUDIO;
	if (AudioOff)
		dwFlags |= MCI_SET_ON;
	else
		dwFlags |= MCI_SET_OFF;
	return !(m_dwError = mciSendCommand(m_ciOpen.wDeviceID, MCI_SET, dwFlags, (DWORD) TURN(&setAudio)));
#else
	if (AudioOff)
		return !(m_dwError = mciSendString(_T("setaudio MusicAlias off"), nullptr, 0, m_hWnd));
	else
		return !(m_dwError = mciSendString(_T("setaudio MusicAlias on"), nullptr, 0, m_hWnd));
#endif
}

/// ���ò����ٶ�1-100���ٷֱ�
BOOL CPlayer::SetSpeed(DWORD Speed)
{
	TmpLog(__func__);
#ifdef _USER_MCI_COMMAND
	MCI_DGV_SET_PARMS setSpeed;
	setSpeed.dwCallback = (DWORD)TURN(m_hWnd);
	//setSpeed.dwTimeFormat = MCI_FORMAT_MILLISECONDS;
	//setSpeed.dwAudio = MCI_SET_AUDIO_ALL;
	//setSpeed.dwFileFormat = 0;
	setSpeed.dwSpeed = Speed * 10;/// ���ò����ٶ�1-2000,1000Ϊ�����ٶ�
	DWORD dwFlags = MCI_DGV_SET_SPEED;
	return !(m_dwError = mciSendCommand(m_ciOpen.wDeviceID, MCI_SET, dwFlags, (DWORD) TURN(&setSpeed)));
#else
	TCHAR lpstrCommand[32] = {};
	_stprintf_s(lpstrCommand, _T("set MusicAlias speed %ld"), Speed);
	return !(m_dwError = mciSendString(lpstrCommand, nullptr, 0, m_hWnd));
#endif
}

/// ��ô�������
BOOL CPlayer::GetError(LPTSTR pszText, UINT cchText)
{
	return mciGetErrorString(m_dwError, pszText, cchText);
}
//from https://blog.csdn.net/u010682281/article/details/66473313
#endif
