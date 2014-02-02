/******************************************************************************/
/*                       (c) IBM Canada Ltd. 1993                             */
/*                                                                            */
/* Program:     TIMETRAC - PM Activity Time Tracker                           */
/* Component:   Dialog procedures                                             */
/*                                                                            */
/* Author : Enrico Zapanta                                                    */
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
#include <process.h>
#include <time.h>
#include "timetrac.h"                  /* main include file                   */
#include "timedlg.h"                   /* include file for dialog boxes       */

MRESULT EXPENTRY wpSaveReportDlgProc(HWND hwnd, ULONG msg, MPARAM mp1,
                                     MPARAM mp2);
#pragma linkage (wpSaveReportDlgProc, system)

MRESULT EXPENTRY wpOptionsDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#pragma linkage (wpOptionsDlgProc, system)

MRESULT EXPENTRY wpConfirmDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#pragma linkage (wpConfirmDlgProc, system)

MRESULT EXPENTRY wpTimeDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#pragma linkage (wpTimeDlgProc, system)

MRESULT EXPENTRY wpDateDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#pragma linkage (wpDateDlgProc, system)

MRESULT EXPENTRY wpRepSetDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#pragma linkage (wpRepSetDlgProc, system)

MRESULT EXPENTRY wpAlarmDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#pragma linkage (wpAlarmDlgProc, system)

MRESULT EXPENTRY wpUserExitDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
#pragma linkage (wpUserExitDlgProc, system)

VOID fnOptionsDlgInit ( HWND hwnd );
VOID fnConfirmDlgInit ( HWND hwnd );
VOID fnTimeDlgInit    ( HWND hwnd );
VOID fnDateDlgInit    ( HWND hwnd );
VOID fnRepSetDlgInit  ( HWND hwnd );
VOID fnUserExitDlgInit( HWND hwnd );
VOID fnAlarmDlgInit   ( HWND hwnd );

PACTDATA fnInitRepData( BOOL type, HWND hwnd, PACTDATA *startdata,
                        PACTDATA *lastdata, float *total, CHAR *repdata,
                        CHAR *comdata );
VOID fnPutDataList( PACTDATA item, PACTDATA *startdata, PACTDATA *lastdata );
VOID fnFreeDataList( PACTDATA startdata );
VOID fnFreeReptotalList( PREPTOTAL starttot );
VOID fnResetList( HWND hwnd, PACTDATA startdata );

BOOL fnCheckHotkey(LONG hotkey);
BOOL fnCheckActivityCode(CHAR *code, CHAR *parent);
float fnTimeControl(HWND hwnd, float ftime, BOOL type);
VOID fnActivityList(HWND hwnd, CHAR *activity, CHAR *parent, LONG dlgId,
                    BOOL optNone, BOOL addDesc, ULONG type);
VOID fnChangeParent( CHAR *oldcode, CHAR *code );
VOID fnChangeParentReport( CHAR *code, PACTDATA startdata );

VOID fnFormatReport(PREPTOTAL starttot, float total, ULONG units,
                    CHAR* repdate, CHAR* buf);
VOID fnFormatActivity(PREPTOTAL act, float percent, ULONG units, CHAR* buf);

ULONG fnProcessReportList( HWND hwnd, ULONG id );
VOID  fnReportNotes( CHAR *szBuffer );

/******************************************************************************/
/*                                                                            */
/*        D I A L O G      W I N D O W       P R O C E D U R E S              */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/* wpAddDlgProc: Window procedure for Add Activity Code dialog box.           */
/*                                                                            */
/******************************************************************************/

MRESULT EXPENTRY wpAddDlgProc (HWND hwnd, ULONG msg, MPARAM mp1,
                                   MPARAM mp2)

{

 MRESULT mr = (MRESULT) FALSE;
 static  HAB hab;

 switch (msg)
    {
     case WM_INITDLG:                  /* Dialog initialization routine       */
     {
       hab = WinQueryAnchorBlock( hwnd );

       WinSendMsg( WinWindowFromID( hwnd, IDE_CODE ), EM_SETTEXTLIMIT,
                   (MPARAM)CODE_WIDTH, (MPARAM)0 );
       WinSendMsg( WinWindowFromID( hwnd, IDE_DESCRIPTION ), EM_SETTEXTLIMIT,
                   (MPARAM)DESC_WIDTH, (MPARAM)0 );
       WinSendMsg( WinWindowFromID( hwnd, IDE_COMMENTS ), EM_SETTEXTLIMIT,
                   (MPARAM)COMM_WIDTH, (MPARAM)0 );
       WinSendMsg( WinWindowFromID( hwnd, IDE_ACTCMD ), EM_SETTEXTLIMIT,
                   (MPARAM)PROG_WIDTH, (MPARAM)0 );
       WinSendMsg( WinWindowFromID( hwnd, IDE_APARM ), EM_SETTEXTLIMIT,
                   (MPARAM)PARA_WIDTH, (MPARAM)0 );
       WinSendMsg( WinWindowFromID( hwnd, IDE_FOCUS ), EM_SETTEXTLIMIT,
                   (MPARAM)WFOC_WIDTH, (MPARAM)0 );
       WinSendDlgItemMsg (hwnd, IDC_EXCLUDE, BM_SETCHECK,
                          MPFROMSHORT (FALSE), 0L);
       WinSendDlgItemMsg (hwnd, IDC_HIDDEN, BM_SETCHECK,
                          MPFROMSHORT (FALSE), 0L);
       WinSendDlgItemMsg (hwnd, IDC_LOCK, BM_SETCHECK,
                          MPFROMSHORT (FALSE), 0L);
       WinSendDlgItemMsg( hwnd, IDC_QKEY, SPBM_SETLIMITS,
                          MPFROMSHORT(9), MPFROMSHORT(0) );
       WinSendDlgItemMsg( hwnd, IDC_QKEY, SPBM_SETCURRENTVALUE,
                          MPFROMSHORT(0), 0L );
       WinSendDlgItemMsg( hwnd, IDC_QKEY, SPBM_SETTEXTLIMIT,
                          MPFROMSHORT(1L), 0L );
       WinSendDlgItemMsg( hwnd, IDC_ACTALARM, SPBM_SETLIMITS,
                          MPFROMSHORT(1440), MPFROMSHORT(0) );
       WinSendDlgItemMsg( hwnd, IDC_ACTALARM, SPBM_SETCURRENTVALUE,
                          MPFROMSHORT(0), 0L );
       WinSendDlgItemMsg( hwnd, IDC_ACTALARM, SPBM_SETTEXTLIMIT,
                          MPFROMSHORT(4L), 0L );

       if(subactwin == YES)
         fnActivityList(hwnd, subact, szBlank, IDC_PARENT, TRUE,
                        FALSE, TYPE_NO_PARENT);
       else
         fnActivityList(hwnd, szBlank, szBlank, IDC_PARENT, TRUE,
                        FALSE, TYPE_NO_PARENT);
     }
     break;                            /* end case (WM_INITDLG)               */

     case WM_COMMAND:
        switch (SHORT1FROMMP(mp1))
           {
            case DID_OK:               /* User clicked on OK push button      */
               {                       /* Process options settings and place  */
                                       /* into appropriate variables          */
                 APIRET rc;

                 rc = fnAddActivityCode( hab, hwnd );
                 if( rc == 0 )         /* no error, remove the dialog box     */
                   WinDismissDlg (hwnd, TRUE);
               }                       /* end case (DID_OK)                   */
               break;

            case DID_CANCEL:           /* User clicked on Cancel push button  */
               WinDismissDlg (hwnd, FALSE);
               break;

            case IDP_SAVE:             /* User clicked on Save push button    */
               {
                 APIRET rc;

                 rc = fnAddActivityCode( hab, hwnd );
                 if( rc == 0 )
                 {
                   WinSetWindowText(WinWindowFromID(hwnd, IDE_CODE), '\0');
                   WinSetWindowText(WinWindowFromID(hwnd, IDE_DESCRIPTION),
                                     '\0' );
                   WinSetWindowText(WinWindowFromID(hwnd, IDE_COMMENTS), '\0');
                   WinSetWindowText(WinWindowFromID(hwnd, IDE_ACTCMD), '\0');
                   WinSetWindowText(WinWindowFromID(hwnd, IDE_APARM), '\0');
                   WinSetWindowText(WinWindowFromID(hwnd, IDE_FOCUS), '\0');
                   WinSendDlgItemMsg (hwnd, IDC_EXCLUDE, BM_SETCHECK,
                                      MPFROMSHORT (FALSE), 0L);
                   WinSendDlgItemMsg (hwnd, IDC_HIDDEN, BM_SETCHECK,
                                      MPFROMSHORT (FALSE), 0L);
                   WinSendDlgItemMsg (hwnd, IDC_LOCK, BM_SETCHECK,
                                      MPFROMSHORT (FALSE), 0L);
                   WinSendDlgItemMsg( hwnd, IDC_QKEY, SPBM_SETCURRENTVALUE,
                                      MPFROMSHORT(0), 0L );
                   WinSendDlgItemMsg( hwnd, IDC_ACTALARM, SPBM_SETCURRENTVALUE,
                                      MPFROMSHORT(0), 0L );
                   WinSetFocus(HWND_DESKTOP, WinWindowFromID( hwnd, IDE_CODE));
                 }
               }
               break;

            default:                   /* Let PM handle rest of messages      */
               mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
               break;
           }
        break;

     default:                          /* Let PM handle rest of messages      */
        mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
        break;
    }

 return (mr);

}

/******************************************************************************/
/*                                                                            */
/* fnAddActivityCode: Add activity code to linked list.                       */
/*                                                                            */
/******************************************************************************/

APIRET fnAddActivityCode( HAB hab, HWND hwnd )

{

  APIRET   rc;
  PACTINFO activity;
  PACTINFO item;
  LONG     hotkey;
  CHAR     code[CODE_WIDTH+1];
  CHAR     parent[CODE_WIDTH+1];
  CHAR     description[DESC_WIDTH+1];
  CHAR     comments[COMM_WIDTH+1];
  CHAR     prog[PROG_WIDTH+1];
  CHAR     para[PARA_WIDTH+1];
  CHAR     wfoc[WFOC_WIDTH+1];
  SHORT    i,j;

  WinQueryWindowText( WinWindowFromID( hwnd, IDE_CODE ), sizeof( code ), code );
  WinQueryWindowText( WinWindowFromID( hwnd, IDE_DESCRIPTION ),
                      sizeof( description ), description );
  WinQueryWindowText( WinWindowFromID( hwnd, IDE_COMMENTS ),
                      sizeof( comments ), comments );
  WinQueryWindowText( WinWindowFromID( hwnd, IDE_ACTCMD ),
                      sizeof( prog ), prog );
  WinQueryWindowText( WinWindowFromID( hwnd, IDE_APARM ),
                      sizeof( para ), para );
  WinQueryWindowText( WinWindowFromID( hwnd, IDE_FOCUS ),
                      sizeof( wfoc ), wfoc );

  if( code[0] == '\0' )                /* Activity code is blank, error       */
  {
    WinLoadString( hab, 0L, IDS_ERRTITLE, sizeof( szTitle ), szTitle );
    WinLoadString( hab, 0L, IDS_CODENULL, sizeof( szText ), szText );
    WinMessageBox (HWND_DESKTOP, hwnd, szText, szTitle,
                   0, MB_WARNING | MB_OK | MB_MOVEABLE);
    WinSetFocus( HWND_DESKTOP, WinWindowFromID( hwnd, IDE_CODE ) );
    return( ERROR_CODE_NULL );
  }
  fnToUpperString( code );             /* put formatted data into data struct */
  fnPadString(code, CODE_WIDTH);
  j = (SHORT) WinSendDlgItemMsg( hwnd, IDC_PARENT,
              LM_QUERYSELECTION, 0L, 0L );
  if( j == 0 || j == LIT_NONE )
    strcpy(parent, szBlank);
  else
  {
    item = start;
    i = 1;
    while(item)
    {
      if(strcmp(item->parent, szBlank) == 0)
      {
        i++;
        if(i > j)
          break;
      }
      item = (PACTINFO)item->next;
    }
    if(strcmp(item->parent, szBlank) != 0)
    {
      /* Error, parent selected is a sub-activity */
      WinLoadString(hab, 0L, IDS_PARENT, sizeof(szTitle), szTitle );
      WinLoadString(hab, 0L, IDS_PARENTWARN1, sizeof(szText), szText);
      WinMessageBox(HWND_DESKTOP, hwnd, szText, szTitle,
                    0, MB_WARNING | MB_OK | MB_MOVEABLE);
      return(WARN_PARENT);
    }
    else
      strcpy(parent, item->code);
  }
  if(!fnCheckActivityCode(code, parent))
  {
    WinLoadString(hab, 0L, IDS_ACTCODE, sizeof(szTitle), szTitle );
    WinLoadString(hab, 0L, IDS_ACTCODEWARN, sizeof(szText), szText);
    WinMessageBox(HWND_DESKTOP, hwnd, szText, szTitle,
                  0, MB_WARNING | MB_OK | MB_MOVEABLE);
    return(WARN_DUP_CODE);
   }
  if( description[0] == '\0' )         /* Activity description blank, error   */
  {
    WinLoadString( hab, 0L, IDS_ERRTITLE, sizeof( szTitle ), szTitle );
    WinLoadString( hab, 0L, IDS_DESCNULL, sizeof( szText ), szText );
    WinMessageBox (HWND_DESKTOP, hwnd, szText, szTitle,
                   0, MB_WARNING | MB_OK | MB_MOVEABLE);
    WinSetFocus( HWND_DESKTOP, WinWindowFromID( hwnd, IDE_DESCRIPTION ) );
    return( ERROR_DESC_NULL );
  }
  WinSendDlgItemMsg(hwnd, IDC_QKEY, SPBM_QUERYVALUE, &hotkey,
                    MPFROM2SHORT(0L, 0L));
  if(!fnCheckHotkey(hotkey))
  {
    WinLoadString(hab, 0L, IDS_HOTKEY, sizeof(szTitle), szTitle );
    WinLoadString(hab, 0L, IDS_HOTKEYWARN, sizeof(szText), szText);
    WinMessageBox(HWND_DESKTOP, hwnd, szText, szTitle,
                  0, MB_WARNING | MB_OK | MB_MOVEABLE);
    return(WARN_HOTKEY);
  }

  /* No input errors, allocate memory for new activity */
  activity = (PACTINFO)malloc(sizeof(ACTINFO));
  if( !activity )
  {
    WinLoadString( hab, 0L, IDS_ERRTITLE, sizeof( szTitle ), szTitle );
    WinLoadString( hab, 0L, IDS_MEMERROR, sizeof( szText ), szText );
    WinMessageBox (HWND_DESKTOP, hwnd, szText, szTitle,
                   0, MB_WARNING | MB_OK | MB_MOVEABLE);
    return( ERROR_MEMORY );
  }

  strcpy( activity->code, code );
  fnStrip( description, activity->description, 'B', ' ' );
  fnStrip( comments, activity->comments, 'B', ' ' );
  fnToUpperString( prog );
  fnStrip( prog, activity->program, 'B', ' ' );
  fnToUpperString( para );
  fnStrip( para, activity->parameters, 'B', ' ' );
  fnStrip( wfoc, activity->winfocus, 'B', ' ' );
  activity->timer = (float)0;
  activity->count = 0;
  strcpy(activity->parent, parent);
  activity->children = 0;

  if( WinSendDlgItemMsg( hwnd, IDC_EXCLUDE, BM_QUERYCHECK, 0L, 0L ) )
    activity->exclude = EXCLUDE_CHAR;
  else
    activity->exclude = ' ';

  if( WinSendDlgItemMsg( hwnd, IDC_HIDDEN, BM_QUERYCHECK, 0L, 0L ) )
    activity->hide = HIDE_CHAR;
  else
    activity->hide = ' ';

  if( WinSendDlgItemMsg( hwnd, IDC_LOCK, BM_QUERYCHECK, 0L, 0L ) )
    activity->lock = LOCK_CHAR;
  else
    activity->lock = ' ';
  if(hotkey == 0)
    activity->hotkey = ' ';
  else
    activity->hotkey = hotkey+48;
  activity->expand = ' ';

  WinSendDlgItemMsg(hwnd, IDC_ACTALARM, SPBM_QUERYVALUE,
                    &(activity->alarmtime), MPFROM2SHORT(0L, 0L));

  fnPutLinkList( activity );           /* put at the end of the link list     */
  fnChangeParentInfo(activity->parent);
  totalactivities++;

  return( 0 );

}

/******************************************************************************/
/*                                                                            */
/* wpEditDlgProc: Window procedure for Edit Activity Code dialog box.         */
/*                                                                            */
/******************************************************************************/

MRESULT EXPENTRY wpEditDlgProc (HWND hwnd, ULONG msg, MPARAM mp1,
                                MPARAM mp2)

