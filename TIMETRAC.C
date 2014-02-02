/******************************************************************************/
/*                       (c) IBM Canada Ltd. 1993                             */
/*                                                                            */
/* Program:     TIMETRAC - PM Activity Time Tracker                           */
/* Description: Tool to track the time spend on daily activity or tasks.      */
/*                                                                            */
/* Author : Enrico Zapanta                                                    */
/* Date   : 23Feb93                                                           */
/* Version: 1.0                                                               */
/*                                                                            */
/* History: 25Feb93  BETA  Beta release (V 0.1)                               */
/*          01Mar93  BETA  Beta release (V 0.2)                               */
/*          07Mar93  BETA  Beta release (V 0.3)                               */
/*                           Multi-threaded support                           */
/*                           Complete the report facility                     */
/*          13Mar93  V1.0  First release to OS2TOOLS                          */
/*          20Mar93  V1.1  Many new features:                                 */
/*                           Title includes activity code being tracked       */
/*                           Sort function (user sequence not yet done)       */
/*                           Alarm (reminder)                                 */
/*                           Hide/Show option in pop-up menu                  */
/*                           User defined exit, last item under File pulldown */
/*          24Mar93  V1.2  Changes include:                                   */
/*                           Add % to activity list                           */
/*                           Show hide character (#) and exclude+hide char    */
/*                             (%) in activity list                           */
/*                           Keyboard support (like Window List)              */
/*                           Right mouse click automatically selects code if  */
/*                             on valid position                              */
/*                           Change accelerator keys to be unique             */
/*                           Add % to report, make it only single column, add */
/*                             total time and units used. Required migration  */
/*                             of control files (MIGRREP.EXE)                 */
/*          26Mar93  V1.21 Fix bugs:                                          */
/*                           Error when adding code because of timing problem */
/*                             because totaltime used by other thread, use    */
/*                             fnAddTotal                                     */
/*                           Make dialog window keyboard support consistent   */
/*                           Fix keyboard enter                               */
/*                         Give focus back to original window when user reply */
/*                           of No to alarm reminder                          */
/*                         Use check mark on selected sort                    */
/*                         Add "Total" text and unit text to report, don't    */
/*                           show activity codes with 0 in report             */
/*          27Mar93  V1.22 Fix bug in fnGetActivityInfo, divide by 0.         */
/*          30Mar93  V1.3  New features:                                      */
/*                           Show TIMETRAC window if minimize when user       */
/*                             answers Yes to alarm reminder                  */
/*                           Save report during the day                       */
/*                           New time formats (hh:mm:ss and hh.mm.ss)         */
/*          20Apr93  V1.4  New features:                                      */
/*                           Report dialog boxes now modeless                 */
/*                           Use notebook control for all settings            */
/*                           Option to total several selected reports         */
/*                           Save reports automatically with new day          */
/*                           New alarm settings:                              */
/*                             - default application to track                 */
/*                             - allow user to change default alarm interval  */
/*                             - option to edit code when alarm expires       */
/*                           New report settings:                             */
/*                             - option to include or remove excluded/hidden  */
/*                                 codes from report                          */
/*                         Start TIMETRAC using /S option                     */
/*                         Put focus back on original window after user       */
/*                           double clicks to start tracking activity         */
/*                         Fix when TIMETRAC closed when minimized            */
/*          22Apr93  V1.41 Bug fixes:                                         */
/*                           Make the Continue push button the default push   */
/*                              push button in the Alarm Reminder pop-up      */
/*                           Set title correctly when using the /S option     */
/*                           Use listbox instead of MLE in report (so PgUp    */
/*                              and PgDn are automatically supported          */
/*                         New option:                                        */
/*                           Save to file during refresh                      */
/*          30Apr93  V1.5  New features:                                      */
/*                           Save report to file                              */
/*                           Show description in report (optional setting)    */
/*                           Counter for number of times activity code        */
/*                             started, also added to report                  */
/*                           Default sort support, no sort menu option        */
/*                           Transfer time from one activity to another       */
/*                           /P= (location of profile) and /D= (location of   */
/*                             data file) parameter options                   */
/*                           Option setting to minimize TIMETRAC when an      */
/*                             activity is started                            */
/*                         Bug fixes:                                         */
/*                           Fix when closing TIMETRAC when minimize, next    */
/*                              time TIMETRAC starts, will be minimized       */
/*                           Add Exclude and Add Hidden to report causes      */
/*                              incorrect total to be placed in report        */
/*                           Use MLE instead of listbox in report             */
/*                           Deleted activities shown in settings list and    */
/*                              are incorrectly added to report               */
/*          10May93  V1.51 Bug fixes:                                         */
/*                           Fix exit routine which causes activity codes to  */
/*                              be lost due to multi-threading problem        */
/*                           Fix keyboard focus problem                       */
/*                           Change Save report to Save data in File pull-down*/
/*          11May93  V1.52 Bug fixes:                                         */
/*                           Reset count to 0 for initial reset option.       */
/*                         New features:                                      */
/*                           Lockup option to automatically lock WPS          */
/*          18May93  V1.53 Bug fixes:                                         */
/*                           Reset time and count to 0 for autosave report    */
/*                         New features:                                      */
/*                           Allow to save report for another day             */
/*          11Jun93  V1.6  Bug fixes:                                         */
/*                           Transfer correct time without refreshing         */
/*                           Change accelerator keys to Ctrl-?                */
/*                           Sorted report list                               */
/*                           Improve Create data (now called Change data) win */
/*                         New features:                                      */
/*                           New settings for default startup activity        */
/*                           Modify report data for another day               */
/*                           Special window (no title, etc) option            */
/*          25Jun93  V1.61 Bug fixes:                                         */
/*                           Save data at midnight when exiting TIMETRAC      */
/*                              before first refresh                          */
/*                         New features:                                      */
/*                           Save pushbutton in Change Data window            */
/*                           Reset to 0 when nothing retrieved in Change data */
/*                           Grey out Stop menu item when not available.      */
/*                           Display Add window when double clicking          */
/*          30Jun93  V1.62 Compile using OS/2 ToolKit V2.1                    */
/*                         Strip blanks from window title                     */
/*                         Don't show reset message for same day              */
/*          13Aug93  V1.7  Bug fixes:                                         */
/*                           Problem with Use Hidden when last item is set    */
/*                              a hidden                                      */
/*                           Save correct window positions when TIMETRAC is   */
/*                              closed when minimized                         */
/*                         New features:                                      */
/*                           Add activity desciption to bottom status line    */
/*                              and Transfer dialog box                       */
/*                           Support for comments (TIMETRAC.CM)               */
/*                           New Confirmation setting "Reset for new day"     */
/*                           Sort by % and count, secondary sort support      */
/*                           Quick key (Ctrl-#) to start tracking activity    */
/*                           Use spin buttons for setting times               */
/*                           Invoke program when activity started             */
/*                           Allow user to customize fonts                    */
/*          16Aug93  V1.71 Bug fixes:                                         */
/*                           Increase stack/heap size in DEF file             */
/*                           Remove secondary sort (bug in sorting)           */
/*          20Aug93  V1.72 Bug fixes:                                         */
/*                           Description not shown in report for new added    */
/*                             code                                           */
/*                           Change fonts, right mouse button selection       */
/*                           Change accelerator for Fonts... to Ctrl-F        */
/*                           Fix secondary sort, add back to Sort menu        */
/*                           Delete flag lost when going into Settings        */
/*                           Fix several problems when there are no activities*/
/*                         New features:                                      */
/*                           Select focus title when starting activity code   */
/*          28Sep93  V1.73 Bug fixes:                                         */
/*                           Minor bug fix to default activity to start       */
/*                         New features:                                      */
/*                           Option to blank out all comments on new day      */
/*                           Restore window (if minimized) on startup         */
/*          26Jan94  V1.80 Bug fixes:                                         */
/*                           Problem with hidden codes and quick key          */
/*                           Back up TIMETRAC.LST once a day only             */
/*                           Report not saved correctly in new year           */
/*                           Restore window if minimized when given focus     */
/*                         New features:                                      */
/*                           Support for sub-activities (one level only)      */
/*                           Add count to transfer dialog                     */
/*                           Option to add hidden activity time to total time */
/*                           Accelerator key (Ctrl-U) for User Exit           */
/*          05Feb94  V1.82 Bug fixes:                                         */
/*                           Problem with total in Change data function       */
/*                           Trap when double clicking to Add when list empty */
/*                         New features:                                      */
/*                           Option to track current activity for alarm       */
/*                           Option to return to main list when starting a    */
/*                             sub-activity                                   */
/*                           Add 1 to count in Transfer dialog                */
/*          16Feb94  V1.83 Bug fixes:                                         */
/*                           Problems deleting last sub-activity              */
/*                           Fix trap when alarm expires tracking sub-activity*/
/*                         New features:                                      */
/*                           Allow to create a new report for previous date   */
/*          17Apr94  V1.9  Bug fixes:                                         */
/*                           Improve sub-activity report                      */
/*                         New features:                                      */
/*                           Allow parent-activity unique codes               */
/*                           Alarm time settable by activity                  */
/*                           Option for No focus change                       */
/*                           Sort report list in descending date order        */
/*                           Add date in status line                          */
/*                           Option to set Alarm Expiry time                  */
/*                           Collapse/Expand parent activities (+/-)          */
/*                           Moving bitmap in About                           */
/*          25Apr94  V1.91 Bug fixes:                                         */
/*                           Problem with Change data (sub-activities)        */
/*                           Edit activity, duplicate hotkey                  */
/*                           Problem with startup activity (sub-activities)   */
/*                           Alarm only shown once                            */
/*                         New features:                                      */
/*                           Double-click to collapse and expand              */
/*                           Option to show activities with 0 times in report */
/*                           Option to Automatically collapse (used to be     */
/*                             Return to Main list)                           */
/*                           Currently selected item remains selected and do  */
/*                             not scroll to top when activity tracked        */
/*          29Apr94  V1.92 Bug fixes:                                         */
/*                           Increase stack/heap size to 327680 in DEF file   */
/*                             to fix OS/2 2.0 trap                           */
/*                           Problem with default alarm activity setting      */
/*                           Prevent times > 999.99, display error message    */
/*                         New features:                                      */
/*                           Option for sub-activity list window type         */
/*          04May94  V1.93 Bug fixes:                                         */
/*                           Increase stack/heap size to 655360 in DEF file   */
/*                             to fix OS/2 2.0 trap                           */
/*                           Problem with alarm message timer when Continue   */
/*                             push button pressed                            */
/*                           Closing Settings will trap for new user          */
/*                         New features:                                      */
/*                           Ability to delete report                         */
/*          15May94  V1.94 Bug fixes:                                         */
/*                           Bug when Continue press in Alarm Message dialog. */
/*                           Do not change Alarm Interval setting when alarm  */
/*                             interval changed in Set Alarm Interval dialog. */
/*                           Ensure -0.00 is not shown.                       */
/*                         New features:                                      */
/*                           Print report (simple format and only to LPT1)    */
/*                           Combo boxes contain activities shows only valid  */
/*          01Aug94  1.94a Bug fixes:                                         */
/*                           Fix fnCalculateTime() when activity code and     */
/*                             parent are the same.                           */
/*                           Fix IDM_DEBUG processing.                        */
/*                           When refresh and no activity being tracked,      */
/*                             refresh list anyway.                           */
/*          28Aug94  1.95  Bug fixes:                                         */
/*                           Hotkey does not work for collapsed subactivity   */
/*                         Include hotkey number in list.                     */
/*                         3D status bar area.                                */
/*          31Aug94  1.96  Put parent in Alarm Message dialog box.            */
/*                         Do not close Report List window.                   */
/*          23Jan95  1.97  Bug fixes:                                         */
/*                           Deleting last report and last activity causes    */
/*                              TIMETRAC to hang (problem with sort routine)  */
/*                           Don't allow to transfer > activity time, avoid   */
/*                              negative times                                */
/*                           Deletion of multiple reports in Reports List     */
/*                           Update title when deleting activity being tracked*/
/*                           Fix Change Data problem with WARP, retrieve new  */
/*                              day                                           */
/*                           Total check box always checked in Report List    */
/*                         Save settings option                               */
/*          19Apr95  1.98  Bug fixes:                                         */
/*                           Fix fnSaveReport() for edited TT and CM, < 50    */
/*                           Display error message when save to file fails    */
/*                           Trap in Change Data when data not retrieved first*/
/*                         New command line parameters:                       */
/*                             /O=TIMETRAC.LST (control file)                 */
/*                             /R=TIMETRAC.TT (report file)                   */
/*                             /C=TIMETRAC.CM (comment file)                  */
/*                         Add reset to popup menu                            */
/*                         Allow two lines of notes to report                 */
/*                         Use System settings for date and time format       */
/*                         Remove Add Hidden to Total option                  */
/*                         Use listbox extended choice in Report List dialog  */
/*                         Add hh:mm time format                              */
/*                         Pad time spin buttons with leading 0s              */
/*                         Change default report days to save from 8 to 365   */
/*                                                                            */
/*          ddJul95  1.99  Bug fixes:                                         */
/*                           Parent cannot be the activity                    */
/*                                                                            */
/******************************************************************************/

#define INCL_WIN
#define INCL_BASE
#define INCL_DOS
#define INCL_GPI

#include <os2.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timetrac.h"                  /* main include file                   */
#include "timedlg.h"                   /* include file for dialog boxes       */

#define  DB_RAISED              0x0400 /* Used by WinDrawBorder()             */
#define  DB_DEPRESSED           0x0800

#define  PRTDEBUG 0                    /* set PRTDEBUG to 1 for debugging     */
#define  FOCUS    1                    /* set FOCUS to 0 for debugging        */

#define  IDMI_LOCKUPNOW         0x02C1 /* Message to lock up WPS              */

VOID fnFreeList();
VOID fnFreeReportList();
VOID fnPutLinkList( PACTINFO item );
VOID fnDeleteLinkList( PACTINFO delitem );
VOID fnPutReportLinkList( PREPINFO item );
VOID fnDeleteReportLinkList( PREPINFO delitem );
VOID fnProfileInfo( HAB hab, CHAR *profileDir);

APIRET fnGetActivityInfo( VOID );
VOID   fnPutActivityInfo( VOID );
APIRET fnSaveReport( BOOL newday, ULONG juldate, CHAR *outstring,
                     CHAR *coutstring, CHAR *filedate );

PACTINFO fnSelectItem( HAB hab, HWND hwnd, BOOL display );
VOID     fnProcessItem( HAB hab, HWND hwnd, PACTINFO curact, ULONG cxClient,
                        ULONG cyChar, BOOL putFile, ULONG *exFlag,
                        ULONG *colFlag );
VOID   fnAddEntryToListBox(PACTINFO item, PACTINFO selAct, PACTINFO topAct,
       LONG sel);
VOID   fnSort( VOID );
VOID   fnQuickKey( HWND hwnd, HWND hwndPopup, ULONG qkey, PACTINFO curact );
VOID   fnSortReport( ULONG sort );
VOID   fnSortSelect( HWND hwnd, ULONG sort );
VOID   fnSecSortSelect( HWND hwnd, ULONG secsort );
APIRET fnStartCommand( CHAR *szProgram, CHAR *szParms );
VOID   fnAddTotal( VOID );
VOID   fnCalculateTime( HAB hab, HWND hwnd, PACTINFO activity,
                        time_t starttime, ULONG xunits );
BOOL   fnCalJulDate( ULONG odate, ULONG ndate, ULONG diff );
BOOL   fnSelectActivity( HWND hwnd, HWND hwndPopup, CHAR *activity,
                         CHAR *parent, PACTINFO curact );
LONG   fnGetSelectedItem(HWND hwnd, LONG y, LONG cyClient, LONG cyChar);
PACTINFO fnGetLBoxActivity(LONG index);
VOID   fnToggleMenuItems(HWND hwnd, BOOL swtch);
#if PRTDEBUG
static FILE *wptr;
#endif

/******************************************************************************/
/*                                                                            */
/* Main routine: Standard PM mainline message queue processing.               */
/*                                                                            */
/******************************************************************************/
void main( int argc, char *argv[] )    /* main routine, optional argument is  */
                                       /* drive letter                        */
{

 HAB   hab;                            /* anchor block handle                 */
 HMQ   hmq;                            /* message queue handle                */
 QMSG  qmsg;                           /* PM message                          */
 CHAR  szHelpName [13];                /* filename of help file, ie. *.HLP    */
 CHAR  szChar2[2];
 CHAR  profileDir[80];
 RECTL rectlDesktop;                   /* rectangle structure                 */
 ULONG ulSize;                         /* size of SWP structure               */
 LONG  x;
 LONG  lLogoDisplay;                   /* number of seconds to display logo   */
 BOOL  windowSize;
 ULONG flFrameFlags;                   /* frame creation flags                */
 HELPINIT hiMain;                      /* help initialization structure       */

 strcpy(szBlank, "");
 fnPadString(szBlank, CODE_WIDTH);

#if PRTDEBUG
 wptr = fopen("TIMETRAC.DBG", "w");
#endif
 /* Process arguments - /S, /P and /D                                         */
 strcpy(startact, szBlank);
 strcat(startact, " ");
 strcat(startact, szBlank);
 profileDir[0]  = '\0';
 dataDir[0]     = '\0';
 Reportfile[0]  = '\0';
 Commentfile[0] = '\0';
 Outfile[0]     = '\0';
 if( argc > 1 )
 {
   for( x=1; x < argc; x++ )
   {
     strcpy( szText, argv[x]);         /* copy argument to work string        */
     fnToUpperString( szText );        /* convert to upper case               */

     if( szText[0] == '/' && szText[2] == '=' )
     {
       switch( szText[1] )
       {
         case( 'S' ):
           fnSubstr( szText, startact, 4, 2*CODE_WIDTH+1 );
           fnPadString(startact, 2*CODE_WIDTH+1);
           break;
         case( 'P' ):
           fnSubstr( szText, profileDir, 4, strlen(szText)-3 );
           break;
         case( 'D' ):
           fnSubstr( szText, dataDir, 4, strlen(szText)-3 );
           break;
         case( 'R' ):    // V1.98
           fnSubstr( szText, Reportfile, 4, strlen(szText)-3 );
           break;
         case( 'C' ):    // V1.98
           fnSubstr( szText, Commentfile, 4, strlen(szText)-3 );
           break;
         case( 'O' ):    // V1.98
           fnSubstr( szText, Outfile, 4, strlen(szText)-3 );
           break;
         default:
           break;
       }                               /* end switch                          */
     }                                 /* end if szText[0] == '='             */
   }                                   /* end if( x=1; i < argc ..            */
 }                                     /* end if arg > 1                      */

 start    = NULL;                      /* initialize link lists starting and  */
 last     = NULL;                      /* ending addresses                    */
 lastrep  = NULL;
 startrep = NULL;

 /* PM window initialization                                                  */

 hab = WinInitialize (0);              /* initialization procedures, PM and   */
 hmq = WinCreateMsgQueue (hab, 0);     /* application message queue           */

 fnProfileInfo(hab, profileDir);       /* Get save profile information        */

 /* Register all window classes                                               */

 WinRegisterClass (hab, szClientClass, wpClientWndProc, CS_SIZEREDRAW, 0);
 WinRegisterClass (hab, szNotebookClass, wpNBWndProc,   CS_SIZEREDRAW, 0);

 /* Query the system profile for the user-configured value of logo display    */
 /* time. If no time found, set default to indefinite (-1) display time. If   */
 /* non-zero, call dialog box to display the logo 'about' box.                */
 lLogoDisplay = PrfQueryProfileInt( HINI_PROFILE, "PM_ControlPanel",
                                    "LogoDisplayTime", -1L);
 iDate        = PrfQueryProfileInt( HINI_PROFILE, "PM_National",
                                    "iDate", 0);
 iTime        = PrfQueryProfileInt( HINI_PROFILE, "PM_National",
                                    "iTime", 0);
 PrfQueryProfileString( HINI_PROFILE, "PM_National", "sDate", "/", szChar2, 2);
 sDate = szChar2[0];
 PrfQueryProfileString( HINI_PROFILE, "PM_National", "sTime", ":", szChar2, 2);
 sTime = szChar2[0];

// sprintf(szText, "sDate: %c, sTime: %c, iDate: %d, iTime: %d",
//                 sDate, sTime, iDate, iTime);
// WinMessageBox (HWND_DESKTOP, 0L, szText, "Debug", 1,
//                MB_ERROR | MB_MOVEABLE | MB_OK );

 if (lLogoDisplay != 0)
   WinDlgBox (HWND_DESKTOP, 0L, wpAboutDlgProc,
              0L, IDD_ABOUT, (PVOID) &lLogoDisplay);

 /* Standard window creation. Get title bar text in resource string table.    */
 /* Position the window as desired based on Desktop. Finally, show it!        */

 if( smallwin == NORMAL_WINDOW )
   flFrameFlags = FCF_TITLEBAR | FCF_SYSMENU       | FCF_SIZEBORDER |
                  FCF_MINMAX   | FCF_SHELLPOSITION | FCF_TASKLIST   |
                  FCF_MENU     | FCF_ICON          | FCF_ACCELTABLE;
 else
   flFrameFlags = FCF_SIZEBORDER | FCF_SHELLPOSITION | FCF_TASKLIST |
                  FCF_ACCELTABLE;
 hwndFrame = WinCreateStdWindow( HWND_DESKTOP, 0L, &flFrameFlags,
                                 szClientClass, NULL, 0L, 0L,
                                 idFrameWindow, &hwndClient );

 windowSize = TRUE;
 ulSize = sizeof (SWP);
 if( PrfQueryProfileData( hini, szAppName, szWinPos, &swpWin, &ulSize ) )
 {
   if( swpWin.x >= 0 || swpWin.y >= 0 )
     windowSize = FALSE;
 }
 if( windowSize == TRUE )
 {                                     /* no profile data, use system default */
                                       /* window size and position            */
   WinQueryWindowRect (HWND_DESKTOP, &rectlDesktop);
   swpWin.x = rectlDesktop.xRight / 5;
   swpWin.y = rectlDesktop.yTop / 3;
   swpWin.cx = rectlDesktop.xRight * 2 / 3;
   swpWin.cy = rectlDesktop.yTop / 2;
#if PRTDEBUG
   fprintf(wptr, "DeskTop size is: %d %d %d %d\n", rectlDesktop.xRight,
           rectlDesktop.yTop, rectlDesktop.xLeft, rectlDesktop.yBottom);
   fprintf(wptr, "TIMETRAC size is: %d %d %d %d\n", swpWin.x, swpWin.y,
           swpWin.cx, swpWin.cy);
#endif
 }

 if( swpWin.fl & SWP_MINIMIZE )
   WinSetWindowPos (hwndFrame, HWND_TOP, swpWin.x, swpWin.y,
                    swpWin.cx, swpWin.cy,
                    SWP_SHOW | SWP_SIZE | SWP_MOVE | SWP_ACTIVATE |
                    SWP_MINIMIZE );
 else
 {
   WinSetWindowPos (hwndFrame, HWND_TOP, swpWin.x, swpWin.y,
                    swpWin.cx, swpWin.cy,
                    SWP_SHOW | SWP_SIZE | SWP_MOVE | SWP_ACTIVATE);
   WinShowWindow( hwndFrame, TRUE );
   WinSetActiveWindow( HWND_DESKTOP, hwndFrame );
 }

 /* Help manager initialization & preparation. Set up the HELPINIT structure  */
 /* Create help instance, if unable, display error message.                   */

 hiMain.cb = sizeof (HELPINIT);        /* Standard size of structure          */
 hiMain.ulReturnCode = 0L;             /* rc - if non-zero after -> error!    */
 hiMain.pszTutorialName = (PSZ)NULL;   /* tutorial program, if none, set NULL */
                                       /* Help table ID in resources          */
 hiMain.phtHelpTable = (PVOID)( 0xffff0000 | IDH_TABLE_MAIN );
 hiMain.hmodHelpTableModule = 0L;      /* Help not in DLL                     */
 hiMain.hmodAccelActionBarModule = 0L; /* No add'l help resources             */
 hiMain.idAccelTable = 0L;             /* No add'l help accelerator           */
 hiMain.idActionBar = 0L;              /* No add'l help menu                  */

 WinLoadString (hab, 0L, IDS_HELPTITLE, 50, szTitle);
 hiMain.pszHelpWindowTitle = szTitle;  /* Help manager window title           */

 hiMain.fShowPanelId = FALSE;             /* Don't show panel numbers         */

 WinLoadString (hab, 0L, IDS_HELPNAME, 13, szHelpName);
 hiMain.pszHelpLibraryName = szHelpName;  /* Name of .HLP file                */

 hwndHelp = WinCreateHelpInstance (hab, &hiMain); /* create help instance     */
 if (!hwndHelp)
    WinMessageBox (HWND_DESKTOP, 0L, szHelpName,
                   "Help Error", 1, MB_ERROR | MB_OK | MB_MOVEABLE);
 else
    if (hiMain.ulReturnCode)
       {
        WinMessageBox (HWND_DESKTOP, 0L, "Help not available!",
                       "Help Error", 1, MB_ERROR | MB_OK | MB_MOVEABLE);
        WinDestroyHelpInstance (hwndHelp);
        hwndHelp = 0L;
       }
    else
       WinAssociateHelpInstance (hwndHelp, hwndFrame);

 /* Standard message loop. Get messages from the queue and dispatch them to   */
 /* the approprite windows.                                                   */

 while (WinGetMsg (hab, &qmsg, 0L, 0, 0))
    WinDispatchMsg (hab, &qmsg);

 /* Main loop has terminated. Destroy all windows, help instance and message  */
 /* queue and then terminate the application.                                 */

 if (hwndHelp)
    WinDestroyHelpInstance (hwndHelp);
 WinDestroyWindow (hwndFrame);
 WinDestroyMsgQueue (hmq);
 WinTerminate (hab);

 DosExit (EXIT_PROCESS, 0L);

}

