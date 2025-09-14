#ifndef CLARGS_H
#define CLARGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stddef.h>
#include <errno.h>

typedef enum {
    ARG_FLAG,
    ARG_STRING,
    ARG_CHAR,
    ARG_SHORT,
    ARG_INT,
    ARG_LONG,
    ARG_LLONG,
    ARG_UCHAR,
    ARG_USHORT,
    ARG_UINT,
    ARG_ULONG,
    ARG_ULLONG,
    ARG_SIZE,
    ARG_FLOAT,
    ARG_DOUBLE,
    ARG_POSITIONAL
} ArgKind;

typedef struct {
    char short_name;
    const char *long_name;
    const char *meta;
    const char *help;
    ArgKind kind;
    int required;
    int present;
    char *val_str;
    char val_char;
    short val_short;
    int val_int;
    long val_long;
    long long val_llong;
    unsigned char val_uchar;
    unsigned short val_ushort;
    unsigned int val_uint;
    unsigned long val_ulong;
    unsigned long long val_ullong;
    size_t val_size;
    float val_float;
    double val_double;
    const char *def_str;
    char def_char;
    short def_short;
    int def_int;
    long def_long;
    long long def_llong;
    unsigned char def_uchar;
    unsigned short def_ushort;
    unsigned int def_uint;
    unsigned long def_ulong;
    unsigned long long def_ullong;
    size_t def_size;
    float def_float;
    double def_double;
} Clarg;

typedef struct {
    const char *prog;
    const char *desc;
    Clarg **args;
    int cap;
    int count;
} Clargs;

static Clarg *make_arg() {
    return (Clarg*)calloc(1, sizeof(Clarg));
}

static void free_arg(Clarg *a) {
    if (!a) return;
    if (a->val_str) free(a->val_str);
    free(a);
}

Clargs *cl_create(const char *prog, const char *desc) {
    Clargs *p = (Clargs*)malloc(sizeof(Clargs));
    p->prog = prog ? prog : "program";
    p->desc = desc ? desc : "";
    p->cap = 8;
    p->count = 0;
    p->args = (Clarg**)calloc(p->cap, sizeof(Clarg*));
    return p;
}

void cl_free(Clargs *p) {
    if (!p) return;
    for (int i=0;i<p->count;i++) free_arg(p->args[i]);
    free(p->args);
    free(p);
}

static void cl_grow(Clargs *p) {
    if (p->count >= p->cap) {
        p->cap *= 2;
        p->args = (Clarg**)realloc(p->args, p->cap * sizeof(Clarg*));
    }
}

static int cl_find_idx(Clargs *p, const char *name) {
    for (int i=0;i<p->count;i++) {
        Clarg *a = p->args[i];
        if (a->long_name && name && strcmp(a->long_name, name) == 0) return i;
        if (a->short_name && name && strlen(name)==1 && a->short_name == name[0]) return i;
        if (a->kind == ARG_POSITIONAL && name && strcmp(a->long_name, name)==0) return i;
    }
    return -1;
}

int cl_add_flag(Clargs *p, char short_name, const char *long_name, const char *help) {
    Clarg *a = make_arg();
    a->short_name = short_name;
    a->long_name = long_name;
    a->help = help;
    a->kind = ARG_FLAG;
    cl_grow(p);
    p->args[p->count++] = a;
    return p->count - 1;
}

int cl_add_string(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, const char *def) {
    Clarg *a = make_arg();
    a->short_name = short_name;
    a->long_name = long_name;
    a->meta = meta ? meta : "STR";
    a->help = help;
    a->kind = ARG_STRING;
    a->required = req;
    a->def_str = def;
    if (def) a->val_str = strdup(def);
    cl_grow(p);
    p->args[p->count++] = a;
    return p->count - 1;
}

/* char */
int cl_add_char(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, char def) {
    Clarg *a = make_arg(); a->short_name = short_name; a->long_name = long_name; a->meta = meta?meta:"CHAR"; a->help = help; a->kind = ARG_CHAR; a->required = req; a->def_char = def; a->val_char = def; cl_grow(p); p->args[p->count++] = a; return p->count-1;
}