{

 MRESULT mr = (MRESULT) FALSE;
 static BOOL  fccodeFldChg = FALSE;
 static BOOL  fcdescFldChg = FALSE;
 static BOOL  fccommFldChg = FALSE;
 static BOOL  fcacmdFldChg = FALSE;
 static BOOL  fcparaFldChg = FALSE;
 static BOOL  fctimeFldChg = FALSE;
 static BOOL  fcwfocFldChg = FALSE;
 static HAB   hab;
 static CHAR  oldparent[CODE_WIDTH+1];
 static CHAR  oldcode[CODE_WIDTH+1];
 static ULONG oldhotkey;

 switch (msg)
    {
     case WM_INITDLG:                  /* Dialog initialization routine       */
       {                               /* Place data in entry fields          */
         PACTINFO actinfo;             /* Check/Uncheck check box             */
         ULONG    hotkey;

         hab = WinQueryAnchorBlock( hwnd );

         actinfo = PVOIDFROMMP (mp2);
         WinSetWindowPtr( hwnd, QWL_USER, actinfo );
                                       /* activity code, set max width        */
         WinSetWindowText( WinWindowFromID( hwnd, IDE_CODE ),
                           actinfo->code );
         WinSendMsg( WinWindowFromID( hwnd, IDE_CODE ), EM_SETTEXTLIMIT,
                     (MPARAM)CODE_WIDTH, (MPARAM)0 );
                                       /* description, set max width          */
         WinSetWindowText( WinWindowFromID( hwnd, IDE_DESCRIPTION ),
                           actinfo->description );
         WinSendMsg( WinWindowFromID( hwnd, IDE_DESCRIPTION ), EM_SETTEXTLIMIT,
                     (MPARAM)DESC_WIDTH, (MPARAM)0 );
                                       /* comments, set max width             */
         WinSetWindowText( WinWindowFromID( hwnd, IDE_COMMENTS ),
                           actinfo->comments );
         WinSendMsg( WinWindowFromID( hwnd, IDE_COMMENTS ), EM_SETTEXTLIMIT,
                     (MPARAM)COMM_WIDTH, (MPARAM)0 );
                                       /* program, set max width              */
         WinSetWindowText( WinWindowFromID( hwnd, IDE_ACTCMD ),
                           actinfo->program );
         WinSendMsg( WinWindowFromID( hwnd, IDE_ACTCMD ), EM_SETTEXTLIMIT,
                     (MPARAM)PROG_WIDTH, (MPARAM)0 );
                                       /* parameters, set max width           */
         WinSetWindowText( WinWindowFromID( hwnd, IDE_APARM ),
                           actinfo->parameters );
         WinSendMsg( WinWindowFromID( hwnd, IDE_APARM ), EM_SETTEXTLIMIT,
                     (MPARAM)PARA_WIDTH, (MPARAM)0 );
                                       /* window focus, set max width         */
         WinSetWindowText( WinWindowFromID( hwnd, IDE_FOCUS ),
                           actinfo->winfocus );
         WinSendMsg( WinWindowFromID( hwnd, IDE_FOCUS ), EM_SETTEXTLIMIT,
                     (MPARAM)WFOC_WIDTH, (MPARAM)0 );
                                       /* track time, float variable          */
         fnTimeControl(hwnd, actinfo->timer, 0);
                                       /* count spin button                   */
         WinSendDlgItemMsg( hwnd, IDC_COUNT, SPBM_SETLIMITS,
                            MPFROMSHORT(999), MPFROMSHORT(0) );
         WinSendDlgItemMsg( hwnd, IDC_COUNT, SPBM_SETCURRENTVALUE,
                            MPFROMSHORT(actinfo->count), 0L );
         WinSendDlgItemMsg( hwnd, IDC_COUNT, SPBM_SETTEXTLIMIT,
                            MPFROMSHORT(3L), 0L );
                                       /* Exclude from total check box        */
         if( actinfo->exclude == ' ' )
           WinSendDlgItemMsg (hwnd, IDC_EXCLUDE, BM_SETCHECK,
                              MPFROMSHORT (FALSE), 0L);
         else
           WinSendDlgItemMsg (hwnd, IDC_EXCLUDE, BM_SETCHECK,
                              MPFROMSHORT (TRUE), 0L);

         if( actinfo->hide == ' ' )
           WinSendDlgItemMsg (hwnd, IDC_HIDDEN, BM_SETCHECK,
                              MPFROMSHORT (FALSE), 0L);
         else
           WinSendDlgItemMsg (hwnd, IDC_HIDDEN, BM_SETCHECK,
                              MPFROMSHORT (TRUE), 0L);

         if( actinfo->lock == ' ' )
           WinSendDlgItemMsg (hwnd, IDC_LOCK, BM_SETCHECK,
                              MPFROMSHORT (FALSE), 0L);
         else
           WinSendDlgItemMsg (hwnd, IDC_LOCK, BM_SETCHECK,
                              MPFROMSHORT (TRUE), 0L);

         if(actinfo->hotkey == ' ')
           hotkey = 0;
         else
           hotkey = actinfo->hotkey - 48;
         oldhotkey = hotkey;
         WinSendDlgItemMsg( hwnd, IDC_QKEY, SPBM_SETLIMITS,
                            MPFROMSHORT(9), MPFROMSHORT(0) );
         WinSendDlgItemMsg( hwnd, IDC_QKEY, SPBM_SETCURRENTVALUE,
                            MPFROMSHORT(hotkey), 0L );
         WinSendDlgItemMsg( hwnd, IDC_QKEY, SPBM_SETTEXTLIMIT,
                            MPFROMSHORT(1L), 0L );
                                       /* alarm time spin button              */
         WinSendDlgItemMsg( hwnd, IDC_ACTALARM, SPBM_SETLIMITS,
                            MPFROMSHORT(1440), MPFROMSHORT(0) );
         WinSendDlgItemMsg( hwnd, IDC_ACTALARM, SPBM_SETCURRENTVALUE,
                            MPFROMSHORT(actinfo->alarmtime), 0L );
         WinSendDlgItemMsg( hwnd, IDC_ACTALARM, SPBM_SETTEXTLIMIT,
                            MPFROMSHORT(4L), 0L );

         fnActivityList(hwnd, actinfo->parent, szBlank, IDC_PARENT,
                        TRUE, FALSE, TYPE_NO_PARENT);

         if(actinfo->children > 0)     /* If activity has sub-activities, do  */
         {                             /* not allow to modify time and count  */
           WinEnableControl(hwnd, IDC_PARENT, FALSE);          /* and parent  */
           WinEnableControl(hwnd, IDC_COUNT, FALSE);
           WinEnableControl(hwnd, IDC_HH, FALSE);
           WinEnableControl(hwnd, IDC_MM, FALSE);
           WinEnableControl(hwnd, IDC_SS, FALSE);
           WinEnableControl(hwnd, IDC_ACTALARM, FALSE);
         }

         strcpy(oldparent, actinfo->parent);
         strcpy(oldcode, actinfo->code);
       }
       break;                          /* end case (WM_INITDLG)               */

     case WM_CONTROL:
       switch( SHORT1FROMMP( mp1 ))    /* determine if entry fields changed   */
       {
         case IDE_CODE:
           if( (USHORT) SHORT2FROMMP(mp1) == EN_CHANGE )
             fccodeFldChg = TRUE;
           break;
         case IDE_DESCRIPTION:
           if( (USHORT) SHORT2FROMMP(mp1) == EN_CHANGE )
             fcdescFldChg = TRUE;
           break;
         case IDE_COMMENTS:
           if( (USHORT) SHORT2FROMMP(mp1) == EN_CHANGE )
             fccommFldChg = TRUE;
           break;
         case IDE_ACTCMD:
           if( (USHORT) SHORT2FROMMP(mp1) == EN_CHANGE )
             fcacmdFldChg = TRUE;
           break;
         case IDE_APARM:
           if( (USHORT) SHORT2FROMMP(mp1) == EN_CHANGE )
             fcparaFldChg = TRUE;
           break;
         case IDE_FOCUS:
           if( (USHORT) SHORT2FROMMP(mp1) == EN_CHANGE )
             fcwfocFldChg = TRUE;
           break;
         default:
           mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
           break;
       }                               /* end case WM_CONTROL                 */
       break;

     case WM_COMMAND:
        switch (SHORT1FROMMP(mp1))
           {
            case DID_OK:               /* User clicked on OK push button      */
               {                       /* Process options settings and place  */
                                       /* into appropriate variables          */
                 PACTINFO actinfo;
                 PACTINFO item;
                 LONG     hotkey, rc;
                 CHAR     code[CODE_WIDTH+1];
                 CHAR     parent[CODE_WIDTH+1];
                 CHAR     desc[DESC_WIDTH+1];
                 CHAR     comm[COMM_WIDTH+1];
                 CHAR     prog[PROG_WIDTH+1];
                 CHAR     para[PARA_WIDTH+1];
                 CHAR     wfoc[WFOC_WIDTH+1];
                 SHORT    i, j;

                 rc = 0;
                 actinfo = WinQueryWindowPtr( hwnd, QWL_USER );

                 // Check parent
                 j = (SHORT) WinSendDlgItemMsg( hwnd, IDC_PARENT,
                             LM_QUERYSELECTION, 0L, 0L );
                 if( j == 0 || j == LIT_NONE )
                   strcpy(parent, szBlank);
                 else
                 {
                   item = start;
                   i = 1;
                   while(item)
                   {
                     if(strcmp(item->parent, szBlank) == 0)
                     {
                       i++;
                       if(i > j)
                         break;
                     }
                     item = (PACTINFO)item->next;
                   }
                   strcpy(parent, item->code);
                   if(strcmp(parent, actinfo->code) == 0)  /* 1.99 */
                   {
                     // Activity cannot be the parent
                     WinLoadString(hab, 0L, IDS_PARENT, sizeof(szTitle),
                                   szTitle );
                     WinLoadString(hab, 0L, IDS_PARENTWARN3,
                                   sizeof(szText), szText);
                     WinMessageBox(HWND_DESKTOP, hwnd, szText, szTitle,
                                   0, MB_WARNING | MB_OK | MB_MOVEABLE);
                     WinSetFocus(HWND_DESKTOP, WinWindowFromID(hwnd,
                                 IDC_PARENT));
                     rc = WARN_PARENT;
                   }
                   else
                   {
                     if(strcmp(parent, oldparent) != 0)
                     {
                       if(strcmp(item->parent, szBlank) != 0)
                       {
                         // Error, selected parent is a sub-activity
                         WinLoadString(hab, 0L, IDS_PARENT, sizeof(szTitle),
                                       szTitle );
                         WinLoadString(hab, 0L, IDS_PARENTWARN1,
                                       sizeof(szText), szText);
                         WinMessageBox(HWND_DESKTOP, hwnd, szText, szTitle,
                                       0, MB_WARNING | MB_OK | MB_MOVEABLE);
                         WinSetFocus(HWND_DESKTOP, WinWindowFromID(hwnd,
                                     IDC_PARENT));
                         rc = WARN_PARENT;
                       }
                       else
                       {
                         if(actinfo->children > 0)
                         {
                           // Activity cannot have parent because it is
                           // already a parent itself
                           WinLoadString(hab, 0L, IDS_PARENT, sizeof(szTitle),
                                         szTitle );
                           WinLoadString(hab, 0L, IDS_PARENTWARN2,
                                         sizeof(szText), szText);
                           WinMessageBox(HWND_DESKTOP, hwnd, szText, szTitle,
                                         0, MB_WARNING | MB_OK | MB_MOVEABLE);
                           WinSetFocus(HWND_DESKTOP, WinWindowFromID(hwnd,
                                       IDC_PARENT));
                           rc = WARN_PARENT;
                         }
                       }
                     }
                   }
                 }
                 if(rc == 0)
                 {
                   WinQueryWindowText( WinWindowFromID( hwnd, IDE_CODE ),
                                       sizeof( code ), code );
                   fnToUpperString( code );
                   fnPadString(code, CODE_WIDTH);
                   if(strcmp(code, szBlank)==0)
                   {
                     WinLoadString(hab, 0L, IDS_ERRTITLE, sizeof( szTitle ),
                                   szTitle);
                     WinLoadString(hab, 0L, IDS_CODENULL, sizeof( szText ),
                                   szText);
                     rc = ERROR_CODE_NULL;
                   }
                   else
                   {
                     if(strcmp(code, oldcode) != 0 ||
                        strcmp(parent, oldparent) != 0)
                     {
                       if(!fnCheckActivityCode(code, parent))
                       {
                         WinLoadString(hab, 0L, IDS_ACTCODE, sizeof(szTitle),
                                       szTitle);
                         WinLoadString(hab, 0L, IDS_ACTCODEWARN, sizeof(szText),
                                       szText);
                         rc = WARN_DUP_CODE;
                       }
                     }
                   }
                   if(rc != 0)
                   {
                     WinMessageBox(HWND_DESKTOP, hwnd, szText, szTitle,
                                   0, MB_WARNING | MB_OK | MB_MOVEABLE);
                     WinSetFocus(HWND_DESKTOP, WinWindowFromID(hwnd, IDE_CODE));
                   }
                 }
                 if(rc == 0)
                 {
                   // Check description
                   if( fcdescFldChg == TRUE )
                   {
                     WinQueryWindowText(WinWindowFromID(hwnd, IDE_DESCRIPTION),
                                        sizeof(desc), desc);
                     if( desc[0] == '\0' )
                     {
                       WinLoadString( hab, 0L, IDS_ERRTITLE,
                                      sizeof( szTitle ), szTitle );
                       WinLoadString( hab, 0L, IDS_DESCNULL,
                                      sizeof( szText ), szText );
                       WinMessageBox (HWND_DESKTOP, hwnd, szText, szTitle,
                                      0, MB_WARNING | MB_OK | MB_MOVEABLE);
                       WinSetFocus( HWND_DESKTOP, WinWindowFromID( hwnd,
                                    IDE_DESCRIPTION ) );
                       rc = ERROR_DESC_NULL;
                     }
                   }
                 }
                 if(rc == 0)
                 {
                   // Check quick key
                   WinSendDlgItemMsg(hwnd, IDC_QKEY, SPBM_QUERYVALUE,
                                     &hotkey, MPFROM2SHORT(0L, 0L));
                   if(hotkey != oldhotkey)
                   {
                     if(!fnCheckHotkey(hotkey))
                     {
                       WinLoadString(hab, 0L, IDS_HOTKEY, sizeof(szTitle),
                                     szTitle );
                       WinLoadString(hab, 0L, IDS_HOTKEYWARN,
                                     sizeof(szText), szText);
                       WinMessageBox(HWND_DESKTOP, hwnd, szText, szTitle,
                                     0, MB_WARNING | MB_OK | MB_MOVEABLE);
                       WinSetFocus(HWND_DESKTOP, WinWindowFromID(hwnd,
                                   IDC_QKEY));
                       rc = WARN_HOTKEY;
                     }
                   }
                 }
                 // Ok no input errors, transfer data into actinfo structure
                 if(rc == 0)
                 {
                   strcpy(actinfo->code, code);
                   if(strcmp(oldcode, actinfo->code) != 0)
                     fnChangeParent(oldcode, code);
                   strcpy(actinfo->parent, parent);

                   if( fcdescFldChg == TRUE )
                     fnStrip( desc, actinfo->description, 'B', ' ' );

                   if( WinSendDlgItemMsg( hwnd, IDC_EXCLUDE,
                       BM_QUERYCHECK, 0L, 0L ) )
                     actinfo->exclude = EXCLUDE_CHAR;
                   else
                     actinfo->exclude = ' ';

                   if( WinSendDlgItemMsg( hwnd, IDC_HIDDEN,
                       BM_QUERYCHECK, 0L, 0L ) )
                     actinfo->hide = HIDE_CHAR;
                   else
                     actinfo->hide = ' ';

                   if( WinSendDlgItemMsg( hwnd, IDC_LOCK,
                       BM_QUERYCHECK, 0L, 0L ) )
                     actinfo->lock = LOCK_CHAR;
                   else
                     actinfo->lock = ' ';

                   WinSendDlgItemMsg(hwnd, IDC_COUNT, SPBM_QUERYVALUE,
                      &(actinfo->count), MPFROM2SHORT(0L, 0L));

                   if( fccommFldChg == TRUE )
                   {
                     WinQueryWindowText( WinWindowFromID( hwnd, IDE_COMMENTS ),
                                         sizeof( comm ), comm );
                     fnStrip( comm, actinfo->comments, 'B', ' ' );
                   }

                   if( fcacmdFldChg == TRUE )
                   {
                     WinQueryWindowText( WinWindowFromID( hwnd, IDE_ACTCMD ),
                                         sizeof( prog ), prog );
                     fnToUpperString( prog );
                     fnStrip( prog, actinfo->program, 'B', ' ' );
                   }

                   if( fcparaFldChg == TRUE )
                   {
                     WinQueryWindowText( WinWindowFromID( hwnd, IDE_APARM ),
                                         sizeof( para ), para );
                     fnToUpperString( para );
                     fnStrip( para, actinfo->parameters, 'B', ' ' );
                   }

                   if( fcwfocFldChg == TRUE )
                   {
                     WinQueryWindowText( WinWindowFromID( hwnd, IDE_FOCUS ),
                                         sizeof( wfoc ), wfoc );
                     fnStrip( wfoc, actinfo->winfocus, 'B', ' ' );
                   }

                   if(hotkey == 0)
                     actinfo->hotkey = ' ';
                   else
                     actinfo->hotkey = hotkey+48;

                   WinSendDlgItemMsg(hwnd, IDC_ACTALARM, SPBM_QUERYVALUE,
                      &(actinfo->alarmtime), MPFROM2SHORT(0L, 0L));

                   DosRequestMutexSem( hmtxNB, SEM_INDEFINITE_WAIT );
                   actinfo->timer = fnTimeControl(hwnd, 0.0, 1);
                   if(strcmp(actinfo->parent, oldparent) != 0)
                     fnChangeParentInfo(oldparent);
                   fnChangeParentInfo(actinfo->parent);
                   DosReleaseMutexSem( hmtxNB );

                   WinDismissDlg (hwnd, TRUE);   /* remove the dialog box  */
                 }
               }                       /* end case (DID_OK)                   */
               break;

            case DID_CANCEL:           /* User clicked on Cancel push button  */
               WinDismissDlg (hwnd, FALSE);
               break;

            default:                   /* Let PM handle rest of messages      */
               mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
               break;
           }
        break;

     default:                          /* Let PM handle rest of messages      */
        mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
        break;
    }

 return (mr);
}

/******************************************************************************/
/*                                                                            */
/* wpTransferDlgProc: Window procedure for Transfer dialog box.               */
/*                                                                            */
/******************************************************************************/

MRESULT EXPENTRY wpTransferDlgProc (HWND hwnd, ULONG msg, MPARAM mp1,
                                MPARAM mp2)

{

 MRESULT mr = (MRESULT) FALSE;
 static  HAB  hab;

 switch (msg)
    {
     case WM_INITDLG:                  /* Dialog initialization routine       */
       {                               /* Place data in entry fields          */
         PACTINFO actinfo;             /* Check/Uncheck check box             */

         hab = WinQueryAnchorBlock( hwnd );

         actinfo = PVOIDFROMMP (mp2);
         WinSetWindowPtr( hwnd, QWL_USER, actinfo );
                                       /* activity code, set max width        */
         WinSetWindowText( WinWindowFromID( hwnd, IDS_TRANSFER ),
                           actinfo->code );

                                       /* track time, float variable          */
         fnTimeControl(hwnd, actinfo->timer, 0);

         fnActivityList(hwnd, actinfo->code, actinfo->parent, IDC_TRANSFER,
                        FALSE, TRUE, TYPE_NO_CHILD);

         WinSendDlgItemMsg( hwnd, IDC_COUNT, SPBM_SETLIMITS,
                            MPFROMSHORT(actinfo->count), MPFROMSHORT(0) );
         WinSendDlgItemMsg( hwnd, IDC_COUNT, SPBM_SETCURRENTVALUE,
                            MPFROMSHORT(actinfo->count), 0L );
         WinSendDlgItemMsg( hwnd, IDC_COUNT, SPBM_SETTEXTLIMIT,
                            MPFROMSHORT(3L), 0L );

       }
       break;                          /* end case (WM_INITDLG)               */

     case WM_CONTROL:
       switch (SHORT1FROMMP (mp1))
          {                            /* Save data to file must be On to     */
           case IDC_ADDCOUNT:          /* enable Prune days spin button ctrl  */
             if( SHORT2FROMMP (mp1) == BN_CLICKED )
               if( WinSendDlgItemMsg( hwnd, IDC_ADDCOUNT,
                                     BM_QUERYCHECK, 0L, 0L ) )
                 WinEnableControl( hwnd, IDC_COUNT, FALSE );
               else
                 WinEnableControl( hwnd, IDC_COUNT, TRUE );
             break;

           default:
             break;
          }
       break;

     case WM_COMMAND:
        switch (SHORT1FROMMP(mp1))
           {
            case DID_OK:               /* User clicked on OK push button      */
               {                       /* Process options settings and place  */
                                       /* into appropriate variables          */
                 PACTINFO actinfo, item;
                 float    trantime;
                 ULONG    trancount;
                 SHORT    i, j;

                 actinfo = WinQueryWindowPtr( hwnd, QWL_USER );

                 trantime = fnTimeControl(hwnd, 0.0, 1);
                 if(trantime > actinfo->timer)              // V1.97
                    trantime = actinfo->timer;

                 WinSendDlgItemMsg(hwnd, IDC_COUNT, SPBM_QUERYVALUE,
                                   &trancount, MPFROM2SHORT(0L, 0L));

                 j = (SHORT) WinSendDlgItemMsg( hwnd, IDC_TRANSFER,
                             LM_QUERYSELECTION, 0L, 0L );
                 if( j != LIT_NONE)
                 {
                   item = start;
                   i = 0;
                   while(item)
                   {
                     if(item->children == 0)
                     {
                       i++;
                       if(i > j)
                         break;
                     }
                     item = (PACTINFO)item->next;
                   }

                   if(item->children > 0)
                   {
                     WinLoadString(hab, 0L, IDS_TRAN, sizeof(szTitle),
                                   szTitle);
                     WinLoadString(hab, 0L, IDS_TRANWARN, sizeof(szText),
                                   szText);
                     WinMessageBox(HWND_DESKTOP, hwnd, szText, szTitle,
                                   0, MB_WARNING | MB_OK | MB_MOVEABLE);
                   }
                   else
                   {
                     DosRequestMutexSem( hmtxNB, SEM_INDEFINITE_WAIT );
                     actinfo->timer = actinfo->timer - trantime + ROUND_OFF_0;
                     item->timer    = item->timer    + trantime;
                     if(WinSendDlgItemMsg(hwnd, IDC_ADDCOUNT,
                                          BM_QUERYCHECK, 0L, 0L))
                       item->count    = item->count + 1;
                     else
                     {
                       actinfo->count = actinfo->count - trancount;
                       item->count    = item->count    + trancount;
                     }
                     if(strcmp(actinfo->parent, item->parent) != 0)
                     {
                       fnChangeParentInfo(actinfo->parent);
                       fnChangeParentInfo(item->parent);
                     }
                     DosReleaseMutexSem( hmtxNB );

                     WinDismissDlg (hwnd, TRUE);    /* remove the dialog box  */
                   }
                 }                                  /* end if j != LIT_NONE   */
               }                       /* end case (DID_OK)                   */
               break;

            case DID_CANCEL:           /* User clicked on Cancel push button  */
               WinDismissDlg (hwnd, FALSE);
               break;

            default:                   /* Let PM handle rest of messages      */
               mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
               break;
           }
        break;

     default:                          /* Let PM handle rest of messages      */
        mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
        break;
    }

 return (mr);

}

