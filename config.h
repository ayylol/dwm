/* See LICENSE file for copyright and license details. */
//
/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#008899";
//static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* Autostart */
static const char *const autostart[] = {
  "sh", "-c", "autostart", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; // for single monitors

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class        instance  title    tags mask     isfloating   monitor */
	{ "Gimp",       NULL,     NULL,    0,            1,           -1 },
	{ "ncspot",     NULL,     NULL,    1 << 8,       0,            1 },
	{ "calcurse",   NULL,     NULL,    1 << 0,       0,            0 },
  // Godot Rules
	{ "Godot",      NULL,     "DEBUG", 0,            1,           -1 }, // Needs update rules patch probably
  // Steam Rules
	{ "Steam",      NULL,     NULL,    0,            1,           -1 },
	{ "Steam",      "Steam",  "Steam", 0,            0,           -1 }, // Unfloats main screen
	{ "Steam",      "Steam",  "News",  0,            1,           -1 }, // floating other stuff with Steam in title
	{ "Steam",      "Steam",  "Info",  0,            1,           -1 }, 
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
// TODO: see if moving with window behavior is desirable
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

// For dual monitors
// TODO: Change to not follow screens when moving
#define TAGKEYSLEFT(KEY,TAG) \
	{ MODKEY,                       KEY,      focusmon,      {.i = -1 } }, \
	{ MODKEY,                       KEY,      view,          {.ui = 1 << TAG} }, \
  \
	{ MODKEY|ControlMask,           KEY,      focusmon,      {.i = -1} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,    {.ui = 1 << TAG} }, \
  \
	{ MODKEY|ShiftMask,             KEY,      tagmon,        {.i = -1 } }, \
	{ MODKEY|ShiftMask,             KEY,      focusmon,      {.i = -1 } }, \
	{ MODKEY|ShiftMask,             KEY,      tag,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      view,          {.ui = 1 << TAG} }, \
  \
	{ MODKEY|ControlMask|ShiftMask, KEY,      tagmon,        {.i = -1 } }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      focusmon,      {.i = -1 } }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,     {.ui = 1 << TAG} },

#define TAGKEYSRIGHT(KEY,TAG) \
	{ MODKEY,                       KEY,      focusmon,      {.i = +1 } }, \
	{ MODKEY,                       KEY,      view,          {.ui = 1 << TAG} }, \
  \
	{ MODKEY|ControlMask,           KEY,      focusmon,      {.i = +1 } }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,    {.ui = 1 << TAG} }, \
  \
	{ MODKEY|ShiftMask,             KEY,      tagmon,        {.i = +1 } }, \
	{ MODKEY|ShiftMask,             KEY,      focusmon,      {.i = +1 } }, \
	{ MODKEY|ShiftMask,             KEY,      tag,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      view,          {.ui = 1 << TAG} }, \
  \
	{ MODKEY|ControlMask|ShiftMask, KEY,      tagmon,        {.i = +1 } }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      focusmon,      {.i = +1 } }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,     {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

// Program launching
static const char *dmenucmd[]     = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]      = { "kitty", NULL };
static const char *browsercmd[]   = { "firefox", NULL };
static const char *filecmd[]      = { "kitty", "--class", "ranger", "ranger", NULL };
static const char *musiccmd[]     = { "kitty", "--class", "ncspot", "ncspot", NULL };
static const char *calendarcmd[]  = { "kitty", "--class", "calcurse", "calcurse", NULL };
static const char *discordcmd[]   = { "discord", NULL }; 
static const char *pmcmd[]        = { "keepassxc", NULL };
static const char *screenkeycmd[] = { "togglesk", NULL };

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

  // UNCOMMENT THIS FOR DOUBLE MONITOR SETUP
  /*
	{ MODKEY,                       XK_a,      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_a,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_a,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_a,      view,           {.ui = ~0 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period, focusmon,       {.i = +1 } },

	TAGKEYSLEFT(                    XK_1,                      0)
	TAGKEYSLEFT(                    XK_2,                      1)
	TAGKEYSLEFT(                    XK_3,                      2)
	TAGKEYSLEFT(                    XK_4,                      3)
	TAGKEYSLEFT(                    XK_5,                      4)
	TAGKEYSRIGHT(                   XK_6,                      0)
	TAGKEYSRIGHT(                   XK_7,                      1)
	TAGKEYSRIGHT(                   XK_8,                      2)
	TAGKEYSRIGHT(                   XK_9,                      3)
	TAGKEYSRIGHT(                   XK_0,                      4)
 */ 
  // END OF DOUBLE MONITOR CODE

  // UNCOMMENT THIS FOR SINGLE MONITOR SETUP
  
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
  
  // END OF SINGLE MONITOR CODE
  
	/*--------------------------PROGRAMS/SHORTCUTS------------------------------*/
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = musiccmd } },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = calendarcmd } }, // TODO: see if bind is easy to get used to
	{ MODKEY|ShiftMask,             XK_r,      spawn,          {.v = filecmd } },
	{ MODKEY|ShiftMask,             XK_z,      spawn,          {.v = pmcmd } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = discordcmd } },
	{ MODKEY,	                XK_s,      spawn,          {.v = sectioncmd } },
	{ MODKEY|ShiftMask,           	XK_s,      spawn,          {.v = screencmd } },
	{ MODKEY,                       XK_v,      spawn,          {.v = vpncmd } },
	{ MODKEY,                       XK_u,      spawn,          {.v = mountcmd } },
	{ MODKEY|ControlMask,           XK_u,      spawn,          {.v = umountcmd } },
	{ MODKEY,                       XK_c,      spawn,          {.v = screenkeycmd } },

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

