:userdoc.
:h1 res=9110.PM Activity Time Tracker
:i1.General Description
:p.TIMETRAC is a 32-bit, OS/2 Presentation Manager (PM)
application which allows you to track the time you spend on your daily
activities or tasks very easily with a click of a mouse button.
The times are shown on a list and the running total time is shown
on the bottom status line along with the activity code currently being
tracked. You can optionally set how often this information is refreshed.
:p.You may also define sub-activities or sub-tasks. The total times for
all the sub-activities are added and shown on the parent activity.
:p.To select an activity from the list, click on the activity with mouse
button 1 (left mouse button). Then, click mouse button 2 (right mouse
button) to bring up a popup menu where you can start, stop or edit the
selected activity code. A faster way to start tracking the time spent on
any activity, just double click on the desired activity code. The previously
tracked activity code will stop being tracked automatically.
:p.Optionally, you can save your daily reports. To view it, just press F9.
You may customize how long the data is kept.
:p.TIMETRAC is also available for Windows 3.1.

:h1 res=9121.Automatic Start
:i1 id=start./S Option
:p.To start tracking an activity code automatically when TIMETRAC is invoked,
use the /S parameter. For example, TIMETRAC /S=ACTIVITY will start tracking
the activity code called ACTIVITY after TIMETRAC is initialized.

:h1 res=9124.Profile Location
:i1 id=prof./P Option
:p.To specify another location for the TIMETRAC profile (TIMETRAC.INI), use
the /P parameter. For example, TIMETRAC /P=D&colon.\PATH tells TIMETRAC that the
full profile path name is D&colon.\PATH\TIMETRAC.INI.

:h1 res=9125.Data Files Location
:i1 id=data./D Option
:p.To specify another location for the TIMETRAC data files (TIMETRAC.LST and
TIMETRAC.TT), use the /D parameter. For example, TIMETRAC /D=D&colon.\PATH tells
TIMETRAC that the TIMETRAC data files can be found in D&colon.\PATH.

:h1 res=9132.Output File Name
:i1 id=outname./O Option
:p.To specify another name for the TIMETRAC data file (TIMETRAC.LST by
default), use the /O parameter. For example, TIMETRAC /O=USER.LST tells
TIMETRAC that the TIMETRAC data file is named USER.LST.

:h1 res=9133.Report File Name
:i1 id=repname./R Option
:p.To specify another name for the TIMETRAC report file (TIMETRAC.TT by
default), use the /R parameter. For example, TIMETRAC /R=USER.TT tells
TIMETRAC that the TIMETRAC report file is named USER.TT.

:h1 res=9134.Comments File Name
:i1 id=comname./C Option
:p.To specify another name for the TIMETRAC comments file (TIMETRAC.CM by
default), use the /C parameter. For example, TIMETRAC /C=USER.CM tells
TIMETRAC that the TIMETRAC comment file is named USER.CM.

:h1 res=9120.Technical Notes
:i1 id=Notes.Technical Notes
:p.A few technical notes which may be helpful for those who are interested:
:ol.
:li.The system clock is used for all time processing. Therefore it is
important that your computer's system clock is accurate and is not changed
during the operation of TIMETRAC.
:li.The control file which contains the activity code and description data
is called TIMETRAC.LST with the backup file as TIMETRAC.0ST. The contents
of this control file is described as follows:
:ul.
:li.The first line which has a ! in column 1 contains the date. The first
date is in the format of mm/dd/yyyy and the next date is the julian date
in the format yyyynnn.
:li.Comment lines have a * in column 1.
:li.All other lines contain activity information in the following format:
:xmp.
  xcccccccc dddddddddddddddddddd ttt.tt nnn comments
:exmp.
:p.x is a blank character for normal activities, # indicates a hidden
activity code and @ indicates an excluded (from the total) activity code.
c is the 8 characters or less activity code. d is the 20 characters or
less activity description. t is the tracked time in the user selected units.
n is the count for the number of times the activity has been started (to
be tracked).
:eul.
:p.If you wish, you can use an ASCII editor to change the order of the
activities in this file. Just ensure that there is a CRLF sequence at the end
of each line.
:li.The report file which contains the saved tracked time records is called
TIMETRAC.TT with the backup file called TIMETRAC.0TT. The report contains
one line or record per day. Each record is in the following format:
:xmp.
  mm/dd/yyyy yyyynnn xxxx.xx u    cccccccc nnn tttt.tt    cccccccc nnn tttt.tt ...