/******************************************************************************/
/*                                                                            */
/* wpClientWndProc: Window procedure to handle pie chart window, menu bar     */
/* processing, help, etc.                                                     */
/*                                                                            */
/******************************************************************************/

MRESULT EXPENTRY wpClientWndProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)

{

 MRESULT         mr = (MRESULT) FALSE;
 FONTMETRICS     fm;
 APIRET          rc;
 static HAB      hab;
 static LONG     cxChar, cyChar, cyDesc, cxClient, cyClient;
 static CHAR     szListHdr[80], szStatusOn[40], szStatusOff[40],
                 szTitleBar[51], szProgram[12];
 static HWND     hwndPopup, hwndFile;  /* window handles                      */
 static HWND     hwndFocus;
 static PACTINFO curact;               /* current activity                    */
 static time_t   startime;             /* tracking starting time              */
 static ULONG    refreshtimecount;     /* used by refresh interval            */
 static ULONG    alarmtimecount;       /* used by the alarm timer             */
 static ULONG    ulJuldate;            /* current date                        */
 static CHAR     szJuldate[8], szDate[11];
 static BOOL     messageon, nofocus;
 static MENUITEM mi;
 static ULONG    expandFlag, collapseFlag;

 switch (msg)
    {

     case WM_CREATE:                   /* Window just got created. Perform    */
        {                              /* other window initialization here    */
          RECTL       rectl;           /* frame. Then start the thread to     */
          HPS         hps;             /* insert items into the listbox       */
          FONTMETRICS fm;

          alarmflag = OFF;
          DosCreateMutexSem( "\\SEM32\\TIMETRAC", &hmtx,   0, FALSE );
          DosCreateMutexSem( "\\SEM32\\TIMEDLGS", &hmtxNB, 0, FALSE );

          hab = WinQueryAnchorBlock( hwnd );
                                       /* get some common strings and store   */
                                       /* into static variable because they   */
                                       /* will be used often, performance!    */
          WinLoadString (hab, 0L, IDS_TITLEBAR, 50, szTitleBar );
          WinLoadString( hab, 0L, IDS_LISTHDR, sizeof( szListHdr ), szListHdr );
          WinLoadString( hab, 0L, IDS_STATUSON, sizeof( szStatusOn ),
                         szStatusOn );
          WinLoadString( hab, 0L, IDS_STATUSOFF, sizeof( szStatusOff ),
                         szStatusOff );
          if(strlen(Outfile) == 0)             // V1.98
            WinLoadString( hab, 0L, IDS_OUTFILE, sizeof( Outfile ),
                           Outfile );
          WinLoadString( hab, 0L, IDS_BACKFILE, sizeof( BackOutfile ),
                         BackOutfile );
          if(strlen(Reportfile) == 0)          // V1.98
            WinLoadString( hab, 0L, IDS_REPORTFILE, sizeof( Reportfile ),
                           Reportfile );
          WinLoadString( hab, 0L, IDS_BACKREPFILE, sizeof( BackReportfile ),
                         BackReportfile );
          if(strlen(Commentfile) == 0)         // V1.98
            WinLoadString( hab, 0L, IDS_COMMENTFILE, sizeof( Commentfile ),
                           Commentfile );
          WinLoadString( hab, 0L, IDS_BACKCOMFILE, sizeof( BackCommentfile ),
                         BackCommentfile );
          if( dataDir[0] != '\0' )
          {
            CHAR tempStr[256];
            strcpy( tempStr, Outfile );
            strcpy( Outfile, dataDir );
            strcat( Outfile, "\\" );
            strcat( Outfile, tempStr );
            strcpy( tempStr, BackOutfile );
            strcpy( BackOutfile, dataDir );
            strcat( BackOutfile, "\\" );
            strcat( BackOutfile, tempStr );
            strcpy( tempStr, Reportfile );
            strcpy( Reportfile, dataDir );
            strcat( Reportfile, "\\" );
            strcat( Reportfile, tempStr );
            strcpy( tempStr, BackReportfile );
            strcpy( BackReportfile, dataDir );
            strcat( BackReportfile, "\\" );
            strcat( BackReportfile, tempStr );
            strcpy( tempStr, Commentfile );
            strcpy( Commentfile, dataDir );
            strcat( Commentfile, "\\" );
            strcat( Commentfile, tempStr );
            strcpy( tempStr, BackCommentfile );
            strcpy( BackCommentfile, dataDir );
            strcat( BackCommentfile, "\\" );
            strcat( BackCommentfile, tempStr );
          }
          WinLoadString( hab, 0L, IDS_PROGRAM, sizeof( szProgram ),
                         szProgram );
                                       /* use non-proportional font because   */
                                       /* of columar list box, this is for    */
                                       /* the client                          */
          WinSetWindowText( WinQueryWindow( hwnd, QW_PARENT), szTitleBar );
          sprintf(szText, "%d.%-s", fontsize, fontname);
          WinSetPresParam( hwnd, PP_FONTNAMESIZE,
                           sizeof( szText ), szText );
                                       /* get presentation space values       */
          hps = WinBeginPaint( hwnd, 0L, 0L );

          GpiQueryFontMetrics( hps, sizeof(FONTMETRICS), &fm );
          cxChar = (LONG)fm.lAveCharWidth;
          cyChar = (LONG)fm.lMaxBaselineExt;
          cyDesc = (LONG)fm.lMaxDescender;

          WinEndPaint( hps );
                                       /* create the list box containing all  */
                                       /* the data shown in the client area   */
          WinQueryWindowRect( hwnd, &rectl );
          hwndList = WinCreateWindow( hwnd, WC_LISTBOX, NULL, LS_NOADJUSTPOS,
                                   0, cyChar, rectl.xRight,
                                   rectl.yTop-smallwin*cyChar,
                                   hwnd, HWND_TOP, ID_LISTBOX, NULL, NULL);
                                       /* load listbox popup menu from res    */
          hwndPopup = WinLoadMenu( hwnd, (HMODULE)NULL, idPopup );

          WinEnableMenuItem(WinWindowFromID(WinQueryWindow(hwnd,
                            QW_PARENT), FID_MENU), IDM_STOP, FALSE);
          WinEnableMenuItem(hwndPopup, IDM_STOP, FALSE);
                                       /* get out of WM_CREATE and complete   */
                                       /* the rest of the initialization using*/
                                       /* a user defined message UM_CREATE    */
          WinSendMsg( hwnd, UM_CREATE, 0L, 0L );
#if PRTDEBUG
          fprintf(wptr, "Completed WM_CREATE processing.\n");
#endif
        }                              /* end case (WM_CREATE)                */
        break;

     case UM_CREATE:                   /* Window just got created. Perform    */
        {                              /* own window initialization here      */
          TID         tidThread;

          strcpy(subact, szBlank);
          if(subactwin == YES)
          {
            WinEnableMenuItem(WinWindowFromID(WinQueryWindow(hwnd,
                              QW_PARENT), FID_MENU), IDM_MAIN, FALSE );
            WinEnableMenuItem(hwndPopup, IDM_MAIN, FALSE);
          }

          ulJuldate = fnJulDate( );
          fnCurDate( szJuldate, szDate );

          curact = (PACTINFO)NULL;     /* initialize currently selected item  */

          rc = fnGetActivityInfo( );
          if( rc != 0 )                /* error reading file, inform the user */
          {                            /* except this error which is a warning*/
            if( rc == WARN_RESET )     /* user want auto-reset but we did not */
            {                          /* since the data is for the same day  */
              fnAddTotal();
              fnListBoxEntry( hwnd, curact, &expandFlag, &collapseFlag );
              if( showresetnew == YES && totalactivities > 0 )
                WinPostMsg( hwnd, UM_WARNRESET, 0L, 0L );
            }
            else
            {
              WinLoadString( hab, 0L, IDS_ERRTITLE, sizeof( szTitle ), szTitle );
              WinLoadString( hab, 0L, IDS_GETERROR, sizeof( szText ), szText );
              sprintf( szText1, "%s %d.", szText, rc );
              WinMessageBox (HWND_DESKTOP, hwnd, szText1, szTitle, 1,
                             MB_ERROR | MB_MOVEABLE | MB_OK );
            }
          }
          else                         /* insert all activity codes into the  */
          {                            /* list box                            */
            fnAddTotal();
            fnListBoxEntry( hwnd, curact, &expandFlag, &collapseFlag );
          }

          DosCreateThread( &tidThread, (PFNTHREAD)fnPutActivityInfo, 0L, 0L,
                           STACKSIZE );

          if( refreshtime > 0 )        /* start the refresh timer is requested*/
          {
            refreshtimecount = refreshtime;
            WinStartTimer( hab, hwnd, ID_REFRESHTIMER, REFRESH_MINUTE );
          }

          nofocus   = NO;
          messageon = NO;              /* BOOL to ensure msg box shown 1 only */
                                       /* get the hwnd for the File pulldown  */
          WinSendMsg( WinWindowFromID( WinQueryWindow( hwnd, QW_PARENT ),
                      FID_MENU ), MM_QUERYITEM,
                      MPFROM2SHORT( IDM_FILE, FALSE ), (MPARAM)&mi );
          hwndFile = mi.hwndSubMenu;   /* populate the static MENUITEM var    */
          mi.iPosition = MIT_END;      /* called mi with proper data          */
          mi.afStyle = MIS_TEXT;
          mi.afAttribute = 0;
          mi.id = IDM_COMMAND;         /* id for user exit command            */
          mi.hwndSubMenu = 0;
          mi.hItem = 0;
                                       /* insert menu item in File pulldown   */
          if( menutext[0] != '\0' && program[0] != '\0' )
          {
            strcpy(szTitle, menutext);
            strcat(szTitle, " \tCtrl-U");
            WinSendMsg( hwndFile, MM_INSERTITEM, (MPARAM)&mi, (MPARAM)szTitle );
          }

          if( totalactivities == 0 )
            WinPostMsg( hwnd, UM_WARNADD, 0L, 0L );
                                       /* enable/disable Save Report menu     */
          if( repsave > 0 )            /* item according to Settings          */
            WinEnableMenuItem( WinWindowFromID(WinQueryWindow(hwnd, QW_PARENT),
                               FID_MENU), IDM_SAVE, TRUE );
          else
            WinEnableMenuItem( WinWindowFromID(WinQueryWindow(hwnd, QW_PARENT),
                               FID_MENU), IDM_SAVE, FALSE );

          if(totalactivities == 0)     /* turn menu items if no activities    */
            fnToggleMenuItems(hwnd, FALSE);

          if(startact[0] != ' ' || startitem[0] != ' ')
          {
            PACTINFO item;
            CHAR     activity[CODE_WIDTH+1];
            CHAR     parent[CODE_WIDTH+1];

            if(startact[0] == ' ' && startitem[0] != ' ')
              strcpy(startact, startitem);
            fnSubstr(startact, activity, 1, CODE_WIDTH);
            fnSubstr(startact, parent, CODE_WIDTH+2, CODE_WIDTH);
            item = fnFindActivity(activity, parent);
            if(item)
              WinPostMsg( hwnd, UM_ACTIVITY, MPFROMLONG(item), 0L);
          }

          fnSortSelect( hwnd, sort );
          fnSecSortSelect( hwnd, secsort );
#if PRTDEBUG
          fprintf(wptr, "Completed UM_CREATE processing.\n");
#endif
        }                              /* end case UM_CREATE                  */
        break;

     case WM_SIZE:                     /* Window has been resized, re-calc    */
        {                              /* listbox on top of frame window      */
          RECTL rectl;

          cxClient = SHORT1FROMMP( mp2 );
          cyClient = SHORT2FROMMP( mp2 );

          WinSetWindowPos (WinWindowFromID (hwnd, ID_LISTBOX), HWND_TOP,
                           0, cyChar, cxClient, cyClient - smallwin * cyChar,
                           SWP_SIZE | SWP_MOVE | SWP_SHOW);
          WinSetFocus (HWND_DESKTOP, WinWindowFromID (hwnd, ID_LISTBOX));
#if PRTDEBUG
          fprintf(wptr, "WM_SIZE: cxClient %d - cyClient %d\n",
                  cxClient, cyClient);
#endif
        }                              /* end case (WM_SIZE)                  */
        break;

     case WM_PAINT:                    /* Redraw the client window here ...   */
        {
          RECTL  rectl;
          HPS    hps;
          POINTL point;
          CHAR   showunit;
          CHAR   szDate[11];
          float  showtotal;

          hps = WinBeginPaint (hwnd, 0L, 0L);

          rectl.xLeft   = 0;
          rectl.xRight  = cxClient;
          rectl.yBottom = 0;
          rectl.yTop    = cyClient;
          WinFillRect (hps, &rectl, SYSCLR_WINDOW);
                                       /* write the column headings on the    */
          if( smallwin == NORMAL_WINDOW )
          {
            point.x = cxChar;          /* top of window just above list box   */
            point.y = cyClient - cyChar + cyDesc;
            GpiCharStringAt( hps, &point, strlen( szListHdr ), szListHdr );
          }
                                       /* units to show in the status line    */
          if( units == UNITS_MINUTES )
            showunit = MINUTE_CHAR;
          else
            showunit = HOUR_CHAR;

          if( showexclude == YES )     /* total time, either all or excluded  */
            showtotal = extottime;
          else
            showtotal = totaltime;

          fnDate(szDate);              /* Get formatted date                  */

          rectl.xLeft   = 0;           /* Create 3D status bar at bottom of   */
          rectl.xRight  = cxClient;    /* main TIMETRAC window                */
          rectl.yBottom = 0;
          rectl.yTop    = cyChar;
          WinFillRect (hps, &rectl, CLR_PALEGRAY);
          WinDrawBorder (hps, &rectl, 1, 1,
                         SYSCLR_BUTTONDARK, SYSCLR_BUTTONMIDDLE, DB_DEPRESSED);
          point.x = cxChar;            /* Write information on the status     */
          point.y = cyDesc;            /* line at the bottom on the window    */
          if( curact != NULL )         /* just under the list box             */
          {                            /* show which item being tracked       */
            if( units == UNITS_HOURS || units == UNITS_MINUTES )
              sprintf( szText, "%s %s <%6.2f%c> %s %s %-s", szDate,
                       subact, showtotal, showunit, szStatusOn,
                       curact->code, curact->description );
            else
            {
              CHAR szTime[9];
              fnConvertTime( showtotal, secunits, units, szTime );
              sprintf(szText, "%s %s <%s> %s %s %-s", szDate, subact,
                      szTime, szStatusOn, curact->code, curact->description);
            }
            GpiCharStringAt( hps, &point, strlen( szText ), szText );
          }
          else                         /* time tracking is off or stopped     */
          {
            if( units == UNITS_HOURS || units == UNITS_MINUTES )
              sprintf( szText, "%s %s <%6.2f%c> %s", szDate, subact,
                       showtotal, showunit, szStatusOff );
            else
            {
              CHAR szTime[9];
              fnConvertTime( showtotal, secunits, units, szTime );
              sprintf( szText, "%s %s <%s> %s", szDate, subact, szTime,
                       szStatusOff );
            }
            GpiCharStringAt( hps, &point, strlen( szText ), szText );
          }

          WinEndPaint (hps);

        }                              /* end case WM_PAINT                   */
        break;

     case WM_BUTTON1DBLCLK:            /* User clicked mouse button twice on  */
     case WM_BUTTON2DBLCLK:            /* the client window/list box, find    */
        {                              /* out which item was selected         */
          LONG  y, item;

          y = SHORT2FROMMP( mp1 );

          if( ( y>cyChar && y<cyClient-cyChar && smallwin==NORMAL_WINDOW) ||
              ( y>cyChar && y<cyClient && smallwin==SMALL_WINDOW ) )
          {
            item = fnGetSelectedItem(hwnd, y, cyClient, cyChar);
            if( item > -1 )
              WinSendMsg( hwnd, UM_ACTIVITY, 0L, 0L );
            else                       /* no activity selected, show Add      */
              WinSendMsg( hwnd, WM_COMMAND, MPFROM2SHORT( IDM_ADD, TRUE ), 0L );
#if PRTDEBUG
            fprintf(wptr, "WM_BUTTONxDLBCLK, item selected is %d.\n", item);
#endif
          }
          else
            WinSendMsg( hwnd, WM_COMMAND, MPFROM2SHORT( IDM_ADD, TRUE ), 0L );
        }                              /* end case WM_BUTTONxDBLCLK           */
        break;

     case UM_ACTIVITY:                 /* Processing when an activity is      */
       {                               /* started to be tracked               */
         PACTINFO item;
         ULONG    oldalarm;

         if(LONGFROMMP(mp1) == 0)
           item = fnSelectItem( hab, hwnd, NO );
         else
           item = (PACTINFO)LONGFROMMP(mp1);
         if( item && item->children == 0  && item->expand == ' ')
         {
           if(subactwin == YES)
             strcpy(subact, item->parent);

           oldalarm = alarmtime;       /* Save the original alarmtime         */
           if( alarmchg == YES && alarmtime > 0 && item->alarmtime == 0 &&
               alarmflag == OFF )
           {
             if(!WinDlgBox (HWND_DESKTOP, hwnd, wpSetAlarmDlgProc, 0L,
                 IDD_ALARMCHG, 0L))
               alarmtime = oldalarm;
           }
           if(item->alarmtime > 0)
             alarmtimecount = item->alarmtime;
           else
             alarmtimecount = alarmtime;
           alarmtime = oldalarm;       /* Set the original alarmtime back     */
           if( alarmtimecount > 0 )    /* Start alarm reminder timer on if    */
           {                           /* required                            */
             WinStopTimer( hab, hwnd, ID_ALARMTIMER );
             WinStartTimer( hab, hwnd, ID_ALARMTIMER, ALARM_MINUTE );
           }

                                       /* Add time to old activity            */
           if( curact != NULL )        /* Check first if old activity exists  */
             fnCalculateTime( hab, hwnd, curact, startime, secunits );
           curact = item;              /* Make new activity the current one   */
           curact->count = curact->count + 1; /* add 1 to count for new act.  */
           if(strcmp(curact->parent, szBlank) != 0)
           {                           /* Add count to parent activity also   */
             PACTINFO listitem;
             listitem = start;
             while(listitem)
             {
               if(strcmp(listitem->code, curact->parent) == 0)
               {
                 listitem->count = listitem->count + 1;
                 break;
               }
               listitem = (PACTINFO)listitem->next;
             }
           }
           time( &startime );

           if( ulJuldate != fnJulDate() && repsave > 0 )
             WinSendMsg( hwnd, WM_COMMAND, MPFROM2SHORT( IDM_SAVE, TRUE ), 0L );
                                       /* Update the application title bar    */
           sprintf( szText, "%s @ %s", szProgram, item->code );
           fnStrip( szText, szText, 'B', ' ' );
           WinSetWindowText( WinQueryWindow( hwnd, QW_PARENT), szText );

           if(gomain == YES && strcmp(curact->parent, szBlank)!= 0)
           {
             /* automatically collapse parent activity when sub-activity */
             /* started                                                  */
             PACTINFO parent;
             parent = fnFindActivity(curact->parent, szBlank);
             if(parent)
               parent->expand = '+';
             if(strcmp(subact, szBlank) != 0 && subactwin == YES)
               WinSendMsg(hwnd, WM_COMMAND, MPFROM2SHORT(IDM_MAIN, TRUE), 0L);
           }

           fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                          &expandFlag, &collapseFlag);

           alarmflag = OFF;
#if FOCUS
           if(curact->winfocus[0] != '\0' && nofocuschg == NO)
           {                           /* Process window focus if given       */
             HSWITCH hswitch;          /* Match the window focus title to     */
             HENUM   henum;            /* any desktop window titles found     */
             HWND    hwndDesktop;      /* If found, give focus and restore    */
             HWND    hwndNext;         /* if minimized                        */
             SWCNTRL swctl;
             ULONG   rc;

             hwndDesktop = HWND_DESKTOP;
             henum = WinBeginEnumWindows(hwndDesktop);
             while((hwndNext = WinGetNextWindow(henum)) != NULLHANDLE)
             {
               hswitch=WinQuerySwitchHandle(hwndNext,0);
               if(hswitch != NULLHANDLE)
               {
                 rc = WinQuerySwitchEntry(hswitch,&swctl);
                 if(!rc)
                 {
                   if(!strncmp(curact->winfocus, swctl.szSwtitle,
                      strlen(curact->winfocus)))
                   {
                     SWP   swp;

                     WinQueryWindowPos(swctl.hwnd, &swp);
                     if(swp.fl & SWP_MINIMIZE)
                     {
                       if(swp.x > 0 || swp.y > 0)
                         WinSetWindowPos(swctl.hwnd, HWND_TOP,
                                         swp.x, swp.y, swp.cx, swp.cy,
                                         SWP_SHOW | SWP_SIZE | SWP_MOVE |
                                         SWP_ACTIVATE);
                       else
                         WinSetWindowPos(swctl.hwnd, HWND_TOP, 0L, 0L, 0L, 0L,
                                         SWP_RESTORE );
                     }
                     WinSetFocus(HWND_DESKTOP, swctl.hwnd);
#if PRTDEBUG
                     fprintf(wptr, "%s HWND=%d, VIS=%d, JUMP=%d, PROG=%d, X=%d, Y=%d, CX=%d, CY=%d\n",
                             swctl.szSwtitle, swctl.uchVisibility, swctl.fbJump,
                             swctl.bProgType, swp.x, swp.y, swp.cx, swp.cy);
#endif
                   }
                 }
               }
             }
             WinEndEnumWindows(henum);
           }
           else
           {
             if( minimize == YES )
             {
               SWP   swp;

               WinQueryWindowPos (WinQueryWindow (hwnd, QW_PARENT), &swp);
               WinSetWindowPos( WinQueryWindow(hwnd, QW_PARENT), HWND_TOP,
                                swp.x, swp.y, swp.cx, swp.cy,
                                SWP_SHOW | SWP_SIZE | SWP_MOVE |
                                SWP_ACTIVATE | SWP_MINIMIZE );
               if(nofocuschg == NO)
               {
                 hwndFocus = WinQueryWindow( HWND_DESKTOP, QW_PREV );
                 WinSetFocus( HWND_DESKTOP, hwndFocus );
               }
             }
             else
             {
               if(nofocuschg == NO)
               {
                 if( hwndFocus != hwnd )
                   WinSetFocus( HWND_DESKTOP, hwndFocus );
               }
             }
           }
#endif

           if( curact->lock == LOCK_CHAR )
           {                               /* Lock up WPS here if required    */
             HWND hwndWPS;                 /* Handle for WPS                  */

             hwndWPS = WinQueryWindow(HWND_DESKTOP, QW_BOTTOM);
             if( hwndWPS )
               WinPostMsg(hwndWPS, WM_COMMAND, MPFROMSHORT(IDMI_LOCKUPNOW),
                          MPFROM2SHORT(CMDSRC_MENU, TRUE));
           }
                                           /* Processing for user exit here   */
           if( curact->program[0] != '\0' )
             fnStartCommand( curact->program, curact->parameters );

           WinEnableMenuItem(WinWindowFromID(WinQueryWindow(hwnd,
                             QW_PARENT), FID_MENU), IDM_STOP, TRUE);
           WinEnableMenuItem(hwndPopup, IDM_STOP, TRUE);

#if PRTDEBUG
          fprintf(wptr, "UM_ACTIVITY processing complete.\n");
#endif
         }
         else
         {
           if(item)
           {
             if(subactwin == YES)
             {
               strcpy(subact, item->code);
               WinEnableMenuItem(WinWindowFromID(WinQueryWindow(hwnd,
                                 QW_PARENT), FID_MENU), IDM_MAIN, TRUE);
               WinEnableMenuItem(hwndPopup, IDM_MAIN, TRUE);
             }
             else
             {
               if(item->expand == '+')
                 item->expand = '-';
               else
                 item->expand = '+';
             }
             fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                            &expandFlag, &collapseFlag );
           }
         }
       }                               /* end case UM_ACTIVITY                */
       break;

