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
    {ControlMask, XK_VoidSymbol,    Kcommand, Cnone,        NULL},

    /* Motion commands following the WordStar diamond. */
    {ControlMask, XK_k, Kcommand,  Clineup,     NULL},
    {ControlMask, XK_j, Kcommand,  Clinedown,   NULL},
    {ControlMask, XK_l, Kcommand,  Ccharright,  NULL},
    {ControlMask, XK_h, Kcommand,  Ccharleft,   NULL},
    {ControlMask, XK_u, Kcommand,  Cdelbol,     NULL},
    {ControlMask, XK_w, Kcommand,  Cdelword,    NULL},
    {ControlMask, XK_BackSpace,     Kcommand,  Cdelword,    NULL},
    {ControlMask, XK_k, Kcommand,  Cjump,       NULL},
    {ControlMask, XK_x, Kcommand,  Ccut,        NULL},
    {ControlMask, XK_c, Kcommand,  Csnarf,      NULL},
    {ControlMask, XK_v, Kcommand,  Cpaste,      NULL},
    {ControlMask, XK_q, Kcommand,  Cexchange,   NULL},

    /* Handle arrow keys, page up/down, and escape. */
    {0,           XK_Up,            Kcommand, Cscrollup,    NULL},
    {0,           XK_Prior,         Kcommand, Cscrollup,    NULL},
    {0,           XK_Left,          Kcommand, Cscrollup,    NULL},
    {0,           XK_Down,          Kcommand, Cscrolldown,  NULL},
    {0,           XK_Next,          Kcommand, Cscrolldown,  NULL},
    {0,           XK_Right,         Kcommand, Cscrolldown,  NULL},
    {0,           XK_Escape,        Kcommand, Cescape,      NULL},
    
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
    {ControlMask, XK_Tab,           Kraw,     '\t',     NULL},

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

