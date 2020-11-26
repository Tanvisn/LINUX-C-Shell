#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>

#include <sys/stat.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "pinfo.h"
#include "cd.h"
#include "prompt.h"
#include "echo.h"
#include "pwd.h"
#include "ls.h"
#include "background.h"
#include "foreground.h"
#include "history.h"
#include "pipeline.h"
#include "settingenv.h"
#include "unsettingenv.h"
#include "jobs.h"
#include "kjob.h"
#include "overkill.h"
#include "bg.h"
#include "fg.h"
#include "setInOut.h"
#include "commands.h"
#include "executecom.h"

extern char home[100];
extern char buffer[100005];
extern char his_path[1005];
extern char file_in[1005];
extern char file_out[1005];
extern int job_number[100005];
extern int job_idx;
extern int cd_idx;
extern int myshellid;
extern int curforid;
extern char curforname[105];
extern int flag_pipe;
extern int flag_replace;
extern int last_pipe;

struct job_name
{
	char name[505];
};

typedef struct job_name job_name;

job_name jname[100005];

struct cd_name
{
	char name[505];
};

typedef struct cd_name cd_name;

cd_name cd_args[100005];