:exmp.
:p.where xxxx.xx is the total time, u is the units (m for minutes, h for
hours, 0 for hhmmss and 2 for hhmm),
cccccccc is the activity code, tttt.tt is the activity time and nnn is
the count for the number of times the activity has been tracked.
:eol.

:h1 res=9111.Help for File
:i1 id=File.File Menu
:p.Use this choice to start and stop tracking the selected activity code.
As well, you can create a new activity code, edit or delete an existing
activity code.
Finally, you can also view the report data from this menu choice.

:h1 res=9113.Help for Report
:i2 refid=File.Report
:p.Use this choice to view previous daily reports of activity times.

:h1 res=9123.Help for Save Data
:i2 refid=File.Save Data
:p.Use this choice to save the current data into the TIMETRAC data file
called TIMETRAC.TT (see Technical Notes under the Help Index).

:h1 res=9140.Help for Start
:i2 refid=File.Start
:p.Use this choice to start tracking the selected activity code. The previously
tracked activity code will automatically be stopped being tracked.

:h1 res=9141.Help for Stop
:i2 refid=File.Stop
:p.Use this choice to stop tracking the selected activity code.

:h1 res=9114.Help for Options
:i1 id=Options.Options Menu
:p.Use this choice to refresh the tracked times, reset all the tracked times
and customize the application settings.

:h1 res=9115.Help for Settings
:i2 refid=Options.Settings...
:p.Use this choice to customize:
:ul.
:li.Time units (minutes or hours, hhmmss or hhmm time format)
:li.Refresh interval (in minutes)
:li.Display warning confirmation message boxes for Exit, Reset and Delete
:li.Initially reset all times
:li.Alarm options
:li.Report options
:li.User exit parameters
:eul.

:h1 res=9116.Help for Refresh
:i2 refid=Options.Refresh
:p.Use this choice to refresh the track times shown on the list and the
total time shown on the bottom status line of the window. Set the
Refresh time interval (you can set this from Settings) for regular automatic
refreshes.

:h1 res=9131.Help for Save Settings
:i2 refid=Options.Save Settings
:p.Use this choice to save your settings. Settings are normally saved when
you exit the application.

:h1 res=9126.Help for Fonts
:i2 refid=Options.Fonts...
:p.Use this choice to change the font used in TIMETRAC. You may select
any fixed width (monospaced) font.

:h1 res=9127.Fonts Dialog Help
:i1 id=Fonts.Fonts Dialog
:p.You may select a new font name, type and size to be used in displaying
the list of activities times in the main TIMETRAC window. Only monospaced
fonts can be selected, emphasis is ignored.

:h1 res=9118.Help for Sort
:i2 refid=Options.Sort
:p.Use this choice to select how you want to sort the activity list. You may
sort the list in ascending or descending order by:
:ul.
:li.activity code
:li.activity description
:li.time
:li.%
:li.count
:eul.
:p.The activity list will be automatically sorted everytime it is changed
unless you select No Sort.

:h1 res=9128.Help for Secondary Sort
:i2 refid=Options.Secondary Sort
:p.Use this choice to select a secondary sort for the activity list. You may
sort the list in ascending or descending order by:
:ul.
:li.activity code
:li.activity description
:li.time
:li.%
:li.count
:eul.
:p.The activity list will be automatically sorted everytime it is changed
unless you select No Sort.

:h1 res=9117.Help for Reset
:i2 refid=Options.Reset
:p.Use this choice to reset all the activity track times to 0.

:h1 res=9129.Collapse All Help
:i2 refid=Options.Collapse All
:p.Use this choice to collapse the activity list to not show any
sub-activities.

:h1 res=9130.Expand All Help
:i2 refid=Options.Expand All
:p.Use this choice to expand the activity list to show all sub-activities.

