
typedef struct keyword_
{
	char  * keyword;
	int state;
	int prev_state;
}keyword;

enum
{
	ENTRY_STATE,
	DISK_LAYOUT,
	DISK_LAYOUT_NAME,
	DISK_LAYOUT_DESCRIPTION,
	FILEEXT,
	FILESIZE,
	INTERFACE_MODE,
	DOUBLE_STEP,
	LAYOUT,
	NUMBEROFTRACK,
	NUMBEROFSIDE,
	FORMAT,
	NUMBEROFSECTOR,
	SECTORSIZE,
	INTERLEAVE,
	BITRATE,
	SKEW,
	SKEW_PER_TRACK,
	SKEW_PER_SIDE,
	GAP3,
	PREGAP,
	FORMATVALUE,
	RPM,
	SECTORIDSTART,
	TRACKLIST,
	TRACK,
	DATAOFFSET,
	FORMAT_TRACK,
	NUMBEROFSECTOR_TRACK,
	SECTORSIZE_TRACK,
	STARTSECTORID_TRACK,
	SECTORLIST,
	SECTOR,
	TRACKID_SECTOR,
	SIZEID_SECTOR,
	SECTORDATA_SECTOR,
	SECTORSIZE_SECTOR
};

keyword keyword_list[]=
{
	{"disk_layout",					DISK_LAYOUT,				ENTRY_STATE},
	{"disk_layout_name",			DISK_LAYOUT_NAME,			DISK_LAYOUT},
	{"disk_layout_description",		DISK_LAYOUT_DESCRIPTION,	DISK_LAYOUT},
	{"prefered_file_extension",		FILEEXT,					DISK_LAYOUT},
	{"file_size",					FILESIZE,					DISK_LAYOUT},
	{"interface_mode",				INTERFACE_MODE,				DISK_LAYOUT},
	{"double_step",					DOUBLE_STEP,				DISK_LAYOUT},
	{"layout",						LAYOUT,						DISK_LAYOUT},
	{"number_of_track",				NUMBEROFTRACK,				LAYOUT},
	{"number_of_side",				NUMBEROFSIDE,				LAYOUT},
	{"format",						FORMAT,						LAYOUT},
	{"bitrate",						BITRATE,					LAYOUT},
	{"sector_per_track",			NUMBEROFSECTOR,				LAYOUT},
	{"sector_size",					SECTORSIZE,					LAYOUT},
	{"interleave",					INTERLEAVE,					LAYOUT},
	{"skew",						SKEW,						LAYOUT},
	{"skew_per_track",				SKEW_PER_TRACK,				LAYOUT},
	{"skew_per_side",				SKEW_PER_SIDE,				LAYOUT},
	{"formatvalue",					FORMATVALUE,				LAYOUT},
	{"gap3",						GAP3,						LAYOUT},
	{"pregap",						PREGAP,						LAYOUT},
	{"rpm",							RPM,						LAYOUT},
	{"sectoridstart",				SECTORIDSTART,				LAYOUT},
	{"track_list",					TRACKLIST,					LAYOUT},
	{"track",						TRACK,						TRACKLIST},
	{"data_offset",					DATAOFFSET,					TRACK},
	{"format",						FORMAT_TRACK,				TRACK},
	{"sector_per_track",			NUMBEROFSECTOR_TRACK,		TRACK},
	{"sector_size",					SECTORSIZE_TRACK,			TRACK},
	{"start_sector_id",				STARTSECTORID_TRACK,		TRACK},
	{"sector_list",					SECTORLIST,					TRACK},
	{"sector",						SECTOR,						SECTORLIST},
	{"track_id",					TRACKID_SECTOR,				SECTOR},
	{"size_id",						SIZEID_SECTOR,				SECTOR},
	{"sector_data",					SECTORDATA_SECTOR,			SECTOR},
	{"sector_size",					SECTORSIZE_SECTOR,			SECTOR},
	{0,0,0}
};