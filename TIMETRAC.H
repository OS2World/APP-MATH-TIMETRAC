/* Application defines                                                        */

#define STACKSIZE           65536

#define szClientClass       "WC_CLIENT"
#define szNotebookClass     "NB_CLIENT"

#define idFrameWindow       100
#define idPopup             101

#define ROUND_OFF_0         0.000005
#define ROUND_OFF_1         0.005

#define REFRESH_MINUTE      60000
#define ALARM_MINUTE        60000
#define ALARMMSG_MINUTE     60000
#define ABOUT_MINUTE        1000

/* Defines controls (ID_)                                                     */

#define ID_LISTBOX          200
#define ID_REFRESHTIMER     201
#define ID_ALARMTIMER       202
#define ID_ALARMMSGTIMER    205
#define ID_NBWINDOW         203
#define ID_NBSETTINGS       204
#define ID_ABOUTTIMER       206

/* Defines bitmaps                                                            */

#define ID_TTBMP1           301
#define ID_TTBMP2           302
#define ID_TTBMP3           303
#define ID_TTBMP4           304
#define ID_TTBMP5           305
#define ID_TTBMP6           306
#define ID_TTBMP7           307
#define ID_TTBMP8           308

/* Defines menu option identifiers (IDM_)                                     */

#define IDM_FILE            3000
#define IDM_REPORT          3001
#define IDM_OPTIONS         3003
#define IDM_SETTINGS        3004
#define IDM_RESET           3005
#define IDM_REFRESH         3006
#define IDM_START           3007
#define IDM_STOP            3008
#define IDM_DELETE          3009
#define IDM_ADD             3010
#define IDM_EDIT            3011
#define IDM_EXCLUDE         3012
#define IDM_HIDE            3013
#define IDM_SORT            3014
#define IDM_SORT_CODE_A     3015
#define IDM_SORT_CODE_D     3016
#define IDM_SORT_DESC_A     3017
#define IDM_SORT_DESC_D     3018
#define IDM_SORT_TIME_A     3019
#define IDM_SORT_TIME_D     3020
#define IDM_SORT_PERC_A     3030
#define IDM_SORT_PERC_D     3031
#define IDM_SORT_COUNT_A    3032
#define IDM_SORT_COUNT_D    3033
#define IDM_SORT_NONE       3021
#define IDM_SORT_SEQUENCE   3022
#define IDM_ALARM           3023
#define IDM_USEREXIT        3024
#define IDM_COMMAND         3025
#define IDM_SAVE            3026
#define IDM_TRANSFER        3027
#define IDM_REPEDIT         3028
#define IDM_EXIT            3029
#define IDM_CTRL_1          3034
#define IDM_CTRL_2          3035
#define IDM_CTRL_3          3036
#define IDM_CTRL_4          3037
#define IDM_CTRL_5          3038
#define IDM_CTRL_6          3039
#define IDM_CTRL_7          3040
#define IDM_CTRL_8          3041
#define IDM_CTRL_9          3042
#define IDM_FONT            3043
#define IDM_SEC_SORT        3044
#define IDM_SECSORT_CODE_A  3045
#define IDM_SECSORT_CODE_D  3046
#define IDM_SECSORT_DESC_A  3047
#define IDM_SECSORT_DESC_D  3048
#define IDM_SECSORT_TIME_A  3049
#define IDM_SECSORT_TIME_D  3050
#define IDM_SECSORT_PERC_A  3051
#define IDM_SECSORT_PERC_D  3052
#define IDM_SECSORT_COUNT_A 3053
#define IDM_SECSORT_COUNT_D 3054
#define IDM_SECSORT_NONE    3055
#define IDM_MAIN            3056
#define IDM_COLLAPSEALL     3057
#define IDM_EXPANDALL       3058
#define IDM_SAVESETTINGS    3059   /* 1.97 */
#define IDM_RESETIT         3060   /* 1.98 */
#define IDM_HELP            4000
#define IDM_USINGHELP       4001
#define IDM_HELPPRODINFO    4002
#define IDM_TEST            4003
#define IDM_DEBUG           4004

/* Defines string identifiers (IDS_)                                          */

