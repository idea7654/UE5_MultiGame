// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientSocket.h"
#include "..\Public\ClientSocket.h"

ClientSocket::ClientSocket(FString threadName) : StopTaskCounter(0)
{
	m_Kill = false;
	m_Pause = false;
	Thread = FRunnableThread::Create(this, *threadName, 0, TPri_BelowNormal);
}

ClientSocket::~ClientSocket()
{
	if (Thread)
	{
		delete Thread;
		Thread = nullptr;
		CloseSocket();
	}
}

void ClientSocket::PauseThread()
{
	m_Pause = true;
}

void ClientSocket::ContinueThread()
{
	m_Pause = false;
}

void ClientSocket::StopThread()
{
	Stop();
	if (Thread)
	{
		Thread->WaitForCompletion();
	}
}

bool ClientSocket::IsThreadPaused()
{
	return (bool)m_Pause;
}

bool ClientSocket::IsThreadKilled()
{
	return (bool)m_Kill;
}

bool ClientSocket::Init()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("ClientSocketInit"));
	UE_LOG(LogTemp, Warning, TEXT("ClientSocketInit"));
	return true;
}

uint32 ClientSocket::Run()
{
	FPlatformProcess::Sleep(0.03);
	while (StopTaskCounter.GetValue() == 0 && !m_Kill)
	{
		if (m_Pause)
		{
			if (m_Kill)
			{
				return 0;
			}
		}
		else
		{
			m_mutex.Lock();
			//Need synchronous processing

			m_mutex.Unlock();
			FPlatformProcess::Sleep(0.01);
		}
	}
	return 0;
}

void ClientSocket::Stop()
{
	StopTaskCounter.Increment();
	m_Kill = true;
	m_Pause = false;
}

bool ClientSocket::Begin()
{
	if (WSAStartup(MAKEWORD(2, 2), &mWsaData) != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("WSAStartup() Error"));
		return false;
	}

	mSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (mSocket == INVALID_SOCKET)
	{
		UE_LOG(LogTemp, Warning, TEXT("socket() Error"));
		return false;
	}
		
	memset(&mServerInfo, 0, sizeof(mServerInfo));
	mServerInfo.sin_family = AF_INET;
	mServerInfo.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
	mServerInfo.sin_port = htons(SERVER_PORT);

	return true;
}

bool ClientSocket::Connect()
{
	if (connect(mSocket, (SOCKADDR*)&mServerInfo, sizeof(mServerInfo)) == SOCKET_ERROR)
	{
		UE_LOG(LogTemp, Warning, TEXT("connect() Error"));
		return false;
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("connect"));

	return true;
}

bool ClientSocket::Recv()
{
	return false;
}

bool ClientSocket::Write(BYTE* data, DWORD dataLength)
{
	return false;
}

void ClientSocket::CloseSocket()
{
	closesocket(mSocket);
	WSACleanup();
}