/******************************************************************************/
/*                                                                            */
/* wpSetAlarmDlgProc: Window procedure for Set Alarm Interval dialog box.     */
/*                                                                            */
/******************************************************************************/

MRESULT EXPENTRY wpSetAlarmDlgProc (HWND hwnd, ULONG msg, MPARAM mp1,
                                    MPARAM mp2)

{

 MRESULT mr = (MRESULT) FALSE;

 switch (msg)
    {
     case WM_INITDLG:                  /* dialog initialization routine       */
       {
         WinSendDlgItemMsg( hwnd, IDC_NEWALARM, SPBM_SETLIMITS,
                            MPFROMSHORT(1440), MPFROMSHORT(0) );
         WinSendDlgItemMsg( hwnd, IDC_NEWALARM, SPBM_SETCURRENTVALUE,
                            MPFROMSHORT(alarmtime), 0L );
         WinSendDlgItemMsg( hwnd, IDC_NEWALARM, SPBM_SETTEXTLIMIT,
                            MPFROMSHORT(4L), 0L );
       }
       break;                          /* end case (WM_INITDLG)               */

     case WM_COMMAND:
        switch (SHORT1FROMMP(mp1))
           {
            case DID_OK:               /* User clicked on OK push button      */
               {                       /* Process options settings and place  */
                 WinSendDlgItemMsg( hwnd, IDC_NEWALARM, SPBM_QUERYVALUE,
                                    &alarmtime, MPFROM2SHORT( 0L, 0L ));
                 WinDismissDlg (hwnd, TRUE);        /* remove the dialog box  */
               }                       /* end case (DID_OK)                   */
               break;

            case DID_CANCEL:           /* User clicked on Cancel push button  */
               WinDismissDlg(hwnd, FALSE);
               break;

            default:                   /* Let PM handle rest of messages      */
               mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
               break;
           }
        break;

     default:                          /* Let PM handle rest of messages      */
        mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
        break;
    }

 return (mr);

}

/******************************************************************************/
/*                                                                            */
/* wpAlarmMsgDlgProc: Window procedure for Set Alarm Interval dialog box.     */
/*                                                                            */
/******************************************************************************/

MRESULT EXPENTRY wpAlarmMsgDlgProc (HWND hwnd, ULONG msg, MPARAM mp1,
                                    MPARAM mp2)

{

 MRESULT mr = (MRESULT) FALSE;
 static  HAB hab;
 static  ULONG alarmtimecount;

 switch (msg)
    {
     case WM_INITDLG:                  /* dialog initialization routine       */
       {

         PACTINFO actinfo;             /* Check/Uncheck check box             */
         CHAR     showunit[12];
         CHAR     activity[CODE_WIDTH+1];

         alarmflag = OFF;
         hab  = WinQueryAnchorBlock( hwnd );

         actinfo = PVOIDFROMMP (mp2);
         WinSetWindowPtr( hwnd, QWL_USER, actinfo );

         fnSubstr(alarmitem, activity, 1, CODE_WIDTH);

         WinSetWindowText( WinWindowFromID( hwnd, IDS_CURACT ),
                           actinfo->code );
         WinSetWindowText( WinWindowFromID( hwnd, IDS_PARACT ),
                           actinfo->parent );
         if(strncmp(activity, "$CURACT$", CODE_WIDTH) == 0)
         {
           WinLoadString( hab, 0L, IDS_CURRENT, sizeof( szTitle ), szTitle );
           WinSetWindowText( WinWindowFromID( hwnd, IDS_DEFACT ), szTitle );
         }
         else
           WinSetWindowText( WinWindowFromID( hwnd, IDS_DEFACT ),
                             activity );
         WinLoadString( hab, 0L, IDS_MINUTES, sizeof( showunit ), showunit );
         if(actinfo->alarmtime > 0)
           sprintf( szText, "%d %s", actinfo->alarmtime, showunit );
         else
           sprintf( szText, "%d %s", alarmtime, showunit );
         WinSetWindowText( WinWindowFromID( hwnd, IDS_ALARMINT ), szText );

         sprintf( szText, "%d %s", alarmexp, showunit );
         WinSetWindowText( WinWindowFromID( hwnd, IDS_ALARMEXP ), szText );

         alarmtimecount = alarmexp;

         if( alarmitem[0] != ' ' )
           WinStartTimer( hab, hwnd, ID_ALARMMSGTIMER, ALARMMSG_MINUTE );
       }
       break;                          /* end case (WM_INITDLG)               */

     case WM_TIMER:
       {
          USHORT timerid;              /* get timer id from mp1 first         */
          timerid = SHORT1FROMMP( mp1 );

          switch( timerid )
          {
            case ID_ALARMMSGTIMER:     /* alarm reminder timer procedure here */
              {
                alarmtimecount--;
                if( alarmtimecount == 0 )
                {
                  WinStopTimer( hab, hwnd, ID_ALARMMSGTIMER );
                  alarmflag = ON;
                  WinDismissDlg (hwnd, FALSE );
                }
              }
              break;

            default:
              break;
          }
       }
       break;


     case WM_COMMAND:
        switch (SHORT1FROMMP(mp1))
           {
            case DID_OK:               /* User clicked on Stop push button    */
               if( alarmitem[0] != ' ' )
                 WinStopTimer( hab, hwnd, ID_ALARMMSGTIMER );
               WinDismissDlg (hwnd, TRUE);          /* remove the dialog box  */
               break;

            case DID_CANCEL:           /* User clicked on Continue push button*/
               if( alarmitem[0] != ' ' )
                 WinStopTimer( hab, hwnd, ID_ALARMMSGTIMER );
/*             alarmflag = ON; */
               WinDismissDlg(hwnd, FALSE);
               break;

            default:                   /* Let PM handle rest of messages      */
               mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
               break;
           }
        break;

     default:                          /* Let PM handle rest of messages      */
        mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
        break;
    }

 return (mr);

}

/******************************************************************************/
/*                                                                            */
/* wpSaveReportDlgProc: Window procedure for Save Report dialog box.          */
/*                                                                            */
/******************************************************************************/

MRESULT EXPENTRY wpSaveReportDlgProc (HWND hwnd, ULONG msg, MPARAM mp1,
                                      MPARAM mp2)

{

 MRESULT mr = (MRESULT) FALSE;
 static BOOL fcFldChg = FALSE;
 static HAB  hab;

 switch (msg)
    {
     case WM_INITDLG:                  /* dialog initialization routine       */
       {
          CHAR *szBuffer;

          hab  = WinQueryAnchorBlock( hwnd );

          szBuffer = PVOIDFROMMP (mp2);
          WinSetWindowPtr( hwnd, QWL_USER, szBuffer );

          WinSetWindowText( WinWindowFromID( hwnd, IDE_REPFILE ), repfile );
          WinSendMsg( WinWindowFromID( hwnd, IDE_REPFILE ), EM_SETTEXTLIMIT,
                      (MPARAM)(79), (MPARAM)0 );
       }
       break;                          /* end case (WM_INITDLG)               */

     case WM_CONTROL:
       switch( SHORT1FROMMP( mp1 ))
       {
         case IDE_REPFILE:
           if( (USHORT) SHORT2FROMMP(mp1) == EN_CHANGE )
             fcFldChg = TRUE;
           break;
         default:
           break;
      }
      break;

     case WM_COMMAND:
        switch (SHORT1FROMMP(mp1))
           {
            case DID_OK:               /* User clicked on OK push button      */
               {                       /* Process options settings and place  */
                 CHAR *szBuffer;
                 FILE *pOutfile;

                 if( fcFldChg == TRUE )
                   WinQueryWindowText( WinWindowFromID( hwnd, IDE_REPFILE ),
                                       sizeof( repfile ), repfile );
                 fnToUpperString( repfile );

                 szBuffer = WinQueryWindowPtr( hwnd, QWL_USER );
                 if( pOutfile = fopen( repfile, "w" ))
                 {
                   fputs( szBuffer, pOutfile );
                   fclose( pOutfile );
                   WinDismissDlg (hwnd, TRUE);      /* remove the dialog box  */
                 }
                 else
                 {
                   /* 1.98 */
                   WinLoadString(hab, 0L, IDS_ERRTITLE, sizeof(szTitle), szTitle );
                   WinLoadString(hab, 0L, IDS_SAVEERROR, sizeof(szText), szText);
                   WinMessageBox(HWND_DESKTOP, hwnd, szText, szTitle,
                                 0, MB_WARNING | MB_OK | MB_MOVEABLE);
                 }
               }                       /* end case (DID_OK)                   */
               break;

            case DID_CANCEL:           /* User clicked on Cancel push button  */
               WinDismissDlg(hwnd, FALSE);
               break;

            default:                   /* Let PM handle rest of messages      */
               mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
               break;
           }
        break;

     default:                          /* Let PM handle rest of messages      */
        mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
        break;
    }

 return (mr);

}

/******************************************************************************/
/*                                                                            */
/* wpRepEditDlgProc: Window procedure to Create Report dialog box.            */
/*                                                                            */
/******************************************************************************/

MRESULT EXPENTRY wpRepEditDlgProc (HWND hwnd, ULONG msg, MPARAM mp1,
                                   MPARAM mp2)

{

 MRESULT mr = (MRESULT) FALSE;
 static float  total;
 static HAB  hab;
 static PACTDATA selitem;
 static PACTDATA startdata;
 static PACTDATA lastdata;

 switch (msg)
    {
     case WM_INITDLG:                  /* Dialog initialization routine       */
       {
         struct tm *today;
         time_t    ltime;

         startdata = NULL;
         lastdata  = NULL;
         selitem = fnInitRepData( 0, hwnd, &startdata, &lastdata,
                                  &total, NULL, NULL );
         total = 0.0;
                                       /* initialize count spin button here   */
         WinSendDlgItemMsg( hwnd, IDC_COUNT, SPBM_SETLIMITS,
                            MPFROMSHORT(999), MPFROMSHORT(0) );
         WinSendDlgItemMsg( hwnd, IDC_COUNT, SPBM_SETTEXTLIMIT,
                            MPFROMSHORT(3L), 0L );

         time( &ltime );
         today = localtime( &ltime );
         WinSendDlgItemMsg( hwnd, IDC_MONTH, SPBM_SETLIMITS,
                            MPFROMSHORT(12), MPFROMSHORT(1) );
         WinSendDlgItemMsg( hwnd, IDC_MONTH, SPBM_SETTEXTLIMIT,
                            MPFROMSHORT(2L), 0L );
         WinSendDlgItemMsg( hwnd, IDC_MONTH, SPBM_SETCURRENTVALUE,
                            MPFROMSHORT(today->tm_mon+1), 0L );
         WinSendDlgItemMsg( hwnd, IDC_DAY, SPBM_SETLIMITS,
                            MPFROMSHORT(31), MPFROMSHORT(1) );
         WinSendDlgItemMsg( hwnd, IDC_DAY, SPBM_SETTEXTLIMIT,
                            MPFROMSHORT(2L), 0L );
         WinSendDlgItemMsg( hwnd, IDC_DAY, SPBM_SETCURRENTVALUE,
                            MPFROMSHORT(today->tm_mday), 0L );
         WinSendDlgItemMsg( hwnd, IDC_YEAR, SPBM_SETLIMITS,
                            MPFROMSHORT(9999), MPFROMSHORT(1900));
         WinSendDlgItemMsg( hwnd, IDC_YEAR, SPBM_SETTEXTLIMIT,
                            MPFROMSHORT(4L), 0L );
         WinSendDlgItemMsg( hwnd, IDC_YEAR, SPBM_SETCURRENTVALUE,
                            MPFROMSHORT(1900+today->tm_year), 0L );
         WinSendMsg( WinWindowFromID( hwnd, IDE_COMMENTS ), EM_SETTEXTLIMIT,
                     (MPARAM)COMM_WIDTH, (MPARAM)0 );
         WinSendMsg( WinWindowFromID( hwnd, IDE_PARENT ), EM_SETTEXTLIMIT,
                     (MPARAM)CODE_WIDTH, (MPARAM)0 );
       }
       break;                          /* end case (WM_INITDLG)               */

     case WM_CHAR:
     case WM_BUTTON1DOWN:
     case WM_BUTTON2DOWN:
       {
         if(WinWindowFromID(hwnd,IDL_ACTIVITY) == WinQueryFocus(HWND_DESKTOP))
         {
           PACTDATA item;
           ULONG    i, j;
           CHAR     szTime[10];

           WinSendDlgItemMsg( hwnd, IDC_COUNT, SPBM_QUERYVALUE,
                              &(selitem->repcount), MPFROM2SHORT(0L, 0L));

           selitem->reptimer = fnTimeControl(hwnd, 0.0, 1);

           WinQueryWindowText( WinWindowFromID( hwnd, IDE_COMMENTS ),
                               sizeof( selitem->repcom ), selitem->repcom );
           fnChangeParentReport( selitem->repparent, startdata );

           j = WinQueryLboxSelectedItem( WinWindowFromID( hwnd,
               IDL_ACTIVITY ));
           item = startdata;
           for( i = 0; i < j; i++ )
             item = (PACTDATA)item->next;

           if(item != selitem)
           {
             fnTimeControl(hwnd, item->reptimer, 0);
             WinSendDlgItemMsg( hwnd, IDC_COUNT, SPBM_SETCURRENTVALUE,
                                MPFROMSHORT(item->repcount), 0L );
             selitem = item;
             WinSetWindowText(WinWindowFromID(hwnd, IDS_CODE),
                               selitem->code);
             WinSetWindowText(WinWindowFromID(hwnd, IDE_COMMENTS),
                               selitem->repcom);
             WinSetWindowText(WinWindowFromID(hwnd, IDE_PARENT),
                               selitem->repparent);
             fnStrip(selitem->repparent, selitem->repparent, 'B', ' ');
             fnChangeParentReport( selitem->repparent, startdata );
           }
           total = ROUND_OFF_0;
           item = startdata;
           while( item )
           {
             if(item->repparent[0] == '\0')
               total = total + item->reptimer;
             item = (PACTDATA)item->next;
           }
           if( units == UNITS_MINUTES || units == UNITS_HOURS )
             sprintf( szTime, "%6.2f", total );
           else
             fnConvertTime( total, secunits, units, szTime );
           WinSetWindowText( WinWindowFromID(hwnd, IDS_REPTOTAL), szTime );
         }
         else
           mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
       }
       break;

     case WM_COMMAND:
        switch (SHORT1FROMMP(mp1))
           {
            case IDP_SAVE:
            case DID_OK:               /* User clicked on OK push button      */
               {                       /* Process options settings and place  */
                                       /* into appropriate variables          */
                  CHAR     outstring[MAXLENGTH], coutstring[MAXLENGTH];
                  CHAR     szJuldate[8],szDate[11];
                  ULONG    ulJuldate, i, month, day, year;
                  PACTDATA item;
                  PREPINFO repitem;
                  USHORT   answer;
                  BOOL     duplicate;

                  WinSendDlgItemMsg(hwnd, IDC_COUNT, SPBM_QUERYVALUE,
                                    &(selitem->repcount), MPFROM2SHORT(0L, 0L));

                  selitem->reptimer = fnTimeControl(hwnd, 0.0, 1);

                  WinSendDlgItemMsg(hwnd, IDC_MONTH, SPBM_QUERYVALUE,
                                    &month, MPFROM2SHORT(0L, 0L));
                  WinSendDlgItemMsg(hwnd, IDC_DAY, SPBM_QUERYVALUE,
                                    &day, MPFROM2SHORT(0L, 0L));
                  WinSendDlgItemMsg(hwnd, IDC_YEAR, SPBM_QUERYVALUE,
                                    &year, MPFROM2SHORT(0L, 0L));
                  ulJuldate = fnMakeDate(month, day, year, szJuldate, szDate);

                  WinQueryWindowText( WinWindowFromID( hwnd, IDE_COMMENTS ),
                                      sizeof( selitem->repcom ),
                                      selitem->repcom );

                  WinQueryWindowText( WinWindowFromID( hwnd, IDE_PARENT ),
                                      sizeof( selitem->repparent ),
                                      selitem->repparent );
                  fnStrip(selitem->repparent, selitem->repparent, 'B', ' '); /* 1.97 */
                  fnChangeParentReport( selitem->repparent, startdata );

                  duplicate = NO;
                  repitem = startrep;
                  while( repitem )
                  {
//                  if(strncmp(szDate,repitem->repdate,strlen(szDate)) == 0)
                    if(repitem->juldate == ulJuldate)  /* 1.98 */
                    {
                      duplicate = YES;
                      break;
                    }
                    repitem = (PREPINFO)repitem->next;
                  }

                  answer = MBID_YES;
                  if(duplicate == YES)
                  {
                    HAB hab;
                    hab = WinQueryAnchorBlock(hwnd);
                    WinLoadString(hab, 0L, IDS_CREATE, sizeof(szTitle),
                                  szTitle);
                    WinLoadString(hab, 0L, IDS_CREATEWARN, sizeof(szText),
                                  szText);

                    answer = WinMessageBox(HWND_DESKTOP, hwnd,
                                           szText, szTitle, 0,
                                           MB_ICONQUESTION | MB_YESNOCANCEL |
                                           MB_MOVEABLE);
                  }
                  if(answer == MBID_YES)
                  {
                    outstring[0] = '\0';
                    coutstring[0] = '\0';
                    fnDateInfo(outstring);

                    for( i=0; i<10; i++)
                      outstring[i] = szDate[i];
                    for( i=0; i<7; i++ )
                      outstring[i+11] = szJuldate[i];
                    strcat( outstring, "                    " );
                    strcpy(coutstring, outstring);
                    strcat(coutstring, " ");

                    total = 0.0;
                    item = startdata;
                    while( item )
                    {
                      sprintf( szText, " %-8s %3d %7.2f %-8s",
                               item->code, item->repcount, item->reptimer,
                               item->repparent);
                      strcat( outstring, szText );
                      if(item->repparent[0] == '\0')
                        total = total + item->reptimer;
                      sprintf( szText, "%-30s", item->repcom );
                      strcat( coutstring, szText );
                      item = (PACTDATA)item->next;
                    }
                    sprintf( szText, "%7.2f", total );
                    for( i=0; i<7; i++ )
                      outstring[i+19] = szText[i];

                    fnFreeReportList();
                    startrep = NULL;
                    lastrep  = NULL;
                    fnSaveReport( YES, ulJuldate, outstring, coutstring,
                                  szJuldate );

                    if(SHORT1FROMMP(mp1) == DID_OK)
                    {
                      fnFreeDataList(startdata);
                      WinDismissDlg (hwnd, TRUE);
                    }
                    else
                      fnResetList(hwnd, startdata);
                  }
                  else
                  {
                    if(answer == MBID_NO)
                    {
                      if(SHORT1FROMMP(mp1) == DID_OK)
                      {
                        fnFreeDataList(startdata);
                        WinDismissDlg (hwnd, FALSE);
                      }
                      else
                        fnResetList(hwnd, startdata);
                    }
                  }
               }                       /* end case (DID_OK)                   */
               break;

            case IDP_GETDATA:          /* User clicked on Get data push       */
               {                       /* button                              */
                  CHAR     szJuldate[8],szDate[11];
                  ULONG    ulJuldate, i, month, day, year;
                  PREPINFO repitem;
                  BOOL     found;

                  WinSendDlgItemMsg(hwnd, IDC_MONTH, SPBM_QUERYVALUE,
                                    &month, MPFROM2SHORT( 0L, 0L ));
                  WinSendDlgItemMsg(hwnd, IDC_DAY, SPBM_QUERYVALUE,
                                    &day, MPFROM2SHORT(0L,0L));
                  WinSendDlgItemMsg(hwnd, IDC_YEAR, SPBM_QUERYVALUE,
                                    &year, MPFROM2SHORT( 0L, 0L));
                  ulJuldate = fnMakeDate(month, day, year, szJuldate, szDate);

                  found = NO;
                  repitem = startrep;
                  while( repitem )
                  {
//                  if(strncmp(szDate,repitem->repdate,strlen(szDate)) == 0)
                    if(repitem->juldate == ulJuldate)
                    {
                      found = YES;
                      break;
                    }
                    repitem = (PREPINFO)repitem->next;
                  }

                  if(found == NO)
                  {
                    HAB hab;

                    hab = WinQueryAnchorBlock(hwnd);
                    WinLoadString(hab, 0L, IDS_GET, sizeof(szTitle), szTitle);
                    WinLoadString(hab, 0L, IDS_GETWARN, sizeof(szText), szText);

                    if(WinMessageBox(HWND_DESKTOP, hwnd, szText,
                                  szTitle, 0, MB_ICONQUESTION | MB_YESNO |
                                  MB_MOVEABLE) == MBID_YES)
                    {
                      fnFreeDataList(startdata);
                      startdata = NULL;
                      lastdata  = NULL;
                      selitem = fnInitRepData( 0, hwnd, &startdata, &lastdata,
                                               &total, NULL, NULL );
                      total = 0.0;
                      WinSendMsg(hwnd, WM_COMMAND, MPFROM2SHORT(IDP_SAVE,
                                 TRUE), 0L );
                    }
                    else
                      fnResetList(hwnd, startdata);
                  }
                  else
                  {
                    fnFreeDataList(startdata);
                    startdata = NULL;
                    lastdata  = NULL;
                    WinSendDlgItemMsg (hwnd, IDL_ACTIVITY, LM_DELETEALL,
                                       MPFROMSHORT(0), (MPARAM) NULL );
                    selitem = fnInitRepData(1, hwnd, &startdata, &lastdata,
                              &total, repitem->repdata, repitem->commentdata);
                  }
               }                       /* end case (IDP_GETDATA)              */
               break;

            case DID_CANCEL:           /* User clicked on Cancel push button  */
               fnFreeDataList(startdata);
               WinDismissDlg (hwnd, FALSE);
               break;

            default:                   /* Let PM handle rest of messages      */
               mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
               break;
           }
        break;

     default:                          /* Let PM handle rest of messages      */
        mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
        break;
    }

 return (mr);
}