:h1 res=9142.Help for Add
:i2 refid=File.Add
:p.Use this choice to add new activities to the list.

:h1 res=9143.Help for Edit
:i2 refid=File.Edit
:p.Use this choice to edit the information for the selected activity code.

:h1 res=9144.Help for Delete
:i2 refid=File.Delete
:p.Use this choice to delete the selected activity code.

:h1 res=9148.Help for Collapse
:i2 refid=File.Collapse
:p.Use this choice to collapse a parent activity list.

:h1 res=9122.Help for User Program
:i2 refid=File.User Program
:p.If you specified a program in the User Exit dialog window, the menu
text is shown. Click on this menu item to invoke the program you specified.

:h1 res=9145.Help for Ex/Include
:i1 id=Exclude.Ex/Include
:p.Use this choice to exclude or include the time of the selected activity code
to the total time shown on the bottom status area. Excluded activity codes
are shown with a '@' beside the activity code.
:p.Those that are both hidden and excluded are indicated with a '%'.

:h1 res=9146.Help for Hide/Show
:i1 id=Hide.Hide/Show
:p.Use this choice to hide or show the selected activity code from the
activity list. Hidden activity codes are shown with a '#' beside the
activity code if shown on the activity list.
:p.Those that are both hidden and excluded are indicated with a '%'.

:h1 res=9147.Help for Transfer
:i1 id=Transfer.Transfer
:p.Use this choice to transfer all or part of the time and count
from the selected activity code to another activity code.
:p.Note: You cannot transfer to or from an activity which has sub-activities.

:h1 res=9149.Help for Reset
:i1 id=ResetIt.Reset Activity
:p.Use this choice to reset for the time and count for the selected
activity code.
:p.Note: You cannot reset an activity which has sub-activities.

:h1 res=9410.Settings Help
:i1 id=Settings.Settings
:p.You may customize several options settings from the Settings dialog
window:
:ul.
:li.Time units (minutes or hours in decimal, hh.mm.ss or hh&colon.mm&colon.ss)
:li.Date format
:li.Refresh interval
:li.Display warning confirmation message boxes for Exit, Reset and Delete
:li.Initially reset all times
:li.Report options
:li.Alarm options
:li.User exit parameters
:eul.
:p.Select Default to restore the settings to the original system defaults.

:h1 res=9411.Units Help
:i2 refid=Settings.Units
:p.You may select which units are to be used in the application. The
following units are available:
:ul.
:li.Minutes (in decimal notation)
:li.Hours (in decimal notation)
:li.hh mm ss
:li.hh mm
:eul.

:h1 res=9420.Date Format Help
:i2 refid=Settings.Date Format
:p.Use the OS/2 System Settings (Country) to select the date format display.

:h1 res=9412.Refresh Interval Help
:i2 refid=Settings.Refresh Interval
:p.Click on the spin button to set the automated refresh interval time in
minutes. Set to 0 for no automatic refreshes. If you want to refresh the
information immediately, select Refresh under the Options menu bar choice.

:h1 res=9476.Save to File on Refresh Help
:i2 refid=Settings.Save to File on Refresh
:p.If your machine slows down during the automated refreshes, click off or
do not select this option. The data will not be saved to the control file
during the automated refreshes. The danger is that if
TIMETRAC terminates abnormally, the control file may be out of date.
:p.By default, click on to ensure full data integrity at all times.

:h1 res=9413.Exit Confirmation Help
:i2 refid=Settings.Exit Confirmation
:p.Click on to display an Exit confirmation dialog box when you exit TIMETRAC.

:h1 res=9418.Delete Confirmation Help
:i2 refid=Settings.Delete Confirmation
:p.Click on to display an Delete confirmation dialog box whenever you delete an
activity code.

:h1 res=9419.Reset Confirmation Help
:i2 refid=Settings.Reset Confirmation
:p.Click on to display an Reset confirmation dialog box whenever you request to
reset all activity times to 0.