#define IDS_TITLEBAR        1350
#define IDS_HELPTITLE       1351
#define IDS_HELPNAME        1352
#define IDS_EXITPROMPT      1353
#define IDS_TITLEEXIT       1354
#define IDS_LISTHDR         1355
#define IDS_SELECT          1356
#define IDS_ININAME         1357
#define IDS_LISTTITLE       1358
#define IDS_STATUSOFF       1359
#define IDS_STATUSON        1360
#define IDS_DELETE          1361
#define IDS_DELETEMSG       1362
#define IDS_RESET           1363
#define IDS_RESETMSG        1364
#define IDS_CODENULL        1365
#define IDS_DESCNULL        1366
#define IDS_MEMERROR        1367
#define IDS_GETERROR        1368
#define IDS_PUTERROR        1369
#define IDS_ERRTITLE        1370
#define IDS_OUTFILE         1371
#define IDS_BACKFILE        1372
#define IDS_REPORTFILE      1373
#define IDS_BACKREPFILE     1374
#define IDS_RESETWARN       1375
#define IDS_ADD             1376
#define IDS_ADDMSG          1377
#define IDS_WARNADD         1378
#define IDS_PROGRAM         1379
#define IDS_ALARM           1380
#define IDS_ALARMMSG        1381
#define IDS_MINUTES         1382
#define IDS_HOURS           1383
#define IDS_TOTAL           1384
#define IDS_SAVE            1385
#define IDS_SAVEMSG         1386
#define IDS_OPTIONS         1387
#define IDS_CONFIRM         1388
#define IDS_DATE            1389
#define IDS_TIME            1390
#define IDS_REPORT          1391
#define IDS_ALARMSET        1392
#define IDS_USEREXIT        1393
#define IDS_NONE            1394
#define IDS_SETTINGS        1395
#define IDS_CREATE          1396
#define IDS_CREATEWARN      1397
#define IDS_GET             1398
#define IDS_GETWARN         1399
#define IDS_COMMENTFILE     1400
#define IDS_BACKCOMFILE     1401
#define IDS_HOTKEY          1402
#define IDS_HOTKEYWARN      1403
#define IDS_PARENT          1404
#define IDS_PARENTWARN1     1405
#define IDS_PARENTWARN2     1411
#define IDS_ACTCODE         1406
#define IDS_ACTCODEWARN     1407
#define IDS_TRAN            1408
#define IDS_TRANWARN        1409
#define IDS_DELETEWARN      1410
#define IDS_CURRENT         1412
#define IDS_MAXTIMEWARN     1413
#define IDS_SAVESETWARN     1414   /* 1.97 */
#define IDS_SAVEERROR       1415   /* 1.98 */
#define IDS_RESETERROR      1416   /* 1.98 */
#define IDS_PARENTWARN3     1417   /* 1.99 */

/* Defines help identifiers (IDH_)                                            */

#define IDH_TABLE_MAIN          9999

#define IDH_SUBTABLE_MAIN       9100
#define IDH_MAIN                9110
#define IDH_MENU_FILE           9111
#define IDH_FILE_REPORT         9113
#define IDH_MENU_OPTIONS        9114
#define IDH_OPTIONS_SETTINGS    9115
#define IDH_OPTIONS_REFRESH     9116
#define IDH_OPTIONS_RESET       9117
#define IDH_OPTIONS_SORT        9118
#define IDH_TECH_NOTES          9120
#define IDH_FILE_COMMAND        9122
#define IDH_FILE_SAVE           9123
#define IDH_START_OPTION        9121
#define IDH_PROFILE_OPTION      9124
#define IDH_DATA_OPTION         9125
#define IDH_FONT                9126
#define IDH_FONT_DLG            9127
#define IDH_OPTIONS_SECSORT     9128
#define IDH_COLLAPSEALL         9129
#define IDH_EXPANDALL           9130
#define IDH_SAVESETTINGS        9131  /* 1.97 */
#define IDH_OUTPUT_OPTION       9132  /* 1.98 */
#define IDH_REPORT_OPTION       9133  /* 1.98 */
#define IDH_COMMENT_OPTION      9134  /* 1.98 */

