// custom commads //
static void x_nexttag(const Arg *arg);
static void x_nexttag_all(const Arg *arg);
static void x_prevtag(const Arg *arg);
static void x_prevtag_all(const Arg *arg);
static void x_adjtag(int n, int all, int seltag);
//     Tag Cycling From //
//     
//
static void x_prevtag(const Arg *arg) {
    (void)arg;
    x_adjtag(-1,0,-1);
}
static void x_prevtag_all(const Arg *arg) {
    (void)arg;
    x_adjtag(-1,1,-1);
}

static void x_nexttag(const Arg *arg) {
    (void)arg;
    x_adjtag(+1,0,-1);
}
static void x_nexttag_all(const Arg *arg) {
    (void)arg;
    x_adjtag(+1,1,-1);
}

static void x_adjtag(int n, int all,int seltag) {
    int i, curtags;
    Arg arg;

    Client *c;
    int occ = 0;

    //cycle through all tags?
    if (all == 1){
        occ=0;
    } else {
        for (c = selmon->clients; c; c = c->next) {
            occ |= c->tags;
        }
        if ( all == 0 && occ == 0 ) return;
    }

    /*
     *     * Check first tag currently selected.  If 
     there are
     *         * several tags selected we only pick 
     first one.
     *             */
    if (selmon != NULL) {
        curtags = (selmon->tagset[selmon->seltags] & 
                TAGMASK);
    } else {
        return;
    }

    if (seltag < 0){
        for (i = 0; i < LENGTH(tags); i++) {
            if ((curtags & (1 << i)) != 0) {
                seltag = i;
                break;
            }
        }
    }

    /*
     *      * Calculate next selected tag wrapping 
     around
     *           * when tag overflows.
     *                */
    seltag = (seltag + n) % (int)LENGTH(tags);
    if (seltag < 0)
        seltag += LENGTH(tags);


    //cycle through only populated tags?
    if ((occ != 0) && !(occ & 1 << seltag)){
        x_adjtag(n,0,seltag);
        return;
    }  
    arg.ui = (1 << seltag);
    view(&arg);
}