:h1 res=9428.Reset for New Day Confirmation Help
:i2 refid=Settings.Reset for New Day Confirmation
:p.Click on to display an Reset confirmation dialog box you bring up TIMETRAC
during the day which warns you that the activity times have not been reset.

:h1 res=9415.Use Exclusions Help
:i2 refid=Settings.Use Exclusions
:p.Click on Use Exclusions to exclude the track times for activity codes that
have been marked as Exclude from the total time. Click off to include
all activity codes irregardless.
:p.Excluded activity codes
are shown with a '@' beside the activity code.
Those that are both hidden and excluded are indicated with a '%'.

:h1 res=9421.Use Hidden Help
:i2 refid=Settings.Use Hidden
:p.Click on Use Hidden to hide the activity codes that have been marked as
hidden from the activity list. Click off to show all hidden (if any) activity
codes.
:p.Hidden activity codes
are shown with a '#' beside the activity code if shown on the activity
list. Those that are both hidden and excluded are indicated with a '%'.

:h1 res=9416.Initial Reset Help
:i2 refid=Settings.Initial Reset
:p.Click on to initially reset all activity track times to 0 when TIMETRAC
is initially started.

:h1 res=9425.Minimize Help
:i2 refid=Settings.Minimize
:p.Click on to automatically minimize TIMETRAC when you start tracking an
activity code.

:h1 res=9426.Startup Activity Help
:i2 refid=Settings.Default Startup Activity
:p.Select an activity code which will be tracked by default when you first
invoke TIMETRAC. You can override this by using the /S command line parameter.

:h1 res=9427.Special Window Help
:i2 refid=Settings.Special Window
:p.Click on to invoke TIMETRAC without a title bar, menu bar and heading
information. With a smaller window, you can see more activity codes in
the list.
:p.A change to this option setting will take effect the next time you
invoke TIMETRAC.
:p.Hint: You will not be able to position the window easily without the
title bar, so before selecting this option, position the TIMETRAC window
first.

:h1 res=9430.Blank Comments Help
:i2 refid=Settings.Blank Comments
:p.Click on to automatically blank out all activity comments at the start
of a new day.

:h1 res=9460.Automatically Collapse
:i2 refid=Settings.Automatically Collapse
:p.Click on to always collapse the parent activity when a sub-activity is
started.

:h1 res=9462.No Focus Change Help
:i2 refid=Settings.No Focus Change
:p.Click on to disable window focus change.

:h1 res=9464.Sub-activity Window Help
:i2 refid=Settings.Sub-activity Window
:p.Click on to show sub-activities in its own window instead of expanding
the activity list.

:h1 res=9417.Report Help
:i2 refid=Settings.Report
:p.Click on to save the activity track times on a daily basis. You may then
customize how long these will be kept by clicking on the spin button for
days to save. For example, if you select 7 days, only daily reports for the
past week will be kept in the report file.

:h1 res=9434.Notes Help
:i2 refid=Settings.Notes
:p.Type any text (up to 80 characters) which will be shown at the top of
the report.

:h1 res=9422.Add Descriptions Help
:i2 refid=Settings.Add Descriptions
:p.Click on to display activity descriptions in the report.

:h1 res=9429.Add Comments Help
:i2 refid=Settings.Add Comments
:p.Click on to display activity comments in the report. Note that comments
will not be shown if report totals are selected in the Report List.

:h1 res=9432.Report Details Help
:i2 refid=Settings.Report Details
:p.Click on to show sub-activity codes in the report.

:h1 res=9423.Use Excluded Flags Help
:i2 refid=Settings.Use Excluded Flags
:p.Click on to include excluded activity codes in the report.

:h1 res=9424.Use Hidden Flags Help
:i2 refid=Settings.Use Hidden Flags
:p.Click on to include hidden activity codes in the report.

:h1 res=9433.Show 0 Times
:i2 refid=Settings.Show 0 Times
:p.Click on to include activities with 0 times in the report.

:h1 res=9452.Default Alarm Interval Help
:i2 refid=Settings.Default Alarm Interval
:p.Click on the spin button to set the alarm interval time in minutes. Set
the alarm interval to 0 if you do not want any alarm reminders.