#if FOCUS
     case UM_WARNRESET:                /* warning that reset not done         */
        WinLoadString( hab, 0L, IDS_RESET, sizeof( szTitle ), szTitle );
        WinLoadString( hab, 0L, IDS_RESETWARN, sizeof( szText ), szText );
        WinMessageBox (HWND_DESKTOP, hwnd, szText, szTitle, 1,
                      MB_WARNING | MB_MOVEABLE | MB_OK );
        break;

     case UM_WARNADD:                  /* warning that no activity codes found*/
        WinLoadString( hab, 0L, IDS_ADD, sizeof( szTitle ), szTitle );
        WinLoadString( hab, 0L, IDS_WARNADD, sizeof( szText ), szText );
        WinMessageBox (HWND_DESKTOP, hwnd, szText, szTitle, 1,
                      MB_WARNING | MB_MOVEABLE | MB_OK );
        break;
#endif

     case WM_CHAR:                     /* keyboard support here ...           */
       {
                                       /* ignore all key down presses         */
         if (SHORT1FROMMP(mp1) & KC_SCANCODE)
         {                             /* user pressed a valid character on   */
                                       /* the keyboard, let's process it      */
           SHORT    selitem, i, previtem;
           PACTINFO listitem;
           UCHAR    uchChr1;
           BOOL     first, found, prevfound;
                                       /* convert letter to upper case here   */
           uchChr1 = (UCHAR) CHAR1FROMMP( mp2 );
           if( uchChr1 > 96 && uchChr1 < 123 )
             uchChr1 = uchChr1 - 32;

           found     = NO;             /* we want to find the first item whose*/
           prevfound = NO;             /* first letter as its activity code   */
                                       /* matches the keyboard letter that    */
                                       /* was just pressed by the user        */
           selitem = WinQueryLboxSelectedItem( hwndList );
           if( selitem < 0 )           /* we have to traverse the linked list */
             selitem = 0;              /* starting from the currently selected*/
                                       /* item in the list box                */
           listitem = start;
           i = 0;
           if(listitem && totalitems > 0)
           {
             while(1)                    /* process the items before the      */
             {                           /* currently selected item first     */
               if(listitem->display > -1)
               {
                 if( listitem->code[0] == uchChr1 && prevfound == NO )
                 {
                   previtem  = i;        /* find any that matches in case none*/
                   prevfound = YES;      /* of those after the selected item  */
                 }                       /* matches                           */
                 i++;
               }
               listitem = (PACTINFO)listitem->next;
               if(i > selitem)
                 break;
             }

             while( listitem )         /* process all items after the current */
             {                         /* selected item, find a match!        */
               if(listitem->display > -1)
               {
                 if(listitem->code[0] == uchChr1)
                 {                       /* yup, found a match, select item   */
                   WinSendMsg(WinWindowFromID(hwnd, ID_LISTBOX), LM_SELECTITEM,
                             MPFROMSHORT(listitem->display), MPFROMSHORT(TRUE));
                   found = YES;          /* set found flag to yes and get out */
                   break;
                 }
               }
               listitem = (PACTINFO)listitem->next;
             }

             if( found == NO && prevfound == YES )
               WinSendMsg( WinWindowFromID( hwnd, ID_LISTBOX ), LM_SELECTITEM,
                           MPFROMSHORT(previtem), MPFROMSHORT(TRUE) );
           }

           mr = (MRESULT)TRUE;
         }

         if (SHORT1FROMMP(mp1) & KC_KEYUP )
           break;

         if (SHORT1FROMMP(mp1) & KC_VIRTUALKEY)
         {
           switch( SHORT2FROMMP( mp2 ) )
           {
              case VK_NEWLINE:         /* user press Enter or Newline key,    */
              case VK_ENTER:           /* this is just like a double mouse    */
              {                        /* click so start tracking currently   */
                SHORT selitem;         /* selected item                       */

                selitem = WinQueryLboxSelectedItem( hwndList );
                if( selitem >= 0 )
                  WinSendMsg( hwnd, UM_ACTIVITY, 0L, 0L );
                return (MRESULT)TRUE;
              }
              default:
                return (MRESULT)FALSE;
           }
         }
#if PRTDEBUG
         fprintf(wptr, "WM_CHAR processing completed.\n");
#endif
       }
       break;

     case WM_TIMER:
        {
          USHORT timerid;              /* get timer id from mp1 first         */
          timerid = SHORT1FROMMP( mp1 );

          switch( timerid )
          {
            case ID_REFRESHTIMER:      /* Refresh timer procedure here        */
              {
                refreshtimecount--;    /* WinStartTimer can only timout to a  */
                if( refreshtimecount == 0 )/* max of 1 min, so we must use a  */
                {                      /* counter if > 1 minute. Decrement    */
                                       /* counter until 0 then desired timeout*/
                                       /* has occurred then process           */
                   if( curact != NULL )
                   {
                     fnCalculateTime( hab, hwnd, curact, startime, secunits );
                     time( &startime );
                   }
                   /* Refresh list always, even if no activity being tracked  */
                   fnProcessItem( hab, hwnd, curact, cxClient, cyChar,
                                  refreshsave, &expandFlag,
                                  &collapseFlag );

                   refreshtimecount = refreshtime;
                }
                if( ulJuldate != fnJulDate() && repsave > 0 )
                  WinSendMsg( hwnd, WM_COMMAND, MPFROM2SHORT( IDM_SAVE,
                              TRUE ), 0L );
              }                        /* end case ID_REFRESHTIMER            */
              break;

            case ID_ALARMTIMER:        /* alarm reminder timer procedure here */
              {
                alarmtimecount--;
                if( alarmtimecount == 0 )
                {
                  if( curact != NULL ) /* check if tracking an activity code  */
                  {                    /* yup, continue then                  */

                    if( alarmsound == YES ) /* user want a sound, use beep    */
                      DosBeep( 100, 100 );
                                       /* user want a message box to show     */
                    if( alarmmsg == YES && messageon == NO )
                    {                  /* messageon = NO ensures we only have */
                      CHAR showunit[12];  /* one of these msg boxes around    */
                      HWND hwndFocusWin, hwndActiveWin;
                      CHAR saveact[CODE_WIDTH+1];
                      CHAR savepar[CODE_WIDTH+1];

                      hwndActiveWin = WinQueryActiveWindow( HWND_DESKTOP );
                      hwndFocusWin  =  WinQueryFocus( HWND_DESKTOP );

                      messageon = YES; /* set flag to ON                      */

                      nofocus = YES;
                      if( WinDlgBox (HWND_DESKTOP, hwnd, wpAlarmMsgDlgProc, 0L,
                          IDD_ALARMMSG, curact ) )
                      {
                        strcpy(saveact, curact->code);
                        strcpy(savepar, curact->parent);
                        WinSendMsg( hwnd, WM_COMMAND,
                                    MPFROM2SHORT( IDM_STOP, TRUE ), 0L );
                        WinSetWindowPos( WinQueryWindow( hwnd, QW_PARENT ),
                                         HWND_TOP, 0L, 0L, 0L, 0L,
                                         SWP_RESTORE );
                        if( alarmedit == YES )
                        {
                          if( fnSelectActivity( hwnd, hwndPopup, saveact,
                                                savepar, curact ) == TRUE )
                            WinSendMsg( hwnd, WM_COMMAND,
                                        MPFROM2SHORT( IDM_EDIT, TRUE ), 0L );
                        }
                      }
                      else             /* return focus to the window that     */
                      {                /* just lost focus when timer expired  */
                        if( alarmflag == ON )
                        {
                          if(strncmp(alarmitem, "$CURACT$", CODE_WIDTH) == 0)
                            WinSendMsg( hwnd, UM_ACTIVITY,
                                        MPFROMLONG(curact), 0L );
                          else
                          {
                            CHAR     activity[CODE_WIDTH+1];
                            CHAR     parent[CODE_WIDTH+1];
                            PACTINFO actinfo;

                            fnSubstr(alarmitem, activity, 1, CODE_WIDTH);
                            fnSubstr(alarmitem, parent, CODE_WIDTH+2,
                                     CODE_WIDTH);
//                          if( fnSelectActivity( hwnd, hwndPopup, activity,
//                                                parent, curact ) == TRUE )
//                            WinSendMsg( hwnd, UM_ACTIVITY,0L, 0L );
                            actinfo = fnFindActivity(activity, parent);
                            if(actinfo)
                              WinSendMsg( hwnd, UM_ACTIVITY,
                                          MPFROMLONG(actinfo), 0L );
                          }
                        }
                        else
                        {
                          alarmflag = ON;
//                        if( fnSelectActivity( hwnd, hwndPopup, curact->code,
//                            curact->parent, curact ) == TRUE )
//                          WinSendMsg( hwnd, UM_ACTIVITY,0L, 0L );
                          WinSendMsg( hwnd, UM_ACTIVITY, MPFROMLONG(curact),
                                      0L );
                        }
#if FOCUS
                        if(nofocuschg == NO)
                        {
                          WinSetFocus( HWND_DESKTOP, hwndFocusWin );
                          WinSetActiveWindow( HWND_DESKTOP, hwndActiveWin );
                        }
#endif
                      }
                      nofocus = NO;
                      messageon = NO;
                    }
                  }
                }
                if( ulJuldate != fnJulDate() && repsave > 0 )
                  WinSendMsg( hwnd, WM_COMMAND, MPFROM2SHORT( IDM_SAVE, TRUE ),
                              0L );
              }                        /* end case ID_ALARMTIMER              */
              break;

            default:
              break;
          }                            /* end switch statement                */
        }                              /* end case WM_TIMER                   */
        break;

#if FOCUS
     case WM_FOCUSCHANGE:
        if( SHORT1FROMMP(mp2)==TRUE )
          hwndFocus = HWNDFROMMP(mp1);
        mr = WinDefWindowProc (hwnd, msg, mp1, mp2);
        break;