#define IDH_POPUP_START         9140
#define IDH_POPUP_STOP          9141
#define IDH_POPUP_ADD           9142
#define IDH_POPUP_EDIT          9143
#define IDH_POPUP_DELETE        9144
#define IDH_POPUP_EXCLUDE       9145
#define IDH_POPUP_HIDE          9146
#define IDH_POPUP_TRANSFER      9147
#define IDH_POPUP_MAIN          9148
#define IDH_POPUP_RESETIT       9149  /* 1.98 */

#define IDH_MENU_HELP           9180
#define IDH_MENU_HELPINDEX      9182
#define IDH_MENU_HELPGENERAL    9183
#define IDH_MENU_HELPUSING      9184
#define IDH_MENU_HELPKEYS       9185
#define IDH_MENU_HELPPRODINFO   9186
#define IDH_HELPKEYS            9187

#define IDH_SUBTABLE_EDIT       9200
#define IDH_EDIT                9201
#define IDH_EDIT_CODE           9202
#define IDH_EDIT_DESCRIPTION    9203
#define IDH_EDIT_TIME           9204
#define IDH_EDIT_EXCLUDE        9205
#define IDH_EDIT_HIDDEN         9206
#define IDH_EDIT_COUNT          9207
#define IDH_EDIT_LOCK           9208
#define IDH_EDIT_COMMENTS       9209
#define IDH_EDIT_PROGRAM        9210
#define IDH_EDIT_PARAMETERS     9211
#define IDH_EDIT_HOTKEY         9212
#define IDH_EDIT_FOCUS          9213
#define IDH_EDIT_PARENT         9214
#define IDH_EDIT_ACTALARM       9215

#define IDH_SUBTABLE_ADD        9300
#define IDH_ADD                 9301
#define IDH_ADD_CODE            9302
#define IDH_ADD_DESCRIPTION     9303
#define IDH_ADD_EXCLUDE         9304
#define IDH_ADD_SAVE            9305
#define IDH_ADD_HIDDEN          9306
#define IDH_ADD_LOCK            9307
#define IDH_ADD_COMMENTS        9308
#define IDH_ADD_PROGRAM         9309
#define IDH_ADD_PARAMETERS      9310
#define IDH_ADD_HOTKEY          9311
#define IDH_ADD_FOCUS           9312
#define IDH_ADD_PARENT          9313
#define IDH_ADD_ACTALARM        9314

#define IDH_SUBTABLE_SETTINGS   9400
#define IDH_SETTINGS            9410
#define IDH_SETTINGS_UNITS      9411
#define IDH_SETTINGS_REFRESH    9412
#define IDH_SETTINGS_REFSAVE    9476
#define IDH_SETTINGS_EXIT       9413
#define IDH_SETTINGS_DEFAULT    9414
#define IDH_SETTINGS_EXCLUDE    9415
#define IDH_SETTINGS_INITRESET  9416
#define IDH_SETTINGS_DELETE     9418
#define IDH_SETTINGS_RESET      9419
#define IDH_SETTINGS_RESETNEW   9428
//#define IDH_SETTINGS_DATEFORMAT 9420  /* 1.98 */
#define IDH_SETTINGS_HIDE       9421
#define IDH_SETTINGS_MINIMIZE   9425
#define IDH_SETTINGS_STARTITEM  9426
#define IDH_SETTINGS_SMALLWIN   9427
#define IDH_SETTINGS_BLANKCOM   9430
//#define IDH_SETTINGS_HIDETOTAL  9431 /* 1.98 */
#define IDH_SETTINGS_GOMAIN     9460
#define IDH_SETTINGS_NOFOCUS    9462
#define IDH_SETTINGS_SUBACTWIN  9464
#define IDH_REPORT_SAVEDATA     9417
#define IDH_REPORT_DESCRIPTION  9422
#define IDH_REPORT_COMMENTS     9429
#define IDH_REPORT_EXCLUDE      9423
#define IDH_REPORT_HIDDEN       9424
#define IDH_REPORT_DETAILS      9432
#define IDH_REPORT_ZERO         9433
#define IDH_REPORT_NOTES        9434
#define IDH_ALARM_TIME          9452
#define IDH_ALARM_SOUND         9453
#define IDH_ALARM_MESSAGE       9454
#define IDH_ALARM_DEFAULT       9455
#define IDH_ALARM_EDIT          9456
#define IDH_ALARM_ITEM          9457
#define IDH_ALARM_CHANGE        9458
#define IDH_ALARM_CURRENT       9461
#define IDH_ALARM_ALARMEXP      9463
#define IDH_USEREXIT_MENUTEXT   9472
#define IDH_USEREXIT_PROGRAM    9473
#define IDH_USEREXIT_PARAMETERS 9474
#define IDH_USEREXIT_CLEAR      9475