:h1 res=9463.Default Alarm Expiry Help
:i2 refid=Settings.Default Alarm Expiry
:p.Click on the spin button to set the alarm expiry time in minutes,
default is 1 minute.

:h1 res=9453.Sound Alarm Help
:i2 refid=Settings.Sound Alarm
:p.Click on to sound a beep when the alarm reminder has expired.

:h1 res=9454.Display Message Help
:i2 refid=Settings.Display Message
:p.Click on to display a message box when the alarm reminder has expired. You
will be asked if you want to continue to track the current activity code.

:h1 res=9455.Default Help
:i2 refid=Settings.Default
:p.Select this push button to restore all alarm settings to the
original system default values.

:h1 res=9456.Edit When Expired Help
:i2 refid=Settings.Edit When Expired
:p.Click on this option to automatically bring up the edit dialog window
when the alarm expires.

:h1 res=9457.Default Activity Help
:i2 refid=Settings.Default Activity
:p.Select an activity code which will be tracked by default when the alarm
expires and you have not responded within a minute. For example, create
an activity code called AWAY (Away from my desk) and use as the default
activity code so that when the alarm expires when you are not at your
desk to respond to the prompt, the AWAY activity code tracked automatically.

:h1 res=9461.Currect Activity Help
:i2 refid=Settings.Current Activity
:p.Click on if you want the current activity to be tracked when the alarm
expires and you have not responded within a minute.

:h1 res=9458.Set Alarm Interval Help
:i2 refid=Settings.Set Alarm Interval
:p.Select this option if you want to be given the option of changing the
default alarm interval when you start tracking a new activity code.

:h1 res=9472.Menu Text Help
:i2 refid=Settings.Menu Text
:p.Type the text which you want to display as the last item in the
File pull-down. You must specify both Menu text and Program name.

:h1 res=9473.Program Name Help
:i2 refid=Settings.Program Name
:p.Type the full path and name of the program you want to access from TIMETRAC
as the user exit. You must specify both Menu text and Program name.

:h1 res=9474.Parameters Help
:i2 refid=Settings.Parameters
:p.Type any parameters which the user exit program accepts.

:h1 res=9475.Clear Help
:i2 refid=Settings.Clear
:p.Click on Clear to set all the fields in the User Exit dialog window to
blank.

:h1 res=9201.Edit Dialog Help
:i1 id=EditDlg.Edit Dialog
:p.You may modify the activity information from the Edit dialog window. You
may change:
:ul.
:li.Activity code (8 characters or less)
:li.Activity description (20 characters or less)
:li.Tracked time
:li.Exclude or include to total time
:li.Hide or show from activity list
:eul.
:p.After making all the changes, click on Ok.

:h1 res=9202.Activity Code Help
:i2 refid=EditDlg.Activity Code
:p.Type 8 characters or less for the activity code.

:h1 res=9203.Description Help
:i2 refid=EditDlg.Activity Description
:p.Type 20 characters or less for the activity description.

:h1 res=9204.Time Help
:i2 refid=EditDlg.Time
:p.According to your default units setting, click on the spin buttons to
indicate a new track time either in
minutes or hours and up to two decimal places, or hh.mm.ss or
hh&colon.mm&colon.ss.

:h1 res=9205.Exclude Help
:i2 refid=EditDlg.Exclude
:p.Click on Exclude from total time to exclude the track times for this
activity code from the total. You have also have set Use Exclusions under
Settings.
:p.Excluded activity codes
are shown with a '@' beside the activity code.
Those that are both hidden and excluded are indicated with a '%'.

:h1 res=9206.Hide Help
:i2 refid=EditDlg.Hide
:p.Click on Hide from list to hide this activity code from the
activity list. You have also have set Use Hidden under Settings.
:p.Hidden activity codes
are shown with a '#' beside the activity code if shown on the activity
list. Those that are both hidden and excluded are indicated with a '%'.

:h1 res=9207.Count Help
:i2 refid=EditDlg.Count
:p.Click on Count spinbutton up or down arrows to change the number of times
this activity code was (started to be) tracked.