/* short */
int cl_add_short(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, short def) {
    Clarg *a = make_arg(); a->short_name = short_name; a->long_name = long_name; a->meta = meta?meta:"SHORT"; a->help = help; a->kind = ARG_SHORT; a->required = req; a->def_short = def; a->val_short = def; cl_grow(p); p->args[p->count++] = a; return p->count-1;
}

/* int */
int cl_add_int(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, int def) {
    Clarg *a = make_arg();
    a->short_name = short_name;
    a->long_name = long_name;
    a->meta = meta ? meta : "INT";
    a->help = help;
    a->kind = ARG_INT;
    a->required = req;
    a->def_int = def;
    a->val_int = def;
    cl_grow(p);
    p->args[p->count++] = a;
    return p->count - 1;
}

/* long */
int cl_add_long(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, long def) {
    Clarg *a = make_arg(); a->short_name = short_name; a->long_name = long_name; a->meta = meta?meta:"LONG"; a->help = help; a->kind = ARG_LONG; a->required = req; a->def_long = def; a->val_long = def; cl_grow(p); p->args[p->count++] = a; return p->count-1;
}

/* long long */
int cl_add_llong(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, long long def) {
    Clarg *a = make_arg(); a->short_name = short_name; a->long_name = long_name; a->meta = meta?meta:"LLONG"; a->help = help; a->kind = ARG_LLONG; a->required = req; a->def_llong = def; a->val_llong = def; cl_grow(p); p->args[p->count++] = a; return p->count-1;
}

/* unsigned variants */
int cl_add_uchar(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, unsigned char def) {
    Clarg *a = make_arg(); a->short_name = short_name; a->long_name = long_name; a->meta = meta?meta:"UCHAR"; a->help = help; a->kind = ARG_UCHAR; a->required = req; a->def_uchar = def; a->val_uchar = def; cl_grow(p); p->args[p->count++] = a; return p->count-1;
}
int cl_add_ushort(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, unsigned short def) {
    Clarg *a = make_arg(); a->short_name = short_name; a->long_name = long_name; a->meta = meta?meta:"USHORT"; a->help = help; a->kind = ARG_USHORT; a->required = req; a->def_ushort = def; a->val_ushort = def; cl_grow(p); p->args[p->count++] = a; return p->count-1;
}
int cl_add_uint(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, unsigned int def) {
    Clarg *a = make_arg(); a->short_name = short_name; a->long_name = long_name; a->meta = meta?meta:"UINT"; a->help = help; a->kind = ARG_UINT; a->required = req; a->def_uint = def; a->val_uint = def; cl_grow(p); p->args[p->count++] = a; return p->count-1;
}
int cl_add_ulong(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, unsigned long def) {
    Clarg *a = make_arg(); a->short_name = short_name; a->long_name = long_name; a->meta = meta?meta:"ULONG"; a->help = help; a->kind = ARG_ULONG; a->required = req; a->def_ulong = def; a->val_ulong = def; cl_grow(p); p->args[p->count++] = a; return p->count-1;
}
int cl_add_ullong(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, unsigned long long def) {
    Clarg *a = make_arg(); a->short_name = short_name; a->long_name = long_name; a->meta = meta?meta:"ULLONG"; a->help = help; a->kind = ARG_ULLONG; a->required = req; a->def_ullong = def; a->val_ullong = def; cl_grow(p); p->args[p->count++] = a; return p->count-1;
}

/* size_t */
int cl_add_size(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, size_t def) {
    Clarg *a = make_arg(); a->short_name = short_name; a->long_name = long_name; a->meta = meta?meta:"SIZE"; a->help = help; a->kind = ARG_SIZE; a->required = req; a->def_size = def; a->val_size = def; cl_grow(p); p->args[p->count++] = a; return p->count-1;
}