#endif

      case WM_BUTTON2DOWN:             /* Display the popup menu              */
        {
          LONG  y, item;

          y = SHORT2FROMMP( mp1 );
          if( ( y>cyChar && y<cyClient-cyChar && smallwin==NORMAL_WINDOW) ||
              ( y>cyChar && y<cyClient && smallwin==SMALL_WINDOW ) )
          {
            item = fnGetSelectedItem(hwnd, y, cyClient, cyChar);
            if( item > -1 )
              WinPostMsg( WinWindowFromID( hwnd, ID_LISTBOX ), LM_SELECTITEM,
                         MPFROMSHORT(item), MPFROMSHORT(TRUE) );

            WinPopupMenu( hwnd, WinQueryWindow( hwnd, QW_PARENT ),
                          hwndPopup, SHORT1FROMMP(mp1), SHORT2FROMMP(mp1), 0,
                          PU_HCONSTRAIN | PU_VCONSTRAIN |
                          PU_KEYBOARD | PU_MOUSEBUTTON1 | PU_MOUSEBUTTON2 );
#if PRTDEBUG
            fprintf(wptr, "WM_BUTTON2DOWN, item selected is %d.\n", item);
#endif
          }
        }                              /* end case WM_BUTTON2DOWN             */
        break;

     case WM_COMMAND:                  /* Application command processing here */
        {
         switch (SHORT1FROMMP (mp1))   /* Message contained in mp1 variable   */
            {
//           case IDM_TEST:
//              break;

             case IDM_DEBUG:
                {
                  PACTINFO item;
                  item = start;
                  while(item)
                  {
                    fnChangeParentInfo(item->parent);
                    item = (PACTINFO)item->next;
                  }
                  WinSendMsg( hwnd, WM_COMMAND,
                              MPFROM2SHORT( IDM_REFRESH, TRUE ), 0L );
                  WinMessageBox(HWND_DESKTOP, hwnd,
                                "Ctrl-Z pressed. Activity list corrected.",
                                "TIMETRAC for OS/2", 0, MB_MOVEABLE | MB_OK);
                }
                break;
                                       /* Menu popup command processing first */
             case IDM_START:           /* Start the timer for the item picked */
                {
                  PACTINFO item;

                  item = fnSelectItem( hab, hwnd, YES );
                  if( item )
                    WinSendMsg( hwnd, UM_ACTIVITY, 0L, 0L );
                }                      /* end case IDM_START                  */
                break;

             case IDM_STOP:            /* Stop the timer.                     */
                {
                  if( curact != NULL )
                  {
                    fnCalculateTime( hab, hwnd, curact, startime, secunits );
                    curact = (PACTINFO)NULL;
                    WinSetWindowText( WinQueryWindow(hwnd, QW_PARENT),
                                      szTitleBar );

                    fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                                   &expandFlag, &collapseFlag );

                    WinEnableMenuItem(WinWindowFromID(WinQueryWindow(hwnd,
                                      QW_PARENT), FID_MENU), IDM_STOP, FALSE);
                    WinEnableMenuItem(hwndPopup, IDM_STOP, FALSE);
                  }
                  if( ulJuldate != fnJulDate() && repsave > 0 )
                    WinSendMsg( hwnd, WM_COMMAND, MPFROM2SHORT( IDM_SAVE,
                                TRUE ), 0L );
                }                      /* end case IDM_STOP                   */
                break;

             case IDM_DELETE:          /* Delete the selected item from the   */
                {                      /* list. First make sure an item was   */
                  PACTINFO item;       /* selected.                           */
                  BOOL doit = FALSE;

                  item = fnSelectItem( hab, hwnd, YES );
                  if( item )
                  {
                    if(item->children == 0)
                    {                  /* if user wants confirmation, then    */
                      if( showdelete == YES )    /* show message box first    */
                      {
                        WinLoadString(hab, 0L, IDS_DELETE, sizeof(szTitle),
                                       szTitle);
                        WinLoadString(hab, 0L, IDS_DELETEMSG, sizeof(szText),
                                      szText);
                        sprintf( szText1, "%s %s?", szText, item->code );
                        if (WinMessageBox (HWND_DESKTOP, hwnd, szText1, szTitle,
                                           1, MB_MOVEABLE | MB_YESNO |
                                           MB_WARNING |
                                           MB_DEFBUTTON2) == MBID_YES)
                          doit = TRUE;
                      }
                      else
                        doit = TRUE;
                      if( doit == TRUE ) /* ok, we really want to delete, set */
                      {                  /* the delete flag on                */
                        if( item == curact ) /* tracked item deleted, set NULL*/
                        {
                          WinSendMsg( hwnd, WM_COMMAND,
                                      MPFROM2SHORT( IDM_STOP, TRUE ), 0L );
//                        curact = (PACTINFO)NULL;
                        }
                        fnDeleteLinkList(item);
                        totalitems--;
                        if(totalitems == 0 && subactwin == YES)
                        {
                          strcpy(subact, szBlank);
                          WinEnableMenuItem(WinWindowFromID(
                                            WinQueryWindow(hwnd,
                                            QW_PARENT), FID_MENU), IDM_MAIN,
                                            FALSE );
                          WinEnableMenuItem(hwndPopup, IDM_MAIN, FALSE );
                        }
                        totalactivities--;
                        fnChangeParentInfo(item->parent);
                        fnProcessItem( hab, hwnd, curact, cxClient, cyChar,
                                       YES, &expandFlag, &collapseFlag );
                        if(totalactivities == 0)
                          fnToggleMenuItems(hwnd, FALSE);
                      }
                    }
                    else               /* Activity cannot be deleted if it has*/
                    {                  /* sub-activities defined for it       */
                      WinLoadString( hab, 0L, IDS_DELETE, sizeof( szTitle ),
                                     szTitle );
                      WinLoadString( hab, 0L, IDS_DELETEWARN, sizeof( szText ),
                                     szText );
                      WinMessageBox (HWND_DESKTOP, hwnd, szText,
                                     szTitle, 0, MB_MOVEABLE | MB_OK |
                                     MB_WARNING);
                    }
                  }
                }                      /* end case IDM_DELETE                 */
                break;

             case IDM_ADD:             /* Add a new activity code to the list */
                {
                  if( totalactivities < MAXITEMS )
                  {
                    WinDlgBox (HWND_DESKTOP, hwnd, wpAddDlgProc, 0L,
                               IDD_ADD, NULL );
                    if(totalactivities > 0)
                    {
                      fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                                     &expandFlag, &collapseFlag );
                      fnToggleMenuItems(hwnd, TRUE);
                    }
                  }
                  else
                  {
                    WinLoadString( hab, 0L, IDS_ADD, sizeof( szTitle ),
                                   szTitle );
                    WinLoadString( hab, 0L, IDS_ADDMSG, sizeof( szText ),
                                   szText );
                    WinMessageBox( HWND_DESKTOP, hwnd, szText, szTitle, 1,
                                   MB_MOVEABLE | MB_OK | MB_WARNING );
                  }
                }                      /* end case IDM_ADD                    */
                break;

             case IDM_EDIT:            /* Edit the selected activity code     */
                {
                  PACTINFO item;

                  item = fnSelectItem( hab, hwnd, YES );
                  if( item )
                  {
                    if( WinDlgBox (HWND_DESKTOP, hwnd, wpEditDlgProc, 0L,
                        IDD_EDIT, item ) )
                       fnProcessItem( hab, hwnd, curact, cxClient, cyChar,
                                      YES, &expandFlag, &collapseFlag );
                  }
                }                      /* end case IDM_EDIT                   */
                break;

             case IDM_RESETIT:         /* Reset the time for the activity code*/
                {                      /* 1.98                                */
                  BOOL doit = FALSE;

                  if( showreset == YES )
                  {
                    WinLoadString( hab, 0L, IDS_RESET, sizeof( szTitle ),
                                   szTitle );
                    WinLoadString( hab, 0L, IDS_RESETMSG, sizeof( szText ),
                                     szText );
                    if (WinMessageBox (HWND_DESKTOP, hwnd, szText, szTitle,
                                       1, MB_MOVEABLE | MB_YESNO |
                                       MB_WARNING | MB_DEFBUTTON2) == MBID_YES)
                       doit = TRUE;
                  }
                  else
                    doit = TRUE;
                  if( doit == TRUE )
                  {
                    PACTINFO item;

                    item = fnSelectItem( hab, hwnd, YES );
                    if( item )
                    {
                      if(item->children == 0)
                      {
                        DosRequestMutexSem( hmtxNB, SEM_INDEFINITE_WAIT );

                        item->timer = (float)0;
                        item->count = 0;
                        fnChangeParentInfo(item->parent);

                        DosReleaseMutexSem( hmtxNB );

                        fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                                       &expandFlag, &collapseFlag );

                      }
                      else
                      {
                        WinLoadString( hab, 0L, IDS_RESET, sizeof( szTitle ),
                                       szTitle );
                        WinLoadString( hab, 0L, IDS_RESETERROR, sizeof( szText ),
                                       szText );
                        WinMessageBox( HWND_DESKTOP, hwnd, szText, szTitle, 1,
                                       MB_MOVEABLE | MB_OK | MB_WARNING );
                      }
                    }
                  }
                }                      /* end case IDM_RESETIT                */
                break;

             case IDM_TRANSFER:        /* Transfer                            */
                {
                  PACTINFO item;

                  item = fnSelectItem( hab, hwnd, YES );
                  if( item )
                  {
                    if(item->children == 0)
                    {
                      if( item == curact )
                        fnCalculateTime(hab, hwnd, curact, startime, secunits);
                      if( WinDlgBox (HWND_DESKTOP, hwnd, wpTransferDlgProc, 0L,
                          IDD_TRANSFER, item ) )
                         fnProcessItem( hab, hwnd, curact, cxClient, cyChar,
                                        YES, &expandFlag, &collapseFlag );
                    }
                    else
                    {
                      WinLoadString( hab, 0L, IDS_TRAN, sizeof( szTitle ),
                                     szTitle );
                      WinLoadString( hab, 0L, IDS_TRANWARN, sizeof( szText ),
                                     szText );
                      WinMessageBox( HWND_DESKTOP, hwnd, szText, szTitle, 1,
                                     MB_MOVEABLE | MB_OK | MB_WARNING );
                    }
                  }
                }                      /* end case IDM_TRANSFER               */
                break;

             case IDM_EXCLUDE:         /* Exclude activity code from total    */
                {                      /* time calculated                     */
                  PACTINFO item;

                  item = fnSelectItem( hab, hwnd, YES );
                  if( item )
                  {
                    if( item->exclude == ' ' )
                      item->exclude = EXCLUDE_CHAR;
                    else
                      item->exclude = ' ';
                    fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                                   &expandFlag, &collapseFlag );
                  }
                }                      /* end case IDM_EXCLUDE                */
                break;

             case IDM_HIDE:            /* Hide activity code from list        */
               {
                  PACTINFO item;

                  item = fnSelectItem( hab, hwnd, YES );
                  if( item )
                  {
                    if( item->hide == ' ' )
                      item->hide = HIDE_CHAR;
                    else
                      item->hide = ' ';
                    fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                                   &expandFlag, &collapseFlag );
                  }
                }                      /* end case IDM_HIDE                   */
                break;

             case IDM_SAVE:            /* Save report                         */
                {

                  CHAR     outstring[MAXLENGTH], coutstring[MAXLENGTH];
                  float    reptotal;
                  time_t   now;
                  ULONG    i;
                  PACTINFO item;

                  if( curact != NULL )
                  {
                    fnCalculateTime( hab, hwnd, curact, startime, secunits );
                    time( &startime );
                  }
                  fnAddTotal();

                  outstring[0] = '\0';
                  fnDateInfo( outstring );

                  for( i=0; i<10; i++)
                    outstring[i] = szDate[i];
                  for( i=0; i<7; i++ )
                    outstring[i+11] = szJuldate[i];
                  strcat( outstring, "                    " );
                  strcpy(coutstring, outstring);
                  strcat(coutstring, " ");

                  reptotal = 0.0;
                  item = start;
                  while( item )
                  {
                    if( (item->hide == HIDE_CHAR && rephide == NO ) ||
                        (item->exclude == EXCLUDE_CHAR && repexcl == NO ) );
                    else
                    {
                      sprintf( szText, " %-8s %3d %7.2f %-8s",
                               item->code, item->count, item->timer,
                               item->parent );
                      strcat( outstring, szText );
                      sprintf(szText, "%-30s", item->comments);
                      strcat( coutstring, szText );
                      if(item->children == 0)
                        reptotal = reptotal + item->timer;
                    }
                    item = (PACTINFO)item->next;
                  }
                  sprintf( szText, "%7.2f", reptotal );
                  for( i=0; i<7; i++ )
                    outstring[i+19] = szText[i];

                  fnFreeReportList();
                  startrep = NULL;
                  lastrep  = NULL;

                  rc = fnSaveReport( YES, ulJuldate, outstring, coutstring,
                                     szJuldate );
                  if(ulJuldate != fnJulDate() &&
                     (initreset == YES || blankcom == YES))
                  {
                    item = start;
                    while( item )
                    {
                      if(initreset == YES)
                      {
                        item->timer = 0.0;
                        item->count = 0;
                      }
                      if(blankcom == YES)
                        item->comments[0] = '\0';
                      item = (PACTINFO)item->next;
                    }
                  }
                  fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                                 &expandFlag, &collapseFlag );

                  ulJuldate = fnJulDate( );
                  fnCurDate( szJuldate, szDate );
                }                      /* end case IDM_SAVE                   */
                break;

             case IDM_REPORT:          /* Report function                     */
                WinLoadDlg (HWND_DESKTOP, 0L, wpReportListDlgProc, 0L,
                            IDD_REPORTLIST, NULL );
                break;

             case IDM_SETTINGS:        /* Settings notebook                   */
                fnCreateNotebook( hab, hwnd );
                break;

             case IDM_REFRESH:         /* Refresh now, just message WM_TIMER  */
                refreshtimecount = 1;  /* set to 1 to force timeout           */
                WinSendMsg( hwnd, WM_TIMER, MPFROMSHORT(ID_REFRESHTIMER), 0L );
                break;

             case IDM_RESET:           /* Reset all time values to 0          */
                {
                  BOOL doit = FALSE;

                  if( showreset == YES )
                  {
                    WinLoadString( hab, 0L, IDS_RESET, sizeof( szTitle ),
                                   szTitle );
                    WinLoadString( hab, 0L, IDS_RESETMSG, sizeof( szText ),
                                     szText );
                    if (WinMessageBox (HWND_DESKTOP, hwnd, szText, szTitle,
                                       1, MB_MOVEABLE | MB_YESNO |
                                       MB_WARNING | MB_DEFBUTTON2) == MBID_YES)
                       doit = TRUE;
                  }
                  else
                    doit = TRUE;
                  if( doit == TRUE )
                  {
                    PACTINFO item;

                    DosRequestMutexSem( hmtxNB, SEM_INDEFINITE_WAIT );
                    item = start;
                    while( item )
                    {
                      item->timer = (float)0;
                      item->count = 0;
                      item = (PACTINFO)item->next;
                    }
                    curact = (PACTINFO)NULL;
                    DosReleaseMutexSem( hmtxNB );
                    fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                                   &expandFlag, &collapseFlag );
                  }
                }                      /* end case IDM_RESET                  */
                break;

             case IDM_REPEDIT:         /*                                     */
                WinDlgBox (HWND_DESKTOP, hwnd, wpRepEditDlgProc, 0L,
                           IDD_REPORTEDIT, NULL );
                break;                 /* end case IDM_REPEDIT                */

             case IDM_EXPANDALL:
               {
                 PACTINFO item;
                 item = start;
                 while(item)
                 {
                   if(item->expand == '+')
                     item->expand = '-';
                   item = (PACTINFO)item->next;
                 }
                 fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                                &expandFlag, &collapseFlag );
               }
               break;                  /* end case IDM_EXPANDALL              */

             case IDM_COLLAPSEALL:
               {
                 PACTINFO item;
                 item = start;
                 while(item)
                 {
                   if(item->expand == '-')
                     item->expand = '+';
                   item = (PACTINFO)item->next;
                 }
                 fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                                &expandFlag, &collapseFlag );
               }
               break;                  /* end case IDM_COLLAPSEALL            */

             /* primary sort menu selections */
             case IDM_SORT_NONE:
               sort = SORT_NONE;
               fnSortSelect( hwnd, sort );
               break;
             case IDM_SORT_CODE_A:
               sort = SORT_CODE_A;
               fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                              &expandFlag, &collapseFlag );
               fnSortSelect( hwnd, sort );
               break;
             case IDM_SORT_CODE_D:
               sort = SORT_CODE_D;
               fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                              &expandFlag, &collapseFlag );
               fnSortSelect( hwnd, sort );
               break;
             case IDM_SORT_DESC_A:
               sort = SORT_DESC_A;
               fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                              &expandFlag, &collapseFlag );
               fnSortSelect( hwnd, sort );
               break;
             case IDM_SORT_DESC_D:
               sort = SORT_DESC_D;
               fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                              &expandFlag, &collapseFlag );
               fnSortSelect( hwnd, sort );
               break;
             case IDM_SORT_TIME_A:
               sort = SORT_TIME_A;
               fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                              &expandFlag, &collapseFlag );
               fnSortSelect( hwnd, sort );
               break;
             case IDM_SORT_TIME_D:
               sort = SORT_TIME_D;
               fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                              &expandFlag, &collapseFlag );
               fnSortSelect( hwnd, sort );
               break;
             case IDM_SORT_PERC_A:
               sort = SORT_PERC_A;
               fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                              &expandFlag, &collapseFlag );
               fnSortSelect( hwnd, sort );
               break;
             case IDM_SORT_PERC_D:
               sort = SORT_PERC_D;
               fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                              &expandFlag, &collapseFlag );
               fnSortSelect( hwnd, sort );
               break;
             case IDM_SORT_COUNT_A:
               sort = SORT_COUNT_A;
               fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                              &expandFlag, &collapseFlag );
               fnSortSelect( hwnd, sort );
               break;
             case IDM_SORT_COUNT_D:
               sort = SORT_COUNT_D;
               fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                              &expandFlag, &collapseFlag );
               fnSortSelect( hwnd, sort );
               break;
             case IDM_SORT_SEQUENCE:
                WinMessageBox( HWND_DESKTOP, 0L, "Under construction.", "Sort",
                               1, MB_OK | MB_MOVEABLE );
                break;

             /* secondary sort menu selections */
             case IDM_SECSORT_NONE:
               secsort = SORT_NONE;
               fnSecSortSelect( hwnd, secsort );
               break;
             case IDM_SECSORT_CODE_A:
               secsort = SORT_CODE_A;
               fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                              &expandFlag, &collapseFlag );
               fnSecSortSelect( hwnd, secsort );
               break;
             case IDM_SECSORT_CODE_D:
               secsort = SORT_CODE_D;
               fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                              &expandFlag, &collapseFlag );
               fnSecSortSelect( hwnd, secsort );
               break;
             case IDM_SECSORT_DESC_A:
               secsort = SORT_DESC_A;
               fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                              &expandFlag, &collapseFlag );
               fnSecSortSelect( hwnd, secsort );
               break;
             case IDM_SECSORT_DESC_D:
               secsort = SORT_DESC_D;
               fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                              &expandFlag, &collapseFlag );
               fnSecSortSelect( hwnd, secsort );
               break;
             case IDM_SECSORT_TIME_A:
               secsort = SORT_TIME_A;
               fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                              &expandFlag, &collapseFlag );
               fnSecSortSelect( hwnd, secsort );
               break;
             case IDM_SECSORT_TIME_D:
               secsort = SORT_TIME_D;
               fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                              &expandFlag, &collapseFlag );
               fnSecSortSelect( hwnd, secsort );
               break;
             case IDM_SECSORT_PERC_A:
               secsort = SORT_PERC_A;
               fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                              &expandFlag, &collapseFlag );
               fnSecSortSelect( hwnd, secsort );
               break;
             case IDM_SECSORT_PERC_D:
               secsort = SORT_PERC_D;
               fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                              &expandFlag, &collapseFlag );
               fnSecSortSelect( hwnd, secsort );
               break;
             case IDM_SECSORT_COUNT_A:
               secsort = SORT_COUNT_A;
               fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                              &expandFlag, &collapseFlag );
               fnSecSortSelect( hwnd, secsort );
               break;
             case IDM_SECSORT_COUNT_D:
               secsort = SORT_COUNT_D;
               fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                              &expandFlag, &collapseFlag );
               fnSecSortSelect( hwnd, secsort );
               break;

             /* Quick key activity code selections */
             case IDM_CTRL_1:
               fnQuickKey(hwnd, hwndPopup, 1, curact);
               break;
             case IDM_CTRL_2:
               fnQuickKey(hwnd, hwndPopup, 2, curact);
               break;
             case IDM_CTRL_3:
               fnQuickKey(hwnd, hwndPopup, 3, curact);
               break;
             case IDM_CTRL_4:
               fnQuickKey(hwnd, hwndPopup, 4, curact);
               break;
             case IDM_CTRL_5:
               fnQuickKey(hwnd, hwndPopup, 5, curact);
               break;
             case IDM_CTRL_6:
               fnQuickKey(hwnd, hwndPopup, 6, curact);
               break;
             case IDM_CTRL_7:
               fnQuickKey(hwnd, hwndPopup, 7, curact);
               break;
             case IDM_CTRL_8:
               fnQuickKey(hwnd, hwndPopup, 8, curact);
               break;
             case IDM_CTRL_9:
               fnQuickKey(hwnd, hwndPopup, 9, curact);
               break;

             case IDM_COMMAND:         /* invoke user exit using DosStartSess */
               fnStartCommand( program, parameters );
               break;

             case IDM_FONT:
                {
                  FONTDLG pfdFontdlg;      /* Font dialog info structure       */
                  HWND    hwndFontDlg;     /* Font dialog window               */
                  RECTL   rectl;
                  ULONG   fontSize;

                  memset(&pfdFontdlg, 0, sizeof(FONTDLG));

                  pfdFontdlg.cbSize = sizeof(FONTDLG);   /*Size of structure  */
                  pfdFontdlg.hpsScreen = WinGetPS(hwnd); /*Screen presentation*/
                  pfdFontdlg.pszFamilyname  = fontname;
                  pfdFontdlg.usFamilyBufLen = FACESIZE;
                  fontSize = fontsize;
                  pfdFontdlg.fxPointSize = MAKEFIXED(fontSize,0);
                  pfdFontdlg.fl = FNTS_CENTER | FNTS_RESETBUTTON |
                                  FNTS_HELPBUTTON | FNTS_FIXEDWIDTHONLY;
                  pfdFontdlg.clrFore = CLR_BLACK;       /* Foreground color   */
                  pfdFontdlg.clrBack = CLR_WHITE;       /* Background color   */
                  pfdFontdlg.usWeight = FWEIGHT_NORMAL;
                  pfdFontdlg.usWidth  = FWIDTH_NORMAL;

                  hwndFontDlg = WinFontDlg(HWND_DESKTOP, hwnd, &pfdFontdlg);
                  if (hwndFontDlg && (pfdFontdlg.lReturn == DID_OK))
                  {
                    HPS         hps;
                    FONTMETRICS fm;

                    fontsize = pfdFontdlg.sNominalPointSize/10;
                    strcpy(fontname, pfdFontdlg.fAttrs.szFacename);
                    sprintf(szText, "%d.%-s", fontsize, fontname);
                    WinSetPresParam( hwnd, PP_FONTNAMESIZE, sizeof( szText ),
                                     szText );

                    hps = WinBeginPaint( hwnd, 0L, 0L );
                    GpiQueryFontMetrics( hps, sizeof(FONTMETRICS), &fm );
                    cxChar = (LONG)fm.lAveCharWidth;
                    cyChar = (LONG)fm.lMaxBaselineExt;
                    cyDesc = (LONG)fm.lMaxDescender;
                    WinEndPaint( hps );

                    rectl.xLeft = 0;         rectl.yBottom = cyClient-cyChar;
                    rectl.xRight = cxClient; rectl.yTop = cyClient;
                    WinInvalidateRect( hwnd, &rectl, FALSE );

                    fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                                   &expandFlag, &collapseFlag );
                  }
                  WinReleasePS(pfdFontdlg.hpsScreen);
                }                      /* end case (IDM_FONT)                 */
                break;

             case IDM_SAVESETTINGS:            // V1.97
                WinPostMsg( hwnd, WM_SAVEAPPLICATION, 0L, 0L );
                WinLoadString( hab, 0L, IDS_SETTINGS, sizeof( szTitle ), szTitle );
                WinLoadString( hab, 0L, IDS_SAVESETWARN, sizeof( szText ), szText );
                WinMessageBox (HWND_DESKTOP, hwnd, szText, szTitle, 1,
                               MB_WARNING | MB_MOVEABLE | MB_OK );
                break;

             case IDM_MAIN:
               {
                 if(subactwin == YES)
                 {
                   strcpy(subact, szBlank);
                   WinEnableMenuItem(WinWindowFromID(WinQueryWindow(hwnd,
                                     QW_PARENT), FID_MENU), IDM_MAIN, FALSE);
                   WinEnableMenuItem(hwndPopup, IDM_MAIN, FALSE );
                   fnProcessItem( hab, hwnd, curact, cxClient, cyChar,
                                  YES, &expandFlag, &collapseFlag );
                 }
                 else
                 {
                   PACTINFO item;

                   item = fnSelectItem( hab, hwnd, YES );
                   if(item)
                   {
                     if(item->expand == '-')
                     {
                       item->expand = '+';
                       fnProcessItem( hab, hwnd, curact, cxClient, cyChar,
                                      YES, &expandFlag, &collapseFlag );
                     }
                   }
                 }
               }
               break;

             case IDM_USINGHELP:       /* Display Using Help Facility window  */
               {                       /* Just post HM_DISPLAY_HELP message   */
                HWND hwndHelpId;

                hwndHelpId = WinQueryHelpInstance (hwnd);
                WinSendMsg (hwndHelpId, HM_DISPLAY_HELP, 0L, 0L);
               }                       /* end case (IDM_USINGHELP)            */
               break;

             case IDM_HELPPRODINFO:    /* Display Product Information window  */
               {
                 LONG lLogoDisplay = -1;
                 WinDlgBox (HWND_DESKTOP, hwnd, wpAboutDlgProc,
                            0L, IDD_ABOUT, (PVOID) &lLogoDisplay);
               }                       /* end case (IDM_HELPPRODINFO)         */
               break;

             case IDM_EXIT:
               WinSendMsg (hwnd, WM_CLOSE, 0L, 0L);
               break;

             default:                  /* Let PM handle the rest of messages  */
               mr = WinDefWindowProc (hwnd, msg, mp1, mp2);
               break;
            }                          /* end switch                          */
        }                              /* end case (WM_COMMAND)               */
        break;

     case WM_HELP:                     /* WM_HELP message processing here     */
        {
         switch (SHORT1FROMMP (mp1))
            {

             case DID_HELP_BUTTON:     /* Help push button pressed for        */
                {                      /* standard Font dialog window         */
                  HWND hwndHelpId;

                  hwndHelpId = WinQueryHelpInstance (hwnd);
                  WinSendMsg(hwndHelpId, HM_DISPLAY_HELP,
                             MPFROM2SHORT(IDH_FONT_DLG, NULL),
                             MPFROMSHORT(HM_RESOURCEID));
                }                      /* end case DID_HELP_BUTTON            */
                break;

             default:                  /* Let PM handle the rest of messages  */
                mr = WinDefWindowProc (hwnd, msg, mp1, mp2);
                break;
            }                          /* end switch                          */
        }                              /* end case (WM_HELP)                  */
        break;

     case UM_SETREFRESH:
        WinStopTimer( hab, hwnd, ID_REFRESHTIMER );
        if( refreshtime > 0 )
        {
          refreshtimecount = refreshtime;
          WinStartTimer( hab, hwnd, ID_REFRESHTIMER, REFRESH_MINUTE );
        }
        break;                         /* end case (UM_SETREFRESH)            */

     /* User defined messages sent by Settings notebook */
     case UM_SETSHOW:
        fnProcessItem( hab, hwnd, curact, cxClient, cyChar, YES,
                       &expandFlag, &collapseFlag );
        break;
     case UM_SETREP:
        if( repsave > 0 )
          WinEnableMenuItem( WinWindowFromID(WinQueryWindow(hwnd,
                             QW_PARENT), FID_MENU), IDM_SAVE, TRUE );
        else
          WinEnableMenuItem( WinWindowFromID(WinQueryWindow(hwnd,
                             QW_PARENT), FID_MENU), IDM_SAVE, FALSE );
        break;
     case UM_SETALARM:
        WinStopTimer( hab, hwnd, ID_ALARMTIMER );
        if( alarmtime > 0 )
        {
          if(curact != NULL)
          {
            if(curact->alarmtime > 0)
              alarmtimecount = curact->alarmtime;
            else
              alarmtimecount = alarmtime;
          }
          else
            alarmtimecount = alarmtime;
          WinStartTimer( hab, hwnd, ID_ALARMTIMER, ALARM_MINUTE );
        }
        break;
     case UM_SETEXIT:
        if( menutext[0] == '\0' || program[0] == '\0' )
          WinSendMsg( WinWindowFromID( WinQueryWindow( hwnd, QW_PARENT ),
                      FID_MENU ), MM_DELETEITEM,
                      MPFROM2SHORT( IDM_COMMAND, TRUE ), NULL );
        else
        {
          WinSendMsg( WinWindowFromID( WinQueryWindow( hwnd, QW_PARENT ),
                      FID_MENU ), MM_DELETEITEM,
                      MPFROM2SHORT( IDM_COMMAND, TRUE ), NULL );
          strcpy(szTitle, menutext);
          strcat(szTitle, "\tCtrl-U");
          WinSendMsg( hwndFile, MM_INSERTITEM, (MPARAM)&mi,
                      (MPARAM)szTitle );
        }
        break;

     case HM_QUERY_KEYS_HELP:          /* User requested keys help            */
       mr = (MRESULT) IDH_HELPKEYS;    /* Return keys help panel id           */
       break;

     case WM_SAVEAPPLICATION:          /* Application about to terminate.     */
       {                               /* Save information in profile data.   */
         SWP         swp;
         PROFILEINFO profinfo;
         PROFILEINFO alarminfo;
         PROFILEINFO reportinfo;
         USERINFO    userinfo;
                                       /* stop tracking the current activity  */
                                       /* this will also force a save of data */
         WinSendMsg( hwnd, WM_COMMAND, MPFROM2SHORT( IDM_STOP, TRUE ), 0L );

         profinfo.bool1  = showexit;   /* these are all the setting variables */
         profinfo.bool2  = showdelete;
         profinfo.bool3  = showreset;
         profinfo.bool4  = initreset;
         profinfo.bool5  = showexclude;
         profinfo.bool6  = showhidden;
         profinfo.ulong1 = units;
         profinfo.ulong2 = refreshtime;
         profinfo.ulong3 = (ULONG)refreshsave;
         profinfo.ulong4 = sort;
         /* profinfo.ulong5 = dateformat; */     /* 1.98 */
         profinfo.ulong6 = minimize;
         strcpy( profinfo.char40, startitem );
         strcpy( profinfo.char80, repline1 );    /* 1.98 */
         PrfWriteProfileData( hini, szAppName, szSettings,
                              &profinfo, sizeof (PROFILEINFO));

         alarminfo.bool1  = alarmsound;
         alarminfo.bool2  = alarmmsg;
         alarminfo.bool3  = alarmedit;
         alarminfo.bool4  = alarmchg;
         alarminfo.bool5  = subactwin;
         alarminfo.bool6  = nofocuschg;
         alarminfo.ulong1 = alarmtime;
         alarminfo.ulong2 = alarmexp;
         alarminfo.ulong3 = xsmlwin;
         alarminfo.ulong4 = gomain;
         alarminfo.ulong5 = repdetails;
         /* alarminfo.ulong6 = hidetotal; */     /* 1.98 */
         strcpy( alarminfo.char40, alarmitem );
         strcpy( alarminfo.char80, repline2 );   /* 1.98 */
         PrfWriteProfileData( hini, szAppName, szAlarm,
                              &alarminfo, sizeof (PROFILEINFO));

         reportinfo.bool1  = repexcl;
         reportinfo.bool2  = rephide;
         reportinfo.bool3  = repdesc;
         reportinfo.bool4  = reptotal;
         reportinfo.bool5  = showresetnew;
         reportinfo.bool6  = repcomm;
         reportinfo.ulong1 = repsave;
         reportinfo.ulong2 = repdays;
         reportinfo.ulong3 = repzero;
         reportinfo.ulong4 = fontsize;
         reportinfo.ulong5 = secsort;
         reportinfo.ulong6 = blankcom;
         strcpy( reportinfo.char40, fontname );
         strcpy( reportinfo.char80, repfile );
         PrfWriteProfileData( hini, szAppName, szReport,
                              &reportinfo, sizeof (PROFILEINFO));

         strcpy( userinfo.char40, menutext );
         strcpy( userinfo.char48, program );
         strcpy( userinfo.char80, parameters );
         PrfWriteProfileData( hini, szAppName, szUser,
                              &userinfo, sizeof (USERINFO));

         WinQueryWindowPos (WinQueryWindow (hwnd, QW_PARENT), &swp);
         if(swp.fl & SWP_MINIMIZE)
         {
           swp.x  = swpWin.x;
           swp.y  = swpWin.y;
           swp.cx = swpWin.cx;
           swp.cy = swpWin.cy;
         }
         PrfWriteProfileData( hini, szAppName, szWinPos, &swp, sizeof (SWP));

         if( hini != 0L )
           PrfCloseProfile( hini );

#if PRTDEBUG
         fprintf(wptr, "WM_SAVEAPPLICATION, profile written to INI file.\n");
         fclose(wptr);
#endif

         mr = WinDefWindowProc (hwnd, msg, mp1, mp2);
       }                               /* end case (WM_SAVEAPPLICATION)       */
       break;

     case WM_CLOSE:                    /* User requested to exit application  */
       {                               /* so just post a WM_QUIT message      */
         if( showexit == YES )
         {

           WinLoadString (hab, 0L, IDS_TITLEEXIT,  50, szTitle);
           WinLoadString (hab, 0L, IDS_EXITPROMPT, 80, szText);

           if (WinMessageBox (HWND_DESKTOP, hwnd, szText, szTitle, 1,
                              MB_MOVEABLE | MB_YESNO | MB_WARNING |
                              MB_DEFBUTTON2 ) == MBID_YES)
           {
             if( ulJuldate != fnJulDate() && repsave > 0 )
               WinSendMsg(hwnd, WM_COMMAND, MPFROM2SHORT(IDM_SAVE, TRUE), 0L);
             WinSendMsg(hwnd, WM_COMMAND, MPFROM2SHORT(IDM_STOP, TRUE), 0L);
             WinPostMsg (hwnd, WM_QUIT, 0L, 0L); /* user really wants to exit */
           }
         }
         else
         {
           if( ulJuldate != fnJulDate() && repsave > 0 )
             WinSendMsg( hwnd, WM_COMMAND, MPFROM2SHORT( IDM_SAVE,
                         TRUE ), 0L );
           WinSendMsg( hwnd, WM_COMMAND, MPFROM2SHORT( IDM_STOP, TRUE ), 0L );
           WinPostMsg (hwnd, WM_QUIT, 0L, 0L);
         }
        }                              /* end case WM_CLOSE                   */
        break;

     case WM_DESTROY:                  /* Window about to be destroyed.       */
        {
          DosRequestMutexSem( hmtx, SEM_INDEFINITE_WAIT );
          fnFreeList( );               /* free linked list memory             */
          fnFreeReportList( );         /* free linked list memory             */
          DosReleaseMutexSem( hmtx );
          DosCloseMutexSem( hmtx );
          DosCloseMutexSem( hmtxNB );
        }                              /* end case (WM_DESTROY)               */
        break;

     default:                          /* Let PM handle rest of messages      */
        mr = WinDefWindowProc (hwnd, msg, mp1, mp2);
        break;

    }                                  /* end main switch statement           */

 return mr;

}