/******************************************************************************/
/*                                                                            */
/* fnInitRepData:                                                             */
/*                                                                            */
/******************************************************************************/

PACTDATA fnInitRepData( BOOL type, HWND hwnd, PACTDATA *startdata,
                        PACTDATA *lastdata, float *total, CHAR *repdata,
                        CHAR *comdata )

{

  PACTINFO item;
  PACTDATA selitem;
  PACTDATA actdata;
  ULONG    i, max;
  CHAR     szTime[10];

  *startdata = NULL;
  *lastdata  = NULL;

  if(type == 0)
  {
    WinSendDlgItemMsg(hwnd, IDL_ACTIVITY, LM_DELETEALL,
                      MPFROMSHORT(0), (MPARAM)NULL);
    item = start;                      /* populate listbox with the list of   */
    while( item )                      /* of activity codes, reset report     */
    {                                  /* values to 0 as well                 */
      WinSendDlgItemMsg (hwnd, IDL_ACTIVITY, LM_INSERTITEM,
                         MPFROMLONG(LIT_END), MPFROMP ( item->code ));
      actdata = (PACTDATA) malloc(sizeof(ACTDATA));
      strcpy(actdata->code, item->code);
      actdata->reptimer = 0.0;
      actdata->repcount = 0;
      actdata->repcom[0] = '\0';
      strcpy(actdata->repparent, item->parent);
      fnStrip(actdata->repparent, actdata->repparent, 'B', ' ');  /* 1.98 */
//    actdata->repparent[0] = '\0';
      fnPutDataList(actdata, &(*startdata), &(*lastdata));
      item = (PACTINFO)item->next;
    }
    *total = 0.0;
  }
  else
  {
    *total = 0.0;
    i = 1;
    max = strlen(repdata) + 1;
    while( 1 )
    {
      if( i > max )
        break;

      actdata = (PACTDATA) malloc(sizeof(ACTDATA));

      fnSubstr( repdata, actdata->code, i, CODE_WIDTH );
      WinSendDlgItemMsg (hwnd, IDL_ACTIVITY, LM_INSERTITEM,
                         MPFROMLONG(LIT_END), MPFROMP ( actdata->code ));
      fnSubstr( repdata, szText, i+9, 3 );
      actdata->repcount = atol( szText );
      fnSubstr( repdata, szText, i+13, 7 );
      actdata->reptimer = atof( szText );
      fnSubstr( comdata, actdata->repcom, i, 30 );
      fnSubstr( repdata, actdata->repparent, i+21, CODE_WIDTH );
      fnStrip(actdata->repparent, actdata->repparent, 'B', ' ');

      if(actdata->repparent[0] == '\0')
        *total = *total + actdata->reptimer;

      fnPutDataList(actdata, &(*startdata), &(*lastdata));

      i = i + 30;
    }
  }

  selitem = *startdata;
  if( units == UNITS_MINUTES || units == UNITS_HOURS )
    sprintf( szTime, "%6.2f", *total );
  else
    fnConvertTime( *total, secunits, units, szTime );
  WinSetWindowText( WinWindowFromID( hwnd, IDS_REPTOTAL ), szTime);
  WinSendDlgItemMsg (hwnd, IDL_ACTIVITY, LM_SELECTITEM,
                     MPFROMLONG(0), MPFROMSHORT (TRUE));
  fnTimeControl(hwnd, selitem->reptimer, 0);
  WinSetWindowText( WinWindowFromID( hwnd, IDS_CODE ), selitem->code);
  WinSendDlgItemMsg( hwnd, IDC_COUNT, SPBM_SETCURRENTVALUE,
                     MPFROMSHORT(selitem->repcount), 0L );
  WinSetWindowText(WinWindowFromID(hwnd, IDE_COMMENTS), selitem->repcom);
  WinSetWindowText(WinWindowFromID(hwnd, IDE_PARENT), selitem->repparent);

  return( selitem );
}

/******************************************************************************/
/*                                                                            */
/*                                                                            */
/******************************************************************************/

VOID fnPutDataList( PACTDATA item, PACTDATA *startdata, PACTDATA *lastdata )
{

  if( *lastdata == NULL )
  {
    *lastdata    = item;
    *startdata   = item;
    item->prior = NULL;
  }
  else
  {
    (*lastdata)->next = (PACTDATA)item;
    item->prior       = (PACTDATA)*lastdata;
  }
  item->next = NULL;
  *lastdata  = item;

}

VOID fnFreeDataList( PACTDATA startdata )
{

  PACTDATA item;
  PACTDATA temp;

  item = startdata;
  while( item )
  {
    temp = (PACTDATA)item->next;
    free( item );
    item = temp;
  }

}

VOID fnResetList( HWND hwnd, PACTDATA startdata )
{

  PACTDATA item;
  float    zero = 0.0;
  CHAR     szTime[10];

  item = startdata;
  while( item )
  {
    item->reptimer = 0.0;
    item->repcount = 0;
    item = (PACTDATA)item->next;
  }

  fnTimeControl(hwnd, zero, 0);
  if( units == UNITS_MINUTES || units == UNITS_HOURS )
    sprintf( szTime, "%6.2f", 0.0 );
  else
    fnConvertTime( 0.0, secunits, units, szTime );
  WinSetWindowText( WinWindowFromID( hwnd, IDS_REPTOTAL ), szTime);
  WinSendDlgItemMsg( hwnd, IDC_COUNT, SPBM_SETCURRENTVALUE,
                     MPFROMSHORT(0), 0L );

}

/******************************************************************************/
/*                                                                            */
/* fnCreateNotebook: Create Settings window (as a notebook).                  */
/*                                                                            */
/******************************************************************************/

BOOL fnCreateNotebook( HAB hab, HWND hwnd )
{

  HWND     hwndNBFrame;                /* Notebook window handle           */
  HWND     hwndNBClient;               /* Notebook client window           */
  ULONG    flFrameFlags;               /* Window creation flags            */

  WinLoadString (hab, 0L, IDS_SETTINGS, 50, szTitle);

  flFrameFlags = FCF_TITLEBAR   | FCF_SYSMENU | FCF_MINMAX |
                 FCF_SIZEBORDER | FCF_SHELLPOSITION;

  hwndNBFrame = WinCreateStdWindow(HWND_DESKTOP, WS_SAVEBITS,
                                   &flFrameFlags, NULL, szTitle,
                                   0L, 0L, ID_NBWINDOW, &hwndNBClient);

  if (hwndNBFrame)
    {
      RECTL rectlDesktop;              /* rectangle structure                 */
      SWP   swp;                       /* set window position structure       */
      ULONG ulSize;                    /* size of SWP structure               */
      LONG  x, y, cx, cy;              /* window position coordinates and size*/
      BOOL  windowSize;

      hwndNBClient = WinCreateWindow(hwndNBFrame, szNotebookClass, NULL, 0L,
                      0, 0, 0, 0, hwndNBFrame, HWND_TOP, FID_CLIENT,
                      NULL, NULL);
      if (hwndHelp)                    /* Associate help instance             */
        WinAssociateHelpInstance(hwndHelp, hwndNBFrame);

      windowSize = TRUE;               /* Position NB window and show it      */
      ulSize = sizeof (SWP);
      if( PrfQueryProfileData( hini, szAppName, szSetWinPos, &swp, &ulSize ) )
      {
        x = swp.x;                     /* ok, got it, set coordinates and     */
        y = swp.y;                     /* window size                         */
        cx = swp.cx;
        cy = swp.cy;
        if( x >= 0 || y >= 0 )
          windowSize = FALSE;
      }
      if( windowSize == TRUE )         /* no profile data, use system default */
      {                                /* window size and position            */
        WinQueryWindowRect (HWND_DESKTOP, &rectlDesktop);
        x = rectlDesktop.xRight / 5;
        y = rectlDesktop.yTop / 5;
        cx = rectlDesktop.xRight * 2 / 3;
        cy = rectlDesktop.yTop * 2 / 3;
      }

      WinSetWindowPos (hwndNBFrame, HWND_TOP, x, y, cx, cy,
                  SWP_SHOW | SWP_SIZE | SWP_MOVE | SWP_ACTIVATE);
      WinShowWindow(hwndNBFrame, TRUE);
      WinSetFocus(HWND_DESKTOP, hwndNBFrame);
    }

  return TRUE;
}                                         /* End of CreateNotebook function*/

/******************************************************************************/
/*                                                                            */
/* wpNBWndProc: Window procedure the Settings notebook window.                */
/*                                                                            */
/******************************************************************************/

MRESULT wpNBWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  MRESULT  mResult = FALSE;            /* Function result parameter        */
  HWND     hwndNb;                     /* Notebook control window handle   */
  ULONG    ulPageID;                   /* Notebook page ID number          */
  HWND     hwndPage;                   /* Notebook page window handle      */
  static   HWND hwndNBPage[7];
  static   BOOL  oldsecunits, oldunits, oldshowexclude, oldshowhidden,
                 oldhidetotal;
  static   ULONG oldrefreshtime, oldalarmtime, oldrepsave;
  static   CHAR oldmenutext[MENU_WIDTH], oldprogram[PROG_WIDTH];

  switch (msg)
    {
      case WM_CREATE:                  /* Window initialisation*/
        {
          FONTMETRICS fm;              /* Font metric information          */
          HPS      hps;                /* Presentation space handle        */
          LONG     lCharHeight;        /* Character height                 */
          LONG     lCharWidth;         /* Character width                  */
          HAB      hab;
          USHORT   usAttr;             /* Notebook page attributes         */

          oldsecunits    = secunits;
          oldunits       = units;
          oldshowexclude = showexclude;
          oldshowhidden  = showhidden;
          oldrefreshtime = refreshtime;
          oldalarmtime   = alarmtime;
          oldrepsave     = repsave;
          /* oldhidetotal   = hidetotal; */  /* 1.98 */
          strcpy( oldmenutext, menutext );
          strcpy( oldprogram, program );

          WinEnableMenuItem(WinWindowFromID(WinQueryWindow(hwndClient,
                            QW_PARENT), FID_MENU), IDM_SETTINGS, FALSE);

          hab = WinQueryAnchorBlock( hwnd );

          hwndNb = WinCreateWindow(hwnd, WC_NOTEBOOK, "",
                                   WS_VISIBLE | BKS_MAJORTABRIGHT |
                                   BKS_BACKPAGESBR | BKS_SQUARETABS,
                                   0, 0, 0, 0, hwnd, HWND_TOP, ID_NBSETTINGS,
                                   0L, 0L);

          hps = (HPS)WinGetPS(hwndNb); /* Get system font information      */
          GpiQueryFontMetrics(hps, (LONG)sizeof(FONTMETRICS), &fm);
          WinReleasePS(hps);
          lCharHeight = fm.lMaxBaselineExt + 7;
          lCharWidth  = (fm.lAveCharWidth + 4) * 10;

          WinSendMsg(hwndNb, BKM_SETDIMENSIONS,
                     MPFROM2SHORT(lCharWidth, lCharHeight),
                     MPFROMSHORT(BKA_MAJORTAB));
          WinSendMsg(hwndNb, BKM_SETDIMENSIONS,
                     MPFROM2SHORT(0, 0),
                     MPFROMSHORT(BKA_MINORTAB));
          WinSendMsg(hwndNb, BKM_SETNOTEBOOKCOLORS,
                     MPFROMLONG(SYSCLR_DIALOGBACKGROUND),
                     MPFROMLONG(BKA_BACKGROUNDPAGECOLORINDEX));
          WinSendMsg(hwndNb, BKM_SETNOTEBOOKCOLORS,
                     MPFROMLONG(SYSCLR_DIALOGBACKGROUND),
                     MPFROMLONG(BKA_BACKGROUNDMAJORCOLORINDEX));

          usAttr = BKA_MAJOR | BKA_STATUSTEXTON | BKA_AUTOPAGESIZE;

          WinLoadString (hab, 0L, IDS_OPTIONS, 50, szTitle);
          ulPageID = (ULONG)WinSendMsg(hwndNb, BKM_INSERTPAGE, NULL,
                            MPFROM2SHORT(usAttr, BKA_LAST));
          WinSendMsg(hwndNb, BKM_SETTABTEXT,
                     MPFROMLONG(ulPageID), MPFROMP(szTitle));
          hwndPage = WinLoadDlg(hwndNb, hwndNb, wpOptionsDlgProc,
                                0L, IDD_OPTIONS, NULL);
          WinSendMsg(hwndNb, BKM_SETPAGEWINDOWHWND, MPFROMLONG(ulPageID),
                     MPFROMHWND(hwndPage));
          hwndNBPage[0] = hwndPage;

          WinLoadString (hab, 0L, IDS_CONFIRM, 50, szTitle);
          ulPageID = (ULONG)WinSendMsg(hwndNb, BKM_INSERTPAGE, NULL,
                            MPFROM2SHORT(usAttr, BKA_LAST));
          WinSendMsg(hwndNb, BKM_SETTABTEXT,
                     MPFROMLONG(ulPageID), MPFROMP(szTitle));
          hwndPage = WinLoadDlg(hwndNb, hwndNb, wpConfirmDlgProc,
                                0L, IDD_CONFIRM, NULL);
          WinSendMsg(hwndNb, BKM_SETPAGEWINDOWHWND, MPFROMLONG(ulPageID),
                     MPFROMHWND(hwndPage));
          hwndNBPage[1] = hwndPage;

          WinLoadString (hab, 0L, IDS_TIME, 50, szTitle);
          ulPageID = (ULONG)WinSendMsg(hwndNb, BKM_INSERTPAGE, NULL,
                            MPFROM2SHORT(usAttr, BKA_LAST));
          WinSendMsg(hwndNb, BKM_SETTABTEXT,
                     MPFROMLONG(ulPageID), MPFROMP(szTitle));
          hwndPage = WinLoadDlg(hwndNb, hwndNb, wpTimeDlgProc,
                                0L, IDD_TIME, NULL);
          WinSendMsg(hwndNb, BKM_SETPAGEWINDOWHWND, MPFROMLONG(ulPageID),
                     MPFROMHWND(hwndPage));
          hwndNBPage[2] = hwndPage;

          WinLoadString (hab, 0L, IDS_DATE, 50, szTitle);
          ulPageID = (ULONG)WinSendMsg(hwndNb, BKM_INSERTPAGE, NULL,
                            MPFROM2SHORT(usAttr, BKA_LAST));
          WinSendMsg(hwndNb, BKM_SETTABTEXT,
                     MPFROMLONG(ulPageID), MPFROMP(szTitle));
          hwndPage = WinLoadDlg(hwndNb, hwndNb, wpDateDlgProc,
                                0L, IDD_DATE, NULL);
          WinSendMsg(hwndNb, BKM_SETPAGEWINDOWHWND, MPFROMLONG(ulPageID),
                     MPFROMHWND(hwndPage));
          hwndNBPage[3] = hwndPage;

          WinLoadString (hab, 0L, IDS_REPORT, 50, szTitle);
          ulPageID = (ULONG)WinSendMsg(hwndNb, BKM_INSERTPAGE, NULL,
                            MPFROM2SHORT(usAttr, BKA_LAST));
          WinSendMsg(hwndNb, BKM_SETTABTEXT,
                     MPFROMLONG(ulPageID), MPFROMP(szTitle));
          hwndPage = WinLoadDlg(hwndNb, hwndNb, wpRepSetDlgProc,
                                0L, IDD_REPSET, NULL);
          WinSendMsg(hwndNb, BKM_SETPAGEWINDOWHWND, MPFROMLONG(ulPageID),
                     MPFROMHWND(hwndPage));
          hwndNBPage[4] = hwndPage;

          WinLoadString (hab, 0L, IDS_ALARMSET, 50, szTitle);
          ulPageID = (ULONG)WinSendMsg(hwndNb, BKM_INSERTPAGE, NULL,
                            MPFROM2SHORT(usAttr, BKA_LAST));
          WinSendMsg(hwndNb, BKM_SETTABTEXT,
                     MPFROMLONG(ulPageID), MPFROMP(szTitle));
          hwndPage = WinLoadDlg(hwndNb, hwndNb, wpAlarmDlgProc,
                                0L, IDD_ALARM, NULL);
          WinSendMsg(hwndNb, BKM_SETPAGEWINDOWHWND, MPFROMLONG(ulPageID),
                     MPFROMHWND(hwndPage));
          hwndNBPage[5] = hwndPage;

          WinLoadString (hab, 0L, IDS_USEREXIT, 50, szTitle);
          ulPageID = (ULONG)WinSendMsg(hwndNb, BKM_INSERTPAGE, NULL,
                            MPFROM2SHORT(usAttr, BKA_LAST));
          WinSendMsg(hwndNb, BKM_SETTABTEXT,
                     MPFROMLONG(ulPageID), MPFROMP(szTitle));
          hwndPage = WinLoadDlg(hwndNb, hwndNb, wpUserExitDlgProc,
                                0L, IDD_USEREXIT, NULL);
          WinSendMsg(hwndNb, BKM_SETPAGEWINDOWHWND, MPFROMLONG(ulPageID),
                     MPFROMHWND(hwndPage));
          hwndNBPage[6] = hwndPage;

          WinShowWindow(hwndNb, TRUE);
          WinPostMsg(hwnd, UM_CREATENB, 0L, 0L);
        }
        break;

      case UM_CREATENB:
        WinSendMsg(hwndNBPage[0], UM_SELECT, 0L, 0L);
        break;

      case WM_CLOSE:                      /* Don't close the parent window!*/
        {
          ULONG i;
          for( i=0; i<7; i++)
            WinSendMsg(hwndNBPage[i], WM_COMMAND, MPFROMSHORT(DID_OK), 0L);

          if( refreshtime != oldrefreshtime )
            WinSendMsg(hwndClient, UM_SETREFRESH, 0L, 0L);
          if( alarmtime != oldalarmtime )
            WinSendMsg(hwndClient, UM_SETALARM, 0L, 0L);
          if( secunits != oldsecunits )
          {
             PACTINFO item;

             DosRequestMutexSem( hmtxNB, SEM_INDEFINITE_WAIT );

             item = start;
             while( item )
             {
               item->timer = item->timer * (float)oldsecunits /
                                           (float)secunits;
               item = (PACTINFO)item->next;
             }

             DosReleaseMutexSem( hmtxNB );
          }
          if( showexclude != oldshowexclude || showhidden != oldshowhidden ||
//            units != oldunits || hidetotal != oldhidetotal )
              units != oldunits )  /* 1.98 */
            WinSendMsg(hwndClient, UM_SETSHOW, 0L, 0L);
          if( repsave != oldrepsave )
            WinSendMsg(hwndClient, UM_SETREP, 0L, 0L);
          if( strcmp( menutext, oldmenutext ) != 0 ||
              strcmp( program, oldprogram ) != 0 )
            WinSendMsg(hwndClient, UM_SETEXIT, 0L, 0L);

          WinEnableMenuItem(WinWindowFromID(WinQueryWindow(hwndClient,
                            QW_PARENT), FID_MENU), IDM_SETTINGS, TRUE);

          WinDestroyWindow(WinQueryWindow(hwnd, QW_PARENT));
        }
        break;

      case WM_SAVEAPPLICATION:                      /* Save window position*/
        {
          SWP swp;

          WinQueryWindowPos (WinQueryWindow (hwnd, QW_PARENT), &swp);
          PrfWriteProfileData(hini, szAppName, szSetWinPos,
                              &swp, sizeof (SWP));
        }
        break;

      case WM_SIZE:                     /* Make sure notebook fills the window*/
        hwndNb = WinWindowFromID(hwnd, ID_NBSETTINGS);
        WinSetWindowPos(hwndNb, HWND_TOP, 0, 0,
                        SHORT1FROMMP(mp2), SHORT2FROMMP(mp2),
                        SWP_SIZE | SWP_MOVE);
        break;

      case WM_CONTROL:
        if ((SHORT1FROMMP(mp1) == ID_NBSETTINGS)
         && (SHORT2FROMMP(mp1) == BKN_PAGESELECTED))
          {                       /* Tell old page to save possible changes*/
            PPAGESELECTNOTIFY pPsn;

            pPsn = (PPAGESELECTNOTIFY)mp2;
            hwndPage = (HWND)WinSendMsg(pPsn->hwndBook,
                                        BKM_QUERYPAGEWINDOWHWND,
                                        MPFROMLONG(pPsn->ulPageIdNew), 0L);
            WinSendMsg(hwndPage, UM_SELECT, 0L, 0L);
          };                                                      /* End if*/
        break;

      default:
        mResult = WinDefWindowProc(hwnd, msg, mp1, mp2);
        break;
    }                                                         /* End switch*/

  return mResult;
}                                            /* End of NotebookWnd function*/