/* float */
int cl_add_float(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, float def) {
    Clarg *a = make_arg(); a->short_name = short_name; a->long_name = long_name; a->meta = meta?meta:"FLT"; a->help = help; a->kind = ARG_FLOAT; a->required = req; a->def_float = def; a->val_float = def; cl_grow(p); p->args[p->count++] = a; return p->count-1;
}

/* double */
int cl_add_double(Clargs *p, char short_name, const char *long_name, const char *meta, const char *help, int req, double def) {
    Clarg *a = make_arg(); a->short_name = short_name; a->long_name = long_name; a->meta = meta?meta:"DBL"; a->help = help; a->kind = ARG_DOUBLE; a->required = req; a->def_double = def; a->val_double = def; cl_grow(p); p->args[p->count++] = a; return p->count-1;
}

int cl_add_pos(Clargs *p, const char *name, const char *help, int req) {
    Clarg *a = make_arg();
    a->long_name = name;
    a->meta = name;
    a->help = help;
    a->kind = ARG_POSITIONAL;
    a->required = req;
    cl_grow(p);
    p->args[p->count++] = a;
    return p->count - 1;
}

/* parsing helpers */

static int parse_int_simple(const char *s, long *out, int base) {
    if (!s) return 0;
    errno = 0;
    char *end = NULL;
    long v = strtol(s, &end, base);
    if (end == s || *end != '\0' || errno) return 0;
    *out = v;
    return 1;
}

static int parse_llong_simple(const char *s, long long *out, int base) {
    if (!s) return 0;
    errno = 0;
    char *end = NULL;
    long long v = strtoll(s, &end, base);
    if (end == s || *end != '\0' || errno) return 0;
    *out = v;
    return 1;
}

static int parse_unsigned_long_simple(const char *s, unsigned long *out, int base) {
    if (!s) return 0;
    errno = 0;
    char *end = NULL;
    unsigned long v = strtoul(s, &end, base);
    if (end == s || *end != '\0' || errno) return 0;
    *out = v;
    return 1;
}

static int parse_unsigned_llong_simple(const char *s, unsigned long long *out, int base) {
    if (!s) return 0;
    errno = 0;
    char *end = NULL;
    unsigned long long v = strtoull(s, &end, base);
    if (end == s || *end != '\0' || errno) return 0;
    *out = v;
    return 1;
}

static int parse_float_simple(const char *s, float *out) {
    if (!s) return 0;
    errno = 0;
    char *end = NULL;
    float v = strtof(s, &end);
    if (end == s || *end != '\0' || errno) return 0;
    *out = v;
    return 1;
}

static int parse_double_simple(const char *s, double *out) {
    if (!s) return 0;
    errno = 0;
    char *end = NULL;
    double v = strtod(s, &end);
    if (end == s || *end != '\0' || errno) return 0;
    *out = v;
    return 1;
}

/* help printer */