/******************************************************************************/
/*                                                                            */
/*                       F I L E   F U N C T I O N S                          */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/* fnGetActivityInfo: Read control file and create linked list of activity    */
/*                    codes.                                                  */
/*                                                                            */
/******************************************************************************/

APIRET fnGetActivityInfo( VOID )

{

  CHAR     inline[MAXLENGTH];          /* work string                         */
  CHAR     timer[7];
  FILE     *fpinfile, *fpoutfile;      /* file pointers ...                   */
  PACTINFO activity;
  CHAR     szCurdate[11];
  CHAR     szJuldate[11];
  CHAR     outstring[MAXLENGTH], coutstring[MAXLENGTH];
  ULONG    juldate, filejuldate;
  ULONG    rc, i;
  float    reptotal;
  time_t   now;

  fnDate( szCurdate );  /* 1.98 */
  now = time( NULL );
  strftime( szJuldate, sizeof(szJuldate), "%Y%j", localtime( &now ) );
  juldate = atol( szJuldate );
  outstring[0]  = '\0';
  coutstring[0] = '\0';
  szJuldate[0]  = '\0';

  totalactivities = 0;
  reptotal = 0.0;
  if( fpinfile = fopen( Outfile, "r" ))
  {
    while( 1 )                             /* read one line at a time until   */
    {                                      /* EOF                             */
      if( fgets( inline, MAXLENGTH - 1, fpinfile ) == NULL )
        if( feof( fpinfile ) )             /* this is EOF, bail out           */
          break;
        else
          return( 3 );                     /* trouble reading line, exit      */

      if( inline[0] != COMMENT_CHAR )
      {
        if( inline[0] == '!' )
        {
          fnSubstr( inline, szJuldate, 2, 10 );
          if( strcmp( szJuldate, szCurdate ) == 0 )
            newDay = NO;
          else
            newDay = YES;
          fnSubstr( inline, szJuldate, 13, 7 );
          fnSubstr( inline, outstring, 2, 28 );
          /* 1.98 */
          if((outstring[27] == '.') || (outstring[27] == ':'))
            outstring[27] = HMS_CHAR;
          strcat( outstring, "                    " );
          strcpy(coutstring, outstring);
          strcat(coutstring, " ");
        }
        else
        {
          activity = (PACTINFO) malloc(sizeof(ACTINFO));
          if(!activity)                /* Allocate memory for this item in    */
            return( ERROR_MEMORY );    /* linked list, address stored in      */
                                       /* variable called activity            */
          fnSubstr( inline, inline, 1, strlen( inline ) - 1 );

          if( inline[0] == ' ' )
          {
            activity->exclude = ' ';
            activity->hide    = ' ';
          }
          else
          {
            if( inline[0] == DELETE_CHAR )
            {
              activity->exclude = ' ';
              activity->hide    = ' ';
            }
            else
            {
              if( inline[0] == EXCLUDE_CHAR )
              {
                activity->exclude = EXCLUDE_CHAR;
                activity->hide    = ' ';
              }
              else
              {
                if( inline[0] == HIDE_CHAR )
                {
                  activity->exclude = ' ';
                  activity->hide    = HIDE_CHAR;
                }
                else
                {
                  activity->exclude = EXCLUDE_CHAR;
                  activity->hide    = HIDE_CHAR;
                }
              }
            }
          }
          fnSubstr( inline, activity->code, 2, CODE_WIDTH );
          activity->hotkey = inline[9];
          fnSubstr( inline, activity->description, 11, DESC_WIDTH );
          fnStrip(activity->description, activity->description, 'B', ' ');
          activity->lock = inline[30];
          fnSubstr( inline, timer, 32, 6 );
          activity->timer = atof( timer );
          activity->expand = inline[37];
          fnSubstr( inline, timer, 39, 3 );
          activity->count = atoi( timer );
          if( activity->count < 0 )
            activity->count = 0;
          fnSubstr( inline, activity->comments, 43, COMM_WIDTH );
          fnStrip(activity->comments, activity->comments, 'B', ' ');
          fnSubstr( inline, activity->program, 74, PROG_WIDTH );
          fnStrip(activity->program, activity->program, 'B', ' ');
          fnSubstr( inline, activity->parameters, 123, PROG_WIDTH );
          fnStrip(activity->parameters, activity->parameters, 'B', ' ');
          fnSubstr( inline, activity->winfocus, 172, WFOC_WIDTH );
          fnStrip(activity->winfocus, activity->winfocus, 'B', ' ');
          fnSubstr( inline, activity->parent, 193, CODE_WIDTH );
          fnSubstr( inline, timer, 202, 3 );
          activity->children = atoi( timer );
          if( activity->children < 0 )
            activity->children = 0;
          fnSubstr( inline, timer, 206, 3 );
          activity->alarmtime = atoi( timer );
          if( activity->alarmtime < 0 )
            activity->alarmtime = 0;
          if(activity->children > 0 && activity->expand == ' ')
            activity->expand = '+';

          if( (activity->hide == HIDE_CHAR && rephide == NO ) ||
              (activity->exclude == EXCLUDE_CHAR && repexcl == NO ) );
          else
          {
            sprintf( szText, " %-8s %3d %7.2f %-8s", activity->code,
                     activity->count, activity->timer, activity->parent );
            strcat( outstring, szText );
            sprintf(szText, "%-30s", activity->comments);
            strcat(coutstring, szText);
            if(activity->children == 0)
              reptotal = reptotal + activity->timer;
          }

          if( initreset == YES && newDay == YES )
          {
            activity->timer = (float)0;
            activity->count = 0;
          }
          if( blankcom == YES && newDay == YES )
            activity->comments[0] = '\0';

          fnPutLinkList( activity );
          totalactivities++;
        }                                  /* end else                        */
      }                                    /* end if line is not a comment    */
    }                                      /* end while( 1 )                  */
    fclose( fpinfile );                    /* cleanup, close all files        */
  }                                        /* end if file opened ok           */
  else                                     /* unable to open input file       */
    return ( ERROR_OPEN_FILE );

  sprintf( szText, "%7.2f", reptotal );
  for( i=0; i<7; i++ )
    outstring[i+19] = szText[i];
  if(totalactivities > 0)
    rc = fnSaveReport( newDay, juldate, outstring, coutstring, szJuldate );

  if( initreset == YES && newDay == NO )   /* times were not reset because it */
    return( WARN_RESET );                  /* is still the same day, warn user*/

#if PRTDEBUG
  fprintf(wptr, "Completed fnGetActivityInfo().\n");
#endif

  return( 0 );                             /* normal exit from this routine   */

}

/******************************************************************************/
/*                                                                            */
/* fnPutActivityInfo: Write activities codes/description to control file.     */
/*                                                                            */
/******************************************************************************/

VOID fnPutActivityInfo( VOID )

{

  PACTINFO activity;
  CHAR     inline[MAXLENGTH];          /* work string                         */
  CHAR     first;
  FILE     *fpinfile;                  /* control file pointer                */
  LONG     rc;                         /* return code                         */

  DosRequestMutexSem( hmtx, SEM_INDEFINITE_WAIT );

  if(newDay == YES && totalactivities > 0)
  {
    remove( BackOutfile );
    rename( Outfile, BackOutfile );
    newDay = NO;
  }

  strcpy( inline, "!" );
  fnDateInfo( inline );

  if( fpinfile = fopen( Outfile, "w" ))
  {
    fputs( inline, fpinfile );
                                           /* Write some comments to warn     */
    fputs( "\n*\n", fpinfile );            /* user not to erase or edit file  */
    fputs( "* <PLEASE DO NOT ERASE OR EDIT THIS FILE>\n", fpinfile );
    fputs( "*\n", fpinfile );

    activity = start;
    while( activity )                      /* Loop thru the activity LL       */
    {
      if( activity->exclude == ' ' && activity->hide == ' ' )
        first = ' ';
      else
      {
        if( activity->exclude == EXCLUDE_CHAR && activity->hide == HIDE_CHAR )
          first = EX_HIDE_CHAR;
        else
        {
          if( activity->exclude == EXCLUDE_CHAR )
            first = EXCLUDE_CHAR;
          else
            first = HIDE_CHAR;
        }
      }
      sprintf( inline, "%c%-8s%c%-20s%c%6.2f%c%3d %-30s %-48s %-48s %-20s %-8s %3d %3d\n",
               first, activity->code, activity->hotkey,
               activity->description, activity->lock,
               activity->timer, activity->expand, activity->count,
               activity->comments,
               activity->program, activity->parameters,
               activity->winfocus, activity->parent, activity->children,
               activity->alarmtime );
      rc = fputs( inline, fpinfile );      /* write string to output file     */
      activity = (PACTINFO)activity->next; /* get next activity code in list  */
    }                                      /* End while(activity)             */
    fclose( fpinfile );                    /* cleanup, close file             */
  }
  else
  {
  }

  DosReleaseMutexSem( hmtx );

#if PRTDEBUG
  fprintf(wptr, "Completed fnPutActivityInfo().\n");
#endif

  DosExit( EXIT_THREAD, 0L );

}

/******************************************************************************/
/*                                                                            */
/* fnSaveReport: Read and save report file.                                   */
/*                                                                            */
/******************************************************************************/

APIRET fnSaveReport( BOOL newday, ULONG juldate, CHAR *outstring,
                     CHAR *coutstring, CHAR *filedate )

{
  FILE     *fpinfile, *fpoutfile,      /* file pointers ...                   */
           *fpincfile, *fpoutcfile;
  PREPINFO report;
  CHAR     inline[MAXLENGTH];          /* work string                         */
  CHAR     cline[MAXLENGTH];           /* work string                         */
  CHAR     szJuldate[8];
  ULONG    filejuldate;
  APIRET   rc;
                                       /* prune report file if needed         */
  if( repsave == YES && repdays > 0 && newday == YES )
  {
    remove( BackReportfile );
    remove( BackCommentfile );
    rc = rename( Commentfile, BackCommentfile );
    rc = rename( Reportfile, BackReportfile );
    if( rc == 0 )
    {
      if( (fpinfile = fopen( Reportfile, "w" )) &&
          (fpincfile = fopen( Commentfile, "w" )) )
      {
        if( (fpoutfile = fopen( BackReportfile, "r" )) &&
            (fpoutcfile = fopen( BackCommentfile, "r" )) )
        {
          while( 1 )                       /* read one line at a time until   */
          {                                /* EOF                             */
            if( fgets( inline, MAXLENGTH - 1, fpoutfile ) == NULL )
              if( feof( fpoutfile ) )      /* this is EOF, bail out           */
                break;
              else
                return( 3 );               /* trouble reading line, exit      */
            fgets( cline, MAXLENGTH - 1, fpoutcfile );

            fnSubstr( inline, szJuldate, 12, 7 );
            filejuldate = atol( szJuldate );
            if( fnCalJulDate(filejuldate, juldate, repdays) &&
                filejuldate != atol( filedate ) )
            {
              fputs( inline, fpinfile );
              fputs( cline, fpincfile );
            }
          }
          fclose( fpoutfile );
          fclose( fpoutcfile );
        }
//      else
//        return ( ERROR_OPEN_FILE );
        fclose( fpinfile );
        fclose( fpincfile );
      }
//    else
//      return ( ERROR_OPEN_FILE );
    }                                      /* end if rc == 0                  */
  }                                        /* end if prune report             */
                                           /* save latest data to report file */
  if( repsave == YES && newday == YES && filedate[0] != '\0' )
  {
    if( fpinfile = fopen( Reportfile, "a" ))
    {
      strcat( outstring, "\n" );
      fputs( outstring, fpinfile );
      fclose( fpinfile );
    }
    else
      return ( ERROR_OPEN_FILE );
    if( fpincfile = fopen( Commentfile, "a" ))
    {
      strcat( coutstring, "\n" );
      fputs( coutstring, fpincfile );
      fclose( fpincfile );
    }
    else
      return ( ERROR_OPEN_FILE );
  }

  if( (fpinfile = fopen( Reportfile, "r" )) &&
      (fpincfile = fopen( Commentfile, "r" )) )
  {
    totalreports = 0;
    while( 1 )                             /* read one line at a time until   */
    {                                      /* EOF                             */
      if( fgets( inline, MAXLENGTH - 1, fpinfile ) == NULL )
        if( feof( fpinfile ) )             /* this is EOF, bail out           */
          break;
        else
          return( 3 );                     /* trouble reading line, exit      */
      fgets(cline, MAXLENGTH - 1, fpincfile);
      fnStrip(cline, cline, 'T', '\n');

      report = (PREPINFO) malloc(sizeof(REPINFO));
      if(!report)                      /* allocate memory for this item in    */
        return( ERROR_MEMORY );        /* linked list, address stored in      */
                                       /* variable called report              */
      fnSubstr( inline, inline, 1, strlen( inline ) - 1 );
      fnSubstr( inline, report->repdate, 1, 10 );
      fnSubstr( inline, szJuldate, 12, 7 );
      report->juldate = atol( szJuldate );
      fnSubstr( inline, szJuldate, 20, 7 );
      report->total = atof( szJuldate );
      report->units = inline[27];
      /* 1.98 */
      if((report->units == '.') || (report->units == ':'))
        report->units = HMS_CHAR;
      if(strlen(inline) > 50)                  // V1.98
        fnSubstr( inline, report->repdata, 50, strlen( inline ) - 49 );
      else
        strcpy( report->repdata, "");
      report->selected = NO;
      if(strlen(cline) > 50)                   // V1.98
        fnSubstr( cline, report->commentdata, 50, strlen( cline ) - 49 );
      else
        strcpy( report->commentdata, "");

      fnPutReportLinkList( report );
      totalreports++;
    }                                      /* end while( 1 )                  */
    fclose( fpinfile );                    /* cleanup, close all files        */
    fclose( fpincfile );
    fnSortReport( 2 );
  }                                        /* end if file opened ok           */
//else                                     /* unable to open input file       */
//  return ( ERROR_OPEN_FILE );

  return( 0 );

}

/******************************************************************************/
/*                                                                            */
/* fnSaveReportList:                                                          */
/*                                                                            */
/******************************************************************************/

APIRET fnSaveReportList(VOID)

{
  FILE     *fpinfile, *fpoutfile,      /* file pointers ...                   */
           *fpincfile, *fpoutcfile;
  PREPINFO report;
  CHAR     inline[MAXLENGTH];          /* work string                         */
  CHAR     header[50];
  APIRET   rc;
                                       /* prune report file if needed         */
  remove( BackReportfile );
  remove( BackCommentfile );
  rc = rename( Commentfile, BackCommentfile );
  rc = rename( Reportfile, BackReportfile );
  if( rc == 0 )
  {
    if( (fpinfile = fopen( Reportfile, "w" )) &&
        (fpincfile = fopen( Commentfile, "w" )) )
    {
      report = startrep;
      while(report)
      {
        sprintf(header, "%10s %7d %7.2f %c %20s", report->repdate,
                report->juldate, report->total, report->units, " ");
        strcpy(inline, header);
        strcat(inline, report->repdata);
        strcat(inline, "\n");
        fputs(inline, fpinfile);

        strcpy(inline, header);
        strcat(inline, report->commentdata);
        strcat(inline, "\n");
        fputs(inline, fpincfile);

        report = (PREPINFO)report->next;
      }
      fclose( fpinfile );
      fclose( fpincfile );
    }
//  else
//    return ( ERROR_OPEN_FILE );
  }
//else
//  return ( ERROR_OPEN_FILE );

  return(0);
}

/******************************************************************************/
/*                                                                            */
/*                     G E N E R A L    F U N C T I O N S                     */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/* fnInitialize: Initialize global variables.                                 */
/*                                                                            */
/******************************************************************************/

VOID fnInitialize( USHORT type )
{

  switch( type )
  {
    case( IDD_OPTIONS ):               /* Setting values                      */
      showexclude = YES;               /* how totals shown on status line     */
      showhidden  = NO;                /* hide activity codes as marked       */
      initreset   = YES;               /* reset times to 0 upon startup       */
      refreshtime = 60;                /* automated refresh interval (min)    */
      refreshsave = YES;               /* save to file when refresh           */
      minimize    = NO;                /* minimize when activity tracked      */
      smallwin    = NORMAL_WINDOW;
      blankcom    = NO;                /* blank comments for new day          */
      /*hidetotal   = NO;           1.98  add hidden activities time to total */
      gomain      = NO;                /* go to main list when sub-act start  */
      nofocuschg  = NO;                /* No focus change                     */
      subactwin   = NO;                /* Sub-activity window                 */
      strcpy(startitem, szBlank);      /* default starting activity or NULL   */
      strcat(startitem, " ");
      strcat(startitem, szBlank);
      break;
    case( IDD_CONFIRM ):               /* Confirmation setting values         */
      showexit    = YES;               /* display exit confirmation box?      */
      showdelete  = YES;               /* display delete confirmation box?    */
      showreset   = YES;               /* display reset confirmation box?     */
      showresetnew = YES;              /* display reset confirm for new day?  */
      break;
    case( IDD_REPSET ):                /* Report settings                     */
      repsave     = YES;               /* save daily data to report file?     */
      repdays     = 365;               /* how many days to save daily reports */
      reptotal    = NO;                /* Total or individual reports?        */
      repexcl     = YES;               /* show excluded activities in report  */
      rephide     = YES;               /* show hidden activities in report    */
      repdesc     = NO;                /* show description in report          */
      repcomm     = NO;                /* show comments in report             */
      repzero     = YES;               /* show 0 times in report              */
      repdetails  = YES;               /* show details in report              */
      repfile[0]  = '\0';              /* saved report filename               */
      repline1[0] = '\0';              /* report notes                        */
      repline2[0] = '\0';
      break;
    case( IDD_TIME ):                  /* Time settings                       */
      units       = UNITS_HOURS;       /* time units (minutes or hours)       */
      secunits    = units;
      break;
    case( IDD_DATE ):                  /* Date settings                       */
      /* dateformat  = DATE_FORMAT_1;     date format to show on reports 1.98 */
      break;
    case( IDD_ALARM ):                 /* Alarm values                        */
      alarmtime   = 0;                 /* alarm timer (min)                   */
      alarmsound  = NO;                /* beep when alarm expires             */
      alarmmsg    = NO;                /* display message box when alarm      */
      alarmedit   = NO;                /* edit activity when alarm expires    */
      alarmchg    = NO;                /* set alarm time when activity started*/
      alarmexp    = 1;                 /* alarm expire (min)                  */
      strcpy(alarmitem, "$CURACT$");   /* default alarm activity to current   */
      strcat(alarmitem, " ");
      strcat(alarmitem, szBlank);
      break;
    case( IDD_USEREXIT ):              /* User Exit values                    */
      menutext[0]   = '\0';            /* Text shown in File pull-down        */
      program[0]    = '\0';            /* Program name (full path required)   */
      parameters[0] = '\0';            /* Parameters to be passed             */
      break;
    default:
      break;

  }
}

/******************************************************************************/
/*                                                                            */
/* fnProfileInfo: Get profile information.                                    */
/*                                                                            */
/******************************************************************************/

VOID fnProfileInfo( HAB hab, CHAR *profileDir)
{

  ULONG       ulSize;
  PROFILEINFO profinfo;
  PROFILEINFO alarminfo;
  PROFILEINFO reportinfo;
  USERINFO    userinfo;

  WinLoadString (hab, 0L, IDS_ININAME, 50, szTitle );
  if( profileDir[0] != '\0' )
  {
    strcat( profileDir, "\\" );
    strcat( profileDir, szTitle );
  }
  else
    strcpy( profileDir, szTitle );
  hini = PrfOpenProfile( hab, profileDir );
  if( hini == 0L )
    WinMessageBox( HWND_DESKTOP, 0L, "Error loading initialization profile.",
                   "Profile Error", 1, MB_ERROR | MB_OK | MB_MOVEABLE );

  /* Option settings */
  ulSize = sizeof (PROFILEINFO );
  if (PrfQueryProfileData( hini, szAppName, szSettings, &profinfo, &ulSize ))
  {
    showexit      = profinfo.bool1;
    if( showexit != NO && showexit != YES )
      showexit = YES;
    showdelete    = profinfo.bool2;
    if( showdelete != NO && showdelete != YES )
      showdelete = YES;
    showreset     = profinfo.bool3;
    if( showreset != NO && showreset != YES )
      showreset = YES;
    initreset     = profinfo.bool4;
    if( initreset != NO && initreset != YES )
      initreset = YES;
    showexclude   = profinfo.bool5;
    if( showexclude != NO && showexclude != YES )
      showexclude = YES;
    showhidden    = profinfo.bool6;
    if( showhidden != NO && showhidden != YES )
      showhidden = NO;
    units         = profinfo.ulong1;
    if( units != UNITS_MINUTES && units != UNITS_HOURS &&
        units != UNITS_HMS     && units != UNITS_HM )     /* 1.98 */
//      units != UNITS_TIME_C  && units != UNITS_TIME_D )
      units = UNITS_HOURS;
    if( units == UNITS_HOURS)
      secunits = units;
    else
      secunits = UNITS_MINUTES;
    refreshtime   = profinfo.ulong2;
    if( refreshtime < 0 )
      refreshtime = 60;
    refreshsave   = (BOOL)profinfo.ulong3;
    if( refreshsave != NO && refreshsave != YES )
      refreshsave = YES;
    sort = profinfo.ulong4;
    if( sort != SORT_NONE   && sort != SORT_CODE_A && sort != SORT_CODE_D &&
        sort != SORT_DESC_A && sort != SORT_DESC_D && sort != SORT_TIME_A &&
        sort != SORT_TIME_D && sort != SORT_PERC_A && sort != SORT_PERC_D &&
        sort != SORT_COUNT_A && sort != SORT_COUNT_D )
     sort = SORT_NONE;
/* 1.98 */
//  dateformat    = profinfo.ulong5;
//  if( dateformat != DATE_FORMAT_1 && dateformat != DATE_FORMAT_2 &&
//      dateformat != DATE_FORMAT_3 )
//    dateformat = DATE_FORMAT_1;
    minimize = (BOOL)profinfo.ulong6;
    if( minimize != NO && minimize != YES )
      minimize = NO;
    strcpy( startitem, profinfo.char40 );
    strcpy( repline1,  profinfo.char80 );   /* 1.98 */
  }
  else
  {
    sort = SORT_NONE;
    fnInitialize( IDD_OPTIONS );
    fnInitialize( IDD_CONFIRM );
    fnInitialize( IDD_DATE );
    fnInitialize( IDD_TIME );
  }
  fnPadString(startitem, 2*CODE_WIDTH+1);

  /* Alarm settings */
  ulSize = sizeof (PROFILEINFO );
  if (PrfQueryProfileData( hini, szAppName, szAlarm, &alarminfo, &ulSize ))
  {
    alarmsound = alarminfo.bool1;
    alarmmsg   = alarminfo.bool2;
    alarmedit  = alarminfo.bool3;
    alarmchg   = alarminfo.bool4;
    subactwin  = alarminfo.bool5;
    if( subactwin != NO && subactwin != YES )
      subactwin = NO;
    nofocuschg = alarminfo.bool6;
    if( nofocuschg != NO && nofocuschg != YES )
      nofocuschg = NO;
    alarmtime  = alarminfo.ulong1;
    alarmexp   = alarminfo.ulong2;
    if( alarmexp < 1 )
      alarmexp = 1;
    smallwin   = alarminfo.ulong3;
    if( smallwin != SMALL_WINDOW && smallwin != NORMAL_WINDOW )
      smallwin = NORMAL_WINDOW;
    gomain     = alarminfo.ulong4;
    if( gomain != NO && gomain != YES )
      gomain = NO;
    repdetails = alarminfo.ulong5;
    if( repdetails != NO && repdetails != YES )
      repdetails = YES;
/* 1.98 */
//  hidetotal  = alarminfo.ulong6;
//  if( hidetotal != NO && hidetotal != YES )
//    hidetotal = NO;
    strcpy( alarmitem, alarminfo.char40 );
    strcpy( repline2,  alarminfo.char80 );   /* 1.98 */
  }
  else
  {
    /* hidetotal  = NO; */   /* 1.98 */
    repdetails = YES;
    gomain     = NO;
    nofocuschg = NO;
    subactwin  = NO;
    alarmexp   = 1;
    smallwin   = NORMAL_WINDOW;
    fnInitialize( IDD_ALARM );
  }
  fnPadString(alarmitem, 2*CODE_WIDTH+1);

  /* Report settings */
  ulSize = sizeof (PROFILEINFO );
  if (PrfQueryProfileData( hini, szAppName, szReport, &reportinfo, &ulSize ))
  {
    repexcl    = reportinfo.bool1;
    rephide    = reportinfo.bool2;
    repdesc    = reportinfo.bool3;
    reptotal   = reportinfo.bool4;
    showresetnew = reportinfo.bool5;
    if( showresetnew != NO && showresetnew != YES )
      showresetnew = YES;
    repcomm    = reportinfo.bool6;
    if( repcomm != NO && repcomm != YES )
      repcomm = YES;
    repsave    = reportinfo.ulong1;
    if( repsave != NO && repsave != YES )
      repsave = YES;
    repdays    = reportinfo.ulong2;
    if( repdays < 0 )
      repdays = 7;
    repzero    = reportinfo.ulong3;
    if( repzero != NO && repzero != YES )
      repzero = YES;
    secsort = reportinfo.ulong5;
    if( secsort != SORT_NONE   && secsort != SORT_CODE_A &&
        secsort != SORT_CODE_D && secsort != SORT_DESC_A &&
        secsort != SORT_DESC_D && secsort != SORT_TIME_A &&
        secsort != SORT_TIME_D && secsort != SORT_PERC_A &&
        secsort != SORT_PERC_D && secsort != SORT_COUNT_A &&
        secsort != SORT_COUNT_D )
      secsort = SORT_NONE;
    strcpy( repfile, reportinfo.char80 );
    fontsize = reportinfo.ulong4;
    strcpy(fontname, reportinfo.char40);
    if(fontsize == 0)
    {
      fontsize = 10;
      strcpy( fontname, "System Monospaced" );
    }
    blankcom   = (BOOL)reportinfo.ulong6;
    if( blankcom != YES && blankcom != NO )
      blankcom = NO;
  }
  else
  {
    secsort      = SORT_NONE;
    showresetnew = YES;
    fontsize = 10;
    strcpy( fontname, "System Monospaced" );
    blankcom     = NO;
    fnInitialize( IDD_REPSET );
  }
  xsmlwin = smallwin;

  /* User Exit */
  ulSize = sizeof ( USERINFO );
  if (PrfQueryProfileData( hini, szAppName, szUser, &userinfo, &ulSize ))
  {
    strcpy( menutext, userinfo.char40 );
    strcpy( program, userinfo.char48 );
    strcpy( parameters, userinfo.char80 );
  }
  else
    fnInitialize( IDD_USEREXIT );

}

/******************************************************************************/
/*                                                                            */
/* fnListBoxEntry: Populate the main window list box with activity codes.     */
/*                                                                            */
/******************************************************************************/

VOID fnListBoxEntry( HWND hwnd, PACTINFO curact, ULONG *expandFlag,
                     ULONG *collapseFlag )
{

  PACTINFO  item;
  PACTINFO  selActivity = NULL;
  PACTINFO  topActivity = NULL;
  APIRET    rc;
  LONG      sel;
  LONG      selitem;
  LONG      topindex;

  totalitems = 0;
  sel        = 0;

  *collapseFlag = FALSE;
  *expandFlag   = FALSE;

  selitem   = (LONG)WinQueryLboxSelectedItem( hwndList );
  if(selitem > -1)
    selActivity = fnGetLBoxActivity(selitem);
  topindex  = (LONG)WinSendMsg( hwndList, LM_QUERYTOPINDEX, 0L, 0L );
  if(topindex != LIT_NONE)
    topActivity = fnGetLBoxActivity(topindex);

  /* Insert each activity information in the list box. Data found in the      */
  /* linked list.                                                             */

  WinEnableWindowUpdate( hwndList, FALSE );

  WinSetPresParam( hwndList, PP_FONTNAMESIZE, sizeof("10.System Proportional"),
                   "8.System Proportional" );

  WinSendMsg( hwndList, LM_DELETEALL, MPFROMSHORT(0), (MPARAM) NULL );

  item = start;
  while( item )
  {
    if(item->hide!=' ' && showhidden==YES ||
      (strcmp(item->parent, subact)!=0 && subactwin==YES))
      item->display = -1;
    else                               /* insert each item at the end of the  */
    {                                  /* list box                            */
      if(subactwin == YES)
      {
        fnAddEntryToListBox(item, selActivity, topActivity, sel);
        sel++;
      }
      else
      {
        if(strcmp(item->parent, szBlank) == 0)
        {
          fnAddEntryToListBox(item, selActivity, topActivity, sel);
          sel++;

          if(item->expand == '+')      /* Check if any activities collapsed   */
            *expandFlag   = TRUE;      /* set expand flag to true             */
          if(item->expand == '-')      /* Check if any activities expanded    */
            *collapseFlag = TRUE;      /* set collapse flag to true           */

          if(item->children > 0)
          {
            PACTINFO item1;

            item1 = start;
            while( item1 )
            {
              if(strcmp(item1->parent, item->code) == 0)
              {
                if(item1->hide != ' ' && showhidden == YES)
                  item1->display = -1;
                else
                {
                  if(item->expand == '-')
                  {
                    fnAddEntryToListBox(item1, selActivity, topActivity, sel);
                    sel++;
                  }
                  else
                    item1->display = -1;
                }
              }
              item1 = (PACTINFO)item1->next;
            }                         /* end while(item1)                    */
          }                           /* end if(item->children > 0)          */
        }                             /* end if item->parent == szBlank      */
      }
    }                                 /* end else                            */
    item = (PACTINFO)item->next;      /* get next item in the linked list    */
  }                                   /* end do while( item )                */

  sprintf(szText, "%d.%-s", fontsize, fontname);
  WinSetPresParam( hwndList, PP_FONTNAMESIZE, sizeof( szText ), szText );

  WinEnableWindowUpdate( hwndList, TRUE );

  if(topActivity)
  {
    item = start;
    while( item )
    {
      if(item == topActivity && item->display > -1)
        WinSendMsg (hwndList, LM_SETTOPINDEX, MPFROMSHORT(item->display), 0L);
      item = (PACTINFO)item->next;     /* get next item in the linked list    */
    }
  }

  // Enable/Disable Collapse All/Expand All menu items
  WinEnableMenuItem(WinWindowFromID(WinQueryWindow(hwnd, QW_PARENT),
                    FID_MENU), IDM_EXPANDALL, *expandFlag);
  WinEnableMenuItem(WinWindowFromID(WinQueryWindow(hwnd, QW_PARENT),
                    FID_MENU), IDM_COLLAPSEALL, *collapseFlag);

}

/******************************************************************************/
/*                                                                            */
/* fnAddEntryToListBox: Add activity line to listbox.                         */
/*                                                                            */
/******************************************************************************/

VOID fnAddEntryToListBox(PACTINFO item, PACTINFO selectAct, PACTINFO topAct,
                         LONG sel)
{

  CHAR  subflag;
  CHAR  szTime[9];
  CHAR  code[CODE_WIDTH+3];
  float percent;

  if( showexclude == YES )
  {
    if( item->exclude == EXCLUDE_CHAR )
      percent = (float)0.0;
    else
    {
      if( extottime > 0 )
        percent = item->timer * 100 / extottime;
      else
        percent = (float)0.0;
    }
  }
  else
  {
    if( extottime > 0 )
      percent = item->timer * 100 / totaltime;
    else
      percent = (float)0.0;
  }

  if(strcmp(item->parent, szBlank) == 0 || subactwin == YES)
    strcpy(code, item->code);
  else
  {
    strcpy(code, "  ");
    strcat(code, item->code);
  }

  if(subactwin == YES)
  {
    if(item->children > 0)
      subflag = 16;
    else
      subflag = ' ';
  }
  else
    subflag = item->expand;

  if( units == UNITS_HOURS || units == UNITS_MINUTES )
    sprintf( item->listtext, "%c%c%-10s %c %-20s %8.2f %5.1f %3d  %-30s",
             item->showflag, subflag, code, item->hotkey, item->description,
             item->timer, percent, item->count, item->comments );
  else
  {
    fnConvertTime( item->timer, secunits, units, szTime );
    sprintf( item->listtext, "%c%c%-10s %c %-20s %8s %5.1f %3d  %-30s",
             item->showflag, subflag, code, item->hotkey, item->description,
             szTime, percent, item->count, item->comments );
  }

  WinSendMsg (hwndList, LM_INSERTITEM, MPFROMSHORT(LIT_END),
              MPFROMP (item->listtext));
  // Select the last selected item
  if( selectAct == item )
    WinSendMsg (hwndList, LM_SELECTITEM, MPFROMSHORT(totalitems),
                MPFROMSHORT(TRUE) );
  item->display = sel;
  totalitems++;

}