#define IDH_SUBTABLE_REPORTLIST 9500
#define IDH_REPORTLIST          9501
#define IDH_REPORTLIST_ALL      9502
#define IDH_REPORTLIST_NONE     9503
#define IDH_REPORTLIST_TOTAL    9504
#define IDH_REPORTLIST_DELETE   9505

#define IDH_SUBTABLE_REPORT     9550
#define IDH_REPORT              9551

#define IDH_SUBTABLE_NOTEBOOK   9560

#define IDH_SUBTABLE_ALARMMSG   9570
#define IDH_ALARMMSG            9571
#define IDH_SUBTABLE_ALARMCHG   9580
#define IDH_ALARMCHG            9581
#define IDH_ALARMCHG_ALARM      9582

#define IDH_SUBTABLE_SAVEREP    9600
#define IDH_SAVEREP             9601

#define IDH_SUBTABLE_TRANSFER   9650
#define IDH_TRANSFER            9651
#define IDH_TRANSFER_AMOUNT     9652
#define IDH_TRANSFER_LIST       9653
#define IDH_TRANSFER_COUNT      9654
#define IDH_TRANSFER_ADDCOUNT   9655

#define IDH_SUBTABLE_REPORTEDIT 9700
#define IDH_REPORTEDIT          9701
#define IDH_REPEDIT_DATE        9702
#define IDH_REPEDIT_LIST        9703
#define IDH_REPEDIT_TIME        9704
#define IDH_REPEDIT_COUNT       9705
#define IDH_REPEDIT_GETDATA     9706
#define IDH_REPEDIT_COMMENTS    9707
#define IDH_REPEDIT_PARENT      9708

#define TID_LOGOTIMER           TID_USERMAX - 1
#define UM_WARNRESET            WM_USER + 1
#define UM_WARNADD              WM_USER + 2
#define UM_CREATE               WM_USER + 3
#define UM_SELECT               WM_USER + 4
#define UM_SETREFRESH           WM_USER + 5
#define UM_SETALARM             WM_USER + 6
#define UM_SETSHOW              WM_USER + 7
#define UM_SETREP               WM_USER + 8
#define UM_SETEXIT              WM_USER + 9
#define UM_CREATENB             WM_USER + 10
#define UM_ACTIVITY             WM_USER + 11

#define szAppName     "TIMETRAC"
#define szWinPos      "Window Position"
#define szSettings    "Settings"
#define szAlarm       "Alarm"
#define szUser        "User Exit"
#define szReport      "Report"
#define szSetWinPos   "Settings Win Pos"

#define SEPCHARS     " \"\n"
#define NEWLINE      "\"\n"
#define EXCLUDE_CHAR '@'
#define HIDE_CHAR    '#'
#define EX_HIDE_CHAR '%' /* activity code excluded and hidden */
#define DELETE_CHAR  '-'
#define COMMENT_CHAR '*'
#define MINUTE_CHAR  'm'
#define HOUR_CHAR    'h'
#define HMS_CHAR     '0'
#define HM_CHAR      '2'
// 1.98
//#define DOT_CHAR     '.'
//#define COLON_CHAR   ':'
#define LOCK_CHAR    '&'
#define SMALL_WINDOW  1
#define NORMAL_WINDOW 2

#define MAX_TIME      1000

#define OFF  0
#define ON   1
#define NO   0
#define YES  1