void cl_help(Clargs *p) {
    printf("Usage: %s", p->prog);
    for (int i=0;i<p->count;i++) {
        Clarg *a = p->args[i];
        if (a->kind == ARG_POSITIONAL) continue;
        printf(" ");
        if (!a->required) printf("[");
        if (a->short_name) {
            printf("-%c", a->short_name);
            if (a->kind != ARG_FLAG) printf(" %s", a->meta);
        } else if (a->long_name) {
            printf("--%s", a->long_name);
            if (a->kind != ARG_FLAG) printf(" %s", a->meta);
        }
        if (!a->required) printf("]");
    }
    for (int i=0;i<p->count;i++) if (p->args[i]->kind == ARG_POSITIONAL) printf(" %s", p->args[i]->meta);
    printf("\n\n%s\n\n", p->desc && p->desc[0] ? p->desc : "");
    printf("Options:\n");
    for (int i=0;i<p->count;i++) {
        Clarg *a = p->args[i];
        if (a->kind == ARG_POSITIONAL) continue;
        char buf[128] = "";
        if (a->short_name) { sprintf(buf+strlen(buf), "-%c", a->short_name); if (a->long_name) strcat(buf, ", "); }
        if (a->long_name) sprintf(buf+strlen(buf), "--%s", a->long_name);
        if (a->kind != ARG_FLAG) sprintf(buf+strlen(buf), " %s", a->meta ? a->meta : "");
        printf("  %-30s %s", buf, a->help ? a->help : "");
        switch (a->kind) {
            case ARG_STRING: if (a->def_str) printf(" (default: %s)", a->def_str); break;
            case ARG_CHAR: printf(" (default: %c)", a->def_char); break;
            case ARG_SHORT: printf(" (default: %d)", a->def_short); break;
            case ARG_INT: printf(" (default: %d)", a->def_int); break;
            case ARG_LONG: printf(" (default: %ld)", a->def_long); break;
            case ARG_LLONG: printf(" (default: %lld)", (long long)a->def_llong); break;
            case ARG_UCHAR: printf(" (default: %u)", (unsigned)a->def_uchar); break;
            case ARG_USHORT: printf(" (default: %u)", (unsigned)a->def_ushort); break;
            case ARG_UINT: printf(" (default: %u)", a->def_uint); break;
            case ARG_ULONG: printf(" (default: %lu)", a->def_ulong); break;
            case ARG_ULLONG: printf(" (default: %llu)", (unsigned long long)a->def_ullong); break;
            case ARG_SIZE: printf(" (default: %zu)", a->def_size); break;
            case ARG_FLOAT: printf(" (default: %.6g)", (double)a->def_float); break;
            case ARG_DOUBLE: printf(" (default: %.6g)", a->def_double); break;
            default: break;
        }
        if (a->required) printf(" [required]");
        printf("\n");
    }
    int any = 0; for (int i=0;i<p->count;i++) if (p->args[i]->kind == ARG_POSITIONAL) any = 1;
    if (any) {
        printf("\nPositional:\n");
        for (int i=0;i<p->count;i++) {
            Clarg *a = p->args[i]; if (a->kind != ARG_POSITIONAL) continue;
            printf("  %-30s %s", a->meta, a->help ? a->help : "");
            if (a->required) printf(" [required]");
            printf("\n");
        }
    }
}

/* parsing */