:h1 res=9208.Lock Help
:i2 refid=EditDlg.Lock
:p.Click on Lockup when startup to automatically lock the WPS (OS/2 DeskTop)
when this activity code is started to be tracked. This is ideal for activity
codes for meetings, breaks, lunch, etc. when you have to leave your desk.

:h1 res=9209.Comments Help
:i2 refid=EditDlg.Comments
:p.Type 30 characters or less comments for this activity. The comments
will be displayed in the report.

:h1 res=9210.Program Help
:i2 refid=EditDlg.Program
:p.Type the full path and name of the program you want to automatically
execute when this activity is started.

:h1 res=9211.Parameters Help
:i2 refid=EditDlg.Parameters
:p.Type any parameters which the program accepts. For REXX programs, put
CMD.EXE in the Program field and /C REXX.CMD in the Parameters field.

:h1 res=9212.Quick Key Help
:i2 refid=EditDlg.Quick Key
:p.Click on the spin button to select a "quick key" which allows
you to start tracking the activity code by pressing a Ctrl-# (1-9) key
combination. 0 indicates no quick key for this activity.

:h1 res=9213.Focus Help
:i2 refid=EditDlg.Window Focus
:p.Type 20 characters or less the window title to get the focus when
this activity is started.

:h1 res=9214.Parent Help
:i2 refid=EditDlg.Parent
:p.Select a parent activity code from the list if this is a sub-activity
of the parent activity.

:h1 res=9215.Alarm Interval Help
:i2 refid=EditDlg.Alarm Interval
:p.Click on the spin button to select an alarm interval when tracking
this activity. This value overrides the general Alarm Interval setting
unless it is 0.

:h1 res=9301.Add Dialog Help
:i1 id=AddDlg.Add Dialog
:p.You can add new activity codes to the list using the Add dialog window. You
need to enter the following information:
:ul.
:li.Activity code
:li.Activity description
:li.Comments
:li.Exclude or include to total time
:li.Hide or show from activity list
:li.Startup options (lockup, program to run, quick key)
:eul.
:p.The initial track time is automatically set to 0. Use Edit if you want
change it.
:p.Click on Ok if you have completed with all the additions. Click on Save
if you want to save and continue adding more activity codes.
:h1 res=9302.Activity Code Help
:i2 refid=AddDlg.Activity Code
:p.Type 8 characters or less for the activity code.

:h1 res=9303.Description Help
:i2 refid=AddDlg.Activity Description
:p.Type 20 characters or less for the activity description.

:h1 res=9304.Exclude Help
:i2 refid=AddDlg.Exclude
:p.Click on Exclude from total time to exclude the track times for this
activity code from the total. You have also have set Exclusions to Total.
:p.Excluded activity codes
are shown with a '@' beside the activity code.
Those that are both hidden and excluded are indicated with a '%'.

:h1 res=9306.Hide Help
:i2 refid=AddDlg.Hide
:p.Click on Hide from list to hide this activity code from the
activity list. You have also have set Use Hidden under Settings.
:p.Hidden activity codes
are shown with a '#' beside the activity code if shown on the activity
list. Those that are both hidden and excluded are indicated with a '%'.

:h1 res=9307.Lock Help
:i2 refid=AddDlg.Lock
:p.Click on Lockup when startup to automatically lock the WPS (OS/2 DeskTop)
when this activity code is started to be tracked. This is ideal for activity
codes for meetings, breaks, lunch, etc. when you have to leave your desk.

:h1 res=9308.Comments Help
:i2 refid=AddDlg.Comments
:p.Type 30 characters or less comments for this activity. The comments
will be displayed in the report.

:h1 res=9309.Program Help
:i2 refid=AddDlg.Program
:p.Type the full path and name of the program you want to automatically
execute when this activity is started.

:h1 res=9310.Parameters Help
:i2 refid=AddDlg.Parameters
:p.Type any parameters which the program accepts. For REXX programs, put
CMD.EXE in the Program field and /C REXX.CMD in the Parameters field.

:h1 res=9311.Quick Key Help
:i2 refid=AddDlg.Quick Key
:p.Click on the spin button to select a "quick key" which allows
you to start tracking the activity code by pressing a Ctrl-# (1-9) key
combination. 0 indicates no quick key for this activity.

