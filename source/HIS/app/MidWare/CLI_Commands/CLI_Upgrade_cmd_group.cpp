/*
 * CLI_Upgrade_cmd_group.cpp
 *
 *  Created on: 2013-12-23
 *      Author: Administrator
 */

#include "CLI_Upgrade_cmd_group.h"
#include "s1l_cmds.h"
#include "EZ_types.h"
#include "CBaseSlot.h"
#include "SlotModule.h"
#include "ObjectReference.h"
#include "CardTypeID_define.h"
#include "CardXC.h"
#include "ChipUOPTLogic.h"
#include <iostream>
#include <stdio.h>
#include "Lpc3250upload.h"
#include "Card24E1.h"
#include "SyncFileBakAPI.h"

/********************************* upgradefpga command ********************************************/
static BOOL_32 cmd_upgradefpga (void);
static UNS_32 cmd_upgrade_plist[] =
{
    (PARSE_TYPE_STR), /* The "upgradefpga" command */
    (PARSE_TYPE_DEC | PARSE_TYPE_OPT),
    (PARSE_TYPE_STR | PARSE_TYPE_OPT),
    (PARSE_TYPE_STR | PARSE_TYPE_END)
};
static CMD_ROUTE_T fpga_upgrade_cmd =
{
    (UNS_8 *) "upfpga",
    cmd_upgradefpga,
    (UNS_8 *) "upgrade the fpga by slot and file specified",
    (UNS_8 *) "upfpga [slot] [file]\r\n" \
              "\t\t[slot] 0~6 \r\n"             \
              "\t\t[file] file name for the fpga\r\n",
    cmd_upgrade_plist,
    (CMD_ROUTE_E*)NULL
};

BOOL_32 cmd_upgradefpga(void) {

    uint8 slot =  cmd_get_field_val(1);
    CBaseSlot* pslt = SlotModule::getSlot(slot);
    if( !pslt || !pslt->cardExist()) {
        std::cout << "!!!No Card!!!." << std::endl;
        return FALSE;
    }
    if( pslt->GetCardType() == XC_CARD_TYPEID ) {
        CardXC* pxc = ObjectReference::getPXCCard(slot);
        if( pxc ) {

            pxc->getChipUOPTLogic().updataTwoFPGA(true);
            return TRUE;
        }
    }
    else if( pslt->GetCardType() == E1_24_CARD_TYPEID ) {
        Card24E1* pe1 = ObjectReference::get24E1Card(slot);
        if( pe1 ) {
            return pe1->getChipE1Logic().updataFPGA();
        }
    }
    return FALSE;
}
/********************************* upgradefpga command end*****************************************/

/********************************* upgrademain command ********************************************/
static BOOL_32 cmd_upgrademain (void);
static UNS_32 cmd_upgrade_main_plist[] =
{
    (PARSE_TYPE_STR | PARSE_TYPE_OPT), /* The "type" command */
    (PARSE_TYPE_STR | PARSE_TYPE_END)
};
static CMD_ROUTE_T main_upgrade_cmd =
{
    (UNS_8 *) "upmain",
    cmd_upgrademain,
    (UNS_8 *) "upgrade the main by the file specified",
    (UNS_8 *) "upmain [file]\r\n" \
              "\t[file] : file name for the main\r\n",
    cmd_upgrade_main_plist,
    (CMD_ROUTE_E*)NULL
};

BOOL_32 cmd_upgrademain(void) {
    char* fname = "main.bit";
    if( parse_get_entry_count() > 1 ) {
        fname = (char*)cmd_get_field_val(1);
    }
    if( updata_main(fname) < 0 ) {
        std::cout << "!!!upgrade main failed!!!" << std::endl;
        return FALSE;
    }

    std::cout << "upgrade main successful!!" << std::endl;
    return TRUE;
}

/********************************* upgrademain command end*****************************************/

/********************************* send file command ********************************************/
static BOOL_32 cmd_sendfile (void);
static UNS_32 cmd_send_file_plist[] =
{
    (PARSE_TYPE_STR | PARSE_TYPE_OPT), /* The "sdfile" command */
    (PARSE_TYPE_STR | PARSE_TYPE_OPT),
    (PARSE_TYPE_STR | PARSE_TYPE_END)
};
static CMD_ROUTE_T send_file_cmd =
{
    (UNS_8 *) "sdfile",
    cmd_sendfile,
    (UNS_8 *) "send a file to bakup card.",
    (UNS_8 *) "sdfile [file] [rip]\r\n" \
              "\t[file] : file name for the transmited. It's optional. default main.bit\r\n"
              "\t[rip] : The ip that file send to. format xxx.xxx.xxx.xxx. It's optional. default Backup card ip.\r\n",
    cmd_send_file_plist,
    (CMD_ROUTE_E*)NULL
};

BOOL_32 cmd_sendfile(void) {
    char* fname = "main.bit";
    uint8 rip[4] = {0};
    if( parse_get_entry_count() > 1 ) {
        fname = (char*)cmd_get_field_val(1);
    }
    if( parse_get_entry_count() > 2 ) {
        char* s = (char*)cmd_get_field_val(2);
        std::string str(s);
        CPPTools::ezip_aton(str, rip);
        if( SyncFileBakAPI::putFileTo(fname, rip) ) {
            printf("file:%s send to backup card succeed.\n", fname);
            return TRUE;
        }
    }
    else {
        if( SyncFileBakAPI::putFileTo(fname) ) {
            printf("file:%s send to backup card succeed.\n", fname);
            return TRUE;
        }
    }
    return FALSE;
}

/********************************* send file command end*****************************************/

/********************************* get file command ********************************************/
static BOOL_32 cmd_getfile (void);
static UNS_32 cmd_get_file_plist[] =
{
    (PARSE_TYPE_STR ), /* The "sdfile" command */
    (PARSE_TYPE_STR ),
    (PARSE_TYPE_STR | PARSE_TYPE_END)
};
static CMD_ROUTE_T get_file_cmd =
{
    (UNS_8 *) "getfile",
    cmd_getfile,
    (UNS_8 *) "get a file from the server.",
    (UNS_8 *) "getfile [file] [rip]\r\n" \
              "\t[file] : The file name will get.\r\n"
              "\t[rip] : The ip that file get from. format xxx.xxx.xxx.xxx. \r\n",
    cmd_get_file_plist,
    (CMD_ROUTE_E*)NULL
};

BOOL_32 cmd_getfile(void) {
    char* fname = (char*)cmd_get_field_val(1);;
    uint8 rip[4] = {0};
    char* s = (char*)cmd_get_field_val(2);
    std::string str(s);
    CPPTools::ezip_aton(str, rip);
    if( SyncFileBakAPI::getFileFrom(fname, rip) ) {
        printf("file:%s send to backup card succeed.\n", fname);
        return TRUE;
    }
    return FALSE;
}

/********************************* get file command end*****************************************/

/*************** Debug group ******************************/
static GROUP_LIST_T group =
{
    (UNS_8 *) "upgrade", /* File group */
    (UNS_8 *) "ISAP300 upgrade command group",
    (CMD_ROUTE_E*)NULL,
    (GROUP_LIST_E*)NULL
};

void CLI_upgrade_add_commands(void) {
    /* Add core group */
    cmd_add_group(&group);

    /* Add commands to the core group */
     cmd_add_new_command(&group, &fpga_upgrade_cmd);
     cmd_add_new_command(&group, &main_upgrade_cmd);
     cmd_add_new_command(&group, &send_file_cmd);
     cmd_add_new_command(&group, &get_file_cmd);

}//�����������ӵ�main��������Ҫ�ĸ�������



