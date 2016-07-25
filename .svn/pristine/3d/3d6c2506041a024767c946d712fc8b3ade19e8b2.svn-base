/*
 * CLI_File_cmd_group.cpp
 *
 *  Created on: 2013-11-22
 *      Author: Administrator
 */

#include "CLI_File_cmd_group.h"
#include "s1l_cmds.h"
#include <fstream>
#include <iostream>
#include "TerminalUart.h"
#include <stdio.h>                    /* standard I/O .h-file                */
#include <ctype.h>                    /* character functions                 */
#include <string.h>                   /* string and memory functions         */
#include <stdlib.h>
#include "os.h"
#include "File_Config.h"
#include "lpc32xx_intc_driver.h"
#include "CCheckData.h"

extern char fileBuf[340736];

/*----------------------------------------------------------------------------
 *        Print size in dotted fomat
 *---------------------------------------------------------------------------*/
static void dot_format (U64 val, char *sp) {

  if (val >= (U64)1e9) {
    sp += sprintf (sp,"%d.",(U32)(val/(U64)1e9));
    val %= (U64)1e9;
    sp += sprintf (sp,"%03d.",(U32)(val/(U64)1e6));
    val %= (U64)1e6;
    sprintf (sp,"%03d.%03d",(U32)(val/1000),(U32)(val%1000));
    return;
  }
  if (val >= (U64)1e6) {
    sp += sprintf (sp,"%d.",(U32)(val/(U64)1e6));
    val %= (U64)1e6;
    sprintf (sp,"%03d.%03d",(U32)(val/1000),(U32)(val%1000));
    return;
  }
  if (val >= 1000) {
    sprintf (sp,"%d.%03d",(U32)(val/1000),(U32)(val%1000));
    return;
  }
  sprintf (sp,"%d",(U32)(val));
}

/********************************* type command ********************************************/
static BOOL_32 cmd_type(void);
static UNS_32 cmd_type_plist[] =
{
    (PARSE_TYPE_STR), /* The "type" command */
    (PARSE_TYPE_STR | PARSE_TYPE_END)
};
static CMD_ROUTE_T file_type_cmd =
{
    (UNS_8 *) "type",
    cmd_type,
    (UNS_8 *) "display the file's component",
    (UNS_8 *) "type [full path + file name]",
    cmd_type_plist,
    (CMD_ROUTE_E*)NULL
};

BOOL_32 cmd_type(void) {

    char* fname = (char*)cmd_get_field_val(1);

    std::ifstream in(fname);
    if( in ) {
        std::cout << in.rdbuf() << std::endl;
    }
    else {
        std::cout << fname << " no exist!" << std::endl;
    }
	return TRUE;
}
/********************************* type command end*****************************************/

/********************************* fload command ********************************************/
static BOOL_32 cmd_fload(void);
static UNS_32 cmd_fload_plist[] =
{
    (PARSE_TYPE_STR), /* The "type" command */
    (PARSE_TYPE_STR | PARSE_TYPE_END)
};
static CMD_ROUTE_T file_fload_cmd =
{
    (UNS_8 *) "fload",
    cmd_fload,
    (UNS_8 *) "display the file's component",
    (UNS_8 *) "fload [full path + file name]",
    cmd_fload_plist,
    (CMD_ROUTE_E*)NULL
};

BOOL_32 cmd_fload(void) {

    char* fname = (char*)cmd_get_field_val(1);
    int bytes = 0;
    std::cout << "Starting file load, send break to stop." << std::endl;
    bool loading = true;
    while ( loading ) {
        char c = getkey();
        if( term_break() ) {
            break;
        }
        fileBuf[bytes] = c;
        ++bytes;
    }
    std::cout << "File end of data. Start verify file CRC." << std::endl;
    int len = sizeof(fileBuf);
    uint32 crcResult = 0;
    CCheckData::CRCCheck1((uint8*)fileBuf, len-16, &crcResult);
    uint32 filecrc = (fileBuf[len-12] << 24) | (fileBuf[len-11] << 16) | (fileBuf[len-10] << 8) | (fileBuf[len-9] << 0);
    if( filecrc != crcResult ) {
        std::cout << "File load Failed!" << "count:" << bytes<< std::endl;
        return FALSE;
    }
    else {
        //std::ofstream out(fname, std::ios::binary);
//        out.write(fileBuf, len);
        FILE* out = fopen(fname, "wb");
//        tsk_lock();
        fwrite(fileBuf,1, len,out);
//        tsk_unlock();
        fclose(out);
        std::cout << "File load complete!" << "count:" << bytes<< std::endl;
    }
    return TRUE;
}
/********************************* fload command end*****************************************/

/********************************* dir command ********************************************/
static BOOL_32 cmd_dir(void);
static UNS_32 cmd_dir_plist[] =
{
    (PARSE_TYPE_STR | PARSE_TYPE_OPT), /* The "type" command */
    (PARSE_TYPE_STR | PARSE_TYPE_END)
};
static CMD_ROUTE_T file_dir_cmd =
{
    (UNS_8 *) "dir",
    cmd_dir,
    (UNS_8 *) "display the file's name",
    (UNS_8 *) "dir + mask\r\n"
                "\t* or *.* \tSearches for all files in the directory\r\n"
                "\tabc* \tSearches for files that begin with abc\r\n"
                "\t*.htm \tSearches for files that end with .htm\r\n"
                "\tabc*.text \tSearches for files that begin with abc and that end with .text\r\n",
    cmd_dir_plist,
    (CMD_ROUTE_E*)NULL
};