int cl_parse(Clargs *p, int argc, char **argv) {
    if (!p) return -1;
    if (argc > 0) p->prog = argv[0];
    for (int i=1;i<argc;i++) {
        char *tok = argv[i];
        if (!strcmp(tok, "--help") || !strcmp(tok, "-h")) { cl_help(p); exit(0); }
        if (tok[0] == '-' && tok[1] == '-') {
            char *eq = strchr(tok, '=');
            char name[128];
            const char *val = NULL;
            if (eq) { int n = eq - (tok + 2); strncpy(name, tok+2, n); name[n]=0; val = eq+1; }
            else strcpy(name, tok+2);
            int idx = cl_find_idx(p, name);
            if (idx < 0) { fprintf(stderr, "Unknown option: %s\n", tok); return -1; }
            Clarg *a = p->args[idx]; a->present = 1;
            if (a->kind == ARG_FLAG) continue;
            if (!val) { if (i+1 >= argc) { fprintf(stderr, "Missing value for --%s\n", name); return -1; } val = argv[++i]; }
            switch (a->kind) {
                case ARG_STRING: if (a->val_str) free(a->val_str); a->val_str = strdup(val); break;
                case ARG_CHAR: if (!val[0]) { fprintf(stderr, "Bad char for --%s\n", name); return -1; } a->val_char = val[0]; break;
                case ARG_SHORT: { long tmp; if (!parse_int_simple(val, &tmp, 10)) { fprintf(stderr, "Bad short for --%s\n", name); return -1; } a->val_short = (short)tmp; break; }
                case ARG_INT: { long tmp; if (!parse_int_simple(val, &tmp, 10)) { fprintf(stderr, "Bad int for --%s\n", name); return -1; } a->val_int = (int)tmp; break; }
                case ARG_LONG: { long tmp; if (!parse_int_simple(val, &tmp, 10)) { fprintf(stderr, "Bad long for --%s\n", name); return -1; } a->val_long = tmp; break; }
                case ARG_LLONG: { long long tmp; if (!parse_llong_simple(val, &tmp, 10)) { fprintf(stderr, "Bad long long for --%s\n", name); return -1; } a->val_llong = tmp; break; }
                case ARG_UCHAR: { unsigned long tmp; if (!parse_unsigned_long_simple(val, &tmp, 10) || tmp > UCHAR_MAX) { fprintf(stderr, "Bad uchar for --%s\n", name); return -1; } a->val_uchar = (unsigned char)tmp; break; }
                case ARG_USHORT: { unsigned long tmp; if (!parse_unsigned_long_simple(val, &tmp, 10) || tmp > USHRT_MAX) { fprintf(stderr, "Bad ushort for --%s\n", name); return -1; } a->val_ushort = (unsigned short)tmp; break; }
                case ARG_UINT: { unsigned long tmp; if (!parse_unsigned_long_simple(val, &tmp, 10) || tmp > UINT_MAX) { fprintf(stderr, "Bad uint for --%s\n", name); return -1; } a->val_uint = (unsigned int)tmp; break; }
                case ARG_ULONG: { unsigned long tmp; if (!parse_unsigned_long_simple(val, &tmp, 10)) { fprintf(stderr, "Bad ulong for --%s\n", name); return -1; } a->val_ulong = tmp; break; }
                case ARG_ULLONG: { unsigned long long tmp; if (!parse_unsigned_llong_simple(val, &tmp, 10)) { fprintf(stderr, "Bad ullong for --%s\n", name); return -1; } a->val_ullong = tmp; break; }
                case ARG_SIZE: { unsigned long tmp; if (!parse_unsigned_long_simple(val, &tmp, 10)) { fprintf(stderr, "Bad size for --%s\n", name); return -1; } a->val_size = (size_t)tmp; break; }
                case ARG_FLOAT: { float tmp; if (!parse_float_simple(val, &tmp)) { fprintf(stderr, "Bad float for --%s\n", name); return -1; } a->val_float = tmp; break; }
                case ARG_DOUBLE: { double tmp; if (!parse_double_simple(val, &tmp)) { fprintf(stderr, "Bad double for --%s\n", name); return -1; } a->val_double = tmp; break; }
                default: break;
            }
        } else if (tok[0] == '-' && tok[1]) {
            int len = (int)strlen(tok);
            for (int k=1;k<len;k++) {
                char ch = tok[k];
                char n[2] = { ch, 0 };
                int idx = cl_find_idx(p, n);
                if (idx < 0) { fprintf(stderr, "Unknown -%c\n", ch); return -1; }
                Clarg *a = p->args[idx];
                a->present = 1;
                if (a->kind == ARG_FLAG) continue;
                const char *val = NULL;
                if (k+1 < len) { val = &tok[k+1]; k = len; }
                else { if (i+1 >= argc) { fprintf(stderr, "Missing value for -%c\n", ch); return -1; } val = argv[++i]; }
                switch (a->kind) {
                    case ARG_STRING: if (a->val_str) free(a->val_str); a->val_str = strdup(val); break;
                    case ARG_CHAR: if (!val[0]) { fprintf(stderr, "Bad char for -%c\n", ch); return -1; } a->val_char = val[0]; break;
                    case ARG_SHORT: { long tmp; if (!parse_int_simple(val, &tmp, 10)) { fprintf(stderr, "Bad short for -%c\n", ch); return -1; } a->val_short = (short)tmp; break; }
                    case ARG_INT: { long tmp; if (!parse_int_simple(val, &tmp, 10)) { fprintf(stderr, "Bad int for -%c\n", ch); return -1; } a->val_int = (int)tmp; break; }
                    case ARG_LONG: { long tmp; if (!parse_int_simple(val, &tmp, 10)) { fprintf(stderr, "Bad long for -%c\n", ch); return -1; } a->val_long = tmp; break; }
                    case ARG_LLONG: { long long tmp; if (!parse_llong_simple(val, &tmp, 10)) { fprintf(stderr, "Bad long long for -%c\n", ch); return -1; } a->val_llong = tmp; break; }
                    case ARG_UCHAR: { unsigned long tmp; if (!parse_unsigned_long_simple(val, &tmp, 10) || tmp > UCHAR_MAX) { fprintf(stderr, "Bad uchar for -%c\n", ch); return -1; } a->val_uchar = (unsigned char)tmp; break; }
                    case ARG_USHORT: { unsigned long tmp; if (!parse_unsigned_long_simple(val, &tmp, 10) || tmp > USHRT_MAX) { fprintf(stderr, "Bad ushort for -%c\n", ch); return -1; } a->val_ushort = (unsigned short)tmp; break; }
                    case ARG_UINT: { unsigned long tmp; if (!parse_unsigned_long_simple(val, &tmp, 10) || tmp > UINT_MAX) { fprintf(stderr, "Bad uint for -%c\n", ch); return -1; } a->val_uint = (unsigned int)tmp; break; }
                    case ARG_ULONG: { unsigned long tmp; if (!parse_unsigned_long_simple(val, &tmp, 10)) { fprintf(stderr, "Bad ulong for -%c\n", ch); return -1; } a->val_ulong = tmp; break; }
                    case ARG_ULLONG: { unsigned long long tmp; if (!parse_unsigned_llong_simple(val, &tmp, 10)) { fprintf(stderr, "Bad ullong for -%c\n", ch); return -1; } a->val_ullong = tmp; break; }
                    case ARG_SIZE: { unsigned long tmp; if (!parse_unsigned_long_simple(val, &tmp, 10)) { fprintf(stderr, "Bad size for -%c\n", ch); return -1; } a->val_size = (size_t)tmp; break; }
                    case ARG_FLOAT: { float tmp; if (!parse_float_simple(val, &tmp)) { fprintf(stderr, "Bad float for -%c\n", ch); return -1; } a->val_float = tmp; break; }
                    case ARG_DOUBLE: { double tmp; if (!parse_double_simple(val, &tmp)) { fprintf(stderr, "Bad double for -%c\n", ch); return -1; } a->val_double = tmp; break; }
                    default: break;
                }
            }
        } else {
            int ok = 0;
            for (int j=0;j<p->count;j++) {
                Clarg *a = p->args[j];
                if (a->kind == ARG_POSITIONAL && !a->present) {
                    a->present = 1;
                    if (a->val_str) free(a->val_str);
                    a->val_str = strdup(tok);
                    ok = 1;
                    break;
                }
            }
            if (!ok) { fprintf(stderr, "Unexpected arg %s\n", tok); return -1; }
        }
    }

    for (int i=0;i<p->count;i++) {
        Clarg *a = p->args[i];
        if (a->kind == ARG_STRING) {
            if (!a->val_str && a->def_str) a->val_str = strdup(a->def_str);
            if (a->required && !a->val_str) { fprintf(stderr, "Missing --%s\n", a->long_name ? a->long_name : "(arg)"); return -1; }
        }
        if ((a->kind == ARG_CHAR || a->kind == ARG_SHORT || a->kind == ARG_INT || a->kind == ARG_LONG || a->kind == ARG_LLONG
             || a->kind == ARG_UCHAR || a->kind == ARG_USHORT || a->kind == ARG_UINT || a->kind == ARG_ULONG || a->kind == ARG_ULLONG
             || a->kind == ARG_SIZE || a->kind == ARG_FLOAT || a->kind == ARG_DOUBLE) && a->required && !a->present) {
            fprintf(stderr, "Missing --%s\n", a->long_name ? a->long_name : "(arg)");
            return -1;
        }
        if (a->kind == ARG_POSITIONAL && a->required && !a->present) { fprintf(stderr, "Missing %s\n", a->meta ? a->meta : "(pos)"); return -1; }
    }
    return 0;
}

