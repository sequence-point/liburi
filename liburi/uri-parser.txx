namespace uri {

template< typename Iterator >
optional< uri >
try_parse_uri(Iterator first, Iterator last)
{
  optional< std::string > opt_scheme;
  optional< std::string > opt_userinfo;
  optional< std::string > opt_host;
  optional< std::string > opt_port;
  std::string path;
  optional< std::string > opt_query;
  optional< std::string > opt_fragment;

  auto try_parse_scheme = [&](auto init) {
    auto c = init;

    std::string scheme;
    while (c != last && grammar::is_scheme(*c))
      scheme += *c++;

    if (c != last && *c == ':') {
      ++c; // skips ':'
      opt_scheme = std::move(scheme);
      return c;
    }

    return init;
  };

  auto try_parse_userinfo = [&](auto init) {
    auto c = init;

    std::string userinfo;
    while (c != last && grammar::is_userinfo(*c))
      userinfo += *c++;

    if (c != last && *c == '@') {
      ++c; // skips '@'
      opt_userinfo = std::move(userinfo);
      return c;
    }

    return init;
  };

  auto try_parse_host = [&](auto init) {
    auto c = init;

    opt_host = std::string{};

    while (c != last && grammar::is_host(*c))
      *opt_host += *c++;

    return c;
  };

  auto try_parse_port = [&](auto init) {
    auto c = init;

    if (c != last && *c == ':') {
      ++c; // skips ':'

      opt_port = std::string{};

      while (c != last && grammar::is_digit(*c))
        *opt_port += *c++;

      return c;
    }

    return init;
  };

  auto try_parse_authority = [&](auto init) {
    auto c = init;

    if (c == last || *c != '/')
      return init;

    ++c; // skips first '/'

    if (c == last || *c != '/')
      return init;

    ++c; // skips second '/'

    c = try_parse_userinfo(c);
    c = try_parse_host(c);
    c = try_parse_port(c);

    return c;
  };

  auto try_parse_path = [&](auto init) {
    auto c = init;

    while (c != last && (grammar::is_pchar(*c) || *c == '/'))
      path += *c++;

    return c;
  };

  auto try_parse_query = [&](auto init) {
    auto c = init;

    if (c != last && *c == '?') {
      ++c; // skips '?'
      opt_query = std::string{};

      while (c != last && grammar::is_query(*c))
        *opt_query += *c++;

      return c;
    }

    return init;
  };

  auto try_parse_fragment = [&](auto init) {
    auto c = init;

    if (c != last && *c == '#') {
      ++c; // skips '?#'

      opt_fragment = std::string{};

      while (c != last && grammar::is_fragment(*c))
        *opt_fragment += *c++;

      return c;
    }

    return init;
  };

  first = try_parse_scheme(first);
  first = try_parse_authority(first);
  first = try_parse_path(first);
  first = try_parse_query(first);
  first = try_parse_fragment(first);

  if (first != last)
    return {};

  return uri{ opt_scheme, opt_userinfo, opt_host,    opt_port,
              path,       opt_query,    opt_fragment };
}

} // namespace uri
