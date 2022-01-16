// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#pragma comment(lib, "ws2_32.lib")
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <windows.h>
#include <string>
#include "Runtime/Core/Public/HAL/Runnable.h"
/**
 * 
 */

#define MAX_BUFFER_LENGTH	1024
#define SERVER_PORT			9706
#define SERVER_IP			"127.0.0.1"

class MORPG_API ClientSocket : public FRunnable
{
public:
	ClientSocket(FString threadName);
	~ClientSocket();

	void PauseThread();
	void ContinueThread();
	void StopThread();

	bool IsThreadPaused();
	bool IsThreadKilled();

private:
	FRunnableThread*	Thread;
	FThreadSafeCounter	StopTaskCounter;
	FCriticalSection	m_mutex;

public:
	virtual bool	Init() override;
	virtual uint32	Run() override;
	virtual void	Stop() override;

public:
	bool Begin();
	bool Connect();
	bool Recv();
	bool Write(BYTE* data, DWORD dataLength);
	void CloseSocket();

private:
	char						mReadBuffer[MAX_BUFFER_LENGTH];
	char						mWriteBuffer[MAX_BUFFER_LENGTH];
	SOCKET						mSocket;
	SOCKADDR_IN					mServerInfo;
	WSADATA						mWsaData;
	class ABPlayerController*	PlayerController;

private:
	FThreadSafeBool m_Kill;
	FThreadSafeBool m_Pause;
};
