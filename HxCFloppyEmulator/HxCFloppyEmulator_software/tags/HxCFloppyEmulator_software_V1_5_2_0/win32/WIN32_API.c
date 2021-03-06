/*
//
// Copyright (C) 2006, 2007, 2008, 2009 Jean-Fran?ois DEL NERO
//
// This file is part of HxCFloppyEmulator.
//
// HxCFloppyEmulator may be used and distributed without restriction provided
// that this copyright statement is not removed from the file and that any
// derivative work contains the original copyright notice and the associated
// disclaimer.
//
// HxCFloppyEmulator is free software; you can redistribute it
// and/or modify  it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// HxCFloppyEmulator is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//   See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HxCFloppyEmulator; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
*/
#include <windows.h>
#include <stdio.h>

#include "hxc_floppy_emulator.h"
#include "internal_floppy.h"
#include "..\common\usb_floppyemulator\usb_hxcfloppyemulator.h"

#include "win32_api.h"

HANDLE eventtab[256];


DWORD WINAPI ThreadProc( LPVOID lpParameter)
{
	threadinit *threadinitptr;
	THREADFUNCTION thread;
	HXCFLOPPYEMULATOR* floppycontext;
	HWINTERFACE* hw_context;

	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

	threadinitptr=(threadinit*)lpParameter;
	thread=threadinitptr->thread;
	floppycontext=threadinitptr->hxcfloppyemulatorcontext;
	hw_context=threadinitptr->hwcontext;
	thread(floppycontext,hw_context);

	return 0;
}



unsigned long  hxc_createevent(HXCFLOPPYEMULATOR* floppycontext,unsigned char id)
{
	eventtab[id]=CreateEvent(NULL,FALSE,FALSE,NULL);
	return (unsigned long)eventtab[id];
}

int hxc_setevent(HXCFLOPPYEMULATOR* floppycontext,unsigned char id)
{
	SetEvent(eventtab[id]);
	return 0;
}

int hxc_waitevent(HXCFLOPPYEMULATOR* floppycontext,int id,int timeout)
{
	int ret;

	if(timeout==0) timeout=INFINITE;
	ret=WaitForSingleObject(eventtab[id],timeout);

	if(ret==0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void hxc_pause(int ms)
{
	Sleep(ms);
}


int hxc_createthread(HXCFLOPPYEMULATOR* floppycontext,HWINTERFACE* hwcontext,THREADFUNCTION thread,int priority)
{
	DWORD sit;
	threadinit *threadinitptr;

	threadinitptr=malloc(sizeof(threadinit));
	threadinitptr->thread=thread;
	threadinitptr->hxcfloppyemulatorcontext=floppycontext;
	threadinitptr->hwcontext=hwcontext;

	CreateThread(NULL,8*1024,&ThreadProc,threadinitptr,0,&sit);

	return sit;
}

int getlistoffile(unsigned char * directorypath,unsigned char *** filelist)
{
	int numberoffile;
	char ** filepathtab;
	
	HANDLE findfilehandle;
	WIN32_FIND_DATA FindFileData;

	filepathtab=0;
	numberoffile=0;

	findfilehandle=FindFirstFile(directorypath,&FindFileData);
	if(findfilehandle!=INVALID_HANDLE_VALUE)
	{
		
		do
		{
			filepathtab=(char **) realloc(filepathtab,sizeof(char*)*(numberoffile+1));
			filepathtab[numberoffile]=(char*)malloc(strlen(FindFileData.cFileName)+1);
			strcpy(filepathtab[numberoffile],FindFileData.cFileName);
			numberoffile++;	
		}while(FindNextFile(findfilehandle,&FindFileData));
				
		FindClose(findfilehandle);
	}
	*filelist=filepathtab;

	return numberoffile;
}


char * getcurrentdirectory(char *currentdirectory,int buffersize)
{
	memset(currentdirectory,0,buffersize);
	if(GetModuleFileName(GetModuleHandle(NULL),currentdirectory,buffersize))
	{
		if(strrchr(currentdirectory,'\\'))
		{
			*((char*)strrchr(currentdirectory,'\\'))=0;
			return currentdirectory;
		}
	}

	return 0;
}

long find_first_file(char *folder,char *file,filefoundinfo* fileinfo)
{
	HANDLE hfindfile;
	char *folderstr;
	WIN32_FIND_DATA FindFileData;

	if(file)
	{
		folderstr=(char *) malloc(strlen(folder)+strlen(file)+2);
		sprintf((char *)folderstr,"%s\\%s",folder,file);
	}
	else
	{
		folderstr=(char *) malloc(strlen(folder)+1);
		sprintf((char *)folderstr,"%s",folder);
	}

	hfindfile=FindFirstFile(folderstr, &FindFileData); 
	if(hfindfile!=INVALID_HANDLE_VALUE)
	{
		sprintf(fileinfo->filename,"%s",FindFileData.cFileName);

		fileinfo->isdirectory=0;

		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			fileinfo->isdirectory=1;
		}
		
		fileinfo->size=FindFileData.nFileSizeLow;
		free(folderstr);
		return (long)hfindfile;
	}
	else
	{
		free(folderstr);
		return -1;
	}
	
return 0;
}

long find_next_file(long handleff,char *folder,char *file,filefoundinfo* fileinfo)
{
	WIN32_FIND_DATA FindFileData;
	long ret;

	ret=FindNextFile((HANDLE)handleff,&FindFileData);
	if(ret)
	{
		sprintf(fileinfo->filename,"%s",FindFileData.cFileName);

		fileinfo->isdirectory=0;

		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			fileinfo->isdirectory=1;
		}
		
		fileinfo->size=FindFileData.nFileSizeLow;
	}
	
	return ret;
}

long find_close(long handle)
{
	FindClose((void*)handle);
	return 0;
}


char * strupper(char * str)
{
	int i;
	
	i=0;
	while(str[i])
	{
	
		if(str[i]>='a' && str[i]<='z')
		{
			str[i]=str[i]+('A'-'a');
		}
		i++;
	}

	return str;
}


char * strlower(char * str)
{
	int i;
	
	i=0;
	while(str[i])
	{
	
		if(str[i]>='A' && str[i]<='Z')
		{
			str[i]=str[i]+('a'-'A');
		}
		i++;
	}

	return str;
}


