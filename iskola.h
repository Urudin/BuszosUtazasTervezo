int getline(char *s, int n) {
	int c;
	char *t = s;
	while (n-- > 0 && (c = getchar()) != EOF && c != '\n')
		*t++ = c;
	*t = '\0';
	while (c != EOF&&c != '\n')
		c = getchar();
	return(t - s);
}