:h1 res=9312.Focus Help
:i2 refid=AddDlg.Window Focus
:p.Type 20 characters or less the window title to get the focus when
this activity is started.

:h1 res=9305.Save Help
:i2 refid=AddDlg.Save
:p.After entering all the required information, click on Save to save the
data.

:h1 res=9313.Parent Help
:i2 refid=AddDlg.Parent
:p.Select a parent activity code from the list if this is a sub-activity
of the parent activity.

:h1 res=9314.Alarm Interval Help
:i2 refid=AddDlg.Alarm Interval
:p.Click on the spin button to change the alarm interval when tracking
this activity. This value overrides the general Alarm Interval setting
unless it is 0.

:h1 res=9501.Report List Help
:i1 id=Replist.Report List
:p.A list of daily reports are shown in the Report List dialog window. Select
one or more reports and click on Ok to display the selected reports.

:h1 res=9502.All Help
:i2 refid=Replist.All
:p.Click on All to quickly select all the reports shown on the list.

:h1 res=9503.None Help
:i2 refid=Replist.None
:p.Click on None to quickly select no reports.

:h1 res=9505.Delete Help
:i2 refid=Replist.Delete
:p.Click on Delete to delete the selected reports.

:h1 res=9504.Total Help
:i2 refid=Replist.Total
:p.Click on Total to display a summary of the selected reports (showing
totals) instead of individual reports.

:h1 res=9551.Report Help
:i1 id=Report.Report
:p.The selected daily report(s) is/are shown on the Report dialog window. Click
on the scrolling arrows to scroll up or down. Click on Close when you are
finished viewing the report(s).
:p.The report displays the activity description (optional),
activity code, number of times tracked, time and % of total time.
:p.Click on the Save push button to save the report to a file on your PC.
:p.Click on the Print push button to print the report to your PC printer
attached to the LPT1 port. The printed report is very simple and does not
contain any page breaks.

:h1 res=9571.Alarm Reminder Help
:i1 id=Alrmrem.Alarm Reminder Dialog
:p.The alarm has expired. Click on Stop to stop tracking the current activity
or click on Continue otherwise. If you do not respond within one minute and
you have selected a default activity, the default activity will be
automatically tracked. If you have not selected a default activity, then
this window will be displayed until you respond.

:h1 res=9581.Set Alarm Interval Help
:i1 id=Alrmchg.Set Alarm Interval Dialog
:p.This window has been displayed because you selected the option to Set
Alarm Interval under Settings. You may change the alarm interval for
this specific instance. Click on Ok to start tracking the selected activity
code.

:h1 res=9582.Alarm Interval Help
:i2 refid=Alrmchg.Alarm Interval
:p.Click on the spin button to set the alarm interval time in minutes. Set
the alarm interval to 0 if you do not want any alarm reminders. This will
only change the alarm interval for this specific instance, the default
alarm interval will remain the same.

:h1 res=9601.Save Report Help
:i1 id=Saverep.Save Report Dialog
:p.Type the full path filename where you want the report to be stored. Click
on Save to actually save the file.

:h1 res=9651.Transfer Help
:i1 id=Trans.Transfer Dialog
:p.This window allows you to transfer the all or part of the time from
the selected activity code to any other activity code.

:h1 res=9652.Time Help
:i2 refid=Trans.Time
:p.To transfer all the time from the selected activity code, do not change
this field. Otherwise, click on the spin buttons to indicate
the partial amount of time to be transfered.

:h1 res=9654.Count Help
:i2 refid=Trans.Count
:p.To transfer all the count from the selected activity code, do not change
this field. Otherwise, click on the spin buttons to indicate
the partial amount of count to be transferred.

:h1 res=9653.To Help
:i2 refid=Trans.To
:p.Select an activity code to transfer the amount of time and count
specified. Click on the drop-down button and select an activity code.

:h1 res=9655.Add 1 to Count Help
:i2 refid=Trans.Add 1 to Count
:p.Click on if you only want to add 1 to the count of the activity being
transferred.

