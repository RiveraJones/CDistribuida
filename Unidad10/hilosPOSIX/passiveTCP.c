/* passiveTCP.c - passiveTCP */

int	passivesock(const char *service, const char *transport,
		int qlen);

int
passiveTCP(const char *service, int qlen) {
  return passivesock(service, "tcp", qlen);
}
