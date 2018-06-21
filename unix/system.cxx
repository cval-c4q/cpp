/**
 *  A POSIX.1-compliant implementation of the standard library's system() call
 *
 *  - Invocation is through execl(<shell path>, "sh", "-c", command, (char*)0)
 *  - Shall ignore SIGINT and SIGQUIT, shall block SIGCHLD
 *  - Shall not affect termination status of child processes other than the one it itself spawns
 *  - Shall not return until child process terminates
 *  - Need not be thread-safe
 */

#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

const char *_path_to_bin_sh = "/bin/sh";

int system(const char *command)
{
	sigset_t sset, oset;
	struct sigaction osigint, osigquit, ignore;
	pid_t pid;
	int status;

	// - If command is NULL
	if (command == NULL) {
		// ... and shell is available
		if (access(_path_to_bin_sh, R_OK | X_OK) == 0)
			return -1;
		else
			return 0;
	}

	// block SIGCHLD
	sigemptyset(&sset);
	sigaddset(&sset, SIGCHLD);
	if (sigprocmask(SIG_BLOCK, &sset, &oset) < 0)
		return -1;

	// Generic 'Ignore' sigaction_t for both SIGQUIT and SIGINT
	ignore.sa_handler = SIG_IGN;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;

	// Ignore SIGs QUIT and INT
	if (sigaction(SIGINT, &ignore, &osigint) < 0) {
		sigprocmask(SIG_SETMASK, &oset, NULL);
		return -1;
	}
	if (sigaction(SIGQUIT, &ignore, &osigquit) < 0) {
		sigprocmask(SIG_SETMASK, &oset, NULL);
		sigaction(SIGINT, &osigint, NULL);
		return -1;
	}

	if ((pid = fork()) == 0) { // child
		execl(_path_to_bin_sh, "sh", "-c", command, (char*)0);
		_exit(127);
	} else if (pid > 0) { // parent
		sigaction(SIGINT, &osigint, NULL);
		sigaction(SIGQUIT, &osigquit, NULL);
		sigprocmask(SIG_SETMASK, &oset, NULL);
		while (waitpid(pid, &status, 0) < 0)
			if (errno != EINTR) {
				status = -1;
				break;
			}
		if (WIFEXITED(status)) // XXX: APUE3 doesn't do this
			status = WEXITSTATUS(status);
		else
			status = -1; // - -1 if exit status cannot be determined
	} else {
		status = -1; // - ... or on failure to fork()
	}

	// restore process signal mask and SIGINT/SIGQUIT saved dispositions
	status |= sigprocmask(SIG_SETMASK, &oset, NULL);
	status |= sigaction(SIGINT, &osigint, NULL);
	status |= sigaction(SIGQUIT, &osigquit, NULL);
	return status;
}