:h1 res=9701.Change Data Help
:i1 id=CreaDat.Change Data Dialog
:p.This window has been displayed because you selected the option to Change
data. Use this option if you want to create data for a day in which you
were not able to use TIMETRAC to track your activity times (for example, you
were on vacation or on course). As well, you can modify the existing data
for any day.
:p.First, set the desired date you want to create the data for. If you
want to change the data an existing report, click on Retrieve first.
:p.You can then
change the time and count for each activity code by selecting the
desired activity code from the list. The selected
activity code is displayed just above the time. As well, the total time
is also calculated and displayed below the count.
:p.After you have made all your changes, click on Save to save the data into
the report file.

:h1 res=9702.Date Help
:i2 refid=CreaDat.Date
:p.Click on the spin buttons to set the desired date.

:h1 res=9703.Activity List Help
:i2 refid=CreaDat.Activity List
:p.Select an activity code by double clicking on one of the activity codes
shown on the list. Then you can change the time and count for that activity.

:h1 res=9704.Time Help
:i2 refid=CreaDat.Time
:p.According to your default units setting, click on the spin buttons to
indicate a new track time either in
minutes or hours and up to two decimal places, or hh.mm.ss or
hh&colon.mm&colon.ss.

:h1 res=9705.Count Help
:i2 refid=CreaDat.Count
:p.Click on Count spinbutton up or down arrows to change the number of times
this activity code was (started to be) tracked. Default is 0.

:h1 res=9706.Retrieve Help
:i2 refid=CreaDat.Retrieve
:p.Click on Retrieve push button after you have set the date to get the data
for an existing report.

:h1 res=9707.Comments Help
:i2 refid=CreaDat.Comments
:p.Type 30 characters or less comments for this activity. The comments
will be displayed in the report.

:h1 res=9708.Parent Help
:i2 refid=CreaDat.Parent
:p.Type the parent activity if this is a sub-activity.

:h1 res=9180.Help for Help
:i1 id=Help.Help Menu
:p.Use this choice to get help for the application. You may
request an index of help choices, general help for the application,
help for the supported function keys, or a brief description about the
application.

:h1 res=9182.Help for Help Index
:i2 refid=Help.Help Index
:p.Use this choice to get an index of available help topics.

:h1 res=9183.Help for General Help
:i2 refid=Help.General Help
:p.Use this choice to get general help for the whole application.

:h1 res=9184.Help for Using Help
:i2 refid=Help.Using Help
:p.Use this choice to get help in using the help subsystem itself.

:h1 res=9185.Help for Keys Help
:i2 refid=Help.Keys Help
:p.Use this choice to get help for the supported function keys.

:h1 res=9186.Help for Product Information
:i2 refid=Help.Product Information
:p.Use this choice to get a brief description of this program.

:h1 res=9187.Keys Help
:i1 id=keys.Keys
:p.The following keystrokes are valid in this application:
:table cols='8 20' rules=both frame=box.
:row.
:c.Key
:c.Description
:row.
:c.Ctrl+A
:c.Add
:row.
:c.Ctrl+C
:c.Create data
:row.
:c.Ctrl+D
:c.Delete
:row.
:c.Ctrl+E
:c.Edit
:row.
:c.Ctrl+F
:c.Fonts
:row.
:c.Ctrl+I
:c.Toggle Hide/Show
:row.
:c.Ctrl+M
:c.Collapse
:row.
:c.Alt+R
:c.Reset
:row.
:c.Ctrl+N
:c.Transfer
:row.
:c.Ctrl+R
:c.Reset (selected activity only)
:row.
:c.Alt+S
:c.Settings
:row.
:c.Ctrl+S
:c.Start
:row.
:c.Ctrl+T
:c.Stop
:row.
:c.Ctrl+U
:c.User exit
:row.
:c.Ctrl+V
:c.Save data
:row.
:c.Ctrl+X
:c.Toggle Exclude/Include
:row.
:c.F1
:c.Help
:row.
:c.F2
:c.Refresh
:row.
:c.F9
:c.Report
:etable.
:euserdoc.
