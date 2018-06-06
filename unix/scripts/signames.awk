function ifdef_cpp_in() {
	printf("%s",
	       "#if defined (__cpluscplus)\n" \
	       "extern \"C\" {\n" \
		       "#endif\n");
}

function ifdef_cpp_out() {
	printf("%s",
	       "#if defined (__cpluscplus)\n" \
	       "}\n" \
	       "#endif\n");
}

/#define[[:space:]]+SIG[A-Z]+[[:space:]]+[0-9]+.*/ {
	sigtbl[$3]=$2
}

END {
	printf("/*\n" \
		  " * UNIX signal names for build operating system kernel/libc configuration\n" \
		  " * Automatically generated on %s\n" \
		  " * DO NOT EDIT!\n" \
		  " */\n", strftime("%D %T"));

	print("#ifndef	_SIGNAMES_H");
	print("#define	_SIGNAMES_H");

	printf("\nstatic const struct signame {\n" \
		"	int signo;\n" \
		"	const char *name;\n" \
		"} signametbl[] = {\n");
	for (i=0; i < length(sigtbl); i++)
		if (sigtbl[i])
		printf("\t{ %d, \"%s\" },\n", i, substr(sigtbl[i], 4))
	print("};\n");

	ifdef_cpp_in();
	print("\nconst char *sig_to_str(int signo);\n");
	ifdef_cpp_out();

	print("\n#endif /* _SIGNAMES_H */");
}