/******************************************************************************/
/* wpOptionsDlgProc: Window procedure for Options dialog box.                 */
/******************************************************************************/

MRESULT EXPENTRY wpOptionsDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)

{

 MRESULT mr = (MRESULT) FALSE;
 static BOOL  oldinitreset, oldshowexclude, oldshowhidden, oldrefreshsave,
              oldminimize, oldblankcom, oldhidetotal, oldgomain,
              oldnofocuschg, oldsubactwin;
 static ULONG oldrefreshtime, oldsmallwin;
 static UCHAR oldstartitem[40];

 switch (msg)
    {
     case WM_INITDLG:                  /* dialog initialization routine       */
       {
         oldinitreset   = initreset;
         oldshowexclude = showexclude;
         oldshowhidden  = showhidden;
         oldrefreshtime = refreshtime;
         oldrefreshsave = refreshsave;
         oldminimize    = minimize;
         oldsmallwin    = xsmlwin;
         oldblankcom    = blankcom;
         /* oldhidetotal   = hidetotal; */   /* 1.98 */
         oldgomain      = gomain;
         oldnofocuschg  = nofocuschg;
         oldsubactwin   = subactwin;
         strcpy( oldstartitem, startitem );

         fnActivityList(hwnd, NULL, szBlank, IDC_STARTITEM, TRUE,
                        TRUE, TYPE_NORMAL);
         fnOptionsDlgInit( hwnd );
       }
       break;                          /* end case (WM_INITDLG)               */

     case UM_SELECT:
       WinSetFocus (HWND_DESKTOP, WinWindowFromID (hwnd, IDC_STARTITEM));
       break;

     case WM_COMMAND:
        switch (SHORT1FROMMP(mp1))
           {
            case DID_OK:
              {
                SHORT    i, j;
                PACTINFO item;

                j = (SHORT)WinSendDlgItemMsg(hwnd, IDC_STARTITEM,
                                             LM_QUERYSELECTION, 0L, 0L);
                if( j == 0 || j == LIT_NONE )
                {
                  startitem[0] = '\0';
                  fnPadString(startitem, 2*CODE_WIDTH+1);
                }
                else
                {
                  item = start;
                  for( i = 1; i < j; i++ )
                    item = (PACTINFO)item->next;
                  strcpy(startitem, item->code);
                  strcat(startitem, " ");
                  strcat(startitem, item->parent);
                }

                initreset   = (BOOL) WinSendDlgItemMsg( hwnd, IDC_INITRESET,
                                     BM_QUERYCHECK, 0L, 0L );
                showexclude = (BOOL) WinSendDlgItemMsg( hwnd, IDC_EXCLUDEALL,
                                     BM_QUERYCHECK, 0L, 0L );
                showhidden  = (BOOL) WinSendDlgItemMsg( hwnd, IDC_HIDE,
                                     BM_QUERYCHECK, 0L, 0L );

                WinSendDlgItemMsg( hwnd, IDC_REFRESH, SPBM_QUERYVALUE,
                                   &refreshtime, MPFROM2SHORT( 0L, 0L));

                refreshsave = (BOOL) WinSendDlgItemMsg( hwnd, IDC_REFRESHSAVE,
                                     BM_QUERYCHECK, 0L, 0L );

                minimize    = (BOOL) WinSendDlgItemMsg( hwnd, IDC_MINIMIZE,
                                     BM_QUERYCHECK, 0L, 0L );

                blankcom    = (BOOL) WinSendDlgItemMsg( hwnd, IDC_BLANKCOM,
                                     BM_QUERYCHECK, 0L, 0L );

                // 1.98
                //hidetotal   = (BOOL) WinSendDlgItemMsg( hwnd, IDC_HIDETOTAL,
                //                     BM_QUERYCHECK, 0L, 0L );

                gomain      = (BOOL) WinSendDlgItemMsg( hwnd, IDC_GOMAIN,
                                     BM_QUERYCHECK, 0L, 0L );

                nofocuschg  = (BOOL) WinSendDlgItemMsg( hwnd, IDC_NOFOCUS,
                                     BM_QUERYCHECK, 0L, 0L );

                subactwin   = (BOOL) WinSendDlgItemMsg( hwnd, IDC_SUBACTWIN,
                                     BM_QUERYCHECK, 0L, 0L );

                if(WinSendDlgItemMsg( hwnd, IDC_SMALLWIN, BM_QUERYCHECK,
                   0L, 0L ))
                  xsmlwin = SMALL_WINDOW;
                else
                  xsmlwin = NORMAL_WINDOW;

                WinDismissDlg (hwnd, TRUE);
                mr = (MRESULT) TRUE;
              }
              break;

            case DID_CANCEL:           /* User clicked on Undo push button    */
              initreset   = oldinitreset;
              showexclude = oldshowexclude;
              showhidden  = oldshowhidden;
              refreshtime = oldrefreshtime;
              refreshsave = oldrefreshsave;
              minimize    = oldminimize;
              xsmlwin     = oldsmallwin;
              blankcom    = oldblankcom;
              /* hidetotal   = oldhidetotal; */  /* 1.98 */
              gomain      = oldgomain;
              nofocuschg  = oldnofocuschg;
              subactwin   = oldsubactwin;
              strcpy( startitem, oldstartitem );
              fnOptionsDlgInit( hwnd );
              break;

            case IDP_DEFAULT:
              fnInitialize( IDD_OPTIONS );
              fnOptionsDlgInit( hwnd );
              break;

            default:                   /* Let PM handle rest of messages      */
              mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
              break;
           }
        break;

     default:                          /* Let PM handle rest of messages      */
        mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
        break;
    }

 return (mr);

}

/******************************************************************************/
/* fnOptionsDlgInit: Initialization for Options dialog box.                   */
/******************************************************************************/

VOID fnOptionsDlgInit( HWND hwnd )

{

  SHORT    i;
  PACTINFO item;

  if( startitem[0] == ' ' )
    WinSendDlgItemMsg (hwnd, IDC_STARTITEM, LM_SELECTITEM,
                       MPFROMLONG (0), MPFROMSHORT (TRUE));
  else
  {
    CHAR activity[CODE_WIDTH+1];
    CHAR parent[CODE_WIDTH+1];

    fnSubstr(startitem, activity, 1, CODE_WIDTH);
    fnSubstr(startitem, parent, CODE_WIDTH+2, CODE_WIDTH);

    i = 1;                             /*                                     */
    item = start;                      /*                                     */
    while( item )                      /*                                     */
    {                                  /*                                     */
      if(strcmp(item->code, activity)==0 &&
         strcmp(item->parent, parent)==0)
        WinSendDlgItemMsg (hwnd, IDC_STARTITEM, LM_SELECTITEM,
                           MPFROMLONG (i), MPFROMSHORT (TRUE));
      i++;
      item = (PACTINFO)item->next;
    }
  }

  if( initreset == YES )
    WinSendDlgItemMsg (hwnd, IDC_INITRESET, BM_SETCHECK,
                       MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_INITRESET, BM_SETCHECK,
                       MPFROMSHORT (FALSE), 0L);

  if( showexclude == YES )
    WinSendDlgItemMsg (hwnd, IDC_EXCLUDEALL, BM_SETCHECK,
                       MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_EXCLUDEALL, BM_SETCHECK,
                       MPFROMSHORT (FALSE), 0L);

  if( showhidden == YES )
    WinSendDlgItemMsg (hwnd, IDC_HIDE, BM_SETCHECK, MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_HIDE, BM_SETCHECK, MPFROMSHORT (FALSE), 0L);

  WinSendDlgItemMsg( hwnd, IDC_REFRESH, SPBM_SETLIMITS,
                     MPFROMSHORT(1440), MPFROMSHORT(0) );
  WinSendDlgItemMsg( hwnd, IDC_REFRESH, SPBM_SETCURRENTVALUE,
                     MPFROMSHORT(refreshtime), 0L );
  WinSendDlgItemMsg( hwnd, IDC_REFRESH, SPBM_SETTEXTLIMIT,
                     MPFROMSHORT(4L), 0L );

  if( refreshsave == YES )
    WinSendDlgItemMsg (hwnd, IDC_REFRESHSAVE, BM_SETCHECK,
    MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_REFRESHSAVE, BM_SETCHECK,
    MPFROMSHORT (FALSE), 0L);

  if( minimize == YES )
    WinSendDlgItemMsg (hwnd, IDC_MINIMIZE, BM_SETCHECK,
                       MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_MINIMIZE, BM_SETCHECK,
                       MPFROMSHORT (FALSE), 0L);

  if( xsmlwin == SMALL_WINDOW )
    WinSendDlgItemMsg (hwnd, IDC_SMALLWIN, BM_SETCHECK,
                       MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_SMALLWIN, BM_SETCHECK,
                       MPFROMSHORT (FALSE), 0L);

  if( blankcom == YES )
    WinSendDlgItemMsg (hwnd, IDC_BLANKCOM, BM_SETCHECK,
                       MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_BLANKCOM, BM_SETCHECK,
                       MPFROMSHORT (FALSE), 0L);

/* 1.98 */
//if( hidetotal == YES )
//  WinSendDlgItemMsg (hwnd, IDC_HIDETOTAL, BM_SETCHECK,
//                     MPFROMSHORT (TRUE), 0L);
//else
//  WinSendDlgItemMsg (hwnd, IDC_HIDETOTAL, BM_SETCHECK,
//                     MPFROMSHORT (FALSE), 0L);

  if( gomain == YES )
    WinSendDlgItemMsg (hwnd, IDC_GOMAIN, BM_SETCHECK,
                       MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_GOMAIN, BM_SETCHECK,
                       MPFROMSHORT (FALSE), 0L);

  if( nofocuschg == YES )
    WinSendDlgItemMsg (hwnd, IDC_NOFOCUS, BM_SETCHECK,
                       MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_NOFOCUS, BM_SETCHECK,
                       MPFROMSHORT (FALSE), 0L);

  if( subactwin == YES )
    WinSendDlgItemMsg (hwnd, IDC_SUBACTWIN, BM_SETCHECK,
                       MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_SUBACTWIN, BM_SETCHECK,
                       MPFROMSHORT (FALSE), 0L);

}

/******************************************************************************/
/* wpConfirmDlgProc: Window procedure for Confirmations dialog box.           */
/******************************************************************************/

MRESULT EXPENTRY wpConfirmDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)

{

 MRESULT mr = (MRESULT) FALSE;
 static BOOL  oldshowexit, oldshowreset, oldshowdelete, oldshowresetnew;

 switch (msg)
    {
     case WM_INITDLG:                  /* dialog initialization routine       */
       oldshowexit     = showexit;     /* save old values in case user changes*/
       oldshowreset    = showreset;    /* and then clicks on Cancel, we need  */
       oldshowdelete   = showdelete;
       oldshowresetnew = showresetnew;
       fnConfirmDlgInit( hwnd );
       break;                          /* end case (WM_INITDLG)               */

     case UM_SELECT:
       WinSetFocus (HWND_DESKTOP, WinWindowFromID (hwnd, IDC_EXIT));
       break;

     case WM_COMMAND:
        switch (SHORT1FROMMP(mp1))
           {
            case DID_OK:               /* User clicked on OK push button      */
               showexit     = (BOOL) WinSendDlgItemMsg( hwnd, IDC_EXIT,
                                     BM_QUERYCHECK, 0L, 0L );
               showdelete   = (BOOL) WinSendDlgItemMsg( hwnd, IDC_DELETE,
                                     BM_QUERYCHECK, 0L, 0L );
               showreset    = (BOOL) WinSendDlgItemMsg( hwnd, IDC_RESET,
                                     BM_QUERYCHECK, 0L, 0L );
               showresetnew = (BOOL) WinSendDlgItemMsg( hwnd, IDC_RESETNEW,
                                     BM_QUERYCHECK, 0L, 0L );
               WinDismissDlg (hwnd, TRUE);        /* remove the dialog box  */
               mr = (MRESULT) TRUE;
               break;

            case DID_CANCEL:           /* User clicked on Cancel push button  */
               showexit     = oldshowexit;
               showdelete   = oldshowdelete;
               showreset    = oldshowreset;
               showresetnew = oldshowresetnew;
               fnConfirmDlgInit( hwnd );
               break;

            case IDP_DEFAULT:
               fnInitialize( IDD_CONFIRM );
               fnConfirmDlgInit( hwnd );
               break;

            default:                   /* Let PM handle rest of messages      */
               mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
               break;
           }
        break;

     default:                          /* Let PM handle rest of messages      */
        mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
        break;
    }

 return (mr);

}

/******************************************************************************/
/* fnConfirmDlgInit: Initialization for Confirmations dialog box.             */
/******************************************************************************/

VOID fnConfirmDlgInit( HWND hwnd )

{

  if( showexit == YES )
    WinSendDlgItemMsg (hwnd, IDC_EXIT, BM_SETCHECK, MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_EXIT, BM_SETCHECK, MPFROMSHORT (FALSE), 0L);

  if( showdelete == YES )
    WinSendDlgItemMsg (hwnd, IDC_DELETE, BM_SETCHECK, MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_DELETE, BM_SETCHECK, MPFROMSHORT (FALSE), 0L);

  if( showreset == YES )
    WinSendDlgItemMsg (hwnd, IDC_RESET, BM_SETCHECK, MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_RESET, BM_SETCHECK, MPFROMSHORT (FALSE), 0L);

  if( showresetnew == YES )
    WinSendDlgItemMsg (hwnd, IDC_RESETNEW, BM_SETCHECK, MPFROMSHORT(TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_RESETNEW, BM_SETCHECK, MPFROMSHORT(FALSE), 0L);
}

/******************************************************************************/
/* wpTimeDlgProc: Window procedure for Time dialog box.                       */
/******************************************************************************/

MRESULT EXPENTRY wpTimeDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)

{

 MRESULT mr = (MRESULT) FALSE;
 static ULONG oldunits;

 switch (msg)
    {
     case WM_INITDLG:                  /* dialog initialization routine       */
       oldunits = units;
       fnTimeDlgInit( hwnd );
       break;                          /* end case (WM_INITDLG)               */

     case UM_SELECT:
       switch( units )
       {
         case( UNITS_MINUTES ):
           WinSetFocus (HWND_DESKTOP, WinWindowFromID (hwnd, IDB_MINUTES));
           break;
         case( UNITS_HOURS ):
           WinSetFocus (HWND_DESKTOP, WinWindowFromID (hwnd, IDB_HOURS));
           break;
/* 1.98 */
#if 0
         case( UNITS_TIME_D ):
           WinSetFocus (HWND_DESKTOP, WinWindowFromID (hwnd, IDB_DOTS));
           break;
         case( UNITS_TIME_C ):
           WinSetFocus (HWND_DESKTOP, WinWindowFromID (hwnd, IDB_COLON));
           break;
#endif
         case( UNITS_HMS ):
           WinSetFocus (HWND_DESKTOP, WinWindowFromID (hwnd, IDB_HMS));
           break;
         case( UNITS_HM ):
           WinSetFocus (HWND_DESKTOP, WinWindowFromID (hwnd, IDB_HM));
           break;
         default:
           break;
       }
       break;

     case WM_COMMAND:
        switch (SHORT1FROMMP(mp1))
           {
            case DID_OK:               /* User clicked on OK push button      */
               if( (BOOL) WinSendDlgItemMsg( hwnd, IDB_MINUTES,
                          BM_QUERYCHECK, 0L, 0L ) == 1 )
                 units = UNITS_MINUTES;
               else
               {
                 if( (BOOL) WinSendDlgItemMsg( hwnd, IDB_HOURS,
                            BM_QUERYCHECK, 0L, 0L ) == 1 )
                   units = UNITS_HOURS;
                 else
                 {
/* 1.98 */
#if 0
                   if( (BOOL) WinSendDlgItemMsg( hwnd, IDB_DOTS,
                              BM_QUERYCHECK, 0L, 0L ) == 1 )
                     units = UNITS_TIME_D;
                   else
                     units = UNITS_TIME_C;
#endif
                   if( (BOOL) WinSendDlgItemMsg( hwnd, IDB_HMS,
                              BM_QUERYCHECK, 0L, 0L ) == 1 )
                     units = UNITS_HMS;
                   else
                     units = UNITS_HM;
                 }
               }
               if( units == UNITS_HOURS )
                 secunits = units;
               else
                 secunits = UNITS_MINUTES;

               WinDismissDlg (hwnd, TRUE);        /* remove the dialog box  */
               mr = (MRESULT) TRUE;
               break;

            case DID_CANCEL:           /* User clicked on Cancel push button  */
               units       = oldunits;
               fnTimeDlgInit( hwnd );
               break;

            case IDP_DEFAULT:
               fnInitialize( IDD_TIME );
               fnTimeDlgInit( hwnd );
               break;

            default:                   /* Let PM handle rest of messages      */
               mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
               break;
           }
        break;

     default:                          /* Let PM handle rest of messages      */
        mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
        break;
    }

 return (mr);

}

/******************************************************************************/
/* fnTimeDlgInit: Initialization for Time dialog box.                         */
/******************************************************************************/

VOID fnTimeDlgInit( HWND hwnd )

