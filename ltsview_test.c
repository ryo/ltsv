/*-
 * Copyright (c) 2013 SHIMIZU Ryo <ryo@nerv.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "ltsv.h"

#define KEY_BEGIN	"\e[35m"
#define KEY_END		"\e[m"
#define VALUE_BEGIN	"\e[32m"
#define VALUE_END	"\e[m"

int
main(int argc, char *argv[])
{
	struct ltsv ltsv;
	int rc;
	char *filename;
	int color = 1;

	if (argc != 2) {
		printf("usage: ltsview_test [ltsvfile]\n");
		return -1;
	}
	filename = argv[1];

	if (!isatty(STDOUT_FILENO))
		color = 0;

	rc = ltsv_open(&ltsv, filename);
	if (rc != 0) {
		printf("ltsv_open: %s: %s\n", filename, strerror(errno));
		return -2;
	}

	while (ltsv_get(&ltsv) == 0) {
		if (LTSV_COLUMN(&ltsv) == 0)
			printf("---\n");

		printf("%s%s%s: ",
		    color ? KEY_BEGIN : "",
		    LTSV_KEY(&ltsv),
		    color ? KEY_END : "");
		printf("%s%s%s\n",
		    color ? VALUE_BEGIN : "",
		    LTSV_VALUE(&ltsv),
		    color ? VALUE_END : "");
	}

	ltsv_close(&ltsv);

	return 0;
}
