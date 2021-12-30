/*
//
// Copyright (C) 2006-2021 Jean-François DEL NERO
//
// This file is part of the HxCFloppyEmulator library
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
///////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//
//-----------H----H--X----X-----CCCCC----22222----0000-----0000------11----------//
//----------H----H----X-X-----C--------------2---0----0---0----0--1--1-----------//
//---------HHHHHH-----X------C----------22222---0----0---0----0-----1------------//
//--------H----H----X--X----C----------2-------0----0---0----0-----1-------------//
//-------H----H---X-----X---CCCCC-----222222----0000-----0000----1111------------//
//-------------------------------------------------------------------------------//
//----------------------------------------------------- http://hxc2001.free.fr --//
///////////////////////////////////////////////////////////////////////////////////
// File : streamConvert.c
// Contains: Flux (pulses) Stream conversion utility
//
// Written by: Jean-François DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include <math.h>

#include "types.h"

#include "internal_libhxcfe.h"
#include "tracks/track_generator.h"
#include "libhxcfe.h"

#include "floppy_loader.h"
#include "floppy_utils.h"
#include "tracks/trackutils.h"

#include "fluxStreamAnalyzer.h"

#include "libhxcadaptor.h"

#include "misc/env.h"


streamconv * initStreamConvert(HXCFE* hxcfe, HXCFE_SIDE * track, float stream_period_ps, float overflowvalue,int start_revolution,float start_offset,int end_revolution,float end_offset)
{
	streamconv * sc;
	int start_bitstream_pos;

	sc = malloc(sizeof(streamconv));
	if(sc)
	{
		memset(sc,0,sizeof(streamconv));

		sc->hxcfe = hxcfe;

		sc->stream_period_ps = stream_period_ps;
		sc->track = track;
		sc->overflow_value = overflowvalue;

		sc->bitstream_pos = 0;
		sc->old_index_state = track->indexbuffer[sc->bitstream_pos>>3];

		sc->end_revolution = end_revolution;
		sc->start_revolution = 0;
		sc->end_bitstream_pos = sc->track->tracklen-1;

		StreamConvert_setPosition(sc, start_revolution, start_offset);
		start_bitstream_pos = sc->bitstream_pos;

		hxcfe->hxc_printf(MSG_DEBUG,"initStreamConvert : tracklen : %d\n",sc->track->tracklen);

		sc->bitstream_pos = 0;
		sc->old_index_state = track->indexbuffer[sc->bitstream_pos>>3];

		StreamConvert_setPosition(sc, end_revolution, end_offset);
		sc->end_bitstream_pos = sc->bitstream_pos;
		sc->end_revolution = end_revolution;

		hxcfe->hxc_printf(MSG_DEBUG,"initStreamConvert : end_revolution : %d end_bitstream_pos: %d\n",sc->end_revolution,sc->end_bitstream_pos);

		sc->start_revolution = start_revolution;
		sc->start_bitstream_pos = start_bitstream_pos;

		sc->old_index_state = track->indexbuffer[sc->bitstream_pos>>3];
		sc->index_state = sc->old_index_state;

		hxcfe->hxc_printf(MSG_DEBUG,"initStreamConvert : start_revolution : %d start_bitstream_pos: %d\n",sc->start_revolution,sc->start_bitstream_pos);

		sc->index_event = 0;
		sc->stream_end_event = 0;

		sc->current_revolution = sc->start_revolution;
		sc->bitstream_pos = sc->start_bitstream_pos % sc->track->tracklen ;


	}

	return sc;
}

uint32_t StreamConvert_search_index(streamconv * sc, int index)
{
	int current_index;

	sc->bitstream_pos = 0;

	current_index = 0;

	do
	{
		while(!sc->index_event && !sc->stream_end_event)
		{
			StreamConvert_getNextPulse(sc);
		}

		if(sc->index_event)
		{
			current_index++;
		}

	}while((current_index<index) && !sc->stream_end_event);

	if(sc->stream_end_event)
		return 0;
	else
		return 1;
}

uint32_t StreamConvert_moveOffset(streamconv * sc, float offset)
{
	float totaltime;

	totaltime = 0;

	if(offset >= 0)
	{
		while( (totaltime <= offset) && !sc->stream_end_event )
		{
			if(sc->track->timingbuffer)
			{
				totaltime += ((float)(1000*1000*1000) / (float)(sc->track->timingbuffer[sc->bitstream_pos>>3]*2));
			}
			else
			{
				totaltime += ((float)(1000*1000*1000) / (float)(sc->track->bitrate*2));
			}

			sc->bitstream_pos++;
		}

		if(!sc->stream_end_event)
			return 1;
		else
			return 0;
	}
	else
	{
		while( (totaltime <= (-offset) ) && sc->bitstream_pos )
		{
			if(sc->track->timingbuffer)
			{
				totaltime += ((float)(1000*1000*1000) / (float)(sc->track->timingbuffer[sc->bitstream_pos>>3]*2));
			}
			else
			{
				totaltime += ((float)(1000*1000*1000) / (float)(sc->track->bitrate*2));
			}

			sc->bitstream_pos--;
		}

		if(sc->bitstream_pos)
			return 1;
		else
			return 0;
	}
}

uint32_t StreamConvert_setPosition(streamconv * sc, int revolution, float offset)
{
	sc->current_revolution = 0;

	if(StreamConvert_search_index(sc, revolution))
	{
		return StreamConvert_moveOffset(sc, offset);
	}

	return 0;
}

uint32_t StreamConvert_getNextPulse(streamconv * sc)
{
	int i,startpoint;
	unsigned char tmp_byte;
	float totaltime;

	sc->rollover = 0x00;
	sc->index_event = 0;

	if(sc->track->timingbuffer)
	{
		totaltime = ((float)(1000*1000*1000) / (float)(sc->track->timingbuffer[sc->bitstream_pos>>3]*2));
	}
	else
	{
		totaltime = ((float)(1000*1000*1000) / (float)(sc->track->bitrate*2));
	}

	startpoint = sc->bitstream_pos % sc->track->tracklen;
	i=1;
	do
	{
		sc->bitstream_pos++;

		if( sc->bitstream_pos >= sc->track->tracklen )
		{
			sc->current_revolution++;
			sc->bitstream_pos = (sc->bitstream_pos % sc->track->tracklen);
			sc->rollover = 0xFF;
		}

		if( sc->current_revolution >= sc->end_revolution )
		{
			if( sc->bitstream_pos >= sc->end_bitstream_pos )
			{
				sc->stream_end_event = 1;
				//return 1;
			}
		}

		if( startpoint == sc->bitstream_pos ) // starting point reached ? -> No pulse in this track !
		{
			sc->rollover = 0x01;
			return  (uint32_t)((float)totaltime/(float)(sc->stream_period_ps/1000.0));
		}

		// Overflow...
		if(totaltime >= sc->overflow_value)
		{
			return sc->overflow_value-1;
		}

		sc->index_state = sc->track->indexbuffer[sc->bitstream_pos>>3];
		if(sc->index_state && !sc->old_index_state)
		{
			sc->index_event = 1;
		}
		sc->old_index_state = sc->index_state;

		if(sc->track->flakybitsbuffer)
		{
			tmp_byte =  (sc->track->databuffer[sc->bitstream_pos>>3] & (0x80 >> (sc->bitstream_pos & 7) )) ^ \
						( ( sc->track->flakybitsbuffer[sc->bitstream_pos>>3] & (rand() & 0xFF) ) & (0x80 >> (sc->bitstream_pos & 7) ));
		}
		else
		{
			tmp_byte = (sc->track->databuffer[sc->bitstream_pos>>3] & (0x80 >> (sc->bitstream_pos & 7) ));
		}

		if( tmp_byte )
		{
			return (int)((float)totaltime/(float)(sc->stream_period_ps/1000.0));
		}
		else
		{
			i++;

			if(sc->track->timingbuffer)
			{
				totaltime += ((float)(1000*1000*1000) / (float)(sc->track->timingbuffer[sc->bitstream_pos>>3]*2));
			}
			else
			{
				totaltime += ((float)(1000*1000*1000) / (float)(sc->track->bitrate*2));
			}
		}
	}while(1);
}

void deinitStreamConvert(streamconv * sc)
{
	if(sc)
		free(sc);
}