{

  switch( units )
  {
    case( UNITS_MINUTES ):
      WinSendDlgItemMsg (hwnd, IDB_MINUTES, BM_SETCHECK,
                         MPFROMSHORT (TRUE), 0L);
      break;
    case( UNITS_HOURS ):
      WinSendDlgItemMsg (hwnd, IDB_HOURS, BM_SETCHECK,
                         MPFROMSHORT (TRUE), 0L);
      break;
/* 1.98 */
#if 0
    case( UNITS_TIME_D ):
      WinSendDlgItemMsg (hwnd, IDB_DOTS, BM_SETCHECK,
                         MPFROMSHORT (TRUE), 0L);
      break;
    case( UNITS_TIME_C ):
      WinSendDlgItemMsg (hwnd, IDB_COLON, BM_SETCHECK,
                         MPFROMSHORT (TRUE), 0L);
#endif
    case( UNITS_HMS ):
      WinSendDlgItemMsg (hwnd, IDB_HMS, BM_SETCHECK,
                         MPFROMSHORT (TRUE), 0L);
      break;
    case( UNITS_HM ):
      WinSendDlgItemMsg (hwnd, IDB_HM, BM_SETCHECK,
                         MPFROMSHORT (TRUE), 0L);
      break;
    default:
      break;
  }

}

/******************************************************************************/
/* wpDateDlgProc: Window procedure for Date dialog box.                       */
/******************************************************************************/

MRESULT EXPENTRY wpDateDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)

{

/* 1.98 */
 MRESULT mr = (MRESULT) FALSE;
//static ULONG olddateformat;

 switch (msg)
    {
     case WM_INITDLG:                  /* dialog initialization routine       */
//     olddateformat  = dateformat;
//     fnDateDlgInit( hwnd );
       break;                          /* end case (WM_INITDLG)               */
#if 0
     case UM_SELECT:
       switch( dateformat )
       {
         case( DATE_FORMAT_1 ):
           WinSetFocus (HWND_DESKTOP, WinWindowFromID (hwnd, IDB_DATE1));
           break;
         case( DATE_FORMAT_2 ):
           WinSetFocus (HWND_DESKTOP, WinWindowFromID (hwnd, IDB_DATE2));
           break;
         case( DATE_FORMAT_3 ):
           WinSetFocus (HWND_DESKTOP, WinWindowFromID (hwnd, IDB_DATE3));
           break;
         default:
           break;
        }
        break;
#endif
     case WM_COMMAND:
        switch (SHORT1FROMMP(mp1))
           {
            case DID_OK:               /* User clicked on OK push button      */
#if 0
               if( (BOOL) WinSendDlgItemMsg( hwnd, IDB_DATE1,
                          BM_QUERYCHECK, 0L, 0L ) == 1 )
                 dateformat = DATE_FORMAT_1;
               else
               {
                 if( (BOOL) WinSendDlgItemMsg( hwnd, IDB_DATE2,
                            BM_QUERYCHECK, 0L, 0L ) == 1 )
                   dateformat = DATE_FORMAT_2;
                 else
                   dateformat = DATE_FORMAT_3;
               }
#endif
               WinDismissDlg (hwnd, TRUE);        /* remove the dialog box  */
               mr = (MRESULT) TRUE;
               break;

            case DID_CANCEL:           /* User clicked on Cancel push button  */
//             dateformat  = olddateformat;
//             fnDateDlgInit( hwnd );
               break;

            case IDP_DEFAULT:
//             fnInitialize( IDD_DATE );
//             fnDateDlgInit( hwnd );
               break;

            default:                   /* Let PM handle rest of messages      */
               mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
               break;
           }
        break;

     default:                          /* Let PM handle rest of messages      */
        mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
        break;
    }

 return (mr);

}

/******************************************************************************/
/* fnDateDlgInit: Initialization for Date dialog box.                         */
/******************************************************************************/

VOID fnDateDlgInit( HWND hwnd )

{
/* 1.98 */
#if 0
  switch( dateformat )
  {
    case( DATE_FORMAT_1 ):
      WinSendDlgItemMsg (hwnd, IDB_DATE1, BM_SETCHECK, MPFROMSHORT (TRUE), 0L);
      break;
    case( DATE_FORMAT_2 ):
      WinSendDlgItemMsg (hwnd, IDB_DATE2, BM_SETCHECK, MPFROMSHORT (TRUE), 0L);
      break;
    case( DATE_FORMAT_3 ):
      WinSendDlgItemMsg (hwnd, IDB_DATE3, BM_SETCHECK, MPFROMSHORT (TRUE), 0L);
      break;
    default:
      break;
  }
#endif
}

/******************************************************************************/
/*                                                                            */
/* wpRepSetDlgProc: Window procedure for Report settings dialog box.          */
/*                                                                            */
/******************************************************************************/

MRESULT EXPENTRY wpRepSetDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)

{

 MRESULT mr = (MRESULT) FALSE;
 static ULONG oldrepsave, oldrepdays;
 static BOOL  oldrephide, oldrepexcl, oldrepdesc, oldrepcomm,
              oldrepzero, oldrepdetails;
 static CHAR  oldrepline1[80];
 static CHAR  oldrepline2[80];
 static BOOL  line1FldChg = FALSE;       /* 1.98 */
 static BOOL  line2FldChg = FALSE;       /* 1.98 */

 switch (msg)
    {
     case WM_INITDLG:                  /* dialog initialization routine       */
       oldrepsave  = repsave;
       oldrepdays  = repdays;
       oldrepexcl  = repexcl;
       oldrephide  = rephide;
       oldrepdesc  = repdesc;
       oldrepcomm  = repcomm;
       oldrepdetails = repdetails;
       oldrepzero  = repzero;
       strcpy( oldrepline1, repline1 ); /* 1.98 */
       strcpy( oldrepline2, repline2 ); /* 1.98 */
       fnRepSetDlgInit( hwnd );
       break;                          /* end case (WM_INITDLG)               */

     case UM_SELECT:
       WinSetFocus (HWND_DESKTOP, WinWindowFromID (hwnd, IDC_SAVEDATA));
       break;

     case WM_CONTROL:
       switch (SHORT1FROMMP (mp1))
          {                            /* Save data to file must be On to     */
           case IDC_SAVEDATA:          /* enable Prune days spin button ctrl  */
             if( SHORT2FROMMP (mp1) == BN_CLICKED )
               if( WinSendDlgItemMsg( hwnd, IDC_SAVEDATA,
                                     BM_QUERYCHECK, 0L, 0L ) )
                 WinEnableControl( hwnd, IDC_PRUNEDAYS, TRUE );
               else
                 WinEnableControl( hwnd, IDC_PRUNEDAYS, FALSE );
             break;
           case IDE_REPLINE1:          /* 1.98 */
             if( (USHORT) SHORT2FROMMP(mp1) == EN_CHANGE )
               line1FldChg = TRUE;
             break;
           case IDE_REPLINE2:          /* 1.98 */
             if( (USHORT) SHORT2FROMMP(mp1) == EN_CHANGE )
               line2FldChg = TRUE;
             break;
           default:
             break;
          }
       break;

     case WM_COMMAND:
        switch (SHORT1FROMMP(mp1))
           {
            case DID_OK:               /* User clicked on OK push button      */
               repsave = (ULONG) WinSendDlgItemMsg( hwnd, IDC_SAVEDATA,
                                 BM_QUERYCHECK, 0L, 0L );
               repexcl = (BOOL) WinSendDlgItemMsg( hwnd, IDC_REPEXCL,
                                BM_QUERYCHECK, 0L, 0L );
               rephide = (BOOL) WinSendDlgItemMsg( hwnd, IDC_REPHIDE,
                                BM_QUERYCHECK, 0L, 0L );
               repdesc = (BOOL) WinSendDlgItemMsg( hwnd, IDC_REPDESC,
                                BM_QUERYCHECK, 0L, 0L );
               repcomm = (BOOL) WinSendDlgItemMsg( hwnd, IDC_REPCOMM,
                                BM_QUERYCHECK, 0L, 0L );
               repzero = (BOOL) WinSendDlgItemMsg( hwnd, IDC_REPZERO,
                                BM_QUERYCHECK, 0L, 0L );
               repdetails = (BOOL) WinSendDlgItemMsg( hwnd, IDC_REPDETAILS,
                                BM_QUERYCHECK, 0L, 0L );

               WinSendDlgItemMsg(hwnd, IDC_PRUNEDAYS, SPBM_QUERYVALUE,
                                 &repdays, MPFROM2SHORT( 0L, 0L));

               if( line1FldChg == TRUE )    /* 1.98 */
                 WinQueryWindowText( WinWindowFromID( hwnd, IDE_REPLINE1 ),
                                     sizeof( repline1 ), repline1 );
               if( line2FldChg == TRUE )    /* 1.98 */
                 WinQueryWindowText( WinWindowFromID( hwnd, IDE_REPLINE2 ),
                                     sizeof( repline2 ), repline2 );

               WinDismissDlg (hwnd, TRUE);        /* remove the dialog box  */
               mr = (MRESULT) TRUE;
               break;

            case DID_CANCEL:           /* User clicked on Cancel push button  */
               repsave = oldrepsave;
               repdays = oldrepdays;
               repdesc = oldrepdesc;
               repexcl = oldrepexcl;
               rephide = oldrephide;
               repcomm = oldrepcomm;
               repzero = oldrepzero;
               repdetails = oldrepdetails;
               strcpy( repline1, oldrepline1 );   // 1.98
               strcpy( repline2, oldrepline2 );   // 1.98
               fnRepSetDlgInit( hwnd );
               break;

            case IDP_DEFAULT:
               fnInitialize( IDD_REPSET );
               fnRepSetDlgInit( hwnd );
               break;

            default:                   /* Let PM handle rest of messages      */
               mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
               break;
           }
        break;

     default:                          /* Let PM handle rest of messages      */
        mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
        break;
    }

 return (mr);

}

/******************************************************************************/
/* fnRepSetDlgInit: Initialization for Reports settings dialog box.           */
/******************************************************************************/

VOID fnRepSetDlgInit( HWND hwnd )

{

  if( repsave == YES )
    WinSendDlgItemMsg (hwnd, IDC_SAVEDATA, BM_SETCHECK,
                       MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_SAVEDATA, BM_SETCHECK,
                       MPFROMSHORT (FALSE), 0L);

  if( repexcl == YES )
    WinSendDlgItemMsg (hwnd, IDC_REPEXCL, BM_SETCHECK,
                       MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_REPEXCL, BM_SETCHECK,
                       MPFROMSHORT (FALSE), 0L);

  if( rephide == YES )
    WinSendDlgItemMsg (hwnd, IDC_REPHIDE, BM_SETCHECK,
                       MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_REPHIDE, BM_SETCHECK,
                       MPFROMSHORT (FALSE), 0L);

  if( repdesc == YES )
    WinSendDlgItemMsg (hwnd, IDC_REPDESC, BM_SETCHECK,
                       MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_REPDESC, BM_SETCHECK,
                       MPFROMSHORT (FALSE), 0L);

  if( repcomm == YES )
    WinSendDlgItemMsg (hwnd, IDC_REPCOMM, BM_SETCHECK,
                       MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_REPCOMM, BM_SETCHECK,
                       MPFROMSHORT (FALSE), 0L);

  if( repzero == YES )
    WinSendDlgItemMsg (hwnd, IDC_REPZERO, BM_SETCHECK,
                       MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_REPZERO, BM_SETCHECK,
                       MPFROMSHORT (FALSE), 0L);

  WinSendDlgItemMsg( hwnd, IDC_PRUNEDAYS, SPBM_SETLIMITS,
                     MPFROMSHORT(365), MPFROMSHORT(0) );
  WinSendDlgItemMsg( hwnd, IDC_PRUNEDAYS, SPBM_SETCURRENTVALUE,
                     MPFROMSHORT(repdays), 0L );
  WinSendDlgItemMsg( hwnd, IDC_PRUNEDAYS, SPBM_SETTEXTLIMIT,
                     MPFROMSHORT(3L), 0L );

  if( repsave == YES )
    WinEnableControl( hwnd, IDC_PRUNEDAYS, TRUE );
  else
    WinEnableControl( hwnd, IDC_PRUNEDAYS, FALSE );

  if( repdetails == YES )
    WinSendDlgItemMsg (hwnd, IDC_REPDETAILS, BM_SETCHECK,
                       MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_REPDETAILS, BM_SETCHECK,
                       MPFROMSHORT (FALSE), 0L);

  WinSetWindowText( WinWindowFromID( hwnd, IDE_REPLINE1 ), repline1 ); // 1.98
  WinSetWindowText( WinWindowFromID( hwnd, IDE_REPLINE2 ), repline2 ); // 1.98

}

/******************************************************************************/
/* wpAlarmDlgProc: Window procedure for Alarms dialog box.                    */
/******************************************************************************/

MRESULT EXPENTRY wpAlarmDlgProc (HWND hwnd, ULONG msg, MPARAM mp1,
                                 MPARAM mp2)

{

 MRESULT mr = (MRESULT) FALSE;
 static BOOL  oldalarmsound, oldalarmmsg, oldalarmedit, oldalarmchg;
 static ULONG oldalarmtime, oldalarmexp;
 static CHAR  oldalarmitem[CODE_WIDTH];

 switch (msg)
    {
     case WM_INITDLG:                  /* dialog initialization routine       */
       {
         HAB      hab;
         ULONG    i;
         PACTINFO item;

         hab = WinQueryAnchorBlock( hwnd );
         WinLoadString( hab, 0L, IDS_NONE, sizeof( szTitle ), szTitle );

         oldalarmsound  = alarmsound;  /* save old values in case user changes*/
         oldalarmmsg    = alarmmsg;    /* and then clicks on Cancel, we need  */
         oldalarmtime   = alarmtime;   /* to be able to restore back          */
         oldalarmedit   = alarmedit;
         oldalarmchg    = alarmchg;
         oldalarmexp    = alarmexp;
         strcpy( oldalarmitem, alarmitem );

         fnActivityList(hwnd, NULL, szBlank, IDC_ALARMITEM, FALSE,
                        TRUE, TYPE_NORMAL);
         fnAlarmDlgInit( hwnd );
       }
       break;                          /* end case (WM_INITDLG)               */

     case UM_SELECT:
         WinSetFocus (HWND_DESKTOP, WinWindowFromID (hwnd, IDC_ALARM));
         break;


     case WM_CONTROL:
       switch (SHORT1FROMMP (mp1))
          {                            /* Save data to file must be On to     */
           case IDC_CURRENT:           /* enable Prune days spin button ctrl  */
             if( SHORT2FROMMP (mp1) == BN_CLICKED )
               if( WinSendDlgItemMsg( hwnd, IDC_CURRENT,
                                     BM_QUERYCHECK, 0L, 0L ) )
                 WinEnableControl( hwnd, IDC_ALARMITEM, FALSE );
               else
                 WinEnableControl( hwnd, IDC_ALARMITEM, TRUE );
             break;

           default:
             break;
          }
       break;

     case WM_COMMAND:
        switch (SHORT1FROMMP(mp1))
           {
            case DID_OK:               /* User clicked on OK push button      */
               {                       /* Process options settings and place  */
                 PACTINFO item;        /* into appropriate variables          */
                 SHORT    i, j;

                 alarmsound  = (BOOL) WinSendDlgItemMsg( hwnd, IDC_SOUND,
                               BM_QUERYCHECK, 0L, 0L );
                 alarmmsg    = (BOOL) WinSendDlgItemMsg( hwnd, IDC_MESSAGE,
                               BM_QUERYCHECK, 0L, 0L );
                 alarmedit   = (BOOL) WinSendDlgItemMsg( hwnd, IDC_ALARMEDIT,
                               BM_QUERYCHECK, 0L, 0L );
                 alarmchg    = (BOOL) WinSendDlgItemMsg( hwnd, IDC_ALARMCHG,
                               BM_QUERYCHECK, 0L, 0L );

                 WinSendDlgItemMsg(hwnd, IDC_ALARM, SPBM_QUERYVALUE,
                                   &alarmtime, MPFROM2SHORT( 0L, 0L));

                 WinSendDlgItemMsg(hwnd, IDC_ALARMEXPIRE, SPBM_QUERYVALUE,
                                   &alarmexp, MPFROM2SHORT( 0L, 0L));
                                       /*                                     */

                 if((BOOL) WinSendDlgItemMsg( hwnd, IDC_CURRENT,
                               BM_QUERYCHECK, 0L, 0L ))
                 {
                   strcpy(alarmitem, "$CURACT$");
                   strcat(alarmitem, " ");
                   strcat(alarmitem, szBlank );
                 }
                 else
                 {
                   j = (SHORT)WinSendDlgItemMsg(hwnd, IDC_ALARMITEM,
                                                LM_QUERYSELECTION, 0L, 0L);
                   if(j == LIT_NONE)
                   {
                     strcpy(alarmitem, "$CURACT$");
                     strcat(alarmitem, " ");
                     strcat(alarmitem, szBlank );
                   }
                   else
                   {
                     item = start;
                     for( i = 0; i < j; i++ )
                       item = (PACTINFO)item->next;
                     strcpy(alarmitem, item->code);
                     strcat(alarmitem, " ");
                     strcat(alarmitem, item->parent);
                   }
                 }

                 WinDismissDlg (hwnd, TRUE);        /* remove the dialog box  */
                 mr = (MRESULT) TRUE;
               }                       /* end case (DID_OK)                   */
               break;

            case DID_CANCEL:           /* User clicked on Cancel push button  */
               alarmsound  = oldalarmsound;
               alarmmsg    = oldalarmmsg;
               alarmtime   = oldalarmtime;
               alarmexp    = oldalarmexp;
               alarmedit   = oldalarmedit;
               alarmchg    = oldalarmchg;
               strcpy( alarmitem, oldalarmitem );
               fnAlarmDlgInit( hwnd );
               break;

            case IDP_ALARMDEF:
               fnInitialize( IDD_ALARM );
               fnAlarmDlgInit( hwnd );
               break;

            default:                   /* Let PM handle rest of messages      */
               mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
               break;
           }
        break;

     default:                          /* Let PM handle rest of messages      */
        mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
        break;
    }

 return (mr);

}

/******************************************************************************/
/* fnAlarmDlgInit: Initialization for Alarm dialog box.                       */
/******************************************************************************/

VOID fnAlarmDlgInit( HWND hwnd )

{

  SHORT    i;
  PACTINFO item;
  CHAR     activity[CODE_WIDTH+1];
  CHAR     parent[CODE_WIDTH+1];

  if( alarmsound == YES )
    WinSendDlgItemMsg (hwnd, IDC_SOUND, BM_SETCHECK, MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_SOUND, BM_SETCHECK, MPFROMSHORT (FALSE), 0L);

  if( alarmmsg == YES )
    WinSendDlgItemMsg (hwnd, IDC_MESSAGE, BM_SETCHECK,
                       MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_MESSAGE, BM_SETCHECK,
                       MPFROMSHORT (FALSE), 0L);

  if( alarmedit == YES )
    WinSendDlgItemMsg (hwnd, IDC_ALARMEDIT, BM_SETCHECK,
                       MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_ALARMEDIT, BM_SETCHECK,
                       MPFROMSHORT (FALSE), 0L);

  if( alarmchg == YES )
    WinSendDlgItemMsg (hwnd, IDC_ALARMCHG, BM_SETCHECK,
                       MPFROMSHORT (TRUE), 0L);
  else
    WinSendDlgItemMsg (hwnd, IDC_ALARMCHG, BM_SETCHECK,
                       MPFROMSHORT (FALSE), 0L);

  WinSendDlgItemMsg( hwnd, IDC_ALARM, SPBM_SETLIMITS,
                     MPFROMSHORT(1440), MPFROMSHORT(0) );
  WinSendDlgItemMsg( hwnd, IDC_ALARM, SPBM_SETCURRENTVALUE,
                     MPFROMSHORT(alarmtime), 0L );
  WinSendDlgItemMsg( hwnd, IDC_ALARM, SPBM_SETTEXTLIMIT,
                     MPFROMSHORT(4L), 0L );

  WinSendDlgItemMsg( hwnd, IDC_ALARMEXPIRE, SPBM_SETLIMITS,
                     MPFROMSHORT(1440), MPFROMSHORT(1) );
  WinSendDlgItemMsg( hwnd, IDC_ALARMEXPIRE, SPBM_SETCURRENTVALUE,
                     MPFROMSHORT(alarmexp), 0L );
  WinSendDlgItemMsg( hwnd, IDC_ALARMEXPIRE, SPBM_SETTEXTLIMIT,
                     MPFROMSHORT(4L), 0L );

//if( alarmitem[0] == ' ' )
//  WinSendDlgItemMsg (hwnd, IDC_ALARMITEM, LM_SELECTITEM,
//                     MPFROMLONG (0), MPFROMSHORT (TRUE));
//else
//{

    fnSubstr(alarmitem, activity, 1, CODE_WIDTH);
    fnSubstr(alarmitem, parent, CODE_WIDTH+2, CODE_WIDTH);

    if(strncmp(activity, "$CURACT$", CODE_WIDTH) == 0)
    {
      WinSendDlgItemMsg(hwnd, IDC_CURRENT, BM_SETCHECK, MPFROMSHORT(TRUE), 0L);
      WinEnableControl(hwnd, IDC_ALARMITEM, FALSE);
    }
    else
    {
      i = 0;
      item = start;
      while( item )
      {
        if(strcmp(item->code, activity)==0 &&
           strcmp(item->parent, parent)==0)
          WinSendDlgItemMsg (hwnd, IDC_ALARMITEM, LM_SELECTITEM,
                             MPFROMLONG (i), MPFROMSHORT (TRUE));
          i++;
        item = (PACTINFO)item->next;
      }
     }
// }

}