/* finder and getters */

static Clarg *cl_find(Clargs *p, const char *name) {
    if (!name) return NULL;
    for (int i=0;i<p->count;i++) {
        Clarg *a = p->args[i];
        if (a->long_name && strcmp(a->long_name, name) == 0) return a;
        if (strlen(name) == 1 && a->short_name == name[0]) return a;
        if (a->kind == ARG_POSITIONAL && a->meta && strcmp(a->meta, name) == 0) return a;
    }
    return NULL;
}

int cl_get_flag(Clargs *p, const char *name) {
    Clarg *a = cl_find(p, name); return a && a->present;
}

const char *cl_get_string(Clargs *p, const char *name) {
    Clarg *a = cl_find(p, name); return a ? a->val_str : NULL;
}

char cl_get_char(Clargs *p, const char *name, int *ok) { Clarg *a = cl_find(p, name); if (!a) { if (ok) *ok = 0; return 0; } if (ok) *ok = 1; return a->val_char; }
short cl_get_short(Clargs *p, const char *name, int *ok) { Clarg *a = cl_find(p, name); if (!a) { if (ok) *ok = 0; return 0; } if (ok) *ok = 1; return a->val_short; }
int cl_get_int(Clargs *p, const char *name, int *ok) { Clarg *a = cl_find(p, name); if (!a) { if (ok) *ok = 0; return 0; } if (ok) *ok = 1; return a->val_int; }
long cl_get_long(Clargs *p, const char *name, int *ok) { Clarg *a = cl_find(p, name); if (!a) { if (ok) *ok = 0; return 0L; } if (ok) *ok = 1; return a->val_long; }
long long cl_get_llong(Clargs *p, const char *name, int *ok) { Clarg *a = cl_find(p, name); if (!a) { if (ok) *ok = 0; return 0LL; } if (ok) *ok = 1; return a->val_llong; }

