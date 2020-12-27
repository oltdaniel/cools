#include "log.h"

int main(void) {
    log_debug("loaded sample file.", "/tmp/123.abc");
    log_warning("invalid argument. ignoring.");
    log_error("5 + 6 != %d, expected %d.", 2, 5 + 6);
    log_fatal("huge %s input %s. exit.", "user", "error");
    return 0;
}