/******************************************************************************/
/* wpUserExitDlgProc: Window procedure for User Exit dialog window.           */
/******************************************************************************/

MRESULT EXPENTRY wpUserExitDlgProc (HWND hwnd, ULONG msg, MPARAM mp1,
                                    MPARAM mp2)

{

 MRESULT mr = (MRESULT) FALSE;
 static CHAR  oldmenutext[MENU_WIDTH];
 static CHAR  oldprogram[PROG_WIDTH];
 static CHAR  oldparameters[PARA_WIDTH];
 static BOOL  fcmenuFldChg = FALSE;
 static BOOL  fcprogFldChg = FALSE;
 static BOOL  fcparaFldChg = FALSE;

 switch (msg)
    {
     case WM_INITDLG:
        strcpy( oldmenutext,   menutext );
        strcpy( oldprogram,    program );
        strcpy( oldparameters, parameters );
        fnUserExitDlgInit( hwnd );
        break;                         /* end case (WM_INITDLG)               */

     case UM_SELECT:
        WinSetFocus (HWND_DESKTOP, WinWindowFromID (hwnd, IDE_MENUTEXT));
        break;

     case WM_CONTROL:
       switch( SHORT1FROMMP( mp1 ))
       {
         case IDE_MENUTEXT:
           if( (USHORT) SHORT2FROMMP(mp1) == EN_CHANGE )
             fcmenuFldChg = TRUE;
           break;
         case IDE_PROGRAM:
           if( (USHORT) SHORT2FROMMP(mp1) == EN_CHANGE )
             fcprogFldChg = TRUE;
           break;
         case IDE_PARAMETERS:
           if( (USHORT) SHORT2FROMMP(mp1) == EN_CHANGE )
             fcparaFldChg = TRUE;
           break;
         default:
           mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
           break;
       }
       break;

     case WM_COMMAND:
        switch (SHORT1FROMMP(mp1))
           {
            case DID_OK:               /* User clicked on OK push button      */
               {                       /* Process options settings and place  */
                                       /* into appropriate variables          */
                 /* import commandfree and commandswap from entry fields      */
                 if( fcmenuFldChg == TRUE )
                   WinQueryWindowText( WinWindowFromID( hwnd, IDE_MENUTEXT ),
                                       sizeof( menutext ), menutext );
                 if( fcprogFldChg == TRUE )
                   WinQueryWindowText( WinWindowFromID( hwnd, IDE_PROGRAM ),
                                       sizeof( program ), program );
                 fnToUpperString( program );

                 if( fcparaFldChg == TRUE )
                   WinQueryWindowText( WinWindowFromID( hwnd, IDE_PARAMETERS ),
                                       sizeof( parameters ), parameters );
                 fnToUpperString( parameters );

                 WinDismissDlg (hwnd, TRUE);        /* remove the dialog box  */
                 mr = (MRESULT) TRUE;
               }                       /* end case (DID_OK)                   */
               break;

            case IDP_CLEAR:
               strcpy( menutext,   "" );
               strcpy( program,    "" );
               strcpy( parameters, "" );
               fnUserExitDlgInit( hwnd );
               break;

            case DID_CANCEL:           /* User clicked on Cancel push button  */
               strcpy( menutext,   oldmenutext );
               strcpy( program,    oldprogram );
               strcpy( parameters, oldparameters );
               fnUserExitDlgInit( hwnd );
               break;

            default:                   /* Let PM handle rest of messages      */
               mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
               break;
           }
        break;

     default:                          /* Let PM handle rest of messages      */
        mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
        break;
    }

 return (mr);

}

/******************************************************************************/
/* fnUserExitDlgInit: Initialization for User Exit dialog box.                */
/******************************************************************************/

VOID fnUserExitDlgInit( HWND hwnd )

{

  WinSetWindowText( WinWindowFromID( hwnd, IDE_MENUTEXT ), menutext );
  WinSetWindowText( WinWindowFromID( hwnd, IDE_PROGRAM ), program );
  WinSetWindowText( WinWindowFromID( hwnd, IDE_PARAMETERS ), parameters );

  WinSendMsg( WinWindowFromID( hwnd, IDE_MENUTEXT ), EM_SETTEXTLIMIT,
              (MPARAM)(MENU_WIDTH-1), (MPARAM)0 );
  WinSendMsg( WinWindowFromID( hwnd, IDE_PROGRAM ), EM_SETTEXTLIMIT,
              (MPARAM)(PROG_WIDTH-1), (MPARAM)0 );
  WinSendMsg( WinWindowFromID( hwnd, IDE_PARAMETERS ), EM_SETTEXTLIMIT,
              (MPARAM)(PARA_WIDTH-1), (MPARAM)0 );

  WinEnableWindow( WinWindowFromID( hwnd, IDE_MENUTEXT ), TRUE );
  WinEnableWindow( WinWindowFromID( hwnd, IDE_PROGRAM ), TRUE );
  WinEnableWindow( WinWindowFromID( hwnd, IDE_PARAMETERS ), TRUE );

}

/******************************************************************************/
/*                                                                            */
/* wpReportListDlgProc: Window procedure the Report List dialog box.          */
/*                                                                            */
/******************************************************************************/

MRESULT EXPENTRY wpReportListDlgProc (HWND hwnd, ULONG msg, MPARAM mp1,
                                MPARAM mp2)

{

 MRESULT mr = (MRESULT) FALSE;
 static  HAB hab;
 static  BOOL line1FldChg = FALSE;     /* 1.98 */
 static  BOOL line2FldChg = FALSE;     /* 1.98 */

 switch (msg)
    {
     case WM_INITDLG:                  /* Dialog initialization routine       */
       {                               /* Populate the list box               */
         PREPINFO item;
         LONG     count;

         hab = WinQueryAnchorBlock( hwnd );

         if( hwndHelp )
           WinAssociateHelpInstance( hwndHelp, hwnd );

         count = 0;
         item = startrep;
         while( item )
         {
           WinSendMsg( WinWindowFromID( hwnd, IDL_REPLIST ), LM_INSERTITEM,
                       MPFROMSHORT(LIT_END), MPFROMP(item->repdate) );
           if( item->selected == YES )
             WinSendMsg( WinWindowFromID( hwnd, IDL_REPLIST ), LM_SELECTITEM,
                         MPFROMSHORT(count), MPFROMSHORT(TRUE) );
           item = (PREPINFO)item->next;
           count++;
         }

         if( reptotal == YES )
           WinSendDlgItemMsg (hwnd, IDC_TOTAL, BM_SETCHECK,
                              MPFROMSHORT (TRUE), 0L);
         else
           WinSendDlgItemMsg (hwnd, IDC_TOTAL, BM_SETCHECK,
                              MPFROMSHORT (FALSE), 0L);

         WinSetWindowText( WinWindowFromID( hwnd, IDE_REPLINE1 ),
                           repline1 ); // 1.98
         WinSetWindowText( WinWindowFromID( hwnd, IDE_REPLINE2 ),
                           repline2 ); // 1.98
       }
       break;                          /* end case (WM_INITDLG)               */

     case WM_CLOSE:
        WinDestroyWindow( hwnd );
        break;

     case WM_CONTROL:                        /* 1.98 */
       switch (SHORT1FROMMP (mp1))
          {
           case IDE_REPLINE1:
             if( (USHORT) SHORT2FROMMP(mp1) == EN_CHANGE )
               line1FldChg = TRUE;
             break;
           case IDE_REPLINE2:
             if( (USHORT) SHORT2FROMMP(mp1) == EN_CHANGE )
               line2FldChg = TRUE;
             break;
           default:
             break;
          }
       break;

     case WM_COMMAND:
        switch (SHORT1FROMMP(mp1))
           {
            case DID_OK:               /* User clicked on OK push button      */
               {                       /* Process options settings and place  */
                                       /* into appropriate variables          */
                 if( line1FldChg == TRUE )  /* 1.98 */
                   WinQueryWindowText( WinWindowFromID( hwnd, IDE_REPLINE1 ),
                                       sizeof( repline1 ), repline1 );
                 if( line2FldChg == TRUE )  /* 1.98 */
                   WinQueryWindowText( WinWindowFromID( hwnd, IDE_REPLINE2 ),
                                       sizeof( repline2 ), repline2 );

                 reptotal = (BOOL)WinSendDlgItemMsg (hwnd, IDC_TOTAL,
                            BM_QUERYCHECK, MPFROMSHORT (TRUE), 0L);   /* 1.97 */

                 if(fnProcessReportList(hwnd, IDL_REPLIST) > 0)
                   WinLoadDlg( HWND_DESKTOP, 0L, wpReportDlgProc, 0L,
                               IDD_REPORT, NULL );

//               WinSendMsg (hwnd, WM_CLOSE, 0L, 0L );
               }                       /* end case (DID_OK)                   */
               break;

            case IDP_ALL:
               {
                 PREPINFO item;
                 LONG     count;

                 count = 0;
                 item  = startrep;
                 while( item )
                 {
                   item->selected = YES;
                   WinSendMsg( WinWindowFromID( hwnd, IDL_REPLIST ),
                               LM_SELECTITEM,
                               MPFROMSHORT(count), MPFROMSHORT(TRUE) );
                   item = (PREPINFO)item->next;
                   count++;
                 }
               }                       /* end case (IDP_ALL)                  */
               break;

            case IDP_NONE:
               {
                 PREPINFO item;
                 LONG     count;

                 count = 0;
                 item  = startrep;
                 while( item )
                 {
                   item->selected = NO;
                   WinSendMsg( WinWindowFromID( hwnd, IDL_REPLIST ),
                               LM_SELECTITEM,
                               MPFROMSHORT(count), MPFROMSHORT(FALSE) );
                   item = (PREPINFO)item->next;
                   count++;
                 }
               }                       /* end case (IDP_ALL)                  */
               break;

            case DID_CANCEL:           /* User clicked on Cancel push button  */
               WinSendMsg (hwnd, WM_CLOSE, 0L, 0L );
               break;

            case IDP_DELETE:           /* User clicked on Delete push button  */
               {
                 ULONG found;

                 found = fnProcessReportList(hwnd, IDL_REPLIST);
                 if(found > 0)
                 {
                   PREPINFO item;
                   BOOL     doit = FALSE;

                   if( showdelete == YES )       /* show message box first    */
                   {
                     WinLoadString(hab, 0L, IDS_DELETE, sizeof(szTitle),
                                   szTitle);
                     WinLoadString(hab, 0L, IDS_DELETEMSG, sizeof(szText),
                                   szText);
                     sprintf(szText1, "%s %s?", szText, "report(s)");
                     if(WinMessageBox(HWND_DESKTOP, hwnd, szText1, szTitle, 1,
                                      MB_MOVEABLE | MB_YESNO | MB_WARNING |
                                      MB_DEFBUTTON2) == MBID_YES)
                       doit = TRUE;
                   }
                   else
                     doit = TRUE;
                   if( doit == TRUE )    /* ok, we really want to delete, set */
                   {                     /* the delete flag on                */
                     ULONG i;
                     while(found > 0)
                     {
                       i = 0;            // V1.97
                       item  = startrep;
                       while( item )
                       {
                         if(item->selected == YES)
                         {
//                         WinMessageBox(HWND_DESKTOP, hwnd,
//                                       item->repdate, "Debug", 1,
//                                       MB_MOVEABLE | MB_OK);
                           fnDeleteReportLinkList(item);
                           WinDeleteLboxItem( WinWindowFromID( hwnd,
                                              IDL_REPLIST ), i );
                           break;
                         }
                         i++;
                         item = (PREPINFO)item->next;
                       }
                       found--;
                       totalreports--;
                     }
                   }
                   fnSaveReportList();
                 }

//               WinSendMsg (hwnd, WM_CLOSE, 0L, 0L );
               }                       /* end case (IDP_DELETE)               */
               break;

            default:                   /* Let PM handle rest of messages      */
               mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
               break;
           }
        break;

     default:                          /* Let PM handle rest of messages      */
        mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
        break;
    }

 return (mr);

}

/******************************************************************************/
/*                                                                            */
/* fnProcessReportList:                                                       */
/*                                                                            */
/******************************************************************************/

ULONG fnProcessReportList( HWND hwnd, ULONG id )
{

  SHORT    sel, index, i;
  ULONG    found;
  PREPINFO item;

  item  = startrep;
  while( item )
  {
    item->selected = NO;
    item = (PREPINFO)item->next;
  }

  found = 0;            /* Counter for the reports that were   */
  index = LIT_FIRST;    /* selected in the list                */
  sel = (SHORT)WinSendMsg(WinWindowFromID(hwnd, id),
               LM_QUERYSELECTION, MPFROMSHORT(index), 0L);
  while( sel != LIT_END ) /* loop until end of the list box    */
  {
    found++;
    item  = startrep;
    for( i=0; i < sel; i++ )
      item = (PREPINFO)item->next;
    item->selected = YES;
    index = sel;
    sel = (SHORT)WinSendMsg(WinWindowFromID(hwnd, id),
                 LM_QUERYSELECTION, MPFROMSHORT(index), 0L);
  }

  return (found);

}

/******************************************************************************/
/*                                                                            */
/* wpReportDlgProc: Window procedure the Report dialog box.                   */
/*                                                                            */
/******************************************************************************/

MRESULT EXPENTRY wpReportDlgProc (HWND hwnd, ULONG msg, MPARAM mp1,
                                MPARAM mp2)

{

 MRESULT mr = (MRESULT) FALSE;

 switch (msg)
    {
     case WM_INITDLG:                  /* Dialog initialization routine       */
       {
         ULONG     count  = 0;
         ULONG     replength;
         HAB       hab;
         PREPINFO  item;
         PREPTOTAL starttot;
         PREPTOTAL lasttot;
         PREPTOTAL activity;
         BOOL      newAct;
         CHAR      code[CODE_WIDTH+1], parent[CODE_WIDTH+1], acttime[8];
         ULONG     i, j, max;
         IPT       lOffset = 0;
         ULONG     cbCopy  = 0;
         CHAR     *szBuffer;

         if( hwndHelp )
           WinAssociateHelpInstance( hwndHelp, hwnd );

         hab = WinQueryAnchorBlock( hwnd );

         starttot = lasttot = NULL;

         WinSetPresParam( WinWindowFromID( hwnd, IDE_REPORT), PP_FONTNAMESIZE,
                          sizeof("10.System Monospaced"),
                          "10.System Monospaced" );

         if(repdesc == YES)
           replength = 85;
         else
           replength = 64;

         if(reptotal == NO)
         {
           item = startrep;
           while(item)
           {
             if(item->selected == YES)
               cbCopy = cbCopy + (strlen(item->repdata)/30+2)*replength;
             item = (PREPINFO)item->next;
           }
           cbCopy = cbCopy + strlen(repline1) + 1;  /* 1.98 */
           cbCopy = cbCopy + strlen(repline2) + 2;  /* 1.98 */
           szBuffer = (CHAR *)malloc( cbCopy * sizeof( CHAR ) );
           memset( szBuffer, 0, cbCopy );
                                       /* get MLE ready for importing data    */
           WinSendMsg( WinWindowFromID( hwnd, IDE_REPORT ),
                       MLM_SETIMPORTEXPORT, MPFROMP( szBuffer ),
                       MPFROMSHORT( (USHORT) cbCopy ) );
           fnReportNotes( szBuffer );  /* 1.98 */
         }


         item = startrep;
         while( item )
         {
           if( item->selected == YES )
           {

             if(reptotal == NO)
               starttot = lasttot = NULL;

             i = 1;
             max = strlen(item->repdata) + 1;
             while( 1 )
             {
               if( i > max )
                 break;

               newAct = TRUE;
               fnSubstr(item->repdata, code, i, CODE_WIDTH);
               fnSubstr(item->repdata, parent, i+21, CODE_WIDTH);
               fnPadString(parent, CODE_WIDTH);
               fnSubstr(item->repdata, acttime, i+13, 7);
               if(atof(acttime) == 0.0 && repzero == NO);
               else
               {
                 if(reptotal == YES)
                 {
                   activity = starttot;
                   while(activity)
                   {
                     if(strcmp(activity->code, code)==0 &&
                        strcmp(activity->parent, parent)==0)
                     {
                       float xtime;
                       ULONG xcount;

                       /* add count and timer to existing report member */
                       xtime = atof(acttime);
                       activity->time = activity->time + (float)(xtime *
                          (float)fnGetSecunits(item->units) / (float)secunits);

                       fnSubstr(item->repdata, szText, i+9, 3);
                       xcount = atol(szText);
                       activity->count = activity->count + xcount;

                       newAct = FALSE;
                         break;
                     }
                     activity = (PREPTOTAL)activity->next;
                   }
                 }

                 if(newAct)
                 {
                   activity = (PREPTOTAL) malloc(sizeof(REPTOTAL));
                   strcpy(activity->code, code);
                   strcpy(activity->parent, parent);
                   if(reptotal == YES)
                     activity->time = (float)(atof(acttime) *
                        (float)fnGetSecunits(item->units) / (float)secunits);
                   else
                     activity->time = atof(acttime);
                   fnSubstr(item->repdata, szText, i+9, 3);
                   activity->count = atol(szText);

                   if(repcomm == YES)
                     fnSubstr(item->commentdata, activity->comments, i,
                              COMM_WIDTH);
                   else
                     strcpy(activity->comments, "");

                   if(repdesc == YES)
                     fnGetActivityDesc(code, parent, activity->description);
                   else
                     strcpy(activity->description, "");

                   // add activity to end of linked list
                   if( lasttot == NULL )
                   {
                     lasttot  = activity;
                     starttot = activity;
                     activity->prior = NULL;
                   }
                   else
                   {
                     lasttot->next  = (PREPTOTAL)activity;
                     activity->prior = (PREPTOTAL)lasttot;
                   }
                   activity->next = NULL;
                   lasttot       = activity;

                   count++;
                 }                              /* end if(newAct) */
               }                                /* end else       */
               i = i + 30;
             }                                  /* end while( 1 ) */
             if(reptotal == NO)
             {
               /* now format report */
               fnFormatReport(starttot, item->total, fnGetUnits(item->units),
                              item->repdate, szBuffer);
               fnFreeReptotalList(starttot);
             }

           }                                    /* end if selected == YES */
           item = (PREPINFO)item->next;         /* get next report */
         }                                      /* end while( item ) */
         if(reptotal == YES)
         {
           float total = 0.0;

           cbCopy = (count+1) * replength;
           cbCopy = cbCopy + strlen(repline1) + 1;  /* 1.98 */
           cbCopy = cbCopy + strlen(repline2) + 2;  /* 1.98 */
           szBuffer = (CHAR *)malloc( cbCopy * sizeof( CHAR ) );
           memset( szBuffer, 0, cbCopy );
                                       /* get MLE ready for importing data    */
           WinSendMsg( WinWindowFromID( hwnd, IDE_REPORT ),
                       MLM_SETIMPORTEXPORT, MPFROMP( szBuffer ),
                       MPFROMSHORT( (USHORT) cbCopy ) );
           fnReportNotes( szBuffer );  /* 1.98 */
           activity = starttot;
           while(activity)
           {
             if(strcmp(activity->parent, szBlank) == 0)
               total = total + activity->time;
             activity = (PREPTOTAL)activity->next;
           }
           fnFormatReport(starttot, total, units, "", szBuffer);
           fnFreeReptotalList(starttot);
         }

         cbCopy = strlen( szBuffer );

         WinSendMsg( WinWindowFromID( hwnd, IDE_REPORT ),
                     MLM_IMPORT, MPFROMP( &lOffset ),
                     MPFROMP( &cbCopy ) );
         WinSendMsg( WinWindowFromID( hwnd, IDE_REPORT ),
                     MLM_SETTEXTLIMIT, MPFROMSHORT( cbCopy ), 0 );

         WinSetWindowPtr( hwnd, QWL_USER, szBuffer );

       }
       break;                          /* end case (WM_INITDLG)               */

     case WM_CLOSE:
        {
          CHAR *szBuffer;

          szBuffer = WinQueryWindowPtr( hwnd, QWL_USER );
          free( szBuffer );
          WinDestroyWindow( hwnd );
        }
        break;

     case WM_COMMAND:
        switch (SHORT1FROMMP(mp1))
           {
            case DID_CANCEL:           /* User clicked on Cancel push button  */
               WinSendMsg (hwnd, WM_CLOSE, 0L, 0L );
               break;

            case IDP_PRINT:
               {
                 CHAR *szBuffer;
                 FILE *pOutfile;
                 int  rc;

                 szBuffer = WinQueryWindowPtr( hwnd, QWL_USER );
                 if( pOutfile = fopen( "$TIMETRA.PRT", "w" ))
                   fputs( szBuffer, pOutfile );
                 fclose( pOutfile );

                 rc = system("PRINT.COM /D:LPT1 $TIMETRA.PRT");
               }
               break;


            case IDP_REPSAVE:
               {
                 CHAR *szBuffer;

                 szBuffer = WinQueryWindowPtr( hwnd, QWL_USER );
                 if( WinDlgBox (HWND_DESKTOP, hwnd, wpSaveReportDlgProc, 0L,
                                IDD_SAVEREP, szBuffer ) )
                   WinSendMsg (hwnd, WM_CLOSE, 0L, 0L );
               }
               break;

            default:                   /* Let PM handle rest of messages      */
               mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
               break;
           }
        break;

     default:                          /* Let PM handle rest of messages      */
        mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
        break;
    }

 return (mr);

}


