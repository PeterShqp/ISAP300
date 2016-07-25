/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    FS_TIME.C 
 *      Purpose: File System Time Support Functions
 *      Rev.:    V4.20
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2011 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <RTL.h>
#include <time.h>

/*----------------------------------------------------------------------------
 *      FS Time Functions
 *----------------------------------------------------------------------------
 *  Required functions for File System Time Support
 *   - U32 fs_get_time ()
 *   - U32 fs_get_date ()
 *---------------------------------------------------------------------------*/

/*--------------------------- fs_get_time -----------------------------------*/

U32 fs_get_time (void) {
  /* Return Current Time for FAT File Time stamp. */
  U32 h,m,s,time_r;

  /* Modify here, add a system call to read RTC. */
  /* Hours:   0 - 23 */
  /* Minutes: 0 - 59 */
  /* Seconds: 0 - 59 */
  struct tm* timeinfo;
  time_t rawtime;
  time(&rawtime);
  timeinfo = localtime(&rawtime);

  h = timeinfo->tm_hour;
  m = timeinfo->tm_min;
  s = timeinfo->tm_sec;

  time_r = (h << 16) | (m << 8) | s;
  return (time_r);
}


/*--------------------------- fs_get_date -----------------------------------*/

U32 fs_get_date (void) {
  /* Return Current Date for FAT File Time stamp. */
  U32 d,m,y,date;

  /* Modify here, add a system call to read RTC. */
  /* Day:   1 - 31 */
  /* Month: 1 - 12 */
  /* Year:  1980 - 2107 */
  struct tm* timeinfo;
  time_t rawtime;
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  d = timeinfo->tm_mday;
  m = timeinfo->tm_mon;
  y = timeinfo->tm_year;

  date = (y << 16) | (m << 8) | d;
  return (date);
}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