unsigned char cl_get_uchar(Clargs *p, const char *name, int *ok) { Clarg *a = cl_find(p, name); if (!a) { if (ok) *ok = 0; return 0; } if (ok) *ok = 1; return a->val_uchar; }
unsigned short cl_get_ushort(Clargs *p, const char *name, int *ok) { Clarg *a = cl_find(p, name); if (!a) { if (ok) *ok = 0; return 0; } if (ok) *ok = 1; return a->val_ushort; }
unsigned int cl_get_uint(Clargs *p, const char *name, int *ok) { Clarg *a = cl_find(p, name); if (!a) { if (ok) *ok = 0; return 0u; } if (ok) *ok = 1; return a->val_uint; }
unsigned long cl_get_ulong(Clargs *p, const char *name, int *ok) { Clarg *a = cl_find(p, name); if (!a) { if (ok) *ok = 0; return 0ul; } if (ok) *ok = 1; return a->val_ulong; }
unsigned long long cl_get_ullong(Clargs *p, const char *name, int *ok) { Clarg *a = cl_find(p, name); if (!a) { if (ok) *ok = 0; return 0ull; } if (ok) *ok = 1; return a->val_ullong; }

size_t cl_get_size(Clargs *p, const char *name, int *ok) { Clarg *a = cl_find(p, name); if (!a) { if (ok) *ok = 0; return (size_t)0; } if (ok) *ok = 1; return a->val_size; }

float cl_get_float(Clargs *p, const char *name, int *ok) { Clarg *a = cl_find(p, name); if (!a) { if (ok) *ok = 0; return 0.0f; } if (ok) *ok = 1; return a->val_float; }
double cl_get_double(Clargs *p, const char *name, int *ok) { Clarg *a = cl_find(p, name); if (!a) { if (ok) *ok = 0; return 0.0; } if (ok) *ok = 1; return a->val_double; }

#endif