/******************************************************************************/
/*                                                                            */
/* fnGetSelectedItem: Based on the mouse position, get item in listbox.       */
/*                    Returns -1 if mouse not within items.                   */
/*                                                                            */
/******************************************************************************/

LONG fnGetSelectedItem(HWND hwnd, LONG y, LONG cyClient, LONG cyChar)
{

  LONG top, item;

  if( smallwin == NORMAL_WINDOW )
    item = (( cyClient - cyChar - y ) / cyChar );
  else
    item = (( cyClient - y ) / cyChar );
  top  = (LONG)WinSendMsg( WinWindowFromID( hwnd, ID_LISTBOX ),
                           LM_QUERYTOPINDEX, 0L, 0L );
  if( top == LIT_NONE || totalitems == 0 )
    item = -1;
  else
  {
    item = item + top;
    if( item > totalitems - 1 )
      item = -1;
  }
  return(item);
}

/******************************************************************************/
/*                                                                            */
/* fnSelectItem: Determine which item was selected, return activity code      */
/*               list pointer address.                                        */
/*                                                                            */
/******************************************************************************/

PACTINFO fnSelectItem( HAB hab, HWND hwnd, BOOL display )
{

   PACTINFO listitem;
   SHORT     selitem;
   ULONG     i;

   selitem = WinQueryLboxSelectedItem( hwndList );
   if( selitem < 0 )                   /* no activity selected in list box    */
   {                                   /* inform the user using a message box */
     if(display == YES)
     {
       WinLoadString (hab, 0L, IDS_LISTTITLE, 50, szTitle);
       WinLoadString (hab, 0L, IDS_SELECT,   80, szText);
       WinMessageBox (HWND_DESKTOP, hwnd, szText, szTitle,
                      0, MB_WARNING | MB_OK | MB_MOVEABLE);
     }
     return (PACTINFO)NULL;           /* return NULL to indicate error        */
   }
   else                                /* use the index returned to point the */
   {                                   /* return address to the directory     */
     listitem = start;                 /* seleted                             */
     while(listitem)
     {
       if(listitem->display == selitem)
         break;
       listitem = (PACTINFO)listitem->next;
     }
     return listitem;
   }

}

/******************************************************************************/
/*                                                                            */
/* fnSelectActivity: Select the activity code.                                */
/*                                                                            */
/******************************************************************************/

BOOL fnSelectActivity( HWND hwnd, HWND hwndPopup, CHAR *activity,
                       CHAR *parent, PACTINFO curact )
{

  PACTINFO item;
  ULONG    expandFlag, collapseFlag;

  item = fnFindActivity(activity, parent);
  if(item)
  {

    if(strcmp(item->parent, subact) != 0 && subactwin == YES)
    {                                  /* Now check if the parent is the same */
      strcpy(subact, item->parent);    /* as the current sub-activity         */
      fnListBoxEntry( hwnd, curact, &expandFlag, &collapseFlag );
      if(strcmp(subact, szBlank) != 0) /* Enable/disable the menu choice      */
      {
        WinEnableMenuItem(WinWindowFromID(WinQueryWindow(hwnd,
                          QW_PARENT), FID_MENU), IDM_MAIN, TRUE);
        WinEnableMenuItem(hwndPopup, IDM_MAIN, TRUE);
      }
      else
      {
        WinEnableMenuItem(WinWindowFromID(WinQueryWindow(hwnd,
                          QW_PARENT), FID_MENU), IDM_MAIN, FALSE);
        WinEnableMenuItem(hwndPopup, IDM_MAIN, FALSE);
      }
    }                                  /* end if sub-activity != parent       */

    item = start;                      /* listbox and return TRUE             */
    while( item )
    {
      if(item->display > -1)
      {
        if(strcmp(activity, item->code)==0 &&
           strcmp(parent, item->parent)==0)
        {
          WinSendMsg( WinWindowFromID( hwnd, ID_LISTBOX ),
                      LM_SELECTITEM, MPFROMSHORT(item->display),
                      MPFROMSHORT(TRUE) );
          return( TRUE );
        }
      }
      item = (PACTINFO)item->next;
    }
  }

  return( FALSE );
}

/******************************************************************************/
/*                                                                            */
/* fnFindActivity: Return the activity pointer based on input activity code   */
/*                 and parent.                                                */
/*                                                                            */
/******************************************************************************/

PACTINFO fnFindActivity(CHAR *activity, CHAR *parent)
{

  PACTINFO item;

  item = start;
  while( item )
  {
    if(strcmp(activity, item->code)==0 && strcmp(parent, item->parent)==0)
    {
      return(item);
      break;
    }
    item = (PACTINFO)item->next;
  }
  return(NULL);
}

/******************************************************************************/
/*                                                                            */
/* fnGetLBoxActivity:                                                         */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

PACTINFO fnGetLBoxActivity(LONG index)
{

  PACTINFO item;

  item = start;
  while( item )
  {
    if(item->display == index)
    {
      return(item);
      break;
    }
    item = (PACTINFO)item->next;
  }
  return(NULL);
}

/******************************************************************************/
/*                                                                            */
/* fnProcessItem: Save to control file and refresh list box.                  */
/*                                                                            */
/******************************************************************************/

VOID fnProcessItem( HAB hab, HWND hwnd, PACTINFO curact, ULONG cxClient,
                    ULONG cyChar, BOOL putFile, ULONG *exFlag,
                    ULONG *colFlag )

{
  RECTL    rectl;
  TID      tidThread;

  fnAddTotal();
  fnSort();

  if( putFile == YES )
    DosCreateThread( &tidThread, (PFNTHREAD)fnPutActivityInfo, 0L, 0L,
                     STACKSIZE );

  rectl.xLeft = 0;
  rectl.yBottom = 0;
  rectl.xRight = cxClient;
  rectl.yTop = cyChar;
  WinInvalidateRect( hwnd, &rectl, FALSE );
  fnListBoxEntry( hwnd, curact, exFlag, colFlag );

}

/******************************************************************************/
/*                                                                            */
/* fnAddTotal: Determine the accumulated total time so far and determine      */
/*             proper show flag (%, @ or #) for each activity item/code.      */
/*                                                                            */
/******************************************************************************/

VOID fnAddTotal( VOID )

{
  PACTINFO item;

  totaltime = (float)0.0;
  extottime = (float)0.0;
  item = start;
  while( item )
  {
// 1.98
//  if( item->hide != ' ' && showhidden == YES && hidetotal == NO );
//  else
//  {
      if( showexclude == YES )
      {
        if( item->exclude == EXCLUDE_CHAR && item->hide == HIDE_CHAR )
          item->showflag = EX_HIDE_CHAR;
        else
        {
          if( item->exclude == EXCLUDE_CHAR )
            item->showflag = EXCLUDE_CHAR;
          else
          {
            if( item->hide == HIDE_CHAR )
              item->showflag = HIDE_CHAR;
            else
              item->showflag = ' ';
          }
        }
      }
      else
      {
        if( item->hide == HIDE_CHAR )
          item->showflag = HIDE_CHAR;
        else
          item->showflag = ' ';
      }

      if(item->children == 0)          /* don't total parent activities       */
      {
        if( item->exclude == ' ' )
          extottime = extottime + item->timer;
        totaltime = totaltime + item->timer; /* total for ALL activity codes  */
      }
//  }
    item = (PACTINFO)item->next;       /* get next item in the linked list    */
  }                                    /* end do while( item )                */

}


/******************************************************************************/
/*                                                                            */
/* fnSort: Sort activity list.                                                */
/*                                                                            */
/******************************************************************************/

VOID fnSort( VOID )
{

  ULONG i, j, x;
  PACTINFO temp1, temp2, activity1, activity2;


  DosRequestMutexSem( hmtxNB, SEM_INDEFINITE_WAIT );

  if( sort != 0 && totalactivities > 0 )               // V1.97 fix
  {
    for( i = 0; i < totalactivities-1; i++ )
    {
      for( j = i+1; j < totalactivities; j++ )
      {
        activity1 = start;
        for( x=0; x < i; x++ )
          activity1 = (PACTINFO)activity1->next;
        activity2 = start;
        for( x=0; x < j; x++ )
          activity2 = (PACTINFO)activity2->next;
        if( ((sort==1) && (strcmp(activity1->code, activity2->code) >= 0 )) ||
          ((sort==2) && (strcmp(activity1->code, activity2->code) <= 0 )) ||
          ((sort==3) && (strcmp(activity1->description,
                                activity2->description) >= 0 )) ||
          ((sort==4) && (strcmp(activity1->description,
                                activity2->description) <= 0 )) ||
          ((sort==5) && (activity1->timer >= activity2->timer)) ||
          ((sort==6) && (activity1->timer <= activity2->timer)) ||
          ((sort==7) && (activity1->timer >= activity2->timer)) ||
          ((sort==8) && (activity1->timer <= activity2->timer)) ||
          ((sort==9) && (activity1->count >= activity2->count)) ||
          ((sort==10) && (activity1->count <= activity2->count)) )
        {
          if( (((sort==1) || (sort==2)) &&
              (strcmp(activity1->code, activity2->code) == 0 )) ||
              (((sort==3) || (sort==4)) &&
              (strcmp(activity1->description, activity2->description) == 0)) ||
              (((sort==5) || (sort==6)) &&
              (activity1->timer == activity2->timer)) ||
              (((sort==7) || (sort==8)) &&
              (activity1->timer == activity2->timer)) ||
              (((sort==9) || (sort==10)) &&
              (activity1->count == activity2->count)) )
          {
            if( ((secsort==1) && (strcmp(activity1->code,
                                         activity2->code) < 0 )) ||
                ((secsort==2) && (strcmp(activity1->code,
                                         activity2->code) > 0 )) ||
                ((secsort==3) && (strcmp(activity1->description,
                                         activity2->description) < 0 )) ||
                ((secsort==4) && (strcmp(activity1->description,
                activity2->description) > 0 )) ||
                ((secsort==5) && (activity1->timer < activity2->timer)) ||
                ((secsort==6) && (activity1->timer > activity2->timer)) ||
                ((secsort==7) && (activity1->timer < activity2->timer)) ||
                ((secsort==8) && (activity1->timer > activity2->timer)) ||
                ((secsort==9) && (activity1->count < activity2->count)) ||
                ((secsort==10) && (activity1->count > activity2->count)) )
              continue;
          }
          temp1 = activity1->prior;    /* swap the link pointers of the two   */
          temp2 = activity1->next;     /* items that are being compared       */
          activity1->prior = activity2->prior;
          activity1->next = activity2->next;
          activity2->prior = temp1;
          activity2->next = temp2;

          if( activity1->next == NULL )
            last = activity1;
          else
            ((PACTINFO)(activity1->next))->prior = activity1;
          if( activity1->prior == NULL )
            start = activity1;
          else
          {
            if( activity1->prior == activity1 )
              activity1->prior = activity2;
            else
              ((PACTINFO)(activity1->prior))->next = activity1;
          }

          if( activity2->prior == NULL )
            start = activity2;
          else
            ((PACTINFO)(activity2->prior))->next = activity2;
          if( activity2->next == NULL )
            last = activity2;
          else
          {
            if( activity2->next == activity2 )
              activity2->next = activity1;
            else
              ((PACTINFO)(activity2->next))->prior = activity2;
          }
        }
      }
    }
  }

  DosReleaseMutexSem( hmtxNB );

}

/******************************************************************************/
/*                                                                            */
/* fnSortReport: Sort report link list by julian date order.                  */
/*                                                                            */
/******************************************************************************/

VOID fnSortReport( ULONG sort )
{

  ULONG i, j, x;
  PREPINFO temp1, temp2, report1, report2;

  if( sort != 0 && totalreports > 0 )                  // V1.97 fix
  {
    for( i = 0; i < totalreports-1; i++ )
    {
      for( j = i+1; j < totalreports; j++ )
      {
        report1 = startrep;
        for( x=0; x < i; x++ )
          report1 = (PREPINFO)report1->next;
        report2 = startrep;
        for( x=0; x < j; x++ )
          report2 = (PREPINFO)report2->next;
        if( ((sort==1) && report1->juldate >= report2->juldate) ||
            ((sort==2) && report1->juldate <= report2->juldate) )
        {
          temp1 = report1->prior;    /* swap the link pointers of the two   */
          temp2 = report1->next;     /* items that are being compared       */
          report1->prior = report2->prior;
          report1->next  = report2->next;
          report2->prior = temp1;
          report2->next  = temp2;

          if( report1->next == NULL )
            lastrep = report1;
          else
            ((PREPINFO)(report1->next))->prior = report1;
          if( report1->prior == NULL )
            startrep = report1;
          else
          {
            if( report1->prior == report1 )
              report1->prior = report2;
            else
              ((PREPINFO)(report1->prior))->next = report1;
          }

          if( report2->prior == NULL )
            startrep = report2;
          else
            ((PREPINFO)(report2->prior))->next = report2;
          if( report2->next == NULL )
            lastrep = report2;
          else
          {
            if( report2->next == report2 )
              report2->next = report1;
            else
              ((PREPINFO)(report2->next))->prior = report2;
          }
        }
      }
    }
  }

}

/******************************************************************************/
/*                                                                            */
/* fnSortSelect: Place a check mark on the selected sort menu item.           */
/*                                                                            */
/******************************************************************************/

VOID fnSortSelect( HWND hwnd, ULONG sort )
{

  BOOL sortnone   = 0;
  BOOL sortcodea  = 0;
  BOOL sortdesca  = 0;
  BOOL sorttimea  = 0;
  BOOL sortperca  = 0;
  BOOL sortcounta = 0;
  BOOL sortcoded  = 0;
  BOOL sortdescd  = 0;
  BOOL sorttimed  = 0;
  BOOL sortpercd  = 0;
  BOOL sortcountd = 0;

  switch( sort )
  {
    case( SORT_NONE ):
      sortnone  = 1;
      break;
    case( SORT_CODE_A ):
      sortcodea = 1;
      break;
    case( SORT_CODE_D ):
      sortcoded = 1;
      break;
    case( SORT_DESC_A ):
      sortdesca = 1;
      break;
    case( SORT_DESC_D ):
      sortdescd = 1;
      break;
    case( SORT_TIME_A ):
      sorttimea = 1;
      break;
    case( SORT_TIME_D ):
      sorttimed = 1;
      break;
    case( SORT_PERC_A ):
      sortperca = 1;
      break;
    case( SORT_PERC_D ):
      sortpercd = 1;
      break;
    case( SORT_COUNT_A ):
      sortcounta = 1;
      break;
    case( SORT_COUNT_D ):
      sortcountd = 1;
      break;
    default:
      break;
  }

  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SORT_NONE,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sortnone ? MIA_CHECKED : 0));
  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SORT_CODE_A,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sortcodea ? MIA_CHECKED : 0));
  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SORT_CODE_D,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sortcoded ? MIA_CHECKED : 0));
  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SORT_DESC_A,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sortdesca ? MIA_CHECKED : 0));
  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SORT_DESC_D,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sortdescd ? MIA_CHECKED : 0));
  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SORT_TIME_A,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sorttimea ? MIA_CHECKED : 0));
  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SORT_TIME_D,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sorttimed ? MIA_CHECKED : 0));
  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SORT_PERC_A,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sortperca ? MIA_CHECKED : 0));
  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SORT_PERC_D,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sortpercd ? MIA_CHECKED : 0));
  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SORT_COUNT_A,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sortcounta ? MIA_CHECKED : 0));
  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SORT_COUNT_D,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sortcountd ? MIA_CHECKED : 0));

}

/******************************************************************************/
/*                                                                            */
/* fnSecSortSelect: Place a check mark on the selected sort menu item.        */
/*                                                                            */
/******************************************************************************/

VOID fnSecSortSelect( HWND hwnd, ULONG secsort )
{

  BOOL sortnone   = 0;
  BOOL sortcodea  = 0;
  BOOL sortdesca  = 0;
  BOOL sorttimea  = 0;
  BOOL sortperca  = 0;
  BOOL sortcounta = 0;
  BOOL sortcoded  = 0;
  BOOL sortdescd  = 0;
  BOOL sorttimed  = 0;
  BOOL sortpercd  = 0;
  BOOL sortcountd = 0;

  switch( secsort )
  {
    case( SORT_NONE ):
      sortnone = 1;
      break;
    case( SORT_CODE_A ):
      sortcodea = 1;
      break;
    case( SORT_CODE_D ):
      sortcoded = 1;
      break;
    case( SORT_DESC_A ):
      sortdesca = 1;
      break;
    case( SORT_DESC_D ):
      sortdescd = 1;
      break;
    case( SORT_TIME_A ):
      sorttimea = 1;
      break;
    case( SORT_TIME_D ):
      sorttimed = 1;
      break;
    case( SORT_PERC_A ):
      sortperca = 1;
      break;
    case( SORT_PERC_D ):
      sortpercd = 1;
      break;
    case( SORT_COUNT_A ):
      sortcounta = 1;
      break;
    case( SORT_COUNT_D ):
      sortcountd = 1;
      break;
    default:
      break;
  }

  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SECSORT_NONE,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sortnone ? MIA_CHECKED : 0));
  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SECSORT_CODE_A,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sortcodea ? MIA_CHECKED : 0));
  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SECSORT_CODE_D,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sortcoded ? MIA_CHECKED : 0));
  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SECSORT_DESC_A,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sortdesca ? MIA_CHECKED : 0));
  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SECSORT_DESC_D,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sortdescd ? MIA_CHECKED : 0));
  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SECSORT_TIME_A,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sorttimea ? MIA_CHECKED : 0));
  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SECSORT_TIME_D,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sorttimed ? MIA_CHECKED : 0));
  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SECSORT_PERC_A,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sortperca ? MIA_CHECKED : 0));
  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SECSORT_PERC_D,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sortpercd ? MIA_CHECKED : 0));
  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SECSORT_COUNT_A,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sortcounta ? MIA_CHECKED : 0));
  WinSendDlgItemMsg (WinQueryWindow(hwnd,QW_PARENT),
                     (ULONG) FID_MENU, (ULONG) MM_SETITEMATTR,
                     MPFROM2SHORT(IDM_SECSORT_COUNT_D,TRUE),
                     MPFROM2SHORT(MIA_CHECKED, sortcountd ? MIA_CHECKED : 0));

}


/******************************************************************************/
/*                                                                            */
/* fnToggleMenuItems: Toggle menu items off/on depending if there are any     */
/*                    activity code defined.                                  */
/*                                                                            */
/******************************************************************************/

VOID fnToggleMenuItems(HWND hwnd, BOOL swtch)
{
   WinEnableMenuItem(WinWindowFromID(WinQueryWindow(hwnd, QW_PARENT),
                     FID_MENU), IDM_SAVE, swtch );
   WinEnableMenuItem(WinWindowFromID(WinQueryWindow(hwnd, QW_PARENT),
                     FID_MENU), IDM_REPEDIT, swtch );
   WinEnableMenuItem(WinWindowFromID(WinQueryWindow(hwnd, QW_PARENT),
                     FID_MENU), IDM_REPORT, swtch );
   WinEnableMenuItem(WinWindowFromID(WinQueryWindow(hwnd, QW_PARENT),
                     FID_MENU), IDM_REFRESH, swtch );
   WinEnableMenuItem(WinWindowFromID(WinQueryWindow(hwnd, QW_PARENT),
                     FID_MENU), IDM_RESET, swtch );
   WinEnableMenuItem(WinWindowFromID(WinQueryWindow(hwnd, QW_PARENT),
                     FID_MENU), IDM_SORT, swtch );
   WinEnableMenuItem(WinWindowFromID(WinQueryWindow(hwnd, QW_PARENT),
                     FID_MENU), IDM_FONT, swtch );

}

/******************************************************************************/
/*                                                                            */
/* fnGetActivityDesc: Get the activity description. Input is activity code    */
/*                    output (third parameter)  is its description.           */
/*                                                                            */
/******************************************************************************/

BOOL fnGetActivityDesc( CHAR *code, CHAR *parent, CHAR *outdesc )

{

  PACTINFO item;

  outdesc[0] = '\0';
  item = start;
  while( item )
  {
    if(strcmp(code, item->code)==0 && strcmp(parent, item->parent)==0)
    {
      strcpy( outdesc, item->description );
      return TRUE;
    }
    item = (PACTINFO)item->next;
  }

  return FALSE;

}

/******************************************************************************/
/*                                                                            */
/* fnChangeParentInfo: Change parent activity information based on its        */
/*                     children data. Input is parent activity code.          */
/*                                                                            */
/******************************************************************************/