#define CODE_WIDTH    8
#define DESC_WIDTH    20
#define COMM_WIDTH    30
#define MENU_WIDTH    40
#define PROG_WIDTH    48
#define PARA_WIDTH    48
#define WFOC_WIDTH    20
// 1.98
//#define UNITS_TIME_C  0
//#define UNITS_TIME_D  1
#define UNITS_HMS     0
#define UNITS_HM      2
#define UNITS_MINUTES 60
#define UNITS_HOURS   3600
/* 1.98 */
//#define DATE_FORMAT_1 1
//#define DATE_FORMAT_2 2
//#define DATE_FORMAT_3 3
#define MDY           0
#define DMY           1
#define YMD           2
#define SORT_NONE     0
#define SORT_CODE_A   1
#define SORT_CODE_D   2
#define SORT_DESC_A   3
#define SORT_DESC_D   4
#define SORT_TIME_A   5
#define SORT_TIME_D   6
#define SORT_PERC_A   7
#define SORT_PERC_D   8
#define SORT_COUNT_A  9
#define SORT_COUNT_D  10
#define TYPE_NORMAL    0
#define TYPE_NO_PARENT 1
#define TYPE_NO_CHILD  2

#define MAXITEMS      200
#define MAXLENGTH     6060         /* 30 x (MAXITEMS + 2) */

#define WARN_RESET       80
#define WARN_HOTKEY      81
#define WARN_PARENT      82
#define WARN_DUP_CODE    83
#define ERROR_OPEN_FILE  96
#define ERROR_CODE_NULL  97
#define ERROR_DESC_NULL  98
#define ERROR_MEMORY     99

/* Data structures                                                            */

typedef struct                         /* this is main linked list (double)   */
{                                      /* contains activity codes             */
  CHAR   code[CODE_WIDTH+1];           /* activity code, 8 chars or less      */
  CHAR   description[DESC_WIDTH+1];    /* activity description                */
  CHAR   comments[COMM_WIDTH+1];       /* comments                            */
  CHAR   program[PROG_WIDTH+1];        /* program                             */
  CHAR   parameters[PARA_WIDTH+1];     /* parameters                          */
  CHAR   winfocus[WFOC_WIDTH+1];       /* window focus (title)                */
  CHAR   listtext[100];                /*                                     */
  CHAR   showflag;                     /* control character shown on list     */
  CHAR   expand;                       /* + if collapsed, - if expanded or ' '*/
  CHAR   exclude;                      /* excluded activity                   */
  CHAR   hide;                         /* hidden activity                     */
  CHAR   lock;                         /* invoke WPS lock when started        */
  CHAR   hotkey;                       /* quick or hot-key (1-9) or blank (0) */
  float  timer;                        /* activity time                       */
  ULONG  count;                        /* counter, number of times started    */
  CHAR   parent[CODE_WIDTH+1];         /* parent activity code, subcategory   */
  ULONG  children;                     /* number of children                  */
  ULONG  alarmtime;                    /* alarm timer                         */
  LONG   display;                      /* display flag                        */
  PVOID  next;                         /* pointers to previous and next       */
  PVOID  prior;                        /* addresses of the double link list   */
} ACTINFO;
typedef ACTINFO * PACTINFO;

typedef struct
{                                      /* contains activity codes             */
  CHAR   code[CODE_WIDTH+1];           /* activity code, 8 chars or less      */
  CHAR   repcom[COMM_WIDTH+1];         /* comments                            */
  CHAR   repparent[CODE_WIDTH+1];      /* parent                              */
  float  reptimer;                     /* activity time                       */
  ULONG  repcount;                     /* counter, number of times started    */
  PVOID  next;                         /* pointers to previous and next       */
  PVOID  prior;                        /* addresses of the double link list   */
} ACTDATA;
typedef ACTDATA * PACTDATA;

typedef struct
{
  CHAR  repdate[11];
  ULONG juldate;
  float total;
  CHAR  units;
  CHAR  repdata[MAXLENGTH];
  CHAR  commentdata[MAXLENGTH];
  BOOL  selected;
  PVOID next;
  PVOID prior;
} REPINFO;
typedef REPINFO * PREPINFO;

typedef struct
{
  CHAR   code[CODE_WIDTH+1];
  CHAR   parent[CODE_WIDTH+1];
  CHAR   description[DESC_WIDTH+1];
  CHAR   comments[COMM_WIDTH+1];
  float  time;
  ULONG  count;
  PVOID  next;
  PVOID  prior;
} REPTOTAL;
typedef REPTOTAL * PREPTOTAL;