/******************************************************************************/
/* fnFormatActivity:                                                          */
/******************************************************************************/
VOID fnFormatActivity(PREPTOTAL act, float percent, ULONG units, CHAR* buf)
{

  char szTime[10];                     // time buffer
  CHAR act1[CODE_WIDTH+1];             // activity code

  if(strcmp(act->parent, szBlank)==0)  // parent activity
    strcpy(act1, act->code);
  else                                 // sub-activity
  {
    strcpy(act1, "  ");
    strcat(act1, act->code);
  }

  // Format the time into a string pointer
  if(units == UNITS_HMS || units == UNITS_HM)    /* 1.98 */
    fnConvertTime(act->time, UNITS_MINUTES, units, szTime);
  else
    sprintf(szTime, "%9.2f", act->time);

  // sprintf formatted result into buffer char string pointer
  if(repdesc == YES)
      sprintf(buf, "%-10s %-20s %3d %9s %6.1f %-30s\n", act1,
              act->description, act->count, szTime, percent,
              act->comments);
  else
    sprintf(buf, "%-10s %3d %9s %6.1f %-30s\n", act1,
            act->count, szTime, percent, act->comments);

}


/******************************************************************************/
/* fnFormatReport:                                                            */
/******************************************************************************/
VOID fnFormatReport(PREPTOTAL starttot, float total, ULONG units,
                    CHAR* repdate, CHAR* buf)
{
  float     percent;
  char      buf1[100];
  char      szTotal[10];
  PREPTOTAL activity;

  // First create the header which contains the total time
  if(units == UNITS_HMS || units == UNITS_HM)   /* 1.98 */
    fnConvertTime(total, UNITS_MINUTES, units, szTotal);
  else
    sprintf(szTotal, "%9.2f", total);

  if(repdesc == YES)
    sprintf(buf1, "%-34s# %9s      %c\n", repdate, szTotal, '%');
  else
    sprintf(buf1, "%-13s# %9s      %c\n", repdate, szTotal, '%');
  strcat(buf, buf1);

  // Loop thru all activities and process each one
  activity = starttot;
  while(activity)
  {
    // Determine the percentage value of activity time
    if(total > (float)0.0)
      percent = activity->time / total * 100;
    else
      percent = 0;
    // Process only non sub-activity codes first
    if(strcmp(activity->parent, szBlank) == 0)
    {
      // Format the activity information and place in buf1[]
      fnFormatActivity(activity, percent, units, buf1);
      strcat(buf, buf1);
      // If report detail wanted, process sub-activities if any
      if(repdetails == YES)
      {
        PREPTOTAL item;
        item = starttot;
        while(item)
        {
          if(strcmp(item->parent, activity->code) == 0)
          {
            if(total > (float)0.0)
              percent = item->time / total * 100;
            else
              percent = 0;
            fnFormatActivity(item, percent, units, buf1);
            strcat(buf, buf1);
          }
          item = (PREPTOTAL)item->next;
        }
      }                                // end if(repdetail == YES)
    }                                  // end if(parent == szBlank)
    activity = (PREPTOTAL)activity->next;
  }                                    // while(activity)
  strcat(buf, "\n\n");

}

/******************************************************************************/
/*                                                                            */
/* wpAboutDlgProc: Dialog window procedure for Product Information window.    */
/*                 Use PM timer to display for exactly as long as necessary.  */
/*                                                                            */
/******************************************************************************/

MRESULT EXPENTRY wpAboutDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)

{

 MRESULT mr = (MRESULT) FALSE;
 static  ULONG idBitmap;
 static  RECTL bitmapRect;
 static  ULONG bitmapSize;

 switch (msg)
    {
     case WM_CHAR:
       {
         if(CHARMSG(&msg)->fs & KC_KEYUP)
           return(MRESULT)FALSE;
         if(CHARMSG(&msg)->fs & KC_VIRTUALKEY)
         {
           switch( CHARMSG(&msg)->vkey )
           {
              case VK_ESC:
              case VK_NEWLINE:
              case VK_ENTER:
                WinDismissDlg( hwnd, TRUE );
                return(MRESULT)TRUE;
           }
         }
       }
       break;

     case WM_INITDLG:
        {
          LONG  lLogoDisplay;
          RECTL rectl;
          HAB   hab;

          lLogoDisplay = * (PLONG) PVOIDFROMMP (mp2);
          hab = WinQueryAnchorBlock (hwnd);

          if (lLogoDisplay != -1)
             WinStartTimer (hab, hwnd, TID_LOGOTIMER, lLogoDisplay);

          idBitmap = ID_TTBMP1;
          WinStartTimer(hab, hwnd, ID_ABOUTTIMER, ABOUT_MINUTE);

          bitmapSize = 48;
          WinQueryWindowRect(hwnd, &rectl);
          bitmapRect.xLeft   = rectl.xRight/2 - bitmapSize/2;
          bitmapRect.xRight  = bitmapRect.xLeft + bitmapSize;
          bitmapRect.yBottom = rectl.yTop - 7*bitmapSize/4;
          bitmapRect.yTop    = bitmapRect.yBottom + bitmapSize;

        }
        break;

     case WM_PAINT:
        {
          HPS    hps;
          HBITMAP hbm;
          POINTL  point;
          RECTL   rectl;

          hps = WinBeginPaint(hwnd, 0L, 0L);

          WinQueryWindowRect(hwnd, &rectl);
          WinFillRect (hps, &rectl, SYSCLR_DIALOGBACKGROUND);
          WinDrawBorder(hps, &rectl, 5, 5, 0L, 0L, DB_DLGBORDER);

          hbm = GpiLoadBitmap(hps, 0L, idBitmap, bitmapSize, bitmapSize);
          point.x = bitmapRect.xLeft;
          point.y = bitmapRect.yBottom;
          WinDrawBitmap (hps, hbm, 0L, &point, 0L, 0L, DBM_NORMAL);
          GpiDeleteBitmap (hbm);

          WinEndPaint(hwnd);

        }
        break;

     case WM_TIMER:
        {
          USHORT timerid;
          timerid = SHORT1FROMMP( mp1 );

          switch(timerid)
          {
            case TID_LOGOTIMER:
            {
              HAB hab;

              hab = WinQueryAnchorBlock (hwnd);
              WinStopTimer (hab, hwnd, TID_LOGOTIMER);
              WinStopTimer (hab, hwnd, ID_ABOUTTIMER);
              WinDismissDlg (hwnd, TRUE);
            }
            break;

            case ID_ABOUTTIMER:
              idBitmap++;
              if(idBitmap > ID_TTBMP8)
                idBitmap = ID_TTBMP1;
              WinInvalidateRect(hwnd, &bitmapRect, FALSE);
              break;

            default:
              break;

          }

        }
        break;

//   case WM_ERASEBACKGROUND:
//     mr = (MRESULT) FALSE;
//     break;

     case WM_COMMAND:
        switch (SHORT1FROMMP(mp1))
           {
            case DID_OK:
            {
               HAB hab;

               hab = WinQueryAnchorBlock (hwnd);
               WinStopTimer (hab, hwnd, ID_ABOUTTIMER);
               WinDismissDlg (hwnd, TRUE);
            }
            break;

            default:
               break;
           }
        break;

     default:
        mr = WinDefDlgProc (hwnd, msg, mp1, mp2);
        break;
    }

 return (mr);

}

/******************************************************************************/
/*                     U T I L I T Y   F U N C T I O N S                      */
/******************************************************************************/
/******************************************************************************/
/*                                                                            */
/* fnCheckHotkey: Check if hotkey is unique.                                  */
/*                                                                            */
/******************************************************************************/

BOOL fnCheckHotkey(LONG hotkey)
{
  PACTINFO item;

  item = start;
  while( item )
  {
    if(item->hotkey == hotkey+48 && hotkey != 0)
      return(FALSE);
    item = (PACTINFO)item->next;
  }

  return(TRUE);
}

/******************************************************************************/
/*                                                                            */
/* fnCheckActivityCode: Check if activity code is unique.                     */
/*                                                                            */
/******************************************************************************/

BOOL fnCheckActivityCode(CHAR *code, CHAR *parent)
{
  PACTINFO item;

  item = start;
  while( item )
  {
    if(strcmp(code, item->code)==0 && strcmp(parent, item->parent)==0)
      return(FALSE);
    item = (PACTINFO)item->next;
  }

  return(TRUE);
}

/******************************************************************************/
/*                                                                            */
/* fnTimeControl:                                                             */
/*                                                                            */
/******************************************************************************/

float fnTimeControl(HWND hwnd, float ftime, BOOL type)
{

  LONG mmslimit, ssslimit, hh, mm, ss;
  CHAR szTime[9], szT[3];

  if(type == 0)
  {
    if( units == UNITS_MINUTES || units == UNITS_HOURS )
    {
      mmslimit = 99;
      ssslimit = 99;
      hh = ftime;
      mm = 100 * (float)(ftime - (float)hh + ROUND_OFF_1);
      WinEnableControl(hwnd, IDC_SS, FALSE);

      if(units == UNITS_MINUTES)
        strcpy(szTime, "(mmm.mm)");
      else
        strcpy(szTime, "(hhh.hh)");
    }
    else
    {
      mmslimit = 59;
      ssslimit = 59;
      /* 1.98 */
      fnConvertTime(ftime, secunits, units, szTime );
      if( units == UNITS_HMS )
      {
        fnSubstr(szTime, szT, 1, 2);
        hh = atol(szT);
        fnSubstr(szTime, szT, 4, 2);
        mm = atol(szT);
        fnSubstr(szTime, szT, 7, 2);
        ss = atol(szT);
      }
      else
      {
        fnSubstr(szTime, szT, 4, 2);
        hh = atol(szT);
        fnSubstr(szTime, szT, 7, 2);
        mm = atol(szT);
        ss = 0;
        WinEnableControl(hwnd, IDC_SS, FALSE);
      }
      strcpy(szTime, " ");
    }

    WinSetWindowText(WinWindowFromID(hwnd, IDS_TXTTIME), szTime);

    WinSendDlgItemMsg(hwnd, IDC_HH, SPBM_SETLIMITS,
                      MPFROMSHORT(9999), MPFROMSHORT(0));
    WinSendDlgItemMsg(hwnd, IDC_HH, SPBM_SETCURRENTVALUE,
                      MPFROMSHORT(hh), 0L);
    WinSendDlgItemMsg(hwnd, IDC_HH, SPBM_SETTEXTLIMIT,
                      MPFROMSHORT(4L), 0L );
    WinSendDlgItemMsg(hwnd, IDC_MM, SPBM_SETLIMITS,
                      MPFROMSHORT(mmslimit), MPFROMSHORT(0));
    WinSendDlgItemMsg(hwnd, IDC_MM, SPBM_SETCURRENTVALUE,
                      MPFROMSHORT(mm), 0L);
    WinSendDlgItemMsg(hwnd, IDC_MM, SPBM_SETTEXTLIMIT,
                      MPFROMSHORT(2L), 0L );
    WinSendDlgItemMsg(hwnd, IDC_SS, SPBM_SETLIMITS,
                      MPFROMSHORT(ssslimit), MPFROMSHORT(0));
    WinSendDlgItemMsg(hwnd, IDC_SS, SPBM_SETCURRENTVALUE,
                      MPFROMSHORT(ss), 0L);
    WinSendDlgItemMsg(hwnd, IDC_SS, SPBM_SETTEXTLIMIT,
                      MPFROMSHORT(2L), 0L );
  }
  else
  {
    WinSendDlgItemMsg(hwnd, IDC_HH, SPBM_QUERYVALUE, &hh,
                      MPFROM2SHORT(0L, 0L));
    WinSendDlgItemMsg(hwnd, IDC_MM, SPBM_QUERYVALUE, &mm,
                      MPFROM2SHORT(0L, 0L));
    WinSendDlgItemMsg(hwnd, IDC_SS, SPBM_QUERYVALUE, &ss,
                      MPFROM2SHORT(0L, 0L));
    if( units == UNITS_MINUTES || units == UNITS_HOURS )
      ftime = (float)hh + (float)mm/100;
    else
      ftime = (float)hh*60 + (float)mm + (float)ss/60 + ROUND_OFF_1;
  }

  return(ftime);
}


/******************************************************************************/
/*                                                                            */
/* fnActivityList: Add activity codes to listbox in dialog window control.    */
/*                                                                            */
/******************************************************************************/

VOID fnActivityList(HWND hwnd, CHAR *activity, CHAR *parent, LONG dlgId,
                    BOOL optNone, BOOL addDesc, ULONG type )
{

  PACTINFO item;
  LONG     i;
  CHAR     actcode[CODE_WIDTH+1];
  CHAR     actdesc[DESC_WIDTH+1];
  CHAR     szCodeDesc[CODE_WIDTH+DESC_WIDTH+4];

  i = 0;
  if(optNone)
  {
    WinLoadString(WinQueryAnchorBlock(hwnd), 0L, IDS_NONE,
                  sizeof(szTitle), szTitle);
    WinSendDlgItemMsg(hwnd, dlgId, LM_INSERTITEM, MPFROMLONG (0),
                      MPFROMP (szTitle));
    if(activity)
    {
      if(strcmp(activity, szBlank) == 0)
        WinSendDlgItemMsg (hwnd, dlgId, LM_SELECTITEM,
                           MPFROMLONG (0), MPFROMSHORT (TRUE));
    }
    else
      WinSendDlgItemMsg (hwnd, dlgId, LM_SELECTITEM,
                         MPFROMLONG (0), MPFROMSHORT (TRUE));
    i = 1;
  }

  item = start;
  while( item )
  {
    /* Only those activities that are valid based on input type parameter */
    if(type == TYPE_NORMAL ||
      (type == TYPE_NO_PARENT && strcmp(item->parent, szBlank) == 0) ||
      (type == TYPE_NO_CHILD && item->children == 0))
    {
      fnStrip(item->code, actcode, 'B', ' ');
      if(addDesc)
      {
        fnGetActivityDesc( item->code, item->parent, actdesc );
        strcpy(szCodeDesc, actcode);
        strcat(szCodeDesc, " - ");
        strcat(szCodeDesc, actdesc);
        WinSendDlgItemMsg (hwnd, dlgId, LM_INSERTITEM,
                           MPFROMLONG (i), MPFROMP (szCodeDesc));
      }
      else
        WinSendDlgItemMsg (hwnd, dlgId, LM_INSERTITEM,
                           MPFROMLONG (i), MPFROMP (item->code));
      if(activity)
      {
        if(strcmp(item->code, activity) == 0 &&
           strcmp(item->parent, parent) == 0 &&
           strcmp(activity, szBlank) != 0)
          WinSendDlgItemMsg (hwnd, dlgId, LM_SELECTITEM,
                             MPFROMLONG (i), MPFROMSHORT (TRUE));
      }
      i++;
    }
    item = (PACTINFO)item->next;
  }

}

/******************************************************************************/
/*                                                                            */
/* fnChangeParent:                                                            */
/*                                                                            */
/******************************************************************************/

VOID fnChangeParent( CHAR *oldcode, CHAR *newcode )
{

  PACTINFO item;

  item = start;
  while( item )
  {
    if(strcmp(oldcode, item->parent) == 0)
      strcpy(item->parent, newcode);
    item = (PACTINFO)item->next;
  }

}
/******************************************************************************/
/*                                                                            */
/* fnChangeParentReport: Change parent activity information based on its      */
/*                       children data. Input is parent activity code.        */
/*                                                                            */
/******************************************************************************/

VOID fnChangeParentReport( CHAR *code, PACTDATA startdata )
{

  PACTDATA item;
  PACTDATA parent = NULL;

  if(code[0] != '\0')
  {
    item = startdata;
    while(item)
    {
      if(strncmp(item->code, code, strlen(code)) == 0)
      {
        item->reptimer = (float)0.0;
        item->repcount = 0;
        parent = item;
        break;
      }
      item = (PACTDATA)item->next;
    }

    item = startdata;
    while(item && parent)       /* 1.98 */
    {
      if(strncmp(item->repparent, code, strlen(code)) == 0)
      {
        parent->reptimer = parent->reptimer + item->reptimer;
        parent->repcount = parent->repcount + item->repcount;
      }
      item = (PACTDATA)item->next;
    }

  }

}

/******************************************************************************/
/*                                                                            */
/* fnFreeReptotalList:                                                        */
/*                                                                            */
/******************************************************************************/

VOID fnFreeReptotalList( PREPTOTAL starttot )
{

  PREPTOTAL item, temp;

  item = starttot;
  while( item )
  {
    temp = (PREPTOTAL)item->next;
    free( item );
    item = temp;
  }

}

/******************************************************************************/
/*                                                                            */
/* fnReportNotes: Add two lines of notes (if any) to the report.              */
/*                                                                            */
/******************************************************************************/

VOID fnReportNotes( CHAR *szBuffer )
{
  /* 1.98 */
  if(strlen(repline1) > 0)
  {
    strcat(szBuffer, repline1);
    strcat(szBuffer, "\n");
  }
  if(strlen(repline2) > 0)
  {
    strcat(szBuffer, repline2);
    strcat(szBuffer, "\n");
  }
  if((strlen(repline1) > 0) || (strlen(repline2) > 0))
    strcat(szBuffer, " \n");

}
