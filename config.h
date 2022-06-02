/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const double defaultopacity  = 1;

static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */

static const char *fonts[]          = { "DejaVu Sans:size=10", "FontAwesome:pixelsize=18:antialias=true:autohint=true"};
static const char dmenufont[]       = "DejaVu Sans:size=10";

static const char fg[]         = "#ebdbb2";
static const char bg[]         = "#222222";
static const char acc[]        = "#504945";

static const char *colors[][3]      = {
	/*                   fg  bg   border */
	[SchemeNorm]     = { fg, bg,  bg  },
	[SchemeSel]      = { fg, acc, acc },
	[SchemeHid]      = { fg, bg, "#000000" },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance    title       tags mask   isfloating  isterminal  noswallow  monitor */
	{ "firefox",         NULL,      NULL,       0,          0,          0,           0,        -1 },
	{ "Google-chrome",   NULL,      NULL,       0,          0,          0,           0,        -1 },
	{ "Chromium",        NULL,      NULL,       0,          0,          0,           0,        -1 },
	{ "SpeedCrunch",     NULL,      NULL,       0,          1,          0,           0,        -1 },
	{ "Safeeyes",        NULL,      NULL,       0,          1,          0,           0,        -1 },
	{ "st-256color",     NULL,      NULL,       0,          0,          1,           0,        -1 },
	{ NULL,       NULL,       "Event Tester",   0,          0,          0,           1,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       56,      togglebar,      {0} }, // b
	{ MODKEY,                       44,      focusstack,     {.i = +1 } }, // j
	{ MODKEY,                       45,      focusstack,     {.i = -1 } }, // k
	{ MODKEY,                       31,      incnmaster,     {.i = +1 } }, // i
	{ MODKEY,                       30,      incnmaster,     {.i = -1 } }, // u
	{ MODKEY,                       43,      setmfact,       {.f = -0.05} }, // h
	{ MODKEY,                       46,      setmfact,       {.f = +0.05} }, // l
	{ MODKEY|ShiftMask,             43,      setcfact,       {.f = +0.25} }, // h
	{ MODKEY|ShiftMask,             46,      setcfact,       {.f = -0.25} }, // l
	{ MODKEY|ShiftMask,             32,      setcfact,       {.f =  0.00} }, // o
	{ MODKEY|ShiftMask,             44,      pushdown,       {0} }, // j
	{ MODKEY|ShiftMask,             45,      pushup,         {0} }, // k
    { MODKEY|ShiftMask,             36,      zoom,           {0} }, // return
	{ MODKEY,                       23,      view,           {0} }, // tab
	{ MODKEY,                       24,      killclient,     {0} }, // q
	{ MODKEY,                       28,      setlayout,      {.v = &layouts[0]} }, // t
	{ MODKEY,                       41,      setlayout,      {.v = &layouts[1]} }, // f
 	{ MODKEY|ControlMask,           41,      togglefullscreen, {0} }, // f
 	{ MODKEY|ShiftMask,             41,      togglefakefullscreen, {0} }, // f
	{ MODKEY,                       55,      setlayout,      {.v = &layouts[2]} }, // v
	{ MODKEY,                       65,      setlayout,      {0} }, // space
	{ MODKEY|ShiftMask,             65,      togglefloating, {0} }, // space
	{ MODKEY,                       19,      view,           {.ui = ~0 } }, // 0
	{ MODKEY|ShiftMask,             19,      tag,            {.ui = ~0 } }, // 0
	{ MODKEY,                       59,      focusmon,       {.i = -1 } }, // ,
	{ MODKEY,                       60,      focusmon,       {.i = +1 } }, // .
	{ MODKEY|ShiftMask,             59,      tagmon,         {.i = -1 } }, // ,
	{ MODKEY|ShiftMask,             60,      tagmon,         {.i = +1 } }, // .
	TAGKEYS(                        10,                      0) // 1
	TAGKEYS(                        11,                      1) // 2
	TAGKEYS(                        12,                      2) // 3
	TAGKEYS(                        13,                      3) // 4
	TAGKEYS(                        14,                      4) // 5
	TAGKEYS(                        15,                      5) // 6
	TAGKEYS(                        16,                      6) // 7
	TAGKEYS(                        17,                      7) // 8
	TAGKEYS(                        18,                      8) // 9
	{ MODKEY|ShiftMask,             26,      quit,           {0} }, // e
	{ MODKEY|ShiftMask,             27,      spawn,          SHCMD("killall dwmblocks 2>/dev/null ; dwmblocks &") }, // r
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
   	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
 	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
 	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} }, 
 	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} }, 
 	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} }, 
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button4,        focusstack,     {-1} },
	{ ClkWinTitle,          0,              Button5,        focusstack,     {+1} },
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