typedef struct
{
  BOOL   bool1;
  BOOL   bool2;
  BOOL   bool3;
  BOOL   bool4;
  BOOL   bool5;
  BOOL   bool6;
  ULONG  ulong1;
  ULONG  ulong2;
  ULONG  ulong3;
  ULONG  ulong4;
  ULONG  ulong5;
  ULONG  ulong6;
  CHAR   char40[40];
  CHAR   char80[80];
} PROFILEINFO;
typedef PROFILEINFO * PPROFILEINFO;

typedef struct
{
  CHAR   char40[40];
  CHAR   char48[48];
  CHAR   char80[80];
} USERINFO;
typedef USERINFO * PUSERINFO;

/* Function prototypes                                                        */

MRESULT EXPENTRY wpClientWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#pragma linkage (wpClientWndProc, system)

MRESULT EXPENTRY wpNBWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#pragma linkage (wpNBWndProc, system)

MRESULT EXPENTRY wpEditDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#pragma linkage (wpEditDlgProc, system)

MRESULT EXPENTRY wpTransferDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#pragma linkage (wpTransferDlgProc, system)

MRESULT EXPENTRY wpAddDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#pragma linkage (wpAddDlgProc, system)

MRESULT EXPENTRY wpSetAlarmDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#pragma linkage (wpSetAlarmDlgProc, system)

MRESULT EXPENTRY wpAlarmMsgDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#pragma linkage (wpAlarmMsgDlgProc, system)

MRESULT EXPENTRY wpReportListDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#pragma linkage (wpReportListDlgProc, system)

MRESULT EXPENTRY wpReportDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#pragma linkage (wpReportDlgProc, system)

MRESULT EXPENTRY wpRepEditDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#pragma linkage (wpRepEditDlgProc, system)

MRESULT EXPENTRY wpAboutDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#pragma linkage (wpAboutDlgProc, system)

VOID fnListBoxEntry( HWND hwnd, PACTINFO curact, ULONG *expandFlag,
                     ULONG *collapseFlag );

#pragma linkage (fnListBoxEntry, system)

VOID     fnSubstr( char *source, char *dest, ULONG base, ULONG ofs );
VOID     fnStrip( char *source, char *dest, char what, char pad );
VOID     fnToUpperString( char *string );
VOID     fnPadString( char *str, ULONG length );
VOID     fnReplaceChar( char *string, char old, char new );
VOID     fnDate( CHAR *szDate );
VOID     fnDateInfo( CHAR *inline );
ULONG    fnGetSecunits( CHAR units );
ULONG    fnGetUnits( CHAR units );
VOID     fnConvertTime( float timer, ULONG units, ULONG type, CHAR *szTime );
float    fnChangeTime( CHAR *szTime, ULONG units );
ULONG    fnJulDate( VOID );
VOID     fnCurDate( CHAR *juldate, CHAR *szDate );
ULONG    fnMakeDate( ULONG month, ULONG day, ULONG year,
                     CHAR *szJuldate, CHAR *szDate );
BOOL     fnGetActivityDesc( CHAR *code, CHAR *parent, CHAR *outdesc );

VOID     fnInitialize( USHORT type );
BOOL     fnCreateNotebook ( HAB hab, HWND hwnd );

APIRET   fnAddActivityCode( HAB hab, HWND hwnd );
VOID     fnChangeParentInfo( CHAR *code );
PACTINFO fnFindActivity(CHAR *code, CHAR *parent);

APIRET  fnSaveReportList(VOID);

/* Global variables                                                           */

ULONG fontsize;
CHAR  fontname[FACESIZE];

CHAR szText[81];
CHAR szText1[81];
CHAR szTitle[51];
CHAR dataDir[256];
CHAR Outfile[256];                     /* TIMETRAC.LST control file           */
CHAR BackOutfile[256];                 /* backup file to TIMETRAC.LST         */
CHAR Reportfile[256];                  /* TIMETRAC.TT report file             */
CHAR BackReportfile[256];              /* backup file to TIMETRAC.TT          */
CHAR Commentfile[256];                 /* TIMETRAC.CT comment file            */
CHAR BackCommentfile[256];             /* backup file to TIMETRAC.CT          */

