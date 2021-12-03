#define B1 1
#define B2 2
#define B3 4
#define B4 8
#define B5 16

#define MODMASK ControlMask

int expandtabs = 0;
int tabw = 4;
int autoindent = 1;
char *fontstr = "DeJavu Sans Mono:size=12:antialias=true:autohint=true" ;
char *background = "white:seashell:lightgreen:oldlace:"
	"lightcyan:gainsboro:lightyellow:"
	"mintcream:snow:lightblue:thistle" ;
char *foreground = "black" ;
char *bordercolor = "black" ;
char *clipsrc = "CLIPBOARD" ;

typedef struct Binding Binding;
struct Binding {
    int modifiers;
    KeySym keysym;
    int kind;
    int command;
    const char *arg;
};

static Binding bindings[] ={    
    /* Suppress control key combinations unless explicitly bound. */
    {MODMASK, XK_VoidSymbol,    Kcommand, Cnone,        NULL},

    /* Move. */
    {MODMASK, XK_k, Kcommand,  Clineup,     NULL},
    {MODMASK, XK_j, Kcommand,  Clinedown,   NULL},
    {MODMASK, XK_l, Kcommand,  Ccharright,  NULL},
    {MODMASK, XK_h, Kcommand,  Ccharleft,   NULL},
    {MODMASK, XK_e, Kcommand,  Ceol,   NULL},
    {MODMASK, XK_a, Kcommand,  Cbol,   NULL},
    {MODMASK|ShiftMask, XK_b, Kcommand, Cscrollup,  NULL},
    {MODMASK|ShiftMask, XK_f, Kcommand, Cscrolldown,  NULL},

	/* Delete. */
    {MODMASK, XK_u, Kcommand,  Cdelbol,     NULL},
    {MODMASK, XK_BackSpace, Kcommand, Cdelword, NULL},
    {MODMASK, XK_w, Kcommand, Cdelword, 0},

	/* Save file[s]. */
    {MODMASK, XK_s, Kcommand,  Cwrite,     NULL},
    {MODMASK|ShiftMask, XK_s, Kcommand,  Csend, "X w"},

	/* Tabs. */
	{MODMASK, XK_t, Kcommand, Csend, "|tab-"},
	{MODMASK|ShiftMask, XK_t, Kcommand, Csend, "|tab+"},

	/* Undo. */
	{MODMASK, XK_z, Kcommand, Csend, "u"},

	/* Search. */
	{MODMASK, XK_n, Kcommand, Csearch, 0},
	{MODMASK|ShiftMask, XK_n, Kcommand, Clook, 0},

    /*{MODMASK, XK_Escape, Kcommand,  Cjump,       NULL},*/
	/* Selection. */
    {MODMASK, XK_x, Kcommand,  Ccut,        NULL},
    {MODMASK, XK_c, Kcommand,  Csnarf,      NULL},
    {MODMASK, XK_v, Kcommand,  Cpaste,      NULL},
    {MODMASK, XK_q, Kcommand,  Cexchange,   NULL},

    /* Handle arrow keys, page up/down, and escape. */
    {0,           XK_Left,          Kcommand, Ccharleft,    NULL},
    {0,           XK_Right,         Kcommand, Ccharright,  NULL},
    {0,           XK_Up,         Kcommand, Clineup,  NULL},
    {0,           XK_Down,         Kcommand, Clinedown,  NULL},
    {ShiftMask, XK_Up, Kcommand, Cscrollup, NULL},
    {ShiftMask, XK_Down, Kcommand, Cscrolldown, NULL},
    {0,           XK_Prior,         Kcommand, Cscrollup,    NULL},
    {0,           XK_Next,          Kcommand, Cscrolldown,  NULL},
    {0, XK_Escape, Kcommand, Cjump, NULL},
    
    /* More fundamental stuff: backspace, delete, etc. */
    {0,           XK_BackSpace,     Kcommand, Cdelbs,   NULL},
    {0,           XK_Delete,        Kcommand, Cdel,     NULL},
    {0,           XK_Tab,           Kcommand, Ctab,     NULL},
    {0,           XK_Return,        Kraw,     '\n',     NULL},
    {0,           XK_KP_Enter,      Kraw,     '\n',     NULL},
    {0,           XK_Linefeed,      Kraw,     '\r',     NULL},
    {0,           XK_KP_0,          Kraw,     '0',      NULL},
    {0,           XK_KP_1,          Kraw,     '1',      NULL},
    {0,           XK_KP_2,          Kraw,     '2',      NULL},
    {0,           XK_KP_3,          Kraw,     '3',      NULL},
    {0,           XK_KP_4,          Kraw,     '4',      NULL},
    {0,           XK_KP_5,          Kraw,     '5',      NULL},
    {0,           XK_KP_6,          Kraw,     '6',      NULL},
    {0,           XK_KP_7,          Kraw,     '7',      NULL},
    {0,           XK_KP_8,          Kraw,     '8',      NULL},
    {0,           XK_KP_9,          Kraw,     '9',      NULL},
    {0,           XK_KP_Divide,     Kraw,     '/',      NULL},
    {0,           XK_KP_Multiply,   Kraw,     '*',      NULL},
    {0,           XK_KP_Subtract,   Kraw,     '-',      NULL},
    {0,           XK_KP_Add,        Kraw,     '+',      NULL},
    {0,           XK_KP_Decimal,    Kraw,     '.',      NULL},
    {0,           XK_hyphen,        Kraw,     '-',      NULL},

    /* Use Control-Tab to insert a literal tab when tab expansion is enabled. */
    {MODMASK, XK_Tab,           Kraw,     '\t',     NULL},

    {0,           0,                Kend,     0,        NULL}
};

typedef struct Chord Chord;
struct Chord {
    int state1;
    int state2;
    int command;
    int target;
    const char *arg;
};

static Chord chords[] = {
    {B1, B1|B2,  Ccut,   Tcurrent, NULL},
    {B1, B1|B3,  Cpaste, Tcurrent, NULL},
    {B1|B2, B1,  Cnone,  Tcurrent, NULL},
    {B1|B3, B1,  Cnone,  Tcurrent, NULL},

    {B4, 0,  Cscrollupline,   Tmouse, NULL},
    {B5, 0,  Cscrolldownline, Tmouse, NULL},

    {0, 0, Kend, 0, NULL}
};