VOID fnChangeParentInfo( CHAR *code )
{

  PACTINFO item;
  PACTINFO parent = NULL;

  if(strcmp(code, szBlank) != 0)
  {
    item = start;
    while(item)
    {
      if(strcmp(item->code, code)==0 && strcmp(item->parent, szBlank)==0)
      {
        item->timer = (float)0.0;
        item->count = 0;
        item->children = 0;
        parent = item;
        break;
      }
      item = (PACTINFO)item->next;
    }

    item = start;
    while(item)
    {
      if(strcmp(item->parent, code) == 0)
      {
        parent->timer = parent->timer + item->timer;
        parent->count = parent->count + item->count;
        parent->children = parent->children + 1;
      }
      item = (PACTINFO)item->next;
    }

    // Correct the expand flag
    if(parent->children > 0)
    {
      if(parent->expand == ' ')
        parent->expand = '+';
    }
    else
      parent->expand = ' ';

  }

}
/******************************************************************************/
/*                                                                            */
/* fnStartCommand: Start the user exit program using DosStartSession.         */
/*                                                                            */
/******************************************************************************/

APIRET fnStartCommand( CHAR *szProgram, CHAR *szParms )
{

  UCHAR     szObjBuf[100];
  APIRET    rc;
  PID       pid;
  STARTDATA startData;
  ULONG     sid;

  startData.Length        = sizeof(STARTDATA);
  startData.Related       = SSF_RELATED_CHILD;
  startData.FgBg          = SSF_FGBG_FORE;
  startData.TraceOpt      = SSF_TRACEOPT_NONE;
  startData.PgmTitle      = NULL;
  startData.PgmName       = szProgram;
  startData.PgmInputs     = szParms;
  startData.TermQ         = 0;
  startData.Environment   = 0;
  startData.InheritOpt    = SSF_INHERTOPT_SHELL;
  startData.SessionType   = SSF_TYPE_DEFAULT;
  startData.IconFile      = 0;
  startData.PgmHandle     = NULLHANDLE;
  startData.PgmControl    = 0;
  startData.Reserved      = 0;
  startData.ObjectBuffer  = szObjBuf;
  startData.ObjectBuffLen = 100;
  rc = DosStartSession( &startData, &sid, &pid );

  return( rc );

}

/******************************************************************************/
/*                                                                            */
/* fnQuickKey: Quick key pressed, determine which activity code it belongs    */
/*             to and send a message to the client window procedure to start  */
/*             tracking the activity code.                                    */
/*                                                                            */
/******************************************************************************/

VOID fnQuickKey( HWND hwnd, HWND hwndPopup, ULONG qkey, PACTINFO curact )
{

  PACTINFO item;
  PACTINFO actinfo;

  item = start;
  while( item )
  {
    if(qkey == (item->hotkey-48))
    {
      if(item->hide == HIDE_CHAR && showhidden == YES )
        WinPostMsg( hwnd, UM_ACTIVITY, MPFROMLONG(item), 0L);
      else
      {
//      if(fnSelectActivity(hwnd, hwndPopup, item->code, item->parent,
//                          curact) == TRUE )
//        WinPostMsg( hwnd, UM_ACTIVITY, 0L, 0L);
        actinfo = fnFindActivity(item->code, item->parent);
        if(actinfo)
          WinSendMsg( hwnd, UM_ACTIVITY, MPFROMLONG(actinfo), 0L );
      }
      break;
    }
    item = (PACTINFO)item->next;
  }
}

/******************************************************************************/
/*                                                                            */
/*                     S T R I N G   F U N C T I O N S                        */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/* fnSubstr: Return a portion of a string.                                    */
/*                                                                            */
/******************************************************************************/

VOID fnSubstr( CHAR *source, CHAR *dest, ULONG base, ULONG ofs )
{

  char *sptr=source, *dptr=dest;   /* get a couple of pointer to data         */

  if ( base > 0 )                  /* Return null if offset is 0 or negative. */
    {
                                   /* Move source ptr to base.                */
    for ( ;(base > 1) && (*sptr != '\0'); base-- )
      sptr++;
                                   /* Copy source characters to dest.         */
    for ( ;(ofs > 0) && (*sptr != '\0'); ofs-- )
      *dptr++ = *sptr++;
                                   /* Now pad string out with blanks if       */
                                   /* offset is more than strlen              */
    for ( ;(ofs > 0); ofs-- )
      *dptr++ = ' ';
    }

  *dptr = '\0';                    /* End the dest with a null.               */

}

/******************************************************************************/
/*                                                                            */
/* fnStrip: Remove leading and/or trailing blanks from a string.              */
/*                                                                            */
/******************************************************************************/

VOID fnStrip( char *source, char *dest, char what, char pad )

{
  char *sptr=source, *dptr=dest;            /* get two new pointers to use    */
                                            /* move source pointer along past */
  if ((what=='L')||(what=='l')||(what=='B')||(what=='b')) /* lead pad chars   */
    for ( ; (*sptr == pad) && (*sptr != '\0'); )
      sptr++;
  for ( ;*sptr != '\0'; )                   /* copy from source to dest until */
    *dptr++ = *sptr++;                      /* the end of the source string   */
                                            /* end the dest with a null       */
  *dptr = '\0';
                                            /* now take care of the back end  */
  if ((what=='T')||(what=='t')||(what=='B')||(what=='b'))
    for ( ;*--dptr == pad; )
      *dptr = '\0';                         /* end string with a null         */

}

/******************************************************************************/
/*                                                                            */
/* fnToUpperString: Convert string to upper case.                             */
/*                                                                            */
/******************************************************************************/

VOID fnToUpperString( char *string )

{
  ULONG i;

  for(i=0;i<strlen(string);i++)
  {
    if(string[i] > 96 && string[i] < 123 )
      string[i] = string[i] - 32;
  }
}

/******************************************************************************/
/*                                                                            */
/* fnPadString: Pad string with blanks up to input length.                    */
/*                                                                            */
/******************************************************************************/

VOID fnPadString( char *string, ULONG length )

{
  ULONG i, strlength;

  strlength = strlen(string);
  if(strlength < length)
  {
    for(i=strlength; i<length;i++)
     string[i] = ' ';
    string[i] = '\0';
  }

}

/******************************************************************************/
/*                                                                            */
/* fnReplaceChar: Replace all occurences of old character with new character. */
/*                                                                            */
/******************************************************************************/

VOID fnReplaceChar( char *string, char old, char new )

{
  ULONG i;

  for(i=0;i<strlen(string);i++)
  {
    if(string[i] == old )
      string[i] = new;
  }
}

/******************************************************************************/
/*                                                                            */
/*                 D A T E  &  T I M E   F U N C T I O N S                    */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/* fnDate: Return formatted date.                                             */
/*                                                                            */
/******************************************************************************/

VOID fnDate( CHAR *outDate )

{

  time_t   curdate;                    /* current time/date                   */
  CHAR     szDate[11];

  curdate = time( NULL );
/* 1.98 */
#if 0
  switch( dateformat )
  {
    case( DATE_FORMAT_1 ):
      strftime( szDate, sizeof(szDate), "%m/%d/%Y", localtime(&curdate) );
      break;
    case( DATE_FORMAT_2 ):
      strftime( szDate, sizeof(szDate), "%d-%m-%Y", localtime(&curdate) );
      break;
    case( DATE_FORMAT_3 ):
      strftime( szDate, sizeof(szDate), "%Y-%m-%d", localtime(&curdate) );
      break;
    default:
      strftime( szDate, sizeof(szDate), "%m/%d/%Y", localtime(&curdate) );
      break;
  }
#endif
  switch( iDate )
  {
    case( MDY ):
      strftime( szDate, sizeof(szDate), "%m*%d*%Y", localtime(&curdate) );
      break;
    case( DMY ):
      strftime( szDate, sizeof(szDate), "%d*%m*%Y", localtime(&curdate) );
      break;
    case( YMD ):
      strftime( szDate, sizeof(szDate), "%Y*%m*%d", localtime(&curdate) );
      break;
    default:
      strftime( szDate, sizeof(szDate), "%m*%d*%Y", localtime(&curdate) );
      break;
  }
  fnReplaceChar( szDate, '*', sDate );
  strcpy(outDate, szDate);

}

/******************************************************************************/
/*                                                                            */
/* fnDateInfo: Get information for first line of TIMETRAC.LST control file.   */
/*                                                                            */
/******************************************************************************/

VOID fnDateInfo( CHAR *inline )

{

  CHAR     juldate[10];
  CHAR     showunits[3];
  CHAR     szDate[11];
  time_t   curdate;

  fnDate( szDate );      /* 1.98 */
  strcat( inline, szDate );
  curdate = time( NULL );
  strftime( juldate, sizeof(juldate), " %Y%j ", localtime( &curdate) );
  strcat( inline, juldate );
  sprintf( juldate, "%7.2f", totaltime );
  strcat( inline, juldate );
  showunits[0] = ' ';
  showunits[2] = '\0';
  switch( units )
  {
    case( UNITS_MINUTES ):
      showunits[1] = MINUTE_CHAR;
      break;
    case( UNITS_HOURS ):
      showunits[1] = HOUR_CHAR;
      break;
/* 1.98 */
#if 0
    case( UNITS_TIME_C ):
      showunits[1] = COLON_CHAR;
      break;
    case( UNITS_TIME_D ):
      showunits[1] = DOT_CHAR;
      break;
#endif
    case( UNITS_HMS ):
      showunits[1] = HMS_CHAR;
      break;
    case( UNITS_HM ):
      showunits[1] = HM_CHAR;
      break;
    default:
      break;
  }
  strcat( inline, showunits );

}

/******************************************************************************/
/*                                                                            */
/* fnGetSecUnits: Return the secunits based on input unit char.               */
/*                                                                            */
/******************************************************************************/

ULONG fnGetSecunits( CHAR units )
{
  if(units == HOUR_CHAR)
    return(UNITS_HOURS);

  return(UNITS_MINUTES);

}

/******************************************************************************/
/*                                                                            */
/* fnGetUnits: Returns the units (LONG) based on input unit char.             */
/*                                                                            */
/******************************************************************************/

ULONG fnGetUnits(CHAR units)
{

  ULONG xunits;
  switch(units)
  {
    case(HOUR_CHAR):
      xunits = UNITS_HOURS;
      break;
    case(MINUTE_CHAR):
      xunits = UNITS_MINUTES;
      break;
/* 1.98 */
#if 0
    case(COLON_CHAR):
      xunits = UNITS_TIME_C;
      break;
    case(DOT_CHAR):
      xunits = UNITS_TIME_D;
      break;
#endif
    case(HMS_CHAR):
      xunits = UNITS_HMS;
      break;
    case(HM_CHAR):
      xunits = UNITS_HM;
      break;
    default:
      xunits = UNITS_HOURS;
      break;
  }
  return(xunits);

}

/******************************************************************************/
/*                                                                            */
/* fnCalculateTime: Calculate the elasped time for current activity code.     */
/*                                                                            */
/******************************************************************************/

VOID fnCalculateTime( HAB hab, HWND hwnd, PACTINFO activity, time_t starttime,
                      ULONG xunits )
{

  time_t   endtime;
  float    timediff;
  PACTINFO item;

  DosRequestMutexSem( hmtxNB, SEM_INDEFINITE_WAIT );

  time( &endtime );
  timediff = (float)(difftime( endtime, starttime )) / xunits;
  activity->timer = activity->timer + (float)timediff;
  // Check if over maximum time (1000)
  if(activity->timer > MAX_TIME)
  {
    activity->timer = 999.99;
    WinLoadString (hab, 0L, IDS_ERRTITLE, 50, szTitle);
    WinLoadString (hab, 0L, IDS_MAXTIMEWARN, 80, szText1);
    sprintf(szText, "%s %s", activity->code, szText1);
    WinMessageBox (HWND_DESKTOP, hwnd, szText, szTitle, 1,
                   MB_ERROR | MB_MOVEABLE | MB_OK );
  }

  // Add the time to the parent
  if(strcmp(activity->parent, szBlank) != 0)
  {
    item = start;
    while(item)
    {
      if((strcmp(item->code, activity->parent) == 0) &&
         (item->children > 0))         /* Make sure we found a parent         */
      {
        item->timer = item->timer + (float)timediff;
        if(item->timer > MAX_TIME)
        {
          item->timer = 999.99;
          WinLoadString (hab, 0L, IDS_ERRTITLE, 50, szTitle);
          WinLoadString (hab, 0L, IDS_MAXTIMEWARN, 80, szText1);
          sprintf(szText, "%s %s", item->code, szText1);
          WinMessageBox (HWND_DESKTOP, hwnd, szText, szTitle, 1,
                         MB_ERROR | MB_MOVEABLE | MB_OK );
        }
        break;
      }
      item = (PACTINFO)item->next;
    }
  }

  DosReleaseMutexSem( hmtxNB );

}

/******************************************************************************/
/*                                                                            */
/* fnConvertTime: Convert decimal time to formatted time (hh:mm:ss or         */
/*                hh.mm.ss). Parameters are: time, 60 or 3600, format type,   */
/*                and output string.                                          */
/*                                                                            */
/******************************************************************************/

VOID fnConvertTime( float timer, ULONG units, ULONG type, CHAR *szOuttime )

{
  ULONG sectime;
  ULONG seconds;
  ULONG minutes;
  ULONG hours;

  sectime = timer * units;
  seconds = sectime % 60;
  sectime = sectime / 60;
  minutes = sectime % 60;
  hours   = sectime / 60;

/* 1.98 */
#if 0
  if( type == UNITS_TIME_C )
    sprintf( szOuttime, "%02d:%02d:%02d\0", hours, minutes, seconds );
  else
    sprintf( szOuttime, "%02d.%02d.%02d\0", hours, minutes, seconds );
#endif
  if( type == UNITS_HMS )
    sprintf( szOuttime, "%02d*%02d*%02d\0", hours, minutes, seconds );
  else
    sprintf( szOuttime, "   %02d*%02d\0", hours, minutes );
  fnReplaceChar( szOuttime, '*', sTime );

  return;

}

/******************************************************************************/
/*                                                                            */
/* fnChangeTime: Convert formatted time (hh:mm:ss) into decimal time.         */
/*               Parameters are: Formatted time as a character string and     */
/*               60 or 3600. Returns the time in decimal (float type).        */
/*                                                                            */
/******************************************************************************/

float fnChangeTime( CHAR *szTime, ULONG units )

{
  ULONG sectime;
  ULONG seconds;
  ULONG minutes;
  ULONG hours;
  CHAR  temp[3];
  float rettime;

  fnSubstr( szTime, temp, 1, 2 );
  hours   = atol( temp );
  fnSubstr( szTime, temp, 4, 2 );
  minutes = atol( temp );
  fnSubstr( szTime, temp, 7, 2 );
  seconds = atol( temp );

  sectime = 3600 * hours + 60 * minutes + seconds;
  rettime = (float)sectime / (float)units;

  return( rettime );

}

/******************************************************************************/
/*                                                                            */
/* fnJulDate: Return julian date as an unsigned long.                         */
/*                                                                            */
/******************************************************************************/

ULONG fnJulDate( VOID )

{

  time_t   curdate;                    /* current time/date                   */
  CHAR     juldate[8];

  curdate = time( NULL );
  strftime( juldate, sizeof(juldate), "%Y%j", localtime( &curdate) );

  return( atol( juldate ));

}

/******************************************************************************/
/*                                                                            */
/* fnCurDate: Get the current julian and calendar dates in string formats.    */
/*                                                                            */
/******************************************************************************/

VOID fnCurDate( CHAR *outszJuldate, CHAR *outszDate )

{

  CHAR     juldate[8];
  CHAR     szDate[11];
  time_t   curdate;

  curdate = time( NULL );
  strftime( juldate, sizeof(juldate), "%Y%j", localtime( &curdate) );
  fnDate( szDate );    /* 1.98 */

  strcpy( outszJuldate, juldate );
  strcpy( outszDate, szDate );

  return;

}

/******************************************************************************/
/*                                                                            */
/* fnMakeDate: Based on an input date (month, day and year), return the       */
/*             formatted date and julian date (string and integer value).     */
/*                                                                            */
/******************************************************************************/

ULONG fnMakeDate( ULONG month, ULONG day, ULONG year, CHAR *outszJuldate,
                  CHAR *outszDate )

{

  struct tm tdate;
  time_t    ttime;
  CHAR      juldate[8];
  CHAR      szDate[11];
/* 1.98 */
#if 0
  switch( dateformat )
  {
    case( DATE_FORMAT_1 ):
      sprintf( szDate, "%02d/%02d/%04d", month, day, year );
      break;
    case( DATE_FORMAT_2 ):
      sprintf( szDate, "%02d-%02d-%04d", day, month, year );
      break;
    case( DATE_FORMAT_3 ):
      sprintf( szDate, "%04d-%02d-%02d", year, month, day );
      break;
    default:
      strcpy( szDate, "          " );
      break;
  }
#endif
  switch( iDate )
  {
    case( MDY ):
      sprintf( szDate, "%02d%c%02d%c%04d", month, sDate, day, sDate, year );
      break;
    case( DMY ):
      sprintf( szDate, "%02d%c%02d%c%04d", day, sDate, month, sDate, year );
      break;
    case( YMD ):
      sprintf( szDate, "%04d%c%02d%c%02d", year, sDate, month, sDate, day );
      break;
    default:
      strcpy( szDate, "          " );
      break;
  }

  tdate.tm_sec  = 0;
  tdate.tm_min  = 0;
  tdate.tm_hour = 0;
  tdate.tm_mday = day;
  tdate.tm_mon  = month-1;
  tdate.tm_year = year-1900;
  ttime = mktime( &tdate );
  strftime( juldate, sizeof(juldate), "%Y%j", localtime(&ttime));

  strcpy( outszJuldate, juldate );
  strcpy( outszDate, szDate );

  return( atol( juldate ));

}


/******************************************************************************/
/*                                                                            */
/* fnCalJulDate: Calculate difference between julian dates. Return TRUE if    */
/*               less than difference, FALSE if more.                         */
/*                                                                            */
/******************************************************************************/

BOOL fnCalJulDate( ULONG odate, ULONG ndate, ULONG diff )

{
  if(ndate - odate > 365)
    odate = odate + 635;
  if(odate + diff > ndate)
    return(TRUE);

  return(FALSE);

}

/******************************************************************************/
/*                                                                            */
/*                 L I N K E D   L I S T   F U N C T I O N S                  */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/* fnPutLinkList: Put activity information into a double linked list.         */
/*                                                                            */
/******************************************************************************/

VOID fnPutLinkList( PACTINFO item )
{

  if( last == NULL )
  {
    last = item;
    start = item;
    item->prior = NULL;
  }
  else
  {
    last->next = (PACTINFO)item;
    item->prior = (PACTINFO)last;
  }
  item->next = NULL;
  last = item;

}

/******************************************************************************/
/*                                                                            */
/* fnDeleteLinkList: Delete activity from linked list.                        */
/*                                                                            */
/******************************************************************************/

VOID fnDeleteLinkList( PACTINFO delitem )
{

  if(start == delitem)
  {
    start = (PACTINFO)delitem->next;
    if(start)
      start->prior = NULL;
    else
      last = NULL;
  }
  else
  {
    ((PACTINFO)(delitem->prior))->next = (PACTINFO)delitem->next;
    if(delitem != last)
      ((PACTINFO)(delitem->next))->prior = (PACTINFO)delitem->prior;
    else
      last = (PACTINFO)delitem->prior;
  }
  free(delitem);
}

/******************************************************************************/
/*                                                                            */
/* fnPutReportLinkList: Put report data into a double linked list.            */
/*                                                                            */
/******************************************************************************/

VOID fnPutReportLinkList( PREPINFO item )
{

  if( startrep == NULL )
  {
    lastrep  = item;
    startrep = item;
    item->prior = NULL;
  }
  else
  {
    lastrep->next = (PREPINFO)item;
    item->prior   = (PREPINFO)lastrep;
  }
  item->next = NULL;
  lastrep    = item;

}

/******************************************************************************/
/*                                                                            */
/* fnDeleteReportLinkList: Delete report from linked list.                    */
/*                                                                            */
/******************************************************************************/

VOID fnDeleteReportLinkList( PREPINFO delitem )
{

  if(startrep == delitem)
  {
    startrep = (PREPINFO)delitem->next;
    if(startrep)
      startrep->prior = NULL;
    else
      lastrep = NULL;
  }
  else
  {
    ((PREPINFO)(delitem->prior))->next = (PREPINFO)delitem->next;
    if(delitem != lastrep)
      ((PREPINFO)(delitem->next))->prior = (PREPINFO)delitem->prior;
    else
      lastrep = (PREPINFO)delitem->prior;
  }
  free(delitem);
}

/******************************************************************************/
/*                                                                            */
/* fnFreeList: Free memory for double linked list.                            */
/*                                                                            */
/******************************************************************************/

VOID fnFreeList( VOID )
{

  PACTINFO item;
  PACTINFO temp;

  item = start;
  while( item )
  {
    temp = (PACTINFO)item->next;
    free( item );
    item = temp;
  }

}


/******************************************************************************/
/*                                                                            */
/* fnFreeReportList: Free memory for report double linked list.               */
/*                                                                            */
/******************************************************************************/

VOID fnFreeReportList( VOID )
{

  PREPINFO item, temp;

  item = startrep;
  while( item )
  {
    temp = (PREPINFO)item->next;
    free( item );
    item = temp;
  }

}