BOOL  showexit;                        /* display exit confirmation?          */
BOOL  showdelete;                      /* display delete confirmation?        */
BOOL  showreset;                       /* display reset confirmation?         */
BOOL  showresetnew;                    /* display reset confirm for new day?  */
BOOL  showexclude;                     /* Use exclusion?                      */
BOOL  showhidden;                      /* Use hidden?                         */
BOOL  initreset;                       /* reset times initially?              */
BOOL  refreshsave;                     /* save to file on refresh             */
BOOL  minimize;                        /* minimize on activity tracking       */
BOOL  blankcom;                        /* blank comments for new day          */
BOOL  smallwin;                        /* small window, no title, menu, etc.  */
BOOL  xsmlwin;
/*BOOL  hidetotal;               1.98     add hidden activity time to total   */
BOOL  gomain;                          /* go to main activity list            */
BOOL  nofocuschg;                      /* focus change                        */
BOOL  subactwin;                       /* sub-activity window                 */
ULONG refreshtime;                     /* automated refresh time (minutes)    */
ULONG units;                           /* time units (min or hrs)             */
ULONG secunits;
/* ULONG dateformat;                      report date format             1.98 */
ULONG sort;                            /* sort type, SORT_XXXX_A/D            */
ULONG secsort;                         /* secondary sort type, SORT_XXXX_A/D  */
CHAR  startitem[2*CODE_WIDTH+2];       /* default activity to track on startup*/

ULONG repsave;                         /* save daily data to report?          */
ULONG repdays;                         /* number of days to save              */
BOOL  reptotal;                        /* report should be totalled           */
BOOL  repexcl;                         /* add excluded codes to report        */
BOOL  rephide;                         /* add hidden codes to report          */
BOOL  repdesc;                         /* add description to report           */
BOOL  repcomm;                         /* add comments to report              */
BOOL  repzero;                         /* show 0 times in report              */
BOOL  repdetails;                      /* show detail (subcatogories)         */
CHAR  repfile[80];                     /* filespec of saved report            */
CHAR  repline1[80];                    /* report text line 1             1.98 */
CHAR  repline2[80];                    /* report text line 2             1.98 */

ULONG alarmtime;                       /* alarm timer (minutes)               */
BOOL  alarmsound;                      /* sound when alarm expires            */
BOOL  alarmmsg;                        /* display message box when alarm exp. */
BOOL  alarmedit;                       /* edit activity when alarm expired    */
BOOL  alarmchg;                        /* change alarm timer at every start   */
ULONG alarmexp;                        /* alarm expire (minutes)              */
CHAR  alarmitem[2*CODE_WIDTH+2];       /* default activity to track on alarm  */

ULONG totalitems;                      /* total number of items in list       */
ULONG totalactivities;                 /* total number of activity codes      */
ULONG totalreports;                    /* total number of reports             */
float totaltime;                       /* total time tracked                  */
float extottime;                       /* total time tracked w/ exclusions    */

CHAR  menutext[MENU_WIDTH];            /* user exit character strings         */
CHAR  program[PROG_WIDTH];
CHAR  parameters[PARA_WIDTH];

CHAR  startact[2*CODE_WIDTH+2];        /* starting activity to be tracked     */
CHAR  subact[CODE_WIDTH+1];            /* sub-category                        */

HINI  hini;                            /* handle to user profile              */
HMTX  hmtx;                            /* handle mutex semaphore              */
HMTX  hmtxNB;
HWND  hwndFrame, hwndClient;           /* various window handles              */
HWND  hwndHelp, hwndList;
BOOL  alarmflag;
BOOL  newDay;
SWP   swpWin;
CHAR  szBlank[CODE_WIDTH+1];           /* blank                               */

PACTINFO start;                        /* linked list start and end addresses */
PACTINFO last;
PREPINFO startrep;
PREPINFO lastrep;

CHAR  sDate;
CHAR  sTime;
SHORT iDate;
SHORT iTime;
