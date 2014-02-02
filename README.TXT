                              TIMETRAC Version 1.9
                            PM Activity Time Tracker
                                      by
                                 Ric Zapanta


DESCRIPTION:

TIMETRAC is a 32-bit, multi-threaded OS/2 Presentation Manager (PM) application
written in C which allows you to track the time you spend on your many different
activities during the day. At the end of the day or the week, you now have very
accurate data to input into whatever time reporting system in your site.

After you have entered all the activities you want to track, simply double-click
on the desired activity to begin tracking it. Other features of TIMETRAC
include:

  - Fully customizable options (lots!)
  - View and save daily reports
  - Exclude activities from total time
  - Sub-activities
  - Automated window refresh (based on desired interval time)
  - Hide selected activities from list
  - Alarm reminder facility
  - Counter for number of times an activity has been tracked
  - Comments
  - Invoke a program automatically when activity started
  - Full sort support
  - Access another program/application (ie. time reporting system, like
      PMWARS) directly from TIMETRAC

You may start TIMETRAC using the following optional parameters:

  TIMETRAC /S=activity /P=d:\path /D=d:\path

/S specifies that activity will be automatically tracked when TIMETRAC
is invoked, /P specifies the location of the TIMETRAC profile settings
file and /D specifies the location of the TIMETRAC data files.


INSTALLATION:

Receive TIMETRAC EXEBIN to your PC as TIMETRAC.EXE. Receive TIMETRAC HLPBIN to
your PC as TIMETRAC.HLP and place in HELP path.

   RECEIVE TIMETRAC.EXE h:TIMETRAC EXEBIN *
   RECEIVE TIMETRAC.HLP h:TIMETRAC HLPBIN *
   RECEIVE TIMETRAC.XXX h:TIMETRAC XXX    * (ASCII CRLF

   where h: is your host terminal session, eg. A: or B:

Rename TIMETRAC.XXX to TIMETRAC.LST before you start if you are a
new TIMETRAC user.


GETTING STARTED:

Below are the steps to get you started to use TIMETRAC:

1) Click on the File menu, then click on Add... (or just press Ctrl-A).
2) In the Add Activity Code window, type in an activity code (8 character
   or less) and activity description. You may optionally fill in the rest
   of the activity information. For sub-activities, select a parent
   activity.
3) Click on Save.
4) You can continue to add new activity codes, when you are done, click
   on Ok.
5) The activity code(s) you just added should now show on the main TIMETRAC
   window. All times, % and counts should be 0.
6) There are many ways to start tracking an activity code:
     - Double click on the activity code
     - Left click on the activity code, click on the File menu and click
       on the Start option
     - Right click on the activity code to bring up the popup menu and
       click on the Start option
     - Use just the keyboard, use the arrow keys to select the activity
       code and press Enter or Ctrl-S.
     - Use the Quick key combination

The status line is shown on the bottom of the window which displays the
date, total time and the activity code being tracked (if none, it should
say "Stopped").

There are many other options available, you can find them in both the
File and Options menus.

