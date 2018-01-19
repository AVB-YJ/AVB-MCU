#include "ipc_utils.h"
#include "crc8.h"

enum decode_step
{
   STEP_START = 0,
   STEP_LENGTH,
   STEP_DATA,
   STEP_CRC
};

struct ipc_data fact = {0, 0};

struct ipc_data* decode(unsigned char data)
{
    static struct ipc_data *silent;
    static unsigned char len, loc, crc;
    static unsigned char step = STEP_START;

    silent = &fact;
    switch ( step ) 
	{
    case STEP_START:
        if ( data == IPC_START ) 
		{
            len = 0;
			loc = 0;
			crc = 0;
			step++;
            silent = NULL;
        }
        break;
    case STEP_LENGTH:
        if ( data != IPC_START ) 
		{
            len = data;
            step++;
        }
        break;
    case STEP_DATA:
        silent->data[loc++] = data;
        crc = CRC8Table[crc ^ data];
        if ( ( ( loc & 7 ) == 0 ) || ( loc == len ) )
		{
            step++;
		}
        break;
    case STEP_CRC:
        if ( data == crc ) 
		{
            if ( loc == len ) 
			{
                step = STEP_START;
                silent = &fact;
                fact.len = len;
                return silent;
            } 
			else 
			{
                step--;
                crc = 0;
            }
        } 
		else 
		{
            step = STEP_START;
            silent->len = 0xff;//表示校验出现错误!
            /*
            silent->data[loc++] = data;
            crc = crc & 7;
            if ( crc == 0 )
                crc = 8;
            virturl_send ( silent->data + loc - crc, crc );
            */
            return silent;
        }
        break;
    }
	
    return NULL;
}

struct ipc_data* encode(const void* raw, unsigned char len)
{
    const char* data = raw;
    static struct ipc_data encode_data = {0, 0};
    //static int en_buf_len = 0;

    int i = 0;
    int crc_num = len / 8 + ( len % 8 > 0 ? 1 : 0 );
    int crc_index = 0;
    int all_len = 2 + len + crc_num;                        // all len of START, len, data and CRCs

    if ( !raw || len == 0 || len > 0xE2 ) 
	{
        return 0;
    }

    //en_buf_len = all_len;

    encode_data.data[0] = IPC_START;                        //START
    encode_data.data[1] = len;                              //len of the data

    for ( i = 0; i < len; i++ ) 
	{
        encode_data.data[2 + crc_index + i] = data[i]; //data

        if ( i % 8 == 7 ) 
		{
            encode_data.data[2 + crc_index + i + 1] = crc8 ( data + 8 * crc_index, 8 );             //CRC
            crc_index++;
        }
    }

    if ( crc_index < crc_num ) 	//last CRC
	{ 
        encode_data.data[2 + crc_index + i] = crc8 ( data + 8 * crc_index, len - 8 * crc_index );   //CRC
    }

    encode_data.len = all_len;

    return &encode_data;
}