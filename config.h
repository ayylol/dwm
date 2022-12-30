/* See LICENSE file for copyright and license details. */
//
/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 10, .gappx = 10};
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "FiraCode Nerd Font:size=12:antialias=true" };
static const char dmenufont[]       = "FiraCode Nerd Font:size=18:antialias=true";

static const char col_gray1[]	    = "#282828";
static const char col_gray2[]       = "#282828";
static const char col_gray3[] 	    = "#d2b979";
static const char col_gray4[] 	    = "#282828";
static const char col_cyan[] 	    = "#d2b979";

/*
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#008899";
*/
static const char col_red[]         = "#FF0000";
static const char col_orange[]      = "#FF8800";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeScratchSel]  = { col_gray4, col_cyan,  col_red  },
	[SchemeScratchNorm] = { col_gray4, col_cyan,  col_orange },
};

/* Autostart */
static const char *const autostart[] = {
  "sh", "-c", "autostart", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; 

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class        instance  title    tags mask    isfloating   monitor      float x,y,w,h    floatborderpx   Scratchkey*/
	{ "Gimp",       NULL,     NULL,    0,           1,           -1,         240,110,1440,860,     2,          0},
  // OpenGL test programs
	{ "DEBUG",      NULL,     NULL,    0,           1,           -1,         530,110,860,860,     2,          0 },

  // Godot Rules
	{ "Godot",      NULL,     "DEBUG", 0,           1,           -1,         240,110,1440,860,     2,          0}, // Needs update rules patch probably
  // Steam Rules
	{ "Steam",      NULL,     NULL,    0,           1,           -1,         240,110,1440,860,     2,          0},
	{ "Steam",      "Steam",  "Steam", 0,           0,           -1,         240,110,1440,860,     2,          0},// Unfloats main screen
	{ "Steam",      "Steam",  "News",  0,           1,           -1,         240,110,1440,860,     2,          0}, // floating other stuff with Steam in title
	{ "Steam",      "Steam",  "Info",  0,           1,           -1,         240,110,1440,860,     2,          0},
  // ScratchPads
	{ "ncspot",     NULL,     NULL,    0,           1,           -1,         240,110,1440,860,     4,          'n' },
	{ "calcurse",   NULL,     NULL,    0,           1,           -1,         240,110,1440,860,     4,          'e' },
	{ "btop",       NULL,     NULL,    0,           1,           -1,         240,110,1440,860,     4,          'x' },
	{ NULL,  "keepassxc",     NULL,    0,           0,           -1,         240,110,1440,860,     4,          'z' },
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
// for single monitors
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

// Program launching
static const char *dmenucmd[]     = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-l", "15", NULL };
static const char *termcmd[]      = { "kitty", NULL };
static const char *browsercmd[]   = { "firefox", NULL };
static const char *filecmd[]      = { "kitty", "--class", "ranger", "ranger", NULL };
static const char *discordcmd[]   = { "discord", NULL }; 
static const char *screenkeycmd[] = { "togglesk", NULL };

// Scratch Pads
static const char *spncspot[] = {"n", "kitty", "--class", "ncspot", "ncspot", NULL};
static const char *spcal[] = {"e", "kitty", "--class", "calcurse", "calcurse", NULL};
static const char *spbtop[] = {"x", "kitty", "--class", "btop", "btop", NULL};
static const char *sppm[] = { "z", "keepassxc", NULL };

// dmenu scripts
static const char *mountcmd[]     = { "dmenumount", NULL };
static const char *umountcmd[]    = { "dmenuumount", NULL };
static const char *vpncmd[]       = { "dmenunordvpn", NULL };

// Screenshots
static const char *sectioncmd[]   = { "flameshot", "gui", NULL };
static const char *screencmd[]    = { "flameshot", "screen", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	/*------------------------------TAGS/VIEWS----------------------------------*/
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
 	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, 
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
  
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
  
	/*--------------------------PROGRAMS/SHORTCUTS------------------------------*/
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_r,      spawn,          {.v = filecmd } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = discordcmd } },
	{ MODKEY,	                XK_s,      spawn,          {.v = sectioncmd } },
	{ MODKEY|ShiftMask,           	XK_s,      spawn,          {.v = screencmd } },
	{ MODKEY,                       XK_v,      spawn,          {.v = vpncmd } },
	{ MODKEY,                       XK_u,      spawn,          {.v = mountcmd } },
	{ MODKEY|ControlMask,           XK_u,      spawn,          {.v = umountcmd } },
	{ MODKEY,                       XK_c,      spawn,          {.v = screenkeycmd } },
  // Scratch Pads
	{ MODKEY,                       XK_n,      togglescratch,  {.v = spncspot } },
	{ MODKEY,                       XK_e,      togglescratch,  {.v = spcal } },
	{ MODKEY,                       XK_x,      togglescratch,  {.v = spbtop } },
	{ MODKEY,                       XK_z,      togglescratch,  {.v = sppm } },

	/*-----------------------------MOVE/RESIZE----------------------------------*/
	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
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