BOOL_32 cmd_dir(void) {

    U64 fsize;
    U32 files,dirs,i;
    char temp[32],*mask,ch;
    FINFO info;
    printf ("\nFile System Directory...");
    files = 0;
    dirs  = 0;
    fsize = 0;
    info.fileID  = 0;
    mask = "*.*";
    if( parse_get_entry_count() > 1 ) {
        mask = (char*)cmd_get_field_val(1);
    }

    while (ffind (mask,&info) == 0) {
      if (info.attrib & ATTR_DIRECTORY) {
        i = 0;
        while (strlen((const char *)info.name+i) > 41) {
          ch = info.name[i+41];
          info.name[i+41] = 0;
          printf ("\n%-41s", &info.name[i]);
          info.name[i+41] = ch;
          i += 41;
        }
        printf ("\n%-41s    <DIR>       ", &info.name[i]);
        printf ("  %02d.%02d.%04d  %02d:%02d",
                 info.time.day, info.time.mon, info.time.year,
                 info.time.hr, info.time.min);
        dirs++;
      }
      else {
        dot_format (info.size, &temp[0]);
        i = 0;
        while (strlen((const char *)info.name+i) > 41) {
          ch = info.name[i+41];
          info.name[i+41] = 0;
          printf ("\n%-41s", &info.name[i]);
          info.name[i+41] = ch;
          i += 41;
        }
        printf ("\n%-41s %14s ", &info.name[i], temp);
        printf ("  %02d.%02d.%04d  %02d:%02d",
                 info.time.day, info.time.mon, info.time.year,
                 info.time.hr, info.time.min);
        fsize += info.size;
        files++;
      }
    }
    if (info.fileID == 0) {
      printf ("\nNo files...");
    }
    else {
      dot_format (fsize, &temp[0]);
      printf ("\n              %9d File(s)    %21s bytes", files, temp);
    }
    dot_format (ffree(""), &temp[0]);
    if (dirs) {
      printf ("\n              %9d Dir(s)     %21s bytes free.\n", dirs, temp);
    }
    else {
      printf ("\n%56s bytes free.\n",temp);
    }
    return TRUE;
}
/********************************* dir command end*****************************************/


/********************************* fdelete command ********************************************/
static BOOL_32 cmd_fdelete(void);
static UNS_32 cmd_fdelete_plist[] =
{
    (PARSE_TYPE_STR), /* The "type" command */
    (PARSE_TYPE_STR | PARSE_TYPE_END)
};
static CMD_ROUTE_T file_fdelete_cmd =
{
    (UNS_8 *) "fdelete",
    cmd_fdelete,
    (UNS_8 *) "deletes a file",
    (UNS_8 *) "fdelete mask:\r\n"
                "\t* or *.* \tSearches for all files in the directory\r\n"
                "\tabc*     \tSearches for files that begin with abc\r\n"
                "\t*.htm    \tSearches for files that end with .htm\r\n"
                "\tabc*.cfg \tSearches for files that begin with abc and that end with .cfg\r\n",
    cmd_fdelete_plist,
    (CMD_ROUTE_E*)NULL
};

BOOL_32 cmd_fdelete(void) {

    char *fname;
    FINFO info;
    info.fileID  = 0;
    int files = 0;
    char* mask = (char*)cmd_get_field_val(1);

    while (ffind (mask,&info) == 0) {
        fname = (char*)info.name;
        if( fdelete(fname) == 0 ) {
            files++;
            printf("\nFile %s deleted.\n",fname);
        }
        else {
            printf("\nFile %s not found.\n",fname);
        }
    }
    printf ("\n              %9d File(s)    deleted.\n", files);
    return TRUE;
}
/********************************* fdelete command end*****************************************/

/****************command fformat start************************************************/
static BOOL_32 cmd_fformat(void);
static UNS_32 cmd_fformat_plist[] =
{
    (PARSE_TYPE_STR), /* The "fformat" command */
    (PARSE_TYPE_STR | PARSE_TYPE_END)
};
static CMD_ROUTE_T file_fformat_cmd =
{
    (UNS_8 *) "fformat",
    cmd_fformat,
    (UNS_8 *) "Format file system",
    (UNS_8 *) "fformat [driver:]",
    cmd_fformat_plist,
    (CMD_ROUTE_E*)NULL
};

BOOL_32 cmd_fformat(void) {
    char *driver = (char*) cmd_get_field_val(1);
    if (fformat("Keil") == 0) {
        printf("NAND Flash Formatted with label %s\n", "Keil");
    } else {
        printf("Formatting failed.\n");
    }

    return TRUE;

}
/****************command fformat end************************************************/

/*************** Debug group ******************************/
static GROUP_LIST_T group =
{
    (UNS_8 *) "file system", /* File group */
    (UNS_8 *) \
    "ISAP300 filesystem command group \n",
    (CMD_ROUTE_E*)NULL,
    (GROUP_LIST_E*)NULL
};

void CLI_file_add_commands(void) {
    /* Add core group */
    cmd_add_group(&group);

    /* Add commands to the core group */
    cmd_add_new_command(&group, &file_type_cmd);
    cmd_add_new_command(&group, &file_fload_cmd);
    cmd_add_new_command(&group, &file_dir_cmd);
    cmd_add_new_command(&group, &file_fdelete_cmd);
    cmd_add_new_command(&group, &file_fformat_cmd);

}//这里是对文件系统的调试命令
